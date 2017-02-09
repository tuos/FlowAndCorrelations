#include "GetFileAndSys.C"

void macro_X7223Wei()
{
  const int nDataSets=7;
  char fileNames[nDataSets][200]={"data_chiX7223_2760Gev_integral.txt", "data_chiX7223_5020Gev_integral.txt", "osu_chiX_Glb_SV008_integral.txt", "osu_chiX_Glb_SV020_integral.txt", "osu_chiX_KLN_SV008_integral.txt", "osu_chiX_KLN_SV020_integral.txt", "oli_chiX_AMPT_integral.txt"};

  TGraphErrors *graph[nDataSets];
  graph[0] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[0]),2,25,1.2);
  graph[1] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[1]),1,20,1.2);
  graph[2] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[2]),1,20,0);
  graph[3] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[3]),1,20,0);
  graph[4] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[4]),1,20,0);
  graph[5] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[5]),1,20,0);
  graph[6] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[6]),1,20,0);

  TGraphErrors *graphLines[nDataSets];
  graphLines[2] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[2]),1,20,0,2,3,1);
  graphLines[3] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[3]),1,20,0,3,3,1);
  graphLines[4] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[4]),1,20,0,5,3,1);
  graphLines[5] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[5]),1,20,0,7,3,1);
  graphLines[6] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[6]),1,20,0,1,3,1);

  graph[2]->SetFillColor(kRed-10);
  graph[3]->SetFillColor(kMagenta-10);
  graph[4]->SetFillColor(kCyan-10);
  graph[5]->SetFillColor(kGreen-10);
  graph[6]->SetFillColor(kBlue-10);
  graphLines[2]->SetLineColor(kRed);
  graphLines[3]->SetLineColor(kMagenta);
  graphLines[4]->SetLineColor(kCyan);
  graphLines[5]->SetLineColor(kGreen);
  graphLines[6]->SetLineColor(kBlue);

  TCanvas *c1 = new TCanvas("c1","c1",410,430);
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

  TH1D* hist = new TH1D("hist","",100,0.0001.,62.8);
  hist->SetLineWidth(0);
  hist->SetXTitle("Centrality (%)");
  hist->SetYTitle("#chi_{7223}");
  hist->SetMinimum(-0.3);
  hist->SetMaximum(7.39);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleOffset(0.72);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetXaxis()->SetTitleOffset(0.8);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetLabelSize(0.06);
  c1->cd();
  hist->Draw();


  graph[2]->Draw("e3same");
  graphLines[2]->Draw("lsame");
  graph[3]->Draw("e3same");
  graphLines[3]->Draw("lsame");
  graph[4]->Draw("e3same");
  graphLines[4]->Draw("lsame");
  graph[5]->Draw("e3same");
  graphLines[5]->Draw("lsame");
  graph[6]->Draw("e3same");
  graphLines[6]->Draw("lsame");

  double sysX7223=9; // other sys. in percent;
  double sysX7223Abs=0.4; // eta gap sys.
  const int nCent=10;
  double sys2760[nCent], sys5020[nCent];
  double xv[nCent], yv[nCent];
  for(int i=0; i<graph[0]->GetN(); i++){
    graph[0]->GetPoint(i,xv[i],yv[i]);
    sys2760[i]=sqrt(sysX7223Abs*sysX7223Abs + (yv[i]*sysX7223*0.01)*(yv[i]*sysX7223*0.01));
    graph[1]->GetPoint(i,xv[i],yv[i]);
    sys5020[i]=sqrt(sysX7223Abs*sysX7223Abs + (yv[i]*sysX7223*0.01)*(yv[i]*sysX7223*0.01));
  }
  drawSysBoxValue(graph[0],16,1.6, sys2760);
  drawSysBoxValue(graph[1],16,1.6, sys5020);
  graph[0]->Draw("pezsame");
  graph[1]->Draw("pezsame");


  TLegend *leg = new TLegend(0.57,0.68,0.98,0.905);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.048);
  leg->SetBorderSize(0.035);
  leg->AddEntry(graphLines[2],"Glb, #eta/s=0.08","l");
  leg->AddEntry(graphLines[3],"Glb, #eta/s=0.2","l");
  leg->AddEntry(graphLines[4],"KLN, #eta/s=0.08","l");
  leg->AddEntry(graphLines[5],"KLN, #eta/s=0.2","l");
  leg->AddEntry(graphLines[6],"AMPT","l");
  leg->Draw();
  TLegend *leg2 = new TLegend(0.56,0.18,0.88,0.29);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.048);
  leg2->SetBorderSize(0.035);
  leg2->AddEntry(graph[1],"PbPb 5.02 TeV","pl");
  leg2->AddEntry(graph[0],"PbPb 2.76 TeV","pl");
  leg2->Draw();

  TLatex *tex= new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.048);
  tex->DrawLatex(0.02,0.96,"CMS Preliminary, 0.3 < p_{T} < 3.0 GeV/c, |#eta| < 2.4");


  c1->SaveAs("./plot_chicent_ForWei.png");
  c1->SaveAs("./plot_chicent_ForWei.pdf");

}



