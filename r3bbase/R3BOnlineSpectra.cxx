// ------------------------------------------------------------
// -----                  R3BOnlineSpectra                -----
// -----          Created April 13th 2016 by M.Heil       -----
// ------------------------------------------------------------

/*
 * This task should fill histograms with detector variables which allow  
 * to test the detectors online
 *  
 */


#include "R3BOnlineSpectra.h"
#include "R3BLosCalData.h"
#include "R3BLosMappedData.h"
#include "R3BPaddleTamexMappedData.h"
#include "R3BPaddleCalData.h"
#include "R3BPtofHit.h"
#include "R3BPspxMappedData.h"
#include "R3BPspxCalData.h"
#include "R3BEventHeader.h"
#include "R3BTCalEngine.h"
#include "R3BTCalEngine.h"

#include "R3BBunchedFiberHitData.h"
#include "R3BBunchedFiberCalData.h"
#include "R3BBunchedFiberMappedData.h"

#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairRootManager.h"
#include "FairLogger.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"

#include "TClonesArray.h"
#include <iostream>
#include <sstream>
#include "TMath.h"
#define IS_NAN(x) TMath::IsNaN(x)
using namespace std;


R3BOnlineSpectra::R3BOnlineSpectra()
    : FairTask("OnlineSpectra", 1)
    , fCalItemsLos(NULL)
    , fCalItemsTofd(NULL)
    , fCalItemsPspx(NULL)
    , fHitItemsFi0(NULL)
    , fHitItemsFi1(NULL)
    , fHitItemsFi5(NULL)
    , fHitItemsFi6(NULL)
    , fCalItemsPtof(NULL)
    , fHitItemsPtof(NULL)
    , fMappedItemsLos(NULL)
    , fMappedItemsTofd(NULL)
    , fMappedItemsPspx(NULL)
    , fMappedItemsFi0(NULL)
    , fMappedItemsFi1(NULL)
    , fMappedItemsFi4(NULL)
    , fMappedItemsFi5(NULL)
    , fMappedItemsFi6(NULL)
    , fTrigger(-1)
    , fNofPlanes(4)  
    , fPaddlesPerPlane(6)    
    , flosVeffX1(1.)
    , flosVeffY1(1.)    
    , flosOffsetX1(0.)
    , flosOffsetY1(0.)
    , flosVeffX2(1.)
    , flosVeffY2(1.)    
    , flosOffsetX2(0.)
    , flosOffsetY2(0.)    
    , flosVeffX1T(1.)
    , flosVeffY1T(1.)    
    , flosOffsetX1T(0.)
    , flosOffsetY1T(0.)
    , flosVeffX2T(1.)
    , flosVeffY2T(1.)    
    , flosOffsetX2T(0.)
    , flosOffsetY2T(0.)
    , flosVeffX1wc(1.)
    , flosVeffY1wc(1.)    
    , flosOffsetX1wc(0.)
    , flosOffsetY1wc(0.)
    , flosVeffX2wc(1.)
    , flosVeffY2wc(1.)    
    , flosOffsetX2wc(0.)
    , flosOffsetY2wc(0.) 
    , flosVeffX1Q(1.)
    , flosVeffY1Q(1.)    
    , flosOffsetX1Q(0.)
    , flosOffsetY1Q(0.)
    , flosVeffX2Q(1.)
    , flosVeffY2Q(1.)    
    , flosOffsetX2Q(0.)
    , flosOffsetY2Q(0.) 
    , fClockFreq(1. / VFTX_CLOCK_MHZ * 1000.)
    , fNEvents(0)
    , fNEvents1(0)
	, fNEvents4(0)
    , fNEvents5(0)
    , fNEvents6(0)
{
}

