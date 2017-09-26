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

void getCMeanQxy(){

TH1D::SetDefaultSumw2();

  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  //double cBin[nCentBin+1]={0,5,50,60,70,80,82,84,86,88,90,92,94,96,100};
  double ptBin[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20.0};

  TH1D* hQhfPlusX[nCentBin][nHarmonics];
  TH1D* hQhfPlusY[nCentBin][nHarmonics];
  TH1D* hQhfMinusX[nCentBin][nHarmonics];
  TH1D* hQhfMinusY[nCentBin][nHarmonics];

  TH1D* hQtrkPtX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtY[nCentBin][nHarmonics][nPtBin];

  TFile* inFile = new TFile("../flowCorr_data_5020_v03Ana_5TevCentPar_sep25C_merged.root");
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQhfPlusX[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hQhfPlusX_ibin%d_iH%d",ibin,iH));
      hQhfPlusY[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hQhfPlusY_ibin%d_iH%d",ibin,iH));
      hQhfMinusX[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hQhfMinusX_ibin%d_iH%d",ibin,iH));
      hQhfMinusY[ibin][iH] = (TH1D*)inFile->Get(Form("flowCorr/hQhfMinusY_ibin%d_iH%d",ibin,iH));
      for(int iPt=0; iPt<nPtBin; iPt++){
        hQtrkPtX[ibin][iH][iPt] = (TH1D*)inFile->Get(Form("flowCorr/hQtrkPtX_ibin%d_iH%d_iPt%d",ibin,iH,iPt));
        hQtrkPtY[ibin][iH][iPt] = (TH1D*)inFile->Get(Form("flowCorr/hQtrkPtY_ibin%d_iH%d_iPt%d",ibin,iH,iPt));
      }
    }
  }

  ofstream outvhf;
  outvhf.open("outvmeanHF_v08_corrFlowC.txt");

  outvhf<<"double meanQxPlusC[nCentBin][nHarmonics] = {";
  for(int ibin=0; ibin<nCentBin-1; ibin++){
    outvhf<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outvhf<<hQhfPlusX[ibin][iH]->GetMean()<<", ";
    }
    outvhf<<hQhfPlusX[ibin][nHarmonics-1]->GetMean()<<"}, "<<endl;
  }
  outvhf<<"{";
  for(int iH=0; iH<nHarmonics-1; iH++){
    outvhf<<hQhfPlusX[nCentBin-1][iH]->GetMean()<<", ";
  }
  outvhf<<hQhfPlusX[nCentBin-1][nHarmonics-1]->GetMean()<<"}}; "<<endl;
/////////////
  outvhf<<"double meanQyPlusC[nCentBin][nHarmonics] = {";
  for(int ibin=0; ibin<nCentBin-1; ibin++){
    outvhf<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outvhf<<hQhfPlusY[ibin][iH]->GetMean()<<", ";
    }
    outvhf<<hQhfPlusY[ibin][nHarmonics-1]->GetMean()<<"}, "<<endl;
  }
  outvhf<<"{";
  for(int iH=0; iH<nHarmonics-1; iH++){
    outvhf<<hQhfPlusY[nCentBin-1][iH]->GetMean()<<", ";
  }
  outvhf<<hQhfPlusY[nCentBin-1][nHarmonics-1]->GetMean()<<"}}; "<<endl;
///////////
  outvhf<<"double meanQxMinusC[nCentBin][nHarmonics] = {";
  for(int ibin=0; ibin<nCentBin-1; ibin++){
    outvhf<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outvhf<<hQhfMinusX[ibin][iH]->GetMean()<<", ";
    }
    outvhf<<hQhfMinusX[ibin][nHarmonics-1]->GetMean()<<"}, "<<endl;
  }
  outvhf<<"{";
  for(int iH=0; iH<nHarmonics-1; iH++){
    outvhf<<hQhfMinusX[nCentBin-1][iH]->GetMean()<<", ";
  }
  outvhf<<hQhfMinusX[nCentBin-1][nHarmonics-1]->GetMean()<<"}}; "<<endl;
