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
#include "TComplex.h"
#include "TRandom3.h"
using namespace std; 
void covV2PT_vs_Nch_3sub_pp_sincos(){
double tmpXXX=0;
     long nEvt, nEvtProcess;
     float tempEccPtP, tempV2PtP, tempEccPnP, tempV2PnP; 

     //Int_t MultIndex;
     Int_t multBin = -1;
     Int_t nParticle, iParticle;
     //const int NB_SLICE_B = 330;
     const int NB_SLICE_B = 33;
     //double minbCut[NB_SLICE_B] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329,};
     //double maxbCut[NB_SLICE_B] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330};
     double minbCut[NB_SLICE_B] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320};
     double maxbCut[NB_SLICE_B] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330}; 

     //TH1D *histMult_LOOP[NB_SLICE_B];
     //TH1D *histMult_LOOPCUT[NB_SLICE_B];
     TH1D *histMult_3SUB[NB_SLICE_B];
     TH1D *histCovV2PT_3SUB[NB_SLICE_B];
     TH1D *histMeanPT_3SUB[NB_SLICE_B];
     //TH1D *histCovV2PT_LOOP[NB_SLICE_B];
     //TH1D *histMeanPT_LOOP[NB_SLICE_B];
     //TH1D *histCovV2PT_LOOPCUT[NB_SLICE_B];
     //TH1D *histMeanPT_LOOPCUT[NB_SLICE_B];


     for(int i=0; i<NB_SLICE_B; i++){
       //histMult_LOOP[i] = new TH1D(Form("histMult_LOOP_%d",i), "", 2000,0,2000);
       //histMult_LOOPCUT[i] = new TH1D(Form("histMult_LOOPCUT_%d",i), "", 2000,0,2000);
       histMult_3SUB[i] = new TH1D(Form("histMult_3SUB_%d",i), "", 2000,0,2000);
 
       histCovV2PT_3SUB[i] = new TH1D(Form("histCovV2PT_3SUB_%d",i), "", 220,-11,11);
       //histCovV2PT_LOOP[i] = new TH1D(Form("histCovV2PT_LOOP_%d",i), "", 220,-1.1,1.1);
       //histCovV2PT_LOOPCUT[i] = new TH1D(Form("histCovV2PT_LOOPCUT_%d",i), "", 220,-1.1,1.1);
       //histMeanPT_3SUB[i] = new TH1D(Form("histMeanPT_3SUB_%d",i), "", 220,0.5,5.0); // look more into the range

//change this-tuo:
       histMeanPT_3SUB[i] = new TH1D(Form("histMeanPT_3SUB_%d",i), "", 201,-10,2000.0); // look more into the range


       //histMeanPT_LOOP[i] = new TH1D(Form("histMeanPT_LOOP_%d",i), "", 220,0.5,5.0); // look more into the range
       //histMeanPT_LOOPCUT[i] = new TH1D(Form("histMeanPT_LOOPCUT_%d",i), "", 220,0.5,5.0); // look more into the range
     }
     Float_t hadronphi[200000], hadroneta[200000],hadronpt[200000];
     //Float_t rparton, phiparton, phigluon, Psiparton;
     Float_t b;



     TChain t1("demo/anaTree");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_1.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_10.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_100.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_101.root");
     t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_102.root");
     //t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_103.root");
     //t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_104.root");
     //t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_105.root");
     //t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_106.root");
     //t1.Add("/store/user/tuos/loops/cumulants/pythia/PYTHIA8_treept001eta25_FEB05TeV500M/MinBias/PYTHIA8_treept001eta25_FEB05TeV500M/210305_233631/0000/output_treeproduction_pythia13tev_107.root");
     t1.SetBranchAddress("nTrk", &nParticle);     
     t1.SetBranchAddress("phi", &hadronphi);
     t1.SetBranchAddress("pt", &hadronpt);
     t1.SetBranchAddress("eta", &hadroneta);



     double w_i = 1., w_j= 1., w_k = 1.;
     double weight_sum;  
     double weight_sum_3SUB;  
     double weight_sum_3SUB_A, weight_sum_3SUB_C;
     double PT_sum, PT_nParticle;
     double PT_sum_3SUB, PT_nParticle_3SUB;
     double PT_sum_LOOP, PT_nParticle_LOOP;
     double tmp_meanPT;
     double tmp_meanPT_3SUB, tmp_meanPT_LOOP, tmp_meanPT_LOOPCUT;
     double min_PT = 0.3, max_PT = 2., min_PT_Nch = 0.5, max_PT_Nch = 5.;
     double ETAGAP = 0.8;
     int subevent_A_count, subevent_C_count, loopcount;

     //nEvt=120;
     //nEvt=1000000;
     nEvt = t1.GetEntries();
     

     for(long ne=0; ne<nEvt; ne++)
     {
        if(ne%50000==0)  cout<<"First Loop. Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;

       t1.GetEntry(ne);

       Int_t nParticle_cut = 0;
       for(int i=0;i<nParticle;i++){
         if(hadronpt[i] < min_PT_Nch || hadronpt[i] > max_PT_Nch) continue;
         nParticle_cut++;
       }

       //if(nParticle_cut>330) continue; 
       //if(nParticle_cut<3) continue; 

       for(int imult=0;imult<NB_SLICE_B;imult++){
          if((nParticle_cut>=minbCut[imult]&&nParticle_cut<maxbCut[imult])){
              multBin=imult;
          }
       }

//need this line-tuo:
//       if(nParticle_cut==0) multBin=0;

//cout<<"multBin = "<<multBin<<" nParticle_cut = "<<nParticle_cut<<endl;
       PT_sum_3SUB=0;
       PT_nParticle_3SUB = 0;
       PT_sum_LOOP=0;
       PT_nParticle_LOOP = 0;
       subevent_A_count=0;
       subevent_C_count=0;

       for(iParticle=0; iParticle<nParticle; iParticle++){
          if(hadronpt[iParticle] < min_PT || hadronpt[iParticle] > max_PT) continue;
          //PT_sum_LOOP += hadronpt[iParticle];
          //PT_nParticle_LOOP += 1.;          

          //if(hadroneta[iParticle]<-0.75) subevent_A_count++;
          //if(hadroneta[iParticle]>0.75)  subevent_C_count++;
          if(hadroneta[iParticle]<-0.5 || hadroneta[iParticle]>0.5) continue;     
          PT_sum_3SUB += hadronpt[iParticle];
          PT_nParticle_3SUB += 1.;

       }
      //cout<<"Nch: "<<nParticle_cut<<"   sumPT: "<<PT_sum_3SUB<<"   nB: "<<PT_nParticle_3SUB<<endl; 
/*
      loopcount = 0;

      for(int i=0; i<nParticle; i++){
        if(hadronpt[i] < min_PT || hadronpt[i] > max_PT) continue;

        for(int k=0; k<nParticle; k++){
          if(hadronpt[k] < min_PT || hadronpt[k] > max_PT) continue;
          if( abs(hadroneta[i]-hadroneta[k])<ETAGAP ) continue;

          for(int j=0; j<nParticle; j++){
            if(hadronpt[j] < min_PT || hadronpt[j] > max_PT) continue;
            if( abs(hadroneta[i]-hadroneta[j])<ETAGAP ) continue;
            if( abs(hadroneta[k]-hadroneta[j])<ETAGAP ) continue;

            loopcount++;
          }
        }
      }

       if(loopcount>0){
         histMeanPT_LOOP[multBin]->Fill(PT_sum_LOOP/PT_nParticle_LOOP);
       }
*/

//       if(nParticle_cut>20&&nParticle_cut<31) cout<<"multBin="<<multBin<<" MeanPTsum "<<PT_sum_3SUB<<"  Bnrtk: "<<PT_nParticle_3SUB<<endl;
       //if(PT_nParticle_3SUB>0.1 && subevent_A_count>0 && subevent_C_count>0){
       if(PT_nParticle_3SUB>0.1){
         histMeanPT_3SUB[multBin]->Fill(PT_sum_3SUB/PT_nParticle_3SUB);
         //if(loopcount>0) histMeanPT_LOOPCUT[multBin]->Fill(PT_sum_LOOP/PT_nParticle_LOOP);
       }

     }

     for(int i=0; i<NB_SLICE_B; i++){
       cout<<i<<"  "<<histMeanPT_3SUB[i]->GetEntries()<<"  "<<histMeanPT_3SUB[i]->GetMean()<<endl;
     }


     Float_t qxa, qya, qxc, qyc, weight_a, weight_c;

     // starting the second event loop
     for(long ne=0; ne<nEvt; ne++)
     {
       if(ne%50000==0)  cout<<"Second Loop. Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       //cout<<"Second Loop. Have run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
       t1.GetEntry(ne);
       qxa=0;qya=0;qxc=0;qyc=0;weight_a=0;weight_c=0;

      
       Int_t nParticle_cut = 0;
       for(int i=0;i<nParticle;i++){
        if(hadronpt[i] < min_PT_Nch || hadronpt[i] > max_PT_Nch) continue; 
         nParticle_cut++;
       }
 

       if(nParticle_cut>330) continue;
       //if(nParticle_cut<3) continue; 

       for(int imult=0;imult<NB_SLICE_B;imult++){
          if((nParticle_cut>=minbCut[imult]&&nParticle_cut<maxbCut[imult])){
              multBin=imult;
          }
       }

//need this line-tuo:
//       if(nParticle_cut==0) multBin=0;

      //histMult[multBin]->Fill(nPartonzpc);
      // remeber that in this macro, the variables labeled with multiplicity actually represent b (centrality)
      //histMult[multBin]->Fill(nParticle);

/*
      PT_sum=0;
      PT_nParticle = 0;

       for(iParticle=0; iParticle<nParticle; iParticle++){
         if(hadronpt[iParticle] < min_PT || hadronpt[iParticle] > max_PT) continue;
         PT_sum += hadronpt[iParticle];
         //if(hadroneta[iParticle]<-0.5 || hadroneta[iParticle]>0.5) continue;
         PT_nParticle += 1.;
       }
*/

       PT_sum_3SUB=0;
       PT_nParticle_3SUB = 0;
       PT_sum_LOOP=0;
       PT_nParticle_LOOP = 0;


       for(iParticle=0; iParticle<nParticle; iParticle++){
          if(hadronpt[iParticle] < min_PT || hadronpt[iParticle] > max_PT) continue;
          //PT_sum_LOOP += hadronpt[iParticle];
          //PT_nParticle_LOOP += 1.;

          if(hadroneta[iParticle]<-0.5 || hadroneta[iParticle]>0.5) continue;
          PT_sum_3SUB += hadronpt[iParticle];
          PT_nParticle_3SUB += 1.;

       }



      TComplex CovV2PT_sum_LOOP=0;
      TComplex CovV2PT_sum_LOOPCUT=0;
      weight_sum = 0;
      //tmp_meanPT_LOOP = histMeanPT_LOOP[multBin]->GetMean();
      tmp_meanPT_3SUB = histMeanPT_3SUB[multBin]->GetMean();
      //tmp_meanPT_LOOPCUT = histMeanPT_LOOPCUT[multBin]->GetMean();
      //float tmp_sum = 0;
/*
      for(int i=0; i<nParticle; i++){
        if(hadronpt[i] < min_PT || hadronpt[i] > max_PT) continue;

        for(int k=0; k<nParticle; k++){
          if(hadronpt[k] < min_PT || hadronpt[k] > max_PT) continue;
          if( abs(hadroneta[i]-hadroneta[k])<ETAGAP ) continue;

          for(int j=0; j<nParticle; j++){
            if(hadronpt[j] < min_PT || hadronpt[j] > max_PT) continue;
            if( abs(hadroneta[i]-hadroneta[j])<ETAGAP ) continue;
            if( abs(hadroneta[k]-hadroneta[j])<ETAGAP ) continue;

            CovV2PT_sum_LOOP += ( ( TComplex::Exp(TComplex(0,2*(hadronphi[i]-hadronphi[j]))) ) ).Re() * (hadronpt[k]-tmp_meanPT_LOOP);
            CovV2PT_sum_LOOPCUT += ( ( TComplex::Exp(TComplex(0,2*(hadronphi[i]-hadronphi[j]))) ) ).Re() * (hadronpt[k]-tmp_meanPT_LOOPCUT);
            //CovV2PT_sum += ( w_i*w_k*w_j*( TComplex::Exp(TComplex(0,2*(hadronphi[i]-hadronphi[j]))) ) ).Re() * (hadronpt[k]-tmp_meanPT_LOOP);
            //tmp_sum += ( w_i*w_k*( TComplex::Exp(TComplex(0,2*(hadronphi[i]-hadronphi[j]))) ) ).Re();
            //CovV2PT_sum += ( w_i*w_k*( TComplex::Exp(TComplex(0,2*(hadronphi[i]-hadronphi[j]))) ) ).Re();
            weight_sum += 1.; 
            //weight_sum += w_i*w_k*w_j; 


          }
        }

      }
      //if(weight_sum<0.1) cout<<"npairs:  "<<weight_sum<<"nparticlecut:  "<<nParticle_cut<<endl;
      double temp_COV_LOOP = (CovV2PT_sum_LOOP) / weight_sum;
      double temp_COV_LOOPCUT = (CovV2PT_sum_LOOPCUT) / weight_sum;
      if(weight_sum>0.1){
        histCovV2PT_LOOP[multBin]->Fill(temp_COV_LOOP); 
        histMult_LOOP[multBin]->Fill(nParticle_cut);
      }

*/
      TComplex CovV2PT_sum_3SUB_A=0; 
      TComplex CovV2PT_sum_3SUB_C=0; 
      weight_sum_3SUB_A = 0;
      weight_sum_3SUB_C = 0;
      Float_t Px2_AC = 0, Pw_AC = 0;
/*
      for(int i=0; i<nParticle; i++){
        if(hadronpt[i] < min_PT || hadronpt[i] > max_PT) continue;
        if(hadroneta[i]<-0.75){
          CovV2PT_sum_3SUB_A += TComplex::Exp(TComplex(0,2*hadronphi[i] ));
          weight_sum_3SUB_A += 1.;
          qxa += cos(2*hadronphi[i]);
          qya += sin(2*hadronphi[i]);
          weight_a += 1.;

        } else if(hadroneta[i]>0.75){
          CovV2PT_sum_3SUB_C += TComplex::Exp(TComplex(0,-2*hadronphi[i] ));
          weight_sum_3SUB_C += 1.;
          qxc += cos(2*hadronphi[i]);
          qyc += sin(2*hadronphi[i]);
          weight_c += 1.;
        }
      }*/
      for(int i=0; i<nParticle; i++){
        if(hadronpt[i] < min_PT || hadronpt[i] > max_PT) continue;
        if(hadroneta[i]<-0.75&&PT_nParticle_3SUB>0){
          for(int j=0; j<nParticle; j++){
            if(hadroneta[j]>0.75){
              if(hadronpt[j] < min_PT || hadronpt[j] > max_PT) continue;
              //Px2_AC += cos(2*(hadronphi[i]-hadronphi[j]));
              //Px2_AC += (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB);
              //Px2_AC += (PT_sum_3SUB/PT_nParticle_3SUB - 0);
              Px2_AC += cos(2*(hadronphi[i]-hadronphi[j])) * (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB);
              Pw_AC+=1.;
            }
          }
        }
      }

      //double tmp_COV3SUB = ( (CovV2PT_sum_3SUB_A*CovV2PT_sum_3SUB_C).Re() * (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB) ) / (weight_sum_3SUB_A*weight_sum_3SUB_C);
      //cout<<"TEST: "<<(CovV2PT_sum_3SUB* (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB) ) / weight_sum_3SUB - (tmp_COV3SUB)<<endl;
      //if(weight_sum_3SUB_A>0.1 && weight_sum_3SUB_C>0.1 && PT_nParticle_3SUB>0.1){
      if(Pw_AC>0 && PT_nParticle_3SUB>0){
      //if(Pw_AC>0){
         //Float_t tmp_3sub1 =  ((CovV2PT_sum_3SUB_A*CovV2PT_sum_3SUB_C).Re() * (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB) ) / (weight_sum_3SUB_A*weight_sum_3SUB_C);
      //cout<<"numerator: "<<Px2_AC<<"   denominator: "<<Pw_AC<<"  meanPT: "<<PT_sum_3SUB/PT_nParticle_3SUB<<endl;
         //Float_t tmp_3sub2 = (qxa*qxc + qya*qyc)/(weight_a*weight_c) * ((PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB));
         //cout<<"DIFF: "<<tmp_3sub1-tmp_3sub2<<endl;
         //histCovV2PT_3SUB[multBin]->Fill( ((CovV2PT_sum_3SUB_A*CovV2PT_sum_3SUB_C).Re() * (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB) ) / (weight_sum_3SUB_A*weight_sum_3SUB_C) ); 
         //histCovV2PT_3SUB[multBin]->Fill( ((CovV2PT_sum_3SUB_A*CovV2PT_sum_3SUB_C).Re() * pow((PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB),2) ) / (weight_sum_3SUB_A*weight_sum_3SUB_C) ); 
         //cout<<"numerator: "<<Px2_AC<<"   denominator: "<<Pw_AC<<"  meanPT: "<<PT_sum_3SUB/PT_nParticle_3SUB<<endl;
         //histCovV2PT_3SUB[multBin]->Fill(  Px2_AC/Pw_AC * (PT_sum_3SUB/PT_nParticle_3SUB - tmp_meanPT_3SUB) ); 
         histCovV2PT_3SUB[multBin]->Fill(  Px2_AC/Pw_AC ); 
         histMult_3SUB[multBin]->Fill(nParticle_cut);
        /* if(weight_sum>0.1){
           histCovV2PT_LOOPCUT[multBin]->Fill(temp_COV_LOOPCUT);
           histMult_LOOPCUT[multBin]->Fill(nParticle_cut);
         }*/
      }

      //cout<< (CovV2PT_sum) / weight_sum<<"   "<<(tmp_sum* (PT_sum/PT_nParticle - tmp_meanPT)) / weight_sum<<"   "<<((CovV2PT_sum) / weight_sum)-((tmp_sum* (PT_sum/PT_nParticle - tmp_meanPT)) / weight_sum)<<endl;
     //histCovV2PT[multBin]->Fill( (CovV2PT_sum* (PT_sum/PT_nParticle - tmp_meanPT)) / weight_sum); 
       //cout<<"Px2_AC="<<Px2_AC<<"  Pw_AC="<<Pw_AC<<"  PT_sum_3SUB/PT_nParticle_3SUB="<<PT_sum_3SUB/PT_nParticle_3SUB<<"   tmp_meanPT_3SUB="<<tmp_meanPT_3SUB<<endl;
       if(Pw_AC>0&&nParticle_cut<10&&PT_nParticle_3SUB>0){
//         cout<<ne<<"  nParticle_cut"<<nParticle_cut<<"  Px2_AC="<<Px2_AC<<"  Pw_AC="<<Pw_AC<<"  Px2_AC/Pw_AC="<<Px2_AC/Pw_AC<<endl;
tmpXXX+=Px2_AC/Pw_AC;
       }
      } // end of the second event loop
