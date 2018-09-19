
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
//#include "/u/kelic/R3BRoot/r3bsource/ext_h101.h"
#include "/u/kelic/R3BRoot/r3bsource/ext_h101_los.h"
#include "/u/kelic/R3BRoot/r3bsource/ext_h101_tofd.h"

}
typedef struct EXT_STR_h101_t
{
  EXT_STR_h101_LOS_onion los;
  EXT_STR_h101_TOFD_onion tofd;
} EXT_STR_h101;

void calib_tofd(Int_t RunId)
{
//      Int_t RunId=100;
    TString runNumber=Form ("%03d", RunId);
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

	/* Create source using ucesb for input ------------------ */
	TString filename = "/SAT/nyx/land/jun2016/stitched/run"+runNumber+"*.lmd";
//  TString filename = "stream://lxfs186:8000";
	TString outputFileName = "/u/kelic/R3BRoot/macros/r3b/unpack/june2016/run"+runNumber + "_tofd_time_cal.root";
	TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
	TString ucesb_dir = getenv("UCESB_DIR");
//	TString ucesb_path = ucesb_dir + "/../upexps/jun16Xe2/jun16Xe2";	
	TString ucesb_path = ucesb_dir + "/../upexps/jun16Xe/jun16Xe --allow-errors";

	EXT_STR_h101 ucesb_struct;
	R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
    ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
	source->SetMaxEvents(nev);

//	source->AddReader( new R3BTofdReader(&ucesb_struct) );
    source->AddReader( new R3BLosReader ((EXT_STR_h101_LOS*)&ucesb_struct.los, offsetof(EXT_STR_h101, los)) );
    source->AddReader( new R3BTofdReader((EXT_STR_h101_TOFD*)&ucesb_struct.tofd, offsetof(EXT_STR_h101, tofd)) );

	/* Create online run ------------------------------------ */
	FairRunOnline* run = new FairRunOnline(source);
    run->SetRunId(RunId);

    // Create analysis run ----------------------------------
    //FairRunAna* run = new FairRunAna();
    run->SetOutputFile(outputFileName.Data());

	/* ------------------------------------------------------ */
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut2 = new FairParRootFileIo(kParameterMerged);
    parOut2->open("parameter/tofd_time_params_run"+ runNumber + ".root");
    rtdb->setOutput(parOut2);
    rtdb->print();



	/* Create ALADIN field map ------------------------------ */
/*	R3BAladinFieldMap* magField = new R3BAladinFieldMap("AladinMaps");
	Double_t fMeasCurrent = 2500.; // I_current [A]
	magField->SetCurrent(fMeasCurrent);
	magField->SetScale(1.);
	run->SetField(magField);
*/
	/* ------------------------------------------------------ */



	/* Calibrate Tofd ---------------------------------------- */
    const Int_t updateRate = 15000;
    const Int_t minStats = 1000;        // minimum number of entries for TCAL calibration
    R3BTofdMapped2TCalPar* tofdCalibrator = new R3BTofdMapped2TCalPar("R3BTofdMapped2CalPar", 1);
    tofdCalibrator->SetUpdateRate(updateRate);
    tofdCalibrator->SetMinStats(minStats);
    //losCalibrator->SetTrigger(trigger);
    tofdCalibrator->SetNofModules(10, 100); // planes, bars per plane
    run->AddTask(tofdCalibrator);


	/* Initialize ------------------------------------------- */
	run->Init();
	FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
	/* ------------------------------------------------------ */


	/* Run -------------------------------------------------- */
	run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);
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

