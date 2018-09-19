
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
 */

// ToDo: replace /u/rplag with the actual path to your installation
extern "C" {
#include </u/mheil/R3BRoot/r3bsource/ext_h101_ptof.h>
#include </u/mheil/R3BRoot/r3bsource/ext_h101_unpack.h>
}

struct EXT_STR_h101_t
{
	EXT_STR_h101_unpack_t unpack;
	EXT_STR_h101_ptof_t ptof;
};

void
calib_ptof(Int_t RunId = 200)
{
	TString runNumber = Form("%03d", RunId);
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
	const Int_t max_events_ucesb = -1;
	TString max_events = Form("%d", max_events_ucesb);

	/* Create source using ucesb for input ------------------ */
	// ToDo: adjust all paths accordingly
//	TString filename = "/SAT/nyx/land/mheil/ptof/lmd/run" + runNumber + ".lmd";

	TString filename = "/d/land2/mheil/ptof/lmd/run"+runNumber+".lmd";
/*
	for(Int_t i=102; i<133;i++){
		runNumber = Form("%03d", i);
		filename = filename+ " /d/land2/mheil/ptof/lmd/run" + runNumber + ".lmd";
	}
*/
	//filename=filename+" /SAT/nyx/land/mheil/ptof/lmd/run004.lmd";
	TString outputFileName = "/tmp/testCalib_michael.root";
	TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
	TString ucesb_dir = getenv("UCESB_DIR");
	TString ucesb_path = "/u/mheil/upexps/1718/1718"
	    " --max-events=" + max_events;

	EXT_STR_h101 ucesb_struct;
	R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
	    ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
	source->SetMaxEvents(nev);

	source->AddReader(new R3BUnpackReader(
	    (EXT_STR_h101_unpack_t *)&ucesb_struct,
	    offsetof(EXT_STR_h101, unpack)));
	source->AddReader(new R3BPtofReader(
	    (EXT_STR_h101_ptof_t *)&ucesb_struct.ptof,
	    offsetof(EXT_STR_h101, ptof)));

	const Int_t refresh = 100;  /* refresh rate for saving */

	/* Create online run ------------------------------------ */
#define RUN_ONLINE
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



	FairParRootFileIo* parOut2 = new FairParRootFileIo(kParameterMerged);
	parOut2->open("ptof_cal_params_run200.root");
	rtdb1->setOutput(parOut2);

	rtdb1->print();

	rtdb1->addRun(RunId);
	rtdb1->getContainer("PtofTCalPar");
	rtdb1->setInputVersion(RunId, (char*)"PtofTCalPar", 1, 1);
//	rtdb1->getContainer("Fi6TCalPar");
//	rtdb1->setInputVersion(RunId, (char*)"Fi6TCalPar", 1, 1);




	/* Add analysis tasks ----------------------------------- */
    const Int_t updateRate = 15000;
    const Int_t minStats = 10000;        // minimum number of entries for TCAL calibration
    R3BPtofMapped2CalPar* ptofCalibrator = new R3BPtofMapped2CalPar("R3BPtofMapped2CalPar", 1);
    ptofCalibrator->SetUpdateRate(updateRate);
    ptofCalibrator->SetMinStats(minStats);
	// ToDo: You probably have not implemented this optional function.
	// Then skip it. The standard solution from Ralf needs it though.
	//ptofCalibrator->SetNofModules(10, 100); // planes, bars per plane
	run->AddTask(ptofCalibrator);


	/* Initialize ------------------------------------------- */
	run->Init();

	/* Set log level either to WARNING, DEBUG or ERROR */
	FairLogger::GetLogger()->SetLogScreenLevel("INFO");
//	FairLogger::GetLogger()->SetLogScreenLevel("ERROR");

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