cout<<"tmpXXX="<<tmpXXX<<endl;
cout<<"tmpXXX="<<tmpXXX/histCovV2PT_3SUB[0]->GetEntries()<<endl;
cout<<"histCovV2PT_3SUB_mean = "<<histCovV2PT_3SUB[0]->GetMean()<<" entries="<<histCovV2PT_3SUB[0]->GetEntries()<<"  sum="<<histCovV2PT_3SUB[0]->GetMean()*histCovV2PT_3SUB[0]->GetEntries()<<endl;

     TFile *f = new TFile("output_covV2PT_vs_Nch_3sub_pp_PT2to2.root","recreate");
     //TFile *f = new TFile("output_covV2PT_vs_Nch_looping_pp_PT2to2.root","recreate");
     f->cd();
     for(int i=0; i<NB_SLICE_B; i++){
       //histCovV2PT_LOOP[i]->Write();
     }
     for(int i=0; i<NB_SLICE_B; i++){
       histCovV2PT_3SUB[i]->Write();
       cout<<histMult_3SUB[i]->GetMean()<<"   "<<histMeanPT_3SUB[i]->GetMean()<<endl;
     }
     for(int i=0; i<NB_SLICE_B; i++){
       //histCovV2PT_LOOPCUT[i]->Write();
     }
     for(int i=0; i<NB_SLICE_B; i++){
       //histMult_LOOP[i]->Write();
     }
     for(int i=0; i<NB_SLICE_B; i++){
       histMult_3SUB[i]->Write();
     }
     for(int i=0; i<NB_SLICE_B; i++){
       //histMult_LOOPCUT[i]->Write();
     }

     f->Write();
     f->Close();

     //ofstream output1;
     //output1.open("output_covV2PT_vs_Nch_looping_pp_PT2to2_0to330.txt");

     for(int i=0; i<NB_SLICE_B; i++){

         //output1<<histMult_LOOP[i]->GetEntries()<<"   "<<histMult_3SUB[i]->GetEntries()<<"   "<<histMult_LOOP[i]->GetMean()<<"   "<<histMult_3SUB[i]->GetMean()<<"   "<<(minbCut[i]+maxbCut[i])/2<<"   "<<histCovV2PT_LOOP[i]->GetMean()<<"   "<<histCovV2PT_LOOP[i]->GetMeanError()<<"   "<<histCovV2PT_3SUB[i]->GetMean()<<"   "<<histCovV2PT_3SUB[i]->GetMeanError()<<"   "<<histCovV2PT_LOOPCUT[i]->GetMean()<<"   "<<histCovV2PT_LOOPCUT[i]->GetMeanError()<<endl;
         //cout<<histMult_LOOP[i]->GetEntries()<<"   "<<histMult_3SUB[i]->GetEntries()<<"   "<<histMult_LOOPCUT[i]->GetEntries()<<"   "<<histMult_LOOP[i]->GetMean()<<"   "<<histMult_3SUB[i]->GetMean()<<"   "<<(minbCut[i]+maxbCut[i])/2<<"   "<<histCovV2PT_LOOP[i]->GetMean()<<"   "<<histCovV2PT_LOOP[i]->GetMeanError()<<"   "<<histCovV2PT_3SUB[i]->GetMean()<<"   "<<histCovV2PT_3SUB[i]->GetMeanError()<<"   "<<histCovV2PT_LOOPCUT[i]->GetMean()<<"   "<<histCovV2PT_LOOPCUT[i]->GetMeanError()<<endl;
         cout<<histMult_3SUB[i]->GetEntries()<<"   "<<histMult_3SUB[i]->GetMean()<<"   "<<(minbCut[i]+maxbCut[i])/2<<"   "<<histCovV2PT_3SUB[i]->GetMean()<<"   "<<histCovV2PT_3SUB[i]->GetMeanError()<<endl;
     }



}
