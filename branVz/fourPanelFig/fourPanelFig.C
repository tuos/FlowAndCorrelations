#include "TGraphErrors.h"

void fourPanelFig()
{
// variables
const int nCentBin=4;
const int nPtBin=10;
double tmp;
double ptValues[nCentBin][nPtBin];
double v2Obs[nCentBin][nPtBin];
double v2ObsError[nCentBin][nPtBin];
double EPresulotion[nCentBin]={0.2689, 0.3750, 0.4045, 0.3222};
double EPresulotionError[nCentBin]={0.00001, 0.00001, 0.00002, 0.000005};
double v2Corrected[nCentBin][nPtBin];
double v2CorrectedError[nCentBin][nPtBin];

// read v2 values
  ifstream inputV2;
  inputV2.open("txt_cent_pt_v2_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputV2>>tmp;
        inputV2>>ptValues[i][j];
        inputV2>>v2Obs[i][j];
        inputV2>>v2ObsError[i][j];
      }
    }
    inputV2.close();

// get v2 corrected
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        v2Corrected[i][j] = v2Obs[i][j]/EPresulotion[i];
        v2CorrectedError[i][j] = (v2Obs[i][j]/EPresulotion[i])*sqrt(v2ObsError[i][j]*v2ObsError[i][j]/v2Obs[i][j]/v2Obs[i][j] + EPresulotionError[i]*EPresulotionError[i]/EPresulotion[i]/EPresulotion[i]);
      }
    }

  TCanvas *c1 = new TCanvas("c1","c1",960,800);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);
  c1->Divide(2,2);

  TH1D* hist = new TH1D("hist","",60,-0.01,5.99);
  hist->SetLineWidth(0);
  hist->SetXTitle("p_{T} (GeV)");
  hist->SetYTitle("v_{2}");
  hist->SetMinimum(-0.002);
  hist->SetMaximum(0.249);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleOffset(0.9);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetXaxis()->SetTitleOffset(0.9);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetLabelSize(0.06);

  //0-10%
  c1->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist1 = (TH1D*) hist->Clone();
  hist1->Draw();
  TGraphErrors *graph1 = new TGraphErrors(nPtBin, &ptValues[0][0],&v2Corrected[0][0],0,&v2CorrectedError[0][0]);
  graph1->SetTitle("");
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerSize(1.2);
  graph1->SetMarkerColor(1);
  graph1->SetLineWidth(2);
  graph1->SetLineColor(1);
  graph1->Draw("psameez");
  TLegend *leg1 = new TLegend(0.63,0.7,0.98,0.950);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.048);
  leg1->SetBorderSize(0);
  leg1->AddEntry(graph1,"v_{2}","pl");
  leg1->Draw();
  TLatex *tex1= new TLatex();
  tex1->SetNDC();
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.05);
  tex1->DrawLatex(0.2,0.88,"0-10%");

  //10-20%
  c1->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist2 = (TH1D*) hist->Clone();
  hist2->Draw();
  TGraphErrors *graph2 = new TGraphErrors(nPtBin, &ptValues[1][0],&v2Corrected[1][0],0,&v2CorrectedError[1][0]);
  graph2->SetTitle("");
  graph2->SetMarkerStyle(21);
  graph2->SetMarkerSize(1.2);
  graph2->SetMarkerColor(1);
  graph2->SetLineWidth(2);
  graph2->SetLineColor(1);
  graph2->Draw("psameez");
  TLatex *tex2= new TLatex();
  tex2->SetNDC();
  tex2->SetTextFont(42);
  tex2->SetTextSize(0.048);
  tex2->DrawLatex(0.2,0.88,"10-20%");

  //20-40%
  c1->cd(3);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist3 = (TH1D*) hist->Clone();
  hist3->Draw();
  TGraphErrors *graph3 = new TGraphErrors(nPtBin, &ptValues[2][0],&v2Corrected[2][0],0,&v2CorrectedError[2][0]);
  graph3->SetTitle("");
  graph3->SetMarkerStyle(21);
  graph3->SetMarkerSize(1.2);
  graph3->SetMarkerColor(1);
  graph3->SetLineWidth(2);
  graph3->SetLineColor(1);
  graph3->Draw("psameez");
  TLatex *tex3= new TLatex();
  tex3->SetNDC();
  tex3->SetTextFont(42);
  tex3->SetTextSize(0.048);
  tex3->DrawLatex(0.2,0.88,"20-40%");

  //40-60%
  c1->cd(4);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist4 = (TH1D*) hist->Clone();
  hist4->Draw();
  TGraphErrors *graph4 = new TGraphErrors(nPtBin, &ptValues[3][0],&v2Corrected[3][0],0,&v2CorrectedError[3][0]);
  graph4->SetTitle("");
  graph4->SetMarkerStyle(21);
  graph4->SetMarkerSize(1.2);
  graph4->SetMarkerColor(1);
  graph4->SetLineWidth(2);
  graph4->SetLineColor(1);
  graph4->Draw("psameez");
  TLatex *tex4= new TLatex();
  tex4->SetNDC();
  tex4->SetTextFont(42);
  tex4->SetTextSize(0.048);
  tex4->DrawLatex(0.2,0.88,"40-60%");

  c1->SaveAs("./fourPanelFig.png");
  c1->SaveAs("./fourPanelFig.pdf");


}



