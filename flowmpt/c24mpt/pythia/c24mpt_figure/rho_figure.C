void rho_figure(){
  TFile *infile1 = new TFile("../../standard_c24mpt//up/outfile_corr_c24mpt_standard.root","read");
  TFile *infile2 = new TFile("../../twosub/c24mpt/up/outfile_corr_c24mpt_2sub.root","read");
  TFile *infile3 = new TFile("../../threesub/nogap/reCheckCode/c24mpt/up/outfile_corr_c24mpt.root","read");
  TFile *infile4 = new TFile("../../foursub/c24mpt/up/outfile_corr_c24mpt_4sub.root","read");
  
  const int NMultBin = 17;
  TH2D *hc24mpt1[NMultBin];
  TH2D *hc24mpt2[NMultBin];
  TH2D *hc24mpt3[NMultBin];
  TH2D *hc24mpt4[NMultBin];
  TH1D *hmult1[NMultBin];
  TH1D *hmult2[NMultBin];
  TH1D *hmult3[NMultBin];
  TH1D *hmult4[NMultBin];

  double mmult1[NMultBin];
  double mmult2[NMultBin];
  double mmult3[NMultBin];
  double mmult4[NMultBin];
  double cov1[NMultBin];
  double cov2[NMultBin];
  double cov3[NMultBin];
  double cov4[NMultBin];
  double cove1[NMultBin];
  double cove2[NMultBin];
  double cove3[NMultBin];
  double cove4[NMultBin];
  for(int k =0; k<NMultBin; k++){
    hc24mpt1[k] = (TH2D*)infile1->Get(Form("c24mpt_%d",k));
    hc24mpt2[k] = (TH2D*)infile2->Get(Form("c24mpt_%d",k));
    hc24mpt3[k] = (TH2D*)infile3->Get(Form("c24mpt_%d",k));
    hc24mpt4[k] = (TH2D*)infile4->Get(Form("c24mpt_%d",k));
    hmult1[k] = (TH1D*)infile1->Get(Form("mult_%d",k));
    hmult2[k] = (TH1D*)infile2->Get(Form("mult_%d",k));
    hmult3[k] = (TH1D*)infile3->Get(Form("mult_%d",k));
    hmult4[k] = (TH1D*)infile4->Get(Form("mult_%d",k));

    mmult1[k]=hmult1[k]->GetMean();
    mmult2[k]=hmult2[k]->GetMean();
    mmult3[k]=hmult3[k]->GetMean();
    mmult4[k]=hmult4[k]->GetMean();
    cov1[k]=hc24mpt1[k]->GetCorrelationFactor();
    cov2[k]=hc24mpt2[k]->GetCorrelationFactor();
    cov3[k]=hc24mpt3[k]->GetCorrelationFactor();
    cov4[k]=hc24mpt4[k]->GetCorrelationFactor();
    cove1[k]=0;
    cove2[k]=0;
    cove3[k]=0;
    cove4[k]=0;
  }

 TH1D* hist = new TH1D("hist","",150,0.,150.);
 hist->SetXTitle("N_{ch}");
 //hist->SetYTitle("#rho(c_{2}{4},[p_{T}])");
 //hist->SetMinimum(-0.05);
 //hist->SetMaximum(0.05);
 hist->GetYaxis()->SetNdivisions(505);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.0);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 //hist->Draw();

        TCanvas *c1 = new TCanvas("c1","c1",1.1*1*550,1*550);
        //c1->Divide(3,2);
        gStyle->SetOptStat(0);

        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist3=(TH1D*)hist->Clone();
        hist3->SetYTitle("#rho(c_{2}{4}, #LTp_{T}#GT)");
        hist3->SetMinimum(-0.12);
        hist3->SetMaximum(0.12);
        hist3->Draw();
        TGraphErrors *gr1 = new TGraphErrors(NMultBin,mmult1,cov1,0,cove1);
        gr1->SetTitle("");
        gr1->SetMarkerStyle(24);
        gr1->SetMarkerSize(1);
        gr1->SetMarkerColor(1);
        gr1->SetLineWidth(2);
        gr1->SetLineColor(1);
        gr1->Draw("psameezL");
        TGraphErrors *gr2 = new TGraphErrors(NMultBin,mmult2,cov2,0,cove2);
        gr2->SetTitle("");
        gr2->SetMarkerStyle(25);
        gr2->SetMarkerSize(1);
        gr2->SetMarkerColor(2);
        gr2->SetLineWidth(2);
        gr2->SetLineColor(2);
        gr2->Draw("psameezL");
        TGraphErrors *gr3 = new TGraphErrors(NMultBin,mmult3,cov3,0,cove3);
        gr3->SetTitle("");
        gr3->SetMarkerStyle(20);
        gr3->SetMarkerSize(1);
        gr3->SetMarkerColor(4);
        gr3->SetLineWidth(2);
        gr3->SetLineColor(4);
        gr3->Draw("psameezL");
        TGraphErrors *gr4 = new TGraphErrors(NMultBin,mmult4,cov4,0,cove4);
        gr4->SetTitle("");
        gr4->SetMarkerStyle(21);
        gr4->SetMarkerSize(1);
        gr4->SetMarkerColor(8);
        gr4->SetLineWidth(2);
        gr4->SetLineColor(8);
        gr4->Draw("psameezL");

        TLatex *tex = new TLatex(12,0.092,"PYTHIA8 13 TeV");
        tex->SetTextSize(0.04);
        tex->SetLineWidth(2);
        tex->SetTextFont(42);
        tex->Draw();
        tex = new TLatex(12,0.075,"0.3 < p_{T} < 2 GeV");
        tex->SetTextSize(0.04);
        tex->SetLineWidth(2);
        tex->SetTextFont(42);
        tex->Draw();
        tex = new TLatex(60,0.2,"c_{2}{4} from standard");
        tex->SetTextSize(0.05);
        tex->SetLineWidth(2);
        //tex->Draw();
    TLegend *leg = new TLegend(0.53,0.65,0.7,0.9);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    leg->AddEntry(gr1," Standard","pl");
    leg->AddEntry(gr2," 2-subevent","pl");
    leg->AddEntry(gr3," 3-subevent","pl");
    leg->AddEntry(gr4," 4-subevent","pl");
    leg->Draw();

  c1->Print("plot_figure_rho.png");

}

