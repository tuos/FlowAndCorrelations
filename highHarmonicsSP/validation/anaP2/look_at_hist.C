void look_at_hist(){

  const int nPtBin = 14;
  TH1D *phipsihist0_2pi[nPtBin];
  TFile* inFile = new TFile("./output_histograms.root");
  for(int i=0; i<nPtBin; i++){
    phipsihist0_2pi[i] = (TH1D*)inFile->Get(Form("phipsihist0_2pi_%d", i));
  }

  TCanvas *c1 = new TCanvas("c1","c1",1000,750);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.07);
  c1->SetRightMargin(0.02);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  c1->Divide(4,3,0,0);

  for(int i=0; i<12; i++){
    c1->cd(i+1);
    gPad->SetTicks(-1);
    if(i==3||i==7||i==11){
      gPad->SetRightMargin(0.02);
    }
    phipsihist0_2pi[i]->Rebin(2);
    phipsihist0_2pi[i]->SetMaximum(1.4*phipsihist0_2pi[i]->GetMaximum());
    phipsihist0_2pi[i]->SetMarkerStyle(24);
    phipsihist0_2pi[i]->SetMarkerSize(1.2);
    phipsihist0_2pi[i]->Draw("pez");
  }  



}


