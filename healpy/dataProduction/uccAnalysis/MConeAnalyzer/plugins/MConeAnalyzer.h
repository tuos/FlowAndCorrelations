#include "TComplex.h"
#include <vector>
#include <TVector3.h>
#include "TTree.h"

#define nCentBin 14
#define nHarmonics 8
#define nPtBin 20 

using namespace std;
using namespace reco;
using namespace edm;

  bool useReDenominator = true;
  bool useRe = true;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  //double cBin[nCentBin+1]={0,20,60,70,80,81,82,84,86,88,90,92,94,96,100};
  double ptBin[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20.0};

  vector<TVector3> *pVect_trkEtaPlus;
  vector<TVector3> *pVect_trkEtaMinus;
  vector<TVector3> *pVect_hfEtaPlus;
  vector<TVector3> *pVect_hfEtaMinus;

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

  const int maxN = 50000;
  Int_t d_centralityBin;
  Int_t d_nTracks; 
  Float_t d_pt[maxN];    
  Float_t d_phi[maxN];     
  Float_t d_eta[maxN];
  Float_t d_hfEnergy;
  Float_t d_vz;
  Float_t d_vx;
  Float_t d_vy;

