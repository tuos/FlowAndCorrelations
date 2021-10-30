void plot_pPb_v2c24_atlascomparison() {
  //const int nMultBin=20;
  const int nMultBin=9;
  double tmp;

  double v2_pPb[nMultBin];
  double v2e_pPb[nMultBin];
  double Nchv2_pPb[nMultBin];
  double v2_PbPb[nMultBin];
  double v2e_PbPb[nMultBin];
  double Nchv2_PbPb[nMultBin];
  double c2reg_pPb[nMultBin];
  double c2rege_pPb[nMultBin];
  double Nchc2reg_pPb[nMultBin];
  double c2reg_PbPb[nMultBin];
  double c2rege_PbPb[nMultBin];
  double Nchc2reg_PbPb[nMultBin];
  double c2double_pPb[nMultBin];
  double c2doublee_pPb[nMultBin];
  double Nchc2double_pPb[nMultBin];
  double c2double_PbPb[nMultBin];
  double c2doublee_PbPb[nMultBin];
  double Nchc2double_PbPb[nMultBin];
  double v2_pPbangantyr[nMultBin];
  double v2e_pPbangantyr[nMultBin];
  double Nchv2_pPbangantyr[nMultBin];
  double v2_PbPbangantyr[nMultBin];
  double v2e_PbPbangantyr[nMultBin];
  double Nchv2_PbPbangantyr[nMultBin];
  double c2double_pPbangantyr[nMultBin];
  double c2doublee_pPbangantyr[nMultBin];
  double Nchc2double_pPbangantyr[nMultBin];
  double c2double_PbPbangantyr[7];
  double c2doublee_PbPbangantyr[7];
  double Nchc2double_PbPbangantyr[7];

  double v2_pPbatlas[8];
  double v2e_pPbatlas[8];
  double Nchv2_pPbatlas[8];
  double v2_PbPbatlas[10];
  double v2e_PbPbatlas[10];
  double Nchv2_PbPbatlas[10];


  ifstream in1;
  ifstream in2;
  ifstream in3;
  ifstream in4;
  ifstream in5;
  ifstream in6;
  ifstream in7;
  ifstream in8;
  ifstream in9;
  ifstream in10;
  ifstream in11;
  ifstream in12;
  in1.open("./outputTEXT_pPbv2_rho_Nch.txt");
  in5.open("./outputTEXT_pPbc2doubledyn_rho_Nch.txt");
  in7.open("./outputTEXT_ATLAS_pPbv2_cov_Nch.txt");
  in9.open("./outputTEXT_ANGANTYR_pPbv2_rho_Nch.txt");
  in11.open("./outputTEXT_angantyr_pPbc2doubledyn_rho_Nch.txt");
  //in7.open("./outputTEXT_ATLAS_pPbv2_rho_Nch.txt");
  //in8.open("./outputTEXT_ATLAS_PbPbv2_rho_Nch.txt");
  for(int i=0;i<nMultBin;i++){
    in1>>Nchv2_pPb[i]; in1>>tmp; in1>>tmp; in1>>v2_pPb[i]; in1>>v2e_pPb[i];
    in5>>Nchc2double_pPb[i]; in5>>tmp; in5>>tmp; in5>>c2double_pPb[i]; in5>>c2doublee_pPb[i];
    //in7>>Nchv2_pPbatlas[i]; in7>>v2_pPbatlas[i]; in7>>v2e_pPbatlas[i];
    //in8>>Nchv2_PbPbatlas[i]; in8>>v2_PbPbatlas[i]; in8>>v2e_PbPbatlas[i];
    in9>>Nchv2_pPbangantyr[i]; in9>>tmp; in9>>tmp; in9>>v2_pPbangantyr[i]; in9>>v2e_pPbangantyr[i];
    in11>>Nchc2double_pPbangantyr[i]; in11>>tmp; in11>>tmp; in11>>c2double_pPbangantyr[i]; in11>>c2doublee_pPbangantyr[i];
    //in12>>Nchc2double_PbPbangantyr[i]; in12>>tmp; in12>>tmp; in12>>c2double_PbPbangantyr[i]; in12>>c2doublee_PbPbangantyr[i];

    c2double_pPb[i] = c2double_pPb[i]*10;
    c2doublee_pPb[i] = c2doublee_pPb[i]*10;
   
    c2double_pPbangantyr[i] = c2double_pPbangantyr[i]*10;
    c2doublee_pPbangantyr[i] = c2doublee_pPbangantyr[i]*10;
  } 
  //cout<<"TEST: "<<test<<endl;

  for(int i=0;i<8;i++){
    in7>>Nchv2_pPbatlas[i]; in7>>v2_pPbatlas[i]; in7>>v2e_pPbatlas[i];
  }
  for(int i=0;i<10;i++){
    //in8>>Nchv2_PbPbatlas[i]; in8>>v2_PbPbatlas[i]; in8>>v2e_PbPbatlas[i];
}
  for(int i=0;i<7;i++){
  }


///////////////

////////

  TCanvas *c1 = new TCanvas("c1","c1",1,1,550*1.1,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.16);
  c1->SetBottomMargin(0.14);
  c1->SetTopMargin(0.06);
  c1->SetRightMargin(0.02);
  //c1->Divide(2,1,0,0);
 gStyle->SetOptStat(0);
  c1->SetTicks(-1);
 TH1D* hist = new TH1D("hist","",299,0.,299.);
 hist->SetXTitle("N_{ch}");
 hist->SetYTitle("cov(c_{2}{n}, [p_{T}])");
 //hist->SetMinimum(-0.001);
 //hist->SetMaximum(0.0005);
 hist->SetMinimum(-0.000099);
 hist->SetMaximum(0.000049);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(1.38);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.055);
 hist->GetYaxis()->SetTitleSize(0.055);
 hist->GetXaxis()->SetLabelSize(0.04);
 hist->GetYaxis()->SetLabelSize(0.04);
 hist->Draw();

  TGraphErrors *gr1 = new TGraphErrors(6,Nchv2_pPb,v2_pPb,0,v2e_pPb); //7
  gr1->SetTitle("");
  gr1->SetMarkerStyle(24);
  gr1->SetMarkerSize(1);
  gr1->SetMarkerColor(1);
  gr1->SetLineWidth(2);
  gr1->SetLineColor(1);
  gr1->Draw("psameezL");

  TGraphErrors *gr2 = new TGraphErrors(nMultBin,Nchv2_PbPb,v2_PbPb,0,v2e_PbPb);
  gr2->SetTitle("");
  gr2->SetMarkerStyle(8);
  gr2->SetMarkerSize(1);
  gr2->SetMarkerColor(2);
  gr2->SetLineWidth(2);
  gr2->SetLineColor(2);
  //gr2->Draw("psameezL");

  TGraphErrors *gr3 = new TGraphErrors(nMultBin,Nchc2double_pPb,c2double_pPb,0,c2doublee_pPb);
  gr3->SetTitle("");
  gr3->SetMarkerStyle(25);
  gr3->SetMarkerSize(1);
  gr3->SetMarkerColor(2);
  gr3->SetLineWidth(2);
  gr3->SetLineColor(2);
  gr3->Draw("psameezL");

  TGraphErrors *gr4 = new TGraphErrors(nMultBin,Nchc2double_PbPb,c2double_PbPb,0,c2doublee_PbPb);
  gr4->SetTitle("");
  gr4->SetMarkerStyle(21);
  gr4->SetMarkerSize(1);
  gr4->SetMarkerColor(8);
  gr4->SetLineWidth(2);
  gr4->SetLineColor(8);
  //gr4->Draw("psameezL");

  TGraphErrors *gr5 = new TGraphErrors(8,Nchv2_pPbatlas,v2_pPbatlas,0,v2e_pPbatlas);
  gr5->SetTitle("");
  gr5->SetMarkerStyle(47);
  gr5->SetMarkerSize(1);
  gr5->SetMarkerColor(3);
  gr5->SetLineWidth(2);
  gr5->SetLineColor(3);
  gr5->Draw("psameezL");

  TGraphErrors *gr6 = new TGraphErrors(10,Nchv2_PbPbatlas,v2_PbPbatlas,0,v2e_PbPbatlas);
  gr6->SetTitle("");
  gr6->SetMarkerStyle(47);
  gr6->SetMarkerSize(1);
  gr6->SetMarkerColor(7);
  gr6->SetLineWidth(2);
  gr6->SetLineColor(7);
  //gr6->Draw("psameezL");

  TGraphErrors *gr7 = new TGraphErrors(nMultBin,Nchv2_pPbangantyr,v2_pPbangantyr,0,v2e_pPbangantyr);
  gr7->SetTitle("");
  gr7->SetMarkerStyle(30);
  gr7->SetMarkerSize(1);
  gr7->SetMarkerColor(4);
  gr7->SetLineWidth(2);
  gr7->SetLineColor(4);
  gr7->Draw("psameezL");

  TGraphErrors *gr8 = new TGraphErrors(nMultBin,Nchv2_PbPbangantyr,v2_PbPbangantyr,0,v2e_PbPbangantyr);
  gr8->SetTitle("");
  gr8->SetMarkerStyle(29);
  gr8->SetMarkerSize(1);
  gr8->SetMarkerColor(45);
  gr8->SetLineWidth(2);
  gr8->SetLineColor(45);
  //gr8->Draw("psameezL");

  TGraphErrors *gr9 = new TGraphErrors(7,Nchc2double_pPbangantyr,c2double_pPbangantyr,0,c2doublee_pPbangantyr);
  gr9->SetTitle("");
  gr9->SetMarkerStyle(26);
  gr9->SetMarkerSize(1);
  gr9->SetMarkerColor(6);
  gr9->SetLineWidth(2);
  gr9->SetLineColor(6);
  gr9->Draw("psameezL");

  TGraphErrors *gr10 = new TGraphErrors(7,Nchc2double_PbPbangantyr,c2double_PbPbangantyr,0,c2doublee_PbPbangantyr);
  gr10->SetTitle("");
  gr10->SetMarkerStyle(22);
  gr10->SetMarkerSize(1);
  gr10->SetMarkerColor(40);
  gr10->SetLineWidth(2);
  gr10->SetLineColor(40);
  //gr10->Draw("psameezL");


    //TLatex *tex1 = new TLatex(20,0.00008,"pp 13TeV, PYTHIA, 0.3 < p_{T} < 2 GeV/c");
    TLatex *tex1 = new TLatex(20,0.00008,"PbPb 13 TeV, 0.5 < p_{T} < 2 GeV");
    tex1->SetTextColor(1);
    tex1->SetTextSize(0.045);
    tex1->SetTextFont(42);
    //tex1->Draw();
    TLatex *tex2 = new TLatex(30,0.000034,"pPb, 0.3 < p_{T} < 2 GeV");
    tex2->SetTextColor(1);
    tex2->SetTextSize(0.045);
    tex2->SetTextFont(42);
    tex2->Draw();



    TLegend *leg = new TLegend(0.18,0.17,0.35,0.44);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.04);
    //leg->SetLineStyle(0.06);

    //leg->AddEntry(gr1,"Looping","pl");
    leg->AddEntry(gr1,"AMPT #rho(c_{2}{2}, [p_{T}])","pl");
    leg->AddEntry(gr3,"AMPT #rho(c_{2}{4}, [p_{T}]) #times 10","pl");
    leg->AddEntry(gr7,"ANGANTYR #rho(c_{2}{2}, [p_{T}])","pl");
    leg->AddEntry(gr9,"ANGANTYR #rho(c_{2}{4}, [p_{T}]) #times 10","pl");
    leg->AddEntry(gr5,"ATLAS #rho(c_{2}{2}, [p_{T}])","pl");

    leg->Draw();

  c1->Print("fig_08.png");
  c1->Print("fig_08.pdf");

}


