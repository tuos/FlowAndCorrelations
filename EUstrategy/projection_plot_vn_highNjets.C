#include <iostream>
#include "TROOT.h"
#include "TObject.h"
#include "TProfile.h"
#include "TFile.h"
#include "TTree.h"
#include "math.h"
#include "TH1.h"
#include "GetFileAndSys.C"

void projection_plot_vn_highNjets(){
  const int nNchBin = 9;
  double Nch03[nNchBin];
  double Nch05[nNchBin];
  double v2_03[nNchBin];
  double v2_05[nNchBin];
  double v2_03_stat[nNchBin];
  double v2_05_stat[nNchBin];
  double v2_03_sys[nNchBin];
  double v2_05_sys[nNchBin];
  double tmp;
  double v2_03_stat_new[nNchBin+1];
  double v2_05_stat_new[nNchBin+1];

  ifstream input03;
  input03.open("vn_03_30.txt");
  for(int i=0; i<nNchBin; i++){
    input03>>Nch03[i];
    input03>>v2_03[i];
    input03>>v2_03_stat[i];
    input03>>tmp;
    input03>>v2_03_sys[i];
    input03>>tmp;
    v2_03_stat_new[i] = v2_03_stat[i]/sqrt(21.7);
    cout<<Nch03[i]<<"  "<<v2_03[i]<<"  "<<v2_03_stat[i]<<"  "<<v2_03_stat_new[i]<<endl;
  }
  cout<<"pt: 0.5 - 3.0"<<endl;
  ifstream input05;
  input05.open("vn_05_30.txt");
  for(int i=0; i<nNchBin; i++){
    input05>>Nch05[i];
    input05>>v2_05[i];
    input05>>v2_05_stat[i];
    input05>>tmp;
    input05>>v2_05_sys[i];
    input05>>tmp;
    v2_05_stat_new[i] = v2_05_stat[i]/sqrt(21.7);
    cout<<Nch05[i]<<"  "<<v2_05[i]<<"  "<<v2_05_stat[i]<<"  "<<v2_05_stat_new[i]<<endl;
  }

/*
  gStyle->SetPadLeftMargin(0.18);
  //gStyle->SetPadRightMargin(0.14);
  gStyle->SetPadBottomMargin(0.10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetOptStat(0);  // hide statistics box
  gStyle->SetHistLineWidth(2);
  gStyle->SetLabelFont(132,"xyz");
  gStyle->SetLabelSize(0.04,"xyz"); // size of axis labels (rel. to pad size)
  gStyle->SetTitleFont(132,"xyz");  // roman font
  gStyle->SetTitleSize(0.04,"xyz"); // size of axis titles                                                                         
  gStyle->SetLabelOffset(0.01,"xyz"); // label offset (to fit bigger font
  gStyle->SetNdivisions(505,"xyz");
  gStyle->SetPalette(1);
*/
  
  TCanvas* c_vn_jet;
  c_vn_jet = new TCanvas("c_vn_jet", "c_vn_jet", 1200, 600);
  c_vn_jet->SetFillColor(10);
  c_vn_jet->SetFrameFillColor(0);
  c_vn_jet->SetFrameBorderSize(0);
  c_vn_jet->SetFrameBorderMode(0);
  c_vn_jet->SetLeftMargin(0.16);
  c_vn_jet->SetBottomMargin(0.01);
  c_vn_jet->SetTopMargin(0.01);
  c_vn_jet->SetRightMargin(0.01);
  //gPad->SetTicks(-1);
  gStyle->SetOptStat(0);
  c_vn_jet->Divide(2,1,0,0);
  //c_vn_jet->Divide(2,1);

  c_vn_jet->cd(1);
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.05);
  //gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  
  
  TH1D* hist_1 = new TH1D("hist_1","",140,1,141);
  hist_1->SetMarkerStyle(kFullCircle);
  hist_1->SetMarkerColor(kBlue);
  hist_1->SetMarkerSize(1.5);
  hist_1->GetXaxis()->SetTitle("N_{ch}^{j}");
  hist_1->GetYaxis()->SetTitle("v_{2}^{*}{2, |#Delta#eta^{*}|>2}");
  hist_1->GetXaxis()->CenterTitle(1);
  hist_1->GetYaxis()->CenterTitle(1);
  hist_1->GetYaxis()->SetTitleFont(42);
  hist_1->GetYaxis()->SetTitleSize(0.05);
  hist_1->GetYaxis()->SetLabelSize(0.05);
  hist_1->GetYaxis()->SetTitleOffset(1.43);
  hist_1->GetYaxis()->SetNdivisions(505);
  hist_1->GetXaxis()->SetTitleFont(42);
  hist_1->GetXaxis()->SetTitleSize(0.05);
  hist_1->GetXaxis()->SetLabelSize(0.05);
  hist_1->GetXaxis()->SetTitleOffset(1.1);
  hist_1->GetXaxis()->SetNdivisions(505);
  hist_1->SetTitle("");
  hist_1->SetMinimum(0.);
  hist_1->SetMaximum(0.41);
  hist_1->Draw("");
  
  TGraphErrors *gr2 = new TGraphErrors(nNchBin,Nch03,v2_03,0,v2_03_stat);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(25);
  gr2->SetMarkerSize(1.0);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(3);
  gr2->SetLineColor(2);

  double Nch03new[nNchBin+1];
  double v2_03new[nNchBin+1];
  for(int i=0; i<nNchBin; i++){
    Nch03new[i]=Nch03[i]+2.5;
    v2_03new[i] = v2_03[i];
  }
  Nch03new[nNchBin] = Nch03new[nNchBin-1]+15;
  v2_03new[nNchBin] = v2_03[nNchBin-1] + (v2_03[nNchBin-1] - v2_03[nNchBin-2])/(Nch03new[nNchBin-1] - Nch03new[nNchBin-2])*(Nch03new[nNchBin] - Nch03new[nNchBin-1]);
  v2_03_stat_new[nNchBin] = v2_03_stat_new[nNchBin-1]*v2_03_stat_new[nNchBin-1]/v2_03_stat_new[nNchBin-3];

  TGraphErrors *gr2b = new TGraphErrors(nNchBin+1,Nch03new,v2_03new,0,v2_03_stat_new);
  gr2b->SetTitle("");
  gr2b->SetMarkerStyle(20);
  gr2b->SetMarkerSize(1.0);
  gr2b->SetMarkerColor(1);
  gr2b->SetLineWidth(3);
  gr2b->SetLineColor(1);

  drawSysBoxValue(gr2,16,1.6, v2_03_sys);

  gr2->Draw("psameez");
  gr2b->Draw("psameez");


  TLegend *leg = new TLegend(0.5,0.65,0.8,0.82);
  leg->SetFillColor(10);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextColor(1);
  leg->SetTextSize(0.045);
  leg->AddEntry(gr2,"pp 138 fb^{-1}","p");
  leg->AddEntry(gr2b,"Projected 3000 fb^{-1}","p");
  leg->Draw();

  TLatex *tex1= new TLatex();
  tex1->SetNDC();
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.045);
  tex1->DrawLatex(0.53,0.85,"0.3 < j_{T} < 3.0 GeV");
  tex1->DrawLatex(0.23,0.34,"p_{T}^{jet} > 550 GeV");
  tex1->DrawLatex(0.23,0.26,"|#eta^{jet}| < 1.6");
  tex1->DrawLatex(0.23,0.19,"Anti-k_{T} R = 0.8");
  tex1->SetTextFont(62);
  tex1->DrawLatex(0.16,0.965,"CMS Projection");



  c_vn_jet->cd(2);
  //gPad->SetLeftMargin(0.14);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.05);
  gPad->SetRightMargin(0.01);
  gPad->SetTicks(-1);

  TH1D *hist_2;
  hist_2 = (TH1D*)hist_1->Clone("hist_2");
  hist_2->SetMarkerSize(1);
  hist_2->SetMarkerStyle(20);
  hist_2->Draw();

  TGraphErrors *gr3 = new TGraphErrors(nNchBin,Nch05,v2_05,0,v2_05_stat);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(25);
  gr3->SetMarkerSize(1.0);
  gr3->SetMarkerColor(2);
  gr3->SetLineWidth(3);
  gr3->SetLineColor(2);

  double Nch05new[nNchBin+1];
  double v2_05new[nNchBin+1];
  for(int i=0; i<nNchBin; i++){
    Nch05new[i]=Nch05[i]+2.5;
    v2_05new[i] = v2_05[i];
  }
  Nch05new[nNchBin] = Nch05new[nNchBin-1]+15;
  v2_05new[nNchBin] = v2_05[nNchBin-1] + (v2_05[nNchBin-1] - v2_05[nNchBin-2])/(Nch05new[nNchBin-1] - Nch05new[nNchBin-2])*(Nch05new[nNchBin] - Nch05new[nNchBin-1]);
  v2_05_stat_new[nNchBin] = v2_05_stat_new[nNchBin-1]*v2_05_stat_new[nNchBin-1]/v2_05_stat_new[nNchBin-3];

  TGraphErrors *gr3b = new TGraphErrors(nNchBin+1,Nch05new,v2_05new,0,v2_05_stat_new);
  gr3b->SetTitle("");
  gr3b->SetMarkerStyle(20);
  gr3b->SetMarkerSize(1.0);
  gr3b->SetMarkerColor(1);
  gr3b->SetLineWidth(3);
  gr3b->SetLineColor(1);

  drawSysBoxValue(gr3,16,1.6, v2_05_sys);

  gr3->Draw("psameez");
  gr3b->Draw("psameez");


  TLegend *leg2 = new TLegend(0.5,0.65,0.8,0.82);
  leg2->SetFillColor(10);
  leg2->SetBorderSize(0);
  leg2->SetTextFont(42);
  leg2->SetTextColor(1);
  leg2->SetTextSize(0.045);
  leg2->AddEntry(gr3,"pp 138 fb^{-1}","p");
  leg2->AddEntry(gr3b,"Projected 3000 fb^{-1}","p");
  leg2->Draw();

  TLatex *tex2= new TLatex();
  tex2->SetNDC();
  tex2->SetTextFont(42);
  tex2->SetTextSize(0.045);
  tex2->DrawLatex(0.615,0.962,"pp 13 TeV 3000 fb^{-1}");
  tex2->DrawLatex(0.53,0.85,"0.5 < j_{T} < 3.0 GeV");


  c_vn_jet->SaveAs("fig_projection_vn_jet.png");
  c_vn_jet->SaveAs("fig_projection_vn_jet.pdf");


}


