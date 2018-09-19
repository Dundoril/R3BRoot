void run_sim_0001()
{
    TString transport = "TGeant4";
    Bool_t userPList = kFALSE; // option for TGeant4

    TString outFile = "sim_0001.root";
    TString parFile = "par_0001.root";

    Bool_t magnet = kTRUE;
    Double_t fieldScale = -0.4794;

    TString generator1 = "box";
    TString generator2 = "ascii";
    TString generator3 = "r3b";
    // TString generator = generator2;
    TString generator = generator1;
    TString inputFile = "evt_gen_16O_500AMeV_1MeV_1e5.dat";
    // TString inputFile = "evt_gen_16O_500AMeV_1MeV_test.dat";

    Int_t nEvents = 1000000;
    Bool_t storeTrajectories = kTRUE;
    Double_t randomSeed = 335566.0;

    // Target type
    TString target1 = "LeadTarget";
    TString target2 = "Para";
    TString target3 = "Para45";
    TString target4 = "LiH";
    TString targetType = target1;

    // ------------------------------------------------------------------------
    // Stable part ------------------------------------------------------------

    TString dir = getenv("VMCWORKDIR");

    // ----    Debug option   -------------------------------------------------
    gDebug = 0;

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;
    timer.Start();

    // -----   Create simulation run   ----------------------------------------
    FairRunSim* run = new FairRunSim();
    run->SetName(transport);            // Transport engine
    run->SetOutputFile(outFile.Data()); // Output file
    FairRuntimeDb* rtdb = run->GetRuntimeDb();

    //  R3B Special Physics List in G4 case
    if ((userPList == kTRUE) && (transport.CompareTo("TGeant4") == 0))
    {
        run->SetUserConfig("g4R3bConfig.C");
        run->SetUserCuts("SetCuts.C");
    }

    // -----   Create media   -------------------------------------------------
    run->SetMaterials("media_r3b.geo"); // Materials

    // -----   Create R3B geometry --------------------------------------------
    // R3B Cave definition
    FairModule* cave = new R3BCave("CAVE");
    cave->SetGeometryFileName("r3b_cave_vacuum.geo");
    run->AddModule(cave);

    // To skip the detector comment out the line with: run->AddModule(...
// 
    // Target
    Double_t distanceZeroTarget = 0.0;
    // run->AddModule(new R3BTarget(targetType, "target_" + targetType + ".geo.root"));
    run->AddModule(new R3BTarget(targetType, "target_" + targetType + ".geo.root", {distanceZeroTarget, 0.00, 0.}, {"",0.,0.,0.0}));


    // GLAD
    run->AddModule(new R3BGladMagnet("glad_v17_flange.geo.root")); // GLAD should not be moved or rotated

    // PSP
    //run->AddModule(new R3BPsp("psp_v13a.geo.root", {}, -221., -89., 94.1));

    // Fi3a detector
    Double_t distanceZeroDet = 75.5;
    Double_t fi3Distance = 1005.632;
    Double_t distanceZeroMagnet = 271.0;
    
    run->AddModule(new R3BFi3a("fi3a_16O.geo.root", {fi3Distance, 0.00, distanceZeroDet}, {"" ,-90.,90.,0.0}));

    // Fi3b detector

    run->AddModule(new R3BFi3b("fi3b_16O.geo.root", {-fi3Distance, 0.00, distanceZeroDet-0.5}, {"" ,-90.,90.,0.0}));

    // Fi7 detector
    Double_t fi7_8Distance = 38.75;
    Double_t fi7_8DistanceMagnetDetectors = 433.6;

    Double_t fi7X;
    Double_t fi7Z;
    fi7X = -(TMath::Sin(TMath::DegToRad()*18.0))*fi7_8DistanceMagnetDetectors                       +  TMath::Cos(TMath::DegToRad()*18.0)*fi7_8Distance;
    fi7Z =  (TMath::Cos(TMath::DegToRad()*18.0))*fi7_8DistanceMagnetDetectors + distanceZeroMagnet  +  TMath::Sin(TMath::DegToRad()*18.0)*fi7_8Distance;
    run->AddModule(new R3BFi7("fi7_16O.geo.root",{fi7X, 0.0,fi7Z}, {"" ,90.0,90.0-18.0,0.0}));

    // Fi8 detector
    Double_t fi8X;
    Double_t fi8Z;
    fi8X = -(TMath::Sin(TMath::DegToRad()*18.0))*fi7_8DistanceMagnetDetectors                       -  TMath::Cos(TMath::DegToRad()*18.0)*fi7_8Distance;
    fi8Z =  (TMath::Cos(TMath::DegToRad()*18.0))*fi7_8DistanceMagnetDetectors + distanceZeroMagnet  -  TMath::Sin(TMath::DegToRad()*18.0)*fi7_8Distance;
    run->AddModule(new R3BFi8("fi8_16O.geo.root",{fi8X, 0.0,fi8Z-0.5 }, {"" ,90.0,90.0-18.0,0.0}));

    // Fi10 detector
    Double_t fi10_11Distance = 1026.88;
    Double_t fi10_11DistanceMagnetDetectors = 333.6;
    Double_t fi10_11AbsoluteOffset = 0.48;

    Double_t fi10X;
    Double_t fi10Z;
    fi10X = -(TMath::Sin(TMath::DegToRad()*18.0))*fi10_11DistanceMagnetDetectors                       +  TMath::Cos(TMath::DegToRad()*18.0)*(fi10_11Distance)
    +  TMath::Cos(TMath::DegToRad()*18.0)*(fi10_11AbsoluteOffset) ;
    fi10Z =  (TMath::Cos(TMath::DegToRad()*18.0))*fi10_11DistanceMagnetDetectors + distanceZeroMagnet  +  TMath::Sin(TMath::DegToRad()*18.0)*(fi10_11Distance)
    +  TMath::Sin(TMath::DegToRad()*18.0)*(fi10_11AbsoluteOffset) ;    
    run->AddModule(new R3BFi10("fi10_16O.geo.root", {fi10X, 0.0,fi10Z}, {"" ,90.0,90.0-18.0,0.0}));

    // Fi11 detector

    Double_t fi11X;
    Double_t fi11Z;
    fi11X = -(TMath::Sin(TMath::DegToRad()*18.0))*fi10_11DistanceMagnetDetectors                       -  TMath::Cos(TMath::DegToRad()*18.0)*(fi10_11Distance)
    +  TMath::Cos(TMath::DegToRad()*18.0)*(fi10_11AbsoluteOffset);
    fi11Z =  (TMath::Cos(TMath::DegToRad()*18.0))*fi10_11DistanceMagnetDetectors + distanceZeroMagnet  -  TMath::Sin(TMath::DegToRad()*18.0)*(fi10_11Distance)
    +  TMath::Sin(TMath::DegToRad()*18.0)*(fi10_11AbsoluteOffset) ; 
    run->AddModule(new R3BFi11("fi11_16O.geo.root", {fi11X, 0.0, fi11Z-0.5 }, {"" ,90.0,90.0-18.0,0.0}));
    
    // CALIFA
    R3BCalifa* califa = new R3BCalifa("califa_10_v8.11.geo.root");
    califa->SelectGeometryVersion(10);
    // Selecting the Non-uniformity of the crystals (1 means +-1% max deviation)
    califa->SetNonUniformity(1.0);

    // dTof
    Double_t dTof_DistanceMagnetDetectors = 448.6;
    Double_t dTof_offset = 0.0;
    Double_t dTofX;
    Double_t dTofZ;
    dTofX = -(TMath::Sin(TMath::DegToRad()*18.0))*dTof_DistanceMagnetDetectors                      -  TMath::Cos(TMath::DegToRad()*18.0)*dTof_offset;
    dTofZ =  (TMath::Cos(TMath::DegToRad()*18.0))*dTof_DistanceMagnetDetectors + distanceZeroMagnet -  TMath::Sin(TMath::DegToRad()*18.0)*dTof_offset;
    
    run->AddModule(new R3BdTof("dtof_16O.geo.root", { dTofX, 0., dTofZ}, { "", -90., +18.0, 90. }));

    // MFI
    //run->AddModule(new R3BMfi("mfi_v17a.geo.root", { -63.82, 0., 520.25 }, { "", 90., +13.5, 90. })); // s412

    // NeuLAND
    // run->AddModule(new R3BNeuland("neuland_test.geo.root", { 0., 0., 1400. + 12 * 5. }));

    // -----   Create R3B  magnetic field ----------------------------------------
    // NB: <D.B>
    // If the Global Position of the Magnet is changed
    // the Field Map has to be transformed accordingly
    R3BGladFieldMap* magField = new R3BGladFieldMap("R3BGladMap");
    magField->SetScale(fieldScale);

    if (magnet == kTRUE)
    {
        run->SetField(magField);
    }
    else
    {
        run->SetField(NULL);
    }

    // -----   Create PrimaryGenerator   --------------------------------------
    // 1 - Create the Main API class for the Generator
    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();

    if (generator.CompareTo("box") == 0)
    {
        // FairIonGenerator* boxGen = new FairIonGenerator(50, 128, 50, 1, 0., 0., 1.4, 0., 0., 0.);
        FairIonGenerator* boxGen = new FairIonGenerator(8, 16, 8, 1, 0., 0., 1.08692, 0, 0., -300.);
        primGen->AddGenerator(boxGen);
    }

    if (generator.CompareTo("ascii") == 0)
    {
        R3BAsciiGenerator* gen = new R3BAsciiGenerator((dir + "/input/" + inputFile).Data());
        primGen->AddGenerator(gen);
    }

    run->SetGenerator(primGen);

    run->SetStoreTraj(storeTrajectories);

    FairLogger::GetLogger()->SetLogVerbosityLevel("LOW");
    FairLogger::GetLogger()->SetLogScreenLevel("ERROR");

    // -----   Initialize simulation run   ------------------------------------
    run->Init();
    TVirtualMC::GetMC()->SetRandom(new TRandom3(randomSeed));

    // ------  Increase nb of step for CALO
    Int_t nSteps = -15000;
    TVirtualMC::GetMC()->SetMaxNStep(nSteps);

    // -----   Runtime database   ---------------------------------------------
    R3BFieldPar* fieldPar = (R3BFieldPar*)rtdb->getContainer("R3BFieldPar");
    if (NULL != magField)
    {
        fieldPar->SetParameters(magField);
        fieldPar->setChanged();
    }
    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
    parOut->open(parFile.Data());
    rtdb->setOutput(parOut);
    rtdb->saveOutput();
    rtdb->print();

    // -----   Start run   ----------------------------------------------------
    if (nEvents > 0)
    {
        run->Run(nEvents);
    }

    // -----   Finish   -------------------------------------------------------
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    cout << endl << endl;
    cout << "Macro finished succesfully." << endl;
    cout << "Output file is " << outFile << endl;
    cout << "Parameter file is " << parFile << endl;
    cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << endl << endl;

    cout << " Test passed" << endl;
    cout << " All ok " << endl;
  cout << dir  << endl;
    // Snap a picture of the geometry
    // If this crashes, set "OpenGL.SavePicturesViaFBO: no" in your .rootrc
    /*gStyle->SetCanvasPreferGL(kTRUE);
    gGeoManager->GetTopVolume()->Draw("ogl");
    TGLViewer* v = (TGLViewer*)gPad->GetViewer3D();
    v->SetStyle(TGLRnrCtx::kOutline);
    v->RequestDraw();
    v->SavePicture("run_sim-side.png");
    v->SetPerspectiveCamera(TGLViewer::kCameraPerspXOZ, 25., 0, 0, -90. * TMath::DegToRad(), 0. * TMath::DegToRad());
    v->SavePicture("run_sim-top.png");*/
}
