void figure5_cl(){

  ifstream fileIn;
  fileIn.open("data_cl_odd.txt");
 
  const int nL = 12;
  double cL[nL];
  double xl[nL];

  for(int i=0; i< nL; i++){
    fileIn>>cL[i];
    cout<<i<<"   "<<cL[i]<<endl;
    xl[i]=2*i+1;
  }
 
  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.05);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  c1->SetLogy();  
  c1->SetLogx();  

 TH1D* hist = new TH1D("hist","",200,0.8,35);
 hist->SetXTitle("#font[12]{l}");
 hist->SetYTitle("#font[12]{C_{l}}");
 hist->SetMinimum(0.000009);
 hist->SetMaximum(0.199);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.045);
 hist->GetYaxis()->SetLabelSize(0.045);
 hist->Draw();

  TGraphErrors *gr2 = new TGraphErrors(nL,xl,cL,0,0);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.0);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameez"); 

}
