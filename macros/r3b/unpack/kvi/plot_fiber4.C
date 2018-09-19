{
TCanvas *c4 = new TCanvas("c4","fiber4 ",0,0,1250,950);
c4->Clear();
c4->Divide(4,4);
c4->cd(1);
fiber4_channels->Draw();
c4->cd(2);
fiber4_number->Draw();
c4->cd(3);
fiber4_xpos->Draw();
c4->cd(4);
fiber4_mult->Draw();
c4->cd(5);
fiber4_multihit->Draw("colz");
c4->cd(6);
fiber4_multihit_s->Draw("colz");
c4->cd(7);
fiber4_ToT->Draw("colz");
c4->cd(8);
fiber4_ToT_s->Draw("colz");
c4->cd(9);
fiber4_ToF->Draw();
c4->cd(10);
fiber4_ToTvsTime_s->Draw("colz");
c4->cd(11);
fiber4_FibervsTime->Draw("colz");
c4->cd(12);
Fiber1_vs_Fiber4->Draw("colz");
c4->cd(13);
Fiber5_vs_Fiber4->Draw("colz");


}
