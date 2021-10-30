void plot_dynvar() {
  const int nMultBin=17;
  double tmp;

  double Nch_regdynvar[nMultBin];
  double regdynvar[nMultBin];
  double regdynvare[nMultBin];
  double Nch_rmsvar[nMultBin];
  double rmsvar[nMultBin];
  double rmsvare[nMultBin];
  double Nch_doubledynvar[nMultBin];
  double doubledynvar[nMultBin];
  double doubledynvare[nMultBin];

  ifstream in1;
  ifstream in2;
  ifstream in3;
  in1.open("./outputTEXT_regdynvarc24.txt");
  in2.open("./outputTEXT_regrmsc24.txt");
  in3.open("./outputTEXT_doubledynvarc24.txt");
  float test=0;
  for(int i=0;i<nMultBin;i++){

  in1>>Nch_regdynvar[i]; in1>>regdynvar[i]; in1>>regdynvare[i];
  in2>>Nch_rmsvar[i]; in2>>rmsvar[i]; in2>>rmsvare[i];
  in3>>Nch_doubledynvar[i]; in3>>doubledynvar[i]; in3>>doubledynvare[i];
  rmsvar[i] = rmsvar[i]/5;
  rmsvare[i] = rmsvare[i]/5;
  } 
  //cout<<"TEST: "<<test<<endl;


////////////////

////////

  TCanvas *c1 = new TCanvas("c1","c1",1,1,550*1.1,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.13);
  c1->SetTopMargin(0.06);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",139,0.,139.);
 hist->SetXTitle("N_{ch}");
 hist->SetYTitle("Var(c_{2}{4})");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-0.000006);
 hist->SetMaximum(0.00001);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(0.9);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.055);
 hist->GetYaxis()->SetTitleSize(0.055);
 hist->GetXaxis()->SetLabelSize(0.04);
 hist->GetYaxis()->SetLabelSize(0.04);
 hist->GetYaxis()->SetNdivisions(505);
 hist->Draw();

  TGraphErrors *gr1 = new TGraphErrors(nMultBin,Nch_regdynvar,regdynvar,0,regdynvare);
  gr1->SetTitle("");
  gr1->SetMarkerStyle(20);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(2);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(2);
  gr1->Draw("psameezL");

  TGraphErrors *gr2 = new TGraphErrors(nMultBin,Nch_rmsvar,rmsvar,0,rmsvare);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(1);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(1);
  gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(nMultBin,Nch_doubledynvar,doubledynvar,0,doubledynvare);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(24);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(4);
  gr3->Draw("psameezL");


    //TLatex *tex1 = new TLatex(20,0.00008,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    TLatex *tex1 = new TLatex(80,0.000008,"PYTHIA8 13 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex2 = new TLatex(80,0.0000065,"0.3 < p_{T} < 2 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();



    TLegend *leg = new TLegend(0.26,0.165,0.4,0.355);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);

    //leg->AddEntry(gr1,"Looping","pl");
    leg->AddEntry(gr2,"[Var(c_{2}{4}) from RMS] / 5","pl");
    leg->AddEntry(gr3,"Var(c_{2}{4})_{dyn} from double three subevents","pl");
    leg->AddEntry(gr1,"Var(c_{2}{4})_{dyn} from 8 particle correlations","pl");
    //leg->AddEntry(gr4,"4-Subevent","pl");
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
  c1->Print("fig_05.png");
  c1->Print("fig_05.pdf");  

}


