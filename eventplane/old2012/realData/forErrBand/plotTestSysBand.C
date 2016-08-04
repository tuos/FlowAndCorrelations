void plotTestSysBand()
{
  const int nBin=5;
  double pt[nBin]={0.5, 0.9, 1.5, 3.5, 5};
  //double v2[nBin]={0.03, 0.06, 0.08, 0.12, 0.1};
  double v2[nBin]={1.0, 1.0, 1.0, 1., 1.0};
  double v2e[nBin]={0.002, 0.004, 0.007, 0.01, 0.015};

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
  hist->SetMinimum(0.801);
  hist->SetMaximum(1.199);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetTitleOffset(0.95);
  hist->GetXaxis()->SetTitleSize(0.066);
  hist->GetYaxis()->SetTitleSize(0.066);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->Draw();

  TGraphErrors *graph = new TGraphErrors(nBin,pt,v2,0,v2e);
  graph->SetTitle("");
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1.0);
  graph->SetMarkerColor(1);
  graph->SetLineWidth(2);
  graph->SetLineColor(1);
  graph->SetFillColor(kYellow+2);
  graph->Draw("e3same");

  c1->Print("v2byhand.png");

}

