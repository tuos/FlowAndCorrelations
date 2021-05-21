void plot_corr_vs_Nch_pp_0to200_PT3to2() {
  const int nMultBin=40;
  double temp;

  double cov_LOOP[nMultBin];
  double cov_LOOP_error[nMultBin];
  double cov_3SUB[nMultBin];
  double cov_3SUB_error[nMultBin];
  double cov_LOOPCUT[nMultBin];
  double cov_LOOPCUT_error[nMultBin];

  double mult_LOOP[nMultBin];
  double mult_3SUB[nMultBin];
  double mult_LOOPCUT[nMultBin];


  ifstream in1;
  //ifstream in2;
  //in1.open("./covV2PT_vs_Nch_PbPb_10M_0to200.txt");
  in1.open("./output_correlations_vs_Nch.txt");
  //in2.open("./rhonumerator_vs_multiplicity_0to2000_2.txt");
  if(!in1.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nMultBin;i++){
   in1>>temp; 
   in1>>mult_3SUB[i];
   in1>>cov_3SUB[i];
   //in1>>cov_3SUB_error[i];

  } 
  


////////////////

////////
  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.2);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.07);
  c1->SetRightMargin(0.05);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,0.,200.);
 hist->SetXTitle("N_{ch}");
 hist->SetYTitle("#rho (pearson correlator)");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-1.);
 hist->SetMaximum(1.);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.5);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  //TF1 *V2vsNpart = new TF1("V2vsNpart","((x/3.4)^1.8/(1+(x/3)^1.8))*(.00005+(1/x)^0.8)",0.2,10);
  //V2vsNpart->SetLineColor(2);
  //V2vsNpart->SetLineWidth(2);
  //V2vsNpart->SetLineStyle(2);
  // V2vsPt->Draw("same");

  //TGraphErrors *gr2 = new TGraphErrors(nPtBin,pt,v2,0,v2e);
/*  TGraphErrors *gr3 = new TGraphErrors(20,mult_LOOPCUT,cov_LOOPCUT,0,cov_LOOPCUT_error);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(4);
  gr3->Draw("psameezL");

  TGraphErrors *gr1 = new TGraphErrors(20,mult_LOOP,cov_LOOP,0,cov_LOOP_error);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(1);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(1);
  gr1->Draw("psameezL");
*/
  TGraphErrors *gr2 = new TGraphErrors(nMultBin,mult_3SUB,cov_3SUB,0,cov_3SUB_error);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");


    TLatex *tex1= new TLatex(20,0.1795,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.025);
    tex1->SetTextFont(42);
    //tex1->Draw();



    TLegend *leg = new TLegend(0.2,0.2,0.2,.2);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);
    
    //leg->AddEntry(gr1,"Looping","pl");
    leg->AddEntry(gr2,"Event-Plane","pl");
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


