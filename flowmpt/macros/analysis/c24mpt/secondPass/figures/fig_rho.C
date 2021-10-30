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
  TH1D *XY_2[nMultBin];
  TH1D *X_2[nMultBin];
  TH1D *Y_2[nMultBin];
  TH1D *CK_2[nMultBin];

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


  //TFile *infile = new TFile("./outputROOT_c2_4_correlator_vs_Nch_allsub_2B_DYN3.root","read");
  TFile *infile = new TFile("../outputROOT_c2_4_correlator_vs_Nch_allsub_mergedAll.root","read");
  //TFile inFile("./../outputROOT_c2_4_correlator_vs_Nch_2sub.root", "read");
  //ifstream in1;
  //ifstream in2;
  //in1.open("./covV2PT_vs_Nch_PbPb_10M_0to200.txt");
  //in1.open("./output_covV2PT_vs_Nch_3sub_pp_PT3to2.txt");
  //in1.open("./outputTEXT_c2_4_correlator_vs_Nch_2sub.txt");
  //in2.open("./rhonumerator_vs_multiplicity_0to2000_2.txt");
  //if(!in1.good())    cout<<" input fail"<<endl;
  //else cout<<" input OK! "<<endl;
  float test=0;
  for(int i=0;i<nMultBin;i++){
/*    XY_1[i] = (TH1D*)infile->Get(Form("histXY_1_%d",i));
    X_1[i] = (TH1D*)infile->Get(Form("histX_1_%d",i));
    Y_1[i] = (TH1D*)infile->Get(Form("histY_1_%d",i));
    histNch_1[i] = (TH1D*)infile->Get(Form("histNch_1_%d",i));
    CK_1[i] = (TH1D*)infile->Get(Form("histCK_1_%d",i));
    Nch_1[i] = (histNch_1[i]->GetMean());
    cov_1[i] = (XY_1[i]->GetMean() - X_1[i]->GetMean()*Y_1[i]->GetMean() );
    rho_1[i] = cov_1[i] / (X_1[i]->GetRMS() * sqrt(CK_1[i]->GetMean()));

    XY_2[i] = (TH1D*)infile->Get(Form("histXY_2_%d",i));
    X_2[i] = (TH1D*)infile->Get(Form("histX_2_%d",i));
    Y_2[i] = (TH1D*)infile->Get(Form("histY_2_%d",i));
    histNch_2[i] = (TH1D*)infile->Get(Form("histNch_2_%d",i));
    CK_2[i] = (TH1D*)infile->Get(Form("histCK_2_%d",i));
    Nch_2[i] = (histNch_2[i]->GetMean());
    cov_2[i] = (XY_2[i]->GetMean() - X_2[i]->GetMean()*Y_2[i]->GetMean() );
    rho_2[i] = cov_2[i] / (X_2[i]->GetRMS() * sqrt(CK_2[i]->GetMean()));
*/

    XY_3[i] = (TH1D*)infile->Get(Form("histXY_3_%d",i));
    X_3[i] = (TH1D*)infile->Get(Form("histX_3_%d",i));
    kXY_3[i] = (TH1D*)infile->Get(Form("khistXY_3_%d",i));
    kX_3[i] = (TH1D*)infile->Get(Form("khistX_3_%d",i));
    Y_3[i] = (TH1D*)infile->Get(Form("histY_3_%d",i));
    histNch_3[i] = (TH1D*)infile->Get(Form("histNch_3_%d",i));
    CK_3[i] = (TH1D*)infile->Get(Form("histCK_3_%d",i));
    Var_XY_3[i] = (TH1D*)infile->Get(Form("histc24abcdef_3_%d",i));
    Var_X_3[i] = (TH1D*)infile->Get(Form("histc24abc_3_%d",i));
    Var_Y_3[i] = (TH1D*)infile->Get(Form("histc24def_3_%d",i));
    kVar_XY_3[i] = (TH1D*)infile->Get(Form("khistc24abcdef_3_%d",i));
    kVar_X_3[i] = (TH1D*)infile->Get(Form("khistc24abc_3_%d",i));
    kVar_Y_3[i] = (TH1D*)infile->Get(Form("khistc24def_3_%d",i));

/*
// rebin: 
    if(i==2){
      histNch_3[i]->Add(histNch_3[0]);
      histNch_3[i]->Add(histNch_3[1]);
      XY_3[i]->Add(XY_3[0]);
      XY_3[i]->Add(XY_3[1]);
      X_3[i]->Add(X_3[0]);
      X_3[i]->Add(X_3[1]);
      Y_3[i]->Add(Y_3[0]);
      Y_3[i]->Add(Y_3[1]);
      Var_XY_3[i]->Add(Var_XY_3[0]);
      Var_XY_3[i]->Add(Var_XY_3[1]);
      Var_X_3[i]->Add(Var_X_3[0]);
      Var_X_3[i]->Add(Var_X_3[1]);
      Var_Y_3[i]->Add(Var_Y_3[0]);
      Var_Y_3[i]->Add(Var_Y_3[1]);
      CK_3[i]->Add(CK_3[0]);
      CK_3[i]->Add(CK_3[1]);
    }
    //if(i==0) continue;
    //if(i==1) continue;
*/
    Nch_3[i] = (histNch_3[i]->GetMean());
    cov_3[i] = (XY_3[i]->GetMean() - X_3[i]->GetMean()*Y_3[i]->GetMean() );
    rho_3[i] = cov_3[i] / ( sqrt( Var_XY_3[i]->GetMean() - Var_X_3[i]->GetMean()*Var_Y_3[i]->GetMean() ) * sqrt(CK_3[i]->GetMean()) );
    kcov_3[i] = (kXY_3[i]->GetMean() - kX_3[i]->GetMean()*Y_3[i]->GetMean() );
    krho_3[i] = kcov_3[i] / ( sqrt( kVar_XY_3[i]->GetMean() - kVar_X_3[i]->GetMean()*kVar_Y_3[i]->GetMean() ) * sqrt(CK_3[i]->GetMean()) );


/*
    XY_4[i] = (TH1D*)infile->Get(Form("histXY_4_%d",i));
    X_4[i] = (TH1D*)infile->Get(Form("histX_4_%d",i));
    kXY_4[i] = (TH1D*)infile->Get(Form("khistXY_4_%d",i));
    kX_4[i] = (TH1D*)infile->Get(Form("khistX_4_%d",i));
    Y_4[i] = (TH1D*)infile->Get(Form("histY_4_%d",i));
    histNch_4[i] = (TH1D*)infile->Get(Form("histNch_3_%d",i));
    CK_4[i] = (TH1D*)infile->Get(Form("histCK_4_%d",i));
    Var_XY_4[i] = (TH1D*)infile->Get(Form("histc24abcdefgh_4_%d",i));
    Var_X_4[i] = (TH1D*)infile->Get(Form("histc24abcd_4_%d",i));
    Var_Y_4[i] = (TH1D*)infile->Get(Form("histc24efgh_4_%d",i));
    kVar_XY_4[i] = (TH1D*)infile->Get(Form("khistc24abcdefgh_4_%d",i));
    kVar_X_4[i] = (TH1D*)infile->Get(Form("khistc24abcd_4_%d",i));
    kVar_Y_4[i] = (TH1D*)infile->Get(Form("khistc24efgh_4_%d",i));

    Nch_4[i] = (histNch_4[i]->GetMean());
    cov_4[i] = (XY_4[i]->GetMean() - X_4[i]->GetMean()*Y_4[i]->GetMean() );
    rho_4[i] = cov_4[i] / ( sqrt( Var_XY_4[i]->GetMean() - Var_X_4[i]->GetMean()*Var_Y_4[i]->GetMean() ) * sqrt(CK_4[i]->GetMean()) );
    kcov_4[i] = (kXY_4[i]->GetMean() - kX_4[i]->GetMean()*Y_4[i]->GetMean() );
    krho_4[i] = kcov_4[i] / ( sqrt( kVar_XY_4[i]->GetMean() - kVar_X_4[i]->GetMean()*kVar_Y_4[i]->GetMean() ) * sqrt(CK_4[i]->GetMean()) );
*/
//cout<<Var_XY_3[i]->GetMean() - Var_X_3[i]->GetMean()*Var_Y_3[i]->GetMean()<<"   "<<kVar_XY_3[i]->GetMean() - kVar_X_3[i]->GetMean()*kVar_Y_3[i]->GetMean()<<"   "<<Var_XY_4[i]->GetMean() - Var_X_4[i]->GetMean()*Var_Y_4[i]->GetMean()<<"   "<<kVar_XY_4[i]->GetMean() - kVar_X_4[i]->GetMean()*kVar_Y_4[i]->GetMean()<<endl;

  rhoe_3[i]=0;
cout<<Nch_3[i]<<"   "<<rho_3[i]<<"   "<<rhoe_3[i]<<endl;

    //cout<<histNch_2[i]->GetEntries()<<endl;
    //test+=histNch_2[i]->GetEntries();
    //cout<<"k = "<<i<<"  "<<cov_3[i]<<endl;
  } 
  //cout<<"TEST: "<<test<<endl;
