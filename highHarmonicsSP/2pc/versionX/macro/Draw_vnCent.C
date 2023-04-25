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

void Draw_vnCent()
{

  gStyle->SetNdivisions(505, "y");
  
  const Int_t multbin = 12;


  const int nfile = 1;

  const char* cent[nfile] = {"1 < p_{T} < 3 GeV"}; 
  const char* centt[nfile] = {"1_3"}; 
    
  TCanvas* c_v2[nfile];
  TCanvas* c_v4_v2_ratio[nfile];
  
  TGraphErrors* gr_v2lm1[nfile];
  TGraphErrors* gr_v3lm1[nfile];
  TGraphErrors* gr_v2lm2[nfile];
  TGraphErrors* gr_v3lm2[nfile];
  TGraphErrors* gr_v2lm3[nfile];
  TGraphErrors* gr_v3lm3[nfile];
  TGraphErrors* gr_v2lm4[nfile];
  TGraphErrors* gr_v3lm4[nfile];

  TGraphErrors* gr_v2_v4_ratio[nfile];
  
  ifstream file1[nfile];
  ifstream file2[nfile];
  ifstream file3[nfile];
  ifstream file4[nfile];

  file1[0].open("Vn_coff_cent_pT0p5to3.dat");
  file2[0].open("Vn_coff_cent_pT0p5to3_DATA.dat");
  file3[0].open("Vn_coff_effCorr_cent_pT0p5to3_DATA.dat");
  file4[0].open("Vn4_coff_cent_pT0p5to3_DATA.dat");
  
  for(int i = 0; i< nfile; i++)
    {
      Double_t Ntrk1[multbin];
      Double_t Ntrk_E1[multbin];
      Double_t v2_LM1[multbin];
      Double_t v2_LM_E1[multbin];
      Double_t v2_ALM1[multbin];
      Double_t v2_ALM_E1[multbin];
      Double_t v3_LM1[multbin];
      Double_t v3_LM_E1[multbin];
      Double_t v3_ALM1[multbin];
      Double_t v3_ALM_E1[multbin];

      Double_t Ntrk2[multbin];
      Double_t Ntrk_E2[multbin];
      Double_t v2_LM2[multbin];
      Double_t v2_LM_E2[multbin];
      Double_t v2_ALM2[multbin];
      Double_t v2_ALM_E2[multbin];
      Double_t v3_LM2[multbin];
      Double_t v3_LM_E2[multbin];
      Double_t v3_ALM2[multbin];
      Double_t v3_ALM_E2[multbin];

      Double_t Ntrk3[multbin];
      Double_t Ntrk_E3[multbin];
      Double_t v2_LM3[multbin];
      Double_t v2_LM_E3[multbin];
      Double_t v2_ALM3[multbin];
      Double_t v2_ALM_E3[multbin];
      Double_t v3_LM3[multbin];
      Double_t v3_LM_E3[multbin];
      Double_t v3_ALM3[multbin];
      Double_t v3_ALM_E3[multbin];

      Double_t Ntrk4[multbin];
      Double_t Ntrk_E4[multbin];
      Double_t v2_LM4[multbin];
      Double_t v2_LM_E4[multbin];
      Double_t v2_ALM4[multbin];
      Double_t v2_ALM_E4[multbin];
      Double_t v3_LM4[multbin];
      Double_t v3_LM_E4[multbin];
      Double_t v3_ALM4[multbin];
      Double_t v3_ALM_E4[multbin];

      Double_t v24_v22_ratio[multbin];
      Double_t v24_v22_ratio_err[multbin];
      
      for(int j = 0; j < multbin; j++)
	{
	  file1[i] >> Ntrk1[j] >> v2_LM1[j] >> v2_LM_E1[j] >> v3_LM1[j] >> v3_LM_E1[j];
	  Ntrk_E1[i] = 0.;

	  file2[i] >> Ntrk2[j] >> v2_LM2[j] >> v2_LM_E2[j] >> v3_LM2[j] >> v3_LM_E2[j];
	  Ntrk_E2[i] = 0.;
	  
	  file3[i] >> Ntrk3[j] >> v2_LM3[j] >> v2_LM_E3[j] >> v3_LM3[j] >> v3_LM_E3[j];
	  Ntrk_E3[i] = 0.;
	  
	  
	  file4[i] >> Ntrk4[j] >> v2_LM4[j] >> v2_LM_E4[j] >> v3_LM4[j] >> v3_LM_E4[j];
	  Ntrk_E3[i] = 0.;

	  v24_v22_ratio[j] = v2_LM4[j]/v2_LM2[j];

	  v24_v22_ratio_err[j] = (TMath::Sqrt((pow(v2_LM_E4[j]/v2_LM4[j],2)) + (pow(v2_LM_E2[j]/v2_LM2[j],2))))*fabs(v2_LM4[j]/v2_LM2[j]);
	  
	}

      c_v2[i] = new TCanvas(Form("cv2_%d", i),Form("cv2_%d", i),500,450);
      c_v2[i]->SetFrameLineWidth(2);
      c_v2[i]->SetFrameBorderMode(0);
      c_v2[i]->SetLeftMargin(0.15);
      c_v2[i]->SetBottomMargin(0.15);
      c_v2[i]->SetRightMargin(0.05);
      c_v2[i]->DrawFrame(1.0, 0.0, 70, 0.2);
      c_v2[i]->SetTickx();
      c_v2[i]->SetTicky();

      gr_v2lm1[i] = new TGraphErrors(multbin, Ntrk1, v2_LM1, Ntrk_E1,  v2_LM_E1);
      gr_v2lm1[i]->SetMarkerStyle(kOpenCircle);
      gr_v2lm1[i]->SetMarkerSize(1.1);
      gr_v2lm1[i]->SetMarkerColor(kRed);
      gr_v2lm1[i]->SetLineColor(kRed);
      gr_v2lm1[i]->SetLineWidth(1);
      gr_v2lm1[i]->SetLineStyle(1);
      gr_v2lm1[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm1[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm1[i]->SetMaximum(0.2);
      gr_v2lm1[i]->SetMinimum(-0.01);
      gr_v2lm1[i]->GetXaxis()->SetRangeUser(1., 70.);
      gr_v2lm1[i]->SetTitle(0);
      //gr_v2lm1[i]->Draw("AP");

      gr_v2lm2[i] = new TGraphErrors(multbin, Ntrk2, v2_LM2, Ntrk_E2,  v2_LM_E2);
      gr_v2lm2[i]->SetMarkerStyle(kFullCircle);
      gr_v2lm2[i]->SetMarkerSize(1);
      gr_v2lm2[i]->SetMarkerColor(kRed);
      gr_v2lm2[i]->SetLineColor(kRed);
      gr_v2lm2[i]->SetLineWidth(1);
      gr_v2lm2[i]->SetLineStyle(1);
      gr_v2lm2[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm2[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm2[i]->SetMaximum(0.2);
      gr_v2lm2[i]->SetMinimum(-0.01);
      gr_v2lm2[i]->GetXaxis()->SetRangeUser(1., 70.);
      gr_v2lm2[i]->SetTitle(0);
      gr_v2lm2[i]->Draw("AP");

      gr_v2lm3[i] = new TGraphErrors(multbin, Ntrk3, v2_LM3, Ntrk_E3,  v2_LM_E3);
      gr_v2lm3[i]->SetMarkerStyle(kOpenCircle);
      gr_v2lm3[i]->SetMarkerSize(1);
      gr_v2lm3[i]->SetMarkerColor(kRed);
      gr_v2lm3[i]->SetLineColor(kRed);
      gr_v2lm3[i]->SetLineWidth(1);
      gr_v2lm3[i]->SetLineStyle(1);
      gr_v2lm3[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm3[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm3[i]->SetMaximum(0.3);
      gr_v2lm3[i]->SetMinimum(-0.03);
      gr_v2lm3[i]->GetXaxis()->SetRangeUser(1., 70.);
      gr_v2lm3[i]->SetTitle(0);
      gr_v2lm3[i]->Draw("PSAME");

      gr_v2lm4[i] = new TGraphErrors(multbin, Ntrk4, v2_LM4, Ntrk_E4,  v2_LM_E4);
      gr_v2lm4[i]->SetMarkerStyle(kFullSquare);
      gr_v2lm4[i]->SetMarkerSize(1.);
      gr_v2lm4[i]->SetMarkerColor(kGreen+3);
      gr_v2lm4[i]->SetLineColor(kGreen+3);
      gr_v2lm4[i]->SetLineWidth(1);
      gr_v2lm4[i]->SetLineStyle(1);
      gr_v2lm4[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2lm4[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2lm4[i]->SetMaximum(0.3);
      gr_v2lm4[i]->SetMinimum(-0.03);
      gr_v2lm4[i]->GetXaxis()->SetRangeUser(1., 70.);
      gr_v2lm4[i]->SetTitle(0);
      gr_v2lm4[i]->Draw("PSAME");
      

      gr_v3lm1[i] = new TGraphErrors(multbin, Ntrk1, v3_LM1, Ntrk_E1,  v3_LM_E1);
      gr_v3lm1[i]->SetMarkerStyle(kOpenStar);
      gr_v3lm1[i]->SetMarkerSize(1.1);
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
   
      gr_v3lm2[i] = new TGraphErrors(multbin, Ntrk2, v3_LM2, Ntrk_E2,  v3_LM_E2);
      gr_v3lm2[i]->SetMarkerStyle(kFullStar);
      gr_v3lm2[i]->SetMarkerSize(1.2);
      gr_v3lm2[i]->SetMarkerColor(kBlue);
      gr_v3lm2[i]->SetLineColor(kBlue);
      gr_v3lm2[i]->SetLineWidth(1);
      gr_v3lm2[i]->SetLineStyle(1);
      gr_v3lm2[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v3lm2[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v3lm2[i]->SetMaximum(0.3);
      gr_v3lm2[i]->SetMinimum(-0.03);
      gr_v3lm2[i]->SetTitle(0);
      gr_v3lm2[i]->Draw("PSAME");

      
      gr_v3lm3[i] = new TGraphErrors(multbin, Ntrk3, v3_LM3, Ntrk_E3,  v3_LM_E3);
      gr_v3lm3[i]->SetMarkerStyle(kOpenStar);
      gr_v3lm3[i]->SetMarkerSize(1.2);
      gr_v3lm3[i]->SetMarkerColor(kBlue);
      gr_v3lm3[i]->SetLineColor(kBlue);
      gr_v3lm3[i]->SetLineWidth(1);
      gr_v3lm3[i]->SetLineStyle(1);
      gr_v3lm3[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v3lm3[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v3lm3[i]->SetMaximum(0.3);
      gr_v3lm3[i]->SetMinimum(-0.03);
      gr_v3lm3[i]->SetTitle(0);
      gr_v3lm3[i]->Draw("PSAME");
      
      
      TLine* t2 = new TLine(1., 0., 70., 0.);
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
      
      v2_tex = new TLatex(0.6,0.84, (cent[i]));
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(12);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.06);
      v2_tex->SetLineWidth(2);
      //v2_tex->Draw();
      v2_tex = new TLatex(0.2,0.6,"2 < #Delta#eta < 4");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(12);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.06);
      v2_tex->SetLineWidth(2);
      //v2_tex->Draw();
      v2_tex = new TLatex(0.7,0.05,"Centrality (%)");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(32);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.06);
      v2_tex->SetLineWidth(2);
      v2_tex->Draw();
      v2_tex = new TLatex(0.032,0.6,"v_{n}");
      v2_tex->SetNDC();
      v2_tex->SetTextAlign(32);
      v2_tex->SetTextFont(42);
      v2_tex->SetTextSize(0.07);
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

      TLine* t3_leg = new TLine();
      t3_leg->SetLineStyle(1);
      t3_leg->SetLineWidth(4);
      t3_leg->SetLineColor(kGreen+3);

      TMarker* m1_leg = new TMarker();
      m1_leg->SetMarkerStyle(kOpenCircle);
      m1_leg->SetMarkerColor(kBlack);

      TMarker* m2_leg = new TMarker();
      m2_leg->SetMarkerStyle(kFullSquare);
      m2_leg->SetMarkerColor(kBlack);

      TMarker* m3_leg = new TMarker();
      m3_leg->SetMarkerStyle(kFullStar);
      m3_leg->SetMarkerColor(kBlack);
      m3_leg->SetMarkerSize(1.2);
      
      TLegend *leg_1 = new TLegend(0.18,0.7,0.4,0.88,NULL,"brNDC");
      leg_1->SetBorderSize(1);
      leg_1->SetLineColor(1);
      leg_1->SetLineStyle(1);
      leg_1->SetLineWidth(0);
      leg_1->SetFillColor(0);
      leg_1->SetTextSize(0.05);
      leg_1->SetFillStyle(1001);
      leg_1->AddEntry(gr_v2lm2[i],"v_{2} (|#Delta#eta| > 2)","ep");
      leg_1->AddEntry(gr_v3lm2[i],"v_{3} (|#Delta#eta| > 2)","ep");
      leg_1->AddEntry(gr_v2lm4[i],"v_{2} {4}","ep");
      leg_1->Draw("SAME");

      TLegend *leg_1_eff = new TLegend(0.4,0.4,0.5,0.5,NULL,"brNDC");
      leg_1_eff->SetBorderSize(1);
      leg_1_eff->SetLineColor(1);
      leg_1_eff->SetLineStyle(1);
      leg_1_eff->SetLineWidth(0);
      leg_1_eff->SetFillColor(0);
      leg_1_eff->SetTextSize(0.05);
      leg_1_eff->SetFillStyle(1001);
      leg_1_eff->AddEntry(gr_v2lm3[i],"v_{2} (eff corr., |#Delta#eta| > 2)","ep");
      leg_1_eff->AddEntry(gr_v3lm3[i],"v_{3} (eff corr., |#Delta#eta| > 2)","ep");
      leg_1_eff->Draw("SAME");

      TLegend *leg_2 = new TLegend(0.6,0.8,0.7,0.88,NULL,"brNDC");
      leg_2->SetBorderSize(1);
      leg_2->SetLineColor(1);
      leg_2->SetLineStyle(1);
      leg_2->SetLineWidth(0);
      leg_2->SetFillColor(0);
      leg_2->SetTextSize(0.05);
      leg_2->SetFillStyle(1001);
      //leg_2->AddEntry(m1_leg,"1 < p_{T} < 3 GeV","ep");
      leg_2->AddEntry(m2_leg,"0.5 < p_{T} < 3 GeV","");
      //leg_2->AddEntry(m2_leg,"Data","ep");
      //leg_2->AddEntry(m1_leg,"MC","ep");
      //leg_2->AddEntry(m3_leg,"0.3 < p_{T} < 3 GeV","ep");
      leg_2->Draw("SAME");

      //c_v2[i]->SaveAs("../pdf_file/Charge_Hadron_VnCent_effCorr_DATA.pdf");
      //c_v2[i]->SaveAs("../pdf_file/Charge_Hadron_VnCent_effCorr_DATA.png");
      //c_v2[i]->SaveAs(Form("../pdf_file/Charge_Hadron_VnpT_cent_%s.pdf", centt[i]));

      c_v4_v2_ratio[i] = new TCanvas(Form("cv4v2_ratio_%d", i),Form("cv4v2_ratio_%d", i),500,450);
      c_v4_v2_ratio[i]->SetFrameLineWidth(2);
      c_v4_v2_ratio[i]->SetFrameBorderMode(0);
      c_v4_v2_ratio[i]->SetLeftMargin(0.15);
      c_v4_v2_ratio[i]->SetBottomMargin(0.15);
      c_v4_v2_ratio[i]->SetRightMargin(0.05);
      c_v4_v2_ratio[i]->DrawFrame(1.0, 0.6, 70, 1.4);
      c_v4_v2_ratio[i]->SetTickx();
      c_v4_v2_ratio[i]->SetTicky();
      
      gr_v2_v4_ratio[i] = new TGraphErrors(multbin, Ntrk2, v24_v22_ratio, Ntrk_E2, v24_v22_ratio_err);
      gr_v2_v4_ratio[i]->SetMarkerStyle(kOpenCircle);
      gr_v2_v4_ratio[i]->SetMarkerSize(1.1);
      gr_v2_v4_ratio[i]->SetMarkerColor(kRed);
      gr_v2_v4_ratio[i]->SetLineColor(kRed);
      gr_v2_v4_ratio[i]->SetLineWidth(1);
      gr_v2_v4_ratio[i]->SetLineStyle(1);
      gr_v2_v4_ratio[i]->GetXaxis()->SetLabelSize(0.05);
      gr_v2_v4_ratio[i]->GetYaxis()->SetLabelSize(0.05);
      gr_v2_v4_ratio[i]->SetMaximum(1.4);
      gr_v2_v4_ratio[i]->SetMinimum(0.6);
      gr_v2_v4_ratio[i]->GetXaxis()->SetRangeUser(1., 70.);
      gr_v2_v4_ratio[i]->SetTitle(0);
      gr_v2_v4_ratio[i]->Draw("AP");

      TLine* t_ratio = new TLine(1,1,70,1);
      t_ratio->SetLineStyle(7);
      t_ratio->SetLineWidth(2);
      t_ratio->SetLineColor(kBlack);
      t_ratio->Draw("SAME");


      TLatex *   v4v2_ratio_tex = new TLatex(0.95,0.9406452,"PbPb, #sqrt{S_{NN}} = 5.36 TeV");
      v4v2_ratio_tex->SetNDC();
      v4v2_ratio_tex->SetTextAlign(32);
      v4v2_ratio_tex->SetTextFont(42);
      v4v2_ratio_tex->SetTextSize(0.05);
      v4v2_ratio_tex->SetLineWidth(4);
      v4v2_ratio_tex->Draw();
      v4v2_ratio_tex = new TLatex(0.45,0.9406452,"#bf{CMS} #it{Preliminary}");
      v4v2_ratio_tex->SetNDC();
      v4v2_ratio_tex->SetTextAlign(32);
      v4v2_ratio_tex->SetTextFont(42);
      v4v2_ratio_tex->SetTextSize(0.05);
      v4v2_ratio_tex->SetLineWidth(4);
      v4v2_ratio_tex->Draw();
      v4v2_ratio_tex = new TLatex(0.7,0.05,"Centrality (%)");
      v4v2_ratio_tex->SetNDC();
      v4v2_ratio_tex->SetTextAlign(32);
      v4v2_ratio_tex->SetTextFont(42);
      v4v2_ratio_tex->SetTextSize(0.06);
      v4v2_ratio_tex->SetLineWidth(2);
      v4v2_ratio_tex->Draw();
      v4v2_ratio_tex = new TLatex(0.033,0.67,"v_{2}{4} / v_{2}{2}");
      v4v2_ratio_tex->SetNDC();
      v4v2_ratio_tex->SetTextAlign(32);
      v4v2_ratio_tex->SetTextFont(42);
      v4v2_ratio_tex->SetTextSize(0.07);
      v4v2_ratio_tex->SetTextAngle(90);
      v4v2_ratio_tex->SetLineWidth(2);
      v4v2_ratio_tex->Draw();

      TLegend *leg_2_ratio = new TLegend(0.6,0.8,0.7,0.88,NULL,"brNDC");
      leg_2_ratio->SetBorderSize(1);
      leg_2_ratio->SetLineColor(1);
      leg_2_ratio->SetLineStyle(1);
      leg_2_ratio->SetLineWidth(0);
      leg_2_ratio->SetFillColor(0);
      leg_2_ratio->SetTextSize(0.05);
      leg_2_ratio->SetFillStyle(1001);
      leg_2_ratio->AddEntry(m2_leg,"0.5 < p_{T} < 3 GeV","");
      leg_2_ratio->Draw("SAME");
      
      //c_v4_v2_ratio[i]->SaveAs("../pdf_file/Charge_Hadron_v24_v22_ratio.png");
    }
}
