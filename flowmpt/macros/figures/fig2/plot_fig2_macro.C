//scratch/tuos/models/v2mPtCorr/pythia8/v1/Model/Pythia8/everett/c22mpt_c24mpt/ppb/re_ana/final/combine/onePanel
void plot_fig2_macro(){

 
  const int NMultBin = 18;


  double mmult1[NMultBin];
  double cov1[NMultBin];
  double cov2[NMultBin];
  double cove1[NMultBin];
  double cove2[NMultBin];
  double cov3[NMultBin];
  double cov4[NMultBin];
  double cove3[NMultBin];
  double cove4[NMultBin];
  double cov5[NMultBin];
  double cove5[NMultBin];

  ifstream inFiles;
  inFiles.open("out_input_c22_c24_toy.txt");
  double tmp;
  for(int k =0; k<NMultBin; k++){
    inFiles>>tmp;
    inFiles>>mmult1[k];
    inFiles>>cov5[k]; inFiles>>cove5[k];
    inFiles>>cov1[k]; inFiles>>cove1[k];
    inFiles>>cov2[k]; inFiles>>cove2[k];  // already multiplied by 10 for c24
  }



 TH1D* hist = new TH1D("hist","",210,0.,210.);
 hist->SetXTitle("N_{ch}");
 //hist->SetYTitle("#rho(c_{2}{4},[p_{T}])");
 //hist->SetMinimum(-0.05);
 //hist->SetMaximum(0.05);
 hist->GetYaxis()->SetNdivisions(505);
 hist->GetXaxis()->SetNdivisions(505);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.22);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 //hist->Draw();

        TCanvas *c1 = new TCanvas("c1","c1",1.1*1*550,1*550);
        //c1->Divide(2,1);
        gStyle->SetOptStat(0);

        c1->cd(1);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.17);
        gPad->SetRightMargin(0.01);
        gPad->SetTicks(-1);
        TH1D *hist3=(TH1D*)hist->Clone();
        hist3->SetYTitle("cov(c_{2}{n}, [p_{T}])");
        hist3->SetMinimum(-0.00014);
        hist3->SetMaximum(0.00008);
        hist3->Draw();
        TGraphErrors *gr1 = new TGraphErrors(NMultBin,mmult1,cov1,0,cove1);
        gr1->SetTitle("");
        gr1->SetMarkerStyle(20);
        gr1->SetMarkerSize(1);
        gr1->SetMarkerColor(1);
        gr1->SetLineWidth(2);
        gr1->SetLineColor(1);
        gr1->Draw("psameez");
        TGraphErrors *gr2 = new TGraphErrors(NMultBin,mmult1,cov2,0,cove2);
        gr2->SetTitle("");
        gr2->SetMarkerStyle(25);
        gr2->SetMarkerSize(1);
        gr2->SetMarkerColor(2);
        gr2->SetLineWidth(2);
        gr2->SetLineColor(2);
        gr2->Draw("psameez");
        TGraphErrors *gr5 = new TGraphErrors(NMultBin,mmult1,cov5,0,cove5);
        gr5->SetTitle("");
        gr5->SetMarkerStyle(25);
        gr5->SetMarkerSize(1);
        gr5->SetMarkerColor(4);
        gr5->SetLineWidth(2);
        gr5->SetLineStyle(2);
        gr5->SetLineColor(4);
        gr5->Draw("sameL");

        TLatex *tex = new TLatex(80,-0.000038,"AMPT 5.02 TeV");
        tex->SetTextSize(0.04);
        tex->SetLineWidth(2);
        tex->SetTextFont(42);
        //tex->Draw();
        tex = new TLatex(80,-0.000045,"0.3 < p_{T} < 2.0 GeV");
        tex->SetTextSize(0.04);
        tex->SetLineWidth(2);
        tex->SetTextFont(42);
        //tex->Draw();
        tex = new TLatex(20,0.000056,"Toy model simulation without nonflow");
        tex->SetTextSize(0.05);
        tex->SetTextFont(42);
        tex->SetLineWidth(2);
        tex->Draw();

    TLegend *leg = new TLegend(0.4,0.22,0.55,0.45);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    leg->AddEntry(gr5," Input cov(v_{2}^{2}, [p_{T}])","l");
    leg->AddEntry(gr1," cov(c_{2}{2}, [p_{T}])","pl");
    leg->AddEntry(gr2," cov(c_{2}{4}, [p_{T}]) #times 10","pl");
    leg->Draw();
/*
        c1->cd(2);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.018);
        gPad->SetTicks(-1);
        TH1D *hist2=(TH1D*)hist->Clone();
        hist2->SetYTitle("#rho(c_{2}{n}, [p_{T}])");
        hist2->GetYaxis()->SetTitleOffset(1.0);
        hist2->SetMinimum(-0.15);
        hist2->SetMaximum(0.15);
        hist2->Draw();
        TGraphErrors *gr3 = new TGraphErrors(NMultBin-2,mmult1,cov3,0,cove3);
        gr3->SetTitle("");
        gr3->SetMarkerStyle(20);
        gr3->SetMarkerSize(1);
        gr3->SetMarkerColor(1);
        gr3->SetLineWidth(2);
        gr3->SetLineColor(1);
        gr3->Draw("psameez");
        TGraphErrors *gr4 = new TGraphErrors(NMultBin-2,mmult1,cov4,0,cove4);
        gr4->SetTitle("");
        gr4->SetMarkerStyle(25);
        gr4->SetMarkerSize(1);
        gr4->SetMarkerColor(2);
        gr4->SetLineWidth(2);
        gr4->SetLineColor(2);
        gr4->Draw("psameez");

    TLegend *leg2 = new TLegend(0.3,0.25,0.45,0.41);
    leg2->SetFillColor(10);
    leg2->SetBorderSize(0);
    leg2->SetTextFont(42);
    leg2->SetTextColor(1);
    leg2->SetTextSize(0.05);
    leg2->AddEntry(gr3," #rho(c_{2}{2}, [p_{T}])","pl");
    leg2->AddEntry(gr4," #rho(c_{2}{4}, [p_{T}])","pl");
    leg2->Draw();
*/
  c1->Print("fig_02.png");
  c1->Print("fig_02.pdf");


}

