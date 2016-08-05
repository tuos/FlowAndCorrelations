#include "TComplex.h"
#include <vector>
#include <TVector3.h>

#define nCentBin 13
#define nHarmonics 8
#define nPtBin 14 

using namespace std;
using namespace reco;
using namespace edm;

  bool useRe = true;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,100};
  double ptBin[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.2, 1.6, 2.0, 2.5, 3.0, 4.0, 6.0, 8.0, 12.0};
  TComplex QhfPlus[nCentBin][nHarmonics];
  TComplex QhfMinus[nCentBin][nHarmonics];
  //TComplex QtrkPlus[nCentBin][nHarmonics];
  //TComplex QtrkMinus[nCentBin][nHarmonics];
  double VnAbs2[nCentBin][nHarmonics]={{0.0},{0.0}};
  double VnAbs4[nCentBin][nHarmonics]={{0.0},{0.0}};
  double VnAbs6[nCentBin][nHarmonics]={{0.0},{0.0}};
  double V2Abs2V3Abs2[nCentBin]={0.0};
  double V2Abs4V3Abs2[nCentBin]={0.0};
  double V4V2starV2star[nCentBin]={0.0};
  double V6V2starV2starV2star[nCentBin]={0.0};
  double V6V3starV3star[nCentBin]={0.0};
  double V5V2starV3star[nCentBin]={0.0};
  double V7V2starV2starV3star[nCentBin]={0.0};
  double v2Psi2[nCentBin]={0.0};
  double v3Psi3[nCentBin]={0.0};
  double v4Psi2[nCentBin]={0.0};
  double v4Psi4[nCentBin]={0.0};
  double v6Psi2[nCentBin]={0.0};
  double v6Psi3[nCentBin]={0.0};
  double v6Psi6[nCentBin]={0.0};
  double v5Psi2Psi3[nCentBin]={0.0};
  double v7Psi2Psi3[nCentBin]={0.0};
  int nEvent[nCentBin]={0};

  vector<TVector3> *pVect_trkEtaPlus;
  vector<TVector3> *pVect_trkEtaMinus;  
  vector<TVector3> *pVect_hfEtaPlus;
  vector<TVector3> *pVect_hfEtaMinus;  

  TH1D* hMultTrkEtaPlus;
  TH1D* hMultTrkEtaMinus;
  TH1D* hMultHFEtaPlus;
  TH1D* hMultHFEtaMinus;
  TH1D* hQhfPlusX[nCentBin][nHarmonics];
  TH1D* hQhfPlusY[nCentBin][nHarmonics];
  TH1D* hQhfPlusQ[nCentBin][nHarmonics];
  TH1D* hQhfMinusX[nCentBin][nHarmonics];
  TH1D* hQhfMinusY[nCentBin][nHarmonics];
  TH1D* hQhfMinusQ[nCentBin][nHarmonics];
  TH1D* hVnAbs2[nCentBin][nHarmonics];
  TH1D* hVnAbs4[nCentBin][nHarmonics];
  TH1D* hVnAbs6[nCentBin][nHarmonics];
  TH1D* hV2Abs2V3Abs2[nCentBin];
  TH1D* hV2Abs4V3Abs2[nCentBin];
  TH1D* hV4V2starV2star[nCentBin];
  TH1D* hV6V2starV2starV2star[nCentBin];
  TH1D* hV6V3starV3star[nCentBin];
  TH1D* hV5V2starV3star[nCentBin];
  TH1D* hV7V2starV2starV3star[nCentBin];
  TH1D* hv4V2starV2star[nCentBin][nPtBin];
  TH1D* hv6V2starV2starV2star[nCentBin][nPtBin];
  TH1D* hv6V3starV3star[nCentBin][nPtBin];
  TH1D* hv5V2starV3star[nCentBin][nPtBin];
  TH1D* hv7V2starV2starV3star[nCentBin][nPtBin];



   TH1D* hCent;
   TH1D* hHF;
   TH1D* hAngle;
   TH1D* hAngleFlat;
   TH1D* hvz;
   TH1D* hvx;
   TH1D* hvy;
   TH1D* hNtrks;
   TH1D* hpt;
   TH1D* heta;
   TH1D* hphi;
   TH1D* hHFcal;


