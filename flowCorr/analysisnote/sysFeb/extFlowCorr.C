#include "TComplex.h"
#include "TString.h"
#include <vector>
#include <TVector3.h>
#include "TDirectory.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TMath.h"
#include <fstream>
#include <iostream>

#define nCentBin 14
#define nHarmonics 8
#define nPtBin 20 

void extFlowCorr(){

TH1D::SetDefaultSumw2();

  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  //double cBin[nCentBin+1]={0,20,60,70,80,81,82,84,86,88,90,92,94,96,100};
  double ptBin[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20.0};

  TH1D* hVnAbs2[nCentBin][nHarmonics];
  TH1D* hVnAbs4[nCentBin][nHarmonics];
  TH1D* hVnAbs6[nCentBin][nHarmonics];
  TH1D* hVnAbs8[nCentBin][nHarmonics];
  TH1D* hV2Abs2V3Abs2[nCentBin];
  TH1D* hV2Abs4V3Abs2[nCentBin];
  TH1D* hV2Abs2V3Abs4[nCentBin];
  //trk 
  TH1D* hV2Abs4trk1[nCentBin];
  TH1D* hV2Abs6trk1[nCentBin];
  TH1D* hV3Abs4trk1[nCentBin];
  TH1D* hV2Abs2V3Abs2trk1[nCentBin];
  TH1D* hV2Abs4V3Abs2trk1[nCentBin];
  TH1D* hV2Abs4trk12[nCentBin];
  TH1D* hV2Abs6trk12[nCentBin];
  TH1D* hV3Abs4trk12[nCentBin];
  TH1D* hV2Abs2V3Abs2trk12[nCentBin];
  TH1D* hV2Abs4V3Abs2trk12[nCentBin];

  TH1D* hq2Q2PstarAB[nCentBin][nPtBin];
  TH1D* hq3Q3PstarAB[nCentBin][nPtBin];
  TH1D* hq4Q4PstarAB[nCentBin][nPtBin];
  TH1D* hq5Q5PstarAB[nCentBin][nPtBin];
  TH1D* hq6Q6PstarAB[nCentBin][nPtBin];
  TH1D* hq7Q7PstarAB[nCentBin][nPtBin];
  TH1D* hq8Q8PstarAB[nCentBin][nPtBin];
  TH1D* hq2Q2MstarAB[nCentBin][nPtBin];
  TH1D* hq3Q3MstarAB[nCentBin][nPtBin];
  TH1D* hq4Q4MstarAB[nCentBin][nPtBin];
  TH1D* hq5Q5MstarAB[nCentBin][nPtBin];
  TH1D* hq6Q6MstarAB[nCentBin][nPtBin];
  TH1D* hq7Q7MstarAB[nCentBin][nPtBin];
  TH1D* hq8Q8MstarAB[nCentBin][nPtBin];

  TH1D* hq4Q2starQ2starAB[nCentBin][nPtBin];
  TH1D* hq6Q2starQ2starQ2starAB[nCentBin][nPtBin];
  TH1D* hq6Q3starQ3starAB[nCentBin][nPtBin];
  TH1D* hq5Q2starQ3starAB[nCentBin][nPtBin];
  TH1D* hq7Q2starQ2starQ3starAB[nCentBin][nPtBin];
  TH1D* hQ2Abs4AB[nCentBin][nPtBin];
  TH1D* hQ2Abs6AB[nCentBin][nPtBin];
  TH1D* hQ3Abs4AB[nCentBin][nPtBin];
  TH1D* hQ2Abs2Q3Abs2AB[nCentBin][nPtBin];
  TH1D* hQ2Abs4Q3Abs2AB[nCentBin][nPtBin];

  TH1D* hMeanPt[nCentBin][nPtBin];

  TFile* inFile = new TFile("./flowCorr_data_5020_v05Ana_5TevCentRec_dec05B_merged.root");
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hVnAbs2[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hVnAbs2_ibin%d_iH%d",ibin,iH));
      hVnAbs4[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hVnAbs4_ibin%d_iH%d",ibin,iH));
      hVnAbs6[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hVnAbs6_ibin%d_iH%d",ibin,iH));
      hVnAbs8[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hVnAbs8_ibin%d_iH%d",ibin,iH));
    }
    hV2Abs2V3Abs2[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs2V3Abs2_ibin%d",ibin));
    hV2Abs4V3Abs2[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs4V3Abs2_ibin%d",ibin));
    hV2Abs2V3Abs4[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs2V3Abs4_ibin%d",ibin));
    //trk
    hV2Abs4trk1[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs4trk1_ibin%d",ibin));
    hV2Abs6trk1[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs6trk1_ibin%d",ibin));
    hV3Abs4trk1[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV3Abs4trk1_ibin%d",ibin));
    hV2Abs2V3Abs2trk1[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs2V3Abs2trk1_ibin%d",ibin));
    hV2Abs4V3Abs2trk1[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs4V3Abs2trk1_ibin%d",ibin));
    hV2Abs4trk12[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs4trk12_ibin%d",ibin));
    hV2Abs6trk12[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs6trk12_ibin%d",ibin));
    hV3Abs4trk12[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV3Abs4trk12_ibin%d",ibin));
    hV2Abs2V3Abs2trk12[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs2V3Abs2trk12_ibin%d",ibin));
    hV2Abs4V3Abs2trk12[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2Abs4V3Abs2trk12_ibin%d",ibin));

    for(int ipt=0; ipt<nPtBin; ipt++){

      hq2Q2PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq2Q2PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq3Q3PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq3Q3PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq4Q4PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq4Q4PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq5Q5PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq5Q5PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq6Q6PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q6PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq7Q7PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq7Q7PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq8Q8PstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq8Q8PstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq2Q2MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq2Q2MstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq3Q3MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq3Q3MstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq4Q4MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq4Q4MstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq5Q5MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq5Q5MstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq6Q6MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q6MstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq7Q7MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq7Q7MstarAB_ibin%d_ipt%d",ibin,ipt)); 
      hq8Q8MstarAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq8Q8MstarAB_ibin%d_ipt%d",ibin,ipt)); 

      hq4Q2starQ2starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq4Q2starQ2starAB_ibin%d_ipt%d",ibin,ipt));
      hq6Q2starQ2starQ2starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q2starQ2starQ2starAB_ibin%d_ipt%d",ibin,ipt));
      hq6Q3starQ3starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q3starQ3starAB_ibin%d_ipt%d",ibin,ipt));
      hq5Q2starQ3starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq5Q2starQ3starAB_ibin%d_ipt%d",ibin,ipt));
      hq7Q2starQ2starQ3starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq7Q2starQ2starQ3starAB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4AB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs6AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs6AB_ibin%d_ipt%d",ibin,ipt));
      hQ3Abs4AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ3Abs4AB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs2Q3Abs2AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs2Q3Abs2AB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4Q3Abs2AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4Q3Abs2AB_ibin%d_ipt%d",ibin,ipt));

      hMeanPt[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hMeanPt_ibin%d_ipt%d",ibin,ipt));
    }
  }

  double value;
  double err;

  ofstream outv22;
  outv22.open("outv22_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv22<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][1]->GetMean()>0)
        value=(hq2Q2PstarAB[ibin][ipt]->GetMean()+hq2Q2MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][1]->GetMean());
      else value=(hq2Q2PstarAB[ibin][ipt]->GetMean()+hq2Q2MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][1]->GetMean());
      err=value*sqrt(hq2Q2MstarAB[ibin][ipt]->GetMeanError()*hq2Q2MstarAB[ibin][ipt]->GetMeanError()/hq2Q2MstarAB[ibin][ipt]->GetMean()/hq2Q2MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][1]->GetMeanError()*hVnAbs2[ibin][1]->GetMeanError()/hVnAbs2[ibin][1]->GetMean()/hVnAbs2[ibin][1]->GetMean());
      outv22<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv33;
  outv33.open("outv33_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv33<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][2]->GetMean()>0)
        value=(hq3Q3PstarAB[ibin][ipt]->GetMean()+hq3Q3MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][2]->GetMean());
      else value=(hq3Q3PstarAB[ibin][ipt]->GetMean()+hq3Q3MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][2]->GetMean());
      err=value*sqrt(hq3Q3MstarAB[ibin][ipt]->GetMeanError()*hq3Q3MstarAB[ibin][ipt]->GetMeanError()/hq3Q3MstarAB[ibin][ipt]->GetMean()/hq3Q3MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][2]->GetMeanError()*hVnAbs2[ibin][2]->GetMeanError()/hVnAbs2[ibin][2]->GetMean()/hVnAbs2[ibin][2]->GetMean());
      outv33<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv44;
  outv44.open("outv44_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv44<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][3]->GetMean()>0)
        value=(hq4Q4PstarAB[ibin][ipt]->GetMean()+hq4Q4MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][3]->GetMean());
      else value=(hq4Q4PstarAB[ibin][ipt]->GetMean()+hq4Q4MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][3]->GetMean());
      err=value*sqrt(hq4Q4MstarAB[ibin][ipt]->GetMeanError()*hq4Q4MstarAB[ibin][ipt]->GetMeanError()/hq4Q4MstarAB[ibin][ipt]->GetMean()/hq4Q4MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][3]->GetMeanError()*hVnAbs2[ibin][3]->GetMeanError()/hVnAbs2[ibin][3]->GetMean()/hVnAbs2[ibin][3]->GetMean());
      outv44<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv55;
  outv55.open("outv55_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv55<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][4]->GetMean()>0)
        value=(hq5Q5PstarAB[ibin][ipt]->GetMean()+hq5Q5MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][4]->GetMean());
      else value=(hq5Q5PstarAB[ibin][ipt]->GetMean()+hq5Q5MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][4]->GetMean());
      err=value*sqrt(hq5Q5MstarAB[ibin][ipt]->GetMeanError()*hq5Q5MstarAB[ibin][ipt]->GetMeanError()/hq5Q5MstarAB[ibin][ipt]->GetMean()/hq5Q5MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][4]->GetMeanError()*hVnAbs2[ibin][4]->GetMeanError()/hVnAbs2[ibin][4]->GetMean()/hVnAbs2[ibin][4]->GetMean());
      outv55<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv66;
  outv66.open("outv66_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv66<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][5]->GetMean()>0)
        value=(hq6Q6PstarAB[ibin][ipt]->GetMean()+hq6Q6MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][5]->GetMean());
      else value=(hq6Q6PstarAB[ibin][ipt]->GetMean()+hq6Q6MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][5]->GetMean());
      err=value*sqrt(hq6Q6MstarAB[ibin][ipt]->GetMeanError()*hq6Q6MstarAB[ibin][ipt]->GetMeanError()/hq6Q6MstarAB[ibin][ipt]->GetMean()/hq6Q6MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][5]->GetMeanError()*hVnAbs2[ibin][5]->GetMeanError()/hVnAbs2[ibin][5]->GetMean()/hVnAbs2[ibin][5]->GetMean());
      outv66<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv77;
  outv77.open("outv77_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv77<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][6]->GetMean()>0)
        value=(hq7Q7PstarAB[ibin][ipt]->GetMean()+hq7Q7MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][6]->GetMean());
      else value=(hq7Q7PstarAB[ibin][ipt]->GetMean()+hq7Q7MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][6]->GetMean());
      err=value*sqrt(hq7Q7MstarAB[ibin][ipt]->GetMeanError()*hq7Q7MstarAB[ibin][ipt]->GetMeanError()/hq7Q7MstarAB[ibin][ipt]->GetMean()/hq7Q7MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][6]->GetMeanError()*hVnAbs2[ibin][6]->GetMeanError()/hVnAbs2[ibin][6]->GetMean()/hVnAbs2[ibin][6]->GetMean());
      outv77<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv88;
  outv88.open("outv88_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv88<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][7]->GetMean()>0)
        value=(hq8Q8PstarAB[ibin][ipt]->GetMean()+hq8Q8MstarAB[ibin][ipt]->GetMean())/2.0/sqrt(hVnAbs2[ibin][7]->GetMean());
      else value=(hq8Q8PstarAB[ibin][ipt]->GetMean()+hq8Q8MstarAB[ibin][ipt]->GetMean())/2.0/sqrt((-1)*hVnAbs2[ibin][7]->GetMean());
      err=value*sqrt(hq8Q8MstarAB[ibin][ipt]->GetMeanError()*hq8Q8MstarAB[ibin][ipt]->GetMeanError()/hq8Q8MstarAB[ibin][ipt]->GetMean()/hq8Q8MstarAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][7]->GetMeanError()*hVnAbs2[ibin][7]->GetMeanError()/hVnAbs2[ibin][7]->GetMean()/hVnAbs2[ibin][7]->GetMean());
      outv88<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outv42;
  outv42.open("outv42_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv42<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs4[ibin][1]->GetMean()>0)
        value=hq4Q2starQ2starAB[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][1]->GetMean());
      else value=hq4Q2starQ2starAB[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs4[ibin][1]->GetMean());
      err=value*sqrt(hq4Q2starQ2starAB[ibin][ipt]->GetMeanError()*hq4Q2starQ2starAB[ibin][ipt]->GetMeanError()/hq4Q2starQ2starAB[ibin][ipt]->GetMean()/hq4Q2starQ2starAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][1]->GetMeanError()*hVnAbs4[ibin][1]->GetMeanError()/hVnAbs4[ibin][1]->GetMean()/hVnAbs4[ibin][1]->GetMean());
      outv42<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }


  ofstream outv62;
  outv62.open("outv62_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv62<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs6[ibin][1]->GetMean()>0)
        value=hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/sqrt(hVnAbs6[ibin][1]->GetMean());
      else value=hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs6[ibin][1]->GetMean());
      err=value*sqrt(hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError()*hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError()/hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs6[ibin][1]->GetMeanError()*hVnAbs6[ibin][1]->GetMeanError()/hVnAbs6[ibin][1]->GetMean()/hVnAbs6[ibin][1]->GetMean());
      outv62<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv63;
  outv63.open("outv63_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv63<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs4[ibin][2]->GetMean()>0)
        value=hq6Q3starQ3starAB[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][2]->GetMean());
      else value=hq6Q3starQ3starAB[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs4[ibin][2]->GetMean());
      err=value*sqrt(hq6Q3starQ3starAB[ibin][ipt]->GetMeanError()*hq6Q3starQ3starAB[ibin][ipt]->GetMeanError()/hq6Q3starQ3starAB[ibin][ipt]->GetMean()/hq6Q3starQ3starAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][2]->GetMeanError()*hVnAbs4[ibin][2]->GetMeanError()/hVnAbs4[ibin][2]->GetMean()/hVnAbs4[ibin][2]->GetMean());
      outv63<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outv523;
  outv523.open("outv523_corrFlow.txt");  
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv523<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hV2Abs2V3Abs2[ibin]->GetMean()>0)
        value=hq5Q2starQ3starAB[ibin][ipt]->GetMean()/sqrt(hV2Abs2V3Abs2[ibin]->GetMean());
      else value=hq5Q2starQ3starAB[ibin][ipt]->GetMean()/sqrt((-1)*hV2Abs2V3Abs2[ibin]->GetMean());
      err=value*sqrt(hq5Q2starQ3starAB[ibin][ipt]->GetMeanError()*hq5Q2starQ3starAB[ibin][ipt]->GetMeanError()/hq5Q2starQ3starAB[ibin][ipt]->GetMean()/hq5Q2starQ3starAB[ibin][ipt]->GetMean() + 1.0/4*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
      outv523<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outv723;
  outv723.open("outv723_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv723<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hV2Abs4V3Abs2[ibin]->GetMean()>0)
        value=hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/sqrt(hV2Abs4V3Abs2[ibin]->GetMean());
      else value=hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/sqrt((-1)*hV2Abs4V3Abs2[ibin]->GetMean());
      err=value*sqrt(hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError()*hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError()/hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean() + 1.0/4*hV2Abs4V3Abs2[ibin]->GetMeanError()*hV2Abs4V3Abs2[ibin]->GetMeanError()/hV2Abs4V3Abs2[ibin]->GetMean()/hV2Abs4V3Abs2[ibin]->GetMean());
      outv723<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
/*
  ofstream outv82;
  outv82.open("outv82_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv82<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs8[ibin][1]->GetMean()>0)
        value=hv8V2starV2starV2starV2star[ibin][ipt]->GetMean()/sqrt(hVnAbs8[ibin][1]->GetMean());
      else value=hv8V2starV2starV2starV2star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs8[ibin][1]->GetMean());
      err=value*sqrt(hv8V2starV2starV2starV2star[ibin][ipt]->GetMeanError()*hv8V2starV2starV2starV2star[ibin][ipt]->GetMeanError()/hv8V2starV2starV2starV2star[ibin][ipt]->GetMean()/hv8V2starV2starV2starV2star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs8[ibin][1]->GetMeanError()*hVnAbs8[ibin][1]->GetMeanError()/hVnAbs8[ibin][1]->GetMean()/hVnAbs8[ibin][1]->GetMean());
      outv82<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv8233;
  outv8233.open("outv8233_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv8233<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hV2Abs2V3Abs4[ibin]->GetMean()>0)
        value=hv8V2starV3starV3star[ibin][ipt]->GetMean()/sqrt(hV2Abs2V3Abs4[ibin]->GetMean());
      else value=hv8V2starV3starV3star[ibin][ipt]->GetMean()/sqrt((-1)*hV2Abs2V3Abs4[ibin]->GetMean());
      err=value*sqrt(hv8V2starV3starV3star[ibin][ipt]->GetMeanError()*hv8V2starV3starV3star[ibin][ipt]->GetMeanError()/hv8V2starV3starV3star[ibin][ipt]->GetMean()/hv8V2starV3starV3star[ibin][ipt]->GetMean() + 1.0/4*hV2Abs2V3Abs4[ibin]->GetMeanError()*hV2Abs2V3Abs4[ibin]->GetMeanError()/hV2Abs2V3Abs4[ibin]->GetMean()/hV2Abs2V3Abs4[ibin]->GetMean());
      outv8233<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
*/

// chi
  ofstream outchi422D;
  outchi422D.open("outchi422D_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi422D<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hq4Q2starQ2starAB[ibin][ipt]->GetMean()/hQ2Abs4AB[ibin][ipt]->GetMean();
        err=value*sqrt(hq4Q2starQ2starAB[ibin][ipt]->GetMeanError()*hq4Q2starQ2starAB[ibin][ipt]->GetMeanError()/hq4Q2starQ2starAB[ibin][ipt]->GetMean()/hq4Q2starQ2starAB[ibin][ipt]->GetMean()  + 1.0/1*hQ2Abs4AB[ibin][ipt]->GetMeanError()*hQ2Abs4AB[ibin][ipt]->GetMeanError()/hQ2Abs4AB[ibin][ipt]->GetMean()/hQ2Abs4AB[ibin][ipt]->GetMean());
      outchi422D<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi422Num;
  outchi422Num.open("outchi422Num_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi422Num<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hq4Q2starQ2starAB[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][1]->GetMean());
      err=value*sqrt(hq4Q2starQ2starAB[ibin][ipt]->GetMeanError()*hq4Q2starQ2starAB[ibin][ipt]->GetMeanError()/hq4Q2starQ2starAB[ibin][ipt]->GetMean()/hq4Q2starQ2starAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][1]->GetMeanError()*hVnAbs4[ibin][1]->GetMeanError()/hVnAbs4[ibin][1]->GetMean()/hVnAbs4[ibin][1]->GetMean());
      //value=hq4Q2starQ2starAB[ibin][ipt]->GetMean();
      //err=hq4Q2starQ2starAB[ibin][ipt]->GetMeanError();
      outchi422Num<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi422Den;
  outchi422Den.open("outchi422Den_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi422Den<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ2Abs4AB[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][1]->GetMean());
      err=value*sqrt(hQ2Abs4AB[ibin][ipt]->GetMeanError()*hQ2Abs4AB[ibin][ipt]->GetMeanError()/hQ2Abs4AB[ibin][ipt]->GetMean()/hQ2Abs4AB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][1]->GetMeanError()*hVnAbs4[ibin][1]->GetMeanError()/hVnAbs4[ibin][1]->GetMean()/hVnAbs4[ibin][1]->GetMean());
      //value=hQ2Abs4AB[ibin][ipt]->GetMean();
      //err=hQ2Abs4AB[ibin][ipt]->GetMeanError();
      outchi422Den<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outchi523D;
  outchi523D.open("outchi523D_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi523D<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hq5Q2starQ3starAB[ibin][ipt]->GetMean()/hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean();
        err=value*sqrt(hq5Q2starQ3starAB[ibin][ipt]->GetMeanError()*hq5Q2starQ3starAB[ibin][ipt]->GetMeanError()/hq5Q2starQ3starAB[ibin][ipt]->GetMean()/hq5Q2starQ3starAB[ibin][ipt]->GetMean()  + 1.0/1*hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMeanError()*hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMeanError()/hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean()/hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean());
      outchi523D<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi523Num;
  outchi523Num.open("outchi523Num_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi523Num<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hq5Q2starQ3starAB[ibin][ipt]->GetMean()/sqrt(hV2Abs2V3Abs2[ibin]->GetMean());
      err=value*sqrt(hq5Q2starQ3starAB[ibin][ipt]->GetMeanError()*hq5Q2starQ3starAB[ibin][ipt]->GetMeanError()/hq5Q2starQ3starAB[ibin][ipt]->GetMean()/hq5Q2starQ3starAB[ibin][ipt]->GetMean() + 1.0/4*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
      //value=hq5Q2starQ3starAB[ibin][ipt]->GetMean();
      //err=hq5Q2starQ3starAB[ibin][ipt]->GetMeanError();
      outchi523Num<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi523Den;
  outchi523Den.open("outchi523Den_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi523Den<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean()/sqrt(hV2Abs2V3Abs2[ibin]->GetMean());
      err=value*sqrt(hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMeanError()*hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMeanError()/hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean()/hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean() + 1.0/4*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
      //value=hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMean();
      //err=hQ2Abs2Q3Abs2AB[ibin][ipt]->GetMeanError();
      outchi523Den<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outchi6222D;
  outchi6222D.open("outchi6222D_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi6222D<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/hQ2Abs6AB[ibin][ipt]->GetMean();
        err=value*sqrt(hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError()*hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError()/hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()  + 1.0/1*hQ2Abs6AB[ibin][ipt]->GetMeanError()*hQ2Abs6AB[ibin][ipt]->GetMeanError()/hQ2Abs6AB[ibin][ipt]->GetMean()/hQ2Abs6AB[ibin][ipt]->GetMean());
      outchi6222D<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi6222Num;
  outchi6222Num.open("outchi6222Num_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi6222Num<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/sqrt(hVnAbs6[ibin][1]->GetMean());
      err=value*sqrt(hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError()*hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError()/hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean()/hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs6[ibin][1]->GetMeanError()*hVnAbs6[ibin][1]->GetMeanError()/hVnAbs6[ibin][1]->GetMean()/hVnAbs6[ibin][1]->GetMean());
      //value=hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMean();
      //err=hq6Q2starQ2starQ2starAB[ibin][ipt]->GetMeanError();
      outchi6222Num<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi6222Den;
  outchi6222Den.open("outchi6222Den_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi6222Den<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ2Abs6AB[ibin][ipt]->GetMean()/sqrt(hVnAbs6[ibin][1]->GetMean());
      err=value*sqrt(hQ2Abs6AB[ibin][ipt]->GetMeanError()*hQ2Abs6AB[ibin][ipt]->GetMeanError()/hQ2Abs6AB[ibin][ipt]->GetMean()/hQ2Abs6AB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs6[ibin][1]->GetMeanError()*hVnAbs6[ibin][1]->GetMeanError()/hVnAbs6[ibin][1]->GetMean()/hVnAbs6[ibin][1]->GetMean());
      //value=hQ2Abs6AB[ibin][ipt]->GetMean();
      //err=hQ2Abs6AB[ibin][ipt]->GetMeanError();
      outchi6222Den<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi633D;
  outchi633D.open("outchi633D_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi633D<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hq6Q3starQ3starAB[ibin][ipt]->GetMean()/hQ3Abs4AB[ibin][ipt]->GetMean();
        err=value*sqrt(hq6Q3starQ3starAB[ibin][ipt]->GetMeanError()*hq6Q3starQ3starAB[ibin][ipt]->GetMeanError()/hq6Q3starQ3starAB[ibin][ipt]->GetMean()/hq6Q3starQ3starAB[ibin][ipt]->GetMean()  + 1.0/1*hQ3Abs4AB[ibin][ipt]->GetMeanError()*hQ3Abs4AB[ibin][ipt]->GetMeanError()/hQ3Abs4AB[ibin][ipt]->GetMean()/hQ3Abs4AB[ibin][ipt]->GetMean());
      outchi633D<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi633Num;
  outchi633Num.open("outchi633Num_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi633Num<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hq6Q3starQ3starAB[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][2]->GetMean());
      err=value*sqrt(hq6Q3starQ3starAB[ibin][ipt]->GetMeanError()*hq6Q3starQ3starAB[ibin][ipt]->GetMeanError()/hq6Q3starQ3starAB[ibin][ipt]->GetMean()/hq6Q3starQ3starAB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][2]->GetMeanError()*hVnAbs4[ibin][2]->GetMeanError()/hVnAbs4[ibin][2]->GetMean()/hVnAbs4[ibin][2]->GetMean());
      //value=hq6Q3starQ3starAB[ibin][ipt]->GetMean();
      //err=hq6Q3starQ3starAB[ibin][ipt]->GetMeanError();
      outchi633Num<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi633Den;
  outchi633Den.open("outchi633Den_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi633Den<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ3Abs4AB[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][2]->GetMean());
      err=value*sqrt(hQ3Abs4AB[ibin][ipt]->GetMeanError()*hQ3Abs4AB[ibin][ipt]->GetMeanError()/hQ3Abs4AB[ibin][ipt]->GetMean()/hQ3Abs4AB[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][2]->GetMeanError()*hVnAbs4[ibin][2]->GetMeanError()/hVnAbs4[ibin][2]->GetMean()/hVnAbs4[ibin][2]->GetMean());
      //value=hQ3Abs4AB[ibin][ipt]->GetMean();
      //err=hQ3Abs4AB[ibin][ipt]->GetMeanError();
      outchi633Den<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi7223D;
  outchi7223D.open("outchi7223D_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi7223D<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean();
        err=value*sqrt(hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError()*hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError()/hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()  + 1.0/1*hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMeanError()*hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMeanError()/hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean()/hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean());
      outchi7223D<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi7223Num;
  outchi7223Num.open("outchi7223Num_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi7223Num<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/sqrt(hV2Abs4V3Abs2[ibin]->GetMean());
      err=value*sqrt(hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError()*hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError()/hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean()/hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean() + 1.0/4*hV2Abs4V3Abs2[ibin]->GetMeanError()*hV2Abs4V3Abs2[ibin]->GetMeanError()/hV2Abs4V3Abs2[ibin]->GetMean()/hV2Abs4V3Abs2[ibin]->GetMean());
      //value=hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMean();
      //err=hq7Q2starQ2starQ3starAB[ibin][ipt]->GetMeanError();
      outchi7223Num<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outchi7223Den;
  outchi7223Den.open("outchi7223Den_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi7223Den<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean()/sqrt(hV2Abs4V3Abs2[ibin]->GetMean());
      err=value*sqrt(hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMeanError()*hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMeanError()/hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean()/hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean() + 1.0/4*hV2Abs4V3Abs2[ibin]->GetMeanError()*hV2Abs4V3Abs2[ibin]->GetMeanError()/hV2Abs4V3Abs2[ibin]->GetMean()/hV2Abs4V3Abs2[ibin]->GetMean());
      //value=hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMean();
      //err=hQ2Abs4Q3Abs2AB[ibin][ipt]->GetMeanError();
      outchi7223Den<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }


  for(int ibin=0; ibin<nCentBin; ibin++)
    cout<<(cBin[ibin]+cBin[ibin+1])*1.0/2.0<<"  "<<hQ2Abs4Q3Abs2AB[ibin][8]->GetMean()<<"  "<<hV2Abs4V3Abs2[ibin]->GetMean()<<endl;

  TCanvas *c01 = new TCanvas("c01","c01",1,1,1110,760);
  c01->SetFillColor(10);
  c01->SetFrameFillColor(0);
  c01->SetFrameBorderSize(0);
  c01->SetFrameBorderMode(0);
  c01->SetLeftMargin(0.15);
  c01->SetBottomMargin(0.15);
  c01->SetTopMargin(0.02);
  c01->SetRightMargin(0.02);
  c01->Divide(2,2);
  //gStyle->SetOptStat(0);
  c01->SetTicks(-1);
  //c01->SetLogx();
  //c01->SetGridx();

  for(int ipt=0; ipt<4; ipt++){
    c01->cd(ipt+1);
    hq4Q2starQ2starAB[0][ipt]->Draw();
    cout<<"ptBin : "<< ptBin[ipt]<<"-"<<ptBin[ipt+1]<<"   hq4Q2starQ2starAB[0][ipt] entries :  "<<hq4Q2starQ2starAB[0][ipt]->GetEntries()<<endl;
  }


}



