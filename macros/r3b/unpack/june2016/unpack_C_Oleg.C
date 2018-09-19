
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
//#include "/u/kelic/R3BRoot/r3bsource/ext_h101.h"
#include "/u/mheil/R3BRoot/r3bsource/ext_h101_los.h"
//#include "/u/mheil/R3BRoot/r3bsource/ext_h101_tofd.h"

}
typedef struct EXT_STR_h101_t
{
  EXT_STR_h101_LOS_onion los;
//  EXT_STR_h101_TOFD_onion tofd;
} EXT_STR_h101;

void unpack(Int_t RunId)
{
//    Int_t RunId=100;
   TString runNumber=Form ("%03d", RunId);
   TStopwatch timer;
    timer.Start();

    const Int_t nev = -1; /* number of events to read, -1 - until CTRL+C */

    /* Create source using ucesb for input ------------------ */
 
//    TString filename = "stream://lxfs186:8000";
    TString filename = "/SAT/nyx/land/jun2016/stitched/run"+runNumber+"_*.lmd";
//    TString outputFileName = "/SAT/nyx/land/jun2016/rootfiles/run"+runNumber + "_los_tofd_hit_b.root";
    TString outputFileName = "/u/mheil/R3BRoot/macros/r3b/unpack/june2016/run"+runNumber + ".root";   
    TString ntuple_options = "UNPACK:EVENTNO,UNPACK:TRIGGER,RAW";
    TString ucesb_dir = getenv("UCESB_DIR");
    TString ucesb_path = ucesb_dir + "/../upexps/jun16/jun16C";

    EXT_STR_h101 ucesb_struct;
    R3BUcesbSource* source = new R3BUcesbSource(filename, ntuple_options,
	ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);

    source->AddReader( new R3BLosReader ((EXT_STR_h101_LOS*)&ucesb_struct.los, offsetof(EXT_STR_h101, los)) );
//    source->AddReader( new R3BTofdReader((EXT_STR_h101_TOFD*)&ucesb_struct.tofd, offsetof(EXT_STR_h101, tofd)) );

    const Int_t refresh = 100;                 // refresh rate for saving     /* Create online run ------------------------------------ */
    FairRunOnline* run = new FairRunOnline(source);
    run->SetRunId(RunId);
//    run->ActivateHttpServer(refresh);

    // Create analysis run ----------------------------------
    //FairRunAna* run = new FairRunAna();
    run->SetOutputFile(outputFileName.Data());


    FairRuntimeDb* rtdb1 = run->GetRuntimeDb();
    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut1 = new FairParRootFileIo(kParameterMerged);
    TList *parList = new TList();
//    parList->Add(new TObjString("parameter/tofd_time_params_run039.root"));
    parList->Add(new TObjString("parameter/los_time_params_run"+runNumber + ".root"));
//    parList->Add(new TObjString("parameter/tofd_hit_params_run039.root"));
    parOut1->open(parList);
    rtdb1->setFirstInput(parOut1);
    rtdb1->print();


    rtdb1->addRun(RunId);
    rtdb1->getContainer("LosTCalPar");
    rtdb1->setInputVersion(RunId, (char*)"LosTCalPar", 1, 1);
//    rtdb1->getContainer("TofdTCalPar");
//    rtdb1->setInputVersion(RunId, (char*)"TofdTCalPar", 1, 1);
//    rtdb1->getContainer("TofdHitPar");
//    rtdb1->setInputVersion(RunId, (char*)"TofdHitPar", 1, 1);




    /* Add analysis task ------------------------------------ */
    // convert Mapped => Cal

    R3BLosMapped2Cal* losMapped2Cal=new R3BLosMapped2Cal("LosTCalPar", 1);
    losMapped2Cal->SetNofModules(1, 5);
    run->AddTask( losMapped2Cal );

    R3BLosCal2Hit* losCal2Hit=new R3BLosCal2Hit("losCal2Hit", 1);
    run->AddTask( losCal2Hit );

//    R3BTofdMapped2TCal* tofdMapped2Cal=new R3BTofdMapped2TCal("TofdTCalPar", 1);
//    tofdMapped2Cal->SetNofModules(5, 100);
//    run->AddTask( tofdMapped2Cal );

//    R3BTofdCal2Hit* tofdCal2Hit=new R3BTofdCal2Hit("TofdCal2Hit", 1);
//    tofdCal2Hit->SetTofdQ(54.); // Set nuclear charge Z of main beam
//    run->AddTask( tofdCal2Hit );
    /* ------------------------------------------------------ */

//    R3BOnlineSpectra* r3bOnlineSpectra=new R3BOnlineSpectra("OnlineSpectra", 1);
//    if(RunId < 54)
//    r3bOnlineSpectra->SetLosParameters(-10.0, -4.1, 7., 7.); // Set offset and effective speeds of light in x, y 
    /* Parameter set after problems with LOS_4 */
//    if(RunId >= 54)
//    r3bOnlineSpectra->SetLosParameters(-7.4, -14.9, 7., 7.); // Set offset and effective speed of light in x, y 


//    run->AddTask( r3bOnlineSpectra );




    /* Initialize ------------------------------------------- */
    run->Init();
    rtdb1->print();
    FairLogger::GetLogger()->SetLogScreenLevel("WARNING");
//    FairLogger::GetLogger()->SetLogScreenLevel("DEBUG");
//    FairLogger::GetLogger()->SetLogScreenLevel("ERROR");

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

