// R3BFibDigitizer.cxx 07. 08. 2017.
// Created by: Aron Kripko

#include "R3BFibDigitizer.h"
#include "TClonesArray.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"


// includes for modeling
#include "TGeoManager.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "TGeoMatrix.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoBBox.h"
#include "TGeoCompositeShape.h"
#include "TGeoShapeAssembly.h"


#include "TVector3.h"
#include "TMath.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TH2F.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>


#include "R3BFibPoint.h"
#include "R3BMCTrack.h"
		
using std::cout;
using std::endl;
		

R3BFibDigitizer::R3BFibDigitizer()
  : FairTask("R3B Fib Digitization scheme ")
  //, fFibPoints(NULL)
  //, fFi6Points(NULL)
  , fFi11Points(NULL)
{
	  
	esigma = 0.001;
	tsigma = 0.01;
	ysigma = 1;
	  
}

R3BFibDigitizer::R3BFibDigitizer(Double_t e, Double_t t, Double_t y)
  : FairTask("R3B Fib Digitization scheme ")
  //, fFibPoints(NULL)
  //, fFi6Points(NULL)
  , fFi11Points(NULL)
{
	  
	esigma = e;
	tsigma = t;
	ysigma = y;
	  
}


R3BFibDigitizer::~R3BFibDigitizer() {
}


void R3BFibDigitizer::SetEnergyResolution(Double_t e)
{
	esigma = e;
}

void R3BFibDigitizer::SetTimeResolution(Double_t t)
{
	tsigma = t;
}

void R3BFibDigitizer::SetYPositionResolution(Double_t y)
{
	ysigma = y;
}

InitStatus R3BFibDigitizer::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) Fatal("Init", "No FairRootManager");
  //fFibPoints = (TClonesArray*) ioman->GetObject("FIBPoint");
  //fFi6Points = (TClonesArray*) ioman->GetObject("Fi6Point");
  fFi11Points = (TClonesArray*) ioman->GetObject("Fi11Point");
  
  fMCTrack = (TClonesArray*) ioman->GetObject("MCTrack");
   
  // Register output array DchDigi
  //fFibHits = new TClonesArray("R3BFibHitItem",1000);
  //ioman->Register("FibHit", "Digital response in Fib", fFibHits, kTRUE);
  
  //fFi6Hits = new TClonesArray("R3BFibHitItem",1000);
  //ioman->Register("Fi6Hit", "Digital response in Fi6", fFi6Hits, kTRUE);
  
  fFi11Hits = new TClonesArray("R3BFibHitItem",1000);
  ioman->Register("Fi11Hit", "Digital response in Fi11", fFi11Hits, kTRUE);
  
  //for sigmas
  prnd = new TRandom3();
  
  
  return kSUCCESS;

}


