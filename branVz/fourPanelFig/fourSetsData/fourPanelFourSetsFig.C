#include "TGraphErrors.h"

void fourPanelFourSetsFig()
{
// variables
const int nCentBin=4;
const int nPtBin=10;
double tmp;
double EPresulotion[nCentBin]={0.2689, 0.3750, 0.4045, 0.3222};
double EPresulotionError[nCentBin]={0.00001, 0.00001, 0.00002, 0.000005};
double ptValues[nCentBin][nPtBin];
double v2Obs[nCentBin][nPtBin];
double v2ObsError[nCentBin][nPtBin];
double v2Corrected[nCentBin][nPtBin];
double v2CorrectedError[nCentBin][nPtBin];
double v2ObsLG23[nCentBin][nPtBin];
double v2ObsLG23Error[nCentBin][nPtBin];
double v2CorrectedLG23[nCentBin][nPtBin];
double v2CorrectedLG23Error[nCentBin][nPtBin];
double v2ObsMinus[nCentBin][nPtBin];
double v2ObsMinusError[nCentBin][nPtBin];
double v2CorrectedMinus[nCentBin][nPtBin];
double v2CorrectedMinusError[nCentBin][nPtBin];
double v2ObsLG23Minus[nCentBin][nPtBin];
double v2ObsLG23MinusError[nCentBin][nPtBin];
double v2CorrectedLG23Minus[nCentBin][nPtBin];
double v2CorrectedLG23MinusError[nCentBin][nPtBin];

// read v2 values plus
  ifstream inputV2;
  inputV2.open("txt_v2_S_LG4_charge1_standard.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputV2>>tmp;
        inputV2>>ptValues[i][j];
        inputV2>>v2Obs[i][j];
        inputV2>>v2ObsError[i][j];
      }
    }
    inputV2.close();
  inputV2.open("txt_v2_S_LG23_charge1_standard.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputV2>>tmp;
        inputV2>>tmp;
        inputV2>>v2ObsLG23[i][j];
        inputV2>>v2ObsLG23Error[i][j];
      }
    }
    inputV2.close();

// read minus
  inputV2.open("txt_v2_S_LG4_charge0_standard.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputV2>>tmp;
        inputV2>>ptValues[i][j];
        inputV2>>v2ObsMinus[i][j];
        inputV2>>v2ObsMinusError[i][j];
      }
    }
    inputV2.close();
  inputV2.open("txt_v2_S_LG23_charge0_standard.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputV2>>tmp;
        inputV2>>tmp;
        inputV2>>v2ObsLG23Minus[i][j];
        inputV2>>v2ObsLG23MinusError[i][j];
      }
    }
    inputV2.close();

