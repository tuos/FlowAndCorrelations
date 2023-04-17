#include "TH1.h"
#include "TRandom3.h"

#include "TComplex.h"

using namespace std;
#include "newtonsMethod.h"

#define nHarmonics 2
#define nPtBin 14

  TComplex QhfPlus[nHarmonics];
  TComplex QhfMinus[nHarmonics];
  TComplex QtrkPtPlus[nHarmonics][nPtBin];
  TComplex QtrkPtMinus[nHarmonics][nPtBin];
  TH1D* hQhfPlusX[nHarmonics];
  TH1D* hQhfPlusY[nHarmonics];
  TH1D* hQhfMinusX[nHarmonics];
  TH1D* hQhfMinusY[nHarmonics];
  TH1D* hQtrkPtPlusX[nHarmonics][nPtBin];
  TH1D* hQtrkPtPlusY[nHarmonics][nPtBin];
  TH1D* hQtrkPtMinusX[nHarmonics][nPtBin];
  TH1D* hQtrkPtMinusY[nHarmonics][nPtBin];

  TH1D* hqnPlusQnMinusStar[nHarmonics][nPtBin];
  TH1D* hqnMinusQnPlusStar[nHarmonics][nPtBin];
  TH1D* hQnPlusQnMinusStar[nHarmonics];

         double sumwPlus=0;
         double sumwMinus=0;
         double sumwPlusTrk[nPtBin]={0.0};
         double sumwMinusTrk[nPtBin]={0.0};

