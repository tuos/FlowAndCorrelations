void histEffVsPt(){
   Float_t bins[30] = {0,  0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0,  10000};
   TH1D *effVsPt = new TH1D("effVsPt","effVsPt",29,bins);   
   effVsPt->SetBinContent(1,0.5013475);
   effVsPt->SetBinContent(2,0.5413475);
   effVsPt->SetBinContent(3,0.6269975);
   effVsPt->SetBinContent(4,0.6778535);
   effVsPt->SetBinContent(5,0.7083387);
   effVsPt->SetBinContent(6,0.7275539);
   effVsPt->SetBinContent(7,0.7405305);
   effVsPt->SetBinContent(8,0.7496165);
   effVsPt->SetBinContent(9,0.7558057);
   effVsPt->SetBinContent(10,0.7598232);
   effVsPt->SetBinContent(11,0.7627781);
   effVsPt->SetBinContent(12,0.7661967);
   effVsPt->SetBinContent(13,0.7712464);
   effVsPt->SetBinContent(14,0.7931089);
   effVsPt->SetBinContent(15,0.8204638);
   effVsPt->SetBinContent(16,0.808872);
   effVsPt->SetBinContent(17,0.7798038);
   effVsPt->SetBinContent(18,0.748735);
   effVsPt->SetBinContent(19,0.7251427);
   effVsPt->SetBinContent(20,0.7128625);
   effVsPt->SetBinContent(21,0.7108469);
   effVsPt->SetBinContent(22,0.7143682);
   effVsPt->SetBinContent(23,0.7167073);
   effVsPt->SetBinContent(24,0.7113711);
   effVsPt->SetBinContent(25,0.6948793);
   effVsPt->SetBinContent(26,0.6980561);
   effVsPt->SetBinContent(27,0.6980561);
   effVsPt->SetBinContent(28,0.6980561);
   effVsPt->SetBinContent(29,0.6980561);

   effVsPt->SetLineWidth(3);
   effVsPt->SetLineColor(4);
   effVsPt->SetLineStyle(2);
   //effVsPt->Draw("");
   effVsPt->Draw("Lsame");

}
