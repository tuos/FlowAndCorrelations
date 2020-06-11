void figure2_cl(){

  ifstream fileIn;
  fileIn.open("data_figure2_allModes.txt");
 
  const int nL = 24;
  double cL[nL];
  double xl[nL];

  for(int i=0; i< nL; i++){
    fileIn>>cL[i];
    cout<<i<<"   "<<cL[i]<<endl;
    xl[i]=i;
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
  //c1->SetLogx();  

 TH1D* hist = new TH1D("hist","",200,-0.3,18.7);
 hist->SetXTitle("#font[12]{l}");
 hist->SetYTitle("#font[12]{C_{l}}");
 hist->SetMinimum(0.000009);
 hist->SetMaximum(15.9);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.1);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.045);
 hist->GetYaxis()->SetLabelSize(0.045);
 hist->Draw();

  //TGraphErrors *gr2 = new TGraphErrors(nL,xl,cL,0,0);
  TGraphErrors *gr2 = new TGraphErrors(19,xl,cL,0,0);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(1.0);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  gr2->Draw("plsameez"); 

    TLegend *leg = new TLegend(0.54,0.83,0.7,0.9);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.05);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(gr2,"Average of events","pl");
    leg->Draw();

    TLatex *tex2= new TLatex(11.1, 0.6,"UCC |#eta|<2.4");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.05);
    tex2->SetTextFont(42);
    tex2->Draw();



  c1->SaveAs("plot_2.pdf");
  //c1->SaveAs("plot_2.png");
  //c1->SaveAs("plot_2.jpg");
  //c1->SaveAs("plot_2.gif");

}
