#include <cmath>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include        "TROOT.h"
#include        "TAttText.h"
#include        "TAxis.h"
#include        "TCanvas.h"
#include        "TChain.h"
#include        "TCut.h"
#include        "TF1.h"
#include        "TFile.h"
#include        "TGraph.h"
#include        "TGraphAsymmErrors.h"
#include        "TGraphErrors.h"
#include        "TH1.h"
#include        "TH2.h"
#include        "THistPainter.h"
#include        "TKey.h"
#include        "TLatex.h"
#include        "TLegend.h"
#include        "TMath.h"
#include        "TMatrixD.h"
#include        "TMinuit.h"
#include        "TMultiGraph.h"
#include        "TNtuple.h"
#include        "TPave.h"
#include        "TPaveText.h"
#include        "TPoint.h"
#include        "TRandom.h"
#include        "TRint.h"
#include        "TStyle.h"
#include        "TString.h"
#include        "TTree.h"
#include        "TH1F.h"
#include        "TH2F.h"
#include        "TSystem.h"
#include        "TProfile.h"



void fit_exp1(Int_t plane, Int_t bar, Int_t pm, TH2 *histo, Double_t xmin,Double_t xmax, Double_t ymin, Double_t ymax, Int_t save){
 
  Double_t y[10000], x[10000]; 
  Double_t para[4];
  Int_t n=0;
  char filename1[100];
  

//  TH1F *histo_py;		
  TCanvas *cfit_exp=new TCanvas("cfit_exp","fit exponential",0,0,800,800); 
  
  gStyle->SetPalette(1);

  cfit_exp->Clear();
  cfit_exp->Divide(1,2);
  cfit_exp->cd(1);
  TH2F *histo1=(TH2F*)histo->Clone();
  TH2F *histo2=(TH2F*)histo->Clone();
  histo1->GetYaxis()->UnZoom();
  histo1->Draw("colz");

  cfit_exp->cd(2);
  
  for(Int_t i=1; i<histo1->GetNbinsX(); i++){
      histo1->SetAxisRange(ymin,ymax,"Y");
      TH1F *histo_py = (TH1F*)histo1->ProjectionY("histo_py",i,i,"");
      histo_py->Draw();
      x[n]=histo1->GetXaxis()->GetBinCenter(i);      
      Int_t binmax = histo_py->GetMaximumBin();
      y[n] = histo_py->GetXaxis()->GetBinCenter(binmax);
//      cout<<"i: "<<i<<" x: "<<x[i]<<" y: "<<y[i]<<" binmax: "<<binmax<<endl;
      if(histo_py->GetMaximum()>10) n++;
      delete histo_py;
            
  }

  TGraph *gr1 = new TGraph(n,x,y);
  //gr1 = new TGraph(n,x,y);
  gr1->Draw("A*");   
 
  TF1 *f1 = new TF1("f1","[0]*(exp(-[1]*(x+50))+exp(-[2]*(x+50)))+[3]", -40, 40);
  f1->SetParameters(40,-0.009,-0.001,40);
  f1->SetLineColor(2); 
  gr1->Fit(f1,"W","",xmin,xmax);
  for(Int_t j=0;j<=3;j++){   
      para[j] = f1->GetParameter(j); 
      cout<<"Parameter: "<<para[j]<<endl;
  }


/*
  // fit a second time
  n=0;
  cfit_exp->cd(3);
  histo2->Draw("colz");
  cfit_exp->cd(4);

  for(Int_t i=1; i<histo2->GetNbinsX(); i++){
      Double_t pos= histo2->GetXaxis()->GetBinCenter(i);
      Double_t ymean= para[0]*(exp(-para[1]*(pos+50))+exp(-para[2]*(pos+50)))+para[3];
      histo2->SetAxisRange(ymean-20.,ymean+20.,"Y");
      histo2->Draw("colz");
      TH1F *histo_py = (TH1F*)histo2->ProjectionY("histo_py",i,i,"");
      histo_py->Draw();
      x[n]=histo2->GetXaxis()->GetBinCenter(i);      
      Int_t binmax = histo_py->GetMaximumBin();
      y[n] = histo_py->GetXaxis()->GetBinCenter(binmax);
//      cout<<"i: "<<i<<" x: "<<x[i]<<" y: "<<y[i]<<" binmax: "<<binmax<<endl;      
      if(histo_py->GetMaximum()>10) n++;
      delete histo_py;
      
  }

  gr2 = new TGraph(n,x,y);
  gr2->Draw("A*");


  TF1 *f2 = new TF1("f1","[0]*(exp(-[1]*(x+50))+exp(-[2]*(x+50)))+[3]", -40, 40);
  f2->SetParameters(para[0],para[1],para[2],para[3]);
  f2->SetLineColor(2); 
  gr2->Fit(f2,"W","",xmin,xmax);
  for(Int_t j=0;j<=3;j++){   
      para[j] = f2->GetParameter(j); 
      cout<<"Parameter: "<<para[j]<<endl;
  }
*/
  if(save){
     sprintf(filename1,"para_paddles_run137.dat"); 
     ofstream a_file ( filename1 , std::ios_base::app | std::ios_base::out);
     for(Int_t j=0;j<=3;j++){   
         cout<<"Saving Parameter: "<<para[j]<<endl;
         a_file<< plane <<"  " << bar<<"  "<<pm<< "  "<< j <<"  "<< para[j] << "\n";
     }
     a_file.close();	 
  }

}
