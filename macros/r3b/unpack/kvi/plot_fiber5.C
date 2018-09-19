{
TCanvas *c5 = new TCanvas("c5","fiber5 ",0,0,1250,950);
c5->Clear();
c5->Divide(4,4);
c5->cd(1);
fiber5_channels->Draw();
c5->cd(2);
fiber5_number->Draw();
c5->cd(3);
fiber5_xpos->Draw();
c5->cd(4);
fiber5_mult->Draw();
c5->cd(5);
fiber5_multihit->Draw("colz");
c5->cd(6);
fiber5_multihit_s->Draw("colz");
c5->cd(7);
fiber5_ToT->Draw("colz");
c5->cd(8);
fiber5_ToT_s->Draw("colz");
c5->cd(9);
fiber5_ToF->Draw();
c5->cd(10);
fiber5_ToT_vsTime_s0->Draw("colz");
c5->cd(11);
fiber5_FibervsTime->Draw("colz");
c5->cd(12);
fiber5_ToTvsTime_m->Draw("colz");
c5->cd(13);
Fiber5_vs_Fiber4->Draw("colz");


}
