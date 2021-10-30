void plot_final_correlator() {
  const int nMultBin=17;
  double tmp;


  double v2[nMultBin-1]; 
  double v2e[nMultBin-1]; 
  double Nchv2[nMultBin-1]; 
  double c2[nMultBin]; 
  double c2e[nMultBin]; 
  double c24[nMultBin]; 
  double c24e[nMultBin]; 
  double Nchc2[nMultBin]; 

  double mult_factor = 10.;

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
  in2>>Nchc2[i];
  in2>>tmp; c2[i] = tmp*mult_factor; c24[i] = tmp;
  in2>>tmp; c2e[i] = tmp*mult_factor; c24e[i] = tmp;
  //in2>>Nchc2[i]; in2>>c2[i]; in2>>c2e[i];
//cout<<Nchv2[i]<<"   "<<v2[i]<<"   "<<v2e[i]<<endl;
  }

  for(int i=0;i<nMultBin-1;i++){
   in1>>Nchv2[i]; in1>>v2[i]; in1>>v2e[i];
cout<<Nchv2[i]<<"   "<<v2[i]<<"   "<<v2e[i]<<endl;
  }
 
  //cout<<"TEST: "<<test<<endl;


////////////////

////////

  TCanvas *c1 = new TCanvas("c1","c1",1,1,550*1.9,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.14);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
 TH1D* hist = new TH1D("hist","",139,0.,139.);
 hist->SetXTitle("N_{ch}");
 hist->SetYTitle("#rho(c_{2}{n}, [p_{T}])");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-0.59);
 hist->SetMaximum(0.59);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 //hist->Draw();

        c1->cd(1);
        //gPad->SetTopMargin(0.06);
        //gPad->SetBottomMargin(0.15);
        gPad->SetLeftMargin(0.15);
        //gPad->SetRightMargin(0.01);
        gPad->SetTicks(-1);
        TH1D *hist3=(TH1D*)hist->Clone();
        //hist3->SetYTitle("cov(c_{2}{n}, [p_{T}])");
        //hist3->SetMinimum(-0.00014);
        //hist3->SetMaximum(0.00008);
        hist3->Draw();

  TGraphErrors *gr2 = new TGraphErrors(nMultBin-1,Nchv2,v2,0,v2e);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(25);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameez");

  TGraphErrors *gr3 = new TGraphErrors(nMultBin-2,Nchc2,c24,0,c24e); //nMultBin-2
  gr3->SetTitle("");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(4);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(4);
  gr3->Draw("psameez");


    //TLatex *tex1 = new TLatex(20,0.00008,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    TLatex *tex1 = new TLatex(75,0.44,"PYTHIA8 13 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.05);
    tex1->SetTextFont(42);
    tex1->Draw();
    TLatex *tex2 = new TLatex(75,0.33,"0.3 < p_{T} < 2 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    tex2->Draw();



    TLegend *leg = new TLegend(0.24,0.795,0.44,0.95);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    leg->AddEntry(gr2,"#rho(c_{2}{2}, [p_{T}])","pl");
    leg->AddEntry(gr3,"#rho(c_{2}{4}, [p_{T}])","pl");
    leg->Draw();

  c1->cd(2);
        //gPad->SetBottomMargin(0.15);
        //gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.02);
        gPad->SetTicks(-1);
  TH1D *hist2=(TH1D*)hist->Clone();
  hist2->Draw("same");
  gr2->Draw("psameez");
  TGraphErrors *gr4 = new TGraphErrors(nMultBin-2,Nchc2,c2,0,c2e); //nMultBin-2
  gr4->SetTitle("");
  gr4->SetMarkerStyle(20);
  gr4->SetMarkerSize(1);
  gr4->SetMarkerColor(4);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(4);
  gr4->Draw("psameez");
    TLegend *leg2 = new TLegend(0.11,0.795,0.31,0.95);
    leg2->SetFillColor(10);
    leg2->SetBorderSize(0);
    leg2->SetTextFont(42);
    leg2->SetTextColor(1);
    leg2->SetTextSize(0.05);
    leg2->AddEntry(gr2,"#rho(c_{2}{2}, [p_{T}])","pl");
    leg2->AddEntry(gr4,"#rho(c_{2}{4}, [p_{T}]) #times 10","pl");
    leg2->Draw();

  c1->Print("fig_07.png");
  c1->Print("fig_07.pdf");

}


