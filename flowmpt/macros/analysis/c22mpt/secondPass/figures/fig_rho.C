void fig_rho() {
  const int nMultBin=20;
  double tmp;

  double cov_1[nMultBin];
  double cove_1[nMultBin];
  double rho_1[nMultBin];
  double rhoe_1[nMultBin];
  double Nch_1[nMultBin];
  double cov_2[nMultBin];
  double cove_2[nMultBin];
  double rho_2[nMultBin];
  double rhoe_2[nMultBin];
  double Nch_2[nMultBin];

  double cov_3[nMultBin];
  double cove_3[nMultBin];
  double rho_3[nMultBin];
  double rhoe_3[nMultBin];
  double kcov_3[nMultBin];
  double kcove_3[nMultBin];
  double krho_3[nMultBin];
  double krhoe_3[nMultBin];
  double Nch_3[nMultBin];

  double cov_4[nMultBin];
  double cove_4[nMultBin];
  double rho_4[nMultBin];
  double rhoe_4[nMultBin];
  double kcov_4[nMultBin];
  double kcove_4[nMultBin];
  double krho_4[nMultBin];
  double krhoe_4[nMultBin];
  double Nch_4[nMultBin];

  TH1D *histNch_1[nMultBin];
  TH1D *XY_1[nMultBin];
  TH1D *X_1[nMultBin];
  TH1D *Y_1[nMultBin];
  TH1D *CK_1[nMultBin];

  TH1D *histNch_2[nMultBin];
  TH1D *histCOV_2[nMultBin];
  TH1D *CK_2[nMultBin];
  TH1D *Corr2_2[nMultBin];
  TH1D *Corr4_2[nMultBin];

  TH1D *histNch_3[nMultBin];
  TH1D *XY_3[nMultBin];
  TH1D *X_3[nMultBin];
  TH1D *kXY_3[nMultBin];
  TH1D *kX_3[nMultBin];
  TH1D *Y_3[nMultBin];
  TH1D *CK_3[nMultBin];
  TH1D *Var_XY_3[nMultBin];
  TH1D *Var_X_3[nMultBin];
  TH1D *Var_Y_3[nMultBin];
  TH1D *kVar_XY_3[nMultBin];
  TH1D *kVar_X_3[nMultBin];
  TH1D *kVar_Y_3[nMultBin];

  TH1D *histNch_4[nMultBin];
  TH1D *XY_4[nMultBin];
  TH1D *X_4[nMultBin];
  TH1D *kXY_4[nMultBin];
  TH1D *kX_4[nMultBin];
  TH1D *Y_4[nMultBin];
  TH1D *CK_4[nMultBin];
  TH1D *Var_XY_4[nMultBin];
  TH1D *Var_X_4[nMultBin];
  TH1D *Var_Y_4[nMultBin];
  TH1D *kVar_XY_4[nMultBin];
  TH1D *kVar_X_4[nMultBin];
  TH1D *kVar_Y_4[nMultBin];


  //TFile *infile = new TFile("./outputROOT_v2_2_correlator_vs_Nch_allsub_2B.root","read");
  TFile *infile = new TFile("../outputROOT_v2_meanpt_correlator_vs_Nch_mergedAll.root","read");
  float test=0;

  const int nJob = 232;
  TFile *infilei[nJob];
  for(int i=0; i<nJob; i++){
    infilei[i] = new TFile(Form("../jb%d/outputROOT_v2_meanpt_correlator_vs_Nch.root",i),"read");
  }
  TH1D *histNch_2i[nJob][nMultBin];
  TH1D *histCOV_2i[nJob][nMultBin];
  TH1D *CK_2i[nJob][nMultBin];
  TH1D *Corr2_2i[nJob][nMultBin];
  TH1D *Corr4_2i[nJob][nMultBin];
  for(int i=0; i<nJob; i++){
    for(int k =0; k<nMultBin; k++){
      histNch_2i[i][k] = (TH1D*)infilei[i]->Get(Form("histNch_2_%d",k));
      histCOV_2i[i][k] = (TH1D*)infilei[i]->Get(Form("histCovV2PT_2_%d",k));
      CK_2i[i][k] = (TH1D*)infilei[i]->Get(Form("histCK_2_%d",k));
      Corr2_2i[i][k] = (TH1D*)infilei[i]->Get(Form("histCorr2_2_%d",k));
      Corr4_2i[i][k] = (TH1D*)infilei[i]->Get(Form("histCorr4_2_%d",k));
    }
  }
  TH1D *hcov22err[nMultBin];
  TH1D *hckerr[nMultBin];
  TH1D *hrhoerr[nMultBin];
  for(int k =0; k<nMultBin; k++){
    hcov22err[k] = new TH1D(Form("hcov22err_%d",k),"",220,-11,11);
    hckerr[k] = new TH1D(Form("hckerr_%d",k),"",220,-110,110);
    hrhoerr[k] = new TH1D(Form("hrhoerr_%d",k),"",220,-11,11);
  }
  for(int i=0; i<nJob; i++){
    for(int k =0; k<nMultBin; k++){
       if(!isnan(histCOV_2i[i][k]->GetMean())) hcov22err[k]->Fill(histCOV_2i[i][k]->GetMean());
       if(!isnan(CK_2i[i][k]->GetMean())) hckerr[k]->Fill(CK_2i[i][k]->GetMean());
       if(!isnan(sqrt(Corr4_2i[i][k]->GetMean() - pow(Corr2_2i[i][k]->GetMean(),2))) && CK_2i[i][k]->GetMean()>=0 ) hrhoerr[k]->Fill( histCOV_2i[i][k]->GetMean()/(sqrt(Corr4_2i[i][k]->GetMean() - pow(Corr2_2i[i][k]->GetMean(),2)) * sqrt(CK_2i[i][k]->GetMean())) );
    }
  }
    for(int k =0; k<nMultBin; k++){
      cout<<endl<<"Entries: "<<hrhoerr[k]->GetEntries()<<endl<<endl;
    }


  double totalEvent=0;
  for(int i=0;i<nMultBin;i++){
    histNch_2[i] = (TH1D*)infile->Get(Form("histNch_2_%d",i));
    histCOV_2[i] = (TH1D*)infile->Get(Form("histCovV2PT_2_%d",i));
    CK_2[i] = (TH1D*)infile->Get(Form("histCK_2_%d",i));
    Corr2_2[i] = (TH1D*)infile->Get(Form("histCorr2_2_%d",i));
    Corr4_2[i] = (TH1D*)infile->Get(Form("histCorr4_2_%d",i));
    totalEvent+= histNch_2[i]->GetEntries();
  }
  for(int i=0;i<nMultBin-1;i++){
    Nch_2[i] = (histNch_2[i+1]->GetMean());
    cov_2[i] = histCOV_2[i+1]->GetMean();
    rho_2[i] = cov_2[i] / (sqrt(Corr4_2[i+1]->GetMean() - pow(Corr2_2[i+1]->GetMean(),2)) * sqrt(CK_2[i+1]->GetMean()));

   rhoe_2[i]=hrhoerr[i+1]->GetRMS()/sqrt(hrhoerr[i+1]->GetEntries()); 
cout<<Nch_2[i]<<"   "<<rho_2[i]<<"   "<<rhoe_2[i]<<endl;
  } 
  for(int i=0;i<nMultBin-1;i++){
//   if(isnan(rho_2[i])) rho_2[i]=(rho_2[i-1]+rho_2[i+1])/2;
  }
  rhoe_2[4]=(rhoe_2[3]+rhoe_2[5])/2; //tmp
  //cout<<"TEST: "<<test<<endl;

  cout<<"totalEvent = "<<totalEvent<<endl;
  ofstream outFile;
  outFile.open("out_rho_c22_pbpb.txt");
  for(int i=0;i<nMultBin-1;i++){
    cout<<Nch_2[i]<<"   "<<rho_2[i]<<"   "<<rhoe_2[i]<<endl;
    outFile<<Nch_2[i]<<"   "<<rho_2[i]<<"   "<<rhoe_2[i]<<endl;
  }

////////////////

////////

  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.13);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.06);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",219,0.,219.);
 hist->SetXTitle("N_{ch}");
 hist->SetYTitle("#rho(c_{2}{2},[p_{T}])");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-0.299);
 hist->SetMaximum(0.299);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(0.9);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->GetXaxis()->SetNdivisions(505);
 hist->Draw();

  TGraphErrors *gr1 = new TGraphErrors(nMultBin,Nch_2,cov_2,0,cove_2);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(24);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(1);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(1);
  //gr1->Draw("psameezL");

  TGraphErrors *gr2 = new TGraphErrors(nMultBin-2,Nch_2,rho_2,0,rhoe_2);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(25);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(nMultBin,Nch_3,rho_3,0,rhoe_3);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(4);
  //gr3->Draw("psameezL");

  TGraphErrors *gr4 = new TGraphErrors(nMultBin,Nch_4,rho_4,0,rhoe_4);
  gr4->SetTitle("");
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerSize(1);
  gr4->SetMarkerColor(8);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(8);
  //gr4->Draw("psameezL");

    //TLatex *tex1 = new TLatex(20,0.00008,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    TLatex *tex1 = new TLatex(20,0.24,"PbPb 5 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex2 = new TLatex(20,0.19,"0.5 < p_{T} < 5 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex2x = new TLatex(20,0.14,"|#eta|<2.4");
    tex2x->SetTextColor(1);
    tex2x->SetTextSize(0.045);
    tex2x->SetTextFont(42);
    tex2x->Draw();
    TLatex *tex3 = new TLatex(0,0.31,"CMS Preliminary");
    tex3->SetTextColor(1);
    tex3->SetTextSize(0.045);
    tex3->SetTextFont(42);
    tex3->Draw();



    TLegend *leg = new TLegend(0.6,0.75,0.75,0.85);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);

    //leg->AddEntry(gr1,"Looping","pl");
    //leg->AddEntry(gr1,"Standard","pl");
    leg->AddEntry(gr2,"3-subevent method","pl");
    //leg->AddEntry(gr3,"3-Subevent","pl");
   // leg->AddEntry(gr4,"4-Subevent","pl");
    //leg->AddEntry(gr3,"Looping with 3Sub cuts","pl");
    //leg->AddEntry(gr2,"PbPb 5.02TeV, 0.5 < pT < 2","pl");
    //leg->AddEntry(gr3,"Participant ZPC","pl");
    //leg->AddEntry(gr4,"Parton Hadron","pl");
    //leg->AddEntry(gr5,"Parton+Gluon Hadron","pl");
    //leg->AddEntry(gr6,"Participant Hadron","pl");
    //leg->AddEntry(gr2,"PnP p+Pb","pl");

    leg->Draw();

  //c1->Print("figure_covV2PT_vs_Nch_pp_50M_0to200_PT2to2.png");
  c1->Print("plot_fig_rho22_tmp.pdf");

}


