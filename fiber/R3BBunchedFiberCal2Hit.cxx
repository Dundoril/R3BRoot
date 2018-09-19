#include "R3BBunchedFiberCal2Hit.h"
#include <cassert>
#include <TClonesArray.h>
#include <FairLogger.h>
#include "R3BTCalEngine.h"
#include "R3BBunchedFiberCalData.h"
#include "R3BBunchedFiberHitData.h"

R3BBunchedFiberCal2Hit::R3BBunchedFiberCal2Hit(const char *a_name, Int_t
    a_verbose, UInt_t a_mapmt_num, UInt_t a_spmt_num)
  : FairTask(TString("R3B") + a_name + "Cal2Hit", a_verbose)
  , fName(a_name)
  , fCalItems(nullptr)
  , fHitItems(new TClonesArray("R3BBunchedFiberHitData"))
  , fNofHitItems(0)
{
  fSideNum[0] = a_mapmt_num;
  fSideNum[1] = a_spmt_num;
}

R3BBunchedFiberCal2Hit::~R3BBunchedFiberCal2Hit()
{
  delete fHitItems;
}

void R3BBunchedFiberCal2Hit::CreateSub(enum Direction a_direction, UInt_t a_seq)
{
  fSubArray.push_back(Sub(a_direction, a_seq));
}

InitStatus R3BBunchedFiberCal2Hit::Init()
{
  auto mgr = FairRootManager::Instance();
  if (!mgr) {
    LOG(ERROR) << "FairRootManager not found." << FairLogger::endl;
    return kERROR;
  }
  auto name = fName + "Cal";
  fCalItems = (TClonesArray *)mgr->GetObject(name);
  if (!fCalItems) {
    LOG(ERROR) << "Branch " << name << " not found." << FairLogger::endl;
    return kERROR;
  }
  mgr->Register(fName + "Hit", "Land", fHitItems, kTRUE);
  // Resize per-channel info arrays.
  for (auto sub_i = 0; sub_i < fSubArray.size(); ++sub_i) {
    for (auto side_i = 0; side_i < 2; ++side_i) {
      fChannelArray[sub_i][side_i].resize(fSideNum[side_i]);
    }
  }
  return kSUCCESS;
}

InitStatus R3BBunchedFiberCal2Hit::ReInit()
{
  return kSUCCESS;
}

void R3BBunchedFiberCal2Hit::Exec(Option_t *option)
{
  // Find largest peak (max ToT) in every electronics channel, then combine
  // the channels to create fibers.
  for (auto sub_i = 0; sub_i < fSubArray.size(); ++sub_i) {
    for (auto side_i = 0; side_i < 2; ++side_i) {
      auto &array = fChannelArray[sub_i][side_i];
      for (auto it = array.begin(); array.end() != it; ++it) {
        it->prev = nullptr;
        it->max_ToT = -1;
      }
    }
  }
  auto const c_period = 4096e3 / CLOCK_TDC_MHZ;
  auto cal_num = fCalItems->GetEntriesFast();
  for (size_t j = 0; j < cal_num; ++j) {
    auto cur_cal = (R3BBunchedFiberCalData const *)fCalItems->At(j);

    auto side_i = cur_cal->IsMAPMT() ? 0 : 1;
    auto sub_i = (cur_cal->GetChannel() - 1) / fSideNum[side_i];
    assert(sub_i < fSubArray.size());

    auto channel_i = (cur_cal->GetChannel() - 1) % fSideNum[side_i];
    auto channel = &fChannelArray[sub_i][side_i].at(channel_i);
    auto prev_cal = channel->prev;
    if (prev_cal &&
        prev_cal->IsLeading() && cur_cal->IsTrailing()) {
      auto ToT = fmod(cur_cal->GetTime_ns() - prev_cal->GetTime_ns() + c_period, c_period);
      if (ToT > channel->max_ToT) {
        // We're only interested in the largest signals.
        channel->max_ToT = ToT;
        channel->max_leading = prev_cal;
        channel->max_trailing = cur_cal;
      }
    }
    channel->prev = cur_cal;
  }

  UInt_t sub_i = 0;
  for (auto it_sub = fSubArray.begin(); fSubArray.end() != it_sub; ++it_sub, ++sub_i) {
    auto const &mapmt_array = fChannelArray[sub_i][0];
    auto const &spmt_array = fChannelArray[sub_i][1];
    for (auto it_spmt = spmt_array.begin(); spmt_array.end() != it_spmt; ++it_spmt) {
      auto const &spmt = *it_spmt;
      if (0 > spmt.max_ToT) {
        continue;
      }
      for (auto it_mapmt = mapmt_array.begin(); mapmt_array.end() != it_mapmt; ++it_mapmt) {
        auto const &mapmt = *it_mapmt;
        if (0 > mapmt.max_ToT) {
          continue;
        }

        // We now have a good MAPMT hit, save a fiber!
        auto sub_fiber_id = (mapmt.max_leading->GetChannel() - 1) * fSideNum[1] +
            spmt.max_leading->GetChannel();
        // Offset by sub-detector sequence, this allows for e.g.:
        //  seq=0 -> fibers   1..128
        //  seq=1 -> fibers 129..256
        auto fiber_id = sub_fiber_id;// + it_sub->seq * fSideNum[0];
        // TODO: Use it_sub->direction to find real life coordinates.

        // Fix fiber installation mistakes.
        fiber_id = FixMistake(fiber_id);

        new ((*fHitItems)[fNofHitItems++])
            R3BBunchedFiberHitData(fiber_id,
                mapmt.max_leading->GetTime_ns(),
                spmt.max_leading->GetTime_ns(),
                mapmt.max_ToT,
                spmt.max_ToT,
                sqrt(mapmt.max_ToT*spmt.max_ToT));
      }
    }
  }
}

void R3BBunchedFiberCal2Hit::FinishEvent()
{
  fHitItems->Clear();
  fNofHitItems = 0;
}

void R3BBunchedFiberCal2Hit::FinishTask()
{
}

ClassImp(R3BBunchedFiberCal2Hit)