float newNch[nMultBin-2];
float newrho[nMultBin-2];
float newrhoe[nMultBin-2];

  for(int i=0; i<nMultBin-2; i++){
   newNch[i] = Nch_3[i+2]; 
   newrho[i] = rho_3[i+2]; 
   newrhoe[i] = rhoe_3[i+2]; 
  }

////////////////

////////

  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.07);
  c1->SetRightMargin(0.05);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",140,0.,140.);
 hist->SetXTitle("N_{ch}");
 hist->SetYTitle("#rho(c_{2}{4},#LTp_{T}#GT)");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-0.04); hist->SetMaximum(0.05);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  TGraphErrors *gr1 = new TGraphErrors(nMultBin,Nch_1,rho_1,0,rhoe_1);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(24);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(1);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(1);
  //gr1->Draw("psameezL");

  TGraphErrors *gr2 = new TGraphErrors(nMultBin,Nch_2,rho_2,0,rhoe_2);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(25);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  //gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(nMultBin-2,newNch,newrho,0,newrhoe);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(4);
  gr3->Draw("psameezL");

  TGraphErrors *gr4 = new TGraphErrors(nMultBin,Nch_4,rho_4,0,rhoe_4);
  gr4->SetTitle("");
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerSize(1);
  gr4->SetMarkerColor(8);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(8);
  //gr4->Draw("psameezL");

    //TLatex *tex1 = new TLatex(20,0.00008,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    TLatex *tex1 = new TLatex(20,0.097,"PYTHIA8 13 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex2 = new TLatex(20,0.077,"0.3 < p_{T} < 2 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();



    TLegend *leg = new TLegend(0.3,0.65,0.5,0.75);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);

    //leg->AddEntry(gr1,"Looping","pl");
    //leg->AddEntry(gr1,"Standard","pl");
    //leg->AddEntry(gr2,"2-Subevent","pl");
    leg->AddEntry(gr3,"3-Subevent","pl");
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
  //c1->Print("figure_covV2PT_vs_Nch_pp_50M_0to200_PT2to2.pdf");

}


