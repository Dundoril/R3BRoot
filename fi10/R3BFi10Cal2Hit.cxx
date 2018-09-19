#include "R3BFi10Cal2Hit.h"

R3BFi10Cal2Hit::R3BFi10Cal2Hit(Int_t a_verbose)
  : R3BBunchedFiberCal2Hit("Fi10", a_verbose, 256, 1)
{
  CreateSub(VERTICAL, 0);
  CreateSub(HORIZONTAL, 0);
}

R3BFi10Cal2Hit::~R3BFi10Cal2Hit()
{
}

UInt_t R3BFi10Cal2Hit::FixMistake(UInt_t a_fiber_id)
{
//  if (192 == a_fiber_id) a_fiber_id = 15;
//  if (256 == a_fiber_id) a_fiber_id = 16;
 

  return a_fiber_id;
}

ClassImp(R3BFi10Cal2Hit)
