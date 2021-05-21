void figure_3sub_c24mpt(){
  TFile *infile = new TFile("./outfile_corr_c24mpt_2sub.root","read");
  
  const int NMultBin = 17;
  TH2D *hc24mpt[NMultBin];
  TH1D *hmpt[NMultBin];
  TH1D *hc24[NMultBin];
  TH1D *hmult[NMultBin];

  double mmult[NMultBin];
  double mc24[NMultBin];
  double mc24e[NMultBin];
  double sc24[NMultBin];
  double sc24e[NMultBin];
  double mpt[NMultBin];
  double mpte[NMultBin];
  double spt[NMultBin];
  double spte[NMultBin];
  double cov[NMultBin];
  double cove[NMultBin];
  double rho[NMultBin];
  double rhoe[NMultBin];
  for(int k =0; k<NMultBin; k++){
    hc24mpt[k] = (TH2D*)infile->Get(Form("c24mpt_%d",k));
    hmpt[k] = (TH1D*)infile->Get(Form("mpt_%d",k));
    hc24[k] = (TH1D*)infile->Get(Form("c24_%d",k));
    hmult[k] = (TH1D*)infile->Get(Form("mult_%d",k));

    mmult[k]=hmult[k]->GetMean();
    mc24[k]=hc24[k]->GetMean();
    mc24e[k]=hc24[k]->GetMeanError();
    sc24[k]=hc24[k]->GetRMS();
    sc24e[k]=hc24[k]->GetRMSError();
    mpt[k]=hmpt[k]->GetMean();
    mpte[k]=hmpt[k]->GetMeanError();
    spt[k]=hmpt[k]->GetRMS();
    spte[k]=hmpt[k]->GetRMSError();
    cov[k]=hc24mpt[k]->GetCovariance();
    cove[k]=0;
    rho[k]=hc24mpt[k]->GetCorrelationFactor();
    rhoe[k]=0;
  }

 TH1D* hist = new TH1D("hist","",150,0.,150.);
 hist->SetXTitle("N_{ch}");
 //hist->SetYTitle("#rho(c_{2}{4},[p_{T}])");
 //hist->SetMinimum(-0.05);
 //hist->SetMaximum(0.05);
 hist->GetYaxis()->SetNdivisions(505);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 //hist->Draw();

        TCanvas *c1 = new TCanvas("c1","c1",1.1*3*350,2*350);
        c1->Divide(3,2);
        gStyle->SetOptStat(0);

        c1->cd(1);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        hist->SetYTitle("#LTc_{2}{4}#GT");
        hist->SetMinimum(-0.00005);
        hist->SetMaximum(0.00005);
        hist->Draw();
        TGraphErrors *gr1 = new TGraphErrors(NMultBin,mmult,mc24,0,mc24e);
        gr1->SetTitle("");
        gr1->SetMarkerStyle(20);
        gr1->SetMarkerSize(1);
        gr1->SetMarkerColor(2);
        gr1->SetLineWidth(2);
        gr1->SetLineColor(2);
        gr1->Draw("psameezL");

        c1->cd(2);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist2=(TH1D*)hist->Clone();
        hist2->SetYTitle("#LTp_{T}#GT");
        hist2->SetMinimum(-0.000001);
        hist2->SetMaximum(0.99);
        hist2->Draw();
        TGraphErrors *gr2 = new TGraphErrors(NMultBin,mmult,mpt,0,mpte);
        gr2->SetTitle("");
        gr2->SetMarkerStyle(20);
        gr2->SetMarkerSize(1);
        gr2->SetMarkerColor(2);
        gr2->SetLineWidth(2);
        gr2->SetLineColor(2);
        gr2->Draw("psameezL");

        c1->cd(3);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist3=(TH1D*)hist->Clone();
        hist3->SetYTitle("cov(c_{2}{4}, #LTp_{T}#GT)");
        hist3->SetMinimum(-0.00001);
        hist3->SetMaximum(0.00001);
        hist3->Draw();
        TGraphErrors *gr3 = new TGraphErrors(NMultBin,mmult,cov,0,cove);
        gr3->SetTitle("");
        gr3->SetMarkerStyle(20);
        gr3->SetMarkerSize(1);
        gr3->SetMarkerColor(2);
        gr3->SetLineWidth(2);
        gr3->SetLineColor(2);
        gr3->Draw("psameezL");


        c1->cd(4);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist4=(TH1D*)hist->Clone();
        hist4->SetYTitle("#sigma_{c_{2}#{}{4}}");
        hist4->SetMinimum(-0.000001);
        hist4->SetMaximum(0.0015);
        hist4->Draw();
        TGraphErrors *gr4 = new TGraphErrors(NMultBin,mmult,sc24,0,sc24e);
        gr4->SetTitle("");
        gr4->SetMarkerStyle(20);
        gr4->SetMarkerSize(1);
        gr4->SetMarkerColor(2);
        gr4->SetLineWidth(2);
        gr4->SetLineColor(2);
        gr4->Draw("psameezL");

        c1->cd(5);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist5=(TH1D*)hist->Clone();
        hist5->SetYTitle("#sigma_{#LTp_{T}#GT}");
        hist5->SetMinimum(-0.000001);
        hist5->SetMaximum(0.99);
        hist5->Draw();
        TGraphErrors *gr5 = new TGraphErrors(NMultBin,mmult,spt,0,spte);
        gr5->SetTitle("");
        gr5->SetMarkerStyle(20);
        gr5->SetMarkerSize(1);
        gr5->SetMarkerColor(2);
        gr5->SetLineWidth(2);
        gr5->SetLineColor(2);
        gr5->Draw("psameezL");

        c1->cd(6);
        gPad->SetTopMargin(0.06);
        gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
        TH1D *hist6=(TH1D*)hist->Clone();
        hist6->SetYTitle("#rho(c_{2}{4}, #LTp_{T}#GT)");
        hist6->SetMinimum(-0.5);
        hist6->SetMaximum(0.5);
        hist6->Draw();
        TGraphErrors *gr6 = new TGraphErrors(NMultBin,mmult,rho,0,rhoe);
        gr6->SetTitle("");
        gr6->SetMarkerStyle(20);
        gr6->SetMarkerSize(1);
        gr6->SetMarkerColor(2);
        gr6->SetLineWidth(2);
        gr6->SetLineColor(2);
        gr6->Draw("psameezL");

        TLatex *tex = new TLatex(60,0.38,"PYTHIA8 13 TeV");
        tex->SetTextSize(0.05);
        tex->SetLineWidth(2);
        tex->Draw();
        tex = new TLatex(60,0.3,"0.3 < p_{T} < 2 GeV");
        tex->SetTextSize(0.05);
        tex->SetLineWidth(2);
        tex->Draw();
        tex = new TLatex(60,0.2,"c_{2}{4} from 2-subevent");
        tex->SetTextSize(0.05);
        tex->SetLineWidth(2);
        tex->Draw();

  c1->Print("plot_figure_2sub_c24mpt.png");
  //c1->Print("plot_figure_3sub_c24mpt.pdf");
  //c1->Print("plot_figure_3sub_c24mpt.C");

}

