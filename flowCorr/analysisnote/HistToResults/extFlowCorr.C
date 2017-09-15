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

  TH1D* hV2V2star[nCentBin];
  TH1D* hV4V2starV2star[nCentBin];
  TH1D* hV6V2starV2starV2star[nCentBin];
  TH1D* hV6V3starV3star[nCentBin];
  TH1D* hV5V2starV3star[nCentBin];
  TH1D* hV7V2starV2starV3star[nCentBin];

  TH1D* hv2V2star[nCentBin][nPtBin];
  TH1D* hv3V3star[nCentBin][nPtBin];
  TH1D* hv4V4star[nCentBin][nPtBin];
  TH1D* hv5V5star[nCentBin][nPtBin];
  TH1D* hv6V6star[nCentBin][nPtBin];
  TH1D* hv7V7star[nCentBin][nPtBin];
  TH1D* hv8V8star[nCentBin][nPtBin];

  TH1D* hv4V2starV2star[nCentBin][nPtBin];
  TH1D* hv6V2starV2starV2star[nCentBin][nPtBin];
  TH1D* hv6V3starV3star[nCentBin][nPtBin];
  TH1D* hv5V2starV3star[nCentBin][nPtBin];
  TH1D* hv7V2starV2starV3star[nCentBin][nPtBin];
  TH1D* hv8V2starV2starV2starV2star[nCentBin][nPtBin];
  TH1D* hv8V2starV3starV3star[nCentBin][nPtBin];
  TH1D* hq4Q2starQ2starAA[nCentBin][nPtBin];
  TH1D* hq4Q2starQ2starBB[nCentBin][nPtBin];
  TH1D* hq4Q2starQ2starAB[nCentBin][nPtBin];
  TH1D* hq6Q2starQ2starQ2starAA[nCentBin][nPtBin];
  TH1D* hq6Q2starQ2starQ2starBB[nCentBin][nPtBin];
  TH1D* hq6Q2starQ2starQ2starAB[nCentBin][nPtBin];
  TH1D* hq6Q3starQ3starAA[nCentBin][nPtBin];
  TH1D* hq6Q3starQ3starBB[nCentBin][nPtBin];
  TH1D* hq6Q3starQ3starAB[nCentBin][nPtBin];
  TH1D* hq5Q2starQ3starAA[nCentBin][nPtBin];
  TH1D* hq5Q2starQ3starBB[nCentBin][nPtBin];
  TH1D* hq5Q2starQ3starAB[nCentBin][nPtBin];
  TH1D* hq7Q2starQ2starQ3starAA[nCentBin][nPtBin];
  TH1D* hq7Q2starQ2starQ3starBB[nCentBin][nPtBin];
  TH1D* hq7Q2starQ2starQ3starAB[nCentBin][nPtBin];
  TH1D* hQ2Abs4AA[nCentBin][nPtBin];
  TH1D* hQ2Abs4BB[nCentBin][nPtBin];
  TH1D* hQ2Abs4AB[nCentBin][nPtBin];
  TH1D* hQ2Abs6AA[nCentBin][nPtBin];
  TH1D* hQ2Abs6BB[nCentBin][nPtBin];
  TH1D* hQ2Abs6AB[nCentBin][nPtBin];
  TH1D* hQ3Abs4AA[nCentBin][nPtBin];
  TH1D* hQ3Abs4BB[nCentBin][nPtBin];
  TH1D* hQ3Abs4AB[nCentBin][nPtBin];
  TH1D* hQ2Abs2Q3Abs2AA[nCentBin][nPtBin];
  TH1D* hQ2Abs2Q3Abs2BB[nCentBin][nPtBin];
  TH1D* hQ2Abs2Q3Abs2AB[nCentBin][nPtBin];
  TH1D* hQ2Abs4Q3Abs2AA[nCentBin][nPtBin];
  TH1D* hQ2Abs4Q3Abs2BB[nCentBin][nPtBin];
  TH1D* hQ2Abs4Q3Abs2AB[nCentBin][nPtBin];

  TH1D* hMeanPt[nCentBin][nPtBin];

  TFile* inFile = new TFile("../flowCorr_data_5020_v02Ana_5tevCent_sep15TRM_merged.root");
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

    hV2V2star[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV2V2star_ibin%d",ibin));
    hV4V2starV2star[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV4V2starV2star_ibin%d",ibin));
    hV6V2starV2starV2star[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV6V2starV2starV2star_ibin%d",ibin));
    hV6V3starV3star[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV6V3starV3star_ibin%d",ibin));
    hV5V2starV3star[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV5V2starV3star_ibin%d",ibin));
    hV7V2starV2starV3star[ibin] = (TH1D*)inFile->Get(Form("flowCorr/hV7V2starV2starV3star_ibin%d",ibin));
    for(int ipt=0; ipt<nPtBin; ipt++){
      hv2V2star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv2V2star_ibin%d_ipt%d",ibin,ipt));
      hv3V3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv3V3star_ibin%d_ipt%d",ibin,ipt));
      hv4V4star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv4V4star_ibin%d_ipt%d",ibin,ipt));
      hv5V5star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv5V5star_ibin%d_ipt%d",ibin,ipt));
      hv6V6star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv6V6star_ibin%d_ipt%d",ibin,ipt));
      hv7V7star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv7V7star_ibin%d_ipt%d",ibin,ipt));
      hv8V8star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv8V8star_ibin%d_ipt%d",ibin,ipt));
      hv4V2starV2star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv4V2starV2starSub_ibin%d_ipt%d",ibin,ipt));
      hv6V2starV2starV2star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv6V2starV2starV2starSub_ibin%d_ipt%d",ibin,ipt));
      hv6V3starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv6V3starV3starSub_ibin%d_ipt%d",ibin,ipt));
      hv5V2starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv5V2starV3starSub_ibin%d_ipt%d",ibin,ipt));
      hv7V2starV2starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv7V2starV2starV3starSub_ibin%d_ipt%d",ibin,ipt));
      //hv4V2starV2star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv4V2starV2star_ibin%d_ipt%d",ibin,ipt));
      //hv6V2starV2starV2star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv6V2starV2starV2star_ibin%d_ipt%d",ibin,ipt));
      //hv6V3starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv6V3starV3star_ibin%d_ipt%d",ibin,ipt));
      //hv5V2starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv5V2starV3star_ibin%d_ipt%d",ibin,ipt));
      //hv7V2starV2starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv7V2starV2starV3star_ibin%d_ipt%d",ibin,ipt));
      hv8V2starV2starV2starV2star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv8V2starV2starV2starV2star_ibin%d_ipt%d",ibin,ipt));
      hv8V2starV3starV3star[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hv8V2starV3starV3star_ibin%d_ipt%d",ibin,ipt));

      hq4Q2starQ2starAA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq4Q2starQ2starAA_ibin%d_ipt%d",ibin,ipt));
      hq4Q2starQ2starBB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq4Q2starQ2starBB_ibin%d_ipt%d",ibin,ipt));
      hq4Q2starQ2starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq4Q2starQ2starAB_ibin%d_ipt%d",ibin,ipt));
      hq6Q2starQ2starQ2starAA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q2starQ2starQ2starAA_ibin%d_ipt%d",ibin,ipt));
      hq6Q2starQ2starQ2starBB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q2starQ2starQ2starBB_ibin%d_ipt%d",ibin,ipt));
      hq6Q2starQ2starQ2starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q2starQ2starQ2starAB_ibin%d_ipt%d",ibin,ipt));
      hq6Q3starQ3starAA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q3starQ3starAA_ibin%d_ipt%d",ibin,ipt));
      hq6Q3starQ3starBB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q3starQ3starBB_ibin%d_ipt%d",ibin,ipt));
      hq6Q3starQ3starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq6Q3starQ3starAB_ibin%d_ipt%d",ibin,ipt));
      hq5Q2starQ3starAA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq5Q2starQ3starAA_ibin%d_ipt%d",ibin,ipt));
      hq5Q2starQ3starBB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq5Q2starQ3starBB_ibin%d_ipt%d",ibin,ipt));
      hq5Q2starQ3starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq5Q2starQ3starAB_ibin%d_ipt%d",ibin,ipt));
      hq7Q2starQ2starQ3starAA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq7Q2starQ2starQ3starAA_ibin%d_ipt%d",ibin,ipt));
      hq7Q2starQ2starQ3starBB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq7Q2starQ2starQ3starBB_ibin%d_ipt%d",ibin,ipt));
      hq7Q2starQ2starQ3starAB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hq7Q2starQ2starQ3starAB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4AA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4AA_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4BB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4BB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4AB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs6AA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs6AA_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs6BB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs6BB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs6AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs6AB_ibin%d_ipt%d",ibin,ipt));
      hQ3Abs4AA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ3Abs4AA_ibin%d_ipt%d",ibin,ipt));
      hQ3Abs4BB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ3Abs4BB_ibin%d_ipt%d",ibin,ipt));
      hQ3Abs4AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ3Abs4AB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs2Q3Abs2AA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs2Q3Abs2AA_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs2Q3Abs2BB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs2Q3Abs2BB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs2Q3Abs2AB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs2Q3Abs2AB_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4Q3Abs2AA[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4Q3Abs2AA_ibin%d_ipt%d",ibin,ipt));
      hQ2Abs4Q3Abs2BB[ibin][ipt] = (TH1D*)inFile->Get(Form("flowCorr/hQ2Abs4Q3Abs2BB_ibin%d_ipt%d",ibin,ipt));
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
        value=hv2V2star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][1]->GetMean());
      else value=hv2V2star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][1]->GetMean());
      err=value*sqrt(hv2V2star[ibin][ipt]->GetMeanError()*hv2V2star[ibin][ipt]->GetMeanError()/hv2V2star[ibin][ipt]->GetMean()/hv2V2star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][1]->GetMeanError()*hVnAbs2[ibin][1]->GetMeanError()/hVnAbs2[ibin][1]->GetMean()/hVnAbs2[ibin][1]->GetMean());
      outv22<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv33;
  outv33.open("outv33_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv33<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][2]->GetMean()>0)
        value=hv3V3star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][2]->GetMean());
      else value=hv3V3star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][2]->GetMean());
      err=value*sqrt(hv3V3star[ibin][ipt]->GetMeanError()*hv3V3star[ibin][ipt]->GetMeanError()/hv3V3star[ibin][ipt]->GetMean()/hv3V3star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][2]->GetMeanError()*hVnAbs2[ibin][2]->GetMeanError()/hVnAbs2[ibin][2]->GetMean()/hVnAbs2[ibin][2]->GetMean());
      outv33<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv44;
  outv44.open("outv44_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv44<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][3]->GetMean()>0)
        value=hv4V4star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][3]->GetMean());
      else value=hv4V4star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][3]->GetMean());
      err=value*sqrt(hv4V4star[ibin][ipt]->GetMeanError()*hv4V4star[ibin][ipt]->GetMeanError()/hv4V4star[ibin][ipt]->GetMean()/hv4V4star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][3]->GetMeanError()*hVnAbs2[ibin][3]->GetMeanError()/hVnAbs2[ibin][3]->GetMean()/hVnAbs2[ibin][3]->GetMean());
      outv44<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv55;
  outv55.open("outv55_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv55<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][4]->GetMean()>0)
        value=hv5V5star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][4]->GetMean());
      else value=hv5V5star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][4]->GetMean());
      err=value*sqrt(hv5V5star[ibin][ipt]->GetMeanError()*hv5V5star[ibin][ipt]->GetMeanError()/hv5V5star[ibin][ipt]->GetMean()/hv5V5star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][4]->GetMeanError()*hVnAbs2[ibin][4]->GetMeanError()/hVnAbs2[ibin][4]->GetMean()/hVnAbs2[ibin][4]->GetMean());
      outv55<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv66;
  outv66.open("outv66_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv66<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][5]->GetMean()>0)
        value=hv6V6star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][5]->GetMean());
      else value=hv6V6star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][5]->GetMean());
      err=value*sqrt(hv6V6star[ibin][ipt]->GetMeanError()*hv6V6star[ibin][ipt]->GetMeanError()/hv6V6star[ibin][ipt]->GetMean()/hv6V6star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][5]->GetMeanError()*hVnAbs2[ibin][5]->GetMeanError()/hVnAbs2[ibin][5]->GetMean()/hVnAbs2[ibin][5]->GetMean());
      outv66<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv77;
  outv77.open("outv77_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv77<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][6]->GetMean()>0)
        value=hv7V7star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][6]->GetMean());
      else value=hv7V7star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][6]->GetMean());
      err=value*sqrt(hv7V7star[ibin][ipt]->GetMeanError()*hv7V7star[ibin][ipt]->GetMeanError()/hv7V7star[ibin][ipt]->GetMean()/hv7V7star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][6]->GetMeanError()*hVnAbs2[ibin][6]->GetMeanError()/hVnAbs2[ibin][6]->GetMean()/hVnAbs2[ibin][6]->GetMean());
      outv77<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv88;
  outv88.open("outv88_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv88<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs2[ibin][7]->GetMean()>0)
        value=hv8V8star[ibin][ipt]->GetMean()/sqrt(hVnAbs2[ibin][7]->GetMean());
      else value=hv8V8star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs2[ibin][7]->GetMean());
      err=value*sqrt(hv8V8star[ibin][ipt]->GetMeanError()*hv8V8star[ibin][ipt]->GetMeanError()/hv8V8star[ibin][ipt]->GetMean()/hv8V8star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs2[ibin][7]->GetMeanError()*hVnAbs2[ibin][7]->GetMeanError()/hVnAbs2[ibin][7]->GetMean()/hVnAbs2[ibin][7]->GetMean());
      outv88<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outv42;
  outv42.open("outv42_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv42<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs4[ibin][1]->GetMean()>0)
        value=hv4V2starV2star[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][1]->GetMean());
      else value=hv4V2starV2star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs4[ibin][1]->GetMean());
      err=value*sqrt(hv4V2starV2star[ibin][ipt]->GetMeanError()*hv4V2starV2star[ibin][ipt]->GetMeanError()/hv4V2starV2star[ibin][ipt]->GetMean()/hv4V2starV2star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][1]->GetMeanError()*hVnAbs4[ibin][1]->GetMeanError()/hVnAbs4[ibin][1]->GetMean()/hVnAbs4[ibin][1]->GetMean());
      outv42<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }


  ofstream outv62;
  outv62.open("outv62_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv62<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs6[ibin][1]->GetMean()>0)
        value=hv6V2starV2starV2star[ibin][ipt]->GetMean()/sqrt(hVnAbs6[ibin][1]->GetMean());
      else value=hv6V2starV2starV2star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs6[ibin][1]->GetMean());
      err=value*sqrt(hv6V2starV2starV2star[ibin][ipt]->GetMeanError()*hv6V2starV2starV2star[ibin][ipt]->GetMeanError()/hv6V2starV2starV2star[ibin][ipt]->GetMean()/hv6V2starV2starV2star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs6[ibin][1]->GetMeanError()*hVnAbs6[ibin][1]->GetMeanError()/hVnAbs6[ibin][1]->GetMean()/hVnAbs6[ibin][1]->GetMean());
      outv62<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
  ofstream outv63;
  outv63.open("outv63_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv63<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hVnAbs4[ibin][2]->GetMean()>0)
        value=hv6V3starV3star[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][2]->GetMean());
      else value=hv6V3starV3star[ibin][ipt]->GetMean()/sqrt((-1)*hVnAbs4[ibin][2]->GetMean());
      err=value*sqrt(hv6V3starV3star[ibin][ipt]->GetMeanError()*hv6V3starV3star[ibin][ipt]->GetMeanError()/hv6V3starV3star[ibin][ipt]->GetMean()/hv6V3starV3star[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][2]->GetMeanError()*hVnAbs4[ibin][2]->GetMeanError()/hVnAbs4[ibin][2]->GetMean()/hVnAbs4[ibin][2]->GetMean());
      outv63<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outv523;
  outv523.open("outv523_corrFlow.txt");  
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv523<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hV2Abs2V3Abs2[ibin]->GetMean()>0)
        value=hv5V2starV3star[ibin][ipt]->GetMean()/sqrt(hV2Abs2V3Abs2[ibin]->GetMean());
      else value=hv5V2starV3star[ibin][ipt]->GetMean()/sqrt((-1)*hV2Abs2V3Abs2[ibin]->GetMean());
      err=value*sqrt(hv5V2starV3star[ibin][ipt]->GetMeanError()*hv5V2starV3star[ibin][ipt]->GetMeanError()/hv5V2starV3star[ibin][ipt]->GetMean()/hv5V2starV3star[ibin][ipt]->GetMean() + 1.0/4*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
      outv523<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outv723;
  outv723.open("outv723_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outv723<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      if(hV2Abs4V3Abs2[ibin]->GetMean()>0)
        value=hv7V2starV2starV3star[ibin][ipt]->GetMean()/sqrt(hV2Abs4V3Abs2[ibin]->GetMean());
      else value=hv7V2starV2starV3star[ibin][ipt]->GetMean()/sqrt((-1)*hV2Abs4V3Abs2[ibin]->GetMean());
      err=value*sqrt(hv7V2starV2starV3star[ibin][ipt]->GetMeanError()*hv7V2starV2starV3star[ibin][ipt]->GetMeanError()/hv7V2starV2starV3star[ibin][ipt]->GetMean()/hv7V2starV2starV3star[ibin][ipt]->GetMean() + 1.0/4*hV2Abs4V3Abs2[ibin]->GetMeanError()*hV2Abs4V3Abs2[ibin]->GetMeanError()/hV2Abs4V3Abs2[ibin]->GetMean()/hV2Abs4V3Abs2[ibin]->GetMean());
      outv723<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

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


// chi
  ofstream outchi422;
  outchi422.open("outchi422_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi422<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hv4V2starV2star[ibin][ipt]->GetMean()/hV2Abs4trk12[ibin]->GetMean();
        err=value*sqrt(hv4V2starV2star[ibin][ipt]->GetMeanError()*hv4V2starV2star[ibin][ipt]->GetMeanError()/hv4V2starV2star[ibin][ipt]->GetMean()/hv4V2starV2star[ibin][ipt]->GetMean()  + 1.0/1*hV2Abs4trk12[ibin]->GetMeanError()*hV2Abs4trk12[ibin]->GetMeanError()/hV2Abs4trk12[ibin]->GetMean()/hV2Abs4trk12[ibin]->GetMean());
      outchi422<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }
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
  ofstream outchi422Denz;
  outchi422Denz.open("outchi422Denz_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi422Denz<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ2Abs4AA[ibin][ipt]->GetMean()/sqrt(hVnAbs4[ibin][1]->GetMean());
      err=value*sqrt(hQ2Abs4AA[ibin][ipt]->GetMeanError()*hQ2Abs4AA[ibin][ipt]->GetMeanError()/hQ2Abs4AA[ibin][ipt]->GetMean()/hQ2Abs4AA[ibin][ipt]->GetMean() + 1.0/4*hVnAbs4[ibin][1]->GetMeanError()*hVnAbs4[ibin][1]->GetMeanError()/hVnAbs4[ibin][1]->GetMean()/hVnAbs4[ibin][1]->GetMean());
      //value=hQ2Abs4AA[ibin][ipt]->GetMean();
      //err=hQ2Abs4AA[ibin][ipt]->GetMeanError();
      outchi422Denz<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outchi523;
  outchi523.open("outchi523_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi523<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hv5V2starV3star[ibin][ipt]->GetMean()/hV2Abs2V3Abs2trk12[ibin]->GetMean();
        err=value*sqrt(hv5V2starV3star[ibin][ipt]->GetMeanError()*hv5V2starV3star[ibin][ipt]->GetMeanError()/hv5V2starV3star[ibin][ipt]->GetMean()/hv5V2starV3star[ibin][ipt]->GetMean()  + 1.0/1*hV2Abs2V3Abs2trk12[ibin]->GetMeanError()*hV2Abs2V3Abs2trk12[ibin]->GetMeanError()/hV2Abs2V3Abs2trk12[ibin]->GetMean()/hV2Abs2V3Abs2trk12[ibin]->GetMean());
      outchi523<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
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
  ofstream outchi523Denz;
  outchi523Denz.open("outchi523Denz_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi523Denz<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
      value=hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMean()/sqrt(hV2Abs2V3Abs2[ibin]->GetMean());
      err=value*sqrt(hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMeanError()*hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMeanError()/hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMean()/hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMean() + 1.0/4*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
      //value=hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMean();
      //err=hQ2Abs2Q3Abs2AA[ibin][ipt]->GetMeanError();
      outchi523Denz<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
    }
  }

  ofstream outchi6222;
  outchi6222.open("outchi6222_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi6222<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hv6V2starV2starV2star[ibin][ipt]->GetMean()/hV2Abs6trk12[ibin]->GetMean();
        err=value*sqrt(hv6V2starV2starV2star[ibin][ipt]->GetMeanError()*hv6V2starV2starV2star[ibin][ipt]->GetMeanError()/hv6V2starV2starV2star[ibin][ipt]->GetMean()/hv6V2starV2starV2star[ibin][ipt]->GetMean()  + 1.0/1*hV2Abs6trk12[ibin]->GetMeanError()*hV2Abs6trk12[ibin]->GetMeanError()/hV2Abs6trk12[ibin]->GetMean()/hV2Abs6trk12[ibin]->GetMean());
      outchi6222<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
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
  ofstream outchi633;
  outchi633.open("outchi633_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi633<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hv6V3starV3star[ibin][ipt]->GetMean()/hV3Abs4trk12[ibin]->GetMean();
        err=value*sqrt(hv6V3starV3star[ibin][ipt]->GetMeanError()*hv6V3starV3star[ibin][ipt]->GetMeanError()/hv6V3starV3star[ibin][ipt]->GetMean()/hv6V3starV3star[ibin][ipt]->GetMean()  + 1.0/1*hV3Abs4trk12[ibin]->GetMeanError()*hV3Abs4trk12[ibin]->GetMeanError()/hV3Abs4trk12[ibin]->GetMean()/hV3Abs4trk12[ibin]->GetMean());
      outchi633<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
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
  ofstream outchi7223;
  outchi7223.open("outchi7223_corrFlow.txt");
  for(int ibin=0; ibin<nCentBin; ibin++){
    outchi7223<<cBin[ibin]<<"   "<<cBin[ibin+1]<<endl;
    for(int ipt=0; ipt<nPtBin; ipt++){
        value=hv7V2starV2starV3star[ibin][ipt]->GetMean()/hV2Abs4V3Abs2trk12[ibin]->GetMean();
        err=value*sqrt(hv7V2starV2starV3star[ibin][ipt]->GetMeanError()*hv7V2starV2starV3star[ibin][ipt]->GetMeanError()/hv7V2starV2starV3star[ibin][ipt]->GetMean()/hv7V2starV2starV3star[ibin][ipt]->GetMean()  + 1.0/1*hV2Abs4V3Abs2trk12[ibin]->GetMeanError()*hV2Abs4V3Abs2trk12[ibin]->GetMeanError()/hV2Abs4V3Abs2trk12[ibin]->GetMean()/hV2Abs4V3Abs2trk12[ibin]->GetMean());
      outchi7223<<ptBin[ipt]<<"  "<<ptBin[ipt+1]<<"   "<<hMeanPt[ibin][ipt]->GetMean()<<"  "<<hMeanPt[ibin][ipt]->GetEntries()*1.0<<"  "<<value<<"  "<<err<<endl;
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


  //for(int ibin=0; ibin<nCentBin; ibin++)
    //cout<<(cBin[ibin]+cBin[ibin+1])*1.0/2.0<<"  "<<hVnAbs4[ibin][1]<<endl;
    //cout<<(cBin[ibin]+cBin[ibin+1])*1.0/2.0<<"  "<<hV2Abs2V3Abs2[ibin]->GetMean()<<endl;
    //cout<<(cBin[ibin]+cBin[ibin+1])*1.0/2.0<<"  "<<hv5V2starV3star[ibin][8]->GetMean()<<"  "<<hV2Abs2V3Abs2[ibin]->GetMean()<<endl;
    //cout<<(cBin[ibin]+cBin[ibin+1])*1.0/2.0<<"  "<<hv4V2starV2star[ibin][8]->GetMean()<<"  "<<hVnAbs2[ibin][1]->GetMean()<<endl;




}



