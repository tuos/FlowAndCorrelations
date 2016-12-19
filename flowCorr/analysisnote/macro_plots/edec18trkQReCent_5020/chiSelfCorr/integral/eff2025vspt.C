void eff2025vspt(){
//=========Macro generated from canvas: c1/c1
//=========  (Tue Aug 16 02:05:23 2016) by ROOT version5.32/00
   Double_t xAxis1[39] = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.05, 1.1, 1.15, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.5, 3, 4, 6, 8, 12}; 
   
   TH1D *h = new TH1D("h","Absolute Efficiency Centrality 20-25%",38, xAxis1);
   h->SetBinContent(4,0.008068635);
   h->SetBinContent(5,0.3442831);
   h->SetBinContent(6,0.4806927);
   h->SetBinContent(7,0.5647607);
   h->SetBinContent(8,0.6249436);
   h->SetBinContent(9,0.6699954);
   h->SetBinContent(10,0.7034954);
   h->SetBinContent(11,0.7270675);
   h->SetBinContent(12,0.7463523);
   h->SetBinContent(13,0.7631849);
   h->SetBinContent(14,0.7716165);
   h->SetBinContent(15,0.7802519);
   h->SetBinContent(16,0.7844637);
   h->SetBinContent(17,0.7918795);
   h->SetBinContent(18,0.7934303);
   h->SetBinContent(19,0.7963511);
   h->SetBinContent(20,0.8010686);
   h->SetBinContent(21,0.8020054);
   h->SetBinContent(22,0.8034762);
   h->SetBinContent(23,0.8051232);
   h->SetBinContent(24,0.8057314);
   h->SetBinContent(25,0.8087671);
   h->SetBinContent(26,0.8100354);
   h->SetBinContent(27,0.8073864);
   h->SetBinContent(28,0.8346975);
   h->SetBinContent(29,0.8314103);
   h->SetBinContent(30,0.7947456);
   h->SetBinContent(31,0.7175398);
   h->SetBinContent(32,0.6850637);
   h->SetBinContent(33,0.6722281);
   h->SetBinContent(34,0.6788572);
   h->SetBinContent(35,0.6769655);
   h->SetBinContent(36,0.673062);
   h->SetBinContent(37,0.7035232);
   h->SetBinContent(38,0.6317467);
   h->SetBinContent(39,0.6967172);
   h->SetBinError(4,0.0001331109);
   h->SetBinError(5,0.0006701894);
   h->SetBinError(6,0.0007010518);
   h->SetBinError(7,0.0007123846);
   h->SetBinError(8,0.000723561);
   h->SetBinError(9,0.0007390598);
   h->SetBinError(10,0.0007593573);
   h->SetBinError(11,0.0007867874);
   h->SetBinError(12,0.0008197283);
   h->SetBinError(13,0.0008553402);
   h->SetBinError(14,0.0009029751);
   h->SetBinError(15,0.0009534416);
   h->SetBinError(16,0.00101477);
   h->SetBinError(17,0.001074051);
   h->SetBinError(18,0.001147233);
   h->SetBinError(19,0.001220551);
   h->SetBinError(20,0.001296236);
   h->SetBinError(21,0.001385056);
   h->SetBinError(22,0.001476322);
   h->SetBinError(23,0.001578782);
   h->SetBinError(24,0.001676797);
   h->SetBinError(25,0.001301312);
   h->SetBinError(26,0.001473839);
   h->SetBinError(27,0.001680171);
   h->SetBinError(28,0.001793693);
   h->SetBinError(29,0.002032325);
   h->SetBinError(30,0.002467963);
   h->SetBinError(31,0.003081251);
   h->SetBinError(32,0.00356299);
   h->SetBinError(33,0.002134642);
   h->SetBinError(34,0.003314384);
   h->SetBinError(35,0.00391009);
   h->SetBinError(36,0.005823004);
   h->SetBinError(37,0.0133506);
   h->SetBinError(38,0.02279981);
   h->SetBinError(39,0.05364709);
   h->SetEntries(736433.4);
   
//   h->Draw("");
   const int n=10;
   double mpt[n]={0.352,0.451,0.550,0.696,0.894,1.093,1.377,1.775,2.207,2.713};
   for(int i=0;i<n;i++){
     cout<<h->GetBinContent(h->FindBin(mpt[i]))<<", ";
   }
   cout<<endl;

}
