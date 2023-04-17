#include "TH1.h"
#include "TRandom3.h"
using namespace std;
#include "newtonsMethod.h"

void ptDepv2inputMC_p2ana(){

  int nEvent = 500;
  int multLow = 500;
  const int multHigh = 500;

  float Psi;
  float pt[multHigh];
  float eta[multHigh];
  float phi[multHigh];
  const int nPtBin = 14;
  float ptBins[nPtBin+1] = {0.2, 0.4, 0.6, 0.8, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0};
  //float ptBins[nPtBin+1] = {0.2, 3.0, 3.2, 3.5, 3.8, 4.2, 4.7, 5.2, 5.8, 6.4, 7.1, 7.8, 8.7, 9.4, 10.0};

  TF1 *ptDist  = new TF1("ptDist","exp(-(x/0.90))+0.15*exp (-(x/15))", 0.2,10);
  TF1 *etaDist = new TF1("etaDist","exp(-(x-2.1)^2/6.3)+exp(-(x+2.1)^2/6.3)",-2.4,2.4);
  TF1 *v2vsPt = new TF1("v2vsPt","((x/3.2)^2.3/(1+(x/3.4)^2.1))*(.00005+(1/x)^1.4)",0.2,10);

  TH1D *v2hist[nPtBin];
  TH1D *phipsihist[nPtBin];
  TH1D *phipsihist0_2pi[nPtBin];
  TH1D *phipsihist0_pi[nPtBin];
  TH1D *v2Input[nPtBin];
  TH1D *meanPt[nPtBin];
  TH1D *ptphipsihist0_2pi[nPtBin][32+8];
  TH1D *mptphipsihist0_2pi[nPtBin];
  TH1D *ptphipsihist0_2pi_1ptbin[32+8];
  TH1D *mptphipsihist0_2pi_1ptbin;
  for(int i=0; i<nPtBin; i++){
    v2hist[i] = new TH1D(Form("v2hist_%d", i), Form("v2hist_%d", i), 120,-1.1,1.1);
    phipsihist[i] = new TH1D(Form("phipsihist_%d", i), Form("phipsihist_%d", i), 160,-8,8);
    phipsihist0_2pi[i] = new TH1D(Form("phipsihist0_2pi_%d", i), Form("phipsihist0_2pi_%d", i), 32+8, -1*TMath::Pi()/4, 2*TMath::Pi()+TMath::Pi()/4); //64+16 or 32+8 (N+N/4)
    for(int j=0; j<32+8; j++){
      ptphipsihist0_2pi[i][j] = new TH1D(Form("ptphipsihist0_2pi_%d_phi_%d", i,j), Form("phipsihist0_2pi_%d_phi_%d", i, j), 100,0,10);
    }
    mptphipsihist0_2pi[i] = new TH1D(Form("mptphipsihist0_2pi_%d", i), Form("mptphipsihist0_2pi_%d", i), 32+8, -1*TMath::Pi()/4, 2*TMath::Pi()+TMath::Pi()/4); //64+16 or 32+8 (N+N/4)
    phipsihist0_pi[i] = new TH1D(Form("phipsihist0_pi_%d", i), Form("phipsihist0_pi_%d", i), 40,-0.5,3.5);
    v2Input[i] = new TH1D(Form("v2Input_%d", i), Form("v2Input_%d", i), 120,-1.1,1.1);
    meanPt[i] = new TH1D(Form("meanPt_%d", i), Form("meanPt_%d", i), 100,0,10);
  }

  // for mpt with 1ptbin
  for(int j=0; j<32+8; j++){
    ptphipsihist0_2pi_1ptbin[j] = new TH1D(Form("ptphipsihist0_2pi_1ptbin_phi_%d", j), Form("phipsihist0_2pi_1ptbin_phi_%d", j), 100,0,10);
  }
  mptphipsihist0_2pi_1ptbin = new TH1D(Form("mptphipsihist0_2pi_1ptbin"), Form("mptphipsihist0_2pi_1ptbin"), 32+8, -1*TMath::Pi()/4, 2*TMath::Pi()+TMath::Pi()/4);

  TH1D *pthist = new TH1D("pthist","pthist",100,0,10);
  TH1D *etahist = new TH1D("etahist","etahist",100,-3,3);
  TH1D *multhist = new TH1D("multhist","multhist",100,multLow-5,multHigh+5);

  TRandom3 *randomN;
  randomN = new TRandom3(0);
  gRandom->SetSeed(0);

  for(int i=0; i<nEvent; i++){
    if(i%50 == 0){
      cout<<" i = "<<i<<" , nEvent = "<<nEvent<<endl;
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
          phipsihist[k]->Fill(newPhi - Psi);
          double deltaphi = 0;
          if((newPhi - Psi) < 0){
            phipsihist0_2pi[k]->Fill(newPhi - Psi + 2*TMath::Pi());
            deltaphi = newPhi - Psi + 2*TMath::Pi();
            //if((newPhi - Psi + 2*TMath::Pi())>TMath::Pi()){
            //  phipsihist0_pi[k]->Fill(newPhi - Psi + 2*TMath::Pi() - TMath::Pi());
            //}else{
            //  phipsihist0_pi[k]->Fill(newPhi - Psi + 2*TMath::Pi());
            //}           
          }else{
            phipsihist0_2pi[k]->Fill(newPhi - Psi);
            deltaphi = newPhi - Psi;
            //if((newPhi - Psi)>TMath::Pi()){
            //  phipsihist0_pi[k]->Fill(newPhi - Psi - TMath::Pi());
            //}else{
            //  phipsihist0_pi[k]->Fill(newPhi - Psi);
            //}
          } 
          v2Input[k]->Fill(v2);
          meanPt[k]->Fill(mypt);

          for(int i_phi=0; i_phi<32+8; i_phi++){
            if(deltaphi>-1*TMath::Pi()/4+i_phi*TMath::Pi()/16 && deltaphi<-1*TMath::Pi()/4+(i_phi+1)*TMath::Pi()/16){ //(0,2*Pi) is 32 bins, bin size is Pi/16
              ptphipsihist0_2pi[k][i_phi]->Fill(mypt);
              //if(k<3){
                ptphipsihist0_2pi_1ptbin[i_phi]->Fill(mypt);
              //}
            }
          }

        } // pt if
      } // pt

    } // particle
  } // event  

  ofstream outTXT;
  outTXT.open("out_ptDep.txt");
  cout<<"nEvent = "<<nEvent<<"  meanMult = "<<multhist->GetMean()<<endl;
  for(int k=0; k<nPtBin; k++){
    //cout<<"k = "<<k<<"  v2input = "<<v2Input[k]->GetMean()<<"  v2Mean = "<<v2hist[k]->GetMean()<<"  v2MeanError = "<<v2hist[k]->GetMeanError()<<endl;
    outTXT<<k<<"  "<<meanPt[k]->GetMean()<<"  "<<v2Input[k]->GetMean()<<"   "<<v2hist[k]->GetMean()<<"  "<<v2hist[k]->GetMeanError()<<endl;
    cout<<k<<"  "<<meanPt[k]->GetMean()<<"  "<<v2Input[k]->GetMean()<<"   "<<v2hist[k]->GetMean()<<"  "<<v2hist[k]->GetMeanError()<<endl;

    // set mpt hist bin contents
    // Only needed for bins from 5 to 36, 1-4 and 37-40 are 0
    for(int i_phi=4; i_phi<32+4; i_phi++){ //not 0-32+8 

      mptphipsihist0_2pi[k]->SetBinContent(i_phi+1, ptphipsihist0_2pi[k][i_phi]->GetMean()); //4+1=5 is the first none 0 bin
      mptphipsihist0_2pi[k]->SetBinError(i_phi+1, ptphipsihist0_2pi[k][i_phi]->GetMeanError()); //4+1=5 is the first none 0 bin

    }

  }

  // for mpt with 1ptbin
  for(int i_phi=4; i_phi<32+4; i_phi++){ //not 0-32+8 

    mptphipsihist0_2pi_1ptbin->SetBinContent(i_phi+1, ptphipsihist0_2pi_1ptbin[i_phi]->GetMean()); //4+1=5 is the first none 0 bin
    mptphipsihist0_2pi_1ptbin->SetBinError(i_phi+1, ptphipsihist0_2pi_1ptbin[i_phi]->GetMeanError()); //4+1=5 is the first none 0 bin
  
  }   

    TFile *outFile = new TFile("output_histograms.root","recreate");
    outFile->cd(); 
    pthist->Write();
    etahist->Write();
    multhist->Write();
    for(int i=0; i<nPtBin; i++){
      v2hist[i]->Write();
      phipsihist[i]->Write();
      phipsihist0_2pi[i]->Write();
      phipsihist0_pi[i]->Write();
      v2Input[i]->Write();
      meanPt[i]->Write();

      for(int j=0; j<32+8; j++){
        ptphipsihist0_2pi[i][j]->Write();
      }
      mptphipsihist0_2pi[i]->Write();

    }
    // for mpt with 1ptbin
    for(int j=0; j<32+8; j++){
      ptphipsihist0_2pi_1ptbin[j]->Write();
    }
    mptphipsihist0_2pi_1ptbin->Write();

    outFile->Write();
    outFile->Close();


}


