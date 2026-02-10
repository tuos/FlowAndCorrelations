void cent_pt_vn(){

  static const int nCentBin = 6;
  static const int nHarmonics = 5;
  static const int nPtBin = 32;
  //int cBin[nCentBin+1]={0, 1, 2, 5, 10, 15, 20, 25, 30, 35,40,45,50,55,60, 65,70,80};
  int cBin[nCentBin+1]={0, 10, 20, 30, 40, 50, 60};
  double ptBins[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0, 70.0, 90.0, 110.0, 20000.0};

  TH1D* hQhfPlusX[nCentBin][nHarmonics];
  TH1D* hQhfPlusY[nCentBin][nHarmonics];
  TH1D* hQhfMinusX[nCentBin][nHarmonics];
  TH1D* hQhfMinusY[nCentBin][nHarmonics];
  TH1D* hQtrkPtPlusX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtPlusY[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtMinusX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtMinusY[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkMidX[nCentBin][nHarmonics];
  TH1D* hQtrkMidY[nCentBin][nHarmonics];
  TH1D* hQtrkPtMidX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtMidY[nCentBin][nHarmonics][nPtBin];

double meanQhfPlusX[nCentBin][nHarmonics];
double meanQhfPlusY[nCentBin][nHarmonics];
double meanQhfMinusX[nCentBin][nHarmonics];
double meanQhfMinusY[nCentBin][nHarmonics];
double meanQtrkPtPlusX[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtPlusY[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtMinusX[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtMinusY[nCentBin][nHarmonics][nPtBin];
double meanQtrkMidX[nCentBin][nHarmonics];
double meanQtrkMidY[nCentBin][nHarmonics];
double meanQtrkPtMidX[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtMidY[nCentBin][nHarmonics][nPtBin];

  TH1D* hqnPlusQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnMinusQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hQnPlusQnMinusStar[nCentBin][nHarmonics];
  TH1D* hMeanPt[nCentBin][nPtBin];

//new
  TH1D* hqnQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hMeanPtMid[nCentBin][nPtBin];


  double nH[nHarmonics];
  double vnValues[nCentBin][nHarmonics][nPtBin];
  double vnErrors[nCentBin][nHarmonics][nPtBin];
  double ptValues[nCentBin][nPtBin];
//new
  double vnValuesMid[nCentBin][nHarmonics][nPtBin];
  double vnErrorsMid[nCentBin][nHarmonics][nPtBin];
  double ptValuesMid[nCentBin][nPtBin];

  TFile *inFile = new TFile("../oo_v2SPOO_feb07_trk10hf40_merged.root","read");
   for(int iC=0;iC<nCentBin;iC++){
     for(int iPt=0; iPt<nPtBin; iPt++){
       hMeanPt[iC][iPt] = (TH1D*)inFile->Get(Form("demo/hMeanPt_iC%d_iPt%d",iC, iPt));
       ptValues[iC][iPt] = hMeanPt[iC][iPt]->GetMean();
       //cout<<" cent = "<<iC<<"  mpt="<<ptValues[iC][iPt]<<endl;
//new
       hMeanPtMid[iC][iPt] = (TH1D*)inFile->Get(Form("demo/hMeanPtMid_iC%d_iPt%d",iC, iPt));
       ptValuesMid[iC][iPt] = hMeanPtMid[iC][iPt]->GetMean();
     }
     for(int iH=0; iH<nHarmonics; iH++){
       hQnPlusQnMinusStar[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQnPlusQnMinusStar_iC%d_iH%d",iC,iH));
       for(int iPt=0; iPt<nPtBin; iPt++){
         hqnPlusQnMinusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnPlusQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hqnMinusQnPlusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnMinusQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
//new
         hqnQnPlusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hqnQnMinusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
       }
       hQhfPlusX[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQhfPlusX_iC%d_iH%d",iC,iH));
       hQhfPlusY[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQhfPlusY_iC%d_iH%d",iC,iH));
       hQhfMinusX[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQhfMinusX_iC%d_iH%d",iC,iH));
       hQhfMinusY[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQhfMinusY_iC%d_iH%d",iC,iH));
       hQtrkMidX[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQtrkMidX_iC%d_iH%d",iC,iH));
       hQtrkMidY[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQtrkMidY_iC%d_iH%d",iC,iH));
       for(int iPt=0; iPt<nPtBin; iPt++){
         hQtrkPtPlusX[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hQtrkPtPlusX_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hQtrkPtPlusY[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hQtrkPtPlusY_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hQtrkPtMinusX[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hQtrkPtMinusX_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hQtrkPtMinusY[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hQtrkPtMinusY_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hQtrkPtMidX[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hQtrkPtMidX_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hQtrkPtMidY[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hQtrkPtMidY_iC%d_iH%d_iPt%d",iC,iH,iPt));
       }
     }
   } //iC

  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      meanQhfPlusX[iC][iH] = hQhfPlusX[iC][iH]->GetMean();
      meanQhfPlusY[iC][iH] = hQhfPlusY[iC][iH]->GetMean();
      meanQhfMinusX[iC][iH] = hQhfMinusX[iC][iH]->GetMean();
      meanQhfMinusY[iC][iH] = hQhfMinusY[iC][iH]->GetMean();
      for(int iPt=0; iPt<nPtBin; iPt++){
        meanQtrkPtPlusX[iC][iH][iPt] = hQtrkPtPlusX[iC][iH][iPt]->GetMean();
        meanQtrkPtPlusY[iC][iH][iPt] = hQtrkPtPlusY[iC][iH][iPt]->GetMean();
        meanQtrkPtMinusX[iC][iH][iPt] = hQtrkPtMinusX[iC][iH][iPt]->GetMean();
        meanQtrkPtMinusY[iC][iH][iPt] = hQtrkPtMinusY[iC][iH][iPt]->GetMean();
        meanQtrkPtMidX[iC][iH][iPt] = hQtrkPtMidX[iC][iH][iPt]->GetMean();
        meanQtrkPtMidY[iC][iH][iPt] = hQtrkPtMidY[iC][iH][iPt]->GetMean();
      }
      meanQtrkMidX[iC][iH] = hQtrkMidX[iC][iH]->GetMean();
      meanQtrkMidY[iC][iH] = hQtrkMidY[iC][iH]->GetMean();
    }
  } //iC
  //print 01
  ofstream outpara;
  outpara.open("recentering_para.txt");
  outpara<<"double OOmeanQhfPlusX[nCentBin][nHarmonics] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outpara<<meanQhfPlusX[iC][iH]<<", ";
    }
    if(iC<nCentBin-1){
      outpara<<meanQhfPlusX[iC][nHarmonics-1]<<"},"<<endl;
    } else {
      outpara<<meanQhfPlusX[iC][nHarmonics-1]<<"}";
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 02
  outpara<<"double OOmeanQhfPlusY[nCentBin][nHarmonics] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outpara<<meanQhfPlusY[iC][iH]<<", ";
    }
    if(iC<nCentBin-1){
      outpara<<meanQhfPlusY[iC][nHarmonics-1]<<"},"<<endl;
    } else {
      outpara<<meanQhfPlusY[iC][nHarmonics-1]<<"}";
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 03
  outpara<<"double OOmeanQhfMinusX[nCentBin][nHarmonics] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outpara<<meanQhfMinusX[iC][iH]<<", ";
    }
    if(iC<nCentBin-1){
      outpara<<meanQhfMinusX[iC][nHarmonics-1]<<"},"<<endl;
    } else {
      outpara<<meanQhfMinusX[iC][nHarmonics-1]<<"}";
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 04
  outpara<<"double OOmeanQhfMinusY[nCentBin][nHarmonics] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outpara<<meanQhfMinusY[iC][iH]<<", ";
    }
    if(iC<nCentBin-1){
      outpara<<meanQhfMinusY[iC][nHarmonics-1]<<"},"<<endl;
    } else {
      outpara<<meanQhfMinusY[iC][nHarmonics-1]<<"}";
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 05
  outpara<<"double OOmeanQtrkMidX[nCentBin][nHarmonics] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outpara<<meanQtrkMidX[iC][iH]<<", ";
    }
    if(iC<nCentBin-1){
      outpara<<meanQtrkMidX[iC][nHarmonics-1]<<"},"<<endl;
    } else {
      outpara<<meanQtrkMidX[iC][nHarmonics-1]<<"}";
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 06
  outpara<<"double OOmeanQtrkMidY[nCentBin][nHarmonics] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outpara<<meanQtrkMidY[iC][iH]<<", ";
    }
    if(iC<nCentBin-1){
      outpara<<meanQtrkMidY[iC][nHarmonics-1]<<"},"<<endl;
    } else {
      outpara<<meanQtrkMidY[iC][nHarmonics-1]<<"}";
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 07
  outpara<<"double OOmeanQtrkPtPlusX[nCentBin][nHarmonics][nPtBin] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics; iH++){
       outpara<<"{";
       for(int iPt=0; iPt<nPtBin; iPt++){
         outpara<<meanQtrkPtPlusX[iC][iH][iPt];
         if(iPt<nPtBin-1) outpara<<", ";
       }
       outpara<<"}";
       if(iH<nHarmonics-1) outpara<<", ";
    }
    outpara<<"}";
    if(iC<nCentBin-1){
      outpara<<", "<<endl;
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 08
  outpara<<"double OOmeanQtrkPtPlusY[nCentBin][nHarmonics][nPtBin] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics; iH++){
       outpara<<"{";
       for(int iPt=0; iPt<nPtBin; iPt++){
         outpara<<meanQtrkPtPlusY[iC][iH][iPt];
         if(iPt<nPtBin-1) outpara<<", ";
       }
       outpara<<"}";
       if(iH<nHarmonics-1) outpara<<", ";
    }
    outpara<<"}";
    if(iC<nCentBin-1){
      outpara<<", "<<endl;
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 09
  outpara<<"double OOmeanQtrkPtMinusX[nCentBin][nHarmonics][nPtBin] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics; iH++){
       outpara<<"{";
       for(int iPt=0; iPt<nPtBin; iPt++){
         outpara<<meanQtrkPtMinusX[iC][iH][iPt];
         if(iPt<nPtBin-1) outpara<<", ";
       }
       outpara<<"}";
       if(iH<nHarmonics-1) outpara<<", ";
    }
    outpara<<"}";
    if(iC<nCentBin-1){
      outpara<<", "<<endl;
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 10
  outpara<<"double OOmeanQtrkPtMinusY[nCentBin][nHarmonics][nPtBin] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics; iH++){
       outpara<<"{";
       for(int iPt=0; iPt<nPtBin; iPt++){
         outpara<<meanQtrkPtMinusY[iC][iH][iPt];
         if(iPt<nPtBin-1) outpara<<", ";
       }
       outpara<<"}";
       if(iH<nHarmonics-1) outpara<<", ";
    }
    outpara<<"}";
    if(iC<nCentBin-1){
      outpara<<", "<<endl;
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 11
  outpara<<"double OOmeanQtrkPtMidX[nCentBin][nHarmonics][nPtBin] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics; iH++){
       outpara<<"{";
       for(int iPt=0; iPt<nPtBin; iPt++){
         outpara<<meanQtrkPtMidX[iC][iH][iPt];
         if(iPt<nPtBin-1) outpara<<", ";
       }
       outpara<<"}";
       if(iH<nHarmonics-1) outpara<<", ";
    }
    outpara<<"}";
    if(iC<nCentBin-1){
      outpara<<", "<<endl;
    }
  } //iC
  outpara<<"};"<<endl<<endl;
  //print 12
  outpara<<"double OOmeanQtrkPtMidY[nCentBin][nHarmonics][nPtBin] = {";
  for(int iC=0;iC<nCentBin;iC++){
    outpara<<"{";
    for(int iH=0; iH<nHarmonics; iH++){
       outpara<<"{";
       for(int iPt=0; iPt<nPtBin; iPt++){
         outpara<<meanQtrkPtMidY[iC][iH][iPt];
         if(iPt<nPtBin-1) outpara<<", ";
       }
       outpara<<"}";
       if(iH<nHarmonics-1) outpara<<", ";
    }
    outpara<<"}";
    if(iC<nCentBin-1){
      outpara<<", "<<endl;
    }
  } //iC
  outpara<<"};"<<endl<<endl;



  TH1D* hqnQnStarMerged[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnQnStarMergedMid[nCentBin][nHarmonics][nPtBin];
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      for(int iPt=0; iPt<nPtBin; iPt++){
        hqnQnStarMerged[iC][iH][iPt] = (TH1D*)hqnPlusQnMinusStar[iC][iH][iPt]->Clone(Form("hqnQnStarMerged_iC%d_iH%d_iPt%d",iC,iH,iPt));
        hqnQnStarMerged[iC][iH][iPt]->Reset();
        hqnQnStarMerged[iC][iH][iPt]->Add(hqnPlusQnMinusStar[iC][iH][iPt], hqnMinusQnPlusStar[iC][iH][iPt],  1, 1);
//new
        hqnQnStarMergedMid[iC][iH][iPt] = (TH1D*)hqnQnPlusStar[iC][iH][iPt]->Clone(Form("hqnQnStarMergedMid_iC%d_iH%d_iPt%d",iC,iH,iPt));
        hqnQnStarMergedMid[iC][iH][iPt]->Reset();
        hqnQnStarMergedMid[iC][iH][iPt]->Add(hqnQnMinusStar[iC][iH][iPt], hqnQnPlusStar[iC][iH][iPt],  1, 1);
      }
    }
  } //iC

  for(int iH=0; iH<nHarmonics; iH++){ 
    nH[iH] = iH+1;
  }
  for(int iC=0;iC<nCentBin;iC++){ //nCentBin
    for(int iH=0; iH<nHarmonics; iH++){ //nHarmonics
      for(int iPt=0; iPt<nPtBin; iPt++){ //nPtBin
        vnValues[iC][iH][iPt] = hqnQnStarMerged[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()));
        vnErrors[iC][iH][iPt] = fabs(vnValues[iC][iH][iPt]) * sqrt( hqnQnStarMerged[iC][iH][iPt]->GetMeanError()*hqnQnStarMerged[iC][iH][iPt]->GetMeanError()/hqnQnStarMerged[iC][iH][iPt]->GetMean()/hqnQnStarMerged[iC][iH][iPt]->GetMean() + 1.0/4*hQnPlusQnMinusStar[iC][iH]->GetMeanError()*hQnPlusQnMinusStar[iC][iH]->GetMeanError()/hQnPlusQnMinusStar[iC][iH]->GetMean()/hQnPlusQnMinusStar[iC][iH]->GetMean() );   
//new
        vnValuesMid[iC][iH][iPt] = hqnQnStarMergedMid[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()));
        vnErrorsMid[iC][iH][iPt] = fabs(vnValuesMid[iC][iH][iPt]) * sqrt( hqnQnStarMergedMid[iC][iH][iPt]->GetMeanError()*hqnQnStarMergedMid[iC][iH][iPt]->GetMeanError()/hqnQnStarMergedMid[iC][iH][iPt]->GetMean()/hqnQnStarMergedMid[iC][iH][iPt]->GetMean() + 1.0/4*hQnPlusQnMinusStar[iC][iH]->GetMeanError()*hQnPlusQnMinusStar[iC][iH]->GetMeanError()/hQnPlusQnMinusStar[iC][iH]->GetMean()/hQnPlusQnMinusStar[iC][iH]->GetMean() );   
      }
    }
  }

  TH1D* hvn[nCentBin][nPtBin];
  for(int iC=0;iC<nCentBin;iC++){
    for(int iPt=0; iPt<nPtBin; iPt++){
      hvn[iC][iPt] = new TH1D(Form("hvn_iC%d_iPt%d", iC, iPt), Form("hvn_iC%d_iPt%d", iC, iPt), 20,0.5,20.5);
      for(int iH=0; iH<nHarmonics; iH++){
        hvn[iC][iPt]->SetBinContent(iH+1, vnValues[iC][iH][iPt]);
        hvn[iC][iPt]->SetBinError(iH+1, vnErrors[iC][iH][iPt]);
      }
    }
  }


//draw 
  TCanvas *c1 = new TCanvas("c1","c1",1150,650);
  c1->SetFillColor(10);
  c1->SetFrameFillColor(0);
  c1->SetFrameBorderSize(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.12);
  c1->SetTopMargin(0.03);
  c1->SetRightMargin(0.02);
  gStyle->SetOptStat(0);
  c1->SetTicks(-1);
  //c1->Divide(4,3);
  c1->Divide(3,2,0,0);
  //gPad->SetLogy();

 TH1D* hist = new TH1D("hist","",106,-0.1,51.5);
 hist->SetXTitle("p_{T} (GeV)");
 hist->SetYTitle("v_{n}{SP}");
 hist->SetMinimum(-0.09);
 hist->SetMaximum(0.305);
 hist->GetXaxis()->CenterTitle(1);
 hist->GetYaxis()->CenterTitle(1);
 hist->GetYaxis()->SetTitleOffset(0.99);
 hist->GetXaxis()->SetTitleOffset(0.95);
 hist->GetXaxis()->SetTitleSize(0.066);
 hist->GetYaxis()->SetTitleSize(0.066);
 hist->GetXaxis()->SetLabelSize(0.05);
 hist->GetYaxis()->SetLabelSize(0.05);
 hist->GetXaxis()->SetNdivisions(508);
 hist->GetYaxis()->SetNdivisions(508);

    TLatex *tex= new TLatex();
    tex->SetTextColor(1);
    tex->SetTextSize(0.07);
    tex->SetTextFont(42);

  TGraphErrors *graph[nCentBin][nHarmonics];
  TGraphErrors *graphMid[nCentBin][nHarmonics];
  for(int iC=0;iC<nCentBin;iC++){ //nCentBin
    for(int iH=0; iH<nHarmonics; iH++){ //nHarmonics
      graph[iC][iH] = new TGraphErrors(nPtBin-2,ptValues[iC],vnValues[iC][iH],0,vnErrors[iC][iH]);
      graphMid[iC][iH] = new TGraphErrors(nPtBin-2,ptValuesMid[iC],vnValuesMid[iC][iH],0,vnErrorsMid[iC][iH]);
    }
  }



  for(int i=0; i<nCentBin; i++){
    c1->cd(i+1);
    gPad->SetTicks(-1);
    //gPad->SetLogy();
    if(i==2||i==5||i==11){
      gPad->SetRightMargin(0.02);
    }
    if(i==0||i==3||i==6){
      gPad->SetLeftMargin(0.16);
    }    
   if(i==3||i==4||i==5||i==11){
      gPad->SetBottomMargin(0.16);
    }
 
    hist->Draw();
    //if(i==nCentBin) break;
    graph[i][1]->SetTitle("");
    graph[i][1]->SetMarkerStyle(20);
    graph[i][1]->SetMarkerSize(1.2);
    graph[i][1]->SetMarkerColor(2);
    graph[i][1]->SetLineWidth(2);
    graph[i][1]->SetLineColor(2);
    graph[i][1]->Draw("psameez");

    graph[i][2]->SetTitle("");
    graph[i][2]->SetMarkerStyle(24);
    graph[i][2]->SetMarkerSize(1.2);
    graph[i][2]->SetMarkerColor(4);
    graph[i][2]->SetLineWidth(2);
    graph[i][2]->SetLineColor(4);
    graph[i][2]->Draw("psameez");

    graphMid[i][1]->SetTitle("");
    graphMid[i][1]->SetMarkerStyle(21);
    graphMid[i][1]->SetMarkerSize(1.2);
    graphMid[i][1]->SetMarkerColor(2);
    graphMid[i][1]->SetLineWidth(2);
    graphMid[i][1]->SetLineColor(2);
//    graphMid[i][1]->Draw("psameez");

    graphMid[i][2]->SetTitle("");
    graphMid[i][2]->SetMarkerStyle(25);
    graphMid[i][2]->SetMarkerSize(1.2);
    graphMid[i][2]->SetMarkerColor(4);
    graphMid[i][2]->SetLineWidth(2);
    graphMid[i][2]->SetLineColor(4);
//    graphMid[i][2]->Draw("psameez");

    graph[i][3]->SetTitle("");
    graph[i][3]->SetMarkerStyle(25);
    graph[i][3]->SetMarkerSize(1.2);
    graph[i][3]->SetMarkerColor(1);
    graph[i][3]->SetLineWidth(2);
    graph[i][3]->SetLineColor(1);
    //graph[i][3]->Draw("psameez");

    hvn[2][i]->SetMaximum(5.5*hvn[2][i]->GetMaximum());
    hvn[2][i]->SetMinimum(0.000002);
    hvn[2][i]->SetMarkerStyle(20);
    hvn[2][i]->SetMarkerColor(1);
    hvn[2][i]->SetMarkerSize(0.6);
    //hvn[2][i]->Draw("pez");

    tex->DrawLatex(5, 0.85*hist->GetMaximum(), Form("%d-%d%%", cBin[i], cBin[i+1]));

  }  

    c1->cd(1);
    TLegend *leg = new TLegend(0.55,0.56,0.89,0.78);
    leg->SetFillColor(10);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextColor(1);
    leg->SetTextSize(0.075);
    //leg->SetLineStyle(0.06);
    leg->AddEntry(graph[0][1],"v_{2}{SP}","pl");
    leg->AddEntry(graph[0][2],"v_{3}{SP}","pl");
//    leg->AddEntry(graphMid[0][1],"v_{2}{SP} - Mid","pl");
//    leg->AddEntry(graphMid[0][2],"v_{3}{SP} - Mid","pl");
    //leg->AddEntry(graph[0][3],"v_{4}{SP}","pl");
    leg->Draw();

    tex->DrawLatex(25.8, 0.85*hist->GetMaximum(), Form("OO 5.36 TeV"));
    tex->DrawLatex(25.8, 0.75*hist->GetMaximum(), Form("HF |#eta|>4"));

  c1->SaveAs("plot_cent_vn_centX.png");
  c1->SaveAs("plot_cent_vn_centX.pdf");


    TFile *f = new TFile("output_graph_sp.root","recreate");
    f->cd();

    for(int iC=0;iC<nCentBin;iC++){
      for(int iH=0; iH<nHarmonics; iH++){
        //graph[iC][iH]->SetName(Form("v%d_cent%d", iH+1, iC));
        //graph[iC][iH]->SetTitle(Form("v%d (cent %d)", iH+1, iC));
        //graph[iC][iH]->Write();
        graph[iC][iH]->Write(Form("v%d_cent%d", iH+1, iC));
      }
       for(int iPt=0; iPt<nPtBin; iPt++){
         hMeanPt[iC][iPt]->Write(Form("pt%d_cent%d", iPt, iC));
       }
    }

     f->Write();
     f->Close();  
  

}


