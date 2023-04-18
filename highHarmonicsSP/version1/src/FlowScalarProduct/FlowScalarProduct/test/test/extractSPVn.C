void extractSPVn(){

  static const int nCentBin = 14;
  static const int nHarmonics = 20;
  static const int nPtBin = 18;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double ptBins[nPtBin+1]={0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20000.0};

  TH1D* hqnPlusQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnMinusQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hQnPlusQnMinusStar[nCentBin][nHarmonics];
  TH1D* hMeanPt[nCentBin][nPtBin];

  TFile *inFile = new TFile("./mergedA_pbpbMB_miniAOD_vn.root","read");
   for(int iC=0;iC<nCentBin;iC++){
     for(int iPt=0; iPt<nPtBin; iPt++){
       hMeanPt[iC][iPt] = (TH1D*)inFile->Get(Form("demo/hMeanPt_iC%d_iPt%d",iC, iPt));
     }
     for(int iH=0; iH<nHarmonics; iH++){
       hQnPlusQnMinusStar[iC][iH] = (TH1D*)inFile->Get(Form("demo/hQnPlusQnMinusStar_iC%d_iH%d",iC,iH));
       for(int iPt=0; iPt<nPtBin; iPt++){
         hqnPlusQnMinusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnPlusQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
         hqnMinusQnPlusStar[iC][iH][iPt] = (TH1D*)inFile->Get(Form("demo/hqnMinusQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt));
       }
     }
   } //iC

  TH1D* hqnQnStarMerged[nCentBin][nHarmonics][nPtBin];
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      for(int iPt=0; iPt<nPtBin; iPt++){
        hqnQnStarMerged[iC][iH][iPt] = (TH1D*)hqnPlusQnMinusStar[iC][iH][iPt]->Clone(Form("hqnQnStarMerged_iC%d_iH%d_iPt%d",iC,iH,iPt));
        hqnQnStarMerged[iC][iH][iPt]->Reset();
        hqnQnStarMerged[iC][iH][iPt]->Add(hqnPlusQnMinusStar[iC][iH][iPt], hqnMinusQnPlusStar[iC][iH][iPt],  1, 1);
      }
    }
  } //iC

  ofstream outTxtFile;
  outTxtFile.open("out_sp.txt");
  for(int iC=0;iC<nCentBin;iC++){ //nCentBin
    for(int iH=0; iH<nHarmonics; iH++){ //nHarmonics
      for(int iPt=0; iPt<nPtBin; iPt++){ //nPtBin
        cout<<iC<<"  "<<iH<<"  "<<iPt<<"  "<<hMeanPt[iC][iPt]->GetMean()<<"   "<<hqnPlusQnMinusStar[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"  "<<hqnPlusQnMinusStar[iC][iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"     "<<hqnMinusQnPlusStar[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"  "<<hqnMinusQnPlusStar[iC][iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"     "<<hqnQnStarMerged[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"  "<<hqnQnStarMerged[iC][iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<endl;
        outTxtFile<<iC<<"  "<<iH<<"  "<<iPt<<"  "<<hMeanPt[iC][iPt]->GetMean()<<"   "<<hqnPlusQnMinusStar[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"  "<<hqnPlusQnMinusStar[iC][iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"     "<<hqnMinusQnPlusStar[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"  "<<hqnMinusQnPlusStar[iC][iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"     "<<hqnQnStarMerged[iC][iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<"  "<<hqnQnStarMerged[iC][iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iC][iH]->GetMean()))<<endl;
      }
    }
  }

}