// get v2 corrected
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        v2Corrected[i][j] = v2Obs[i][j]/EPresulotion[i];
        v2CorrectedError[i][j] = (v2Obs[i][j]/EPresulotion[i])*sqrt(v2ObsError[i][j]*v2ObsError[i][j]/v2Obs[i][j]/v2Obs[i][j] + EPresulotionError[i]*EPresulotionError[i]/EPresulotion[i]/EPresulotion[i]);

        v2CorrectedLG23[i][j] = v2ObsLG23[i][j]/EPresulotion[i];
        v2CorrectedLG23Error[i][j] = (v2ObsLG23[i][j]/EPresulotion[i])*sqrt(v2ObsLG23Error[i][j]*v2ObsLG23Error[i][j]/v2ObsLG23[i][j]/v2ObsLG23[i][j] + EPresulotionError[i]*EPresulotionError[i]/EPresulotion[i]/EPresulotion[i]);

        // minus
        v2CorrectedMinus[i][j] = v2ObsMinus[i][j]/EPresulotion[i];
        v2CorrectedMinusError[i][j] = (v2ObsMinus[i][j]/EPresulotion[i])*sqrt(v2ObsMinusError[i][j]*v2ObsMinusError[i][j]/v2ObsMinus[i][j]/v2ObsMinus[i][j] + EPresulotionError[i]*EPresulotionError[i]/EPresulotion[i]/EPresulotion[i]);

        v2CorrectedLG23Minus[i][j] = v2ObsLG23Minus[i][j]/EPresulotion[i];
        v2CorrectedLG23MinusError[i][j] = (v2ObsLG23Minus[i][j]/EPresulotion[i])*sqrt(v2ObsLG23MinusError[i][j]*v2ObsLG23MinusError[i][j]/v2ObsLG23Minus[i][j]/v2ObsLG23Minus[i][j] + EPresulotionError[i]*EPresulotionError[i]/EPresulotion[i]/EPresulotion[i]);        

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
  graph1->SetMarkerStyle(25);
  graph1->SetMarkerSize(1.2);
  graph1->SetMarkerColor(2);
  graph1->SetLineWidth(2);
  graph1->SetLineColor(2);
  graph1->Draw("psameez");
  TGraphErrors *graph1LG23 = new TGraphErrors(nPtBin, &ptValues[0][0],&v2CorrectedLG23[0][0],0,&v2CorrectedLG23Error[0][0]);
  graph1LG23->SetTitle("");
  graph1LG23->SetMarkerStyle(21);
  graph1LG23->SetMarkerSize(1.2);
  graph1LG23->SetMarkerColor(2);
  graph1LG23->SetLineWidth(2);
  graph1LG23->SetLineColor(2);
  graph1LG23->Draw("psameez");
  TGraphErrors *graph1Minus = new TGraphErrors(nPtBin, &ptValues[0][0],&v2CorrectedMinus[0][0],0,&v2CorrectedMinusError[0][0]);
  graph1Minus->SetTitle("");
  graph1Minus->SetMarkerStyle(24);
  graph1Minus->SetMarkerSize(1.2);
  graph1Minus->SetMarkerColor(4);
  graph1Minus->SetLineWidth(2);
  graph1Minus->SetLineColor(4);
  graph1Minus->Draw("psameez");
  TGraphErrors *graph1LG23Minus = new TGraphErrors(nPtBin, &ptValues[0][0],&v2CorrectedLG23Minus[0][0],0,&v2CorrectedLG23MinusError[0][0]);
  graph1LG23Minus->SetTitle("");
  graph1LG23Minus->SetMarkerStyle(20);
  graph1LG23Minus->SetMarkerSize(1.2);
  graph1LG23Minus->SetMarkerColor(4);
  graph1LG23Minus->SetLineWidth(2);
  graph1LG23Minus->SetLineColor(4);
  graph1LG23Minus->Draw("psameez");
  TLegend *leg1 = new TLegend(0.63,0.7,0.98,0.950);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.048);
  leg1->SetBorderSize(0);
  leg1->AddEntry(graph1,"LG4 Plus","pl");
  leg1->AddEntry(graph1LG23,"LG23 Plus","pl");
  leg1->AddEntry(graph1Minus,"LG4 Minus","pl");
  leg1->AddEntry(graph1LG23Minus,"LG23 Minus","pl");
  leg1->Draw();
  TLatex *tex1= new TLatex();
  tex1->SetNDC();
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.05);
  tex1->DrawLatex(0.2,0.88,"0-10%");
  TLatex *tex1s= new TLatex();
  tex1s->SetNDC();
  tex1s->SetTextFont(42);
  tex1s->SetTextSize(0.05);
  tex1s->DrawLatex(0.2,0.78,"South");

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
  graph2->SetMarkerStyle(25);
  graph2->SetMarkerSize(1.2);
  graph2->SetMarkerColor(2);
  graph2->SetLineWidth(2);
  graph2->SetLineColor(2);
  graph2->Draw("psameez");
  TGraphErrors *graph2LG23 = new TGraphErrors(nPtBin, &ptValues[1][0],&v2CorrectedLG23[1][0],0,&v2CorrectedLG23Error[1][0]);
  graph2LG23->SetTitle("");
  graph2LG23->SetMarkerStyle(21);
  graph2LG23->SetMarkerSize(1.2);
  graph2LG23->SetMarkerColor(2);
  graph2LG23->SetLineWidth(2);
  graph2LG23->SetLineColor(2);
  graph2LG23->Draw("psameez");
  TGraphErrors *graph2Minus = new TGraphErrors(nPtBin, &ptValues[1][0],&v2CorrectedMinus[1][0],0,&v2CorrectedMinusError[1][0]);
  graph2Minus->SetTitle("");
  graph2Minus->SetMarkerStyle(24);
  graph2Minus->SetMarkerSize(1.2);
  graph2Minus->SetMarkerColor(4);
  graph2Minus->SetLineWidth(2);
  graph2Minus->SetLineColor(4);
  graph2Minus->Draw("psameez");
  TGraphErrors *graph2LG23Minus = new TGraphErrors(nPtBin, &ptValues[1][0],&v2CorrectedLG23Minus[1][0],0,&v2CorrectedLG23MinusError[1][0]);
  graph2LG23Minus->SetTitle("");
  graph2LG23Minus->SetMarkerStyle(20);
  graph2LG23Minus->SetMarkerSize(1.2);
  graph2LG23Minus->SetMarkerColor(4);
  graph2LG23Minus->SetLineWidth(2);
  graph2LG23Minus->SetLineColor(4);
  graph2LG23Minus->Draw("psameez");
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
  graph3->SetMarkerStyle(25);
  graph3->SetMarkerSize(1.2);
  graph3->SetMarkerColor(2);
  graph3->SetLineWidth(2);
  graph3->SetLineColor(2);
  graph3->Draw("psameez");
  TGraphErrors *graph3LG23 = new TGraphErrors(nPtBin, &ptValues[2][0],&v2CorrectedLG23[2][0],0,&v2CorrectedLG23Error[2][0]);
  graph3LG23->SetTitle("");
  graph3LG23->SetMarkerStyle(21);
  graph3LG23->SetMarkerSize(1.2);
  graph3LG23->SetMarkerColor(2);
  graph3LG23->SetLineWidth(2);
  graph3LG23->SetLineColor(2);
  graph3LG23->Draw("psameez");
  TGraphErrors *graph3Minus = new TGraphErrors(nPtBin, &ptValues[2][0],&v2CorrectedMinus[2][0],0,&v2CorrectedMinusError[2][0]);
  graph3Minus->SetTitle("");
  graph3Minus->SetMarkerStyle(24);
  graph3Minus->SetMarkerSize(1.2);
  graph3Minus->SetMarkerColor(4);
  graph3Minus->SetLineWidth(2);
  graph3Minus->SetLineColor(4);
  graph3Minus->Draw("psameez");
  TGraphErrors *graph3LG23Minus = new TGraphErrors(nPtBin, &ptValues[2][0],&v2CorrectedLG23Minus[2][0],0,&v2CorrectedLG23MinusError[2][0]);
  graph3LG23Minus->SetTitle("");
  graph3LG23Minus->SetMarkerStyle(20);
  graph3LG23Minus->SetMarkerSize(1.2);
  graph3LG23Minus->SetMarkerColor(4);
  graph3LG23Minus->SetLineWidth(2);
  graph3LG23Minus->SetLineColor(4);
  graph3LG23Minus->Draw("psameez");
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
  graph4->SetMarkerStyle(25);
  graph4->SetMarkerSize(1.2);
  graph4->SetMarkerColor(2);
  graph4->SetLineWidth(2);
  graph4->SetLineColor(2);
  graph4->Draw("psameez");
  TGraphErrors *graph4LG23 = new TGraphErrors(nPtBin, &ptValues[3][0],&v2CorrectedLG23[3][0],0,&v2CorrectedLG23Error[3][0]);
  graph4LG23->SetTitle("");
  graph4LG23->SetMarkerStyle(21);
  graph4LG23->SetMarkerSize(1.2);
  graph4LG23->SetMarkerColor(2);
  graph4LG23->SetLineWidth(2);
  graph4LG23->SetLineColor(2);
  graph4LG23->Draw("psameez");
  TGraphErrors *graph4Minus = new TGraphErrors(nPtBin, &ptValues[3][0],&v2CorrectedMinus[3][0],0,&v2CorrectedMinusError[3][0]);
  graph4Minus->SetTitle("");
  graph4Minus->SetMarkerStyle(24);
  graph4Minus->SetMarkerSize(1.2);
  graph4Minus->SetMarkerColor(4);
  graph4Minus->SetLineWidth(2);
  graph4Minus->SetLineColor(4);
  graph4Minus->Draw("psameez");
  TGraphErrors *graph4LG23Minus = new TGraphErrors(nPtBin, &ptValues[3][0],&v2CorrectedLG23Minus[3][0],0,&v2CorrectedLG23MinusError[3][0]);
  graph4LG23Minus->SetTitle("");
  graph4LG23Minus->SetMarkerStyle(20);
  graph4LG23Minus->SetMarkerSize(1.2);
  graph4LG23Minus->SetMarkerColor(4);
  graph4LG23Minus->SetLineWidth(2);
  graph4LG23Minus->SetLineColor(4);
  graph4LG23Minus->Draw("psameez");
  TLatex *tex4= new TLatex();
  tex4->SetNDC();
  tex4->SetTextFont(42);
  tex4->SetTextSize(0.048);
  tex4->DrawLatex(0.2,0.88,"40-60%");

  c1->SaveAs("./plot_fourPanelFourSetsFig.png");
  c1->SaveAs("./plot_fourPanelFourSetsFig.pdf");


}



