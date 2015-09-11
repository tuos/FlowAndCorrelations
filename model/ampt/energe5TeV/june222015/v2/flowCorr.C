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

  bool useRe = true;
  const int nCentBin = 10;
  //double bbin[nCentBin+1]={0, 5.1065, 7.2225, 8.8585, 10.2225, 11.4295, 12.5195, 13.5275, 14.4755, 15.4765, 30};
  double cbin[nCentBin+1]={0,5,10,15,20,25,30,35,40,45,50};
  const int nHarmonics = 8;
  TComplex QhfPlus[nCentBin][nHarmonics];
  TComplex QhfMinus[nCentBin][nHarmonics];
  double VnAbs2[nCentBin][nHarmonics]={0.0};
  double VnAbs4[nCentBin][nHarmonics]={0.0};
  double VnAbs6[nCentBin][nHarmonics]={0.0};
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

  //gSystem->Load("libPhysics");
  vector<TVector3> *pVect_hfPlus;
  vector<TVector3> *pVect_hfMinus;  

  TFile *outfile = new TFile("dist_results.root","recreate");
  TDirectory *dirQ = outfile->mkdir("Qvector");
  TDirectory *dirVn = outfile->mkdir("VnAbs");
  TDirectory *dirVnxy = outfile->mkdir("Vnxy");
  TH1D::SetDefaultSumw2();
  TH1D* hMultPlus = new TH1D("multplus","N",500,0,5000);
  TH1D* hMultMinus = new TH1D("multminus","N",500,0,5000);
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
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQhfPlusX[ibin][iH] = new TH1D(Form("hQhfPlusX_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfPlusY[ibin][iH] = new TH1D(Form("hQhfPlusY_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfPlusQ[ibin][iH] = new TH1D(Form("hQhfPlusQ_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfMinusX[ibin][iH] = new TH1D(Form("hQhfMinusX_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfMinusY[ibin][iH] = new TH1D(Form("hQhfMinusY_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hQhfMinusQ[ibin][iH] = new TH1D(Form("hQhfMinusQ_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs2[ibin][iH] = new TH1D(Form("hVnAbs2_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs4[ibin][iH] = new TH1D(Form("hVnAbs4_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
      hVnAbs6[ibin][iH] = new TH1D(Form("hVnAbs6_ibin%d_iH%d",ibin,iH),"",200,-1000,1000);
    }
    hV2Abs2V3Abs2[ibin] = new TH1D(Form("hV2Abs2V3Abs2_ibin%d",ibin),"",200,-1000,1000);
    hV2Abs4V3Abs2[ibin] = new TH1D(Form("hV2Abs4V3Abs2_ibin%d",ibin),"",200,-1000,1000);
    hV4V2starV2star[ibin] = new TH1D(Form("hV4V2starV2star_ibin%d",ibin),"",200,-1000,1000);
    hV6V2starV2starV2star[ibin] = new TH1D(Form("hV6V2starV2starV2star_ibin%d",ibin),"",200,-1000,1000);
    hV6V3starV3star[ibin] = new TH1D(Form("hV6V3starV3star_ibin%d",ibin),"",200,-1000,1000);
    hV5V2starV3star[ibin] = new TH1D(Form("hV5V2starV3star_ibin%d",ibin),"",200,-1000,1000);
    hV7V2starV2starV3star[ibin] = new TH1D(Form("hV7V2starV2starV3star_ibin%d",ibin),"",200,-1000,1000);
  }

  double etaMin=0.6;
  double etaMax=2.4;
  double ptMin=0.3;
  double ptMax=3.0;
 
  Int_t mult0=0;
  Int_t cent0=0;
  Float_t b0;
  Float_t phi0[20000];
  Float_t pt0[20000];
  Float_t eta0[20000];

     //char *file1 = "/store/user/tuos/MC_AMPT/PbPb5TeV/StringMelting/v3/July09/run0pbPbv3x10more/energy2760GeVB/mergedOuttreefile_ampt.root";
     char *file1 = "/store/user/tuos/tmp/STEG_run182798_hiGeneralAndPixelTracks_v0.root";
     TFile *f1 = new TFile(file1);
     TTree *t1 = (TTree*)f1->Get("ana/tree");
     //t1->SetBranchAddress("mult", &mult0);
     //t1->SetBranchAddress("pt", &pt0);
     //t1->SetBranchAddress("eta", &eta0);
     //t1->SetBranchAddress("phi", &phi0);
     //t1->SetBranchAddress("b", &b0);
     t1->SetBranchAddress("npg", &mult0);
     t1->SetBranchAddress("cent", &cent0);
     t1->SetBranchAddress("ptg", &pt0);
     t1->SetBranchAddress("etag", &eta0);
     t1->SetBranchAddress("phig", &phi0);
     int neve=t1->GetEntries();
     cout<<"Nevts = "<<neve<<endl;
     neve = 300000;
     for(int ne=0; ne<neve; ne++){
       if(ne%1000==0)  cout<<"Running "<<ne<<"th event"<<endl;
       t1->GetEntry(ne);

       for(int j=0;j<nCentBin;j++){
         for(int iH=0; iH<nHarmonics; iH++){
           QhfPlus[j][iH]=0;   
           QhfMinus[j][iH]=0;   
         }
       }

       int ibin=-1;
       for(int j=0;j<nCentBin;j++)
       //if(b0>=bbin[j]&&b0<bbin[j+1])
       if(cent0>=cbin[j]&&cent0<cbin[j+1])
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
        
       TComplex temp;
       double tempReal;
       for(int iH=0; iH<nHarmonics; iH++){
         hQhfPlusX[ibin][iH]->Fill(QhfPlus[ibin][iH].Re());
         hQhfPlusY[ibin][iH]->Fill(QhfPlus[ibin][iH].Im());
         hQhfPlusQ[ibin][iH]->Fill(TComplex::Abs(QhfPlus[ibin][iH]));
         hQhfMinusX[ibin][iH]->Fill(QhfMinus[ibin][iH].Re());
         hQhfMinusY[ibin][iH]->Fill(QhfMinus[ibin][iH].Im());
         hQhfMinusQ[ibin][iH]->Fill(TComplex::Abs(QhfMinus[ibin][iH]));
         temp=QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH]);
         if(useRe) double vnabs2evt=temp.Re();  // or use Abs(temp) ???
         else double vnabs2evt=TComplex::Abs(temp);  // or use Abs(temp) ???
         //double vnabs2evt=(QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re();
         VnAbs2[ibin][iH]+=vnabs2evt;
         VnAbs4[ibin][iH]+=vnabs2evt*vnabs2evt;
         VnAbs6[ibin][iH]+=vnabs2evt*vnabs2evt*vnabs2evt;
         hVnAbs2[ibin][iH]->Fill(vnabs2evt);
         hVnAbs4[ibin][iH]->Fill(vnabs2evt*vnabs2evt);
         hVnAbs6[ibin][iH]->Fill(vnabs2evt*vnabs2evt*vnabs2evt);
       }
       temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V2Abs2V3Abs2[ibin]+=tempReal;
       hV2Abs2V3Abs2[ibin]->Fill(tempReal);
       //V2Abs2V3Abs2[ibin]+=(QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2])).Re();
       temp=QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][1]*TComplex::Conjugate(QhfMinus[ibin][1]) * QhfPlus[ibin][2]*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);       
       V2Abs4V3Abs2[ibin]+=tempReal;
       hV2Abs4V3Abs2[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][3]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V4V2starV2star[ibin]+=tempReal;
       hV4V2starV2star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V6V2starV2starV2star[ibin]+=tempReal;
       hV6V2starV2starV2star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][5]*TComplex::Conjugate(QhfMinus[ibin][2])*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V6V3starV3star[ibin]+=tempReal;
       hV6V3starV3star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][4]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V5V2starV3star[ibin]+=tempReal;
       hV5V2starV3star[ibin]->Fill(tempReal);
       temp=QhfPlus[ibin][6]*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][1])*TComplex::Conjugate(QhfMinus[ibin][2]);
       if(useRe) tempReal=temp.Re();
       else tempReal=TComplex::Abs(temp);
       V7V2starV2starV3star[ibin]+=tempReal;
       hV7V2starV2starV3star[ibin]->Fill(tempReal);

       delete pVect_hfPlus;
       delete pVect_hfMinus;
     } //evt loop

     cout<<"Mult = "<<hMultPlus->GetMean()<<"   "<<hMultMinus->GetMean()<<endl;
     for(int ibin=0; ibin<nCentBin; ibin++){
       if(VnAbs2[ibin][1]<0 || VnAbs4[ibin][1]<0 || VnAbs6[ibin][1]<0 || V2Abs2V3Abs2[ibin]<0) cout<<"SQRT(negative)!"<<", ibin="<<ibin<<endl;
       //v2Psi2[ibin]=(VnAbs2[ibin][1]/nEvent[ibin])/sqrt(VnAbs2[ibin][1]/nEvent[ibin]);
       //v3Psi3[ibin]=(VnAbs2[ibin][2]/nEvent[ibin])/sqrt(VnAbs2[ibin][2]/nEvent[ibin]);
       //v4Psi2[ibin]=(V4V2starV2star[ibin]/nEvent[ibin])/sqrt(VnAbs4[ibin][1]/nEvent[ibin]);
       //v4Psi4[ibin]=(VnAbs2[ibin][3]/nEvent[ibin])/sqrt(VnAbs2[ibin][3]/nEvent[ibin]);;
       //v6Psi2[ibin]=(V6V2starV2starV2star[ibin]/nEvent[ibin])/sqrt(VnAbs6[ibin][1]/nEvent[ibin]);
       //v6Psi3[ibin]=(V6V3starV3star[ibin]/nEvent[ibin])/sqrt(VnAbs4[ibin][2]/nEvent[ibin]);
       //v6Psi6[ibin]=(VnAbs2[ibin][5]/nEvent[ibin])/sqrt(VnAbs2[ibin][5]/nEvent[ibin]);;
       //v5Psi2Psi3[ibin]=(V5V2starV3star[ibin]/nEvent[ibin])/sqrt(V2Abs2V3Abs2[ibin]/nEvent[ibin]);
       //v7Psi2Psi3[ibin]=(V7V2starV2starV3star[ibin]/nEvent[ibin])/sqrt(V2Abs4V3Abs2[ibin]/nEvent[ibin]);
     }

     //for(int ibin=0; ibin<nCentBin; ibin++)
       //cout<<ibin<<"   "<<v2Psi2[ibin]<<"   "<<v3Psi3[ibin]<<"   "<<v4Psi4[ibin]<<"   "<<v6Psi6[ibin]<<endl;
     //for(int ibin=0; ibin<nCentBin; ibin++)
       //cout<<ibin<<"---"<<hVnAbs2[ibin][1]->GetMean()/sqrt(hVnAbs2[ibin][1]->GetMean())<<"   "<<hVnAbs2[ibin][2]->GetMean()/sqrt(hVnAbs2[ibin][2]->GetMean())<<"   "<<hVnAbs2[ibin][3]->GetMean()/sqrt(hVnAbs2[ibin][3]->GetMean())<<"   "<<hVnAbs2[ibin][5]->GetMean()/sqrt(hVnAbs2[ibin][5]->GetMean())<<endl;
     //for(int ibin=0; ibin<nCentBin; ibin++){
       //cout<<(bbin[ibin]+bbin[ibin+1])/2<<"   "<<v4Psi2[ibin]<<"   "<<v6Psi2[ibin]<<"   "<<v6Psi3[ibin]<<"   "<<v5Psi2Psi3[ibin]<<"   "<<v7Psi2Psi3[ibin]<<endl;  
     //}
  ofstream outf;
  outf.open("corrFlow.txt");  
  double value;
  double err;
  for(int ibin=0; ibin<nCentBin; ibin++){
    value=hV5V2starV3star[ibin]->GetMean()/sqrt(hV2Abs2V3Abs2[ibin]->GetMean());
    err=value*sqrt(hV5V2starV3star[ibin]->GetMeanError()*hV5V2starV3star[ibin]->GetMeanError()/hV5V2starV3star[ibin]->GetMean()/hV5V2starV3star[ibin]->GetMean() + 1.0/4*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
    outf<<ibin*5+2.5<<"  "<<value<<"  "<<err<<endl;
  }
  for(int ibin=0; ibin<nCentBin; ibin++){
    value=hV7V2starV2starV3star[ibin]->GetMean()/sqrt(hV2Abs4V3Abs2[ibin]->GetMean());
    err=value*sqrt(hV7V2starV2starV3star[ibin]->GetMeanError()*hV7V2starV2starV3star[ibin]->GetMeanError()/hV7V2starV2starV3star[ibin]->GetMean()/hV7V2starV2starV3star[ibin]->GetMean() + 1.0/4*hV2Abs4V3Abs2[ibin]->GetMeanError()*hV2Abs4V3Abs2[ibin]->GetMeanError()/hV2Abs4V3Abs2[ibin]->GetMean()/hV2Abs4V3Abs2[ibin]->GetMean());
    outf<<ibin*5+2.5<<"  "<<value<<"  "<<err<<endl;
  }

  for(int ibin=0; ibin<nCentBin; ibin++){
    value=hV5V2starV3star[ibin]->GetMean()/(hV2Abs2V3Abs2[ibin]->GetMean());
    err=value*sqrt(hV5V2starV3star[ibin]->GetMeanError()*hV5V2starV3star[ibin]->GetMeanError()/hV5V2starV3star[ibin]->GetMean()/hV5V2starV3star[ibin]->GetMean() + 1.0/1*hV2Abs2V3Abs2[ibin]->GetMeanError()*hV2Abs2V3Abs2[ibin]->GetMeanError()/hV2Abs2V3Abs2[ibin]->GetMean()/hV2Abs2V3Abs2[ibin]->GetMean());
    outf<<ibin*5+2.5<<"  "<<value<<"  "<<err<<endl;
  }
  for(int ibin=0; ibin<nCentBin; ibin++){
    value=hV7V2starV2starV3star[ibin]->GetMean()/(hV2Abs4V3Abs2[ibin]->GetMean());
    err=value*sqrt(hV7V2starV2starV3star[ibin]->GetMeanError()*hV7V2starV2starV3star[ibin]->GetMeanError()/hV7V2starV2starV3star[ibin]->GetMean()/hV7V2starV2starV3star[ibin]->GetMean() + 1.0/1*hV2Abs4V3Abs2[ibin]->GetMeanError()*hV2Abs4V3Abs2[ibin]->GetMeanError()/hV2Abs4V3Abs2[ibin]->GetMean()/hV2Abs4V3Abs2[ibin]->GetMean());
    outf<<ibin*5+2.5<<"  "<<value<<"  "<<err<<endl;
  }

  outfile->cd();
  dirQ->cd();
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQhfPlusX[ibin][iH]->Write(); 
      hQhfPlusY[ibin][iH]->Write(); 
      hQhfPlusQ[ibin][iH]->Write(); 
      hQhfMinusX[ibin][iH]->Write(); 
      hQhfMinusY[ibin][iH]->Write(); 
      hQhfMinusQ[ibin][iH]->Write(); 
    }
  }
  outfile->cd();
  dirVn->cd();
  for(int ibin=0; ibin<nCentBin; ibin++){
    for(int iH=0; iH<nHarmonics; iH++){
      hVnAbs2[ibin][iH]->Write();
      hVnAbs4[ibin][iH]->Write();
      hVnAbs6[ibin][iH]->Write();
    }
  }
  outfile->cd();
  dirVnxy->cd();
  for(int ibin=0; ibin<nCentBin; ibin++){
    hV2Abs2V3Abs2[ibin]->Write();
    hV2Abs4V3Abs2[ibin]->Write();
    hV4V2starV2star[ibin]->Write();
    hV6V2starV2starV2star[ibin]->Write();
    hV6V3starV3star[ibin]->Write();
    hV5V2starV3star[ibin]->Write();
    hV7V2starV2starV3star[ibin]->Write();
  }
  outfile->Write();
     //hMultPlus->Draw();
     //hMultMinus->SetLineColor(2);
     //hMultMinus->Draw("same");

}

