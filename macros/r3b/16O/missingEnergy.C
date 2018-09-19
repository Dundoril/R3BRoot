{
#define SQR(x) ((x)*(x))

      Double_t px=SQR(MFIPoint.fPx[0] + MFIPoint.fPx[1])*1000000.;
      Double_t py=SQR(MFIPoint.fPy[0] + MFIPoint.fPy[1])*1000000.;
      Double_t pz=SQR(MFIPoint.fPz[0] + MFIPoint.fPz[1])*1000000.;
      Double_t p2=px+py+pz; // MeV^2/c^2

      Double_t C_beta=MFIPoint.fLength[1]/MFIPoint[1].fTime/30.;
      Double_t alpha_beta=MFIPoint.fLength[0]/MFIPoint[0].fTime/30.;
      Double_t MASS_ALPHA_MEV_C2=3727.409;
      Double_t MASS_12C_MEV_C2=11174.950;
      Double_t MASS_16O_MEV_C2=14895.196;
      
      
      Double_t E_f =1.0/sqrt(1-C_beta*C_beta) * MASS_12C_MEV_C2; // *c
      Double_t E_p1=1.0/sqrt(1-alpha_beta*alpha_beta) * MASS_ALPHA_MEV_C2; // *c
      Double_t E2=(E_f+E_p1)*(E_f+E_p1); // MeV^2/c^2

      Double_t E_rel=sqrt(E2-p2)-MASS_16O_MEV_C2; // *c2

      evt->Draw("E_rel","","", 100, 0);
}