R3BOnlineSpectra::R3BOnlineSpectra(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fCalItemsLos(NULL)
    , fCalItemsTofd(NULL)
    , fCalItemsPspx(NULL)
    , fHitItemsFi0(NULL)
    , fHitItemsFi1(NULL)
    , fHitItemsFi5(NULL)
    , fHitItemsFi6(NULL)
    , fCalItemsPtof(NULL)
    , fHitItemsPtof(NULL)
    , fMappedItemsLos(NULL)
    , fMappedItemsTofd(NULL)
    , fMappedItemsPspx(NULL)
    , fMappedItemsFi0(NULL)
    , fMappedItemsFi1(NULL)
    , fMappedItemsFi4(NULL)
    , fMappedItemsFi5(NULL)
    , fMappedItemsFi6(NULL)
    , fTrigger(-1)
    , fNofPlanes(4)  
    , fPaddlesPerPlane(6)    
    , flosVeffX1(1.)
    , flosVeffY1(1.)    
    , flosOffsetX1(0.)
    , flosOffsetY1(0.)
    , flosVeffX2(1.)
    , flosVeffY2(1.)    
    , flosOffsetX2(0.)
    , flosOffsetY2(0.)    
    , flosVeffX1T(1.)
    , flosVeffY1T(1.)    
    , flosOffsetX1T(0.)
    , flosOffsetY1T(0.)
    , flosVeffX2T(1.)
    , flosVeffY2T(1.)    
    , flosOffsetX2T(0.)
    , flosOffsetY2T(0.)
    , flosVeffX1wc(1.)
    , flosVeffY1wc(1.)    
    , flosOffsetX1wc(0.)
    , flosOffsetY1wc(0.)
    , flosVeffX2wc(1.)
    , flosVeffY2wc(1.)    
    , flosOffsetX2wc(0.)
    , flosOffsetY2wc(0.) 
    , flosVeffX1Q(1.)
    , flosVeffY1Q(1.)    
    , flosOffsetX1Q(0.)
    , flosOffsetY1Q(0.)
    , flosVeffX2Q(1.)
    , flosVeffY2Q(1.)    
    , flosOffsetX2Q(0.)
    , flosOffsetY2Q(0.)   
    , fClockFreq(1. / VFTX_CLOCK_MHZ * 1000.)
    , fNEvents(0)
    , fNEvents1(0)
    , fNEvents4(0)
    , fNEvents5(0)
    , fNEvents6(0)
{
}

R3BOnlineSpectra::~R3BOnlineSpectra()
{
}

InitStatus R3BOnlineSpectra::Init()
{

    LOG(INFO) << "R3BOnlineSpectra::Init " << FairLogger::endl;
    
	// try to get a handle on the EventHeader. EventHeader may not be 
	// present though and hence may be null. Take care when using.
	
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        FairLogger::GetLogger()->Fatal(MESSAGE_ORIGIN, "FairRootManager not found");
    header = (R3BEventHeader*)mgr->GetObject("R3BEventHeader");
    FairRunOnline *run = FairRunOnline::Instance();

// create histograms of all detectors    

//------------------------------------------------------------------------ 
// Los detector
	// get access to Mapped data
    fMappedItemsLos = (TClonesArray*)mgr->GetObject("LosMapped");
	// get access to cal data
    fCalItemsLos = (TClonesArray*)mgr->GetObject("LosCal");

	if(fMappedItemsLos){
		TCanvas *cLos = new TCanvas("Los", "LOS", 10, 10, 850, 950);
 
		fh_los_channels = new TH1F("los_channels", "LOS channels", 10, 0., 10.); 
		fh_los_channels->GetXaxis()->SetTitle("Channel number");
		fh_los_tres_MCFD = new TH1F("los_time_res_MCFD", "LOS MCFD Time resolution - raw", 8000, -4., 4.);
		fh_los_tres_MCFD->GetXaxis()->SetTitle("Time MCFD / ns");
		fh_los_tres_TAMEX = new TH1F("los_time_res_TAMEX", "LOS TAMEX Time resolution -raw ", 8000, -4., 4.);  
		fh_los_tres_TAMEX->GetXaxis()->SetTitle("Time TAMEX / ns"); 
		fh_los_pos = new TH2F("los_position", "LOS xy position not-calibrated", 2000, -10., 10.,2000, -10., 10.);
		fh_los_pos->GetXaxis()->SetTitle("X position / ns");
		fh_los_pos->GetYaxis()->SetTitle("Y position / ns"); 
		fh_los_tot = new TH1F("los_tot","LOS Time-over-Threshold",2500,0.,250.); 
		fh_los_tot->GetXaxis()->SetTitle("ToT / ns");
		fh_los_test = new TH2F("los_test", "LOS xy position not-calibrated with cuts", 2000, -10., 10.,2000, -10., 10.); 
   
		cLos->Divide(2, 3);
		cLos->cd(1);
		fh_los_channels->Draw();
		cLos->cd(3);
		fh_los_tres_MCFD->Draw();
		cLos->cd(4);
		fh_los_tres_TAMEX->Draw();
		cLos->cd(5);    
		fh_los_pos->Draw("colZ");
		cLos->cd(6);
		fh_los_tot->Draw();
		cLos->cd(0);
		run->AddObject(cLos);
	}
	

//-----------------------------------------------------------------------
// Fiber 0 detector

	// get access to Mapped data
    fMappedItemsFi0 = (TClonesArray*)mgr->GetObject("Fi0Mapped");

	// get access to cal data
    fHitItemsFi0 = (TClonesArray*)mgr->GetObject("Fi0Hit");
    if(fMappedItemsFi0){ 
		TCanvas *cFi0 = new TCanvas("Fiber0", "Fiber0", 10, 10, 510, 510);
		fh_Fi0_channels = new TH2F("fiber0_channels", "Fiber0 channels", 16, 1., 17., 16, 1., 17.);
		fh_Fi0_ToT_m = new TH2F("fiber0_ToT_m", "Fiber0 ToT of MAPMT", 260, 0., 260., 400, 0., 200.);    
		cFi0->Divide(2, 2);
		cFi0->cd(1);
		fh_Fi0_channels->Draw("colz");
		cFi0->cd(2);
		fh_Fi0_ToT_m->Draw("colz");
		cFi0->cd(0);
		run->AddObject(cFi0);
    }


//-----------------------------------------------------------------------
// Fiber 1 detector

    // get access to Mapped data
    fMappedItemsFi1 = (TClonesArray*)mgr->GetObject("Fi1Mapped");
    
    // get access to cal data
    fHitItemsFi1 = (TClonesArray*)mgr->GetObject("Fi1Hit");
	if(fMappedItemsFi1){ 
		TCanvas *cFi1 = new TCanvas("Fiber1", "Fiber1", 10, 10, 510, 510);
		fh_Fi1_channels = new TH1F("fiber1_channels", "Fiber1 channels", 550, 0., 550.);
		fh_Fi1_fibers = new TH1F("fiber1_number", "Fiber1 number", 550, 0., 550.);    
		fh_Fi1_multihit = new TH2F("fiber1_multihit", "Fiber1 multi hits", 300, 0., 300., 20, 0., 20.);
		fh_Fi1_ToF = new TH1F("fiber1_ToF", "Fiber1 ToF in ns", 10000, -500., 500.);    
		fh_Fi1_ToT = new TH2F("fiber1_ToT", "Fiber1 ToT", 550, 0., 550., 400, 0., 200.);    
		fh_Fi1_FibervsTime= new TH2F("fiber1_FibervsTime", "Fiber1 ToT vs Time", 550, 0., 550., 1000, 0., 100000.);
		fh_Fi1_xpos=new TH1F("fiber1_xpos", "x-position of fiber 1", 300, 0., 6.);
		fh_Fi1_ypos=new TH1F("fiber1_ypos", "y-position of fiber 1", 300, 0., 6.);
      
		fh_Fi1_multihit_s = new TH2F("fiber1_multihit_s", "Fiber1 multi hits of single PMT", 16, 0., 16., 20, 0., 20.);
		fh_Fi1_ToT_s = new TH2F("fiber1_ToT_s", "Fiber1 ToT of single PMT", 550, 0., 550., 400, 0., 200.);    
		fh_Fi1_ToTvsTime_s= new TH2F("fiber1_ToTvsTime_s", "Fiber1 ToT vs Time of single PMT", 550, 0., 550., 1000, 0., 100000.);
		fh_Fi1_test=new TH1F("fiber1_test", "Test ToF in ns", 10000, -500., 500.);    
      
		cFi1->Divide(3, 3);
		cFi1->cd(1);
		fh_Fi1_channels->Draw();
		cFi1->cd(2);
		fh_Fi1_fibers->Draw();
		cFi1->cd(3);
		fh_Fi1_ToF->Draw();
		cFi1->cd(4);
		fh_Fi1_multihit->Draw("colz");
		cFi1->cd(5);
		fh_Fi1_ToT->Draw("colz"); 
		cFi1->cd(6);
		fh_Fi1_FibervsTime->Draw("colz"); 
		cFi1->cd(7);
		fh_Fi1_multihit_s->Draw("colz");
		cFi1->cd(8);
		fh_Fi1_ToT_s->Draw("colz"); 
		cFi1->cd(9);
		fh_Fi1_ToTvsTime_s->Draw("colz"); 
      
		cFi1->cd(0);
		run->AddObject(cFi1);

        FILE *fin = NULL;
        fin = fopen("max_values1.dat", "r");
        if(!fin){
			cerr << "Could not open file with max values for reading!\n";
		}
		else {
			Int_t fib;
			Float_t max;
			for(UInt_t i=1;i<513;i++){
				fscanf (fin, "%i ", &fib);
				fscanf (fin, "%f ", &max);
//				cout<<"Lesen "<<fib<<"  "<<max<<endl;
				max_value1[fib]=max;
			}
			fclose(fin);
		}                
    }
    

//-----------------------------------------------------------------------
// Fiber 4 detector

    // get access to Mapped data
    fMappedItemsFi4 = (TClonesArray*)mgr->GetObject("Fi4Mapped");

    // get access to cal data
    fHitItemsFi4 = (TClonesArray*)mgr->GetObject("Fi4Hit");

    if((fMappedItemsFi4)&&(fMappedItemsFi1)){  

      TCanvas *cFi1vsF4 = new TCanvas("cFiber1_vs_Fiber4", "Fiber1 vs Fiber4", 510, 510, 1010, 1010);

      fh_Fi1vsFi4= new TH2F("Fiber1_vs_Fiber4", "Fiber1 vs Fiber4", 2100, 0., 2100., 2000, -100., 100.);
      fh_Fi1vsFi4->GetXaxis()->SetTitle("Fi4");
      fh_Fi1vsFi4->GetYaxis()->SetTitle("Fi1");  

      cFi1vsF4->cd();
      fh_Fi1vsFi4->Draw("colz");


    }
    
    
	if(fMappedItemsFi4){  
		TCanvas *cFi4 = new TCanvas("Fiber4", "Fiber4", 510, 510, 1010, 1010);
		fh_Fi4_channels = new TH1F("fiber4_channels", "Fiber4 channels", 600, 0., 600.);
		fh_Fi4_fibers = new TH1F("fiber4_number", "Fiber4 number", 2100, 0., 2100.);    
		fh_Fi4_mult= new TH1F("fiber4_mult", "Fiber4 mult of MAPMT", 260, 0., 260.); 
		fh_Fi4_multihit = new TH2F("fiber4_multihit", "Fiber4 multi hits", 600, 0., 600., 20, 0., 20.);
		fh_Fi4_ToT = new TH2F("fiber4_ToT", "Fiber4 ToT", 2100, 0., 2100., 400, 0., 200.);    
		fh_Fi4_ToT_cut = new TH2F("fiber4_ToT_cut", "Fiber4 ToT with cut", 2100, 0., 2100., 400, 0., 200.);    
		fh_Fi4_FibervsTime= new TH2F("fiber4_FibervsTime", "Fiber4 Fiber vs Time", 2100, 0., 2100., 8000, 0., 10000000.);
		fh_Fi4_FibervsTime->GetXaxis()->SetTitle("Fiber number");
		fh_Fi4_FibervsTime->GetYaxis()->SetTitle("Event number");  
		fh_Fi4_multihit_s = new TH2F("fiber4_multihit_s", "Fiber4 multi hits of single PMT", 16, 0., 16., 20, 0., 20.);
		fh_Fi4_ToT_s = new TH2F("fiber4_ToT_s", "Fiber4 ToT of single PMT", 2100, 0., 2100., 400, 0., 200.);    
		fh_Fi4_ToTvsTime_s= new TH2F("fiber4_ToTvsTime_s", "Fiber4 ToT vs Time of single PMT", 1000, 0., 100., 8000, 0., 10000000.);
		fh_Fi4_ToF=new TH1F("fiber4_ToF", "Fiber4 ToF in ns", 10000, -500., 500.);    
		fh_Fi4_test=new TH1F("fiber4_test", "Test ToF in ns", 10000, -50000., 50000.);    
		fh_Fi4_xpos=new TH1F("fiber4_xpos", "x-position of fiber 4", 2500, 0., 50.);
		fh_Fi4_ypos=new TH1F("fiber4_ypos", "y-position of fiber 4", 2100, -1050., 1050.);
		fh_Fi4_eff = new TH1F("fiber4_eff", "Fiber4 efficiency", 2500, 0., 50.);    

		cFi4->Divide(3, 3);
		cFi4->cd(1);
		fh_Fi4_channels->Draw();
		cFi4->cd(2);
		fh_Fi4_fibers->Draw();
		cFi4->cd(3);
		fh_Fi4_mult->Draw(); 
		cFi4->cd(4);
		fh_Fi4_multihit->Draw("colz");
		cFi4->cd(5);
		fh_Fi4_ToT->Draw("colz"); 
		cFi4->cd(6);
		fh_Fi4_FibervsTime->Draw("colz"); 
		cFi4->cd(7);
		fh_Fi4_multihit_s->Draw("colz");
		cFi4->cd(8);
		fh_Fi4_ToT_s->Draw("colz"); 
		cFi4->cd(9);
		fh_Fi4_ToTvsTime_s->Draw("colz"); 
		cFi4->cd(0);
		run->AddObject(cFi4);
			
        FILE *fin = NULL;
        fin = fopen("max_values4.dat", "r");
        if(!fin){
			cerr << "Could not open file with max values for reading!\n";
		}
		else {
			Int_t fib;
			Float_t max;
			for(UInt_t i=1;i<2054;i++){
				fscanf (fin, "%i ", &fib);
				fscanf (fin, "%f ", &max);
//				cout<<"Lesen "<<fib<<"  "<<max<<endl;
				max_value4[fib]=max;
			}
			fclose(fin);
		}                
    }
    
    
    //-----------------------------------------------------------------------
    // Fiber 5 detector
    
    // get access to Mapped data
    fMappedItemsFi5 = (TClonesArray*)mgr->GetObject("Fi5Mapped");
    
    // get access to cal data
    fHitItemsFi5 = (TClonesArray*)mgr->GetObject("Fi5Hit");


    if((fMappedItemsFi4)&&(fMappedItemsFi5)){  

      TCanvas *cFi5vsF4 = new TCanvas("Fiber5_vs_Fiber4", "Fiber5 vs Fiber4", 510, 510, 510, 510);

      fh_Fi5vsFi4= new TH2F("Fiber5_vs_Fiber4", "Fiber5 vs Fiber4", 2100, 0., 2100., 1100, 0., 1100.);
      fh_Fi5vsFi4->GetXaxis()->SetTitle("Fi4");
      fh_Fi5vsFi4->GetYaxis()->SetTitle("Fi5");  

      cFi5vsF4->cd();
      fh_Fi5vsFi4->Draw("colz");


    }

	if(fMappedItemsFi5){  
		TCanvas *cFi5 = new TCanvas("Fiber5", "Fiber5", 100, 100, 600, 600);
		fh_Fi5_channels = new TH1F("fiber5_channels", "Fiber5 channels", 300, 0., 300.);
		fh_Fi5_fibers = new TH1F("fiber5_number", "Fiber5 number", 1200, 0., 1200.);    
		fh_Fi5_mult= new TH1F("fiber5_mult", "Fiber5 mult of MAPMT", 260, 0., 260.); 
		fh_Fi5_multihit = new TH2F("fiber5_multihit", "Fiber5 multi hits", 300, 0., 300., 20, 0., 20.);
		fh_Fi5_ToT = new TH2F("fiber5_ToT", "Fiber5 ToT", 1200, 0., 1200., 400, 0., 200.);    
		fh_Fi5_ToT_m = new TH2F("fiber5_ToT_m", "Fiber5 ToT of MAPMT", 1200, 0., 1200., 400, 0., 200.);    
		fh_Fi5_FibervsTime= new TH2F("fiber5_FibervsTime", "Fiber5 Fiber vs Time", 1200, 0., 1200., 10000, 0., 10000000.);
		fh_Fi5_FibervsTime->GetXaxis()->SetTitle("Fiber number");
		fh_Fi5_FibervsTime->GetYaxis()->SetTitle("Event number");  
		fh_Fi5_multihit_s = new TH2F("fiber5_multihit_s", "Fiber5 multi hits of single PMT", 16, 0., 16., 20, 0., 20.);
		fh_Fi5_ToT_s = new TH2F("fiber5_ToT_s", "Fiber5 ToT of single PMT", 10, 0., 10., 400, 0., 200.);    
		fh_Fi5_ToTvsTime_m= new TH2F("fiber5_ToTvsTime_m", "Fiber5 ToT vs Time of MAPMT", 1200, 0., 120., 8000, 0., 800000.);
		fh_Fi5_xpos=new TH1F("fiber5_xpos", "x-position of fiber 5", 2500, 0., 50.);
		fh_Fi5_ToF=new TH1F("fiber5_ToF", "Fiber5 ToF in ns", 10000, -500., 500.);    
		fh_Fi5_ypos=new TH1F("fiber5_ypos", "y-position of fiber 5", 2100, -1050., 1050.);
		fh_Fi5_eff=new TH1F("fiber5_eff", "efficiency of fiber 5", 2500, 0., 50.);
		for (Int_t j = 0; j < 8; j++){
			char strName1[255];
			char strName2[255];
			sprintf(strName1, "fiber5_ToT_vsTime_s%d", j);
			sprintf(strName2, "Fiber5 ToT vs Time of single PMT %d", j);
			fh_Fi5_ToTvsTime_s[j]= new TH2F(strName1, strName2, 100, 0., 50., 5000, 0., 5000000.);
		}		
      
		cFi5->Divide(3, 3);
		cFi5->cd(1);
		fh_Fi5_channels->Draw();
		cFi5->cd(2);
		fh_Fi5_fibers->Draw();
		cFi5->cd(3);
		fh_Fi5_mult->Draw(); 
		cFi5->cd(4);
		fh_Fi5_multihit->Draw("colz");
		cFi5->cd(5);
		fh_Fi5_ToT->Draw("colz"); 
		cFi5->cd(6);
		fh_Fi5_FibervsTime->Draw("colz"); 
		cFi5->cd(7);
		fh_Fi5_multihit_s->Draw("colz");
		cFi5->cd(8);
		fh_Fi5_ToT_s->Draw("colz"); 
		cFi5->cd(9);
		fh_Fi5_ToTvsTime_s[0]->Draw("colz"); 
		cFi5->cd(0);
		run->AddObject(cFi5);
      
		FILE *fin = NULL;

		fin = fopen("max_values5.dat", "r");
		if(!fin){
			cerr << "Could not open file with max values for reading!\n";
		}
		else {
			Int_t fib;
			Float_t max;
	
			for(UInt_t i=1;i<1030;i++){
				fscanf (fin, "%i ", &fib);
				fscanf (fin, "%f ", &max);
//				cout<<"Lesen "<<fib<<"  "<<max<<endl;
				max_value5[fib]=max;
			}
			fclose(fin);
		}
	}
    
//-----------------------------------------------------------------------
// Fiber 6 detector
    
    // get access to Mapped data
    fMappedItemsFi6 = (TClonesArray*)mgr->GetObject("Fi6Mapped");
    // get access to cal data
    fHitItemsFi6 = (TClonesArray*)mgr->GetObject("Fi6Hit");
    
	if(fMappedItemsFi6){  
		TCanvas *cFi6 = new TCanvas("Fiber6", "Fiber6", 10, 10, 510, 510);
		fh_Fi6_channels = new TH1F("fiber6_channels", "Fiber6 channels", 300, 0., 300.);
		fh_Fi6_fibers = new TH1F("fiber6_number", "Fiber6 number", 600, 0., 600.);    
		fh_Fi6_mult= new TH1F("fiber6_mult", "Fiber6 mult of MAPMT", 260, 0., 260.); 
		fh_Fi6_multihit = new TH2F("fiber6_multihit", "Fiber6 multi hits", 300, 0., 300., 20, 0., 20.);
		fh_Fi6_ToT = new TH2F("fiber6_ToT", "Fiber6 ToT", 600, 0., 600., 400, 0., 200.);    
		fh_Fi6_ToT_m = new TH2F("fiber6_ToT_m", "Fiber6 ToT of MAPMT", 600, 0., 600., 400, 0., 200.);    
		fh_Fi6_FibervsTime= new TH2F("fiber6_FibervsTime", "Fiber6 ToT vs Time", 600, 0., 600., 1000, 0., 5000000.);
		fh_Fi6_FibervsTime->GetXaxis()->SetTitle("Fiber number");
		fh_Fi6_FibervsTime->GetYaxis()->SetTitle("Event number");  
		fh_Fi6_ToTvsTime_m= new TH2F("fiber6_ToTvsTime_m", "Fiber6 ToT vs Time of MAPMT", 120, 0., 120., 50000, 0., 5000000.);
		fh_Fi6_ToT_s = new TH2F("fiber6_ToT_s","Fiber6 ToT of single PMT" , 10, 0., 10., 400, 0., 200.);
		fh_Fi6_multihit_s = new TH2F("fiber6_multihit_s", "Fiber6 multi hits of single PMT", 10, 0., 10., 20, 0., 20.);
		fh_Fi6_xpos=new TH1F("fiber6_xpos", "x-position of fiber 6", 1200, 0., 60.);
		fh_Fi6_ypos=new TH1F("fiber6_ypos", "y-position of fiber 6", 2100, -1050., 1050.);
		fh_Fi6_ToF=new TH1F("fiber6_ToF", "Fiber6 ToF in ns", 10000, -500., 500.);    
		fh_Fi6_eff=new TH1F("fiber6_eff", "efficiency of fiber 6", 2500, 0., 50.);
		for (Int_t j = 0; j < 4; j++){
			char strName1[255];
			char strName2[255];
			sprintf(strName1, "fiber6_ToT_vsTime_s%d", j);
			sprintf(strName2, "Fiber6 ToT vs Time of single PMT %d", j);
			fh_Fi6_ToTvsTime_s[j]= new TH2F(strName1, strName2, 100, 0., 50., 50000, 0., 5000000.);
		}		
      
		cFi6->Divide(3, 3);
		cFi6->cd(1);
		fh_Fi6_channels->Draw();
		cFi6->cd(2);
		fh_Fi6_fibers->Draw();
		cFi6->cd(3);
		fh_Fi6_mult->Draw();
		cFi6->cd(4);
		fh_Fi6_multihit->Draw("colz");
		cFi6->cd(5);
		fh_Fi6_ToT->Draw("colz"); 
		cFi6->cd(6);
		fh_Fi6_FibervsTime->Draw("colz"); 
		cFi6->cd(7);
		fh_Fi6_multihit_s->Draw("colz");
		cFi6->cd(8);
		fh_Fi6_ToT_s->Draw("colz"); 
		cFi6->cd(9);
		fh_Fi6_ToTvsTime_s[0]->Draw("colz"); 
		cFi6->cd(0);
		run->AddObject(cFi6);
      
		FILE *fin = NULL;

		fin = fopen("max_values6.dat", "r");
		if(!fin){
			cerr << "Could not open file with max values for reading!\n";
		}
		else {
			Int_t fib;
			Float_t max;
 
			for(UInt_t i=1;i<513;i++){
				fscanf (fin, "%i ", &fib);
				fscanf (fin, "%f ", &max);
//				cout<<"Lesen "<<fib<<"  "<<max<<endl;
				max_value6[fib]=max;
			}
			fclose(fin);
		}      
    }
    //---------------------------------------------------------------------------------------
//Ptof detector
    
    fCalItemsPtof = (TClonesArray*)mgr->GetObject("PtofCal");
    fHitItemsPtof = (TClonesArray*)mgr->GetObject("PtofHit");
   
	if(fCalItemsPtof){

		TCanvas *cPtof_plane = new TCanvas("Ptof_plane", "Ptof plane", 10, 10, 510, 510);
		cPtof_plane->Divide(1, 2);
      
		fh_ptof_channels = new TH1F("Ptof_channels", "Ptof channels", 65, 0., 65.);
		cPtof_plane->cd(1);
		fh_ptof_channels->Draw();
      
		fh_ptof_channels_cut = new TH1F("Ptof_channels_cut", "Ptof channels with cut", 65, 0., 65.);
		cPtof_plane->cd(2);
		fh_ptof_channels_cut->Draw();
		run->AddObject(cPtof_plane);
      
		TCanvas *cPtof_test = new TCanvas("Ptof_test", "Ptof test", 10, 10, 510, 510);
		cPtof_test->Divide(1, 1);
 		
 		fh_ptof_ToF = new TH1F("Ptof_ToF", "Ptof ToF", 5000, -500., 2000.);
     
		fh_ptof_test1 = new TH1F("Ptof_test1", "Ptof test1", 1000, 0., 100.);
		fh_ptof_test2 = new TH1F("Ptof_test2", "Ptof test2", 1000, 0., 100.);
		fh_ptof_qbar_q_vs_pos = new TH2F("Ptof_q_vs_pos", "Ptof Q vs x", 1000, -100., 100.,1000,0,100.);
		cPtof_test->cd(1);
		fh_ptof_test1->Draw();
//		cPtof_test->cd(2);
//		fh_ptof_test2->Draw();
      
		run->AddObject(cPtof_test);
      
		TCanvas* cPtof1;
		cPtof1 = new TCanvas("Ptof1", "Ptof1", 10, 10, 500, 500);
		cPtof1->Divide(3,3);
		for (Int_t j = 1; j < 2*N_PADDLE_MAX_PTOF+1; j++){
			char strName[255];
			sprintf(strName, "ToT_Bar_%d_PM_1", j);
			fh_ptof_TotPm1[j] = new TH1F(strName, "", 1000, 0., 100.);
			cPtof1->cd(j);
			fh_ptof_TotPm1[j]->Draw();           
		}
		run->AddObject(cPtof1);
      
		TCanvas* cPtof2;
		cPtof2 = new TCanvas("Ptof2", "Ptof2", 10, 10, 500, 500);
		cPtof2->Divide(3,3);
		for (Int_t j = 1; j < 2*N_PADDLE_MAX_PTOF+1; j++){
			char strName[255];
			sprintf(strName, "ToT_Bar_%d_PM_2", j);
			fh_ptof_TotPm2[j] = new TH1F(strName, "", 1000, 0., 100.);
			cPtof2->cd(j);
			fh_ptof_TotPm2[j]->Draw();           
		}
		run->AddObject(cPtof2);
	}
    
    
//---------------------------------------------------------------------------------------------------
//TofD detector

	fMappedItemsTofd = (TClonesArray*)mgr->GetObject("TofdMapped");
	if(fMappedItemsTofd){
		TCanvas *cTofd_planes = new TCanvas("TOFD_planes", "TOFD planes", 10, 10, 500, 500);
		cTofd_planes->Divide(3, 2);
		
		for (Int_t j = 0; j < fNofPlanes; j++)
		{
			 char strName1[255];
			 sprintf(strName1, "tofd_channels_plane_%d", j);
			 char strName2[255];
			 sprintf(strName2, "Tofd channels plane %d", j);        
			 fh_tofd_channels[j] = new TH1F(strName1, strName2, 16, -8., 8.);
			 cTofd_planes->cd(j+1);
			 fh_tofd_channels[j]->Draw();
		}
		
		
	   
		TCanvas* cTofd[fNofPlanes];
		for (Int_t i = 0; i < fNofPlanes; i++)
		{		
			char strName[255];
			sprintf(strName, "TOFD_Plane_%d", i);
			cTofd[i] = new TCanvas(strName, "", 10, 10, 500, 500);
			cTofd[i]->Divide(3,4);
			for (Int_t j = 0; j < fPaddlesPerPlane; j++)
			{
				sprintf(strName, "ToT_Plane_%d_Bar_%d_PM_1", i, j);
				fh_tofd_TotPm1[i][j] = new TH1F(strName, "", 5000, 0., 500.);
				cTofd[i]->cd(2*j+1);
				fh_tofd_TotPm1[i][j]->Draw();
				sprintf(strName, "ToT_Plane_%d_Bar_%d_PM_2", i, j);
				fh_tofd_TotPm2[i][j] = new TH1F(strName, "", 5000, 0., 500.);
				cTofd[i]->cd(2*j+2);
				fh_tofd_TotPm1[i][j]->Draw();
			   
			}
		}
    }
    fCalItemsTofd = (TClonesArray*)mgr->GetObject("TofdCal");

// -------------------------------------------------------------------------
// Pspx Data
    
    fMappedItemsPspx = (TClonesArray*)mgr->GetObject("PspxMappedData");
    fCalItemsPspx = (TClonesArray*)mgr->GetObject("PspxCalData");
    
    if(fMappedItemsPspx || fCalItemsPspx){
		for(UInt_t i=0;i<4;i++){
			  fh_pspx_strips_psp[i] = new TH1F(Form("pspx_strips_psp%d",i), Form("Pspx strips PSP %d",i+1), 16, 1, 17); 
		
		  fh_pspx_energy_psp[i] = new TH1F(Form("pspx_energy_psp%d",i), Form("Pspx cathode energy PSP %d",i+1), 200, 0, 35000); 
		  
		  fh_pspx_multiplicity_psp[i] = new TH1F(Form("pspx_multiplicity_psp%d",i), Form("Pspx multiplicity PSP %d",i+1), 10, 0, 10); 
		}
		
		fh_pspx_strips_psp[0]->GetXaxis()->SetTitle("y position / strips with 3mm width");
		fh_pspx_strips_psp[1]->GetXaxis()->SetTitle("x position / strips with 3mm width");
		fh_pspx_strips_psp[2]->GetXaxis()->SetTitle("y position / strips with 3mm width");
		fh_pspx_strips_psp[3]->GetXaxis()->SetTitle("x position / strips with 3mm width"); 
		
		fh_pspx_pos1_strips = new TH2F("pspx_pos1_strips", "Pspx Position1", 16, 1, 17,16,1,17); 
		fh_pspx_pos2_strips = new TH2F("pspx_pos2_strips", "Pspx Position2", 16, 1, 17,16,1,17);  
		
		fh_pspx_pos1_strips->GetYaxis()->SetTitle("y position / strips with 3mm width");
		fh_pspx_pos1_strips->GetXaxis()->SetTitle("x position / strips with 3mm width"); 
		fh_pspx_pos2_strips->GetYaxis()->SetTitle("y position / strips with 3mm width");
		fh_pspx_pos2_strips->GetXaxis()->SetTitle("x position / strips with 3mm width");
		
		fh_pspx_pos1_energy = new TH2F("pspx_pos1_energy", "Pspx Position1", 32, -1, 1,32,-1,1); 
		fh_pspx_pos2_energy = new TH2F("pspx_pos2_energy", "Pspx Position2", 32, -1, 1,32,-1,1);  
		
		fh_pspx_pos1_energy->GetYaxis()->SetTitle("y position / a.u.");
		fh_pspx_pos1_energy->GetXaxis()->SetTitle("x position / a.u."); 
		fh_pspx_pos2_energy->GetYaxis()->SetTitle("y position / a.u.");
		fh_pspx_pos2_energy->GetXaxis()->SetTitle("x position / a.u.");
		
		
		fh_pspx_cor_x_strips = new TH2F("pspx_cor_x_strips", "Pspx Position1", 16, 1, 17,16,1,17); 
		fh_pspx_cor_y_strips = new TH2F("pspx_cor_y_strips", "Pspx Position2", 16, 1, 17,16,1,17);  
		
		fh_pspx_cor_x_strips->GetYaxis()->SetTitle("x position / strips with 3mm width");
		fh_pspx_cor_x_strips->GetXaxis()->SetTitle("x position / strips with 3mm width"); 
		fh_pspx_cor_y_strips->GetYaxis()->SetTitle("y position / strips with 3mm width");
		fh_pspx_cor_y_strips->GetXaxis()->SetTitle("y position / strips with 3mm width");
		
		fh_pspx_cor_x_energy = new TH2F("pspx_cor_x_energy", "Pspx Position1", 32, -1, 1,32,-1,1); 
		fh_pspx_cor_y_energy = new TH2F("pspx_cor_y_energy", "Pspx Position2", 32, -1, 1,32,-1,1);  
		
		fh_pspx_cor_x_energy->GetYaxis()->SetTitle("x position / a.u.");
		fh_pspx_cor_x_energy->GetXaxis()->SetTitle("x position / a.u."); 
		fh_pspx_cor_y_energy->GetYaxis()->SetTitle("y position / a.u.");
		fh_pspx_cor_y_energy->GetXaxis()->SetTitle("y position / a.u.");
		
		TCanvas *cpspx_position = new TCanvas("pspx_position", "pspx_position", 10, 10, 500, 500);
		cpspx_position->Divide(2, 2);
		
		cpspx_position->cd(1);
		fh_pspx_pos1_strips->Draw();
		cpspx_position->cd(2);
		fh_pspx_pos2_strips->Draw();
		cpspx_position->cd(3);
		fh_pspx_pos1_energy->Draw();
		cpspx_position->cd(4);
		fh_pspx_pos2_energy->Draw();
		cpspx_position->cd(0);
		run->AddObject(cpspx_position);
		
		
		TCanvas *cpspx_strips = new TCanvas("pspx_strips", "pspx_strips", 10, 10, 500, 500);
		cpspx_strips->Divide(2, 2);
		
		cpspx_strips->cd(1);
		fh_pspx_strips_psp[0]->Draw();
		cpspx_strips->cd(2);
		fh_pspx_strips_psp[1]->Draw();
		cpspx_strips->cd(3);
		fh_pspx_strips_psp[2]->Draw();
		cpspx_strips->cd(4);
		fh_pspx_strips_psp[3]->Draw();
		cpspx_strips->cd(0);
		run->AddObject(cpspx_strips);
		
		
		TCanvas *cpspx_energy = new TCanvas("pspx_energy", "pspx_energy", 10, 10, 500, 500);
		cpspx_energy->Divide(2, 2);
		
		cpspx_energy->cd(1);
		fh_pspx_energy_psp[0]->Draw();
		cpspx_energy->cd(2);
		fh_pspx_energy_psp[1]->Draw();
		cpspx_energy->cd(3);
		fh_pspx_energy_psp[2]->Draw();
		cpspx_energy->cd(4);
		fh_pspx_energy_psp[3]->Draw();
		cpspx_energy->cd(0);
		run->AddObject(cpspx_energy);
		
		
		TCanvas *cpspx_multiplicity = new TCanvas("pspx_multiplicity", "pspx_multiplicity", 10, 10, 500, 500);
		cpspx_multiplicity->Divide(2, 2);
		
		cpspx_multiplicity->cd(1);
		fh_pspx_multiplicity_psp[0]->Draw();
		cpspx_multiplicity->cd(2);
		fh_pspx_multiplicity_psp[1]->Draw();
		cpspx_multiplicity->cd(3);
		fh_pspx_multiplicity_psp[2]->Draw();
		cpspx_multiplicity->cd(4);
		fh_pspx_multiplicity_psp[3]->Draw();
		cpspx_multiplicity->cd(0);
		run->AddObject(cpspx_energy);
		
		TCanvas *cpspx_cor = new TCanvas("pspx_cor", "pspx_cor", 10, 10, 500, 500);
		cpspx_cor->Divide(2, 2);
		
		cpspx_cor->cd(1);
		fh_pspx_cor_x_strips->Draw();
		cpspx_cor->cd(2);
		fh_pspx_cor_y_strips->Draw();
		cpspx_cor->cd(3);
		fh_pspx_cor_x_energy->Draw();
		cpspx_cor->cd(4);
		fh_pspx_cor_y_energy->Draw();
		cpspx_strips->cd(0);
		run->AddObject(cpspx_cor);
    }
 
 
 
    return kSUCCESS;
}



void R3BOnlineSpectra::Exec(Option_t* option)
{
//	if(fNEvents>1000000 && fNEvents<2500000) {
	if(1>0){

//----------------------------------------------------------------------
// LOS detector
//----------------------------------------------------------------------
    Bool_t los_cut1=false;	
    	
    Bool_t fiber4_cut1=false;
    
	Double_t time_r_V = 0.0/0.0;   
	Double_t time_t_V = 0.0/0.0;       
	Double_t time_l_V = 0.0/0.0;       
	Double_t time_b_V = 0.0/0.0;           
	Double_t time_r_L = 0.0/0.0;
	Double_t time_r_T = 0.0/0.0;
	Double_t time_l_L = 0.0/0.0;
	Double_t time_l_T = 0.0/0.0;
	Double_t time_t_L = 0.0/0.0;
	Double_t time_t_T = 0.0/0.0;
	Double_t time_b_L = 0.0/0.0;
	Double_t time_b_T = 0.0/0.0;  
	Double_t time_rt_V = 0.0/0.0;   
	Double_t time_lt_V = 0.0/0.0;       
	Double_t time_lb_V = 0.0/0.0;       
	Double_t time_rb_V = 0.0/0.0;           
	Double_t time_rt_L = 0.0/0.0;
	Double_t time_rt_T = 0.0/0.0;
	Double_t time_lb_L = 0.0/0.0;
	Double_t time_lb_T = 0.0/0.0;
	Double_t time_lt_L = 0.0/0.0;
	Double_t time_lt_T = 0.0/0.0;
	Double_t time_rb_L = 0.0/0.0;
	Double_t time_rb_T = 0.0/0.0;              
	Double_t t_hor_M = 0.0/0.0;
	Double_t t_ver_M = 0.0/0.0;
	Double_t t_45_M = 0.0/0.0;
	Double_t t_135_M = 0.0/0.0;
	Double_t t_hor_T = 0.0/0.0;
	Double_t t_ver_T = 0.0/0.0;
	Double_t t_45_T = 0.0/0.0;
	Double_t t_135_T = 0.0/0.0;
	Double_t timeLosM = 0.0/0.0;
	Double_t LosTresM = 0.0/0.0;
	Double_t timeLosT = 0.0/0.0;
	Double_t LosTresT = 0.0/0.0;
	Double_t tot=0./0.0; 
	Double_t totr = 0.0/0.0;
	Double_t totl = 0.0/0.0;
	Double_t tott = 0.0/0.0;
	Double_t totb = 0.0/0.0; 
	Double_t totrt = 0.0/0.0;
	Double_t totlt = 0.0/0.0;
	Double_t totlb = 0.0/0.0;
	Double_t totrb = 0.0/0.0;
	Double_t tot_45 = 0.0/0.0;
	Double_t tot_135 = 0.0/0.0;
	Double_t tot_hor = 0.0/0.0;
	Double_t tot_ver = 0.0/0.0;
	Double_t xT_cm = 0.0/0.0;
	Double_t yT_cm = 0.0/0.0;
	Double_t x_cm = 0.0/0.0;
	Double_t y_cm = 0.0/0.0;
    Double_t xToT = 0.0/0.0;
	Double_t yToT = 0.0/0.0;       
           
    Double_t timeTofd=0;
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
        FairLogger::GetLogger()->Fatal(MESSAGE_ORIGIN, "FairRootManager not found");
	// check for requested trigger (Todo: should be done globablly / somewhere else)
    if ((fTrigger >= 0) && (header) && (header->GetTrigger() != fTrigger))
		return;


    if(fMappedItemsLos && fMappedItemsLos->GetEntriesFast())
    {
      Int_t nHits = fMappedItemsLos->GetEntriesFast();
      for (Int_t ihit = 0; ihit < nHits; ihit++)
      {
         R3BLosMappedData* hit = (R3BLosMappedData*)fMappedItemsLos->At(ihit);
         if (!hit) continue;

         // channel numbers are stored 1-based (1..n)
         Int_t iDet = hit->GetDetector(); // 1..
         Int_t iCha = hit->GetChannel();  // 1..
 
         fh_los_channels->Fill(iCha);				         
      }
    }

    if(fCalItemsLos && fCalItemsLos->GetEntriesFast())
    {
      Int_t nCha = fCalItemsLos->GetEntriesFast();    
      Int_t iDet = 0;
      
   // cout<<"Online, LOS: "<< nCha<<endl;           
      for (Int_t iCha = 0; iCha < nCha; iCha++)     
      {
          R3BLosCalData *calData = (R3BLosCalData*)fCalItemsLos->At(iCha);
    	  iDet=calData->GetDetector();

       if(iCha == 0) 
        {   	     	                 
   // Channels 1-4:
          if(!(IS_NAN(calData->fTimeV_r_ns))) time_r_V = calData->fTimeV_r_ns;
          if(!(IS_NAN(calData->fTimeV_t_ns))) time_t_V = calData->fTimeV_t_ns;
          if(!(IS_NAN(calData->fTimeV_l_ns))) time_l_V = calData->fTimeV_l_ns;
          if(!(IS_NAN(calData->fTimeV_b_ns))) time_b_V = calData->fTimeV_b_ns;  
           // Channels 5-8:
          if(!(IS_NAN(calData->fTimeV_rt_ns))) time_rt_V = calData->fTimeV_rt_ns;
          if(!(IS_NAN(calData->fTimeV_lt_ns))) time_lt_V = calData->fTimeV_lt_ns;
          if(!(IS_NAN(calData->fTimeV_lb_ns))) time_lb_V = calData->fTimeV_lb_ns;
          if(!(IS_NAN(calData->fTimeV_rb_ns))) time_rb_V = calData->fTimeV_rb_ns; 
          
	    }
       else if(iCha == 1)
	   {                 
  // Channels 1-4:      
          if(!(IS_NAN(calData->fTimeL_r_ns))) time_r_L = calData->fTimeL_r_ns;
          if(!(IS_NAN(calData->fTimeT_r_ns))) time_r_T = calData->fTimeT_r_ns;
          if(!(IS_NAN(calData->fTimeL_t_ns))) time_t_L = calData->fTimeL_t_ns;
          if(!(IS_NAN(calData->fTimeT_t_ns))) time_t_T = calData->fTimeT_t_ns;  
          if(!(IS_NAN(calData->fTimeL_l_ns))) time_l_L = calData->fTimeL_l_ns;
          if(!(IS_NAN(calData->fTimeT_l_ns))) time_l_T = calData->fTimeT_l_ns; 
          if(!(IS_NAN(calData->fTimeL_b_ns))) time_b_L = calData->fTimeL_b_ns;
          if(!(IS_NAN(calData->fTimeT_b_ns))) time_b_T = calData->fTimeT_b_ns;  
          // Channels 5-8:
          if(!(IS_NAN(calData->fTimeL_rt_ns))) time_rt_L = calData->fTimeL_rt_ns;
          if(!(IS_NAN(calData->fTimeT_rt_ns))) time_rt_T = calData->fTimeT_rt_ns;
          if(!(IS_NAN(calData->fTimeL_lt_ns))) time_lt_L = calData->fTimeL_lt_ns;
          if(!(IS_NAN(calData->fTimeT_lt_ns))) time_lt_T = calData->fTimeT_lt_ns;  
          if(!(IS_NAN(calData->fTimeL_lb_ns))) time_lb_L = calData->fTimeL_lb_ns;
          if(!(IS_NAN(calData->fTimeT_lb_ns))) time_lb_T = calData->fTimeT_lb_ns; 
          if(!(IS_NAN(calData->fTimeL_rb_ns))) time_rb_L = calData->fTimeL_rb_ns;
          if(!(IS_NAN(calData->fTimeT_rb_ns))) time_rb_T = calData->fTimeT_rb_ns;  
                     
         }           
      }
      
          LOG(DEBUG) << "test1 : "<<flosOffsetX1<<"  "<<flosOffsetY1<<"  "<<flosVeffX1<<"  "<<flosVeffY1<<FairLogger::endl;

	                 
   if(iDet==1){

            t_hor_M = (time_r_V + time_l_V)/2.; 		  
     	    t_ver_M = (time_t_V + time_b_V)/2.;		
            t_hor_T = (time_r_L + time_l_L)/2.;       		  
            t_ver_T = (time_t_L + time_b_L)/2.;	
            t_45_M  = (time_rb_V + time_lt_V)/2.; 		  
	        t_135_M = (time_rt_V + time_lb_V)/2.; 
            t_45_T = (time_rb_L + time_lt_L)/2.; 		  
	        t_135_T = (time_rt_L + time_lb_L)/2.;
	        
            while(time_r_T - time_r_L <0.) 
            {
	         time_r_T=time_r_T+2048.*fClockFreq; 
	        }  
            while(time_l_T - time_l_L <0.) 
            {
	         time_l_T=time_l_T+2048.*fClockFreq; 
	        }	      
            while(time_t_T - time_t_L <0.) 
            {
	         time_t_T=time_t_T+2048.*fClockFreq; 
	        }	                 
            while(time_b_T - time_b_L <0.) 
            {
	         time_b_T=time_b_T+2048.*fClockFreq; 
	        }
	        while(time_rt_T - time_rt_L <0.) 
	       {
	        time_rt_T=time_rt_T+2048.*fClockFreq; 
	       }  
           while(time_lt_T - time_lt_L <0.) 
           {
	        time_lt_T=time_lt_T+2048.*fClockFreq; 
	       }	      
           while(time_rb_T - time_rb_L <0.) 
           {
	        time_rb_T=time_rb_T+2048.*fClockFreq; 
	       }	                 
           while(time_lb_T - time_lb_L <0.) 
           {
	        time_lb_T=time_lb_T+2048.*fClockFreq; 
	       } 
            
             totr = time_r_T - time_r_L;
             totl = time_l_T - time_l_L;
             tott = time_t_T - time_t_L;
             totb = time_b_T - time_b_L;
             totrb = time_rb_T - time_rb_L;
             totlt = time_lt_T - time_lt_L;
             totrt = time_rt_T - time_rt_L;
             totlb = time_lb_T - time_lb_L;	
 
             tot_ver = (tott+totb)/2.;
  	         tot_hor = (totr+totl)/2.;  
  	         
  	         tot_135 = (totrt+totlb)/2.;
             tot_45 = (totlt+totrb)/2.;
	        
             timeLosM = (t_hor_M + t_ver_M + t_45_M + t_135_M)/4.;
			 LosTresM = ((t_hor_M + t_ver_M) - (t_45_M + t_135_M))/2.;  	  		     
		     
		     timeLosT = (t_hor_T + t_ver_T + t_45_T + t_135_T)/4.;
             LosTresT = ((t_hor_T + t_ver_T) - (t_45_T + t_135_T))/2.;         
             
            
             tot = (tot_ver+tot_hor+tot_45+tot_135)/4.;
             fh_los_tot->Fill(tot);
  
  // Position calibration parameters for KVI test                
                 
           // For 12C runs: 
           
             xT_cm = (time_l_L+time_lb_L)/2.-(time_r_L+time_rt_L)/2.;                  
             yT_cm = (time_b_L+time_rb_L)/2.-(time_t_L+time_lt_L)/2.;            
             xT_cm=(xT_cm-1.347)*0.742578 ;  
	   	     yT_cm=(yT_cm-0.139)*0.91525; 
	   	     
	   	     xToT = log((totr+totrt)/(totl+totlb));
             yToT = log((tott+totlt)/(totb+totrb));             
	         xToT = (xToT- 0.003626) * 4.56035;
             yToT = (yToT+ 0.0189) * 4.66216;
           
            /*
             xToT=((totr+totrt)/2.-(totl+totlb)/2.)/((totl+totlb+totr+totrt)/4.);
             yToT=((tott+totlt)/2.-(totb+totrb)/2.)/((tott+totlt+totrb+totb)/4.);
	   	     xToT =(xToT-0.0044)*4.510 ; 
             yToT =(yToT+0.02423)*4.492; 
             */
             
	   	   // For protons run:
	       /*
	         xT_cm = (time_l_L+time_lb_L)/2.-(time_r_L+time_rt_L)/2.;                  
             yT_cm = (time_b_L+time_rb_L)/2.-(time_t_L+time_lt_L)/2.;	   
             xT_cm=(xT_cm+2.612)*1. ;  
	   	     yT_cm=(yT_cm-2.38389)*1. ;
	   	    
	   	     xToT=((totr+totrt)/2.-(totl+totlb)/2.)/((totl+totlb+totr+totrt)/4.);
             yToT=((tott+totlt)/2.-(totb+totrb)/2.)/((tott+totlt+totrb+totb)/4.); 
	   	     xToT =(xToT+0.225)*1. ; 
             yToT =(yToT+0.031975)*1.; 
           */ 

           x_cm=(xT_cm+xToT)/2.;
           y_cm=(yT_cm+yToT)/2.;
            
       
            
          //  if((x_cm-1.735)*(x_cm-1.735)+(y_cm-2.23)*(y_cm-2.23)<0.07*0.07) los_cut1=true;
            if(tot > 53.4 && tot < 59.1) los_cut1=true;
           //  los_cut1=true;
            if(los_cut1) 
            {
			  fh_los_pos->Fill(x_cm,y_cm);
          //    fh_los_tres_MCFD->Fill(LosTresM); // plotted down with cond on Fib1&4
          //    fh_los_tres_TAMEX->Fill(LosTresT);
             }  
    } else {
	  cout<<"Wrong detector ID for LOS!"<<endl;
      }
    }	
    
//----------------------------------------------------------------------
// Ptof detector bar 8 is horizontal for KVI
//----------------------------------------------------------------------
    Bool_t ptof_cut1=false;	
    Bool_t ptof_cut4=false;	
    Bool_t ptof_cut5=false;	
    Bool_t ptof_cut6=false;	

	Double_t ptof_xpos=-100000;
	Double_t ptof_time=-100000;
	
	if(fHitItemsPtof){
		Int_t nHits = fHitItemsPtof->GetEntriesFast();    
		LOG(DEBUG) << "nHits: " << nHits << FairLogger::endl;
		for (Int_t ihit = 0; ihit < nHits; ihit++)     {
			R3BPtofHit *hit = (R3BPtofHit*)fHitItemsPtof->At(ihit);
			
			if (!hit) continue; // should not happen
			
			Int_t iBar  = hit->GetPaddleNr();    // 1..n
			Double_t charge = hit->GetCharge();
			ptof_xpos = hit->GetXX();

			if(charge>5 && iBar==3 ){
				ptof_cut4=true;
				ptof_time=hit->GetTdc();
			}

			if(charge>5 && iBar==3 ){
				ptof_cut5=true;
			}

			if(charge>5 && iBar==3 ){
				ptof_cut6=true;
			}
			
			
			if(iBar==8 && charge>10 && ptof_xpos>12. && ptof_xpos<22.){
				fh_ptof_qbar_q_vs_pos->Fill(ptof_xpos,charge);
				ptof_cut1=true;
//				ptof_cut4=true;
//				ptof_cut5=true;
//				ptof_cut6=true;
			}

		}
		Double_t tdiff=-100000;
		if(ptof_time>-100000. && timeLosM>-100000.){
			tdiff=ptof_time-timeLosM;
			while(tdiff<5000.) tdiff=tdiff+2048.*5.; 
			while(tdiff>5000.) tdiff=tdiff-2048.*5.; 	   
			fh_ptof_ToF->Fill(tdiff);
		}
		
		if(tdiff<-165 || tdiff>-152) {
			ptof_cut1=false;
			ptof_cut4=false;
			ptof_cut5=false;
			ptof_cut6=false;
		}

		if(ptof_cut4) fNEvents4++;
		if(ptof_cut5) fNEvents5++;
		if(ptof_cut6) fNEvents6++;
		if(ptof_cut1) fNEvents1++;
	}


//----------------------------------------------------------------------
// Fiber detectors
//----------------------------------------------------------------------

    if(fMappedItemsFi0 ) 
    {
        Int_t nHits = fMappedItemsFi0->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            R3BBunchedFiberMappedData* hit = (R3BBunchedFiberMappedData*)fMappedItemsFi0->At(ihit);
            if (!hit) continue;
 
            // channel numbers are stored 1-based (1..n)
            Int_t iCha = hit->GetChannel();  // 1..
         
            if (hit->IsMAPMT() && hit->IsLeading()) {
//	 cout<<"test "<<iCha<<"  row "<<(iCha-1)%16+1<<"  col "<<iCha/16+1<<endl;
		        fh_Fi0_channels->Fill((iCha-1)%16+1,iCha/16+1);			 
	        }
        }
    }

    if(fHitItemsFi0) {
        Int_t nHits = fHitItemsFi0->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            R3BBunchedFiberHitData* hit = (R3BBunchedFiberHitData*)fHitItemsFi0->At(ihit);
            if (!hit) continue;

            Int_t iFib = hit->GetFiberId();  // 1..
            fh_Fi0_ToT_m->Fill(iFib,hit->GetMAPMTToT_ns());
        }
    }

	if(fMappedItemsFi1) {
		Int_t nHits = fMappedItemsFi1->GetEntriesFast();
		std::vector<UInt_t> mapmt_num(512);
		std::vector<UInt_t> spmt_num(16);
		for (Int_t ihit = 0; ihit < nHits; ihit++){
			R3BBunchedFiberMappedData* hit = (R3BBunchedFiberMappedData*)fMappedItemsFi1->At(ihit);
			if (!hit) continue;

			// channel numbers are stored 1-based (1..n)
			Int_t iCha = hit->GetChannel();  // 1..
         
			if (hit->IsMAPMT() && hit->IsLeading()) {
				fh_Fi1_channels->Fill(iCha);
				++mapmt_num.at(hit->GetChannel() - 1);
			}
			if (!hit->IsMAPMT() && hit->IsLeading()) {
				++spmt_num.at(hit->GetChannel() - 1);
			}
		}
		UInt_t m_tot = 0;
		for (int i = 0; i < 256; ++i) {
			auto m = mapmt_num.at(i);
			if(m > 0) fh_Fi1_multihit->Fill(i,m);
			m_tot += m;
		}
		for (int i = 0; i < 16; ++i) {
			auto m = spmt_num.at(i);
			if(m > 0) fh_Fi1_multihit_s->Fill(i,m);
		}
	}

    Double_t t1x=0;
	Double_t t1y=0;
	Double_t t1=-1000000;
    Double_t t4=-1000000;
    Double_t t5=-1000000;
    Double_t t6=-1000000;
 	Bool_t fiber1_cut1=false;
   
    Int_t iFib1x=0;	
    Int_t iFib1y=0;	
	
	if(fHitItemsFi1) {
		Double_t start=0.;
		Double_t stop=0.;
		Double_t maxToTx=0;
		Double_t maxToTy=0;
		Int_t nHits = fHitItemsFi1->GetEntriesFast();
		std:vector<UInt_t> fiber1_mult(520);
		for (Int_t ihit = 0; ihit < nHits; ihit++){
			R3BBunchedFiberHitData* hit = (R3BBunchedFiberHitData*)fHitItemsFi1->At(ihit);
			if (!hit) continue;

			Int_t iFib = hit->GetFiberId();  // 1..
			if(iFib==384) fiber1_cut1=true;
                 
			if(hit->GetToT_ns()/max_value1[iFib]>0.9 && iFib<=256) 
				fh_Fi1_xpos->Fill(iFib*0.02);
			if(hit->GetToT_ns()/max_value1[iFib]>0.9 && iFib>256) 
				fh_Fi1_ypos->Fill((iFib-256)*0.02);
				
			
			if(hit->GetSPMTToT_ns() > 0) {
				fh_Fi1_fibers->Fill(iFib);
				
				++fiber1_mult.at(iFib - 1);

				if (iFib <= 256) {
					if (hit->GetToT_ns()/max_value1[iFib] > maxToTx) {
						iFib1x = iFib;
						maxToTx = hit->GetToT_ns()/max_value1[iFib];
						t1x=hit->GetTime_ns();
					}
				}
				if (iFib > 256) {
					if (hit->GetToT_ns()/max_value1[iFib] > maxToTy) {
						iFib1y = iFib;
						maxToTy = hit->GetToT_ns()/max_value1[iFib];
						t1y=hit->GetTime_ns();
					}
				}
			}
			if(hit->GetSPMTToT_ns() > 0){
//        	  	fh_Fi1_ToT->Fill(iFib,hit->GetMAPMTToT_ns());
				fh_Fi1_ToT->Fill(iFib,hit->GetToT_ns());
//				fh_Fi1_FibervsTime->Fill(iFib,fNEvents);
				fh_Fi1_ToT_s->Fill(iFib,hit->GetSPMTToT_ns());
				fh_Fi1_ToTvsTime_s->Fill(hit->GetSPMTToT_ns(),fNEvents);
            
			}				 
		}
		
		fh_Fi1_FibervsTime->Fill(iFib1x,fNEvents);
		if(t1x>-100000. && timeLosM>-100000.){
			Double_t tdiff=t1x-timeLosM;
			while(tdiff<5000.) tdiff=tdiff+2048.*4.; 
			while(tdiff>5000.) tdiff=tdiff-2048.*4.; 	   
			fh_Fi1_ToF->Fill(tdiff);
		}
      
		if(fiber1_cut1) fh_los_test->Fill(xT_cm,yT_cm);	
		fh_Fi1_test->Fill(stop-start);
	}


    Int_t iFib4x = 0;
    
    if(fMappedItemsFi4) 
    {
      Int_t nHits = fMappedItemsFi4->GetEntriesFast();
      std::vector<UInt_t> mapmt_num(512);
      std::vector<UInt_t> spmt_num(8);
      for (Int_t ihit = 0; ihit < nHits; ihit++)
      {
         R3BBunchedFiberMappedData* hit = (R3BBunchedFiberMappedData*)fMappedItemsFi4->At(ihit);
         if (!hit) continue;

         // channel numbers are stored 1-based (1..n)
         Int_t iCha = hit->GetChannel();  // 1..
         
         if (hit->IsMAPMT() && hit->IsLeading()) {
			 fh_Fi4_channels->Fill(iCha);
			 ++mapmt_num.at(hit->GetChannel() - 1);
		 }
         if (!hit->IsMAPMT() && hit->IsLeading()) {
			 ++spmt_num.at(hit->GetChannel() - 1);
		 }
      }

      UInt_t m_tot = 0;
      for (int i = 0; i < 512; ++i) {
        auto m = mapmt_num.at(i);
        if(m > 0) fh_Fi4_multihit->Fill(i,m);
        m_tot += m;
	  }

  	  fh_Fi4_mult->Fill(m_tot);

      for (int i = 0; i < 8; ++i) {
        auto m = spmt_num.at(i);
        if(m > 0) fh_Fi4_multihit_s->Fill(i,m);
	  }
    }

    if(fHitItemsFi4) {
		Int_t nHits = fHitItemsFi4->GetEntriesFast();
		std::vector<UInt_t> fiber4_mult(4096);
		std::vector<UInt_t> spmt_num(8);

		Double_t totMax=0.;
		Bool_t pr=false;
		
		for (Int_t ihit = 0; ihit < nHits; ihit++){
			R3BBunchedFiberHitData* hit = (R3BBunchedFiberHitData*)fHitItemsFi4->At(ihit);
			if (!hit) continue;

			Int_t iFib = hit->GetFiberId();  // 1..

//			if(iFib==932) pr=true;
			
			// times
			Double_t tMAPMT = hit->GetMAPMTTime_ns();
			Double_t tSPMT = hit->GetSPMTTime_ns();
			
			Double_t dt = tMAPMT-tSPMT;
			
			while(dt<1024.) {
				tSPMT=tSPMT-2048.; 
				dt=tMAPMT-tSPMT;
			}
			while(dt>1024.) {
				tSPMT=tSPMT+2048.; 
				dt=tMAPMT-tSPMT;
			}
			fh_Fi4_ypos->Fill(dt);

//			if(dt<38 || dt>150) continue;

			t4=(tMAPMT+tSPMT)/2.;
			
			Double_t tdiff=0.;
			if(t4>-100000. && timeLosM>-100000.){
				tdiff=t4-timeLosM;
				while(tdiff<5000.) tdiff=tdiff+2048.*4.; 
				while(tdiff>5000.) tdiff=tdiff-2048.*4.; 	   
				fh_Fi4_ToF->Fill(tdiff);
			}
		
//			if(tdiff < -185 || tdiff > -135) continue;

			if(pr){
				cout<<"Event: "<<fNEvents<<" fiber: "<<iFib<<endl;
				cout<<" dt: "<<dt<< " tdiff: "<<tdiff<<" tot sPMT: " <<hit->GetSPMTToT_ns()
				<<" tot MAPMT: "<< hit->GetMAPMTToT_ns()<<" rel: "<<
				hit->GetToT_ns()/max_value4[iFib]<<" ptof: "<<ptof_cut4 <<endl;
				
			}
			
			if(hit->GetSPMTToT_ns() > 1 && hit->GetMAPMTToT_ns()>1) {
				fh_Fi4_fibers->Fill(iFib);
				++fiber4_mult.at(iFib - 1);
			}
			
//			if(hit->GetToT_ns()/max_value4[iFib]>0.90 && hit->GetToT_ns()/max_value4[iFib]<1.05) 
//				fh_Fi4_xpos->Fill(iFib*0.02);
//				if (ptof_cut4) fh_Fi4_eff->Fill(iFib*0.02);

			if (hit->GetToT_ns()/max_value4[iFib] > totMax && hit->GetToT_ns()/max_value4[iFib]<1.05 ) {
//			if (hit->GetToT_ns()/max_value4[iFib] > totMax ) {
//			if (hit->GetToT_ns() > totMax ) {
				iFib4x = iFib;
				totMax = hit->GetToT_ns()/max_value4[iFib];
//				totMax = hit->GetToT_ns();
//				t4=hit->GetTime_ns();
				t4=(tMAPMT+tSPMT)/2.;
			}		 
	 
			if(hit->GetSPMTToT_ns() > 0){	   
				fh_Fi4_ToT->Fill(iFib,hit->GetToT_ns());
				if(ptof_cut1) fh_Fi4_ToT_cut->Fill(iFib,hit->GetToT_ns());
				fh_Fi4_ToT_s->Fill(iFib,hit->GetSPMTToT_ns());
				fh_Fi4_ToTvsTime_s->Fill(hit->GetSPMTToT_ns(),fNEvents);
//				fh_Fi4_FibervsTime->Fill(iFib,fNEvents);
				fh_Fi4_fibers->Fill(iFib);      
			}

		}

		fh_Fi4_FibervsTime->Fill(iFib4x,fNEvents);

    }
	if ( ptof_cut1) {
//      if(los_cut1) 
		fh_Fi1vsFi4->Fill(iFib4x,ptof_xpos);

    }
	if (iFib4x != 0   && ptof_cut4) {
		fh_Fi4_test->Fill(t4-t1x);
		fh_Fi4_xpos->Fill(iFib4x*0.02);
		fh_Fi4_eff->Fill(iFib4x*0.02);
	}
	
	
    Int_t iFib5x = 0;   
    if(fMappedItemsFi5) 
    {
        Int_t nHits = fMappedItemsFi5->GetEntriesFast();
        std::vector<UInt_t> mapmt_num(256);
        std::vector<UInt_t> spmt_num(16);
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            R3BBunchedFiberMappedData* hit = (R3BBunchedFiberMappedData*)fMappedItemsFi5->At(ihit);
            if (!hit) continue;

            // channel numbers are stored 1-based (1..n)
            Int_t iCha = hit->GetChannel();  // 1..
         
            if (hit->IsMAPMT() && hit->IsLeading()) {
	            fh_Fi5_channels->Fill(iCha);
		        ++mapmt_num.at(hit->GetChannel() - 1);
	        }
            if (!hit->IsMAPMT() && hit->IsLeading()) {
	            ++spmt_num.at(hit->GetChannel() - 1);
	        }
        }
        UInt_t m_tot = 0;
        for (int i = 0; i < 256; ++i) {
            auto m = mapmt_num.at(i);
            if(m > 0) fh_Fi5_multihit->Fill(i,m);
            m_tot += m;
	    }
        fh_Fi5_mult->Fill(m_tot);
        for (int i = 0; i < 16; ++i) {
            auto m = spmt_num.at(i);
            if(m > 0) fh_Fi5_multihit_s->Fill(i,m);
	    }
    }

    if(fHitItemsFi5) {
        Int_t nHits = fHitItemsFi5->GetEntriesFast();
        std::vector<UInt_t> fiber5_mult(1024);
        Int_t fibMax=0;
        Double_t totMax=0.;
      
//        if(fNEvents>180000 && fNEvents<200000) cout<<"Event: "<<fNEvents<<endl;
      
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            R3BBunchedFiberHitData* hit = (R3BBunchedFiberHitData*)fHitItemsFi5->At(ihit);
            if (!hit) continue;

            Int_t iFib = hit->GetFiberId();  // 1..
			// times
			Double_t tMAPMT = hit->GetMAPMTTime_ns();
			Double_t tSPMT = hit->GetSPMTTime_ns();
			
			Double_t dt = tMAPMT-tSPMT;
			
			while(dt<1024.) {
				tSPMT=tSPMT-2048.; 
				dt=tMAPMT-tSPMT;
			}
			while(dt>1024.) {
				tSPMT=tSPMT+2048.; 
				dt=tMAPMT-tSPMT;
			}
			fh_Fi5_ypos->Fill(dt);
//			if(dt<30 || dt>70) continue;

			t5=(tMAPMT+tSPMT)/2.;
			
			Double_t tdiff=0.;
			if(t5>-100000. && timeLosM>-100000.){
				tdiff=t5-timeLosM;
				while(tdiff<5000.) tdiff=tdiff+2048.*4.; 
				while(tdiff>5000.) tdiff=tdiff-2048.*4.; 	   
				fh_Fi5_ToF->Fill(tdiff);
			}
		
//			if(tdiff < -188 || tdiff > -167) continue;

			if(hit->GetToT_ns()/max_value5[iFib]>0.9) 
//				fh_Fi5_xpos->Fill(iFib*0.02);

            if(hit->GetSPMTToT_ns() > 0) {
//                fh_Fi5_fibers->Fill(iFib);
                ++fiber5_mult.at(iFib - 1);
            }
//            if(hit->GetToT_ns()/max_value5[iFib]>totMax){
            if(hit->GetToT_ns()/max_value5[iFib]>totMax && hit->GetToT_ns()/max_value5[iFib]<1.05){
                totMax = hit->GetToT_ns()/max_value5[iFib];
                fibMax = iFib;
				iFib5x = iFib;                
//            	t5=hit->GetTime_ns();
				t5=(tMAPMT+tSPMT)/2.;
			}

			if(hit->GetSPMTToT_ns() > 0){
                fh_Fi5_ToT_m->Fill(iFib,hit->GetMAPMTToT_ns());
                fh_Fi5_ToT->Fill(iFib,hit->GetToT_ns());
                fh_Fi5_ToT_s->Fill(iFib%4,hit->GetSPMTToT_ns());// must be modulo 8 for the full detector
                fh_Fi5_ToTvsTime_s[iFib%4]->Fill(hit->GetSPMTToT_ns(),fNEvents);
//				fh_Fi5_FibervsTime->Fill(iFib,fNEvents);
				fh_Fi5_fibers->Fill(iFib);      
	        }
        }
		fh_Fi5_FibervsTime->Fill(iFib5x,fNEvents);
		if(t5>0. && timeLosM>0.){
			Double_t tdiff=t5-timeLosM;
			while(tdiff<5000.) tdiff=tdiff+2048.*4.; 
			while(tdiff>5000.) tdiff=tdiff-2048.*4.; 	   
			fh_Fi5_ToF->Fill(tdiff);
		}
    }

    if ( ptof_cut5) {      
		fh_Fi5vsFi4->Fill(iFib4x,iFib5x);
		
    }
	if (iFib5x != 0 && ptof_cut5) {      
		fh_Fi5_xpos->Fill(iFib5x*0.02);
		fh_Fi5_eff->Fill(iFib5x*0.02);
		
    }


		
	
    Int_t iFib6x = 0;
    
    if(fMappedItemsFi6 ) 
    {
        std::vector<UInt_t> mapmt_num(256);
        std::vector<UInt_t> spmt_num(16);
        Int_t nHits = fMappedItemsFi6->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            R3BBunchedFiberMappedData* hit = (R3BBunchedFiberMappedData*)fMappedItemsFi6->At(ihit);
            if (!hit) continue;

            // channel numbers are stored 1-based (1..n)
            Int_t iCha = hit->GetChannel();  // 1..
            
            if (hit->IsMAPMT() && hit->IsLeading()) {
                fh_Fi6_channels->Fill(iCha);
                ++mapmt_num.at(hit->GetChannel() - 1);
	    }
            if (!hit->IsMAPMT() && hit->IsLeading()) {
                ++spmt_num.at(hit->GetChannel() - 1);		
            }
        }
        UInt_t m_tot = 0;
        for (int i = 0; i < 256; ++i) {
            auto m = mapmt_num.at(i);
            if(m > 0) fh_Fi6_multihit->Fill(i,m);
            m_tot += m;
        }
        fh_Fi6_mult->Fill(m_tot);
        for (int i = 0; i < 16; ++i) {
            auto m = spmt_num.at(i);
            if(m > 0) fh_Fi6_multihit_s->Fill(i,m);
        }
    }

    if(fHitItemsFi6 ) {
        std::vector<UInt_t> fiber6_mult(512);
        Int_t fibMax=0;
        Double_t totMax=0.;
        
//        if(fNEvents>854000 && fNEvents<860000) cout<<"Event: "<<fNEvents<<endl;
        
        Int_t nHits = fHitItemsFi6->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            R3BBunchedFiberHitData* hit = (R3BBunchedFiberHitData*)fHitItemsFi6->At(ihit);
            if (!hit) continue;

            Int_t iFib = hit->GetFiberId();  // 1..

			// times
			Double_t tMAPMT = hit->GetMAPMTTime_ns();
			Double_t tSPMT = hit->GetSPMTTime_ns();
			
			Double_t dt = tMAPMT-tSPMT;
			
			while(dt<1024.) {
				tSPMT=tSPMT-2048.; 
				dt=tMAPMT-tSPMT;
			}
			while(dt>1024.) {
				tSPMT=tSPMT+2048.; 
				dt=tMAPMT-tSPMT;
			}
			fh_Fi6_ypos->Fill(dt);
//			if(dt<100 || dt>150) continue;

			t6=(tMAPMT+tSPMT)/2.;
			
			Double_t tdiff=0.;
			if(t6>-100000. && timeLosM>-100000.){
				tdiff=t6-timeLosM;
				while(tdiff<5000.) tdiff=tdiff+2048.*4.; 
				while(tdiff>5000.) tdiff=tdiff-2048.*4.; 	   
				fh_Fi6_ToF->Fill(tdiff);
			}
		
//			if(tdiff < -158 || tdiff > -135) continue;

			
			if(hit->GetSPMTToT_ns() > 1 && hit->GetMAPMTToT_ns()>1) {
				fh_Fi6_fibers->Fill(iFib);
				++fiber6_mult.at(iFib - 1);
			}
			
			if (hit->GetToT_ns()/max_value6[iFib] > totMax && hit->GetToT_ns()/max_value6[iFib]<1.05 ) {
				iFib6x = iFib;
				totMax = hit->GetToT_ns()/max_value6[iFib];
//				totMax = hit->GetToT_ns();
//				t6=hit->GetTime_ns();
				t6=(tMAPMT+tSPMT)/2.;
			}		 
	 
			if(hit->GetSPMTToT_ns() > 0){	   
				fh_Fi6_ToT->Fill(iFib,hit->GetToT_ns());
                fh_Fi6_ToT_m->Fill(iFib,hit->GetMAPMTToT_ns());
//				if(ptof_cut6) fh_Fi6_ToT_cut->Fill(iFib,hit->GetToT_ns());
				fh_Fi6_ToT_s->Fill(iFib,hit->GetSPMTToT_ns());
//				fh_Fi6_ToTvsTime_s->Fill(hit->GetSPMTToT_ns(),fNEvents);
//				fh_Fi6_FibervsTime->Fill(iFib,fNEvents);
				fh_Fi6_fibers->Fill(iFib);      
			}

        }
		fh_Fi6_FibervsTime->Fill(iFib6x,fNEvents);        
	}



	if ( ptof_cut1) {
//      if(los_cut1) 
//		fh_Fi1vsFi4->Fill(iFib4x,ptof_xpos);

    }
	if (iFib6x != 0 && ptof_cut6) {
//		fh_Fi6_test->Fill(t6-t1x);
		fh_Fi6_xpos->Fill(iFib6x*0.05);
		fh_Fi6_eff->Fill(iFib6x*0.05);
	}
	
    



    if(fMappedItemsTofd )
    {
      Int_t nHits = fMappedItemsTofd->GetEntriesFast();    
      for (Int_t ihit = 0; ihit < nHits; ihit++)     
      {
    	R3BPaddleTamexMappedData *hit = (R3BPaddleTamexMappedData*)fMappedItemsTofd->At(ihit);
        if (!hit) continue; // should not happen

        Int_t iPlane = hit->GetPlaneId(); // 1..n
        Int_t iBar   = hit->GetBarId();   // 1..n

            
        if(iPlane<=fNofPlanes){
          fh_tofd_channels[iPlane-1]->Fill(iBar);
          fh_tofd_channels[iPlane-1]->Fill(-iBar-1);
        }
      }
    }

    
    if(fCalItemsTofd)
    {
      Double_t tot1=0.;
      Double_t tot2=0.;
      Double_t t1l=0.;
      Double_t t2l=0.;
      Double_t t1t=0.;
      Double_t t2t=0.;
     
      Int_t nHits = fCalItemsTofd->GetEntriesFast();    
      for (Int_t ihit = 0; ihit < nHits; ihit++)     
      {
    	  R3BPaddleCalData *hit = (R3BPaddleCalData*)fCalItemsTofd->At(ihit);
          if (!hit) continue; // should not happen

          Int_t iPlane  = hit->GetPlane();    // 1..n
          Int_t iBar  = hit->GetBar();    // 1..n

                 // get all times of one bar
          t1l=hit->fTime1L_ns;
          t2l=hit->fTime2L_ns;
          t1t=hit->fTime1T_ns;
          t2t=hit->fTime2T_ns;

	      // calculate time over threshold and check if clock counter went out of range
          while(t1t - t1l < 0.) {
	          t1t=t1t+2048.*fClockFreq; 
	      }

          while(t2t-t2l < 0.) {
	          t2t=t2t+2048.*fClockFreq; 
          }
	      while(t1l-timeLosM<0.){
	          t1t=t1t+2048.*fClockFreq; 
	          t1l=t1l+2048.*fClockFreq; 
	          t2t=t2t+2048.*fClockFreq; 
	          t2l=t2l+2048.*fClockFreq; 			  
		  }
       
          tot1=t1t - t1l;		      
          if(tot1<0) {
	          LOG(WARNING) << "Negative ToT "<< tot1<<FairLogger::endl;	
	          LOG(WARNING) << "times1: " << t1t << " " << t1l << FairLogger::endl;		  
	      }

          tot2=t2t - t2l;	
          if(tot2<0) {
              LOG(WARNING) << "Negative ToT "<< tot2<<FairLogger::endl;              
              LOG(WARNING) << "times2: " << t2t << " " << t2l << FairLogger::endl;		 
          }
          fh_tofd_TotPm1[iPlane-1][iBar-1]->Fill(tot1);
          fh_tofd_TotPm2[iPlane-1][iBar-1]->Fill(tot2);
        	
      }	

    }

	if(fCalItemsPtof){
		Double_t tot1=0.;
		Double_t tot2=0.;
		Double_t t1l=0.;
		Double_t t2l=0.;
		Double_t t1t=0.;
		Double_t t2t=0.;
		Bool_t bar_quer1=false;
		Bool_t bar_quer2=false;
		
		Int_t nHits = fCalItemsPtof->GetEntriesFast();    
		LOG(DEBUG) << "nHits: " << nHits << FairLogger::endl;
		for (Int_t ihit = 0; ihit < nHits; ihit++)     {
			R3BPaddleCalData *hit = (R3BPaddleCalData*)fCalItemsPtof->At(ihit);
			
			if (!hit) continue; // should not happen
			
			Int_t iBar  = hit->GetBar();    // 1..n
			Int_t iPlane = hit->GetPlane();
			// get all times of one bar
			t1l=hit->fTime1L_ns;
			t2l=hit->fTime2L_ns;
			t1t=hit->fTime1T_ns;
			t2t=hit->fTime2T_ns;
			
			if(!(t1l>0 && t2l>0 && t1t>0 && t2t>0)) continue;
			
			fh_ptof_channels->Fill(iBar);
			LOG(DEBUG) << "Bar: " << iBar << FairLogger::endl;
			LOG(DEBUG) << "times PM1: " << t1l<<"  "<<t1t<<"  "<<t1t-t1l << FairLogger::endl;
			LOG(DEBUG) << "times PM2: " << t2l<<"  "<<t2t<<"  "<<t2t-t2l << FairLogger::endl;
//			if(iBar==7) bar_quer1=true;
			if(iBar==8) bar_quer2=true;
			
			// calculate time over threshold and check if clock counter went out of range
			while(t1t - t1l < 0.) {
				t1t=t1t+2048.*fClockFreq; 
			}
			
			while(t2t-t2l < 0.) {
				t2t=t2t+2048.*fClockFreq; 
			}
			while(t1l-timeLosM<0.){
				t1t=t1t+2048.*fClockFreq; 
				t1l=t1l+2048.*fClockFreq; 
				t2t=t2t+2048.*fClockFreq; 
				t2l=t2l+2048.*fClockFreq; 			  
			}
			
			tot1=t1t - t1l;		      
			if(tot1<0) {
				LOG(WARNING) << "Negative ToT "<< tot1<<FairLogger::endl;	
				LOG(WARNING) << "times1: " << t1t << " " << t1l << FairLogger::endl;		  
			}
			
			tot2=t2t - t2l;	
			if(tot2<0) {
				LOG(WARNING) << "Negative ToT "<< tot2<<FairLogger::endl;              
				LOG(WARNING) << "times2: " << t2t << " " << t2l << FairLogger::endl;		 
			}
			if(iBar<20){
				fh_ptof_TotPm1[iBar+(iPlane-1)*N_PADDLE_MAX_PTOF]->Fill(tot1);
				fh_ptof_TotPm2[iBar+(iPlane-1)*N_PADDLE_MAX_PTOF]->Fill(tot2);
			}
			if(iBar==2) fh_ptof_test1->Fill(sqrt(tot1*tot1));	
		}	
      
		//once again
            
		nHits = fCalItemsPtof->GetEntriesFast();    
//		LOG(DEBUG) << "nHits: " << nHits << FairLogger::endl;
		for (Int_t ihit = 0; ihit < nHits; ihit++){
			R3BPaddleCalData *hit = (R3BPaddleCalData*)fCalItemsPtof->At(ihit);

			if (!hit) continue; // should not happen

			Int_t iBar  = hit->GetBar();    // 1..n
			// get all times of one bar
			t1l=hit->fTime1L_ns;
			t2l=hit->fTime2L_ns;
			t1t=hit->fTime1T_ns;
			t2t=hit->fTime2T_ns;
			
			if(!(t1l>0 && t2l>0 && t1t>0 && t2t>0)) continue;
			
			// calculate time over threshold and check if clock counter went out of range
			while(t1t - t1l < 0.) {
				t1t=t1t+2048.*fClockFreq; 
			}
			
			while(t2t-t2l < 0.) {
				t2t=t2t+2048.*fClockFreq; 
			}
			while(t1l-timeLosM<0.){
				t1t=t1t+2048.*fClockFreq; 
				t1l=t1l+2048.*fClockFreq; 
				t2t=t2t+2048.*fClockFreq; 
				t2l=t2l+2048.*fClockFreq; 			  
			}
			
			tot1=t1t - t1l;		      
			if(tot1<0) {
				LOG(WARNING) << "Negative ToT "<< tot1<<FairLogger::endl;	
				LOG(WARNING) << "times1: " << t1t << " " << t1l << FairLogger::endl;		  
			}
			
			tot2=t2t - t2l;	
			if(tot2<0) {
				LOG(WARNING) << "Negative ToT "<< tot2<<FairLogger::endl;              
				LOG(WARNING) << "times2: " << t2t << " " << t2l << FairLogger::endl;		 
			}
				
			if(bar_quer2){
//				fh_ptof_TotPm1[iBar]->Fill(tot1);
//				fh_ptof_TotPm2[iBar]->Fill(tot2);
//				if(iBar==2) fh_ptof_test2->Fill(sqrt(tot1*tot2));	
				fh_ptof_channels_cut->Fill(iBar);			
			}			
		}
	}
	
	
	
	
    if(fCalItemsPspx && fCalItemsPspx->GetEntriesFast())
    {      
      Int_t nHits = fCalItemsPspx->GetEntriesFast();    
      Double_t max_energy1[4] = {0,0,0,0};
      Double_t max_energy2[4] = {0,0,0,0};
      Double_t max_strip[4] = {0,0,0,0};
      
      for (Int_t ihit = 0; ihit < nHits; ihit++)     
      {
	R3BPspxCalData *calData = (R3BPspxCalData*)fCalItemsPspx->At(ihit);
	if(calData->GetEnergy1()>max_energy1[calData->GetDetector()-1] && calData->GetStrip()!=17){
	  max_energy1[calData->GetDetector()-1]=calData->GetEnergy1();
	  max_energy2[calData->GetDetector()-1]=calData->GetEnergy2();
	  max_strip[calData->GetDetector()-1]=calData->GetStrip();
	} 
	
	
	if(calData->GetDetector()==1){
	  if(calData->GetStrip()==17){
	    fh_pspx_energy_psp[0]->Fill(calData->GetEnergy1());  
	  }
	} else if(calData->GetDetector()==2){
	  if(calData->GetStrip()==17){
	    fh_pspx_energy_psp[1]->Fill(calData->GetEnergy1());  
	  }
	} else if(calData->GetDetector()==3){ 
	  if(calData->GetStrip()==17){
	    fh_pspx_energy_psp[2]->Fill(calData->GetEnergy1());  
	  }
	} else if(calData->GetDetector()==4){
	  if(calData->GetStrip()==17){
	    fh_pspx_energy_psp[3]->Fill(calData->GetEnergy1());  
	  }
	} 
      }
      
      fh_pspx_strips_psp[0]->Fill(max_strip[0]);  
      fh_pspx_strips_psp[1]->Fill(max_strip[1]);  
      fh_pspx_strips_psp[2]->Fill(max_strip[2]);  
      fh_pspx_strips_psp[3]->Fill(max_strip[3]);  
      
      if(max_energy1[0]!=0 && max_energy1[1]!=0){
	  fh_pspx_pos1_strips->Fill(max_strip[1],max_strip[0]); 
	  if(max_energy2[0]!=0 && max_energy2[1]!=0){
	      fh_pspx_pos1_energy->Fill(-(max_energy1[0]-max_energy2[0])/(max_energy1[0]+max_energy2[0]),(max_energy1[1]-max_energy2[1])/(max_energy1[1]+max_energy2[1]));
	  }
      }
      if(max_energy1[2]!=0 && max_energy1[3]!=0){
	  fh_pspx_pos2_strips->Fill(max_strip[3],max_strip[2]);
	  if(max_energy2[2]!=0 && max_energy2[3]!=0){
	      fh_pspx_pos2_energy->Fill(-(max_energy1[2]-max_energy2[2])/(max_energy1[2]+max_energy2[2]),-(max_energy1[3]-max_energy2[3])/(max_energy1[3]+max_energy2[3]));
	  }
      }
      
      if(max_energy1[1]!=0 && max_energy1[3]!=0){
	  fh_pspx_cor_x_strips->Fill(max_strip[1],max_strip[3]);
	  if(max_energy2[1]!=0 && max_energy2[3]!=0){
	      fh_pspx_cor_x_energy->Fill(-(max_energy1[1]-max_energy2[1])/(max_energy1[1]+max_energy2[1]),-(max_energy1[3]-max_energy2[3])/(max_energy1[3]+max_energy2[3]));
	  }
      }
      if(max_energy1[0]!=0 && max_energy1[2]!=0){
	  fh_pspx_cor_y_strips->Fill(max_strip[0],max_strip[2]);
	  if(max_energy2[0]!=0 && max_energy2[2]!=0){
	      fh_pspx_cor_y_energy->Fill(-(max_energy1[0]-max_energy2[0])/(max_energy1[0]+max_energy2[0]),-(max_energy1[2]-max_energy2[2])/(max_energy1[2]+max_energy2[2]));
	  }
      }
      
    }

   
    if(fMappedItemsPspx && fMappedItemsPspx->GetEntriesFast())
    {
      Int_t mult1=0;
      Int_t mult2=0;
      Int_t mult3=0;
      Int_t mult4=0;
      
      Int_t nHits = fMappedItemsPspx->GetEntriesFast();    
      
      for (Int_t ihit = 0; ihit < nHits; ihit++)     
      {
	R3BPspxMappedData *mappedData = (R3BPspxMappedData*)fMappedItemsPspx->At(ihit);
	if(mappedData->GetDetector()==1){
	  mult1++;
	} else if(mappedData->GetDetector()==2){
	  mult2++;
	} else if(mappedData->GetDetector()==3){
	  mult3++;
	} else if(mappedData->GetDetector()==4){
	  mult4++;
	} 
	
      }
      fh_pspx_multiplicity_psp[0]->Fill(mult1);
      fh_pspx_multiplicity_psp[1]->Fill(mult2);
      fh_pspx_multiplicity_psp[2]->Fill(mult3);
      fh_pspx_multiplicity_psp[3]->Fill(mult4);
      
    }
  
   
}
    fNEvents += 1;
