#include <stdio.h>
#include <complex>
#include <iostream>
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include <TMath.h>
using namespace std; 
void cov_test_pp_2dhist(){

     long nEvt, nEvtProcess; 

     Int_t MultIndex;
     Int_t multBin = -1;
     Int_t nParticle, iParticle;
     Float_t phi[20000];
     Float_t pt[20000];
     Float_t eta[20000];
     //TH1D *histPt = new TH1D("histPt", "histPt", 200,0,10);

     //TH2D *hist2DPtVsEta = new TH2D("hist2DPtVsEta","2D histogram of pT vs eta", 200, -2.4,2.4, 200,0.0,10);

     TH1D *histQSinPlus = new TH1D("histQSinPlus", "", 200,-1,1);
     TH1D *histQSinMinus = new TH1D("histQSinMinus", "", 200,-1,1);
     TH1D *histQCosPlus = new TH1D("histQCosPlus", "", 200,-1,1);
     TH1D *histQCosMinus = new TH1D("histQCosMinus", "", 200,-1,1);

     TH1D *histTempEP = new TH1D("histTempEP", "", 200, -1,1);
     /*TH1D *histTempPtP = new TH1D("histTempPtP", "", 200, -1,1);
     TH1D *histTempPnP = new TH1D("histTempPnP", "", 200, -1, 1);


     TH1D *histPtPCos = new TH1D("histPtPCos", "", 200,-1,1);
     TH1D *histPtPSin = new TH1D("histPtPSin", "", 200,-1,1); 
     TH1D *histPnPCos = new TH1D("histPnPCos", "", 200,-1,1);
     TH1D *histPnPSin = new TH1D("histPnPSin", "", 200,-1,1);  
*/
     double eventPlanePlus, eventPlaneMinus;

     

     const int NB_SLICE_MULT = 40;
     double minMultCut[NB_SLICE_MULT] =  {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195}; 
     double maxMultCut[NB_SLICE_MULT] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200}; //18 bins
     //double minPtCut[NB_SLICE_MULT] = {0.2,0.4,0.6,0.8,1.1,1.4,1.75,2.2,2.75,3.45,4.2,5.05,6.0,7.2,8.5};
     //double maxPtCut[NB_SLICE_MULT] = {0.4,0.6,0.8,1.1,1.4,1.75,2.2,2.75,3.45,4.2,5.05,6.0,7.2,8.5,1000}; //15 bins
     TH1D *histEventPlaneRes[NB_SLICE_MULT];   
     TH1D *histV2EP[NB_SLICE_MULT];
     TH2D *histCorrEP[NB_SLICE_MULT];
     //TH1D *histV2PtP[NB_SLICE_MULT];
     //TH1D *histV2PnP[NB_SLICE_MULT];
     TH1D *histMult[NB_SLICE_MULT];
     for(int i=0; i<NB_SLICE_MULT; i++){
       histCorrEP[i] = new TH2D(Form("histCorrEP_%d",i), "", 200,0,10,200,0,10);
       histV2EP[i] = new TH1D(Form("histV2EP_%d",i), "", 200,-1,1);
       //histV2PtP[i] = new TH1D(Form("histV2PtP_%d",i), "", 200,-1,1);
       //histV2PnP[i] = new TH1D(Form("histV2PnP_%d",i), "", 200,-1,1);  
       histMult[i] = new TH1D(Form("histMult_%d",i), "", 200,0,200);
       histEventPlaneRes[i] = new TH1D(Form("histEventPlaneRes_%d",i), "", 200,-1,1);
     }

     //TH2D *hist2Dx_y = new TH2D("hist2Dx_y","Nucleon position x vs y", 200, -10,10, 200,-10,10);
/*
     TFile inFile("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_1.root", "read");
     TTree *t1 = (TTree*)inFile.Get("hadronTree");
     t1->SetBranchAddress("nMultiplicityTree", &nParticle);
     t1->SetBranchAddress("ptTree", &pt);
     t1->SetBranchAddress("etaTree", &eta);
     t1->SetBranchAddress("phiTree", &phi);
*/
     TChain t1("demo/anaTree");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_1.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_10.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_100.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_101.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_102.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_103.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_104.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_105.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_106.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_107.root");
     t1.SetBranchAddress("nTrk", &nParticle);
     t1.SetBranchAddress("pt", &pt);
     t1.SetBranchAddress("eta", &eta);
     t1.SetBranchAddress("phi", &phi);