void R3BFibDigitizer::Exec(Option_t* opt)
{
   Reset();
   
   
   auto Digitize = [this](TClonesArray* Points, TClonesArray* Hits, Int_t NumOfFibers, Int_t Detector)
	{
	   
	   Int_t entryNum = Points -> GetEntries();
	   
	   if (!entryNum) return;
	   
	   //creating the storage for energy and time for each PMT
	   std::vector<Double_t>* energy_l = new std::vector<Double_t> [NumOfFibers/4];
	   
	   std::vector<Double_t> energy_r [8];
	   
	   std::vector<Double_t>* time_l = new std::vector<Double_t> [NumOfFibers/4];
	   
	   std::vector<Double_t> time_r [8];
	   
	   std::vector<Double_t>* y_l = new std::vector<Double_t> [NumOfFibers/4];
	   
	   std::vector<Double_t> y_r [8];
	   
	   for(Int_t i = 0; i < NumOfFibers/4; ++i)
	   {
		   time_l[i].push_back(99999);
		   energy_l[i].push_back(0);
		   y_l[i].push_back(0);
	   }
	   
	   for(Int_t i = 0; i < 8; ++i)
	   {
		   time_r[i].push_back(99999);
		   energy_r[i].push_back(0);
		   y_r[i].push_back(0);
	   }
	   
	   struct TempHit
	   {
		   Int_t fiberID;
		   Double_t Energy;
		   Double_t Time;
		   Double_t Y;
		   
		   TempHit(Int_t id, Double_t e, Double_t t, Double_t y):fiberID(id),Energy(e),Time(t), Y(y)
		   {
		   }
	   };
	   
	   //ordering the hits in time
	   
	   std::vector<TempHit> TempHits;
	   
	   for (Int_t i = 0; i < entryNum; ++i)
	   {
		   R3BFibPoint * data_element = (R3BFibPoint *) Points -> At(i);
		   
		   TempHits.push_back(TempHit(data_element -> GetDetectorID(), data_element -> GetEnergyLoss(), data_element -> GetTime(), data_element -> GetYIn()));
	   }
	   
	   std::sort(TempHits.begin(), TempHits.end(), [](const TempHit& lhs, const TempHit& rhs){ return lhs.Time < rhs.Time; });
	   
	   
	   //registering the hits in the PMTs
	   
	   for (TempHit& Hit : TempHits)
	   {
		   if(Hit.Energy < 0.0015)
		   {
			   continue;
		   }
		   
		   Int_t fiberID = Hit.fiberID;
		   
		   if(Hit.Time - time_l[fiberID / 4].back() < 30)
		   {	   		   
				energy_l[fiberID / 4].back() += Hit.Energy;
				
				y_l[fiberID / 4].back() = (time_l[fiberID / 4].back() > Hit.Time) ? Hit.Y : y_l[fiberID / 4].back();
		   
				time_l[fiberID / 4].back() = (time_l[fiberID / 4].back() > Hit.Time) ? Hit.Time : time_l[fiberID / 4].back();
		   }
		   else
		   {
			   energy_l[fiberID / 4].push_back(Hit.Energy);
			   time_l[fiberID / 4].push_back(Hit.Time);
			   y_l[fiberID / 4].push_back(Hit.Y);
		   }

		   if(Hit.Time - time_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back() < 30)
		   {
				energy_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back() += Hit.Energy;
		   
				y_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back() = (time_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back() > Hit.Time) ? Hit.Y : y_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back();
		   
				time_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back() = (time_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back() > Hit.Time) ? Hit.Time : time_r[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].back();
			
				}
		   else
		   {
			   energy_l[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].push_back(Hit.Energy);
			   time_l[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].push_back(Hit.Time);
			   y_l[(fiberID < NumOfFibers/2) ? fiberID % 4 : fiberID % 4 + 4].push_back(Hit.Y);
		   }
		}
		
		//creating the final hits

	   for (Int_t i =0; i < NumOfFibers/4; ++i)
	   {
		   for(Double_t& energyl : energy_l[i])
			if(energyl > 0.0015)
				{
					if(i < NumOfFibers/8)
					{
						for(Int_t j =0; j < 4; ++j)
						{
							for(Double_t& energyr : energy_r[j])
							{
								if(energyr > 0.0015)
								{
									if(std::fabs(time_l[i].at(&energyl-energy_l[i].data()) - time_r[j].at(&energyr-energy_r[j].data())) < 30)
									{
										new ((*Hits) [Hits->GetEntries()]) R3BFibHitItem((UInt_t) Detector ,(UInt_t) i * 4 + j, (i * 4 + j + .5) * ((Detector == 6)?0.05:0.02) * ((Detector == 5)?1:.5) - ((Detector == 6)?25.:20.), prnd->Gaus((y_l[i].at(&energyl-energy_l[i].data())+y_r[j].at(&energyr-energy_r[j].data()))/2, ysigma), 0, prnd->Gaus(energyl, esigma), prnd->Gaus(energyr, esigma), prnd->Gaus(time_l[i].at(&energyl-energy_l[i].data()), tsigma), prnd->Gaus(time_r[j].at(&energyr-energy_r[j].data()), tsigma));
									}
								}
							}
						}
					}
					else
					{
						for(Int_t j =4; j < 8; ++j)
						{
							for(Double_t& energyr : energy_r[j])
							{
								if(energyr > 0.0015)
								{
									if(std::fabs(time_l[i].at(&energyl-energy_l[i].data()) - time_r[j].at(&energyr-energy_r[j].data())) < 30)
									{
										new ((*Hits) [Hits->GetEntries()]) R3BFibHitItem((UInt_t) Detector ,(UInt_t) i * 4 + j - 4, (i * 4 + j + .5 - 4) * ((Detector == 6)?0.05:0.02) * ((Detector == 5)?1:.5) - ((Detector == 6)?25.:20.), prnd->Gaus((y_l[i].at(&energyl-energy_l[i].data())+y_r[j].at(&energyr-energy_r[j].data()))/2, ysigma), 0, prnd->Gaus(energyl, esigma), prnd->Gaus(energyr, esigma), prnd->Gaus(time_l[i].at(&energyl-energy_l[i].data()), tsigma), prnd->Gaus(time_r[j].at(&energyr-energy_r[j].data()), tsigma));
									}
								}
							}
						}
					}
				}
			}

            delete [] energy_l;
            delete [] time_l;
            delete [] y_l;
		};
		
		//running the digitizer for the Fi detectors
		
    //if(fFibPoints)
    //{
        //Digitize(fFibPoints, fFibHits, 4000, 4);
    //}

    //if(fFi6Points)
    //{
		//Digitize(fFi6Points, fFi6Hits, 2048, 6);
    //}

    if(fFi11Points)
    {
		Digitize(fFi11Points, fFi11Hits, 2048, 5);
    }
		
}
// -------------------------------------------------------------------------

void R3BFibDigitizer::Reset()
{
    //if (fFibHits) fFibHits->Clear();
    //if (fFi6Hits) fFi6Hits->Clear();
    if (fFi11Hits) fFi11Hits->Clear();
}   

void R3BFibDigitizer::Finish()
{
}

ClassImp(R3BFibDigitizer)
