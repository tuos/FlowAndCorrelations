#include "GetFileAndSys.C"

void multiparticleFlow()
{
  const int nDataSets=15;
  char fileNames[nDataSets][200]={"alicev22.txt", "alicev24.txt", "alicev26.txt",
                  "atlasv22.txt", "atlasv24.txt", "atlasv26.txt", "atlasv28.txt",
          "cmsv22.txt", "cmsv24.txt", "cmsv26.txt", "cmsv28.txt", "cmsv2lyz.txt",
                               "phenixv22.txt", "phenixv24.txt", "phenixv26.txt"};

  int colors[nDataSets] = {2,1,4, 2,1,4,6, 2,1,4,6,8, 2,1,4};
  int markers[nDataSets] = {21,20,24, 21,20,24,25, 21,20,24,25,28, 21,20,24};
  double sysValues[nDataSets][100];
  ifstream infile;
  TGraphErrors *graph[nDataSets];
  for(int i=0; i<nDataSets; i++){
    graph[i] = (TGraphErrors*)GetGraphWithSymmYErrorsFromFile(Form("./%s",fileNames[i]),colors[i],markers[i],1.2);
    //get sys values
    infile.open(Form("./%s",fileNames[i]));
    float tmp, sysy;
    Char_t buffer[2048];
    Int_t nlines = 0;
    if (!infile.is_open()) {
      cout << "Error opening file. Exiting." << endl;
    } else {
      while (!infile.eof()) {
        infile.getline(buffer,2048);
        sscanf(buffer,"%f %f %f %f\n",&tmp,&tmp,&tmp, &sysy);
        sysValues[i][nlines] = sysy;
        nlines++;
      }
    }
    infile.close();
    //cout<<"x ="<<sysValues[i][10]<<endl;
  }


  TCanvas *c1 = new TCanvas("c1","c1",960,800);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);
  c1->Divide(2,2);

  TH1D* hist = new TH1D("hist","",405,-0.01,404.99);
  hist->SetLineWidth(0);
  hist->SetXTitle("N_{trk}^{offline}");
  hist->SetYTitle("v_{2}");
  hist->SetMinimum(-0.002);
  hist->SetMaximum(0.139);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetTitleOffset(0.9);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetXaxis()->SetTitleOffset(0.9);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetLabelSize(0.06);

  //ALICE
  c1->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist1 = (TH1D*) hist->Clone();
  hist1->GetXaxis()->SetRangeUser(-0.01, 204.99);
  hist1->SetXTitle("N_{ch}(|#eta|<0.8, 0.2 < p_{T} < 3.0 GeV/c)");
  hist1->Draw();
  drawSysBoxValue(graph[0],16,2.0, sysValues[0]);
  drawSysBoxValue(graph[1],16,2.0, sysValues[1]);
  drawSysBoxValue(graph[2],16,2.0, sysValues[2]);
  graph[0]->Draw("pezsame");
  graph[1]->Draw("pezsame");
  graph[2]->Draw("pezsame");
  TLegend *leg1 = new TLegend(0.63,0.7,0.98,0.950);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.048);
  leg1->SetBorderSize(0);
  leg1->AddEntry(graph[0],"v_{2}{2, |#Delta#eta|>1.4}","pl");
  leg1->AddEntry(graph[1],"v_{2}{4}","pl");
  leg1->AddEntry(graph[2],"v_{2}{6}","pl");
  leg1->Draw();
  TLatex *tex1= new TLatex();
  tex1->SetNDC();
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.05);
  tex1->DrawLatex(0.2,0.88,"ALICE pPb 5.02 TeV");
  tex1->DrawLatex(0.2,0.81,"0.2 < p_{T} < 3.0 GeV/c");
  tex1->DrawLatex(0.2,0.74,"|#eta| < 0.8");

  //ATLAS
  c1->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist2 = (TH1D*) hist->Clone();
  hist2->GetXaxis()->SetRangeUser(-0.01, 407.99);
  hist2->SetXTitle("N_{ch}(|#eta|<2.5, p_{T} > 0.4 GeV/c)");
  hist2->Draw();
  drawSysBoxValue(graph[3],16,4.0, sysValues[3]);
  drawSysBoxValue(graph[4],16,4.0, sysValues[4]);
  drawSysBoxValue(graph[5],16,4.0, sysValues[5]);
  drawSysBoxValue(graph[6],16,4.0, sysValues[6]);
  graph[3]->Draw("pezsame");
  graph[4]->Draw("pezsame");
  graph[5]->Draw("pezsame");
  graph[6]->Draw("pezsame");
  TLegend *leg2 = new TLegend(0.65,0.68,0.98,0.950);
  leg2->SetFillStyle(0);
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.048);
  leg2->SetBorderSize(0);
  leg2->AddEntry(graph[3],"v_{2}{2, |#Delta#eta|>2}","pl");
  leg2->AddEntry(graph[4],"v_{2}{4}","pl");
  leg2->AddEntry(graph[5],"v_{2}{6}","pl");
  leg2->AddEntry(graph[6],"v_{2}{8}","pl");
  leg2->Draw();
  TLatex *tex2= new TLatex();
  tex2->SetNDC();
  tex2->SetTextFont(42);
  tex2->SetTextSize(0.048);
  tex2->DrawLatex(0.2,0.88,"ATLAS pPb 5.02 TeV");
  tex2->DrawLatex(0.2,0.81,"0.3 < p_{T} < 3.0 GeV/c");
  tex2->DrawLatex(0.2,0.74,"|#eta| < 2.5");

  //CMS
  c1->cd(3);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist3 = (TH1D*) hist->Clone();
  hist3->GetXaxis()->SetRangeUser(-0.01, 356.99);
  hist3->SetXTitle("N_{trk}^{offline}(|#eta|<2.4, p_{T} > 0.4 GeV/c)");
  hist3->Draw();
  drawSysBoxValue(graph[7],16,3.5, sysValues[7]);
  drawSysBoxValue(graph[8],16,3.5, sysValues[8]);
  drawSysBoxValue(graph[9],16,3.5, sysValues[9]);
  drawSysBoxValue(graph[10],16,3.5, sysValues[10]);
  drawSysBoxValue(graph[11],16,3.5, sysValues[11]);
  graph[7]->Draw("pezsame");
  graph[8]->Draw("pezsame");
  graph[9]->Draw("pezsame");
  graph[10]->Draw("pezsame");
  graph[11]->Draw("pezsame");
  TLegend *leg3 = new TLegend(0.63,0.65,0.98,0.95);
  leg3->SetFillStyle(0);
  leg3->SetFillColor(0);
  leg3->SetTextSize(0.048);
  leg3->SetBorderSize(0);
  leg3->AddEntry(graph[7],"v_{2}^{sub}{2, |#Delta#eta|>2}","pl");
  leg3->AddEntry(graph[8],"v_{2}{4}","pl");
  leg3->AddEntry(graph[9],"v_{2}{6}","pl");
  leg3->AddEntry(graph[10],"v_{2}{8}","pl");
  leg3->AddEntry(graph[11],"v_{2}{LYZ}","pl");
  leg3->Draw();
  TLatex *tex3= new TLatex();
  tex3->SetNDC();
  tex3->SetTextFont(42);
  tex3->SetTextSize(0.048);
  tex3->DrawLatex(0.2,0.88,"CMS pPb 5.02 TeV");
  tex3->DrawLatex(0.2,0.81,"0.3 < p_{T} < 3.0 GeV/c");
  tex3->DrawLatex(0.2,0.74,"|#eta| < 2.4");

  //PHENIX
  c1->cd(4);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.14);
  gPad->SetTopMargin(0.0);
  gPad->SetRightMargin(0.02);
  gPad->SetTicks(-1);
  TH1D *hist4 = (TH1D*) hist->Clone();
  hist4->GetXaxis()->SetRangeUser(-0.01, 51.99);
  hist4->SetXTitle("N_{tracks}^{FVTX}");
  hist4->Draw();
  drawSysBoxValue(graph[12],16,0.5, sysValues[12]);
  drawSysBoxValue(graph[13],16,0.5, sysValues[13]);
  drawSysBoxValue(graph[14],16,0.5, sysValues[14]);
  graph[12]->Draw("pezsame");
  graph[13]->Draw("pezsame");
  graph[14]->Draw("pezsame");
  TLegend *leg4 = new TLegend(0.67,0.75,0.98,0.950);
  leg4->SetFillStyle(0);
  leg4->SetFillColor(0);
  leg4->SetTextSize(0.048);
  leg4->SetBorderSize(0);
  leg4->AddEntry(graph[12],"v_{2}{2, FVTX}","pl");
  leg4->AddEntry(graph[13],"v_{2}{4}","pl");
  leg4->AddEntry(graph[14],"v_{2}{6}","pl");
  leg4->Draw();
  TLatex *tex4= new TLatex();
  tex4->SetNDC();
  tex4->SetTextFont(42);
  tex4->SetTextSize(0.048);
  tex4->DrawLatex(0.29,0.88,"PHENIX dAu 200 GeV");

  c1->SaveAs("./plot_multiparticleFlow.png");
  c1->SaveAs("./plot_multiparticleFlow.pdf");


}