////////////
  outvhf<<"double meanQyMinusC[nCentBin][nHarmonics] = {";
  for(int ibin=0; ibin<nCentBin-1; ibin++){
    outvhf<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outvhf<<hQhfMinusY[ibin][iH]->GetMean()<<", ";
    }
    outvhf<<hQhfMinusY[ibin][nHarmonics-1]->GetMean()<<"}, "<<endl;
  }
  outvhf<<"{";
  for(int iH=0; iH<nHarmonics-1; iH++){
    outvhf<<hQhfMinusY[nCentBin-1][iH]->GetMean()<<", ";
  }
  outvhf<<hQhfMinusY[nCentBin-1][nHarmonics-1]->GetMean()<<"}}; "<<endl;
/////////


  ofstream outvtrk;
  outvtrk.open("outvmeanTrk_v08_corrFlowC.txt");

/////////////
///////////
////////////
/////////

  outvtrk<<"double meanQxTrkPtC[nCentBin][nHarmonics][nPtBin] = {";
  for(int ibin=0; ibin<nCentBin-1; ibin++){
    outvtrk<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outvtrk<<"{";
      for(int ipt=0; ipt<nPtBin-1; ipt++){
        outvtrk<<hQtrkPtX[ibin][iH][ipt]->GetMean()<<", "; 
      }
      outvtrk<<hQtrkPtX[ibin][iH][nPtBin-1]->GetMean()<<"}, "<<endl;
    }
    outvtrk<<"{";
    for(int iH=0; iH<nPtBin-1; iH++){
      outvtrk<<hQtrkPtX[ibin][nHarmonics-1][ipt]->GetMean()<<", ";
    }
    outvtrk<<hQtrkPtX[ibin][nHarmonics-1][nPtBin-1]->GetMean()<<"}}, "<<endl;
  }
  outvtrk<<"{";
  for(int iH=0; iH<nHarmonics-1; iH++){
    outvtrk<<"{";
    for(int ipt=0; ipt<nPtBin-1; ipt++){
      outvtrk<<hQtrkPtX[nCentBin-1][iH][ipt]->GetMean()<<", ";
    }
    outvtrk<<hQtrkPtX[nCentBin-1][iH][nPtBin-1]->GetMean()<<"}, "<<endl;
  }
  outvtrk<<"{";
  for(int iH=0; iH<nPtBin-1; iH++){
    outvtrk<<hQtrkPtX[nCentBin-1][nHarmonics-1][ipt]->GetMean()<<", ";
  }
  outvtrk<<hQtrkPtX[nCentBin-1][nHarmonics-1][nPtBin-1]->GetMean()<<"}}}; "<<endl;

/////////

  outvtrk<<"double meanQyTrkPtC[nCentBin][nHarmonics][nPtBin] = {";
  for(int ibin=0; ibin<nCentBin-1; ibin++){
    outvtrk<<"{";
    for(int iH=0; iH<nHarmonics-1; iH++){
      outvtrk<<"{";
      for(int ipt=0; ipt<nPtBin-1; ipt++){
        outvtrk<<hQtrkPtY[ibin][iH][ipt]->GetMean()<<", ";
      }
      outvtrk<<hQtrkPtY[ibin][iH][nPtBin-1]->GetMean()<<"}, "<<endl;
    }
    outvtrk<<"{";
    for(int iH=0; iH<nPtBin-1; iH++){
      outvtrk<<hQtrkPtY[ibin][nHarmonics-1][ipt]->GetMean()<<", ";
    }
    outvtrk<<hQtrkPtY[ibin][nHarmonics-1][nPtBin-1]->GetMean()<<"}}, "<<endl;
  }
  outvtrk<<"{";
  for(int iH=0; iH<nHarmonics-1; iH++){
    outvtrk<<"{";
    for(int ipt=0; ipt<nPtBin-1; ipt++){
      outvtrk<<hQtrkPtY[nCentBin-1][iH][ipt]->GetMean()<<", ";
    }
    outvtrk<<hQtrkPtY[nCentBin-1][iH][nPtBin-1]->GetMean()<<"}, "<<endl;
  }
  outvtrk<<"{";
  for(int iH=0; iH<nPtBin-1; iH++){
    outvtrk<<hQtrkPtY[nCentBin-1][nHarmonics-1][ipt]->GetMean()<<", ";
  }
  outvtrk<<hQtrkPtY[nCentBin-1][nHarmonics-1][nPtBin-1]->GetMean()<<"}}}; "<<endl;


}



