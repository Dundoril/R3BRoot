
/* In order to generate input for this, please go to $UCESB_DIR and run:
 *
 * Additional info:
 * To generate the header file used for the R3BUcesbSource (ext_h101.h), use:
 *
 * $UCESB_DIR/upexps/s438b/s438b --ntuple=UNPACK:TRIGGER,UNPACK:EVENTNO,RAW\
 *     STRUCT_HH,ext_h101.h
 *
 * Put this header file into the 'r3bsource' directory and recompile.
 * */

#include <sstream>
#include <fstream>
#include <iostream>

extern "C" {
	#include "/u/mheil/R3BRoot/r3bsource/ext_h101_los_tamex.h"
	#include "/u/mheil/R3BRoot/r3bsource/ext_h101_ptof.h"
	#include "/u/mheil/R3BRoot/r3bsource/ext_h101_unpack.h"
}
struct EXT_STR_h101_t
{
	EXT_STR_h101_unpack_t unpack;
	EXT_STR_h101_LOS_TAMEX_onion los;
	EXT_STR_h101_PTOF_t ptof;
};

void unpack_ptof(Int_t RunId=72)
{
    TString runNumber=Form ("%03d", RunId);
    TStopwatch timer;
    timer.Start();

    const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
    

    /* Create source using ucesb for input ------------------ */

	TString filename = "/u/mheil/nyx/bloeher/data/kvi2018/lmd/run"+runNumber+"_*.lmd";
//	TString filename = "/d/land2/kvi2018/lmd/run"+runNumber+"_*.lmd";
    //	TString filename = "stream://krapc005:9000 ";
//    TString outputFileName = "/d/land2/kvi2018/rootfiles/run"+runNumber+".root";
    TString outputFileName = "/tmp/rootfiles/hit_run"+runNumber+".root";
    TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
    TString ucesb_dir = getenv("UCESB_DIR");

    TString ucesb_path;
    if(RunId<61) ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_001_060";
    else if(RunId<69) ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_061_068";
    else if(RunId<102) ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_069_101";

	EXT_STR_h101 ucesb_struct;
	R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
	    ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
	source->SetMaxEvents(nev);

    source->AddReader(new R3BUnpackReader(
        (EXT_STR_h101_unpack_t *)&ucesb_struct,
        offsetof(EXT_STR_h101, unpack)));

    source->AddReader( new R3BLosReader (
	   (EXT_STR_h101_LOS_TAMEX *)&ucesb_struct.los, 
	   offsetof(EXT_STR_h101, los)) );
  
	source->AddReader(new R3BPtofReader(
	    (EXT_STR_h101_PTOF_t *)&ucesb_struct.ptof,
	    offsetof(EXT_STR_h101, ptof)));

    const Int_t refresh = 100;                 // refresh rate for saving     

  /* Create online run ------------------------------------ */
#define RUN_ONLINE
//#define USE_HTTP_SERVER
#ifdef RUN_ONLINE
  FairRunOnline* run = new FairRunOnline(source);
  run->SetRunId(RunId);
#ifdef USE_HTTP_SERVER
  run->ActivateHttpServer(refresh);
#endif
#else
  /* Create analysis run ---------------------------------- */
  FairRunAna* run = new FairRunAna();
#endif
  

    // Create analysis run ----------------------------------
    run->SetOutputFile(outputFileName.Data());


    FairRuntimeDb* rtdb1 = run->GetRuntimeDb();
    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut1 = new FairParRootFileIo(kParameterMerged);
    TList *parList = new TList();
    parList->Add(new TObjString("tcal_los_042.root")); 
	parList->Add(new TObjString("tcal_ptof_072.root"));
    parList->Add(new TObjString("hit_ptof_072.root"));
    parOut1->open(parList);
    rtdb1->setFirstInput(parOut1);
    rtdb1->print();
   
    rtdb1->addRun(RunId);
    rtdb1->getContainer("LosTCalPar");
    rtdb1->setInputVersion(RunId, (char*)"LosTCalPar", 1, 1);
	rtdb1->getContainer("PtofTCalPar");
	rtdb1->setInputVersion(RunId, (char*)"PtofTCalPar", 1, 1);
    rtdb1->getContainer("PtofHitPar");
    rtdb1->setInputVersion(RunId, (char*)"PtofHitPar", 1, 1);


    /* Add analysis task ------------------------------------ */
    // convert Mapped => Cal

    R3BLosMapped2Cal* losMapped2Cal=new R3BLosMapped2Cal("LosTCalPar", 1);
    losMapped2Cal->SetNofModules(1,8);
    run->AddTask( losMapped2Cal );

    R3BLosCal2Hit* losCal2Hit=new R3BLosCal2Hit("losCal2Hit", 1);
 
 
//  Set parameters for X,Y calibration
//  offsetX1, offsetY1,VeffX1,VeffY1, offsetX2, offsetY2,VeffX2,VeffY2 
 
 // Starting     
    losCal2Hit->SetLosParamMCFD(0., 0., 1., 1. ,0., 0., 1., 1.);     // spectra X1_vs_Y1, X2_vs_Y2
    losCal2Hit->SetLosParamMCFDwc(0., 0., 1., 1. ,0., 0., 1., 1.);   // spectra X1_vs_Y1_wc, X2_vs_Y2_wc    
    losCal2Hit->SetLosParamToT(0., 0., 1., 1. ,0., 0., 1., 1.); 
    losCal2Hit->SetLosParamToTc(0., 0., 1., 1. ,0., 0., 1., 1.); 
    losCal2Hit->SetLosParamTAMEX(0., 0., 1., 1. ,0., 0., 1., 1.);    // spectra XT1_vs_YT1, XT2_vs_YT2     
 
          
// Set Sci shape, variable iSciType:
// 0 - Large (10x10) squared, with 2-inch PM
// 1 - Small octagonal, with 1-inch PM
// 2 - Small (5x5) squared, with 2-inch PM  
// 3 - Large octagonal, with 2-inch PM 
// 4 - Large (10x10) squared, with 1-inch PM
// 5 - Large octagional, with 4 2-inch and 4 1inch PMs
// 6 - Large octagional, with 8 1-inch PMs

// losCal2Hit->SetLosInput(iSciType,walk_param_file_name,totcorrection_factor_file_name);

    losCal2Hit->SetLosInput(6,"walk_param_empty.dat",
    "tot_param_empty.dat");             


	/* Add analysis tasks ----------------------------------- */
    run->AddTask( losCal2Hit );

	run->AddTask( new R3BPtofMapped2Cal("PtofTCalPar", 1) );
			

    R3BPtofCal2Hit* PtofCal2Hit=new R3BPtofCal2Hit("PtofCal2Hit", 1);
	run->AddTask( PtofCal2Hit );

	/* ------------------------------------------------------ */
	R3BOnlineSpectra* r3bOnlineSpectra=new R3BOnlineSpectra("OnlineSpectra", 1);
//	run->AddTask( r3bOnlineSpectra );
    
    
    
    

    /* Initialize ------------------------------------------- */
    run->Init();
    rtdb1->print();
//    FairLogger::GetLogger()->SetLogScreenLevel("INFO");    
//    FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
//    FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");
    FairLogger::GetLogger()->SetLogScreenLevel("ERROR");

    /* Run -------------------------------------------------- */
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
//    rtdb1->saveOutput();

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    cout << endl << endl;
    cout << "Macro finished succesfully." << endl;
    cout << "Output file is " << outputFileName << endl;
    cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
         << endl << endl;
}

