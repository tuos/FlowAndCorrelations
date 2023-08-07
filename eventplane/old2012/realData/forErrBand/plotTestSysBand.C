void plotTestSysBand()
{
  const int nBin=5;
  double pt[nBin]={0.5, 0.9, 1.5, 3.5, 5};
  double v2[nBin]={0.03, 0.07, 0.10, 0.13, 0.11};
  double v2StatE[nBin]={0.002, 0.004, 0.007, 0.01, 0.015};
  double v2SystE[nBin]={0.003, 0.005, 0.006, 0.008, 0.009};

  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->SetTicks(-1);
  gStyle->SetOptStat(0);
  TH1D* hist = new TH1D("hist","",100,0.,5.9);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{2}{EP}");
  hist->SetMinimum(-0.001);
  hist->SetMaximum(0.199);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetTitleOffset(0.95);
  hist->GetXaxis()->SetTitleSize(0.066);
  hist->GetYaxis()->SetTitleSize(0.066);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->Draw();

  TGraphErrors *graphSys = new TGraphErrors(nBin,pt,v2,0,v2SystE);
  graphSys->SetTitle("");
  graphSys->SetFillColor(kGray);
  graphSys->Draw("e3same");
  TGraphErrors *graph = new TGraphErrors(nBin,pt,v2,0,v2StatE);
  graph->SetTitle("");
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1.0);
  graph->SetMarkerColor(1);
  graph->SetLineWidth(2);
  graph->SetLineColor(1);
  graph->Draw("pesame");

  c1->Print("v2byhand.png");

}