//	cout<<"R3BOnlineSpectra end"<<endl;

}

void R3BOnlineSpectra::FinishEvent()
{
 
    if (fCalItemsLos)
    {
        fCalItemsLos->Clear();
    }

    if (fCalItemsTofd)
    {
        fCalItemsTofd->Clear();
    }
    if (fCalItemsPtof)
    {
        fCalItemsPtof->Clear();
    }
    if (fMappedItemsLos)
    {
        fMappedItemsLos->Clear();
    }
    if (fMappedItemsTofd)
    {
        fMappedItemsTofd->Clear();
    }
    if (fMappedItemsPspx)
    {
        fMappedItemsPspx->Clear();
    }
    if (fMappedItemsPspx)
    {
        fMappedItemsPspx->Clear();
    }
    if (fMappedItemsFi0)
    {
        fMappedItemsFi0->Clear();
    }
    if (fHitItemsFi0)
    {
        fHitItemsFi0->Clear();
    }
    if (fMappedItemsFi1)
    {
        fMappedItemsFi1->Clear();
    }
    if (fHitItemsFi1)
    {
        fHitItemsFi1->Clear();
    }
    if (fMappedItemsFi5)
    {
        fMappedItemsFi5->Clear();
    }
    if (fHitItemsFi5)
    {
        fHitItemsFi5->Clear();
    }
    if (fMappedItemsFi6)
    {
        fMappedItemsFi6->Clear();
    }
    if (fHitItemsFi6)
    {
        fHitItemsFi6->Clear();
    }
}

