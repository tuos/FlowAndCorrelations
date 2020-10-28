void figure9() {
  const int nPtBin=10;
  double pt[nPtBin];
  double v2[nPtBin];
  double v2e[nPtBin];

  double tmp;
  ifstream inv2;
  inv2.open("v2_ampt_cl_subiso.txt");
  if(!inv2.good())    cout<<" input fail"<<endl;
  else cout<<" input OK! "<<endl;
  for(int i=0;i<nPtBin;i++){
    inv2>>tmp; 
    pt[i]=2.5+i*5; 
    inv2>>v2[i];  
    v2e[i]=0;  
  } 


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
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",200,0.,50.0);
 hist->SetXTitle("Centrality (%)");
 hist->SetYTitle("v_{2}{#font[12]{C_{l}}}");
 hist->SetMinimum(0.0001);
 hist->SetMaximum(0.199);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->Draw();

  TGraphErrors *gr2 = new TGraphErrors(nPtBin,pt,v2,0,v2e);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.2);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("psameezL");
 

    TLegend *leg = new TLegend(0.55,0.73,0.83,0.87);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(gr2,"AMPT, #sigma = 3.0 mb ","pl");
    leg->Draw();
  
    TLatex *tex2= new TLatex(4.3,0.165,"Pb+Pb @ 5.0 TeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    tex2->Draw();
    TLatex *tex3= new TLatex(4.3,0.145,"|#eta| < 2.4");
    tex3->SetTextColor(1);
    tex3->SetTextSize(0.05);
    tex3->SetTextFont(42);
    tex3->Draw();


  c1->Print("plot_figure9.png");
  c1->Print("plot_figure9.pdf");

}


