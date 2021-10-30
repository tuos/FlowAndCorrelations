void plot_v22_correlator_vs_Nch_3and4sub() {
  const int nMultBin=17;
  double tmp;


  double v2[nMultBin-1]; 
  double v2e[nMultBin-1]; 
  double Nchv2[nMultBin-1]; 
  double c2[nMultBin]; 
  double c2e[nMultBin]; 
  double Nchc2[nMultBin]; 


  //TFile *infile = new TFile("./outputROOT_v2_2_correlator_vs_Nch_allsub_2B.root","read");
  ifstream in1;
  ifstream in2;
  in1.open("./outputTEXT_pp_v22.txt");
  in2.open("./outputTEXT_pp_c24doubledyn.txt");
  if(!in1.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl; 
  for(int i=0;i<nMultBin;i++){

//  if(i<16){
//   in1>>Nchv2[i]; in1>>v2[i]; in1>>v2e[i];
//  }
  in2>>Nchc2[i]; in2>>c2[i]; in2>>c2e[i];
//cout<<Nchv2[i]<<"   "<<v2[i]<<"   "<<v2e[i]<<endl;
  }

  for(int i=0;i<nMultBin-1;i++){
   in1>>Nchv2[i]; in1>>v2[i]; in1>>v2e[i];
cout<<Nchv2[i]<<"   "<<v2[i]<<"   "<<v2e[i]<<endl;
  }
 
  //cout<<"TEST: "<<test<<endl;


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
 hist->SetYTitle("#rho");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-0.4);
 hist->SetMaximum(0.5);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  TGraphErrors *gr2 = new TGraphErrors(nMultBin-1,Nchv2,v2,0,v2e);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(25);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(nMultBin-2,Nchc2,c2,0,c2e);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(4);
  gr3->Draw("psameezL");

    //TLatex *tex1 = new TLatex(20,0.00008,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    TLatex *tex1 = new TLatex(20,0.4,"p+p PYTHIA8 13 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex2 = new TLatex(20,0.3,"0.3 < p_{T} < 2 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();



    TLegend *leg = new TLegend(0.5,0.65,0.7,0.75);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);

    //leg->AddEntry(gr1,"Looping","pl");
    //leg->AddEntry(gr1,"Standard","pl");
    leg->AddEntry(gr2,"#rho(c_{2}{2},[p_{T}])","pl");
    leg->AddEntry(gr3,"#rho(c_{2}{4},[p_{T}])","pl");
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