/*
     const int maxNucleons = 208;
     Int_t nNucleonsProjectile, nNucleonsTarget;
     Float_t xProjectile[maxNucleons];
     Float_t yProjectile[maxNucleons];
     Int_t statusProjectile[maxNucleons];
     Float_t xTarget[maxNucleons];
     Float_t yTarget[maxNucleons];
     Int_t statusTarget[maxNucleons];
     Float_t rpart, phipart, Psipart;

     TTree *t2 = (TTree*)inFile.Get("participantTree");
     t2->SetBranchAddress("nNucleonsProjectileTree", &nNucleonsProjectile);
     t2->SetBranchAddress("xProjectileTree", &xProjectile);
     t2->SetBranchAddress("yProjectileTree", &yProjectile);
     t2->SetBranchAddress("statusProjectileTree", &statusProjectile);
     t2->SetBranchAddress("nNucleonsTargetTree", &nNucleonsTarget);
     t2->SetBranchAddress("xTargetTree", &xTarget);
     t2->SetBranchAddress("yTargetTree", &yTarget);
     t2->SetBranchAddress("statusTargetTree", &statusTarget);

     Int_t Partonpid[200000];
     Int_t nParton;
     Float_t xParton[200000];
     Float_t yParton[200000];
     Float_t rparton, phiparton, Psiparton;

     TTree *t3 = (TTree*)inFile.Get("partonTree");
     t3->SetBranchAddress("nPartonTree", &nParton);
     t3->SetBranchAddress("xPartonTree", &xParton);
     t3->SetBranchAddress("yPartonTree", &yParton);
     t3->SetBranchAddress("PartonpidTree", &Partonpid);
*/     
     //t1->AddFriend("t2");

     double min_PT = 0.3, max_PT = 2., min_PT_Nch = 0.5, max_PT_Nch = 5.;

     //nEvt=t1.GetEntries();
     nEvt=1000000;
     //nEvtProcess=50;
     // first event loop for estimatig the event plane resolution
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%5000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       //cout<<"ne = "<<ne<<" ; nParticle= "<<nParticle<<endl;
       t1.GetEntry(ne);
       //t2->GetEntry(ne);
       
       histQSinPlus->Reset();
       histQSinMinus->Reset();
       histQCosPlus->Reset();
       histQCosMinus->Reset();

       //MultIndex = (nParticle-1) / 20;

       //finding multBin for each event
       //int multBin=-1;

       Int_t nParticle_cut = 0;
       for(int i=0;i<nParticle;i++){
         if(pt[i] < min_PT_Nch || pt[i] > max_PT_Nch) continue;
         nParticle_cut++;
       }

       if(nParticle_cut>200 || nParticle_cut<3) continue;

       for(int imult=0;imult<NB_SLICE_MULT;imult++){
          if((nParticle_cut>minMultCut[imult]&&nParticle_cut<=maxMultCut[imult])){
              multBin=imult;
          }
       }


      // if(ne==0){ //The first event
        // cout<<"nNucleonsProjectile = "<<nNucleonsProjectile<<endl;
         //for(int i=0; i<nNucleonsProjectile; i++){
           //hist2Dx_y->Fill(xProjectile[i], yProjectile[i]);
           //cout<<"x = "<<xProjectile[i]<<",  y = "<<yProjectile[i]<<endl;
         //}
         //cout<<"nNucleonsTarget = "<<nNucleonsTarget<<endl;
         //for(int i=0; i<nNucleonsTarget; i++){
           //hist2Dx_y->Fill(xTarget[i], yTarget[i]);
         //}
       //}

       Int_t negative_eta_EP_count = 0;
       Int_t positive_eta_EP_count = 0;
       Int_t mid_eta_count = 0;
       for(iParticle=0; iParticle<nParticle; iParticle++){
           if(pt[iParticle]<min_PT || pt[iParticle]>max_PT) continue;
           //cout<<"evtID = "<<ne<<",  particlesPt = "<<pt[iParticle]<<",  particlePhi = "<<phi[iParticle]<<endl;
           //histPt->Fill(pt[iParticle]);
           //hist2DPtVsEta->Fill(eta[iParticle], pt[iParticle]);
       
           if(eta[iParticle]>1.0){
             histQSinPlus->Fill(sin(2*phi[iParticle]));
             histQCosPlus->Fill(cos(2*phi[iParticle]));
             positive_eta_EP_count++;
           
           } else if(eta[iParticle]<-1.0){
             histQSinMinus->Fill(sin(2*phi[iParticle]));
             histQCosMinus->Fill(cos(2*phi[iParticle]));
             negative_eta_EP_count++;
           } else if(eta[iParticle]>-0.5 && eta[iParticle]<0.5){
             mid_eta_count++;

           }
       }

       eventPlanePlus = 1.0/2*atan2(histQSinPlus->GetMean(), histQCosPlus->GetMean()); // EP in (-pi/2, pi/2);

       eventPlaneMinus = 1.0/2*atan2(histQSinMinus->GetMean(), histQCosMinus->GetMean()); // EP in (-pi/2, pi/2);
       if(negative_eta_EP_count>0 && positive_eta_EP_count>0 && mid_eta_count>0){
         histEventPlaneRes[multBin]->Fill(cos(2*(eventPlanePlus - eventPlaneMinus)));
       }

      } // end of the first event loop
      //cout<<"Event Plane resolution = "<<sqrt(histEventPlaneRes->GetMean())<<endl;

      //histPt->Draw();
      //hist2DPtVsEta->Draw("colz");

     // starting the second event loop
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%5000==0)  cout<<"Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1.GetEntry(ne);
       //t2->GetEntry(ne);
       //t3->GetEntry(ne);

       histQSinPlus->Reset();
       histQSinMinus->Reset();
       histQCosPlus->Reset();
       histQCosMinus->Reset();
       //histPtPCos->Reset();
       //histPtPSin->Reset();
       //histPnPCos->Reset();
       //histPnPSin->Reset();
       histTempEP->Reset();
       //histTempPtP->Reset();
       //histTempPnP->Reset();

       //MultIndex = (nParticle-1) / 20;

       // finding the multBin for each event
       //int multBin=-1;

       Int_t nParticle_cut = 0;
       for(int i=0;i<nParticle;i++){
         if(pt[i] < min_PT_Nch || pt[i] > max_PT_Nch) continue;
         nParticle_cut++;
       }

       if(nParticle_cut>200 || nParticle_cut<3) continue;

       for(int imult=0;imult<NB_SLICE_MULT;imult++){
          if((nParticle_cut>minMultCut[imult]&&nParticle_cut<=maxMultCut[imult])){
              multBin=imult;
          }
       }


       //histMult[multBin]->Fill(nParticle);
