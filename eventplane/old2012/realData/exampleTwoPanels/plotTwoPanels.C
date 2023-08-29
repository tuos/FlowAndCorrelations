void plotTwoPanels()
{
  const int nBin=5;
  double pt[nBin]={0.5, 1.0, 2.0, 3.5, 5};
  double v2A[nBin]={0.03, 0.07, 0.10, 0.13, 0.11};
  double v2A_E[nBin]={0.002, 0.004, 0.007, 0.01, 0.012};
  double v2B[nBin]={0.029, 0.068, 0.09, 0.12, 0.10};
  double v2B_E[nBin]={0.0018, 0.0035, 0.006, 0.009, 0.011};
  double ratioAoverB[nBin];
  double ratioAoverB_E[nBin];
  for(int i=0; i<nBin; i++){
    ratioAoverB[i] = v2B[i]/v2A[i];
    ratioAoverB_E[i] = v2B[i]/v2A[i]*sqrt(v2A_E[i]*v2A_E[i]/v2A[i]/v2A[i] + v2B_E[i]*v2B_E[i]/v2B[i]/v2B[i]); //error of A and B are uncorrelated
  }

  TCanvas *c1 = new TCanvas("c1","c1",1,1,450,750);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.);
  c1->SetBottomMargin(0.);
  c1->SetTopMargin(0.0);
  c1->SetRightMargin(0.0);
  c1->SetTicks(-1);
  gStyle->SetOptStat(0);

  TPad *pad1 = new TPad("pad1","",0.001,0.3,0.999,0.999);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0.15);
  pad1->SetTopMargin(0.02);
  pad1->SetRightMargin(0.01);
  pad1->SetTicks(-1);
  pad1->Draw();

  TPad *pad2 = new TPad("pad2","",0.001,0.001,0.999,0.409);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  pad2->SetTopMargin(0.0);
  pad2->SetRightMargin(0.01);
  pad2->SetTicks(-1);
  pad2->Draw();

  pad1->cd();
  TH1D* hist = new TH1D("hist","",100,0.,5.9);
  hist->SetXTitle("p_{T} (GeV/c)");
  hist->SetYTitle("v_{2}{EP}");
  hist->SetMinimum(-0.005);
  hist->SetMaximum(0.199);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetTitleOffset(0.95);
  hist->GetXaxis()->SetTitleSize(0.066);
  hist->GetYaxis()->SetTitleSize(0.066);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->Draw("*");

  TGraphErrors *graphA = new TGraphErrors(nBin,pt,v2A,0,v2A_E);
  graphA->SetTitle("");
  graphA->SetMarkerStyle(20);
  graphA->SetMarkerSize(1.0);
  graphA->SetMarkerColor(1);
  graphA->SetLineWidth(2);
  graphA->SetLineColor(1);
  graphA->Draw("pesame");
  TGraphErrors *graphB = new TGraphErrors(nBin,pt,v2B,0,v2B_E);
  graphB->SetTitle("");
  graphB->SetMarkerStyle(25);
  graphB->SetMarkerSize(1.0);
  graphB->SetMarkerColor(2);
  graphB->SetLineWidth(2);
  graphB->SetLineColor(2);
  graphB->Draw("pesame");
  TLegend *leg1 = new TLegend(0.23,0.78,0.55,0.94);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.056);
  leg1->SetBorderSize(0);
  leg1->AddEntry(graphA,"v2A","pl");
  leg1->AddEntry(graphB,"v2B","pl");
  leg1->Draw();
  TLatex *tex= new TLatex();
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.056);
  tex->DrawLatex(0.7,0.86,"Example");

  pad2->cd();
  //TH1D* histRatio = (TH1D*)hist->Clone("histRatio");
  //histRatio->SetYTitle("B/A");
  //histRatio->SetMinimum(0.8);
  //histRatio->SetMaximum(1.2);
  //histRatio->Draw();
  TH1D* histR = new TH1D("histR","",100,0.,5.9);
  histR->SetXTitle("p_{T} (GeV/c)");
  histR->SetYTitle("Ratio B/A");
  histR->SetMinimum(0.75);
  histR->SetMaximum(1.25);
  histR->GetXaxis()->CenterTitle(1);
  histR->GetYaxis()->CenterTitle(1);
  histR->GetYaxis()->SetTitleOffset(0.7);
  histR->GetXaxis()->SetTitleOffset(0.95);
  histR->GetXaxis()->SetTitleSize(0.066*0.6/0.4); // 0.6/0.4 is the ratio of the pad size for top and bottom pads
  histR->GetYaxis()->SetTitleSize(0.066*0.6/0.4);
  histR->GetXaxis()->SetLabelSize(0.05*0.6/0.4);
  histR->GetYaxis()->SetLabelSize(0.05*0.6/0.4);
  histR->GetYaxis()->SetNdivisions(506); // control number of divisions
  histR->Draw();
  TGraphErrors *graphRatio = new TGraphErrors(nBin,pt,ratioAoverB,0,ratioAoverB_E);
  graphRatio->SetTitle("");
  graphRatio->SetMarkerStyle(21);
  graphRatio->SetMarkerSize(1.0);
  graphRatio->SetMarkerColor(4);
  graphRatio->SetLineWidth(2);
  graphRatio->SetLineColor(4);
  graphRatio->Draw("pesame");
  TLine *line1 = new TLine(0, 1, 5.9, 1);
  line1->SetLineStyle(1);
  line1->Draw();
  tex->SetTextSize(0.056*0.6/0.4);
  tex->DrawLatex(0.7,0.86,"Example");

  c1->Print("twoPanels.png");

}

