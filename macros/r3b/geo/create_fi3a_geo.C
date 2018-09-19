#include "TGeoManager.h"

TGeoManager* gGeoMan;

void create_fi3a_geo(const char* geoTag)
{

  //fGlobalTrans->SetTranslation(0.0,0.0,0.0);

  // -------   Load media from media file   -----------------------------------
  FairGeoLoader*    geoLoad = new FairGeoLoader("TGeo","FairGeoLoader");
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  TString geoPath = gSystem->Getenv("VMCWORKDIR");
  TString medFile = geoPath + "/geometry/media_r3b.geo";
  geoFace->setMediaFile(medFile);
  geoFace->readMedia();
  gGeoMan = gGeoManager;
  // --------------------------------------------------------------------------



  // -------   Geometry file name (output)   ----------------------------------
  TString geoFileName = geoPath + "/geometry/fi3a_";
  geoFileName = geoFileName + geoTag + ".geo.root";
  // --------------------------------------------------------------------------



  // -----------------   Get and create the required media    -----------------
  FairGeoMedia*   geoMedia = geoFace->getMedia();
  FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

  FairGeoMedium* mAir      = geoMedia->getMedium("Air");
  if ( ! mAir ) Fatal("Main", "FairMedium Air not found");
  geoBuild->createMedium(mAir);
  TGeoMedium* pMed2 = gGeoMan->GetMedium("Air");
  if ( ! pMed2 ) Fatal("Main", "Medium Air not found");

  FairGeoMedium* mVac      = geoMedia->getMedium("vacuum");
  if ( ! mVac ) Fatal("Main", "FairMedium vacuum not found");
  geoBuild->createMedium(mVac);
  TGeoMedium* pMed1 = gGeoMan->GetMedium("vacuum");
  if ( ! pMed1 ) Fatal("Main", "Medium vacuum not found");
  
  FairGeoMedium* mGfi      = geoMedia->getMedium("plasticForGFI");
  if ( ! mGfi ) Fatal("Main", "FairMedium plasticForGFI not found");
  geoBuild->createMedium(mGfi);
  TGeoMedium* pMed35 = gGeoMan->GetMedium("plasticForGFI");
  if ( ! pMed35 ) Fatal("Main", "Medium plasticForGFI not found");

  FairGeoMedium* mAl      = geoMedia->getMedium("aluminium");
  if ( ! mAl ) Fatal("Main", "FairMedium aluminium not found");
  geoBuild->createMedium(mAl);
  TGeoMedium* pMed21 = gGeoMan->GetMedium("aluminium");
  if ( ! pMed21 ) Fatal("Main", "Medium aluminium not found");
  // --------------------------------------------------------------------------



  // --------------   Create geometry and top volume  -------------------------
  gGeoMan = (TGeoManager*)gROOT->FindObject("FAIRGeom");
  gGeoMan->SetName("GFIgeom");
  TGeoVolume* top = new TGeoVolumeAssembly("TOP");
  gGeoMan->SetTopVolume(top);
  // --------------------------------------------------------------------------
  
  //LABPOS(GFI1,-73.274339,0.069976,513.649524)
  Float_t dx = -73.274339; //dE tracker, correction due to wrong angle
  Float_t dy = 0.069976;
  Float_t dz = 513.649524;
  
  TGeoRotation *pMatrix3 = new TGeoRotation();
  //pMatrix3->RotateY(-16.7);
  TGeoCombiTrans*
  pMatrix2 = new TGeoCombiTrans("", dx,dy,dz,pMatrix3);

  //LABPOS(GFI2,-147.135037,0.069976,729.680342)
  dx = -147.135037; //dE tracker, correction due to wrong angle
  dy = 0.069976;
  dz = 729.680342;

  TGeoRotation *pMatrix5 = new TGeoRotation();
  //pMatrix5->RotateY(-16.7);
  TGeoCombiTrans*
  pMatrix4 = new TGeoCombiTrans("", dx,dy,dz,pMatrix5);
  
  
  // World definition
  TGeoVolume* pWorld = gGeoManager->GetTopVolume();
  pWorld->SetVisLeaves(kTRUE);
  
  // SHAPES, VOLUMES AND GEOMETRICAL HIERARCHY 
  
  // Volume: GFILogWorld
  
  TGeoVolume*   pGFILogWorld = new TGeoVolumeAssembly("FI3ALogWorld");
  pGFILogWorld->SetVisLeaves(kTRUE);
  
  // Global positioning
  pWorld->AddNode(pGFILogWorld, 0, pMatrix2);

  
  Float_t detector_height = 10.000000 ;
  Float_t fiber_thickness = 0.020000 ; 
  Int_t fiber_nbr = 512;
  Float_t dead_layer = 0.9;
  Float_t air_layer = 0.1; // relative to fiber_thickness
  Float_t  detector_width = fiber_nbr*fiber_thickness*(1+air_layer);


  TGeoShape *pGFIBox = new TGeoBBox("GFIBox", detector_height/2, fiber_thickness/2 ,fiber_thickness/2);
  
  TGeoVolume* pGFILog = new TGeoVolume("FI3ALog",pGFIBox, pMed35);


  TGeoShape *pGFIBoxActive = new TGeoBBox("GFIBoxActive", detector_height/2 - 0.0001, (fiber_thickness * dead_layer)/2, (fiber_thickness * dead_layer)/2);

  TGeoVolume* pGFILogActive = new TGeoVolume("FI3A1Log",pGFIBoxActive,pMed35);

  TGeoRotation *pMatrixBox = new TGeoRotation();
  pMatrixBox->RotateY(0.0);

  // pGFILog -> AddNode(pGFILogActive, 0, new TGeoCombiTrans("",0,0,0, pMatrixBox));
  pGFILog -> AddNode(pGFILogActive, 0, new TGeoCombiTrans());
  
  pGFILogActive->SetLineColor(kGreen);
  pGFILogActive->SetVisLeaves(kTRUE);
  pGFILog->SetLineColor((Color_t) 4);
  pGFILog->SetVisLeaves(kTRUE);

  


  Int_t real_fiber_id = 0;
  
  for(int fiber_id = 0; fiber_id < fiber_nbr ; fiber_id++)
  {
	pGFILogWorld->AddNode(pGFILog, real_fiber_id++, 
		new TGeoCombiTrans("", 
			0,
			-(fiber_thickness) / 2,
			-detector_width / 2 - fiber_thickness/2 +(fiber_id + (fiber_id * air_layer)) * fiber_thickness , // sf: why + .5
			pMatrixBox
		)
	);
  }
  
  // Add the sensitive part
//  AddSensitiveVolume(pGFILog);
//  fNbOfSensitiveVol+=1;
  
  
  
  // ---------------   Finish   -----------------------------------------------
  gGeoMan->CloseGeometry();
  gGeoMan->CheckOverlaps(0.001);
  gGeoMan->PrintOverlaps();
  gGeoMan->Test();

  TFile* geoFile = new TFile(geoFileName, "RECREATE");
  top->Write();
  geoFile->Close();
  // --------------------------------------------------------------------------
}
