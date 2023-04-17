void mpt_look_at_hist(){

  const int nPtBin = 14;
  TH1D *phipsihist0_2pi[nPtBin];
  TH1D *mptphipsihist0_2pi_1ptbin;
  TFile* inFile = new TFile("./output_histograms.root");
  for(int i=0; i<nPtBin; i++){
    phipsihist0_2pi[i] = (TH1D*)inFile->Get(Form("mptphipsihist0_2pi_%d", i));
  }
    mptphipsihist0_2pi_1ptbin = (TH1D*)inFile->Get(Form("mptphipsihist0_2pi_1ptbin"));

  // add hist
  TH1D *mptphipsihist0_2pi_add;
  mptphipsihist0_2pi_add = (TH1D*)phipsihist0_2pi[0]->Clone();
  for(int i=1; i<nPtBin; i++){
    mptphipsihist0_2pi_add->Add(phipsihist0_2pi[i]);
  }

  TCanvas *c1 = new TCanvas("c1","c1",1250,750);
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
  c1->Divide(5,3);
  //c1->Divide(5,3,0,0);

  for(int i=0; i<nPtBin; i++){
    c1->cd(i+1);
    gPad->SetTicks(-1);
    if(i==4||i==9||i==14){
      gPad->SetRightMargin(0.02);
    }
    //phipsihist0_2pi[i]->Rebin(2);
    phipsihist0_2pi[i]->SetMaximum(1.05*phipsihist0_2pi[i]->GetMaximum());
    phipsihist0_2pi[i]->SetMinimum(0.9*phipsihist0_2pi[i]->GetMaximum());
    phipsihist0_2pi[i]->SetMarkerStyle(24);
    phipsihist0_2pi[i]->SetMarkerColor(2);
    phipsihist0_2pi[i]->SetMarkerSize(1.2);
    phipsihist0_2pi[i]->Draw("pez");
  }  

    // mpt from add
    //mptphipsihist0_2pi_1ptbin = (TH1D*)mptphipsihist0_2pi_add->Clone();
    //mptphipsihist0_2pi_1ptbin->Scale(1.0/14);

    c1->cd(15);
    gPad->SetTicks(-1);
    gPad->SetRightMargin(0.02);
    //mptphipsihist0_2pi_1ptbin->Rebin(2);
    mptphipsihist0_2pi_1ptbin->SetMaximum(1.05*mptphipsihist0_2pi_1ptbin->GetMaximum());
    mptphipsihist0_2pi_1ptbin->SetMinimum(0.9*mptphipsihist0_2pi_1ptbin->GetMaximum());
    mptphipsihist0_2pi_1ptbin->SetMarkerStyle(24);
    mptphipsihist0_2pi_1ptbin->SetMarkerColor(2);
    mptphipsihist0_2pi_1ptbin->SetMarkerSize(1.2);
    mptphipsihist0_2pi_1ptbin->Draw("pez"); 


}


