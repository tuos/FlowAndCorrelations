{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Fri Nov 10 12:21:07 2017) by ROOT version5.30/01
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,74,424,385);
   Canvas_1->Range(-80.96376,-2.438573,728.6738,9.50925);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetLogy();
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(34);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.57963.v1/t1");
   grae->SetFillColor(1);
   grae->SetPoint(0,19.4,1.97e+07);
   grae->SetPointError(0,1.4,1.6,2406305,2662125);
   grae->SetPoint(1,22.4,1.02e+07);
   grae->SetPointError(1,1.4,1.6,1175835,1297968);
   grae->SetPoint(2,25.9,5170000);
   grae->SetPointError(2,1.9,2.1,576194.1,627702.7);
   grae->SetPoint(3,29.9,2670000);
   grae->SetPointError(3,1.9,2.1,288125,314618.5);
   grae->SetPoint(4,34.3,1390000);
   grae->SetPointError(4,2.3,2.7,147850.5,160212.2);
   grae->SetPoint(5,39.8,655000);
   grae->SetPointError(5,2.8,3.2,67782.22,73651.83);
   grae->SetPoint(6,45.8,336000);
   grae->SetPointError(6,2.8,3.2,34926.23,37591.48);
   grae->SetPoint(7,52.3,180000);
   grae->SetPointError(7,3.3,3.7,18790.83,20390.91);
   grae->SetPoint(8,59.7,92100);
   grae->SetPointError(8,3.7,4.3,9508.182,10335.33);
   grae->SetPoint(9,68.6,46600);
   grae->SetPointError(9,4.6,5.4,4864.513,5328.93);
   grae->SetPoint(10,78.7,23700);
   grae->SetPointError(10,4.7,5.3,2531.022,2742.859);
   grae->SetPoint(11,90,11800);
   grae->SetPointError(11,6,7,1275.274,1393.2);
   grae->SetPoint(12,104.8,5420);
   grae->SetPointError(12,7.8,9.2,597.0863,651.2125);
   grae->SetPoint(13,122.7,2380);
   grae->SetPointError(13,8.7,10.3,269.0348,295.2064);
   grae->SetPoint(14,142.3,1080);
   grae->SetPointError(14,9.3,10.7,125.3545,139.387);
   grae->SetPoint(15,162.8,523);
   grae->SetPointError(15,9.8,11.2,62.77961,69.57669);
   grae->SetPoint(16,184.3,261);
   grae->SetPointError(16,10.3,11.7,32.3903,36.04163);
   grae->SetPoint(17,207.3,135);
   grae->SetPointError(17,11.3,12.7,17.28844,19.31255);
   grae->SetPoint(18,231.8,71.5);
   grae->SetPointError(18,11.8,13.2,9.444768,10.6595);
   grae->SetPoint(19,257.7,38.1);
   grae->SetPointError(19,12.7,14.3,5.223175,5.908572);
   grae->SetPoint(20,285.2,20.7);
   grae->SetPointError(20,13.2,14.8,2.942969,3.356529);
   grae->SetPoint(21,314.2,11.6);
   grae->SetPointError(21,14.2,15.8,1.719971,1.963178);
   grae->SetPoint(22,345.1,6.66);
   grae->SetPointError(22,15.1,16.9,1.02161,1.181094);
   grae->SetPoint(23,377.7,3.78);
   grae->SetPointError(23,15.7,17.3,0.607452,0.7015949);
   grae->SetPoint(24,411.6,2.19);
   grae->SetPointError(24,16.6,18.4,0.3680894,0.4290724);
   grae->SetPoint(25,448,1.29);
   grae->SetPointError(25,18,20,0.2265851,0.2662561);
   grae->SetPoint(26,486.5,0.755);
   grae->SetPointError(26,18.5,20.5,0.139389,0.1654983);
   grae->SetPoint(27,526.5,0.439);
   grae->SetPointError(27,19.5,21.5,0.08514903,0.1015457);
   grae->SetPoint(28,568.9,0.277);
   grae->SetPointError(28,20.9,23.1,0.05670387,0.06806821);
   grae->SetPoint(29,613.9,0.144);
   grae->SetPointError(29,21.9,24.1,0.03138044,0.03789417);
   grae->SetPoint(30,660.8,0.0852);
   grae->SetPointError(30,22.8,25.2,0.01987426,0.0240664);
   grae->SetPoint(31,710.2,0.0505);
   grae->SetPointError(31,24.2,26.8,0.01265526,0.01536827);
   grae->SetPoint(32,786.1,0.0202);
   grae->SetPointError(32,49.1,59.9,0.005431697,0.006703022);
   grae->SetPoint(33,1064.4,0.00202);
   grae->SetPointError(33,218.4,619.6,0.0006255741,0.0008061496);
   
   TH1F *Graph_Graph1D_y11 = new TH1F("Graph_Graph1D_y11","doi:10.17182/hepdata.57963.v1/t1",100,0,1850.6);
   Graph_Graph1D_y11->SetMinimum(0.0570439);
   Graph_Graph1D_y11->SetMaximum(2.062849e+08);
   Graph_Graph1D_y11->SetDirectory(0);
   Graph_Graph1D_y11->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   Graph_Graph1D_y11->SetLineColor(ci);
   Graph_Graph1D_y11->GetXaxis()->SetTitle("PT [GEV]");
   Graph_Graph1D_y11->GetXaxis()->SetRange(1,35);
   Graph_Graph1D_y11->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y11->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1D_y11->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1D_y11->GetXaxis()->SetTitleFont(42);
   Graph_Graph1D_y11->GetYaxis()->SetTitle("D2(SIG)/DPT/DYRAP [PB/GEV]");
   Graph_Graph1D_y11->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y11->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1D_y11->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1D_y11->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y11->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y11->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1D_y11->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1D_y11->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y11);
   
   grae->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.2559176,0.9348119,0.7440824,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("doi:10.17182/hepdata.57963.v1/t1");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);


TF1 *f1 = new TF1("f1","[0]*pow(x, [1])", 25, 250);
f1->SetParameters(9e13,-5);
TF1 *fJet = new TF1("fJet","(9.06402e+13)*pow(x, -5.08010e+00)", 25, 250);

//TF1 *f1 = new TF1("f1","[0]/pow([1]+x/[2], [3])", 25, 500);
//f1->SetParameters(1,1,1,1);
f1->SetLineColor(2);
grae->Fit("f1", "R");
//f1->Draw("same");

fJet->SetLineWidth(3);
fJet->SetLineColor(4);
fJet->Draw("same");

Canvas_1->SaveAs("plot_jetSpectraFit.png");
Canvas_1->SaveAs("plot_jetSpectraFit.pdf");

}
