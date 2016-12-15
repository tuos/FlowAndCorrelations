void cent1030EffVsPt(){
   Double_t xAxis1[35] = {0.0, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.05, 1.1, 1.15, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.8, 3.2, 10000}; 
   
   TH1D *EffVsPt1030Hist = new TH1D("EffVsPt1030Hist","",34, xAxis1);
   EffVsPt1030Hist->SetBinContent(1,0.4009751);
   EffVsPt1030Hist->SetBinContent(2,0.4309751);
   EffVsPt1030Hist->SetBinContent(3,0.4860269);
   EffVsPt1030Hist->SetBinContent(4,0.5309778);
   EffVsPt1030Hist->SetBinContent(5,0.5669101);
   EffVsPt1030Hist->SetBinContent(6,0.5961907);
   EffVsPt1030Hist->SetBinContent(7,0.6243077);
   EffVsPt1030Hist->SetBinContent(8,0.6441222);
   EffVsPt1030Hist->SetBinContent(9,0.6576585);
   EffVsPt1030Hist->SetBinContent(10,0.6709314);
   EffVsPt1030Hist->SetBinContent(11,0.6843305);
   EffVsPt1030Hist->SetBinContent(12,0.6930487);
   EffVsPt1030Hist->SetBinContent(13,0.70108);
   EffVsPt1030Hist->SetBinContent(14,0.7082669);
   EffVsPt1030Hist->SetBinContent(15,0.7143234);
   EffVsPt1030Hist->SetBinContent(16,0.722723);
   EffVsPt1030Hist->SetBinContent(17,0.7272676);
   EffVsPt1030Hist->SetBinContent(18,0.7307172);
   EffVsPt1030Hist->SetBinContent(19,0.7342052);
   EffVsPt1030Hist->SetBinContent(20,0.7385603);
   EffVsPt1030Hist->SetBinContent(21,0.7361698);
   EffVsPt1030Hist->SetBinContent(22,0.7296365);
   EffVsPt1030Hist->SetBinContent(23,0.7580977);
   EffVsPt1030Hist->SetBinContent(24,0.7900435);
   EffVsPt1030Hist->SetBinContent(25,0.7902352);
   EffVsPt1030Hist->SetBinContent(26,0.7657154);
   EffVsPt1030Hist->SetBinContent(27,0.740352);
   EffVsPt1030Hist->SetBinContent(28,0.7236057);
   EffVsPt1030Hist->SetBinContent(29,0.7006291);
   EffVsPt1030Hist->SetBinContent(30,0.6766835);
   EffVsPt1030Hist->SetBinContent(31,0.6649335);
   EffVsPt1030Hist->SetBinContent(32,0.6765371);
   EffVsPt1030Hist->SetBinContent(33,0.6988527);
   EffVsPt1030Hist->SetBinContent(34,0.6988527);
 
   EffVsPt1030Hist->SetLineWidth(3);
   EffVsPt1030Hist->SetLineColor(4);
   EffVsPt1030Hist->SetLineStyle(2);
   //EffVsPt1030Hist->Draw("");
   EffVsPt1030Hist->Draw("Lsame");
  
}
