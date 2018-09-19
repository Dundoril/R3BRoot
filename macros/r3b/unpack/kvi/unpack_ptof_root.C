
void unpack_ptof(Int_t RunId = 72)
{
	TString runNumber = Form("%03d", RunId);
	TStopwatch timer;
	timer.Start();

	const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

	/* Create source using ucesb for input ------------------ */
    TString inputFileName = "/u/mheil/nyx/mheil2/data/kvi2018/rootfiles/run"+runNumber+".root";
    TString outputFileName = "/u/mheil/nyx/mheil2/data/kvi2018/rootfiles/run_hit"+runNumber+".root";

	/* Create analysis run ---------------------------------- */
	FairRunAna* run = new FairRunAna();
	run->SetSource(new FairFileSource(inputFileName));
	/* Set output file name --------------------------------- */
	run->SetOutputFile(outputFileName.Data());
	/* ------------------------------------------------------ */

	FairRuntimeDb* rtdb1 = run->GetRuntimeDb();
	Bool_t kParameterMerged = kTRUE;
	FairParRootFileIo* parOut1 = new FairParRootFileIo(kParameterMerged);
	TList *parList = new TList();
	// ToDo: Adjust these paths to your setup:
	parList->Add(new TObjString("tcal_ptof_072.root"));
    parList->Add(new TObjString("hit_ptof_072.root"));
	parOut1->open(parList);
	rtdb1->setFirstInput(parOut1);

	rtdb1->addRun(RunId);
	rtdb1->getContainer("PtofTCalPar");
	rtdb1->setInputVersion(RunId, (char*)"PtofTCalPar", 1, 1);

    rtdb1->getContainer("PtofHitPar");
    rtdb1->setInputVersion(RunId, (char*)"PtofHitPar", 1, 1);


	/* Add analysis tasks ----------------------------------- */	
    R3BPtofCal2Hit* PtofCal2Hit=new R3BPtofCal2Hit("PtofCal2Hit", 1);
	run->AddTask( PtofCal2Hit );

	/* ------------------------------------------------------ */
    R3BOnlineSpectra* r3bOnlineSpectra=new R3BOnlineSpectra("OnlineSpectra", 1);
//    run->AddTask( r3bOnlineSpectra );


	/* Initialize ------------------------------------------- */

	run->Init();

	/* Set log level either to WARNING, DEBUG or ERROR */
	FairLogger::GetLogger()->SetLogScreenLevel("ERROR");
//	FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
//	FairLogger::GetLogger()->SetLogScreenLevel("INFO");
//	FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");

	/* Run -------------------------------------------------- */
	run->Run();

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

