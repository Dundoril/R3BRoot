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


/*
.L fit_exp.C
fit_exp1(Q_vs_ToF_Plane_5_Bar_2,14.5,20)
*/

void fit_exp1(TH2 *histo,Double_t min,Double_t max){
  TCanvas *cfit_exp=new TCanvas("cfit_exp","fit exponential",0,0,800,800); 
  gStyle->SetPalette(1);
  
  histo->GetXaxis()->SetRangeUser(-0.6,0.6);
  histo->GetYaxis()->SetRangeUser(14.5,20.);
  cfit_exp->Clear();
  cfit_exp->Divide(1,2);
  cfit_exp->cd(1);
  histo->Draw("colz");
  cfit_exp->cd(2);
  TProfile *prof = histo->ProfileY();
  prof->Draw("");
/* Ebene 5, Bar 2*/  
  TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x", 14.5, 20.);
  f1->SetParameters(42.256,-7.957,0.50574,-1.0766e-2);    
  f1->SetLineColor(2); 
  prof->Fit("f1","","",min,max); 
  TF1 *fres = new TF1("fres","42.256-7.957*x+0.50574*x*x-1.0766e-2*x*x*x", 14.5, 20);
  fres->SetLineColor(3);
  fres->Draw("same");

/* Ebene 5, Bar 1: 
  TF1 *fres = new TF1("fres","-7.529+1.085*x-3.694e-2*x*x", 14.5, 20);
  fres->SetLineColor(3);
  fres->Draw("same");
*/
/*  
  TF1 *f1 = new TF1("f1","[0]*x*exp(-(x-[1])**2/[2])-[3]*x*exp(-(x-[4])/[5])", 14.5, 20);
  f1->SetParameters(-0.2,24.,14.,-0.1,13.,2.6);   
   f1->SetLineColor(2); 
  prof->Fit("f1","","",min,max);
*/
/* 
  TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x", 10, 20);
  f1->SetParameters(20,-1,0.1,-0.01,0.001);
   f1->SetLineColor(2); 
  prof->Fit("f1","","",min,max);
*/
/*
  TF1 *f1 = new TF1("f1","[0]*exp(-[1]*(x-[2])**2)+[3]*exp(-[4]*(x-[5])**2)", 10, 20);
  f1->SetParameters(1,0.1,15,0.5,0.1,17);
   f1->SetLineColor(2); 
  prof->Fit("f1","","",min,max);
  */
  }



void fit_exp2(TH2 *histo, Int_t plane, Int_t bar,Double_t min,Double_t max, Int_t save){
  Double_t y[1000], x[1000], para[4]; 
  Int_t n=0;
  char filename1[100];
  TGraph *gr=new TGraph();
  TCanvas *cfit_exp=new TCanvas("cfit_exp","fit exponential",0,0,800,800); 
  gStyle->SetPalette(1);

  cfit_exp->Clear();
  cfit_exp->Divide(1,2);
  cfit_exp->cd(1);
  histo->Draw("colz");
  cfit_exp->cd(2);
  TH1D * histo_py = histo->ProjectionY();
 
   
  for(Int_t i=1; i<histo->GetNbinsX(); i++){
      histo_py = histo->ProjectionY("",i,i,"");
      histo_py->Draw();
      x[i-1]=histo->GetXaxis()->GetBinCenter(i);      
      Int_t binmax = histo_py->GetMaximumBin();
      y[i-1] = histo_py->GetXaxis()->GetBinCenter(binmax);
//      LOG(WARNING)<<"i: "<<i<<" x: "<<x[i-1]<<" y: "<<y[i-1]<<" binmax: "<<binmax<<FairLogger::endl;
      n++;      
  }

  gr=new TGraph(n,x,y);
  gr->Draw("A*");

  TF1 *f1 = new TF1("f1", "[0]*(exp(-[1]*(x+50))+exp(-[2]*(x+50)))+[3]", -40, 40 );
  f1->SetParameters(110,0.009,0.1,40);
  f1->SetLineColor(2); 
  gr->Fit("f1","","",min,max);
  for(Int_t j=0;j<=3;j++){   
      para[j] = f1->GetParameter(j); 
//      cout<<"Parameter: "<<para[j]<<endl;
  }
  
  if(save){
   sprintf(filename1,"para_paddles.dat"); 
   ofstream a_file ( filename1 , std::ios_base::app | std::ios_base::out);
    for(Int_t j=0;j<=3;j++){   
      para[j] = f1->GetParameter(j); 
      cout<<"Parameter: "<<para[j]<<endl;
      a_file<< plane <<"  " << bar<<"  "<< j <<"  "<< para[j] << "\n";
     }
   a_file.close();	 
}

  }
 
