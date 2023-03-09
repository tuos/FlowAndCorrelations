void countsVsvz_pt05_10(){

  const int nVzBin=4;
  double vzN4[nVzBin];
  double countsN4[nVzBin];
  double countsN4e[nVzBin];
  double vzS4[nVzBin];
  double countsS4[nVzBin];
  double countsS4e[nVzBin];
  double vzN23[nVzBin];
  double countsN23[nVzBin];
  double countsN23e[nVzBin];
  double vzS23[nVzBin];
  double countsS23[nVzBin];
  double countsS23e[nVzBin];

  ifstream incounts;
  incounts.open("data_counts_pt05_10_N4.txt");
  for(int i=0;i<nVzBin;i++){
    incounts>>vzN4[i];  
    incounts>>countsN4[i];  
    countsN4e[i] = sqrt(countsN4[i]);  
  } 
  incounts.close();
  incounts.open("data_counts_pt05_10_S4.txt");
  for(int i=0;i<nVzBin;i++){
    incounts>>vzS4[i];
    incounts>>countsS4[i];
    countsS4e[i] = sqrt(countsS4[i]);
  }
  incounts.close();
  incounts.open("data_counts_pt05_10_N23.txt");
  for(int i=0;i<nVzBin;i++){
    incounts>>vzN23[i];
    incounts>>countsN23[i];
    countsN23e[i] = sqrt(countsN23[i]);
  }
  incounts.close();
  incounts.open("data_counts_pt05_10_S23.txt");
  for(int i=0;i<nVzBin;i++){
    incounts>>vzS23[i];
    incounts>>countsS23[i];
    countsS23e[i] = sqrt(countsS23[i]);
  }
  incounts.close();

////////
  TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.165);
  c1->SetBottomMargin(0.15);
  c1->SetTopMargin(0.065);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",240,-12.,12.0);
 hist->SetXTitle("v_{z} (cm)");
 hist->SetYTitle("Particle Counts");
 hist->SetMinimum(-0.1);
 double countMax=91000.0;
 hist->SetMaximum(countMax);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.29);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.045);
 hist->Draw();

  TF1 *countsVsVz = new TF1("countsVsVz","[0]+[1]*x+[2]*x*x",-10,10);
  //TF1 *countsVsVz = new TF1("countsVsVz","[0]+[1]*x",-10,10);
  countsVsVz->SetLineColor(1);
  countsVsVz->SetLineWidth(3);
  countsVsVz->SetLineStyle(1);

  TGraphErrors *grN4 = new TGraphErrors(nVzBin,vzN4,countsN4,0,countsN4e);
  grN4->SetTitle("");
  grN4->SetMarkerStyle(21);
  grN4->SetMarkerSize(1.2);
  grN4->SetMarkerColor(1);
  grN4->SetLineWidth(2);
  grN4->SetLineColor(1);
  grN4->Draw("psameez");
  grN4->Fit(countsVsVz,"R");
  countsVsVz->Draw("same");
  TGraphErrors *grS4 = new TGraphErrors(nVzBin,vzS4,countsS4,0,countsS4e);
  grS4->SetTitle("");
  grS4->SetMarkerStyle(21);
  grS4->SetMarkerSize(1.2);
  grS4->SetMarkerColor(2);
  grS4->SetLineWidth(2);
  grS4->SetLineColor(2);
  grS4->Draw("psameez"); 
  countsVsVz->SetLineColor(2);
  grS4->Fit(countsVsVz,"R");
  countsVsVz->Draw("same");
  TGraphErrors *grN23 = new TGraphErrors(nVzBin,vzN23,countsN23,0,countsN23e);
  grN23->SetTitle("");
  grN23->SetMarkerStyle(20);
  grN23->SetMarkerSize(1.4);
  grN23->SetMarkerColor(4);
  grN23->SetLineWidth(2);
  grN23->SetLineColor(4);
  grN23->Draw("psameez");
  countsVsVz->SetLineColor(4);
  grN23->Fit(countsVsVz,"R");
  countsVsVz->Draw("same");
  TGraphErrors *grS23 = new TGraphErrors(nVzBin,vzS23,countsS23,0,countsS23e);
  grS23->SetTitle("");
  grS23->SetMarkerStyle(20);
  grS23->SetMarkerSize(1.4);
  grS23->SetMarkerColor(8);
  grS23->SetLineWidth(2);
  grS23->SetLineColor(8);
  grS23->Draw("psameez");
  countsVsVz->SetLineColor(8);
  grS23->Fit(countsVsVz,"R");
  countsVsVz->Draw("same");

    TLegend *leg = new TLegend(0.19,0.74,0.36,0.9);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    leg->AddEntry(grN4,"North Arm, Lastgap=4","pl");
    leg->AddEntry(grS4,"South Arm, Lastgap=4","pl");
    leg->AddEntry(grN23,"North Arm, Lastgap=2/3","pl");
    leg->AddEntry(grS23,"South Arm, Lastgap=2/3","pl");
    leg->Draw();
  
    TLatex *tex2= new TLatex(-6,countMax*1.03,"0-10%         0.5<p_{T}<1.0 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();


  c1->Print("plot_countsVsvz_pt05_10.png");
  c1->Print("plot_countsVsvz_pt05_10.pdf");


}

