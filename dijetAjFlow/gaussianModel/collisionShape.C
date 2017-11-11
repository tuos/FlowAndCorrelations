#include "TRandom3.h"
#define PIVALUE 3.141592653589793
void collisionShape(){

  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.11);
  //c1->Divide(2,1,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",120,-15.,15.0);
 hist->SetXTitle("x (fm)");
 hist->SetYTitle("y (fm)");
 hist->SetMinimum(-15);
 hist->SetMaximum(15);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",-15,15,-15,15);
f2->SetParameters(1,0,1.5,0,3);
//f2->Draw("same");

 TH2D *h2 = new TH2D("h2","from f2",3000,-15,15,3000,-15,15);
 Long64_t const nEntry = 1e5;
 double x[nEntry], y[nEntry];
 for (Long64_t i=0; i<nEntry; i++){
   f2->GetRandom2(x[i], y[i]);
   h2->Fill(x[i], y[i]);
 }
 h2->Draw("samecolz");

TH1D *pthist = new TH1D("pthist","",300,0,300);
TH1D *phihist = new TH1D("phihist","",300,-1.5,7.5);
TF1 *fJet = new TF1("fJet","(9.06402e+13)*pow(x, -5.08010e+00)", 25, 250);
 double pt1[nEntry], pt2[nEntry], phi1[nEntry], phi2[nEntry];
 double pt, phi;
 rnd = new TRandom3(0);
 for (Long64_t i=0; i<nEntry; i++){
   pt = fJet->GetRandom();
   pt1[i] = pt;
   pt2[i] = pt;
   pthist->Fill(pt);
   phi = rnd->Uniform(0.0, 2*PIVALUE);
   phi1[i] = phi;
   if (phi>PIVALUE) phi2[i] = phi - PIVALUE;
     else phi2[i] = phi + PIVALUE; 
   phihist->Fill(phi);
 }
 //pthist->Draw("");
 //phihist->Draw("");

 double pt1F[nEntry], pt2F[nEntry];
 double dE1, dE2;
 double dr=0.2;
 double E0=15.0;
TH1D *ajhist = new TH1D("ajhist","",100,0,1);
 for (Long64_t i=0; i<nEntry; i++){
if(i%1000==0) cout<<"running i = "<<i<<endl;
   //f2->GetRandom2(x, y);
//if(fabs(x[i])>0.1 || fabs(y[i])>0.1 || phi1[i]>0.2) continue;
   double sumdE1=0; double sumdE2=0;
   for (int j=0;j<100;j++){
     dE1 = pow(dr, 2)*(f2->Eval(x[i], y[i])+ f2->Eval(x[i] + (j+1)*dr*cos(phi1[i]), y[i]+ (j+1)*dr*sin(phi1[i]) ))/2*E0;
     sumdE1 += dE1;
     dE2 = pow(dr, 2)*(f2->Eval(x[i], y[i])+ f2->Eval(x[i] + (j+1)*dr*cos(phi2[i]), y[i]+ (j+1)*dr*sin(phi2[i]) ))/2*E0;
     sumdE2 += dE2;
   }
   pt1F[i]=pt1[1]-sumdE1; 
   if (pt1F[i]<5) pt1F[i]=5;
   pt2F[i]=pt2[1]-sumdE2; 
   if (pt2F[i]<5) pt2F[i]=5;
   //cout<<x[i]<<"  "<<y[i]<<"  , "<<pt1[i]<<"   "<<sumdE1<<endl;
   ajhist->Fill(fabs(pt1F[i]-pt2F[i])/(pt1F[i]+pt2F[i]));
 }
ajhist->Draw();

  c1->Print("plot_collisionShape.png");
  c1->Print("plot_collisionShape.pdf");

}

