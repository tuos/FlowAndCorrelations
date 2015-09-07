#include "TComplex.h"
#include "TString.h"
#include <vector>
#include <TVector3.h>
#include "TDirectory.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <fstream>
#include <iostream>

using namespace std;

void flowCorr(){

  const int nCentBin = 10;
  double bbin[nCentBin+1]={0, 5.1065, 7.2225, 8.8585, 10.2225, 11.4295, 12.5195, 13.5275, 14.4755, 15.4765, 30};
  const int nHarmonics = 8;
  TComplex QhfPlus[nCentBin][nHarmonics];
  TComplex QhfMinus[nCentBin][nHarmonics];
  double VnAbs2[nCentBin][nHarmonics]={0.0};
  double VnAbs4[nCentBin][nHarmonics]={0.0};
  double VnAbs6[nCentBin][nHarmonics]={0.0};
  double V2Abs2V3Abs2[nCentBin]={0.0};
  TComplex V4V2starV2star[nCentBin];
  TComplex V6V2starV2starV2star[nCentBin];
  TComplex V6V3starV3star[nCentBin];
  TComplex V5V2starV3star[nCentBin];
  for(int ibin=0; ibin<nCentBin; ibin++){
    V4V2starV2star[ibin]=0.0;
    V6V2starV2starV2star[ibin]=0.0;
    V6V3starV3star[ibin]=0.0;
    V5V2starV3star[ibin]=0.0;
  }
  double v2Psi2[nCentBin]={0.0};
  double v3Psi3[nCentBin]={0.0};
  double v4Psi2[nCentBin]={0.0};
  double v4Psi4[nCentBin]={0.0};
  double v6Psi2[nCentBin]={0.0};
  double v6Psi3[nCentBin]={0.0};
  double v6Psi6[nCentBin]={0.0};
  double v5Psi2Psi3[nCentBin]={0.0};
  int nEvent[nCentBin]={0};

  //gSystem->Load("libPhysics");
  vector<TVector3> *pVect_hfPlus;
  vector<TVector3> *pVect_hfMinus;  

  TH1D::SetDefaultSumw2();
  TH1D* hMultPlus = new TH1D("multplus","N",500,0,5000);
  TH1D* hMultMinus = new TH1D("multminus","N",500,0,5000);

  double etaMin=1.0;
  double etaMax=5.0;
  double ptMin=0.005;
  double ptMax=30.0;
 
  Int_t mult0=0;
  Float_t b0;
  Float_t phi0[20000];
  Float_t pt0[20000];
  Float_t eta0[20000];

     char *file1 = "/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v3/July09/run0pbPbv3x10more/energy2760GeVA/mergedOuttreefile_ampt.root";
     TFile *f1 = new TFile(file1);
     TTree *t1 = (TTree*)f1->Get("ana/hi");
     t1->SetBranchAddress("mult", &mult0);
     t1->SetBranchAddress("pt", &pt0);
     t1->SetBranchAddress("eta", &eta0);
     t1->SetBranchAddress("phi", &phi0);
     t1->SetBranchAddress("b", &b0);
     int neve=t1->GetEntries();
     cout<<"Nevts = "<<neve<<endl;
     neve = 50000;
     for(int ne=0; ne<neve; ne++){
       if(ne%1000==0)  cout<<"Have run "<<ne<<" events ,"<<" First pass"<<endl;
       t1->GetEntry(ne);

       for(int j=0;j<nCentBin;j++){
         for(int iH=0; iH<nHarmonics; iH++){
           QhfPlus[j][iH]=0;   
           QhfMinus[j][iH]=0;   
         }
       }

       int ibin=-1;
       for(int j=0;j<nCentBin;j++)
       if(b0>=bbin[j]&&b0<bbin[j+1])
         ibin=j;
       if(ibin<0 || ibin==nCentBin) continue;
       nEvent[ibin]+=1;

       pVect_hfPlus = new vector<TVector3>;
       pVect_hfMinus = new vector<TVector3>;
       for(int nh=0;nh<mult0;nh++){
         TVector3 pvector;
         pvector.SetPtEtaPhi(pt0[nh],eta0[nh],phi0[nh]);
         if(eta0[nh]<=etaMax && eta0[nh]>=etaMin && pt0[nh]<=ptMax && pt0[nh]>=ptMin) pVect_hfPlus->push_back(pvector);
         if(eta0[nh]>=-1*etaMax && eta0[nh]<=-1*etaMin && pt0[nh]<=ptMax && pt0[nh]>=ptMin) pVect_hfMinus->push_back(pvector);
       }

       int nMult_hfPlus = (int)pVect_hfPlus->size();
       int nMult_hfMinus = (int)pVect_hfMinus->size();
       hMultPlus->Fill(nMult_hfPlus);  
       hMultMinus->Fill(nMult_hfMinus);  

       for(int iH=0; iH<nHarmonics; iH++){
         double sumwPlus=0;
         double sumwMinus=0;
         for(int iplus=0;iplus<nMult_hfPlus;iplus++){
           TVector3 pvector_hfPlus = (*pVect_hfPlus)[iplus];
           double pt_hfPlus = pvector_hfPlus.Pt();
           double phi_hfPlus = pvector_hfPlus.Phi();
           //sumwPlus+=pt_hfPlus; 
           sumwPlus+=1; 
           QhfPlus[ibin][iH]+=TComplex::Exp(TComplex(0,(iH+1)*phi_hfPlus));
         }
         if(sumwPlus>0) QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus;
         else QhfPlus[ibin][iH]=0;

         for(int iminus=0;iminus<nMult_hfMinus;iminus++){
           TVector3 pvector_hfMinus = (*pVect_hfMinus)[iminus];
           double pt_hfMinus = pvector_hfMinus.Pt();
           double phi_hfMinus = pvector_hfMinus.Phi();
           //sumwMinus+=pt_hfMinus; 
           sumwMinus+=1;
           QhfMinus[ibin][iH]+=TComplex::Exp(TComplex(0,(iH+1)*phi_hfMinus));
         }
         if(sumwMinus>0) QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus;
         else QhfMinus[ibin][iH]=0;
       }

       for(int iH=0; iH<nHarmonics; iH++){
         TComplex temp;
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         double vnabs2evt=temp.Re();
         //double vnabs2evt=(QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re();
         VnAbs2[ibin][iH]+=vnabs2evt;
         VnAbs4[ibin][iH]+=vnabs2evt*vnabs2evt;
         VnAbs6[ibin][iH]+=vnabs2evt*vnabs2evt*vnabs2evt;
       }
       temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       V2Abs2V3Abs2[ibin]+=temp.Re();
       //V2Abs2V3Abs2[ibin]+=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       V4V2starV2star[ibin]+=QhfPlus[ibin][3]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       V6V2starV2starV2star[ibin]+=QhfPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);       
       V6V3starV3star[ibin]+=QhfPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
       V5V2starV3star[ibin]+=QhfPlus[ibin][4]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);

     } //evt loop

     for(int ibin=0; ibin<nCentBin; ibin++){
       v2Psi2[ibin]=(VnAbs2[ibin][1]/nEvent[ibin])/sqrt(VnAbs2[ibin][1]/nEvent[ibin]);
       v3Psi3[ibin]=(VnAbs2[ibin][2]/nEvent[ibin])/sqrt(VnAbs2[ibin][2]/nEvent[ibin]);
       v4Psi2[ibin]=(V4V2starV2star[ibin].Re()/nEvent[ibin])/sqrt(VnAbs4[ibin][1]/nEvent[ibin]);
       v4Psi4[ibin]=(VnAbs2[ibin][3]/nEvent[ibin])/sqrt(VnAbs2[ibin][3]/nEvent[ibin]);;
       v6Psi2[ibin]=(V6V2starV2starV2star[ibin].Re()/nEvent[ibin])/sqrt(VnAbs6[ibin][1]/nEvent[ibin]);
       v6Psi3[ibin]=(V6V3starV3star[ibin].Re()/nEvent[ibin])/sqrt(VnAbs4[ibin][2]/nEvent[ibin]);
       v6Psi6[ibin]=(VnAbs2[ibin][5]/nEvent[ibin])/sqrt(VnAbs2[ibin][5]/nEvent[ibin]);;
       v5Psi2Psi3[ibin]=(V5V2starV3star[ibin].Re()/nEvent[ibin])/sqrt(V2Abs2V3Abs2[ibin]/nEvent[ibin]);
     }

     cout<<hMultPlus->GetMean()<<"   "<<hMultMinus->GetMean()<<endl;  
     for(int ibin=0; ibin<nCentBin; ibin++)
       cout<<i<<"   "<<2Psi2[ibin]<<"   "<<v3Psi3[ibin]<<"   "<<v4Psi4[ibin]<<"   "<<v6Psi6[ibin]<<endl;
     for(int ibin=0; ibin<nCentBin; ibin++){
       cout<<(bbin[ibin]+bbin[ibin+1])/2<<"   "<<v2Psi2[ibin]<<"   "<<v3Psi3[ibin]<<"  "<<v4Psi2[ibin]/v4Psi4[ibin]<<"   "<<v6Psi2[ibin]/v6Psi6[ibin]<<"   "<<v5Psi2Psi3[ibin]<<endl;  
     }

     //hMultPlus->Draw();
     //hMultMinus->SetLineColor(2);
     //hMultMinus->Draw("same");

}