void ptDepv2inputMC(){

  int nEvent = 20000;
  int multLow = 300;
  const int multHigh = 305;

  float Psi;
  float pt[multHigh];
  float eta[multHigh];
  float phi[multHigh];
  //const int nPtBin = 14;
  float ptBins[nPtBin+1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};

  TF1 *ptDist  = new TF1("ptDist","exp(-(x/0.90))+0.15*exp (-(x/15))", 0.2,10);
  TF1 *etaDist = new TF1("etaDist","exp(-(x-2.1)^2/6.3)+exp(-(x+2.1)^2/6.3)",-2.4,2.4);
  TF1 *v2vsPt = new TF1("v2vsPt","((x/3.2)^2.3/(1+(x/3.4)^2.1))*(.00005+(1/x)^1.4)",0.2,10);

  TH1D *v2hist[nPtBin];
  TH1D *v2Input[nPtBin];
  TH1D *meanPt[nPtBin];
  for(int i=0; i<nPtBin; i++){
    v2hist[i] = new TH1D(Form("v2hist_%d", i), Form("v2hist_%d", i), 120,-1.1,1.1);
    v2Input[i] = new TH1D(Form("v2Input_%d", i), Form("v2Input_%d", i), 120,-1.1,1.1);
    meanPt[i] = new TH1D(Form("meanPt_%d", i), Form("meanPt_%d", i), 100,0,10);
  }
  TH1D *pthist = new TH1D("pthist","pthist",100,0,10);
  TH1D *etahist = new TH1D("etahist","etahist",100,-3,3);
  TH1D *multhist = new TH1D("multhist","multhist",100,multLow-5,multHigh+5);

  for(int i=0; i<nHarmonics; i++){
    hQhfPlusX[i] = new TH1D(Form("hQhfPlusX_%d", i), Form("hQhfPlusX_%d", i), 100,-1000,1000);
    hQhfPlusY[i] = new TH1D(Form("hQhfPlusY_%d", i), Form("hQhfPlusY_%d", i), 100,-1000,1000);
    hQhfMinusX[i] = new TH1D(Form("hQhfMinusX_%d", i), Form("hQhfMinusX_%d", i), 100,-1000,1000);
    hQhfMinusY[i] = new TH1D(Form("hQhfMinusY_%d", i), Form("hQhfMinusY_%d", i), 100,-1000,1000);
    for(int j=0; j<nPtBin; j++){
      hQtrkPtPlusX[i][j] = new TH1D(Form("hQhfPlusX_n%d_pt%d", i,j), Form("hQhfPlusX_n%d_pt%d", i,j), 100,-1000,1000);
      hQtrkPtPlusY[i][j] = new TH1D(Form("hQhfPlusY_n%d_pt%d", i,j), Form("hQhfPlusY_n%d_pt%d", i,j), 100,-1000,1000);
      hQtrkPtMinusX[i][j] = new TH1D(Form("hQhfMinusX_n%d_pt%d", i,j), Form("hQhfMinusX_n%d_pt%d", i,j), 100,-1000,1000);
      hQtrkPtMinusY[i][j] = new TH1D(Form("hQhfMinusY_n%d_pt%d", i,j), Form("hQhfMinusY_n%d_pt%d", i,j), 100,-1000,1000);

      hqnPlusQnMinusStar[i][j] = new TH1D(Form("hqnPlusQnMinusStar_n%d_pt%d", i,j), Form("hqnPlusQnMinusStar_n%d_pt%d", i,j), 100,-1000,1000);
      hqnMinusQnPlusStar[i][j] = new TH1D(Form("hqnMinusQnPlusStar_n%d_pt%d", i,j), Form("hqnMinusQnPlusStar_n%d_pt%d", i,j), 100,-1000,1000);
    }
    hQnPlusQnMinusStar[i] = new TH1D(Form("hQnPlusQnMinusStar_%d", i), Form("hQnPlusQnMinusStar_%d", i), 100,-1000,1000);

  }//iH

  TRandom3 *randomN;
  randomN = new TRandom3(0);
  gRandom->SetSeed(0);

  for(int i=0; i<nEvent; i++){
    if(i%500 == 0){
      cout<<" i = "<<i<<" , nEvent = "<<nEvent<<endl;
    }

   sumwPlus=0;
   sumwMinus=0;
    for(int iPt=0; iPt<nPtBin; iPt++){
      sumwPlusTrk[iPt]=0.0;
      sumwMinusTrk[iPt]=0.0;
    }

    for(int iH=0; iH<nHarmonics; iH++){
      QhfPlus[iH]=0;   
      QhfMinus[iH]=0;
      for(int iPt=0; iPt<nPtBin; iPt++){
        QtrkPtPlus[iH][iPt]=0;
        QtrkPtMinus[iH][iPt]=0;
      }
    }

    Psi = randomN->Uniform(0.0, TMath::Pi()*2);
    int mult = randomN->Uniform(multLow, multHigh);
    multhist->Fill(mult);
    //cout<<"Psi = "<<Psi<<"   mult = "<<mult<<endl;
    for(int j=0; j<mult; j++){
      float mypt = ptDist->GetRandom();
      pthist->Fill(mypt);
      float myeta = etaDist->GetRandom();
      etahist->Fill(myeta);
      float phi0 = randomN->Uniform(0.0, TMath::Pi()*2);

      float v2 = v2vsPt->Eval(mypt);
      //float v2 = 0.1;
      float initialPhi = 0.01;

      // get a better initial phi: 
      double phiTmp = -5;
      while (func(phiTmp, v2, Psi, phi0)*func(phiTmp+0.2, v2, Psi, phi0)>0){
        phiTmp = phiTmp + 0.2;
        //cout<<"phiTmp = "<<phiTmp<<endl;
      }   
      initialPhi = phiTmp + 0.1; //update initialPhi to fix the method
      //cout<<"initialPhi = "<<initialPhi<<endl;    

      float newPhi = newtonMethod(initialPhi, v2, Psi, phi0);

      for(int k=0; k<nPtBin; k++){
        if(mypt>ptBins[k] && mypt<ptBins[k+1]){
          v2hist[k]->Fill(cos(2*(newPhi - Psi)));
          v2Input[k]->Fill(v2);
          meanPt[k]->Fill(mypt);
        }
      }//pt

      //mypt, myeta, newPhi;
      // eta(-1,1) for trk, eta (1, 2.4) for hf
         int cpt=-1;
         for(int ipt=0; ipt<nPtBin; ipt++){
           if(mypt>=ptBins[ipt] && mypt<ptBins[ipt+1])
             cpt=ipt;
         }
         if(cpt<0) cpt=nPtBin-1;

       for(int iH=0; iH<nHarmonics; iH++){
         double pt_weight = 1.0; 
         if(myeta>1.0){
           sumwPlus+= pt_weight;
           QhfPlus[iH]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*newPhi));
         }
         if(myeta<-1.0){
           sumwMinus+= pt_weight;
           QhfMinus[iH]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*newPhi));
         }
         if(myeta>0.0 && myeta<1.0){
           sumwPlusTrk[cpt]+= pt_weight;
           QtrkPtPlus[iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*newPhi));
         }
         if(myeta>-1.0 && myeta<0.0){
           sumwMinusTrk[cpt]+= pt_weight;
           QtrkPtMinus[iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*newPhi));
         }
       }//iH

    }//mult

    for(int iH=0; iH<nHarmonics; iH++){
      if(sumwPlus>0) { QhfPlus[iH]=QhfPlus[iH]/(sumwPlus/nHarmonics*1.0); }
      else { QhfPlus[iH]=0; }
      if(sumwMinus>0) { QhfMinus[iH]=QhfMinus[iH]/(sumwMinus/nHarmonics*1.0); }
      else { QhfMinus[iH]=0; }
      for(int iPt=0; iPt<nPtBin; iPt++){
        if(sumwPlusTrk[iPt]>0) { QtrkPtPlus[iH][iPt]=QtrkPtPlus[iH][iPt]/(sumwPlusTrk[iPt]/nHarmonics*1.0); }
        else {QtrkPtPlus[iH][iPt]=0; }
        if(sumwMinusTrk[iPt]>0) { QtrkPtMinus[iH][iPt]=QtrkPtMinus[iH][iPt]/(sumwMinusTrk[iPt]/nHarmonics*1.0); }
        else { QtrkPtMinus[iH][iPt]=0; }
      }
    }//iH

       for(int iH=0; iH<nHarmonics; iH++){
          hQhfPlusX[iH]->Fill(QhfPlus[iH].Re());
          hQhfPlusY[iH]->Fill(QhfPlus[iH].Im());
          hQhfMinusX[iH]->Fill(QhfMinus[iH].Re());
          hQhfMinusY[iH]->Fill(QhfMinus[iH].Im());
         for(int iPt=0; iPt<nPtBin; iPt++){
           hQtrkPtPlusX[iH][iPt]->Fill(QtrkPtPlus[iH][iPt].Re());
           hQtrkPtPlusY[iH][iPt]->Fill(QtrkPtPlus[iH][iPt].Im());
           hQtrkPtMinusX[iH][iPt]->Fill(QtrkPtMinus[iH][iPt].Re());
           hQtrkPtMinusY[iH][iPt]->Fill(QtrkPtMinus[iH][iPt].Im());
         }
       } //iH

  // final histograms
       for(int iH=0; iH<nHarmonics; iH++){
          hQnPlusQnMinusStar[iH]->Fill((QhfPlus[iH]*TComplex::Conjugate(QhfMinus[iH])).Re());
         for(int iPt=0; iPt<nPtBin; iPt++){
           hqnPlusQnMinusStar[iH][iPt]->Fill((QtrkPtPlus[iH][iPt]*TComplex::Conjugate(QhfMinus[iH])).Re());
           hqnMinusQnPlusStar[iH][iPt]->Fill((QtrkPtMinus[iH][iPt]*TComplex::Conjugate(QhfPlus[iH])).Re());

         }
       }


  }//event  

  cout<<"nEvent = "<<nEvent<<"  meanMult = "<<multhist->GetMean()<<endl;
  for(int k=0; k<nPtBin; k++){
    //cout<<"k = "<<k<<"  v2input = "<<v2Input[k]->GetMean()<<"  v2Mean = "<<v2hist[k]->GetMean()<<"  v2MeanError = "<<v2hist[k]->GetMeanError()<<endl;
    cout<<k<<"  "<<meanPt[k]->GetMean()<<"  "<<v2Input[k]->GetMean()<<"   "<<v2hist[k]->GetMean()<<"  "<<v2hist[k]->GetMeanError()<<endl;
  }

  for(int iH=1; iH<nHarmonics; iH++){
    for(int iPt=0; iPt<nPtBin; iPt++){
      cout<<iH<<"  "<<iPt<<"  "<<meanPt[iPt]->GetMean()<<"   "<<v2Input[iPt]->GetMean()<<"  "<<hqnPlusQnMinusStar[iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iH]->GetMean()))<<"  "<<hqnPlusQnMinusStar[iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iH]->GetMean()))<<"     "<<hqnMinusQnPlusStar[iH][iPt]->GetMean()/sqrt(fabs(hQnPlusQnMinusStar[iH]->GetMean()))<<"  "<<hqnMinusQnPlusStar[iH][iPt]->GetMeanError()/sqrt(fabs(hQnPlusQnMinusStar[iH]->GetMean()))<<endl;
    }

    for(int iPt=0; iPt<nPtBin; iPt++){
//      cout<<iH<<"  "<<iPt<<"  "<<meanPt[iPt]->GetMean()<<"   "<<v2Input[iPt]->GetMean()<<"  "<<hqnPlusQnMinusStar[iH][iPt]->GetMean()<<"  "<<hqnPlusQnMinusStar[iH][iPt]->GetMeanError()<<"     "<<hqnMinusQnPlusStar[iH][iPt]->GetMean()<<"  "<<hqnMinusQnPlusStar[iH][iPt]->GetMeanError()<<"     "<<fabs(hQnPlusQnMinusStar[iH]->GetMean())<<endl;
    }

  }


}


