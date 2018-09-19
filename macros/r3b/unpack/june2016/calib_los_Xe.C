
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
//#include "/home/bloeher/git/R3BRoot/r3bsource/ext_h101_full.h"
//#include "/u/rplag/R3BRoot/r3bsource/ext_h101.h"
#include "/u/kelic/R3BRoot/r3bsource/ext_h101.h"
}

void calib_los(Int_t RunId)
{
//      Int_t RunId=100;
    TString runNumber=Form ("%03d", RunId);
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

	/* Create source using ucesb for input ------------------ */
 
	TString filename = "/SAT/hera/land/jun2016/stitched/run"+runNumber+"*.lmd";

//	TString filename = "stream://x86l-3";
//    TString filename = "stream://lxfs186:8000";

	TString outputFileName = "/SAT/hera/land/jun2016/rootfiles/run"+ runNumber + "_los_time_cal_a.root";
	TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
	TString ucesb_dir = getenv("UCESB_DIR");
//	TString ucesb_path = ucesb_dir + "/../upexps/s438b/s438b";
	TString ucesb_path = ucesb_dir + "/../upexps/jun16Xe/jun16Xe";


	EXT_STR_h101 ucesb_struct;
	R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
	    ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
	source->SetMaxEvents(nev);

	//source->AddReader(new R3BPspReader(&ucesb_struct));
	source->AddReader(new R3BLosReader(&ucesb_struct));
	/*source->AddReader(new R3BNeulandTamexReader(&ucesb_struct));*/

	/* ------------------------------------------------------ */

	/* Create online run ------------------------------------ */
	FairRunOnline* run = new FairRunOnline(source);
//        run->SetRunId(250516);
        run->SetRunId(RunId);

    // Create analysis run ----------------------------------
    //FairRunAna* run = new FairRunAna();

    run->SetOutputFile(outputFileName.Data());

	/* ------------------------------------------------------ */

	/* Runtime data base ------------------------------------ */
	FairRuntimeDb* rtdb = run->GetRuntimeDb();
	Bool_t kParameterMerged = kTRUE;
	TString parFileName    = "parameter/los_time_params_run"+ runNumber + ".root";  // name of parameter file
	FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
	parOut->open(parFileName);
    rtdb->setFirstInput(parOut);
    rtdb->setOutput(parOut);
	/* ------------------------------------------------------ */



	/* Create ALADIN field map ------------------------------ */
/*	R3BAladinFieldMap* magField = new R3BAladinFieldMap("AladinMaps");
	Double_t fMeasCurrent = 2500.; // I_current [A]
	magField->SetCurrent(fMeasCurrent);
	magField->SetScale(1.);
	run->SetField(magField);
	*/
	/* ------------------------------------------------------ */



	/* Calibrate Los ---------------------------------------- */
    const Int_t updateRate = 15000;
    const Int_t minStats = 10000;        // minimum number of entries for TCAL calibration
    R3BLosMapped2CalPar* losCalibrator = new R3BLosMapped2CalPar("R3BLosMapped2CalPar", 1);
    losCalibrator->SetUpdateRate(updateRate);
    losCalibrator->SetMinStats(minStats);
    //losCalibrator->SetTrigger(trigger);
    losCalibrator->SetNofModules(1, 5); // dets, bars(incl. master trigger)
    run->AddTask(losCalibrator);
	/* Calibrate Los - END */



	/* Add analysis task ------------------------------------ */
	// convert Mapped => Cal
	//R3BLosMapped2Cal* losMapped2Cal=new R3BLosMapped2Cal("losMapped2Cal", 1);
	//losMapped2Cal->SetNofModules(2, 5);
	//run->AddTask( losMapped2Cal );
	
	//R3BPspxCal* ana = new R3BPspxCal("PspxMappedAna", 1); 
	//run->AddTask(ana);
	/* ------------------------------------------------------ */


	/* Initialize ------------------------------------------- */
	run->Init();
	//FairLogger::GetLogger()->SetLogScreenLevel("INFO");
	FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
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

