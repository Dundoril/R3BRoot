{
 

TCanvas *cPtof1 = new TCanvas("cPtof1","Ptof1",0,0,850,950);
cPtof1->Clear();
cPtof1->Divide(2,2);
cPtof1->cd(1);
Ptof_channels->Draw();
cPtof1->cd(2);
Ptof_channels_cut->Draw();
cPtof1->cd(3);
Ptof_test1->Draw();
cPtof1->cd(4);
Ptof_test2->Draw();

TCanvas *cPtof2 = new TCanvas("cPtof2","Ptof2",0,0,850,950);
cPtof2->Clear();
cPtof2->Divide(8,2);
cPtof2->cd(1);
ToT_Bar_1_PM_2->Draw();
cPtof2->cd(2);
ToT_Bar_2_PM_2->Draw();
cPtof2->cd(3);
ToT_Bar_3_PM_2->Draw();
cPtof2->cd(4);
ToT_Bar_4_PM_2->Draw();
cPtof2->cd(5);
ToT_Bar_5_PM_2->Draw();
cPtof2->cd(6);
ToT_Bar_6_PM_2->Draw();
cPtof2->cd(7);
ToT_Bar_7_PM_2->Draw();
cPtof2->cd(8);
ToT_Bar_8_PM_2->Draw();
cPtof2->cd(9); 
ToT_Bar_1_PM_1->Draw();
cPtof2->cd(10);
ToT_Bar_2_PM_1->Draw();
cPtof2->cd(11);
ToT_Bar_3_PM_1->Draw();
cPtof2->cd(12);
ToT_Bar_4_PM_1->Draw();
cPtof2->cd(13);
ToT_Bar_5_PM_1->Draw();
cPtof2->cd(14);
ToT_Bar_6_PM_1->Draw();
cPtof2->cd(15);
ToT_Bar_7_PM_1->Draw();
cPtof2->cd(16);
ToT_Bar_8_PM_1->Draw();
 


}
