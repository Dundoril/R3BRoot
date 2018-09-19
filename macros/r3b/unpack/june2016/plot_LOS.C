{

/*
 root -l Dateiname.root

 und dann dein macro ausführen:

 .x macro.C

 */
 
 
LOS_X_vs_Y_MCFD->SetXTitle("x from MCFD (cm)");
LOS_X_vs_Y_MCFD->SetYTitle("y from MCFD (cm)");
LOS_X_vs_Y_MCFD->SetTitle("Position from MCFD");
LOS_X_vs_Y_MCFD->GetXaxis()->SetRangeUser(-100.,100.);
LOS_X_vs_Y_MCFD->GetYaxis()->SetRangeUser(-100.,100.);
LOS_X_vs_Y_MCFD->SetMinimum(1.);
LOS_X_vs_Y_MCFD->SetMaximum(10000.);
LOS_X_vs_Y_MCFD->SetLabelSize(0.05,"X");
LOS_X_vs_Y_MCFD->SetLabelSize(0.05,"Y");
LOS_X_vs_Y_MCFD->GetXaxis()->SetTitleSize(0.05);
LOS_X_vs_Y_MCFD->GetYaxis()->SetTitleSize(0.05); 

LOS_Time_Resolution_MCFD->SetXTitle("(Tl+Tr)/2-(To+Tu)/2 from MCFD (ns)");
LOS_Time_Resolution_MCFD->SetYTitle("Counts");
LOS_Time_Resolution_MCFD->SetTitle("LOS time resolution MCFD");
LOS_Time_Resolution_MCFD->GetXaxis()->SetRangeUser(-2000,2000);    //(-1.3,-0.7);
LOS_Time_Resolution_MCFD->SetLabelSize(0.05,"X");
LOS_Time_Resolution_MCFD->SetLabelSize(0.05,"Y");
LOS_Time_Resolution_MCFD->GetXaxis()->SetTitleSize(0.05);
LOS_Time_Resolution_MCFD->GetYaxis()->SetTitleSize(0.05);
LOS_Time_Resolution_MCFD->GetXaxis()->SetTitleSize(0.05);
LOS_Time_Resolution_MCFD->GetYaxis()->SetTitleSize(0.05);

LOS_Time_Resolution_PADI->SetXTitle("(Tl+Tr)/2-(To+Tu)/2 from PADI (ns)");
LOS_Time_Resolution_PADI->SetYTitle("Counts");
LOS_Time_Resolution_PADI->SetTitle("LOS time resolution PADI");
LOS_Time_Resolution_PADI->GetXaxis()->SetRangeUser(-1.9,-1.3);
LOS_Time_Resolution_PADI->SetLabelSize(0.05,"X");
LOS_Time_Resolution_PADI->SetLabelSize(0.05,"Y");
LOS_Time_Resolution_PADI->GetXaxis()->SetTitleSize(0.05);
LOS_Time_Resolution_PADI->GetYaxis()->SetTitleSize(0.05);

LOS_Time_Resolution_PADI_corr->SetXTitle("(Tl+Tr)/2-(To+Tu)/2 from PADI (ns)");
LOS_Time_Resolution_PADI_corr->SetYTitle("Counts");
LOS_Time_Resolution_PADI_corr->SetTitle("LOS time resolution PADI corrected");
LOS_Time_Resolution_PADI_corr->GetXaxis()->SetRangeUser(-0.3,0.3);
LOS_Time_Resolution_PADI_corr->SetLabelSize(0.05,"X");
LOS_Time_Resolution_PADI_corr->SetLabelSize(0.05,"Y");
LOS_Time_Resolution_PADI_corr->GetXaxis()->SetTitleSize(0.05);
LOS_Time_Resolution_PADI_corr->GetYaxis()->SetTitleSize(0.05);

LOS_TimeP_vs_TimeM->SetXTitle("Time from PADI (ns)");
LOS_TimeP_vs_TimeM->SetYTitle("Time from MCFD (ns)");
LOS_TimeP_vs_TimeM->SetTitle("LOS time resolution");
LOS_TimeP_vs_TimeM->GetXaxis()->SetRangeUser(-1.9,-1.3);
LOS_TimeP_vs_TimeM->GetYaxis()->SetRangeUser(-1.3,-0.7);
LOS_TimeP_vs_TimeM->SetMinimum(1.);
LOS_TimeP_vs_TimeM->SetMaximum(300.);
LOS_TimeP_vs_TimeM->SetLabelSize(0.05,"X");
LOS_TimeP_vs_TimeM->SetLabelSize(0.05,"Y");
LOS_TimeP_vs_TimeM->GetXaxis()->SetTitleSize(0.05);
LOS_TimeP_vs_TimeM->GetYaxis()->SetTitleSize(0.05);

LOS_TimeP_vs_TimeM_corr->SetXTitle("Time from PADI (ns)");
LOS_TimeP_vs_TimeM_corr->SetYTitle("Time from MCFD (ns)");
LOS_TimeP_vs_TimeM_corr->SetTitle("LOS time resolution corrected");
LOS_TimeP_vs_TimeM_corr->GetXaxis()->SetRangeUser(-0.3,0.3);
LOS_TimeP_vs_TimeM_corr->GetYaxis()->SetRangeUser(-1.3,-0.7);
LOS_TimeP_vs_TimeM_corr->SetMinimum(1.);
LOS_TimeP_vs_TimeM_corr->SetMaximum(300.);
LOS_TimeP_vs_TimeM_corr->SetLabelSize(0.05,"X");
LOS_TimeP_vs_TimeM_corr->SetLabelSize(0.05,"Y");
LOS_TimeP_vs_TimeM_corr->GetXaxis()->SetTitleSize(0.05);
LOS_TimeP_vs_TimeM_corr->GetYaxis()->SetTitleSize(0.05);


LOS_Charge_vs_PADI_Time->SetYTitle("LOS charge (arb. u.)");
LOS_Charge_vs_PADI_Time->SetXTitle("(Tl+Tr)/2-(To+Tu)/2 from PADI (ns)");
LOS_Charge_vs_PADI_Time->SetTitle("PADI time vs charge");
LOS_Charge_vs_PADI_Time->GetXaxis()->SetRangeUser(-1.9,-1.3);
LOS_Charge_vs_PADI_Time->GetYaxis()->SetRangeUser(14.,20.);
LOS_Charge_vs_PADI_Time->SetMinimum(1.);
LOS_Charge_vs_PADI_Time->SetMaximum(10000.);
LOS_Charge_vs_PADI_Time->SetLabelSize(0.05,"X");
LOS_Charge_vs_PADI_Time->SetLabelSize(0.05,"Y");
LOS_Charge_vs_PADI_Time->GetXaxis()->SetTitleSize(0.05);
LOS_Charge_vs_PADI_Time->GetYaxis()->SetTitleSize(0.05);

LOS_Charge_vs_PADI_Time_corr->SetYTitle("LOS charge (arb. u.)");
LOS_Charge_vs_PADI_Time_corr->SetXTitle("(Tl+Tr)/2-(To+Tu)/2 from PADI (ns)");
LOS_Charge_vs_PADI_Time_corr->SetTitle("PADI time vs charge corrected");
LOS_Charge_vs_PADI_Time_corr->GetXaxis()->SetRangeUser(-0.3,0.3);
LOS_Charge_vs_PADI_Time_corr->GetYaxis()->SetRangeUser(14.,20.);
LOS_Charge_vs_PADI_Time_corr->SetMinimum(1.);
LOS_Charge_vs_PADI_Time_corr->SetMaximum(10000.);
LOS_Charge_vs_PADI_Time_corr->SetLabelSize(0.05,"X");
LOS_Charge_vs_PADI_Time_corr->SetLabelSize(0.05,"Y");
LOS_Charge_vs_PADI_Time_corr->GetXaxis()->SetTitleSize(0.05);
LOS_Charge_vs_PADI_Time_corr->GetYaxis()->SetTitleSize(0.05);

LOS_Charge_vs_MCFD_Time->SetYTitle("LOS charge (arb. u.)");
LOS_Charge_vs_MCFD_Time->SetXTitle("(Tl+Tr)/2-(To+Tu)/2 from MCFD (ns)");
LOS_Charge_vs_MCFD_Time->SetTitle("MCFD time vs charge");
LOS_Charge_vs_MCFD_Time->GetXaxis()->SetRangeUser(-1.3,-0.7);
LOS_Charge_vs_MCFD_Time->GetYaxis()->SetRangeUser(14.,20.);
LOS_Charge_vs_MCFD_Time->SetMinimum(1.);
LOS_Charge_vs_MCFD_Time->SetMaximum(10000.);
LOS_Charge_vs_MCFD_Time->SetLabelSize(0.05,"X");
LOS_Charge_vs_MCFD_Time->SetLabelSize(0.05,"Y");
LOS_Charge_vs_MCFD_Time->GetXaxis()->SetTitleSize(0.05);
LOS_Charge_vs_MCFD_Time->GetYaxis()->SetTitleSize(0.05);

LOS_ToF_vs_Charge->SetXTitle("T_PADI-T_MCFD (ns)");
LOS_ToF_vs_Charge->SetYTitle("LOS charge (arb. u.)");
LOS_ToF_vs_Charge->SetTitle("ToF versus charge");
LOS_ToF_vs_Charge->GetXaxis()->SetRangeUser(-0.6,0.6);
LOS_ToF_vs_Charge->GetYaxis()->SetRangeUser(14.,20.);
LOS_ToF_vs_Charge->SetMinimum(1.);
LOS_ToF_vs_Charge->SetMaximum(10000.);
LOS_ToF_vs_Charge->SetLabelSize(0.05,"X");
LOS_ToF_vs_Charge->SetLabelSize(0.05,"Y");
LOS_ToF_vs_Charge->GetXaxis()->SetTitleSize(0.05);
LOS_ToF_vs_Charge->GetYaxis()->SetTitleSize(0.05);

LOS_ToF_vs_Charge_corr->SetXTitle("T_PADI-T_MCFD (ns)");
LOS_ToF_vs_Charge_corr->SetYTitle("LOS charge (arb. u.)");
LOS_ToF_vs_Charge_corr->SetTitle("ToF versus charge corrected");
LOS_ToF_vs_Charge_corr->GetXaxis()->SetRangeUser(-0.6,0.6);
LOS_ToF_vs_Charge_corr->GetYaxis()->SetRangeUser(14.,20.);
LOS_ToF_vs_Charge_corr->SetMinimum(1.);
LOS_ToF_vs_Charge_corr->SetMaximum(10000.);
LOS_ToF_vs_Charge_corr->SetLabelSize(0.05,"X");
LOS_ToF_vs_Charge_corr->SetLabelSize(0.05,"Y");
LOS_ToF_vs_Charge_corr->GetXaxis()->SetTitleSize(0.05);
LOS_ToF_vs_Charge_corr->GetYaxis()->SetTitleSize(0.05);

LOS_X_vs_Y_PADI->SetXTitle("x from PADI (cm)");
LOS_X_vs_Y_PADI->SetYTitle("y from PADI (cm)");
LOS_X_vs_Y_PADI->SetTitle("Position from PADI");
LOS_X_vs_Y_PADI->GetXaxis()->SetRangeUser(-1.,1.);
LOS_X_vs_Y_PADI->GetYaxis()->SetRangeUser(-1.,1.);
LOS_X_vs_Y_PADI->SetMinimum(1.);
LOS_X_vs_Y_PADI->SetMaximum(10000.);
LOS_X_vs_Y_PADI->SetLabelSize(0.05,"X");
LOS_X_vs_Y_PADI->SetLabelSize(0.05,"Y");
LOS_X_vs_Y_PADI->GetXaxis()->SetTitleSize(0.05);
LOS_X_vs_Y_PADI->GetYaxis()->SetTitleSize(0.05);




/* One can also use:
 * histo->SetAxisRange(a,b,"X");
 * histo->SetAxisRange(c,d,"Y");
 */

TCanvas *c4 = new TCanvas("c2","LOS",0,0,600,900);
c4->Clear();
c4->Divide(1,2);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   /* X position */
gStyle->SetStatY(0.99);   /* Y position */
gStyle->SetStatW(0.25);  /* Width of the box */
gStyle->SetStatH(0.3);  /* hight of the bos */
c4->cd(1);
LOS_Time_Resolution_MCFD->Draw();
c4->cd(2); gPad->SetLogz();
LOS_X_vs_Y_MCFD->Draw("colz");

/*
TCanvas *c2 = new TCanvas("c2","LOS",0,0,900,600);
c2->Clear();
c2->Divide(3,3);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   / * X position * /
gStyle->SetStatY(0.99);   / * Y position * /
gStyle->SetStatW(0.25);  / * Width of the box * /
gStyle->SetStatH(0.3);  / * hight of the bos * /
c2->cd(1);
LOS_Time_Resolution_PADI->Draw();
c2->cd(2);
LOS_Time_Resolution_MCFD->Draw();
c2->cd(3); gPad->SetLogz();
LOS_TimeP_vs_TimeM->Draw("colz");
c2->cd(4); gPad->SetLogz();
LOS_Charge_vs_PADI_Time->Draw("colz");
c2->cd(5); gPad->SetLogz();
LOS_Charge_vs_MCFD_Time->Draw("colz");
c2->cd(6); gPad->SetLogz();
LOS_ToF_vs_Charge->Draw("colz");
c2->cd(7); gPad->SetLogz();
LOS_X_vs_Y_PADI->Draw("colz");
c2->cd(8); gPad->SetLogz();
LOS_X_vs_Y_MCFD->Draw("colz");

TCanvas *c3 = new TCanvas("c3","LOS",0,0,900,900);
c3->Clear();
c3->Divide(2,4);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   /  X position * /
gStyle->SetStatY(0.99);   / * Y position * /
gStyle->SetStatW(0.25);  / * Width of the box * /
gStyle->SetStatH(0.3);  / * hight of the bos * /
c3->cd(1);
LOS_Time_Resolution_PADI->Draw();
c3->cd(2);
LOS_Time_Resolution_PADI_corr->Draw();
c3->cd(3); gPad->SetLogz();
LOS_TimeP_vs_TimeM->Draw("colz");
c3->cd(4); gPad->SetLogz();
LOS_TimeP_vs_TimeM_corr->Draw("colz");
c3->cd(5); gPad->SetLogz();
LOS_Charge_vs_PADI_Time->Draw("colz");
c3->cd(6); gPad->SetLogz();
LOS_Charge_vs_PADI_Time_corr->Draw("colz");
c3->cd(7); gPad->SetLogz();
LOS_ToF_vs_Charge->Draw("colz");
c3->cd(8); gPad->SetLogz();
LOS_ToF_vs_Charge_corr->Draw("colz"); 
*/
}