void R3BOnlineSpectra::FinishTask()
{
    if(fMappedItemsLos){
		fh_los_test->Write();
	}
    if(fCalItemsPtof){
	    fh_ptof_channels->Write(); 
		fh_ptof_channels_cut->Write(); 
		fh_ptof_test1->Write();   
		fh_ptof_test2->Write();
		fh_ptof_qbar_q_vs_pos->Write();
		fh_ptof_ToF->Write();
		for(Int_t i=1;i<10;i++){   
			fh_ptof_TotPm1[i]->Write(); 
			fh_ptof_TotPm2[i]->Write(); 
		}
	}	
    if (fMappedItemsFi0){
		fh_Fi0_channels ->Write();
    }
    if (fMappedItemsFi1){
		fh_Fi1_channels ->Write();
		fh_Fi1_fibers ->Write();    
		fh_Fi1_multihit ->Write();
		fh_Fi1_ToT->Write();
		fh_Fi1_ToF->Write();
		fh_Fi1_FibervsTime->Write();
		fh_Fi1_multihit_s->Write();
        fh_Fi1_ToT_s->Write();
        fh_Fi1_ToTvsTime_s->Write();
        fh_Fi1_test->Write();
		fh_Fi1_xpos->Write();
		fh_Fi1_ypos->Write();
        
        Bool_t calib1=false;
        if(calib1){
			FILE *fout = NULL;  	    
			fout = fopen("max_values1.dat", "w");
			if(!fout){
				cerr << "Could not open file with max values for writing!\n";
				return;
			}
			for(UInt_t i=1;i<fh_Fi1_ToT->GetNbinsX();i++){
			TH1D * p1 = fh_Fi1_ToT->ProjectionY("",i,i,0);

				for(UInt_t j=p1->GetNbinsX()-2;j>1;j--){
					if(j==2){
						// could not find maximum
						fprintf(fout, "%d   %f \n",i-1,1000.);					
					}
					if(p1->GetBinContent(j)>10){
						// found maximum for ToT calibration
//			   			cout<<"Fiber "<<i<<"  Max "<<p1->GetBinCenter(j)<<endl;
						fprintf(fout, "%d   %f \n",i-1,p1->GetBinCenter(j));
						break;
					}
				}
			}
			fclose(fout);
		}
    }

    
    if ((fMappedItemsFi1)&&(fMappedItemsFi4)){
      fh_Fi1vsFi4->Write();
    }
    if ((fMappedItemsFi5)&&(fMappedItemsFi4)){
      fh_Fi5vsFi4->Write();
    }
    
    if (fMappedItemsFi4){
		fh_Fi4_channels ->Write();
		fh_Fi4_fibers ->Write();  

		fh_Fi4_eff->Scale(1./fNEvents4);		
		cout<<"Events with ptof_cut4: "<< fNEvents4 <<endl;	 
		cout<<"Events : "<< fNEvents4 <<endl;	 
		
		fh_Fi4_eff ->Write();    
	    fh_Fi4_mult->Write(); 
		fh_Fi4_multihit ->Write();
		fh_Fi4_ToT->Write();
		fh_Fi4_ToT_cut->Write();
		fh_Fi4_FibervsTime->Write();
  	    fh_Fi4_multihit_s->Write();
        fh_Fi4_ToT_s->Write();
        fh_Fi4_ToTvsTime_s->Write();
        fh_Fi4_test->Write();
		fh_Fi4_ToF->Write();
		fh_Fi4_xpos->Write();
		fh_Fi4_ypos->Write();

        Bool_t calib4=false;
        if(calib4){
			FILE *fout = NULL;  	    
			fout = fopen("max_values4.dat", "w");
			if(!fout){
				cerr << "Could not open file with max values for writing!\n";
				return;
			}
			for(UInt_t i=1;i<fh_Fi4_ToT->GetNbinsX();i++){
			TH1D * p4 = fh_Fi4_ToT->ProjectionY("",i,i,0);

				for(UInt_t j=p4->GetNbinsX()-2;j>1;j--){
					if(j==2){
						// could not find maximum
						fprintf(fout, "%d   %f \n",i-1,1000.);					
					}
					if(p4->GetBinContent(j)>100){
						// found maximum for ToT calibration
//			   			cout<<"Fiber "<<i<<"  Max "<<p4->GetBinCenter(j)<<endl;
						fprintf(fout, "%d   %f \n",i-1,p4->GetBinCenter(j));
						break;
					}
				}
			}
			fclose(fout);
		}
    }
		
    if (fMappedItemsFi5){
		fh_Fi5_channels ->Write();
		fh_Fi5_fibers ->Write();    

		fh_Fi5_eff->Scale(1./fNEvents5);			 
		cout<<"Events with ptof_cut5: "<< fNEvents5 <<endl;	 
		fh_Fi5_eff ->Write();    
	    fh_Fi5_mult->Write(); 
		fh_Fi5_multihit ->Write();
		fh_Fi5_ToT->Write();
		fh_Fi5_ToT_m->Write();
		fh_Fi5_FibervsTime->Write();
  	    fh_Fi5_multihit_s->Write();
        fh_Fi5_ToT_s->Write();
        fh_Fi5_ToTvsTime_m->Write();
		fh_Fi5_ToF->Write();
		fh_Fi5_xpos->Write();
		fh_Fi5_ypos->Write();
		for (Int_t j = 0; j < 8; j++){
    		fh_Fi5_ToTvsTime_s[j]->Write();
		}

        Bool_t calib5=false;
        if(calib5){
			FILE *fout = NULL;  	    
			fout = fopen("max_values5.dat", "w");
			if(!fout){
				cerr << "Could not open file with max values for writing!\n";
				return;
			}
			for(UInt_t i=1;i<fh_Fi5_ToT->GetNbinsX();i++){
				TH1D * p5 = fh_Fi5_ToT->ProjectionY("",i,i,0);

				for(UInt_t j=p5->GetNbinsX()-2;j>1;j--){
					if(j==2){
						// could not find maximum
						fprintf(fout, "%d   %f \n",i-1,1000.);					
					}
					if(p5->GetBinContent(j)>100 ){
//						cout<<"Fiber "<<i<<"  Max "<<p5->GetBinCenter(j)<<endl;
						fprintf(fout, "%d   %f \n",i-1,p5->GetBinCenter(j));
						break;
					}
				}
			}
			fclose(fout);
		}
    }
        
    if (fMappedItemsFi6){
	    fh_Fi6_channels ->Write();
	    fh_Fi6_fibers ->Write();   
		fh_Fi6_eff->Scale(1./fNEvents6);		
		cout<<"Events with ptof_cut6: "<< fNEvents6 <<endl;	 
		fh_Fi6_eff->Write();
	    fh_Fi6_mult->Write(); 
	    fh_Fi6_multihit ->Write();
	    fh_Fi6_ToT->Write();
	    fh_Fi6_FibervsTime->Write();
	    fh_Fi6_multihit_s->Write();
		fh_Fi6_ToT_s->Write();
        fh_Fi6_ToTvsTime_m->Write();
		fh_Fi6_ToF->Write();
		fh_Fi6_xpos->Write();
		for (Int_t j = 0; j < 4; j++){
    		fh_Fi6_ToTvsTime_s[j]->Write();
		}

        Bool_t calib6=false;
        if(calib6){
			FILE *fout = NULL;
			fout = fopen("max_values6.dat", "w");
			if(!fout){
				cerr << "Could not open file with max values for writing!\n";
				return;
			}
			for(UInt_t i=1;i<fh_Fi6_ToT->GetNbinsX();i++){
				TH1D * p6 = fh_Fi6_ToT->ProjectionY("",i,i,0);
				for(UInt_t j=p6->GetNbinsX()-2;j>1;j--){
					if(j==2){
						// could not find maximum
						fprintf(fout, "%d   %f \n",i-1,1000.);					
					}
					if(p6->GetBinContent(j)>100 ){
						//cout<<"Fiber "<<i<<"  Max "<<p6->GetBinCenter(j)<<endl;
						fprintf(fout, "%d   %f \n",i-1,p6->GetBinCenter(j));
						break;
					}
				}
			}
			fclose(fout);
		}

    }
}

ClassImp(R3BOnlineSpectra)
