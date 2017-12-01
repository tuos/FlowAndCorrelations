//#include "histEffVsPt.C"
//#include "cent1030EffVsPt.C"

void getEffPt()
{

//TFile *inFile = new TFile("../../EffCorrectionsPixelPbPb_nominal.root");
TFile *inFile = new TFile("../EffCorrectionsPixelPbPb_tight.root");

TH2F *eff[4];
eff[0] = (TH2F*)inFile->Get("Eff_0_5");
eff[1] = (TH2F*)inFile->Get("Eff_5_10");
eff[2] = (TH2F*)inFile->Get("Eff_10_30");
eff[3] = (TH2F*)inFile->Get("Eff_30_50"); 
////////////////

TH1D *effpt[4];
effpt[0] = (TH1D*)eff[0]->ProjectionY("effpt05",12,19);
effpt[1] = (TH1D*)eff[1]->ProjectionY("effpt510",12,19);
effpt[2] = (TH1D*)eff[2]->ProjectionY("effpt1030",12,19);
effpt[3] = (TH1D*)eff[3]->ProjectionY("effpt3050",12,19);

double mpt[10]={0.350843,0.449501,0.549149,0.696145,0.894131,1.11563,1.3641,1.68857,2.1862,2.71266};
 cout<<"#####"<<endl;
 cout<<"Eff. vs pT for 5.02 TeV, 10-30% : "<<endl;
 for(int i=0;i<10;i++){
   cout<<effpt[2]->GetBinContent(effpt[2]->FindBin(mpt[i]))*1.0/8<<", ";
 }
 cout<<endl;

 for(int i=1;i<52;i++){
   cout<<effpt[2]->GetBinCenter(i)<<"   "<<effpt[2]->GetBinContent(i)*1.0/8<<endl;
 }
 cout<<endl;

ofstream ofile;
ofile.open("mcEffpT5020_1030cent.txt");
 ofile<<"#####"<<endl;
 ofile<<"Eff. vs pT for 5.02 TeV, 10-30% : "<<endl;
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
 TH1D* hist = new TH1D("hist","",100,0.,4.0);
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
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    //leg->SetTextFont(42);
    leg->SetTextColor(1);
    //leg->SetTextSize(0.04);
    leg->AddEntry(effpt[0],"0-5%","pl");
    leg->AddEntry(effpt[1],"5-10%","pl");
    leg->AddEntry(effpt[2],"10-30%","pl");
    leg->AddEntry(effpt[3],"30-50%","pl");
    leg->Draw();
      TLatex *tex=new TLatex(1.,0.92,"PbPb 5.02 TeV,  |#eta|<0.8");
      tex->SetTextSize(0.05);
      tex->Draw();

c1->SaveAs("effVsPt_4CentBins_5020gev.png");
c1->SaveAs("effVsPt_4CentBins_5020gev.pdf");

/*
effpt[2]->Draw("same");
TF1 *f1 = new TF1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x+[6]*x*x*x*x*x*x+[7]*x*x*x*x*x*x*x", 0.3, 1.5);
TF1 *f2 = new TF1("f2","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x+[6]*x*x*x*x*x*x+[7]*x*x*x*x*x*x*x", 1.5, 3.0);
//TF1 *total = new TF1("total","f1+f2",0.3,3.0);
//Double_t par[16];
f1->SetParameters(1,1,1,1,1,1,1,1);
f1->SetLineColor(1);
effpt[2]->Fit("f1", "R");
//f1->Draw("same");
//effpt[2]->Fit("pol6");
f2->SetLineColor(2);
f2->SetParameters(1,1,1,1,1,1,1,1);
effpt[2]->Fit("f2", "R+");
*/
/*
cout<<endl<<endl;
TH1D *effVsPt = new TH1D("effVsPt", "effVsPt",27,0.3,3);
for(int i=0;i<27;i++){
if(i<12){
cout<<0.3+0.05+0.1*i<<"   "<<f1->Eval(0.3+0.05+0.1*i)<<endl;
effVsPt->SetBinContent(i+1, f1->Eval(0.3+0.05+0.1*i));
}
else {
cout<<0.3+0.05+0.1*i<<"   "<<f2->Eval(0.3+0.05+0.1*i)<<endl;
effVsPt->SetBinContent(i+1, f2->Eval(0.3+0.05+0.1*i));
}

}
//effVsPt->Draw("");
*/
//histEffVsPt();
//cout<<endl<<effVsPt->GetBinContent(effVsPt->FindBin(100.85))<<endl;
//cent1030EffVsPt();
//cout<<endl<<EffVsPt1030Hist->GetBinContent(EffVsPt1030Hist->FindBin(100.85))<<endl;
//effpt[2]->Draw();


}


