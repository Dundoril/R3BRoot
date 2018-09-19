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
#include "/u/mheil/R3BRoot/r3bsource/ext_h101_fibsix.h"
#include "/u/mheil/R3BRoot/r3bsource/ext_h101_unpack.h"
}
struct EXT_STR_h101_t
{
  EXT_STR_h101_unpack_t unpack;
  EXT_STR_h101_FIBSIX_t fibsix;
};


void unpack_fiber6(Int_t RunId = 56)
{
  TString runNumber=Form ("%03d", RunId);
  TStopwatch timer;
  timer.Start();

  const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */
  const Int_t max_events_ucesb = 1e9;
  TString max_events = Form("%d", max_events_ucesb);

  /* Create source using ucesb for input ------------------ */

  //	TString filename = "/SAT/hera/land/jun2016/stitched/kvi"+runNumber+"*.lmd";
  TString filename = "/d/land2/mheil/FiberTests/test"+runNumber+".lmd";
  //	TString filename = "stream://x86l-3";

  //	TString outputFileName = "/SAT/hera/land/jun2016/rootfiles/run"+ runNumber + "_los_time_cal.root";
  TString outputFileName = "/tmp/test"+runNumber+".root";
  TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
  TString ucesb_dir = getenv("UCESB_DIR");
  TString ucesb_path = "/u/mheil/uptests/fiber/fiber6"
      " --max-events=" + max_events;
  //	TString ucesb_path = ucesb_dir + "/../upexps/jun16Xe2/jun16Xe2" ;


  EXT_STR_h101 ucesb_struct;
  R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
      ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);

  source->AddReader(new R3BUnpackReader(
      (EXT_STR_h101_unpack_t *)&ucesb_struct,
      offsetof(EXT_STR_h101, unpack)));
  source->AddReader(new R3BFi6Reader(
      (EXT_STR_h101_FIBSIX_t *)&ucesb_struct.fibsix,
      offsetof(EXT_STR_h101, fibsix)));

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
  /* ------------------------------------------------------ */

  FairRuntimeDb* rtdb1 = run->GetRuntimeDb();
  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut1 = new FairParRootFileIo(kParameterMerged);
  TList *parList = new TList();
  // ToDo: Adjust these paths to your setup:
  parList->Add(new TObjString("tcal_fi6_test043.root"));
  parOut1->open(parList);
  rtdb1->setFirstInput(parOut1);
  rtdb1->print();

  rtdb1->addRun(RunId);
  rtdb1->getContainer("Fi6MAPMTTCalPar");
  rtdb1->setInputVersion(RunId, (char*)"Fi6MAPMTTCalPar", 1, 1);
  rtdb1->getContainer("Fi6SPMTTCalPar");
  rtdb1->setInputVersion(RunId, (char*)"Fi6SPMTTCalPar", 1, 1);



  /* Add analysis tasks ----------------------------------- */
  run->AddTask(new R3BFi6Mapped2Cal(1));
  run->AddTask(new R3BFi6Cal2Hit(1));
  /* ------------------------------------------------------ */
  R3BOnlineSpectra* r3bOnlineSpectra=new R3BOnlineSpectra("OnlineSpectra", 1);
  run->AddTask( r3bOnlineSpectra );


  /* Initialize ------------------------------------------- */
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("ERROR");
  //	FairLogger::GetLogger()->SetLogScreenLevel("INFO");
  //	FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");
  /* ------------------------------------------------------ */


  /* Run -------------------------------------------------- */
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

  rtdb1->saveOutput();
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

