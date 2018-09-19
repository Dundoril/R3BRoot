
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
#include "/u/kelic/R3BRoot/r3bsource/ext_h101.h"

}

void unpack_los_online()
{
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

	/* Create source using ucesb for input ------------------ */
 
	TString filename = "/SAT/hera/land/s438b/stitched/s438b/lmd/run301_4307.lmd.gz";
//	TString filename = "/SAT/hera/land/htoernqv/calib_los_tofd.lmd"; // LOS data
//	TString filename = "stream://x86l-3";
	TString outputFileName = "/tmp/unpack_los.root";
	TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
	TString ucesb_dir = getenv("UCESB_DIR");
	TString ucesb_path = ucesb_dir + "/../upexps/jun16/jun16";

	EXT_STR_h101 ucesb_struct;
	R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
	    ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
	source->SetMaxEvents(nev);

//	source->AddReader( new R3BPspReader (&ucesb_struct) );
	source->AddReader( new R3BLosReader (&ucesb_struct) );
//	source->AddReader( new R3BTofdReader(&ucesb_struct) );

	/*source->AddReader(new R3BNeulandTamexReader(&ucesb_struct));*/

	/* ------------------------------------------------------ */

	/* Create online run ------------------------------------ */
	FairRunOnline* run = new FairRunOnline(source);

    // Create analysis run ----------------------------------
    //FairRunAna* run = new FairRunAna();

    run->SetOutputFile(outputFileName.Data());

	/* ------------------------------------------------------ */

	/* Runtime data base ------------------------------------ */
	FairRuntimeDb* rtdb = run->GetRuntimeDb();
	Bool_t kParameterMerged = kTRUE;
	TString parFileName    = "los_params_18-05-16.root";  // name of parameter file
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
/*
    const Int_t updateRate = 15000;
    const Int_t minStats = 10000;        // minimum number of entries for TCAL calibration
    R3BLosMapped2CalPar* losCalibrator = new R3BLosMapped2CalPar("R3BLosMapped2CalPar", 1);
    losCalibrator->SetUpdateRate(updateRate);
    losCalibrator->SetMinStats(minStats);
    //losCalibrator->SetTrigger(trigger);
    losCalibrator->SetNofModules(1, 5); // dets, bars(incl. master trigger, if present)
    run->AddTask(losCalibrator);
*/


	/* Add analysis task ------------------------------------ */
	// convert Mapped => Cal

	R3BLosMapped2Cal* losMapped2Cal=new R3BLosMapped2Cal("LosTCalPar", 1);
	losMapped2Cal->SetNofModules(1, 5);
	run->AddTask( losMapped2Cal );

	R3BLosCal2Hit* losCal2Hit=new R3BLosCal2Hit("losCal2Hit", 1);
	run->AddTask( losCal2Hit );


	/* ------------------------------------------------------ */


	/* Initialize ------------------------------------------- */
	run->Init();
	FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
	/* ------------------------------------------------------ */


	/* Run -------------------------------------------------- */
	run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
	//rtdb->saveOutput();
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

