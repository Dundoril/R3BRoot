
/*
 * In order to generate input for this, please go to $UCESB_DIR and run:
 *
 * Additional info:
 * To generate the header file used for the R3BUcesbSource (ext_h101.h), use:
 *
 * $UCESB_DIR/upexps/s438b/s438b --ntuple=UNPACK:TRIGGER,UNPACK:EVENTNO,RAW\
 *     STRUCT_HH,ext_h101.h
 *
 * Put this header file into the 'r3bsource' directory and recompile.
 *
 * Author: B. Löher
 * Based on: unpack_offline_160.C from M. Heil
 * 
 * Bastis UCESB: export UCESB_DIR=/u/bloeher/git/ucesb/
 */

extern "C" {
	#include </u/mheil/R3BRoot/r3bsource/ext_h101_ptof.h>
	#include </u/mheil/R3BRoot/r3bsource/ext_h101_unpack.h>
}

struct EXT_STR_h101_t
{
	EXT_STR_h101_unpack_t unpack;
	EXT_STR_h101_PTOF_t ptof;
};

void calib_ptof_paddles(Int_t RunId = 72){
	TString runNumber = Form("%03d", RunId);
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
	const Int_t max_events_ucesb = -1;
	TString max_events = Form("%d", max_events_ucesb);

	/* Create source using ucesb for input ------------------ */
//    TString filename = "/d/land2/mheil/kvi2018/lmd/pre"+runNumber+".lmd";
	TString filename = "/u/mheil/nyx/bloeher/data/kvi2018/lmd/run"+runNumber+"_*.lmd";
    TString outputFileName = "/u/mheil/nyx/mheil2/data/kvi2018/rootfiles/run"+runNumber+".root";
	TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
	TString ucesb_dir = getenv("UCESB_DIR");
	
    TString ucesb_path;
    if(RunId<61) ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_001_060";
    else if(RunId<69) ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_061_068";
    else if(RunId<86) ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_before_Run086";
	else ucesb_path = "/u/mheil/upexps/kvi2018/kvi2018_061_068";

	EXT_STR_h101 ucesb_struct;
	R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
	    ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
	source->SetMaxEvents(nev);

	source->AddReader(new R3BUnpackReader(
	    (EXT_STR_h101_unpack_t *)&ucesb_struct,
	    offsetof(EXT_STR_h101, unpack)));
	source->AddReader(new R3BPtofReader(
	    (EXT_STR_h101_PTOF_t *)&ucesb_struct.ptof,
	    offsetof(EXT_STR_h101, ptof)));


	const Int_t refresh = 10;  /* refresh rate for saving */

	/* Create online run ------------------------------------ */
#define RUN_ONLINE
#define USE_HTTP_SERVER
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
	/* Set output file name --------------------------------- */
	run->SetOutputFile(outputFileName.Data());
	/* ------------------------------------------------------ */

	FairRuntimeDb* rtdb1 = run->GetRuntimeDb();
	Bool_t kParameterMerged = kTRUE;
	FairParRootFileIo* parOut1 = new FairParRootFileIo(kParameterMerged);
	TList *parList = new TList();
	// ToDo: Adjust these paths to your setup:
	parList->Add(new TObjString("tcal_ptof_072.root"));
	parOut1->open(parList);
	rtdb1->setFirstInput(parOut1);

    FairParRootFileIo* parOut2 = new FairParRootFileIo(kParameterMerged);
    parOut2->open("hit_ptof_072.root");
    rtdb1->setOutput(parOut2);
	rtdb1->print();

	rtdb1->addRun(RunId);
	rtdb1->getContainer("PtofTCalPar");
	rtdb1->setInputVersion(RunId, (char*)"PtofTCalPar", 1, 1);

    //rtdb1->getContainer("PtofHitPar");
    //rtdb1->setInputVersion(RunId, (char*)"PtofHitPar", 1, 1);

	/* Add analysis tasks ----------------------------------- */	
	run->AddTask( new R3BPtofMapped2Cal("PtofTCalPar", 1) );
		
    R3BPtofCal2HitPar* PtofCal2HitPar=new R3BPtofCal2HitPar("PtofCal2HitPar", 1);
    PtofCal2HitPar->SetBeamCharge(6);
	run->AddTask( PtofCal2HitPar );

	/* ------------------------------------------------------ */
    R3BOnlineSpectra* r3bOnlineSpectra=new R3BOnlineSpectra("OnlineSpectra", 1);
//    run->AddTask( r3bOnlineSpectra );


	/* Initialize ------------------------------------------- */

	run->Init();

	/* Set log level either to WARNING, DEBUG or ERROR */
//	FairLogger::GetLogger()->SetLogScreenLevel("ERROR");
//	FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
	FairLogger::GetLogger()->SetLogScreenLevel("INFO");
//	FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");

	/* Run -------------------------------------------------- */
	run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
	
	rtdb1->saveOutput();

	/* Cleanup ---------------------------------------------- */
	timer.Stop();
	Double_t rtime = timer.RealTime();
	Double_t ctime = timer.CpuTime();
	cout << endl << endl;
	cout << "Macro finished succesfully." << endl;
	cout << "Output file is " << outputFileName << endl;
	cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
	    << endl << endl;
}

