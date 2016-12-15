void getEffPt()
{

TFile *inFile = new TFile("TrackCorrections_HYDJET_5320_hiGenPixelTrk_cent1030.root");

TH2F *eff[4];
eff[0] = (TH2F*)inFile->Get("rTotalEff3D");
eff[1] = (TH2F*)inFile->Get("rTotalEff3D");
eff[2] = (TH2F*)inFile->Get("rTotalEff3D");
eff[3] = (TH2F*)inFile->Get("rTotalEff3D"); 
////////////////

TH1D *effpt[4];
effpt[0] = (TH1D*)eff[0]->ProjectionY("effpt05",12,19);
effpt[1] = (TH1D*)eff[1]->ProjectionY("effpt510",12,19);
effpt[2] = (TH1D*)eff[2]->ProjectionY("effpt1030",12,19);
effpt[3] = (TH1D*)eff[3]->ProjectionY("effpt3050",12,19);

double mpt[10]={0.350843,0.449501,0.549149,0.696145,0.894131,1.11563,1.3641,1.68857,2.1862,2.71266};
 cout<<"#####"<<endl;
 cout<<"Eff. vs pT for 2.76 TeV, 10-30% : "<<endl;
 for(int i=0;i<10;i++){
   cout<<effpt[2]->GetBinContent(effpt[2]->FindBin(mpt[i]))*1.0/8<<", ";
 }
 cout<<endl;
ofstream ofile;
ofile.open("mcEffpT2760_1030cent.txt");
 ofile<<"#####"<<endl;
 ofile<<"Eff. vs pT for 2.76 TeV, 10-30% : "<<endl;
 for(int i=0;i<10;i++){
   ofile<<effpt[2]->GetBinContent(effpt[2]->FindBin(mpt[i]))*1.0/8<<", ";
 }
 ofile<<endl;
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
 TH1D* hist = new TH1D("hist","",100,0.,8.0);
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
 hist->Draw();

 int colors[4]={1,2,4,8};
 int markers[4]={20,21,24,25};
 for(int i=0; i<4; i++){
   effpt[i]->Scale(1.0/8);

   effpt[i]->SetLineColor(colors[i]);
   effpt[i]->SetMarkerColor(colors[i]);
   effpt[i]->SetMarkerStyle(markers[i]);
   effpt[i]->Draw("same");

 }

    TLegend *leg = new TLegend(0.3,0.2,0.6,0.5);
    leg->SetTextSize(0.06);
    leg->AddEntry(effpt[0],"0-5%","pl");
    leg->AddEntry(effpt[1],"5-10%","pl");
    leg->AddEntry(effpt[2],"10-30%","pl");
    leg->AddEntry(effpt[3],"30-50%","pl");
    leg->Draw();
}


