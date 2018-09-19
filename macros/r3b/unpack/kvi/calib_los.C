
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

extern "C" {
#include "/u/mheil/R3BRoot/r3bsource/ext_h101_los_tamex.h"
#include "/u/mheil/R3BRoot/r3bsource/ext_h101_unpack.h"
}
struct EXT_STR_h101_t
{
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_LOS_TAMEX_onion los;
};

void calib_los(Int_t RunId=9)
{
    TString runNumber=Form ("%03d", RunId);
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

	/* Create source using ucesb for input ------------------ */
     
//	TString filename = "/d/land2/kvi2018/lmd/run"+runNumber+"*.lmd";
    TString filename = "/u/mheil/nyx1/bloeher/data/kvi2018/lmd/run"+runNumber+"_*.lmd";
    TString outputFileName = "/tmp/tcal_pre"+runNumber+".root";
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


  const Int_t refresh = 100;  /* refresh rate for saving */

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

    run->SetOutputFile(outputFileName.Data());


	/* Runtime data base ------------------------------------ */
	FairRuntimeDb* rtdb = run->GetRuntimeDb();
	Bool_t kParameterMerged = kTRUE;
	TString parFileName    = "tcal_los_"+runNumber+".root";  // name of parameter file	
	FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
	parOut->open(parFileName);
    rtdb->setFirstInput(parOut);
    rtdb->setOutput(parOut);


	/* Calibrate Los ---------------------------------------- */
    const Int_t updateRate = 1000;
    const Int_t minStats = 10000;        // minimum number of entries for TCAL calibration
    R3BLosMapped2CalPar* losCalibrator = new R3BLosMapped2CalPar("R3BLosMapped2CalPar", 1);
    losCalibrator->SetUpdateRate(updateRate);
    losCalibrator->SetMinStats(minStats);
    //losCalibrator->SetTrigger(trigger);
    losCalibrator->SetNofModules(1, 16); // dets, bars(incl. master trigger)
    run->AddTask(losCalibrator);
	/* Calibrate Los - END */


	/* Initialize ------------------------------------------- */
	run->Init();
	FairLogger::GetLogger()->SetLogScreenLevel("INFO");
	//FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
	/* ------------------------------------------------------ */


	/* Run -------------------------------------------------- */
	run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
	if (rtdb->getCurrentRun()) cout << "have run" << endl;
	else cout << "have no run" << endl;
	rtdb->saveOutput();
	/* ------------------------------------------------------ */

	timer.Stop();
	Double_t rtime = timer.RealTime();
	Double_t ctime = timer.CpuTime();
	cout << endl << endl;
	cout << "Macro finished succesfully." << endl;
	cout << "Output file is " << outputFileName << endl;
	cout << "Real time " << rtime << " s, CPU time " << ctime << " s"
		     << endl << endl;
}

