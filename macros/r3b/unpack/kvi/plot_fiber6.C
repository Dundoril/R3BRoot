{
TCanvas *c6 = new TCanvas("c6","fiber6 ",0,0,1250,950);
c6->Clear();
c6->Divide(4,4);
c6->cd(1);
fiber6_channels->Draw();
c6->cd(2);
fiber6_number->Draw();
c6->cd(3);
fiber6_xpos->Draw();
c6->cd(4);
fiber6_mult->Draw();
c6->cd(5);
fiber6_multihit->Draw("colz");
c6->cd(6);
fiber6_multihit_s->Draw("colz");
c6->cd(7);
fiber6_ToT->Draw("colz");
c6->cd(8);
fiber6_ToT_s->Draw("colz");
c6->cd(9);
fiber6_ToF->Draw();
c6->cd(10);
fiber6_ToT_vsTime_s0->Draw("colz");
c6->cd(11);
fiber6_FibervsTime->Draw("colz");
c6->cd(12);
Fiber1_vs_Fiber4->Draw("colz");
c6->cd(13);
Fiber5_vs_Fiber4->Draw("colz");


}
