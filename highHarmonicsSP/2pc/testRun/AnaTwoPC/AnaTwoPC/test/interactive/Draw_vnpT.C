#include <TFile.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TFrame.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TGraph.h>
#include <iostream>
#include <TAttMarker.h>
#include <string>

void Draw_vnpT()
{
  gStyle->SetErrorX(0);
  gStyle->SetNdivisions(505, "y");
  
  const Int_t multbin = 10;
  const Int_t multbin1 = 17;


  const int nfile = 11;

  const char* cent[nfile] = {"0-5%", "5-10%", "10-15%", "15-20%", "20-25%", "25-30%", "30-35%", "35-40%", "40-50%", "50-60%", "60-70%"};
  const char* centt[nfile] = {"0_5", "5_10", "10_15", "15_20", "20_25", "25_30", "30_35", "35_40", "40_50", "50_60", "60_70"};

  //const char* cent[nfile] = {"0-10%", "10-30%", "30-50%", "50-80%"};
  //const char* centt[nfile] = {"0_10", "10_30", "30_50", "50_80"};

  TFile * XeXe_v2file = new TFile("XeXe_v2pT.root");
  TDirectoryFile * XeXe_v2dir = (TDirectoryFile*)XeXe_v2file->Get("Figure 1a");

  TFile * XeXe_v3file = new TFile("XeXe_v3pT.root");
  TDirectoryFile * XeXe_v3dir = (TDirectoryFile*)XeXe_v3file->Get("Figure 2a");

  TFile * PbPb_v2file = new TFile("PbPb5TeV_v2pT.root");
  TDirectoryFile * PbPb_v2dir = (TDirectoryFile*)PbPb_v2file->Get("Figure 6");

  TFile * PbPb_v3file = new TFile("PbPb5TeV_v3pT.root");
  TDirectoryFile * PbPb_v3dir = (TDirectoryFile*)PbPb_v3file->Get("Figure 7");

  TGraphAsymmErrors* XeXe_v2[nfile];
  TGraphAsymmErrors* XeXe_v3[nfile];

  TGraphAsymmErrors* PbPb_v2[nfile];
  TGraphAsymmErrors* PbPb_v3[nfile];

  TCanvas* c_v2[nfile];
  
  TGraphErrors* gr_v2lm[nfile];
  TGraphErrors* gr_v3lm[nfile];
  
  TGraphErrors* gr_v2lm1[nfile];
  TGraphErrors* gr_v3lm1[nfile];

  TGraphErrors* gr_v2lm2[nfile];
  TGraphErrors* gr_v3lm2[nfile];

  TGraphErrors* gr_v2lm_eff[nfile];
  TGraphErrors* gr_v3lm_eff[nfile];
  
  TGraphErrors* gr_v2lm1_eff[nfile];
  TGraphErrors* gr_v3lm1_eff[nfile];

  
  ifstream file[nfile];
  ifstream file1[nfile];
  ifstream file2[nfile];

  ifstream file_eff[nfile];
  ifstream file1_eff[nfile];

  
  /*
  file[0].open("VnpT_coff_DATA_MergedTrack_0_10.dat");
  file[1].open("VnpT_coff_DATA_MergedTrack_10_30.dat");
  file[2].open("VnpT_coff_DATA_MergedTrack_30_50.dat");
  file[3].open("VnpT_coff_DATA_MergedTrack_50_80.dat");

  file1[0].open("VnpT_coff_DATA_GeneralTrack_0_10.dat");
  file1[1].open("VnpT_coff_DATA_GeneralTrack_10_30.dat");
  file1[2].open("VnpT_coff_DATA_GeneralTrack_30_50.dat");
  file1[3].open("VnpT_coff_DATA_GeneralTrack_50_80.dat");
  
  file_eff[0].open("VnpT_coff_DATA_MergedTrack_effCorr_0_10.dat");
  file_eff[1].open("VnpT_coff_DATA_MergedTrack_effCorr_10_30.dat");
  file_eff[2].open("VnpT_coff_DATA_MergedTrack_effCorr_30_50.dat");
  file_eff[3].open("VnpT_coff_DATA_MergedTrack_effCorr_50_80.dat");
  */

  /*
  file1_eff[0].open("VnpT_coff_DATA_GeneralTrack_effCorr_0_5.dat");
  file1_eff[1].open("VnpT_coff_DATA_GeneralTrack_effCorr_5_10.dat");
  file1_eff[2].open("VnpT_coff_DATA_GeneralTrack_effCorr_10_15.dat");
  file1_eff[3].open("VnpT_coff_DATA_GeneralTrack_effCorr_15_20.dat");
  file1_eff[4].open("VnpT_coff_DATA_GeneralTrack_effCorr_20_25.dat");
  file1_eff[5].open("VnpT_coff_DATA_GeneralTrack_effCorr_25_30.dat");
  file1_eff[6].open("VnpT_coff_DATA_GeneralTrack_effCorr_30_35.dat");
  file1_eff[7].open("VnpT_coff_DATA_GeneralTrack_effCorr_35_40.dat");
  file1_eff[8].open("VnpT_coff_DATA_GeneralTrack_effCorr_40_50.dat");
  file1_eff[9].open("VnpT_coff_DATA_GeneralTrack_effCorr_50_60.dat");
  file1_eff[10].open("VnpT_coff_DATA_GeneralTrack_effCorr_60_70.dat");
  */

  /*
  file1_eff[0].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent0_5.dat");
  file1_eff[1].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent5_10.dat");
  file1_eff[2].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent10_15.dat");
  file1_eff[3].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent15_20.dat");
  file1_eff[4].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent20_25.dat");
  file1_eff[5].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent25_30.dat");
  file1_eff[6].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent30_35.dat");
  file1_eff[7].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent34_40.dat");
  file1_eff[8].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent40_50.dat");
  file1_eff[9].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent50_60.dat");
  file1_eff[10].open("VnpT_coff_DATA_GeneralTrack_WJSON_NeweffCorr_pTass1_3_Cent60_70.dat");
  */
  /*
  file1_eff[0].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent0_5.dat");
  file1_eff[1].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent5_10.dat");
  file1_eff[2].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent10_15.dat");
  file1_eff[3].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent15_20.dat");
  file1_eff[4].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent20_25.dat");
  file1_eff[5].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent25_30.dat");
  file1_eff[6].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent30_35.dat");
  file1_eff[7].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent35_40.dat");
  file1_eff[8].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent40_50.dat");
  file1_eff[9].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent50_60.dat");
  file1_eff[10].open("VnpT_coff_DATA_GeneralTrack_WJSON_Evts_NeweffCorr_pTass1_3_Cent60_70.dat");
  */

  
  file1_eff[0].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent0_5.dat");
  file1_eff[1].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent5_10.dat");
  file1_eff[2].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent10_15.dat");
  file1_eff[3].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent15_20.dat");
  file1_eff[4].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent20_25.dat");
  file1_eff[5].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent25_30.dat");
  file1_eff[6].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent30_35.dat");
  file1_eff[7].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent35_40.dat");
  file1_eff[8].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent40_50.dat");
  file1_eff[9].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent50_60.dat");
  file1_eff[10].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_NeweffCorr_pTass1_3_Cent60_70.dat");
  

  /*
  file1_eff[0].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent0_5.dat");
  file1_eff[1].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent5_10.dat");
  file1_eff[2].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent10_15.dat");
  file1_eff[3].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent15_20.dat");
  file1_eff[4].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent20_25.dat");
  file1_eff[5].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent25_30.dat");
  file1_eff[6].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent30_35.dat");
  file1_eff[7].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent35_40.dat");
  file1_eff[8].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent40_50.dat");
  file1_eff[9].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent50_60.dat");
  file1_eff[10].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_ExcludeMiddleBin_NeweffCorr_pTass1_3_Cent60_70.dat");
  */
  /*
  file1_eff[0].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent0_5.dat");
  file1_eff[1].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent5_10.dat");
  file1_eff[2].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent10_15.dat");
  file1_eff[3].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent15_20.dat");
  file1_eff[4].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent20_25.dat");
  file1_eff[5].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent25_30.dat");
  file1_eff[6].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent30_35.dat");
  file1_eff[7].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent35_40.dat");
  file1_eff[8].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent40_50.dat");
  file1_eff[9].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent50_60.dat");
  file1_eff[10].open("VnpT_coff_DATA_GeneralTrack_WJSON_AllEvts_BothSide_NeweffCorr_pTass1_3_Cent60_70.dat");
  */
  /*
  file2[0].open("VnpT_coff_DATA_GeneralTrack_0_10.dat");
  file2[1].open("VnpT_coff_DATA_GeneralTrack_10_30.dat");
  file2[2].open("VnpT_coff_DATA_GeneralTrack_30_50.dat");
  file2[3].open("VnpT_coff_DATA_GeneralTrack_50_80.dat");
  */
  for(int i = 0; i< nfile; i++)
    {

      Double_t Ntrk[multbin];
      Double_t Ntrk_E[multbin];
      Double_t v2_LM[multbin];
      Double_t v2_LM_E[multbin];
      Double_t v3_LM[multbin];
      Double_t v3_LM_E[multbin];

      Double_t Ntrk1[multbin1];
      Double_t Ntrk_E1[multbin1];
      Double_t v2_LM1[multbin1];
      Double_t v2_LM_E1[multbin1];
      Double_t v3_LM1[multbin1];
      Double_t v3_LM_E1[multbin1];

      Double_t Ntrk_eff[multbin];
      Double_t Ntrk_E_eff[multbin];
      Double_t v2_LM_eff[multbin];
      Double_t v2_LM_E_eff[multbin];
      Double_t v3_LM_eff[multbin];
      Double_t v3_LM_E_eff[multbin];

      Double_t Ntrk1_eff[multbin1];
      Double_t Ntrk_E1_eff[multbin1];
      Double_t v2_LM1_eff[multbin1];
      Double_t v2_LM_E1_eff[multbin1];
      Double_t v3_LM1_eff[multbin1];
      Double_t v3_LM_E1_eff[multbin1];

      Double_t Ntrk2[multbin1];
      Double_t Ntrk_E2[multbin1];
      Double_t v2_LM2[multbin1];
      Double_t v2_LM_E2[multbin1];
      Double_t v3_LM2[multbin1];
      Double_t v3_LM_E2[multbin1];

      /*
      for(int j = 0; j < multbin; j++)
	{
	  file[i] >> Ntrk[j] >> v2_LM[j] >> v2_LM_E[j] >> v3_LM[j] >> v3_LM_E[j];
	  Ntrk_E[j] = 0.;

	  file_eff[i] >> Ntrk_eff[j] >> v2_LM_eff[j] >> v2_LM_E_eff[j] >> v3_LM_eff[j] >> v3_LM_E_eff[j];
	  Ntrk_E_eff[j] = 0.;
	}
      */
      for(int k = 0; k < multbin1; k++)
	{
	  //file1[i] >> Ntrk1[k] >> v2_LM1[k] >> v2_LM_E1[k] >> v3_LM1[k] >> v3_LM_E1[k];
	  //Ntrk_E1[k] = 0.;

	  file1_eff[i] >> Ntrk1_eff[k] >> v2_LM1_eff[k] >> v2_LM_E1_eff[k] >> v3_LM1_eff[k] >> v3_LM_E1_eff[k];
	  Ntrk_E1_eff[k] = 0.;

	  //file2[i] >> Ntrk2[k] >> v2_LM2[k] >> v2_LM_E2[k] >> v3_LM2[k] >> v3_LM_E2[k];
	  //Ntrk_E2[k] = 0.;
	}
      
      c_v2[i] = new TCanvas(Form("cv2_%d", i),Form("cv2_%d", i),500,450);
      c_v2[i]->SetFrameLineWidth(2);
      c_v2[i]->SetFrameBorderMode(0);
      c_v2[i]->SetLeftMargin(0.15);
      c_v2[i]->SetBottomMargin(0.15);
      c_v2[i]->SetRightMargin(0.05);
      c_v2[i]->DrawFrame(0., 0.0, 10., 0.7);
      c_v2[i]->SetTickx();
      c_v2[i]->SetTicky();

      /*
      gr_v2lm1[i] = new TGraphErrors(multbin1, Ntrk1, v2_LM1, Ntrk_E1,  v2_LM_E1);
      gr_v2lm1[i]->SetMarkerStyle(kOpenStar);
      gr_v2lm1[i]->SetMarkerSize(1.2);
      gr_v2lm1[i]->SetMarkerColor(kRed);
      gr_v2lm1[i]->SetLineColor(kRed);
      gr_v2lm1[i]->SetLineWidth(1);
      gr_v2lm1[i]->SetLineStyle(1);
      gr_v2lm1[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm1[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm1[i]->SetMaximum(0.35);
      gr_v2lm1[i]->SetMinimum(-0.03);
      gr_v2lm1[i]->GetXaxis()->SetRangeUser(0.1, 10.);
      gr_v2lm1[i]->SetTitle(0);
      //gr_v2lm1[i]->Draw("AP");
      */
      
      gr_v2lm1_eff[i] = new TGraphErrors(multbin1, Ntrk1_eff, v2_LM1_eff, Ntrk_E1_eff,  v2_LM_E1_eff);
      gr_v2lm1_eff[i]->SetMarkerStyle(kOpenCircle);
      gr_v2lm1_eff[i]->SetMarkerSize(1.2);
      gr_v2lm1_eff[i]->SetMarkerColor(kRed);
      gr_v2lm1_eff[i]->SetLineColor(kRed);
      gr_v2lm1_eff[i]->SetLineWidth(1);
      gr_v2lm1_eff[i]->SetLineStyle(1);
      gr_v2lm1_eff[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm1_eff[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm1_eff[i]->SetMaximum(0.35);
      gr_v2lm1_eff[i]->SetMinimum(-0.03);
      gr_v2lm1_eff[i]->GetXaxis()->SetRangeUser(0.1, 7.);
      gr_v2lm1_eff[i]->SetTitle(0);
      gr_v2lm1_eff[i]->Draw("AP");

      XeXe_v2[i] = (TGraphAsymmErrors*)XeXe_v2dir->Get(Form("Graph1D_y%d", i+1));
      for(int k = 1; k <= 17; k++)
	{
	  XeXe_v2[i]->SetPointEXlow(k,0);
	  XeXe_v2[i]->SetPointEXhigh(k,0);
	}
      XeXe_v2[i]->SetMarkerStyle(kOpenStar);
      XeXe_v2[i]->SetMarkerSize(1.3);
      XeXe_v2[i]->SetMarkerColor(kGreen+3);
      XeXe_v2[i]->SetLineColor(kGreen+3);
      XeXe_v2[i]->SetLineWidth(1);
      XeXe_v2[i]->SetLineStyle(1);
      XeXe_v2[i]->Draw("PSAME");

      PbPb_v2[i] = (TGraphAsymmErrors*)PbPb_v2dir->Get(Form("Graph1D_y%d", i+1));
      for(int k = 1; k <= 17; k++)
	{
	  PbPb_v2[i]->SetPointEXlow(k,0);
	  PbPb_v2[i]->SetPointEXhigh(k,0);
	}
      PbPb_v2[i]->SetMarkerStyle(26);
      PbPb_v2[i]->SetMarkerSize(1.3);
      PbPb_v2[i]->SetMarkerColor(kAzure+2);
      PbPb_v2[i]->SetLineColor(kAzure+2);
      PbPb_v2[i]->SetLineWidth(1);
      PbPb_v2[i]->SetLineStyle(1);
      PbPb_v2[i]->Draw("PSAME");
      /*
      gr_v2lm2[i] = new TGraphErrors(multbin1, Ntrk2, v2_LM2, Ntrk_E2,  v2_LM_E2);
      gr_v2lm2[i]->SetMarkerStyle(kFullSquare);
      gr_v2lm2[i]->SetMarkerSize(1.1);
      gr_v2lm2[i]->SetMarkerColor(kGreen+3);
      gr_v2lm2[i]->SetLineColor(kGreen+3);
      gr_v2lm2[i]->SetLineWidth(1);
      gr_v2lm2[i]->SetLineStyle(1);
      gr_v2lm2[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm2[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm2[i]->SetMaximum(0.35);
      gr_v2lm2[i]->SetMinimum(-0.03);
      gr_v2lm2[i]->SetTitle(0);
      //gr_v2lm2[i]->Draw("P");
    
      gr_v2lm[i] = new TGraphErrors(multbin, Ntrk, v2_LM, Ntrk_E,  v2_LM_E);
      gr_v2lm[i]->SetMarkerStyle(kOpenCircle);
      gr_v2lm[i]->SetMarkerSize(1.1);
      gr_v2lm[i]->SetMarkerColor(kRed);
      gr_v2lm[i]->SetLineColor(kRed);
      gr_v2lm[i]->SetLineWidth(1);
      gr_v2lm[i]->SetLineStyle(1);
      gr_v2lm[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm[i]->SetMaximum(0.3);
      gr_v2lm[i]->SetMinimum(-0.03);
      gr_v2lm[i]->SetTitle(0);
      //gr_v2lm[i]->Draw("PSAME");
      
      gr_v2lm_eff[i] = new TGraphErrors(multbin, Ntrk, v2_LM, Ntrk_E,  v2_LM_E);
      gr_v2lm_eff[i]->SetMarkerStyle(kOpenCircle);
      gr_v2lm_eff[i]->SetMarkerSize(1.1);
      gr_v2lm_eff[i]->SetMarkerColor(kGreen+3);
      gr_v2lm_eff[i]->SetLineColor(kGreen+3);
      gr_v2lm_eff[i]->SetLineWidth(1);
      gr_v2lm_eff[i]->SetLineStyle(1);
      gr_v2lm_eff[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm_eff[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm_eff[i]->SetMaximum(0.3);
      gr_v2lm_eff[i]->SetMinimum(-0.03);
      gr_v2lm_eff[i]->GetXaxis()->SetRangeUser(0.1, 10.);
      gr_v2lm_eff[i]->SetTitle(0);
      gr_v2lm_eff[i]->Draw("AP");
      */
      
      TLine* t1 = new TLine();
      t1->SetLineStyle(1);
      t1->SetLineColor(kBlack);
      
      /*
      gr_v3lm1[i] = new TGraphErrors(multbin1, Ntrk1, v3_LM1, Ntrk_E1,  v3_LM_E1);
      gr_v3lm1[i]->SetMarkerStyle(kOpenStar);
      gr_v3lm1[i]->SetMarkerSize(1.2);
      gr_v3lm1[i]->SetMarkerColor(kBlue);
      gr_v3lm1[i]->SetLineColor(kBlue);
      gr_v3lm1[i]->SetLineWidth(1);
      gr_v3lm1[i]->SetLineStyle(1);
      gr_v3lm1[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v3lm1[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v3lm1[i]->SetMaximum(0.3);
      gr_v3lm1[i]->SetMinimum(-0.03);
      gr_v3lm1[i]->SetTitle(0);
      //gr_v3lm1[i]->Draw("PSAME");
      */
      
      gr_v3lm1_eff[i] = new TGraphErrors(multbin1, Ntrk1_eff, v3_LM1_eff, Ntrk_E1_eff,  v3_LM_E1_eff);
      gr_v3lm1_eff[i]->SetMarkerStyle(kOpenSquare);
      gr_v3lm1_eff[i]->SetMarkerSize(1.1);
      gr_v3lm1_eff[i]->SetMarkerColor(kBlue);
      gr_v3lm1_eff[i]->SetLineColor(kBlue);
      gr_v3lm1_eff[i]->SetLineWidth(1);
      gr_v3lm1_eff[i]->SetLineStyle(1);
      gr_v3lm1_eff[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v3lm1_eff[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v3lm1_eff[i]->SetMaximum(0.3);
      gr_v3lm1_eff[i]->SetMinimum(-0.03);
      gr_v3lm1_eff[i]->SetTitle(0);
      gr_v3lm1_eff[i]->Draw("PSAME");


      XeXe_v3[i] = (TGraphAsymmErrors*)XeXe_v3dir->Get(Form("Graph1D_y%d", i+1));
      for(int k = 1; k <= 17; k++)
        {
          XeXe_v3[i]->SetPointEXlow(k,0);
          XeXe_v3[i]->SetPointEXhigh(k,0);
        }
      XeXe_v3[i]->SetMarkerStyle(27);
      XeXe_v3[i]->SetMarkerSize(1.6);
      XeXe_v3[i]->SetMarkerColor(kMagenta+3);
      XeXe_v3[i]->SetLineColor(kMagenta+3);
      XeXe_v3[i]->SetLineWidth(1);
      XeXe_v3[i]->SetLineStyle(1);
      XeXe_v3[i]->Draw("PSAME");

      PbPb_v3[i] = (TGraphAsymmErrors*)PbPb_v3dir->Get(Form("Graph1D_y%d", i+1));
      for(int k = 1; k <= 17; k++)
	{
	  PbPb_v3[i]->SetPointEXlow(k,0);
	  PbPb_v3[i]->SetPointEXhigh(k,0);
	}
      PbPb_v3[i]->SetMarkerStyle(28);
      PbPb_v3[i]->SetMarkerSize(1.3);
      PbPb_v3[i]->SetMarkerColor(kBlack);
      PbPb_v3[i]->SetLineColor(kBlack);
      PbPb_v3[i]->SetLineWidth(1);
      PbPb_v3[i]->SetLineStyle(1);
      PbPb_v3[i]->Draw("PSAME");
      /*
      gr_v3lm[i] = new TGraphErrors(multbin, Ntrk, v3_LM, Ntrk_E,  v3_LM_E);
      gr_v3lm[i]->SetMarkerStyle(kOpenCircle);
      gr_v3lm[i]->SetMarkerSize(1.1);
      gr_v3lm[i]->SetMarkerColor(kBlue);
      gr_v3lm[i]->SetLineColor(kBlue);
      gr_v3lm[i]->SetLineWidth(1);
      gr_v3lm[i]->SetLineStyle(1);
      gr_v3lm[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v3lm[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v3lm[i]->SetMaximum(0.3);
      gr_v3lm[i]->SetMinimum(-0.03);
      gr_v3lm[i]->SetTitle(0);
      //gr_v3lm[i]->Draw("PSAME");
      
      gr_v3lm_eff[i] = new TGraphErrors(multbin, Ntrk_eff, v3_LM_eff, Ntrk_E_eff,  v3_LM_E_eff);
      gr_v3lm_eff[i]->SetMarkerStyle(kOpenCircle);
      gr_v3lm_eff[i]->SetMarkerSize(1.1);
      gr_v3lm_eff[i]->SetMarkerColor(kMagenta+1);
      gr_v3lm_eff[i]->SetLineColor(kMagenta+1);
      gr_v3lm_eff[i]->SetLineWidth(1);
      gr_v3lm_eff[i]->SetLineStyle(1);
      gr_v3lm_eff[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v3lm_eff[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v3lm_eff[i]->SetMaximum(0.3);
      gr_v3lm_eff[i]->SetMinimum(-0.03);
      gr_v3lm_eff[i]->SetTitle(0);
      gr_v3lm_eff[i]->Draw("AP");
      */
      
      TLine* t2 = new TLine(0., 0., 10., 0.);
      t2->SetLineStyle(7);
      t2->SetLineColor(kBlack);
      t2->Draw("SAME");
      
      TLatex *   v2_tex = new TLatex(0.95,0.9406452,"PbPb, #sqrt{S_{NN}} = 5.36 TeV");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(32);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.05);
      v2_tex->SetLineWidth(4);
      v2_tex->Draw();
      v2_tex = new TLatex(0.45,0.9406452,"#bf{CMS} #it{Preliminary}");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(32);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.05);
      v2_tex->SetLineWidth(4);
      v2_tex->Draw();
      
      v2_tex = new TLatex(0.19,0.7, (cent[i]));
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(12);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.06);
      v2_tex->SetLineWidth(2);
      v2_tex->Draw();
      v2_tex = new TLatex(0.6,0.77,"2 < #Delta#eta < 4");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(12);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.06);
      v2_tex->SetLineWidth(2);
      //v2_tex->Draw();
      v2_tex = new TLatex(0.64,0.05,"p_{T} (GeV)");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(32);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.065);
      v2_tex->SetLineWidth(2);
      v2_tex->Draw();
      v2_tex = new TLatex(0.032,0.6,"v_{n}");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(32);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.065);
      v2_tex->SetTextAngle(90);
      v2_tex->SetLineWidth(2);
      v2_tex->Draw();

      TLine* t1_leg = new TLine();
      t1_leg->SetLineStyle(1);
      t1_leg->SetLineWidth(4);
      t1_leg->SetLineColor(kRed);

      TLine* t2_leg = new TLine();
      t2_leg->SetLineStyle(1);
      t2_leg->SetLineWidth(4);
      t2_leg->SetLineColor(kBlue);

      TLine* t1_leg_eff = new TLine();
      t1_leg_eff->SetLineStyle(1);
      t1_leg_eff->SetLineWidth(4);
      t1_leg_eff->SetLineColor(kGreen+3);

      TLine* t2_leg_eff = new TLine();
      t2_leg_eff->SetLineStyle(1);
      t2_leg_eff->SetLineWidth(4);
      t2_leg_eff->SetLineColor(kMagenta+1);
      
      TLegend *leg_1 = new TLegend(0.18,0.75,0.37,0.89,NULL,"brNDC");
      //TLegend *leg_1 = new TLegend(0.18,0.68,0.4,0.88,NULL,"brNDC");
      leg_1->SetBorderSize(1);
      leg_1->SetLineColor(1);
      leg_1->SetLineStyle(1);
      leg_1->SetLineWidth(0);
      leg_1->SetFillColor(0);
      leg_1->SetTextSize(0.05);
      leg_1->SetFillStyle(1001);
      //leg_1->AddEntry(t1_leg,"v_{2} (|#Delta#eta| > 2)","l");
      //leg_1->AddEntry(t2_leg,"v_{3} (|#Delta#eta| > 2)","l");
      //leg_1->AddEntry(t1_leg_eff,"v_{2} (eff corr., |#Delta#eta| > 2)","l");
      //leg_1->AddEntry(t2_leg_eff,"v_{3} (eff corr., |#Delta#eta| > 2)","l");
      leg_1->AddEntry(gr_v2lm1_eff[i],"v_{2} (|#Delta#eta| > 2)","ep");
      leg_1->AddEntry(gr_v3lm1_eff[i],"v_{3} (|#Delta#eta| > 2)","ep");
      //leg_1->AddEntry(gr_v2lm2[i],"v_{2} {4}","elp");
      leg_1->Draw("SAME");


      TLegend *leg_1_XeXe = new TLegend(0.55,0.62,0.75,0.89,NULL,"brNDC");
      leg_1_XeXe->SetBorderSize(1);
      leg_1_XeXe->SetLineColor(1);
      leg_1_XeXe->SetLineStyle(1);
      leg_1_XeXe->SetLineWidth(0);
      leg_1_XeXe->SetFillColor(0);
      leg_1_XeXe->SetTextSize(0.05);
      leg_1_XeXe->SetFillStyle(1001);
      leg_1_XeXe->AddEntry(XeXe_v2[i],"v_{2} (XeXe 5.44 TeV)","ep");
      leg_1_XeXe->AddEntry(XeXe_v3[i],"v_{3} (XeXe 5.44 TeV)","ep");
      leg_1_XeXe->AddEntry(PbPb_v2[i],"v_{2} (PbPb 5.02 TeV)","ep");
      leg_1_XeXe->AddEntry(PbPb_v3[i],"v_{3} (PbPb 5.02 TeV)","ep");
      leg_1_XeXe->Draw("SAME");

      TMarker* m1_leg = new TMarker();
      m1_leg->SetMarkerStyle(kOpenCircle);
      m1_leg->SetMarkerColor(kBlack);

      TMarker* m2_leg = new TMarker();
      m2_leg->SetMarkerStyle(kOpenStar);
      m2_leg->SetMarkerSize(1.2);
      m2_leg->SetMarkerColor(kBlack);
      
      TLegend *leg_2 = new TLegend(0.6,0.65,0.7,0.8,NULL,"brNDC");
      leg_2->SetBorderSize(1);
      leg_2->SetLineColor(1);
      leg_2->SetLineStyle(1);
      leg_2->SetLineWidth(0);
      leg_2->SetFillColor(0);
      leg_2->SetTextSize(0.05);
      leg_2->SetFillStyle(1001);
      leg_2->AddEntry(m2_leg,"General tracks","ep");
      leg_2->AddEntry(m1_leg,"Merged tracks","ep");
      //leg_2->Draw("SAME");
      
      //c_v2[i]->SaveAs(Form("../pdf_file/new_pdffile/Charge_Hadron_VnpT_PbPb_XeXe_EffCorr_cent_%s.pdf", centt[i]));
      //c_v2[i]->SaveAs(Form("../pdf_file/new_pdffile/Charge_Hadron_VnpT_PbPb_XeXe_NewEffCorr_WJSON_cent_%s.png", centt[i]));
      c_v2[i]->SaveAs(Form("../pdf_file/new_pdffile/Charge_Hadron_VnpT_PbPb_XeXe_NewEffCorr_WJSON_AllEvts_RangeUpto7GeV_cent_%s.png", centt[i]));
    }
}
