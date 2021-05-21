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
void hist_to_txt(){

     int nbins = 330;
     //TH1D *histCovV2PT_LOOP_0[nbins];
     //TH1D *histCovV2PT_LOOP_0 = new TH1D("histCovV2PT_LOOP_0", "", 200,-1,1);

     //TFile inFile("./output_cov_vs_Nch_pp_50M_PT3to3.root", "read");
     //TFile inFile("./../output_covV2PT_vs_Nch_3sub_pp_PT2to2_1B.root", "read");
     TFile inFile("../output_covV2PT_vs_Nch_3sub_pp_PT2to2.root", "read");
     //TFile inFile("./output_cov_vs_Nch.root", "read");

     //TH1D *histCovV2PT_LOOP[nbins];


     ofstream output1;
     //output1.open("output_covV2PT_vs_Nch_looping_pp_50M.txt");
     output1.open("output_covV2PT_vs_Nch_3sub_pp_PT3to2_NEWAC.txt");

    
     for(int i=0; i<nbins; i++){
       //TH1D *histCovV2PT_LOOP[i] = (TH1D*)inFile.Get(Form("histCovV2PT_LOOP_%d",i)); 
       //TH1D *cov_LOOP = (TH1D*)inFile.Get(Form("histCovV2PT_LOOP_%d",i));
       //TH1D *mult_LOOP = (TH1D*)inFile.Get(Form("histMult_LOOP_%d",i));
       TH1D *cov_3SUB = (TH1D*)inFile.Get(Form("histCovV2PT_3SUB_%d",i));
       //TH1D *cov_LOOPCUT = (TH1D*)inFile.Get(Form("histCovV2PT_LOOPCUT_%d",i));
       TH1D *mult_3SUB = (TH1D*)inFile.Get(Form("histMult_3SUB_%d",i));
       //TH1D *mult_LOOPCUT = (TH1D*)inFile.Get(Form("histMult_LOOPCUT_%d",i));
       cout<<mult_3SUB->GetEntries()<<"   "<<mult_3SUB->GetMean()<<"   "<<cov_3SUB->GetMean()<<"   "<<cov_3SUB->GetMeanError()<<endl; 
       output1<<mult_3SUB->GetEntries()<<"   "<<mult_3SUB->GetMean()<<"   "<<cov_3SUB->GetMean()<<"   "<<cov_3SUB->GetMeanError()<<endl; 
       //cout<<mult_LOOP->GetEntries()<<"   "<<mult_LOOP->GetMean()<<"   "<<mult_3SUB->GetEntries()<<"   "<<mult_3SUB->GetMean()<<"   "<<mult_LOOPCUT->GetEntries()<<"   "<<mult_LOOPCUT->GetMean()<<"   "<<cov_LOOP->GetMean()<<"   "<<cov_LOOP->GetMeanError()<<"   "<<cov_3SUB->GetMean()<<"   "<<cov_3SUB->GetMeanError()<<"   "<<cov_LOOPCUT->GetMean()<<"   "<<cov_LOOPCUT->GetMeanError()<<endl; 
       //output1<<mult_LOOP->GetEntries()<<"   "<<mult_LOOP->GetMean()<<"   "<<mult_3SUB->GetEntries()<<"   "<<mult_3SUB->GetMean()<<"   "<<mult_LOOPCUT->GetEntries()<<"   "<<mult_LOOPCUT->GetMean()<<"   "<<cov_LOOP->GetMean()<<"   "<<cov_LOOP->GetMeanError()<<"   "<<cov_3SUB->GetMean()<<"   "<<cov_3SUB->GetMeanError()<<"   "<<cov_LOOPCUT->GetMean()<<"   "<<cov_LOOPCUT->GetMeanError()<<endl; 
     }


     //TFile inFile("./output_cov_vs_Nch_pp_50M.root", "read");
     //TH1D *test = (TH1D*)inFile.Get("histCovV2PT_LOOP_0");
     //TTree *t1 = (TTree*)inFile.Get("hadronTree");
     //t1->SetBranchAddress("histCovV2PT_LOOP_0", &histCovV2PT_LOOP_0);
     
     //cout<<"TEST   "<<test->GetMean()<<endl;


}
