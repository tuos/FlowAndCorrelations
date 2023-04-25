#include <iostream>
#include "TROOT.h"
#include "TObject.h"
#include "TProfile.h"
#include "TFile.h"
#include "TTree.h"
#include "math.h"
#include "TH1.h"

int centmin = 60;
int centmax = 70;

//const int mergepTbin = 12;
const int npTbin = 17;

double phimax = 1.5;
double etamax = 1.0;
double etamin_flow = 2.0;
double etamax_flow = 4.0;
double MaxEtaRange = 4.0;
//double flow_cal_min = -TMath::Pi()*0.5;
double flow_cal_min = 0.;
double flow_cal_max = TMath::Pi()*0.5*3.;

double pTAvg[npTbin+1] = {0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};

void Charge_Hadron_flow_pT_effCorr()
{
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadRightMargin(0.14);
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

  
  //TFile*file3 = new TFile ("MC_HINtestRun3_0p5pttrg10p0_1p0ptass3p0_eta2p4_cent070_Nov21_2022.root");
  //TFile*file3 = new TFile ("2022_PbPbData_WMBTrg_0p3pttrg3p0_0p3ptass3p0_MergedTrack.root");
  //TFile*file3 = new TFile ("2022_PbPbData_WMBTrg_0p5pttrg10_0p5ptass10_GeneralTrack.root");
  // TFile*file3 = new TFile ("2022_PbPbData_WMBTrg_0p3pttrg3p0_1ptass3p0_MergedTrack.root");
  //TFile*file3 = new TFile ("2022_PbPbData_WMBTrg_0p5pttrg10_1ptass3p0_GeneralTrack.root");
  //TFile*file3 = new TFile ("2022_PbPbData_WMBTrg_0p5pttrg10_1ptass3p0_GeneralTrack_WithDiffCent.root");
  //TFile*file3 = new TFile ("PbPbraw_allcent_vnpT.root");
  //TFile*file3 = new TFile ("PbPbraw_allcent_vnpT_genTracks_json_evts_newEff.root");
  TFile*file3 = new TFile ("PbPbraw_allcent_vnpT_genTracks_json_Allevts_newEff.root");

  TDirectory*dirG1d= (TDirectory*)file3->Get(Form("defaultAnalysis_%d%d",centmin, centmax));
  TDirectory*dir1d= (TDirectory*)dirG1d->Get("Signal");
  TDirectory*dir2d= (TDirectory*)dirG1d->Get("Background");
  TDirectory*dir3d= (TDirectory*)dirG1d->Get("Global");

  TH1D* hNtrig[npTbin];
  TH2D* hSignal[npTbin];
  TH2D* hMixed[npTbin];
  TH2D* hCorr[npTbin];

  TH1D* hNtrig_M[npTbin];
  TH2D* hSignal_M[npTbin];
  TH2D* hMixed_M[npTbin];

  TH1D* hNtrig_merge;
  TH2D* hSignal_merge;
  TH2D* hMixed_merge;
  TH2D* hCorr_merge;

  
  TH1D* heta_proj[npTbin];
  TH1D* hphi_proj[npTbin];
  TH1D* hphi_proj_flow[npTbin];

  TF1 * fit_dphi_flow[npTbin];

  TH1D* hphi_proj_merge_flow;

  TF1 * fit_dphi_merge_flow;
  
  TCanvas* c_signal[npTbin];
  TCanvas* c_mixed[npTbin];
  TCanvas* c_corr[npTbin];
  TCanvas* c_deta[npTbin];
  TCanvas* c_dphi[npTbin];
  TCanvas* c_dphi_flow[npTbin];
  TCanvas* c_corr_merge;
  TCanvas* c_dphi_merge_flow;
  
  
  ofstream outfile;
  outfile.open(Form("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent%d_%d.dat", centmin, centmax));

  //*********************************************************************************
  //~~~~~~~~~~~~~~~~~~~~Calculate the denomenator of vn~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //*********************************************************************************
  
  hSignal_merge = (TH2D*)dir1d->Get("signal_all_recocor");
  hSignal_merge->Reset("ICSEM");
  
  hMixed_merge = (TH2D*)dir2d->Get("background_all_recocor");
  hMixed_merge->Reset("ICSEM");
  
  hNtrig_merge = (TH1D*)dir3d->Get("hMult_trg");
  hNtrig_merge->Reset("ICSEM");
  
  for(int j = 5; j < 10; j++)
    {
      hSignal_M[j] = (TH2D*)dir1d->Get(Form("signal_all_ptbin%d_recocor", j));
      hMixed_M[j] = (TH2D*)dir2d->Get(Form("background_all_ptbin%d_recocor", j));
      hNtrig_M[j] = (TH1D*)dir3d->Get(Form("hMult_trg_ptbin%d", j));
      
      hSignal_merge->Add(hSignal_M[j]);
      hMixed_merge->Add(hMixed_M[j]);
      hNtrig_merge->Add(hNtrig_M[j]);
    }
  
  //~~~~~~~~~~~Merge correlation~~~~~~~~~~~~~~~~
  c_corr_merge = new TCanvas("c_corr_merge", "c_corr_merge", 600, 530);
  c_corr_merge->cd();
  
  //hSignal_merge->Scale(1./hNtrig_merge->GetBinContent(2));
  hSignal_merge->Scale(1./((hSignal_merge->GetXaxis()->GetBinWidth(1))*(hSignal_merge->GetYaxis()->GetBinWidth(1))));
  
  //hMixed_merge->Scale(1./hNtrig_merge->GetBinContent(2));
  hMixed_merge->Scale(1./((hMixed_merge->GetXaxis()->GetBinWidth(1))*(hMixed_merge->GetYaxis()->GetBinWidth(1))));
  //hMixed_merge->Scale(1./hMixed_merge->GetBinContent(hMixed_merge->FindBin(0.,0.)));
  
  hCorr_merge = (TH2D*)hSignal_merge->Clone("hCorr_merge");
  hCorr_merge->Reset("ICSEM");
  hCorr_merge->Add(hSignal_merge);
  hCorr_merge->Divide(hMixed_merge);
  hCorr_merge->GetXaxis()->SetTitle("#Delta#eta");
  hCorr_merge->GetYaxis()->SetTitle("#Delta#varphi (rad)");
  hCorr_merge->GetZaxis()->SetTitle("C_{2}^{Corr.}(#Delta#eta, #Delta#varphi)");
  
  hCorr_merge->GetXaxis()->CenterTitle(1);
  hCorr_merge->GetYaxis()->CenterTitle(1);
  hCorr_merge->GetZaxis()->CenterTitle(1);
  
  hCorr_merge->GetYaxis()->SetTitleSize(0.05);
  hCorr_merge->GetYaxis()->SetLabelSize(0.05);
  hCorr_merge->GetYaxis()->SetTitleOffset(1.9);
  
  hCorr_merge->GetXaxis()->SetTitleSize(0.05);
  hCorr_merge->GetXaxis()->SetLabelSize(0.05);
  hCorr_merge->GetXaxis()->SetTitleOffset(1.9);
  
  hCorr_merge->GetZaxis()->SetTitleSize(0.05);
  hCorr_merge->GetZaxis()->SetLabelSize(0.05);
  hCorr_merge->GetZaxis()->SetTitleOffset(1.7);
  
  hCorr_merge->GetXaxis()->SetNdivisions(505);
  hCorr_merge->GetYaxis()->SetNdivisions(505);
  hCorr_merge->GetZaxis()->SetNdivisions(505);
  
  hCorr_merge->GetXaxis()->SetRangeUser(-MaxEtaRange, MaxEtaRange);
  hCorr_merge->Draw("surf1fbb");
  
  //~~~~~~~~~~~phi merge flow projection~~~~~~~~~~~~~~~~~~~~~
  c_dphi_merge_flow = new TCanvas("c_dphi_merge_flow", "c_dphi_merge_flow", 600, 530);
  c_dphi_merge_flow->cd();
  
  Double_t etaMin_merge_flow = hCorr_merge->GetXaxis()->FindBin(etamin_flow);
  Double_t etaMax_merge_flow = hCorr_merge->GetXaxis()->FindBin(etamax_flow);
  
  hphi_proj_merge_flow = hCorr_merge->ProjectionY("hphi_proj_merge_flow", etaMin_merge_flow, etaMax_merge_flow);
  
  int nBins_eta_merge_flow = etaMax_merge_flow - etaMin_merge_flow + 1;
  hphi_proj_merge_flow->Scale(1./(nBins_eta_merge_flow));
  
  hphi_proj_merge_flow->SetMarkerStyle(kFullCircle);
  hphi_proj_merge_flow->SetMarkerColor(kBlue);
  hphi_proj_merge_flow->SetMarkerSize(1.5);
  
  hphi_proj_merge_flow->GetXaxis()->SetTitle("#Delta#varphi");
  hphi_proj_merge_flow->GetYaxis()->SetTitle("C_{2}^{Corr.}(#Delta#varphi)");
  hphi_proj_merge_flow->GetXaxis()->CenterTitle(1);
  hphi_proj_merge_flow->GetYaxis()->CenterTitle(1);
  
  hphi_proj_merge_flow->GetYaxis()->SetTitleFont(42);
  hphi_proj_merge_flow->GetYaxis()->SetTitleSize(0.05);
  hphi_proj_merge_flow->GetYaxis()->SetLabelSize(0.05);
  hphi_proj_merge_flow->GetYaxis()->SetTitleOffset(1.8);
  
  hphi_proj_merge_flow->GetXaxis()->SetTitleFont(42);
  hphi_proj_merge_flow->GetXaxis()->SetTitleSize(0.05);
  hphi_proj_merge_flow->GetXaxis()->SetLabelSize(0.05);
  hphi_proj_merge_flow->GetXaxis()->SetTitleOffset(0.9);
  
  hphi_proj_merge_flow->Draw("EP");
  
  fit_dphi_merge_flow = new TF1("fit_dphi_merge_flow", "[0]*(1.+2.0*([1]*cos(1.0*x) + [2]*cos(2.0*x) + [3]*cos(3.0*x) + [4]*cos(4.0*x) + [5]*cos(5.0*x) + [6]*cos(6.0*x)))", flow_cal_min , flow_cal_max);
  
  fit_dphi_merge_flow->SetLineColor(kRed);
  fit_dphi_merge_flow->SetParameter(0, 10.);
  fit_dphi_merge_flow->SetParameter(1, 1.);
  fit_dphi_merge_flow->SetParameter(2, 1.);
  fit_dphi_merge_flow->SetParameter(3, 1.);
  fit_dphi_merge_flow->SetParameter(4, 0.);
  fit_dphi_merge_flow->SetParameter(5, 0.);
  fit_dphi_merge_flow->SetParameter(6, 0.);
  
  
  hphi_proj_merge_flow->Fit(fit_dphi_merge_flow, "QSER", "", flow_cal_min, flow_cal_max);
  hphi_proj_merge_flow->Fit(fit_dphi_merge_flow, "QSER", "", flow_cal_min, flow_cal_max);
  hphi_proj_merge_flow->Fit(fit_dphi_merge_flow, "SER", "", flow_cal_min, flow_cal_max);
  
  double v2_merge_coff = fit_dphi_merge_flow->GetParameter(2);
  double v2_merge_coff_error = fit_dphi_merge_flow->GetParError(2);
  double v3_merge_coff = fit_dphi_merge_flow->GetParameter(3);
  double v3_merge_coff_error = fit_dphi_merge_flow->GetParError(3);
  
  double v2_merge = TMath::Sqrt(v2_merge_coff);
  double v2_merge_error = v2_merge_coff_error/(2.*v2_merge);
  
  double v3_merge = TMath::Sqrt(v3_merge_coff);
  double v3_merge_error = v3_merge_coff_error/(2.*v3_merge);
  
  std::cout<<"v2 and v3 merge : "<<(centmin+centmax)/2.<<"   "<<v2_merge<<"    "<<v2_merge_error<<"   "<<v3_merge<<"   "<<v3_merge_error<<std::endl;

  //***************************************************************************************************
  //~~~~~~~~~~~~~~~~~~~~Calculate the numerator of vn in different pT bin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //***************************************************************************************************
  
  for(int i = 2; i < 17; i++)
    {
      hSignal[i] = (TH2D*)dir1d->Get(Form("signal_all_ptbin%d_recocor", i));
      hMixed[i] = (TH2D*)dir2d->Get(Form("background_all_ptbin%d_recocor", i));
      hNtrig[i] = (TH1D*)dir3d->Get(Form("hMult_trg_ptbin%d", i));
      
      c_signal[i] = new TCanvas(Form("c_signal%d", i), Form("c_signal%d", i), 600, 530);
      c_mixed[i] = new TCanvas(Form("c_mixed%d", i), Form("c_mixed%d", i), 600, 530);
      c_corr[i] = new TCanvas(Form("c_corr%d", i), Form("c_corr%d", i), 600, 530);
      c_deta[i] = new TCanvas(Form("c_deta%d", i), Form("c_deta%d", i), 600, 530);
      c_dphi[i] = new TCanvas(Form("c_dphi%d", i), Form("c_dphi%d", i), 600, 530);
      c_dphi_flow[i] = new TCanvas(Form("c_dphi_flow%d", i), Form("c_dphi_flow%d", i), 600, 530);

      //~~~~~~~~~~~Signal~~~~~~~~~~~~~~~~
      c_signal[i]->cd();
      hSignal[i]->GetXaxis()->SetTitle("#Delta#eta");
      hSignal[i]->GetYaxis()->SetTitle("#Delta#varphi (rad)");
      hSignal[i]->GetZaxis()->SetTitle("C_{2}^{Signal}(#Delta#eta, #Delta#varphi)");

      hSignal[i]->GetXaxis()->CenterTitle(1);
      hSignal[i]->GetYaxis()->CenterTitle(1);
      hSignal[i]->GetZaxis()->CenterTitle(1);

      hSignal[i]->GetYaxis()->SetTitleSize(0.05);
      hSignal[i]->GetYaxis()->SetLabelSize(0.05);
      hSignal[i]->GetYaxis()->SetTitleOffset(1.9);
      
      hSignal[i]->GetXaxis()->SetTitleSize(0.05);
      hSignal[i]->GetXaxis()->SetLabelSize(0.05);
      hSignal[i]->GetXaxis()->SetTitleOffset(1.9);
      
      hSignal[i]->GetZaxis()->SetTitleSize(0.05);
      hSignal[i]->GetZaxis()->SetLabelSize(0.05);
      hSignal[i]->GetZaxis()->SetTitleOffset(1.9);
      
      hSignal[i]->GetXaxis()->SetNdivisions(505);
      hSignal[i]->GetYaxis()->SetNdivisions(505);
      hSignal[i]->GetZaxis()->SetNdivisions(505);
      
      //hSignal[i]->Scale(1./hNtrig[i]->GetBinContent(2));
      hSignal[i]->Scale(1./((hSignal[i]->GetXaxis()->GetBinWidth(1))*(hSignal[i]->GetYaxis()->GetBinWidth(1))));
      hSignal[i]->Draw("surf1fbb");
      
      //~~~~~~~~~~~Mixed~~~~~~~~~~~~~~~~
      c_mixed[i]->cd();
      hMixed[i]->GetXaxis()->SetTitle("#Delta#eta");
      hMixed[i]->GetYaxis()->SetTitle("#Delta#varphi (rad)");
      hMixed[i]->GetZaxis()->SetTitle("C_{2}^{Mixed}(#Delta#eta, #Delta#varphi)");

      hMixed[i]->GetXaxis()->CenterTitle(1);
      hMixed[i]->GetYaxis()->CenterTitle(1);
      hMixed[i]->GetZaxis()->CenterTitle(1);

      hMixed[i]->GetYaxis()->SetTitleSize(0.05);
      hMixed[i]->GetYaxis()->SetLabelSize(0.05);
      hMixed[i]->GetYaxis()->SetTitleOffset(1.9);
      
      hMixed[i]->GetXaxis()->SetTitleSize(0.05);
      hMixed[i]->GetXaxis()->SetLabelSize(0.05);
      hMixed[i]->GetXaxis()->SetTitleOffset(1.9);
      
      hMixed[i]->GetZaxis()->SetTitleSize(0.05);
      hMixed[i]->GetZaxis()->SetLabelSize(0.05);
      hMixed[i]->GetZaxis()->SetTitleOffset(1.9);
      
      hMixed[i]->GetXaxis()->SetNdivisions(505);
      hMixed[i]->GetYaxis()->SetNdivisions(505);
      hMixed[i]->GetZaxis()->SetNdivisions(505);

      //hMixed[i]->Scale(1./hNtrig[i]->GetBinContent(2));
      hMixed[i]->Scale(1./((hMixed[i]->GetXaxis()->GetBinWidth(1))*(hMixed[i]->GetYaxis()->GetBinWidth(1))));
      //hMixed[i]->Scale(1./hMixed[i]->GetBinContent(hMixed[i]->FindBin(0.,0.)));

      hMixed[i]->Draw("surf1fbb");

      //~~~~~~~~~~~correlation~~~~~~~~~~~~~~~~
      c_corr[i]->cd();
      hCorr[i] = (TH2D*)hSignal[i]->Clone(Form("hCorr_%d", i));
      hCorr[i]->Reset("ICSEM");
      hCorr[i]->Add(hSignal[i]);
      hCorr[i]->Divide(hMixed[i]);
      hCorr[i]->GetXaxis()->SetTitle("#Delta#eta");
      hCorr[i]->GetYaxis()->SetTitle("#Delta#varphi (rad)");
      hCorr[i]->GetZaxis()->SetTitle("C_{2}^{Corr.}(#Delta#eta, #Delta#varphi)");

      hCorr[i]->GetXaxis()->CenterTitle(1);
      hCorr[i]->GetYaxis()->CenterTitle(1);
      hCorr[i]->GetZaxis()->CenterTitle(1);

      hCorr[i]->GetYaxis()->SetTitleSize(0.05);
      hCorr[i]->GetYaxis()->SetLabelSize(0.05);
      hCorr[i]->GetYaxis()->SetTitleOffset(1.9);
      
      hCorr[i]->GetXaxis()->SetTitleSize(0.05);
      hCorr[i]->GetXaxis()->SetLabelSize(0.05);
      hCorr[i]->GetXaxis()->SetTitleOffset(1.9);
      
      hCorr[i]->GetZaxis()->SetTitleSize(0.05);
      hCorr[i]->GetZaxis()->SetLabelSize(0.05);
      hCorr[i]->GetZaxis()->SetTitleOffset(1.7);
      
      hCorr[i]->GetXaxis()->SetNdivisions(505);
      hCorr[i]->GetYaxis()->SetNdivisions(505);
      hCorr[i]->GetZaxis()->SetNdivisions(505);

      hCorr[i]->GetXaxis()->SetRangeUser(-MaxEtaRange, MaxEtaRange);
      hCorr[i]->Draw("surf1fbb");

      //~~~~~~~~~~~eta projection~~~~~~~~~~~~~~~~~~~~~
      c_deta[i]->cd();

      Double_t phiMin = hCorr[i]->GetYaxis()->FindBin(-phimax);
      Double_t phiMax = hCorr[i]->GetYaxis()->FindBin(phimax);
      heta_proj[i] = hCorr[i]->ProjectionX(Form("deta_Proj_%d", i), phiMin, phiMax);

      
      int nBins_phi = phiMax - phiMin + 1;
      heta_proj[i]->Scale(1./(nBins_phi));
      
      heta_proj[i]->SetMarkerStyle(kFullCircle);
      heta_proj[i]->SetMarkerColor(kBlue);
      heta_proj[i]->SetMarkerSize(1.5);

      heta_proj[i]->GetXaxis()->SetTitle("#Delta#eta");
      heta_proj[i]->GetYaxis()->SetTitle("C_{2}^{Corr.}(#Delta#eta)");
      heta_proj[i]->GetXaxis()->CenterTitle(1);
      heta_proj[i]->GetYaxis()->CenterTitle(1);

      heta_proj[i]->GetYaxis()->SetTitleFont(42);
      heta_proj[i]->GetYaxis()->SetTitleSize(0.05);
      heta_proj[i]->GetYaxis()->SetLabelSize(0.05);
      heta_proj[i]->GetYaxis()->SetTitleOffset(1.8);

      heta_proj[i]->GetXaxis()->SetTitleFont(42);
      heta_proj[i]->GetXaxis()->SetTitleSize(0.05);
      heta_proj[i]->GetXaxis()->SetLabelSize(0.05);
      heta_proj[i]->GetXaxis()->SetTitleOffset(0.9);
      
      heta_proj[i]->GetXaxis()->SetRangeUser(-MaxEtaRange, MaxEtaRange);
      heta_proj[i]->Draw("EP");

      //~~~~~~~~~~~phi projection~~~~~~~~~~~~~~~~~~~~~
      c_dphi[i]->cd();
      
      Double_t etaMin = hCorr[i]->GetXaxis()->FindBin(-etamax);
      Double_t etaMax = hCorr[i]->GetXaxis()->FindBin(etamax);

      hphi_proj[i] = hCorr[i]->ProjectionY(Form("dphi_Proj_%d", i), etaMin, etaMax);

      
      int nBins_eta = etaMax - etaMin + 1;
      hphi_proj[i]->Scale(1./(nBins_eta));
      
      hphi_proj[i]->SetMarkerStyle(kFullCircle);
      hphi_proj[i]->SetMarkerColor(kBlue);
      hphi_proj[i]->SetMarkerSize(1.5);

      hphi_proj[i]->GetXaxis()->SetTitle("#Delta#varphi");
      hphi_proj[i]->GetYaxis()->SetTitle("C_{2}^{Corr.}(#Delta#varphi)");
      hphi_proj[i]->GetXaxis()->CenterTitle(1);
      hphi_proj[i]->GetYaxis()->CenterTitle(1);

      hphi_proj[i]->GetYaxis()->SetTitleFont(42);
      hphi_proj[i]->GetYaxis()->SetTitleSize(0.05);
      hphi_proj[i]->GetYaxis()->SetLabelSize(0.05);
      hphi_proj[i]->GetYaxis()->SetTitleOffset(1.8);

      hphi_proj[i]->GetXaxis()->SetTitleFont(42);
      hphi_proj[i]->GetXaxis()->SetTitleSize(0.05);
      hphi_proj[i]->GetXaxis()->SetLabelSize(0.05);
      hphi_proj[i]->GetXaxis()->SetTitleOffset(0.9);

      hphi_proj[i]->Draw("EP");

      //~~~~~~~~~~~phi flow projection~~~~~~~~~~~~~~~~~~~~~
      c_dphi_flow[i]->cd();
      
      Double_t etaMinn_flow = hCorr[i]->GetXaxis()->FindBin(etamin_flow);
      Double_t etaMaxx_flow = hCorr[i]->GetXaxis()->FindBin(etamax_flow);

      hphi_proj_flow[i] = hCorr[i]->ProjectionY(Form("dphi_Proj_flow_%d", i), etaMinn_flow, etaMaxx_flow);

      
      int nBins_eta_flow = etaMaxx_flow - etaMinn_flow + 1;
      hphi_proj_flow[i]->Scale(1./(nBins_eta_flow));
      
      hphi_proj_flow[i]->SetMarkerStyle(kFullCircle);
      hphi_proj_flow[i]->SetMarkerColor(kBlue);
      hphi_proj_flow[i]->SetMarkerSize(1.5);

      hphi_proj_flow[i]->GetXaxis()->SetTitle("#Delta#varphi");
      hphi_proj_flow[i]->GetYaxis()->SetTitle("C_{2}^{Corr.}(#Delta#varphi)");
      hphi_proj_flow[i]->GetXaxis()->CenterTitle(1);
      hphi_proj_flow[i]->GetYaxis()->CenterTitle(1);

      hphi_proj_flow[i]->GetYaxis()->SetTitleFont(42);
      hphi_proj_flow[i]->GetYaxis()->SetTitleSize(0.05);
      hphi_proj_flow[i]->GetYaxis()->SetLabelSize(0.05);
      hphi_proj_flow[i]->GetYaxis()->SetTitleOffset(1.8);

      hphi_proj_flow[i]->GetXaxis()->SetTitleFont(42);
      hphi_proj_flow[i]->GetXaxis()->SetTitleSize(0.05);
      hphi_proj_flow[i]->GetXaxis()->SetLabelSize(0.05);
      hphi_proj_flow[i]->GetXaxis()->SetTitleOffset(0.9);

      hphi_proj_flow[i]->Draw("EP");

      fit_dphi_flow[i] = new TF1(Form("fit_dphi_flow_%d",i), "[0]*(1.+2.0*([1]*cos(1.0*x) + [2]*cos(2.0*x) + [3]*cos(3.0*x) + [4]*cos(4.0*x) + [5]*cos(5.0*x) + [6]*cos(6.0*x)))", flow_cal_min , flow_cal_max);
      
      fit_dphi_flow[i]->SetLineColor(kRed);
      fit_dphi_flow[i]->SetParameter(0, 10.);
      fit_dphi_flow[i]->SetParameter(1, 1.);
      fit_dphi_flow[i]->SetParameter(2, 1.);
      fit_dphi_flow[i]->SetParameter(3, 1.);
      fit_dphi_flow[i]->SetParameter(4, 0.);
      fit_dphi_flow[i]->SetParameter(5, 0.);
      fit_dphi_flow[i]->SetParameter(6, 0.);
      
      hphi_proj_flow[i]->Fit(fit_dphi_flow[i], "QSER", "", flow_cal_min, flow_cal_max);
      hphi_proj_flow[i]->Fit(fit_dphi_flow[i], "QSER", "", flow_cal_min, flow_cal_max);
      hphi_proj_flow[i]->Fit(fit_dphi_flow[i], "SER", "", flow_cal_min, flow_cal_max);

      double v2 = fit_dphi_flow[i]->GetParameter(2)/(TMath::Sqrt(v2_merge_coff));

      double v2_error = fabs(v2*TMath::Sqrt(pow((fit_dphi_flow[i]->GetParError(2)/fit_dphi_flow[i]->GetParameter(2)), 2) + pow((0.5*v2_merge_coff_error)/v2_merge_coff,2))); 
      
      //double v3 = fabs(fit_dphi_flow[i]->GetParameter(3))/(TMath::Sqrt(v3_merge_coff));
      double v3 = fit_dphi_flow[i]->GetParameter(3)/(TMath::Sqrt(v3_merge_coff));
      double v3_error = fabs(v3*TMath::Sqrt(pow((fit_dphi_flow[i]->GetParError(3)/fit_dphi_flow[i]->GetParameter(3)), 2) + pow((0.5*v3_merge_coff_error)/v3_merge_coff,2))); 
      
      double MpT = (pTAvg[i]+pTAvg[i+1])/2.;
      outfile << MpT <<"   "<< v2 <<"   "<<v2_error<<"    "<<v3<<"   "<<v3_error<<endl;

      //c_corr[i]->SaveAs(Form("../pdf_file/new_pdffile/vnpT_Corr_MergedTrack_pTbin_effCorr_%d_cent%d_%d.pdf", i, centmin, centmax));
      //c_dphi_flow[i]->SaveAs(Form("../pdf_file/new_pdffile/vnpT_DphiFit_MergedTrack_pTbin_effCorr_%d_cent%d_%d.pdf", i, centmin, centmax));
      
      //c_corr[i]->SaveAs(Form("../pdf_file/new_pdffile/vnpT_Corr_GeneralTrack_pTbin_effCorr_%d_cent%d_%d.pdf", i, centmin, centmax));
      //c_dphi_flow[i]->SaveAs(Form("../pdf_file/new_pdffile/vnpT_DphiFit_GeneralTrack_pTbin_effCorr_%d_cent%d_%d.pdf", i, centmin, centmax));
    }
						       
  /*
  //Save histograms in a root files
  TFile* fout = new TFile(Form("fout_PbPb_cent%d%d_1p0pttrg2p0_1p0ptass2p0_deleta2p0_delphi1p5_phiproj_modeta1p0_32bin_GEN.root", 20, 30),"RECREATE");
  hsignal_norm->Write();
  hmixingbkg_norm->Write();
  hcorr_norm->Write();
  hdiff->Write();
  hnew->Write();
  hnew_deleta->Write();
  hnew_delphi->Write();
  hphi->Write();
  heta->Write();
  fout->Close();
  */
}