/*
       // estimating the participant plane angle
       for(int i=0; i<nNucleonsProjectile; i++){
           if(statusProjectile[i]>0){
               rpart = TMath::Sqrt((xProjectile[i]*xProjectile[i]) + (yProjectile[i]*yProjectile[i]));
               phipart = TMath::ATan2(yProjectile[i], xProjectile[i]);
               histPtPCos->Fill(rpart*rpart*(TMath::Cos(2*phipart)));
               histPtPSin->Fill(rpart*rpart*(TMath::Sin(2*phipart)));
           }
       }
       for(int i=0; i<nNucleonsTarget; i++){
           if(statusTarget[i]>0){
               rpart = TMath::Sqrt((xTarget[i]*xTarget[i]) + (yTarget[i]*yTarget[i]));
               phipart = TMath::ATan2(yTarget[i], xTarget[i]);
               histPtPCos->Fill(rpart*rpart*(TMath::Cos(2*phipart)));
               histPtPSin->Fill(rpart*rpart*(TMath::Sin(2*phipart)));
           }
       }
       Psipart=(TMath::ATan2(histPtPSin->GetMean(),histPtPCos->GetMean())+TMath::Pi())/2.;

       // estimating the parton plane angle
       for(int i=0;i<nParton; i++){
           rparton = TMath::Sqrt((xParton[i]*xParton[i]) + (yParton[i]*yParton[i]));
           phiparton = TMath::ATan2(yParton[i], xParton[i]);
           histPnPCos->Fill(rparton*rparton*(TMath::Cos(2*phiparton)));
           histPnPSin->Fill(rparton*rparton*(TMath::Sin(2*phiparton)));
       }
       Psiparton=(TMath::ATan2(histPnPSin->GetMean(),histPnPCos->GetMean())+TMath::Pi())/2.;
*/

       // estimating event plane angle
       Int_t negative_eta_EP_count = 0;
       Int_t positive_eta_EP_count = 0;
       for(iParticle=0; iParticle<nParticle; iParticle++){
           if(pt[iParticle]<min_PT || pt[iParticle]>max_PT) continue;

           if(eta[iParticle]>1.0){
             histQSinPlus->Fill(sin(2*phi[iParticle]));
             histQCosPlus->Fill(cos(2*phi[iParticle]));
             positive_eta_EP_count++;
           }
           if(eta[iParticle]<-1.0){
             histQSinMinus->Fill(sin(2*phi[iParticle]));
             histQCosMinus->Fill(cos(2*phi[iParticle]));
             negative_eta_EP_count++;
           }
        }
       //if(positive_eta_EP_count==0 || negative_eta_EP_count==0 continue)
       eventPlanePlus = 1.0/2*atan2(histQSinPlus->GetMean(), histQCosPlus->GetMean()); // EP in (-pi/2, pi/2);
       eventPlaneMinus = 1.0/2*atan2(histQSinMinus->GetMean(), histQCosMinus->GetMean()); // EP in (-pi/2, pi/2);

       Double_t mean_PT_sum = 0;
       Double_t mean_PT_count = 0;
       // calculating v2 for each event
       for(iParticle=0; iParticle<nParticle; iParticle++){
         if(pt[iParticle]<min_PT || pt[iParticle]>max_PT) continue;
         //histTempPtP->Fill(cos(2*(phi[iParticle] - Psipart)));
         //histTempPnP->Fill(cos(2*(phi[iParticle] - Psiparton)));

         if(eta[iParticle]>-0.5 && eta[iParticle]<0.5){
           mean_PT_sum += pt[iParticle];
           mean_PT_count += 1.;

         } else if(eta[iParticle]>0.75){
           histTempEP->Fill(cos(2*(phi[iParticle] - eventPlaneMinus)));
          
         } else if(eta[iParticle]<-0.75){
           histTempEP->Fill(cos(2*(phi[iParticle] - eventPlanePlus)));
         }
        
       } // end of the particle loop

       if(positive_eta_EP_count>0 && negative_eta_EP_count>0 && mean_PT_count>0.1){
         histCorrEP[multBin]->Fill(pow(histTempEP->GetMean(),2) , mean_PT_sum/mean_PT_count);
         histV2EP[multBin]->Fill(histTempEP->GetMean());
         histMult[multBin]->Fill(nParticle_cut); 
       }
       //histV2PtP[multBin]->Fill(histTempPtP->GetMean());
       //histV2PnP[multBin]->Fill(histTempPnP->GetMean());
       //cout<<eventPlaneMinus<<"   "<<eventPlanePlus<<"   "<<Psipart<<"   "<<Psiparton<<endl;


      } // end of the second event loop

       
      ofstream output_nmultv2EP;
      //ofstream output_nmultv2PtP;
      //ofstream output_nmultv2PnP;
      output_nmultv2EP.open("output_correlations_vs_Nch.txt");
      //output_nmultv2PtP.open("output_nmultv2PtP.txt");
      //output_nmultv2PnP.open("output_nmultv2PnP.txt");
      //Float_t error;
      for(int i=0; i<NB_SLICE_MULT; i++){     
        cout<<histMult[i]->GetEntries()<<"   "<<histMult[i]->GetMean()<<"   "<<histCorrEP[i]->GetCorrelationFactor()<<endl;
        output_nmultv2EP<<histMult[i]->GetEntries()<<"   "<<histMult[i]->GetMean()<<"   "<<histCorrEP[i]->GetCorrelationFactor()<<"     "<<histCorrEP[i]->GetCovariance()<<endl;
         //error = sqrt(pow((histV2EP[i]->GetMeanError()/(histEventPlaneRes[i]->GetMean())),2)+ pow((histV2EP[i]->GetMean()*histEventPlaneRes[i]->GetMeanError()/(pow((histEventPlaneRes[i]->GetMean()) ,2))),2));
        //cout<<histMult[i]->GetMean()<<"   "<<histV2EP[i]->GetMean()/sqrt(fabs(histEventPlaneRes[i]->GetMean()))<<"   "<<error<<endl;
        //output_nmultv2EP<<histMult[i]->GetMean()<<"   "<<histV2EP[i]->GetMean()/sqrt(fabs(histEventPlaneRes[i]->GetMean()))<<"   "<<error<<"   "<<histEventPlaneRes[i]->GetMean()<<"   "<<histEventPlaneRes[i]->GetMeanError()<<endl;
     
       //output_nmultv2PtP<<histMult[i]->GetMean()<<"   "<<histV2PtP[i]->GetMean()<<"   "<<histV2PtP[i]->GetMeanError()<<endl;
     
       //output_nmultv2PnP<<histMult[i]->GetMean()<<"   "<<histV2PnP[i]->GetMean()<<"   "<<histV2PnP[i]->GetMeanError()<<endl;

      } 

      //TCanvas *c1 = new TCanvas("c1","c1",1,1,650,550);
      //hist2Dx_y->SetXTitle("x (fm)");
      //hist2Dx_y->SetYTitle("y (fm)"); 
      //hist2Dx_y->GetXaxis()->CenterTitle(1);
      //hist2Dx_y->GetYaxis()->CenterTitle(1);     
      //hist2Dx_y->Draw("box");
      //c1->SaveAs("plot_hist2Dx_y.pdf");

}
