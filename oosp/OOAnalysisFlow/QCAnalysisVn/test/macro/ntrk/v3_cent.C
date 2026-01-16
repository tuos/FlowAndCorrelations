void v3_cent(){

  //static const int nCentBin = 6;
  static const int nHarmonics = 5;
  int iHarmonic = 2;
  static const int nPtBin = 20;
  //int cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  //double cBin[nCentBin+1]={0,100, 200, 300, 400, 500, 600};
  static const int nCentBin = 17;
  double cBin[nCentBin+1]={0, 20, 40, 60, 80, 100, 120, 150, 180, 210, 250, 300, 350, 400, 450, 500, 550, 600};
  double ptBins[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20000.0};

  TH1D *histCorr2_2[nCentBin];
  TH1D *histCorr4_2[nCentBin];
TH1D* hNtrkOffline[nCentBin];

      TH1D *histwCorr2_2_AB00[nCentBin];
      TH1D *histwCorr2_2_AB05[nCentBin];
      TH1D *histwCorr2_2_AB10[nCentBin];
      TH1D *histwCorr2_2_AB15[nCentBin];


  double vcent[nCentBin];
  double v22Values[nCentBin];
  double v22Errors[nCentBin];
  double v24Values[nCentBin];
  double v24Errors[nCentBin];
  //double ptValues[nCentBin][nPtBin];
  double v22ValuesAB00[nCentBin], v22ErrorsAB00[nCentBin];
  double v22ValuesAB05[nCentBin], v22ErrorsAB05[nCentBin];
  double v22ValuesAB10[nCentBin], v22ErrorsAB10[nCentBin];
  double v22ValuesAB15[nCentBin], v22ErrorsAB15[nCentBin];


  //TFile *inFile = new TFile("../../test/oo_miniAOD_qc_2M_gap.root","read");
  TFile *inFile = new TFile("oo_miniAOD_qc_hijingtable_37.root","read");
   for(int iC=0;iC<nCentBin;iC++){
     //for(int iH=0;iH<nHarmonics;iH++){
       histCorr2_2[iC] = (TH1D*)inFile->Get(Form("demo/histwCorr2_2_iC%d_iH%d",iC, iHarmonic));
       histCorr4_2[iC] = (TH1D*)inFile->Get(Form("demo/histwCorr4_2_iC%d_iH%d",iC, iHarmonic));
     //} //iH
       hNtrkOffline[iC] = (TH1D*)inFile->Get(Form("demo/hNtrkOffline_%d",iC));
       //vcent[iC] = (cBin[iC] + cBin[iC+1])*1.0/2;
       vcent[iC] = hNtrkOffline[iC]->GetMean();

       histwCorr2_2_AB00[iC] = (TH1D*)inFile->Get(Form("demo/histwCorr2_2_AB00_iC%d_iH%d",iC, iHarmonic));
       histwCorr2_2_AB05[iC] = (TH1D*)inFile->Get(Form("demo/histwCorr2_2_AB05_iC%d_iH%d",iC, iHarmonic));
       histwCorr2_2_AB10[iC] = (TH1D*)inFile->Get(Form("demo/histwCorr2_2_AB10_iC%d_iH%d",iC, iHarmonic));
       histwCorr2_2_AB15[iC] = (TH1D*)inFile->Get(Form("demo/histwCorr2_2_AB15_iC%d_iH%d",iC, iHarmonic));

   } //iC


  for(int iC=0;iC<nCentBin;iC++){ //nCentBin
    v22Values[iC] = sqrt(histCorr2_2[iC]->GetMean());
    v22Errors[iC] = 0.5/sqrt(histCorr2_2[iC]->GetMean())*histCorr2_2[iC]->GetMeanError();

    v22ValuesAB00[iC] = sqrt(histwCorr2_2_AB00[iC]->GetMean());
    v22ErrorsAB00[iC] = 0.5/sqrt(histwCorr2_2_AB00[iC]->GetMean())*histwCorr2_2_AB00[iC]->GetMeanError();
    v22ValuesAB05[iC] = sqrt(histwCorr2_2_AB05[iC]->GetMean());
    v22ErrorsAB05[iC] = 0.5/sqrt(histwCorr2_2_AB05[iC]->GetMean())*histwCorr2_2_AB05[iC]->GetMeanError();
    v22ValuesAB10[iC] = sqrt(histwCorr2_2_AB10[iC]->GetMean());
    v22ErrorsAB10[iC] = 0.5/sqrt(histwCorr2_2_AB10[iC]->GetMean())*histwCorr2_2_AB10[iC]->GetMeanError();
    v22ValuesAB15[iC] = sqrt(histwCorr2_2_AB15[iC]->GetMean());
    v22ErrorsAB15[iC] = 0.5/sqrt(histwCorr2_2_AB15[iC]->GetMean())*histwCorr2_2_AB15[iC]->GetMeanError();
    //double c24 = histCorr4_2[iC]->GetMean() - 2*histCorr2_2[iC]->GetMean()*histCorr2_2[iC]->GetMean();
    double c24 = -1*fabs( histCorr4_2[iC]->GetMean() - 2*histCorr2_2[iC]->GetMean()*histCorr2_2[iC]->GetMean() );
    double c24err = histCorr4_2[iC]->GetMeanError() - 4*histCorr2_2[iC]->GetMean()*histCorr2_2[iC]->GetMeanError();
    if(c24<0){
      //cout<<"iC = "<<iC<<"  , c24 = "<<c24<<endl;
      v24Values[iC] = pow(-1*c24, 1.0/4); 
      v24Errors[iC] = fabs( 0.25*pow( -1*c24, -0.75)*(-1*histCorr4_2[iC]->GetMeanError() + 4*histCorr2_2[iC]->GetMean()*histCorr2_2[iC]->GetMeanError()) );
      if(v24Errors[iC]>0.2 && iC>0) v24Errors[iC]=v24Errors[iC-1];
    } else{
      v24Values[iC] = 0;
      v24Errors[iC] = 0;
    }
    //cout<<iC<<"  "<<c24<<"  "<<c24err<<"   "<<v24Values[iC]<<"  "<<fabs(v24Errors[iC])<<endl;
    double c22 = histCorr2_2[iC]->GetMean();
    double c22err = histCorr2_2[iC]->GetMeanError();
    //cout<<iC<<"  "<<c22<<"  "<<c22err<<"   "<<v22Values[iC]<<"  "<<v22Errors[iC]<<endl;
    cout<<iC<<"  "<<vcent[iC]<<"     "<<v22Values[iC]<<"  "<<v22Errors[iC]<<"     "<<v22ValuesAB00[iC]<<"  "<<v22ErrorsAB00[iC]<<"     "<<v22ValuesAB05[iC]<<"  "<<v22ErrorsAB05[iC]<<"     "<<v22ValuesAB10[iC]<<"  "<<v22ErrorsAB10[iC]<<"     "<<v22ValuesAB15[iC]<<"  "<<v22ErrorsAB15[iC]<<"     "<<v24Values[iC]<<"  "<<fabs(v24Errors[iC])<<endl;
    //cout<<vcent[iC]<<"     "<<v24Values[iC]<<"  "<<fabs(v24Errors[iC])<<endl;

  }

//draw 
  TCanvas *c1 = new TCanvas("c1","c1",650,550);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  //c1->Divide(4,3);
  //c1->Divide(4,3,0,0);

 TH1D* hist = new TH1D("hist","",611,-1,610);
 hist->SetXTitle("N_{trk}^{offline}");
 hist->SetYTitle("v_{3}");
 hist->SetMinimum(-0.001);
 hist->SetMaximum(0.195);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(0.99);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.06);
 hist->GetYaxis()->SetTitleSize(0.06);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->GetXaxis()->SetNdivisions(508);
 hist->GetYaxis()->SetNdivisions(508);

    TLatex *tex= new TLatex();
    tex->SetTextColor(1);
    tex->SetTextSize(0.06);
    tex->SetTextFont(42);

  TGraphErrors *graph22 = new TGraphErrors(nCentBin-1,vcent,v22Values,0,v22Errors);
  TGraphErrors *graph24 = new TGraphErrors(nCentBin-1,vcent,v24Values,0,v24Errors);


    hist->Draw();
    graph22->SetTitle("");
    graph22->SetMarkerStyle(20);
    graph22->SetMarkerSize(1.2);
    graph22->SetMarkerColor(2);
    graph22->SetLineWidth(2);
    graph22->SetLineColor(2);
    graph22->Draw("psameez");

    graph24->SetTitle("");
    graph24->SetMarkerStyle(24);
    graph24->SetMarkerSize(1.2);
    graph24->SetMarkerColor(1);
    graph24->SetLineWidth(2);
    graph24->SetLineColor(1);
    graph24->Draw("psameez");

    tex->DrawLatex(25, 0.75*hist->GetMaximum(), Form("0.3 < p_{T} < 3.0 GeV"));

    TGraphErrors *grAB00 = new TGraphErrors(nCentBin-1,vcent,v22ValuesAB00,0,v22ErrorsAB00);
    TGraphErrors *grAB05 = new TGraphErrors(nCentBin-1,vcent,v22ValuesAB05,0,v22ErrorsAB05);
    TGraphErrors *grAB10 = new TGraphErrors(nCentBin-1,vcent,v22ValuesAB10,0,v22ErrorsAB10);
    TGraphErrors *grAB15 = new TGraphErrors(nCentBin-1,vcent,v22ValuesAB15,0,v22ErrorsAB15);
    grAB00->SetTitle("");
    grAB00->SetMarkerStyle(21);
    grAB00->SetMarkerSize(1.2);
    grAB00->SetMarkerColor(2);
    grAB00->SetLineWidth(2);
    grAB00->SetLineColor(2);
    grAB00->Draw("psameez");
    grAB05->SetTitle("");
    grAB05->SetMarkerStyle(25);
    grAB05->SetMarkerSize(1.2);
    grAB05->SetMarkerColor(2);
    grAB05->SetLineWidth(2);
    grAB05->SetLineColor(2);
    grAB05->Draw("psameez");
    grAB10->SetTitle("");
    grAB10->SetMarkerStyle(28);
    grAB10->SetMarkerSize(1.2);
    grAB10->SetMarkerColor(2);
    grAB10->SetLineWidth(2);
    grAB10->SetLineColor(2);
    grAB10->Draw("psameez");
    grAB15->SetTitle("");
    grAB15->SetMarkerStyle(33);
    grAB15->SetMarkerSize(1.2);
    grAB15->SetMarkerColor(2);
    grAB15->SetLineWidth(2);
    grAB15->SetLineColor(2);
    grAB15->Draw("psameez");


    TLegend *leg = new TLegend(0.6,0.53,0.89,0.92);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.06);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(graph22,"v_{3}{2, no gap}","pl");
    leg->AddEntry(grAB00,"v_{3}{2, gap>0}","pl");
    leg->AddEntry(grAB05,"v_{3}{2, gap>1}","pl");
    leg->AddEntry(grAB10,"v_{3}{2, gap>2}","pl");
    leg->AddEntry(grAB15,"v_{3}{2, gap>3}","pl");
    leg->AddEntry(graph24,"v_{3}{4}","pl");
    leg->Draw();

    tex->DrawLatex(25, 0.85*hist->GetMaximum(), Form("OO 5.36 TeV"));

  c1->SaveAs("plot_v3qc_cent.png");
  c1->SaveAs("plot_v3qc_cent.pdf");


}


