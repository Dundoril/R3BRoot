#include <iomanip>
#include <iostream>
#include "TGeoManager.h"
#include "TMath.h"

// Create Matrix Unity
TGeoRotation *fGlobalRot = new TGeoRotation();

// Create a null translation
TGeoTranslation *fGlobalTrans = new TGeoTranslation();
TGeoRotation *fRefRot = NULL;

TGeoManager*  gGeoMan = NULL;

TGeoCombiTrans* GetGlobalPosition(TGeoCombiTrans *fRef);

void create_dtof_geo(const char* geoTag)
{


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
  TString geoFileName = geoPath + "/geometry/dtof_";
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
  
  FairGeoMedium* mTof      = geoMedia->getMedium("plasticFormTOF");
  if ( ! mTof ) Fatal("Main", "FairMedium plasticFormTOF not found");
  geoBuild->createMedium(mTof);
  TGeoMedium* pMed34 
  = gGeoMan->GetMedium("plasticFormTOF");
  if ( ! pMed34 ) Fatal("Main", "Medium plasticFormTOF not found");
  // --------------------------------------------------------------------------



  // --------------   Create geometry and top volume  -------------------------
  gGeoMan = (TGeoManager*)gROOT->FindObject("FAIRGeom");
  gGeoMan->SetName("dTOFgeom");
  TGeoVolume* top = new TGeoVolumeAssembly("TOP");
  gGeoMan->SetTopVolume(top);
  // --------------------------------------------------------------------------

  
  //LABPOS(FTF,-155.824045,0.523976,761.870346)
  Float_t x = -155.824045;//dE tracker, correction due to wrong angle
  Float_t y = 0.523976;
  Float_t z = 761.870346;
  
  // Rotation: 16.7 around y-axis

  
  TGeoRotation *pMatrix1 = new TGeoRotation();
  pMatrix1->RotateY(-18.0);
  TGeoCombiTrans* pMatrix2 = new TGeoCombiTrans("", x,y,z,pMatrix1);

  

  
  // Shape: World type: TGeoBBox
  TGeoVolume* pWorld = gGeoManager->GetTopVolume(); // Top volume
  pWorld->SetVisLeaves(kTRUE);
  TGeoVolumeAssembly* pW = new TGeoVolumeAssembly("dTOF"); // keeping volume 
  pWorld->AddNode(pW, 0, pMatrix2);
  
  
  // SHAPES, VOLUMES AND GEOMETRICAL HIERARCHY
  // Shape: mTOFBox type: TGeoBBox
  // Float_t detector_width = 13.500000;
  // Float_t detector_height = 50.000000;
  // Float_t detector_thickness = 0.500000; 
 

  Float_t detector_height = 80.000000;


  Float_t paddle_width = 2.70000;
  Float_t paddle_thickness = 0.50000; 
  Float_t air_gap_paddles = 0.04;
  Float_t air_gap_layer = 0.45;


  
  // define number of layers and paddles with sizes of the detector
  Int_t number_layers = 2; // number of layers
  Int_t number_paddles = 44; // number of paddles per layer

  Float_t  detector_width =number_paddles*paddle_width+(number_paddles-1)*air_gap_paddles;
  Float_t detector_thickness =(number_layers-1)*air_gap_layer+number_layers*paddle_thickness;
 
  /*// directly set number of layers and paddles
  Int_t number_layers = 2;
  Int_t number_paddles = 10; */
  
  TGeoShape *TOFd_Paddle_Box = new TGeoBBox("TOFd_Paddle_Box", paddle_width/2,detector_height/2,paddle_thickness/2);
  // Volume
  //TGeoVolume* TOFd_Paddle_Log = new TGeoVolume("mTOFLog",TOFd_Paddle_Box, pMed34); //TOFd_Paddle_Log
  //TOFd_Paddle_Log->SetVisLeaves(kTRUE);
  
  cout << "number paddles" << number_paddles << endl;
  cout << "number layers" << number_layers << endl;
  
  // build layers of paddles 
  int layer_label;
  int paddle_index = 0 ;
  
  for(int layer_number = 0; layer_number < number_layers; layer_number++){
	  
	  if((layer_number%2)==0){layer_label=0;} else {layer_label=1;}
	  
	  for(int paddle_number = 0; paddle_number < number_paddles; paddle_number++){
	  
    //make hole in the middle
    cout << layer_number << " | " << paddle_number << endl;
   if (layer_number == 1 && (paddle_number == 21 || paddle_number == 20 || paddle_number == 22 )  ) continue;
  //  if (layer_number == 1) continue;
    if (layer_number == 0 && (paddle_number == 21 || paddle_number == 22 || paddle_number == 20 || paddle_number == 23)) continue;
    if (layer_number == 0) continue;
		  
		Float_t paddle_xposition = -detector_width/2 + paddle_width/2*(1+layer_label) + paddle_number*paddle_width+paddle_number*air_gap_paddles;
		Float_t paddle_zposition = -detector_thickness/2 +(layer_number)*paddle_thickness+layer_number*air_gap_layer;
		
    cout << "x: " << paddle_xposition << " z: " << paddle_zposition << endl;

		TGeoCombiTrans* pMatrix3 = new TGeoCombiTrans("", paddle_xposition,0,paddle_zposition,new TGeoRotation());
		
		TGeoVolume* TOFd_Paddle_Log = new TGeoVolume(Form("dTOFLog%d",paddle_index),TOFd_Paddle_Box, pMed34);
		
		if((paddle_index%2)==0){TOFd_Paddle_Log->SetLineColor(kBlue);}
		else {TOFd_Paddle_Log->SetLineColor(kRed);}
		
		
		pW->AddNode(TOFd_Paddle_Log, paddle_index, pMatrix3);
		cout << "paddle number" << paddle_index << endl ;
		paddle_index++;
	  }
  }
  
  
  
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
