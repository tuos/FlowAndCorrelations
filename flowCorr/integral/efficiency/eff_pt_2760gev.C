void eff_pt_2760gev()
{

TFile *inFile0005 = new TFile("TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent05.root");
TFile *inFile0510 = new TFile("TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent510.root");
TFile *inFile1030 = new TFile("TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent1030.root");
TFile *inFile3050 = new TFile("TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent3050.root");
TFile *inFile50100 = new TFile("TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent50100.root");

TH2D *eff[4];
eff[0] = (TH2D*)inFile0005->Get("rTotalEff3D");
eff[1] = (TH2D*)inFile0510->Get("rTotalEff3D");
eff[2] = (TH2D*)inFile1030->Get("rTotalEff3D");
eff[3] = (TH2D*)inFile3050->Get("rTotalEff3D"); 
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

for(int i=0; i<4; i++){
c1->cd(i+1);
//eff[i]->SetTitle("Efficiency/(1-Fake Rate)");
eff[i]->SetTitle("Efficiency");
eff[i]->GetXaxis()->CenterTitle(1);
eff[i]->GetYaxis()->CenterTitle(1);
eff[i]->GetXaxis()->SetTitleSize(0.076);
eff[i]->GetYaxis()->SetTitleSize(0.076);
eff[i]->GetYaxis()->SetTitleOffset(0.61);
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
    tex1->DrawLatex(-1.6,2.5," PbPb 2.76 TeV, 0-5%");
    c1->cd(2);
    tex1->DrawLatex(-1.6,2.5," PbPb 2.76 TeV, 5-10%");
    c1->cd(3);
    tex1->DrawLatex(-1.6,2.5," PbPb 2.76 TeV, 10-30%");
    c1->cd(4);
    tex1->DrawLatex(-1.6,2.5," PbPb 2.76 TeV, 30-50%");


  c1->Print("plot_eff_pt_2760GeV.png");
  c1->Print("plot_eff_pt_2760GeV.pdf");

}

