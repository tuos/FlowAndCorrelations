void eff_pt()
{

TFile *inFile = new TFile("EffCorrectionsPixel_TT_pt_0_10.root");
TH2F *eff0005, *eff0510, *eff1030, *eff3050;
eff0005 = (TH2F*)inFile->Get("Eff_0_5");
eff0510 = (TH2F*)inFile->Get("Eff_5_10");
eff1030 = (TH2F*)inFile->Get("Eff_10_30");
eff3050 = (TH2F*)inFile->Get("Eff_30_50");

TH2F *eff[4];
eff[0] = (TH2F*)inFile->Get("Eff_0_5");
eff[1] = (TH2F*)inFile->Get("Eff_5_10");
eff[2] = (TH2F*)inFile->Get("Eff_10_30");
eff[3] = (TH2F*)inFile->Get("Eff_30_50"); 
////////////////

////////
  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->Divide(2,2);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",100,0.,12.0);
 hist->SetXTitle("p_{T} (GeV/c)");
 hist->SetYTitle("Efficiency/(1-Fake Rate)");
 hist->SetMinimum(0.001);
 hist->SetMaximum(1.01);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 //hist->Draw();

c1->cd(1);
eff0005->GetXaxis()->CenterTitle(1);
eff0005->GetYaxis()->CenterTitle(1);
eff0005->GetXaxis()->SetTitleSize(0.076);
eff0005->GetYaxis()->SetTitleSize(0.076);
eff0005->GetYaxis()->SetTitleOffset(0.6);
eff0005->GetXaxis()->SetTitleOffset(0.6);
eff0005->GetXaxis()->SetLabelSize(0.05);
eff0005->GetYaxis()->SetLabelSize(0.05);
//eff0005
//eff0005->Draw("colz");
for(int i=0; i<4; i++){
c1->cd(i+1);
eff[i]->SetTitle("Efficiency/(1-Fake Rate)");
eff[i]->GetXaxis()->CenterTitle(1);
eff[i]->GetYaxis()->CenterTitle(1);
eff[i]->GetXaxis()->SetTitleSize(0.076);
eff[i]->GetYaxis()->SetTitleSize(0.076);
eff[i]->GetYaxis()->SetTitleOffset(0.56);
eff[i]->GetXaxis()->SetTitleOffset(0.63);
eff[i]->GetXaxis()->SetLabelSize(0.05);
eff[i]->GetYaxis()->SetLabelSize(0.05);
eff[i]->Draw("colz");

}

  
    TLatex *tex1= new TLatex(1,0.345,"PbPb 2.76 TeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.07);
    tex1->SetTextFont(42);
    //tex1->Draw();
 
    c1->cd(1);
    tex1->DrawLatex(-2.0,8.5," PbPb 5.02 TeV, 0-5%");
    c1->cd(2);
    tex1->DrawLatex(-2.0,8.5," PbPb 5.02 TeV, 5-10%");
    c1->cd(3);
    tex1->DrawLatex(-2.0,8.5," PbPb 5.02 TeV, 10-30%");
    c1->cd(4);
    tex1->DrawLatex(-2.0,8.5," PbPb 5.02 TeV, 30-50%");


  c1->Print("plot_eff_pt_5020GeV.png");
  c1->Print("plot_eff_pt_5020GeV.pdf");

}

