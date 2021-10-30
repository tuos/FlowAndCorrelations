// Run this macro second. It computes the c24 and k24 using the three and four subevent methods. It stores is results in histograms in an output root file which can then be converted into text files to be plotted. 
#include <iostream>
#include <fstream>
#include <vector>

#include <TFile.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TTree.h>
#include <TProfile.h>
#include <TComplex.h>

using namespace std;

void c2_4_correlator(){

     const int num_bins = 20;
     int minNchCut[num_bins] = {0,5,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150, 180, 220};
     int maxNchCut[num_bins] = {5,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150, 180, 220, 10000};


    ifstream flist;
    flist.open("/scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src/treeInput/oct22/c24/slurmstep2/files/listFiles_jb0.txt");

    char ifile[300];

    long nEvt;
    const float pt_min = 0.5;
    const float pt_max = 5.;
    const float pt_Nch_min = 0.5;
    const float pt_Nch_max = 5.;


    Float_t pt[2000], eta[2000], phi[2000];
    Int_t nParticle, Nch;
    int multBin = -1;

    const bool one_sub_trigger = false;
    const bool two_sub_trigger = false;
    const bool three_sub_trigger = true;
    const bool four_sub_trigger = false;

    Float_t ptsum, Mpt, meanpt, Mck;
    Float_t cksum_1,  cksum_2, cksum_3, cksum_4; 
    TComplex e_2iphi, e_4iphi;

    Float_t MeanPT_3[num_bins];
    Float_t MeanPT_4[num_bins];
    TFile inFile("/scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src/treeInput/oct22/c24/slurm/outputROOT_covariance_2pc_and_meanpt_mergedAll.root", "read");
    for(int i=0; i<num_bins; i++){
       TH1D *histMeanPT_3 = (TH1D*)inFile.Get(Form("histMeanPT_3_%d",i));
       MeanPT_3[i] = histMeanPT_3->GetMean();
       TH1D *histMeanPT_4 = (TH1D*)inFile.Get(Form("histMeanPT_3_%d",i)); //4->3
       MeanPT_4[i] = histMeanPT_4->GetMean();
    }

    Float_t Cov_2ab_2ac_3[num_bins];
    Float_t cCov_2ab_2ac_3[num_bins];
    Float_t cCov_2de_2df_3[num_bins];
    Float_t Cov_2ac_2bd_4[num_bins];
    Float_t Cov_2ad_2bc_4[num_bins];
    Float_t cCov_2ac_2bd_4[num_bins];
    Float_t cCov_2ad_2bc_4[num_bins];
    Float_t cCov_2eg_2fh_4[num_bins];
    Float_t cCov_2eh_2fg_4[num_bins];
    for(int i=0; i<num_bins; i++){
       TH2D *histCorr_2ab_2ac_3 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i));
       Cov_2ab_2ac_3[i] = histCorr_2ab_2ac_3->GetCovariance();
       TH2D *histCorr_2ac_2bd_4 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i)); //histCorr_2ac_2bd_4_
       Cov_2ac_2bd_4[i] = histCorr_2ac_2bd_4->GetCovariance();
       TH2D *histCorr_2ad_2bc_4 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i)); //
       Cov_2ad_2bc_4[i] = histCorr_2ad_2bc_4->GetCovariance();
       TH2D *histcCorr_2ab_2ac_3 = (TH2D*)inFile.Get(Form("histcCorr_2ab_2ac_3_%d",i));
       cCov_2ab_2ac_3[i] = histcCorr_2ab_2ac_3->GetCovariance();
       TH2D *histcCorr_2de_2df_3 = (TH2D*)inFile.Get(Form("histcCorr_2de_2df_3_%d",i));
       cCov_2de_2df_3[i] = histcCorr_2de_2df_3->GetCovariance();
       TH2D *histcCorr_2ac_2bd_4 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i)); //
       cCov_2ac_2bd_4[i] = histcCorr_2ac_2bd_4->GetCovariance();
       TH2D *histcCorr_2ad_2bc_4 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i)); //
       cCov_2ad_2bc_4[i] = histcCorr_2ad_2bc_4->GetCovariance();
       TH2D *histcCorr_2eg_2fh_4 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i)); //
       cCov_2eg_2fh_4[i] = histcCorr_2eg_2fh_4->GetCovariance();
       TH2D *histcCorr_2eh_2fg_4 = (TH2D*)inFile.Get(Form("histCorr_2ab_2ac_3_%d",i)); //
       cCov_2eh_2fg_4[i] = histcCorr_2eh_2fg_4->GetCovariance();

    }

    //if(one_sub_trigger){
      TComplex Q2a_1, Q4a_1;
      Float_t Ma_1, c2_4_1sub, corr_4aaaa_1, corr_2aa_1;

      TH1D *histXY_1[num_bins];
      TH1D *histX_1[num_bins];
      TH1D *histY_1[num_bins];
      TH1D *histNch_1[num_bins];
      TH1D *histCK_1[num_bins];
      for(int i=0; i<num_bins; i++){
         histNch_1[i] = new TH1D(Form("histNch_1_%d",i), "", 2000,0,2000);
         histXY_1[i] = new TH1D(Form("histXY_1_%d",i), "", 330,-11,11);
         histX_1[i] = new TH1D(Form("histX_1_%d",i), "", 330,-11,11);
         histY_1[i] = new TH1D(Form("histY_1_%d",i), "", 330,-11,11);
         histCK_1[i] = new TH1D(Form("histCK_1_%d",i), "", 330,-11,11);
      }
     ///}

    //if(two_sub_trigger){
      TComplex Q2a_2, Q4a_2, Q2b_2, Q4b_2;
      Float_t Ma_2, Mb_2, c2_4_2sub, corr_4aabb_2, corr_2ab_2;

      TH1D *histXY_2[num_bins];
      TH1D *histX_2[num_bins];
      TH1D *histY_2[num_bins];
      TH1D *histNch_2[num_bins];
      TH1D *histCK_2[num_bins];
      for(int i=0; i<num_bins; i++){
         histNch_2[i] = new TH1D(Form("histNch_2_%d",i), "", 2000,0,2000);
         histXY_2[i] = new TH1D(Form("histXY_2_%d",i), "", 330,-11,11);
         histX_2[i] = new TH1D(Form("histX_2_%d",i), "", 330,-11,11);
         histY_2[i] = new TH1D(Form("histY_2_%d",i), "", 330,-11,11);
         histCK_2[i] = new TH1D(Form("histCK_2_%d",i), "", 330,-11,11); 
      }
    //}

    //if(three_sub_trigger){
      TComplex Q2a_3, Q4a_3, Q6a_3, Q8a_3, Q2b_3, Q4b_3, Q2c_3, Q4c_3;
      TComplex vQ2a_3, vQ4a_3, vQ6a_3, vQ8a_3, vQ2b_3, vQ4b_3, vQ2c_3, vQ4c_3;
      TComplex vQ2d_3, vQ4d_3, vQ6d_3, vQ8d_3, vQ2e_3, vQ4e_3, vQ2f_3, vQ4f_3;
      Float_t Ma_3, Mb_3, Mc_3;
      Float_t vMa_3, vMb_3, vMc_3, vMd_3, vMe_3, vMf_3;
      Float_t c2_4_3sub, k2_4_3sub, corr_4aabc_3, corr_2ab_3, corr_2ac_3, corr_8aaaabbcc_3;
      Float_t vcorr_4aabc_3, vcorr_2ab_3, vcorr_2ac_3, vcorr_4ddef_3, vcorr_2de_3, vcorr_2df_3;
      Float_t c2_4abc_3sub, k2_4abc_3sub, c2_4def_3sub, k2_4def_3sub;

      TH1D *histXY_3[num_bins];
      TH1D *histX_3[num_bins];
      TH1D *histY_3[num_bins];
      TH1D *histNch_3[num_bins];
      TH1D *histCK_3[num_bins];
      TH1D *khistXY_3[num_bins];
      TH1D *khistX_3[num_bins];
      TH1D *histc24abcdef_3[num_bins];
      TH1D *histc24abc_3[num_bins];
      TH1D *histc24def_3[num_bins];
      TH1D *khistc24abcdef_3[num_bins];
      TH1D *khistc24abc_3[num_bins];
      TH1D *khistc24def_3[num_bins];
      for(int i=0; i<num_bins; i++){
         histNch_3[i] = new TH1D(Form("histNch_3_%d",i), "", 2000,0,2000);
         histXY_3[i] = new TH1D(Form("histXY_3_%d",i), "", 330,-11,11);
         histX_3[i] = new TH1D(Form("histX_3_%d",i), "", 330,-11,11);
         histY_3[i] = new TH1D(Form("histY_3_%d",i), "", 330,-11,11);
         histCK_3[i] = new TH1D(Form("histCK_3_%d",i), "", 330,-11,11);
         khistXY_3[i] = new TH1D(Form("khistXY_3_%d",i), "", 330,-11,11);
         khistX_3[i] = new TH1D(Form("khistX_3_%d",i), "", 330,-11,11);
         histc24abcdef_3[i] = new TH1D(Form("histc24abcdef_3_%d",i), "", 330,-11,11);
         histc24abc_3[i] = new TH1D(Form("histc24abc_3_%d",i), "", 330,-11,11);
         histc24def_3[i] = new TH1D(Form("histc24def_3_%d",i), "", 330,-11,11);
         khistc24abcdef_3[i] = new TH1D(Form("khistc24abcdef_3_%d",i), "", 330,-11,11);
         khistc24abc_3[i] = new TH1D(Form("khistc24abc_3_%d",i), "", 330,-11,11);
         khistc24def_3[i] = new TH1D(Form("khistc24def_3_%d",i), "", 330,-11,11);
      }

      TH1D *histXY_3tmp[num_bins];
      TH1D *histX_3tmp[num_bins];
      for(int i=0; i<num_bins; i++){
         histXY_3tmp[i] = new TH1D(Form("histXY_3tmp_%d",i), "", 330,-11,11);
         histX_3tmp[i] = new TH1D(Form("histX_3tmp_%d",i), "", 330,-11,11);
      }

    //}

    //if(three_sub_trigger){
      TComplex Q2a_4, Q4a_4, Q2b_4, Q4b_4, Q2c_4, Q4c_4, Q2d_4, Q4d_4;
      TComplex vQ2a_4, vQ4a_4, vQ2b_4, vQ4b_4, vQ2c_4, vQ4c_4, vQ2d_4, vQ4d_4;
      TComplex vQ2e_4, vQ4e_4, vQ2f_4, vQ4f_4, vQ2g_4, vQ4g_4, vQ2h_4, vQ4h_4;
      Float_t Ma_4, Mb_4, Mc_4, Md_4; 
      Float_t vMa_4, vMb_4, vMc_4, vMd_4, vMe_4, vMf_4, vMg_4, vMh_4; 
      Float_t c2_4_4sub, k2_4_4sub, corr_4abcd_4, corr_2ad_4, corr_2bc_4, corr_2ac_4, corr_2bd_4, corr_8aabbccdd_4;
      Float_t vcorr_4abcd_4, vcorr_2ad_4, vcorr_2bc_4, vcorr_2ac_4, vcorr_2bd_4, vcorr_4efgh_4, vcorr_2eh_4, vcorr_2fg_4, vcorr_2eg_4, vcorr_2fh_4;
      Float_t c2_4abcd_4sub, k2_4abcd_4sub, c2_4efgh_4sub, k2_4efgh_4sub;


      TH1D *histXY_4[num_bins];
      TH1D *histX_4[num_bins];
      TH1D *histY_4[num_bins];
      TH1D *histNch_4[num_bins];
      TH1D *histCK_4[num_bins];
      TH1D *khistXY_4[num_bins];
      TH1D *khistX_4[num_bins];
      TH1D *histc24abcdefgh_4[num_bins];
      TH1D *histc24abcd_4[num_bins];
      TH1D *histc24efgh_4[num_bins];
      TH1D *khistc24abcdefgh_4[num_bins];
      TH1D *khistc24abcd_4[num_bins];
      TH1D *khistc24efgh_4[num_bins];
      for(int i=0; i<num_bins; i++){
         histNch_4[i] = new TH1D(Form("histNch_4_%d",i), "", 2000,0,2000);
         histXY_4[i] = new TH1D(Form("histXY_4_%d",i), "", 330,-11,11);
         histX_4[i] = new TH1D(Form("histX_4_%d",i), "", 330,-11,11);
         histY_4[i] = new TH1D(Form("histY_4_%d",i), "", 330,-11,11);
         histCK_4[i] = new TH1D(Form("histCK_4_%d",i), "", 330,-11,11);
         khistXY_4[i] = new TH1D(Form("khistXY_4_%d",i), "", 330,-11,11);
         khistX_4[i] = new TH1D(Form("khistX_4_%d",i), "", 330,-11,11);
         histc24abcdefgh_4[i] = new TH1D(Form("histc24abcdefgh_4_%d",i), "", 330,-11,11);
         histc24abcd_4[i] = new TH1D(Form("histc24abcd_4_%d",i), "", 330,-11,11);
         histc24efgh_4[i] = new TH1D(Form("histc24efgh_4_%d",i), "", 330,-11,11);
         khistc24abcdefgh_4[i] = new TH1D(Form("khistc24abcdefgh_4_%d",i), "", 330,-11,11);
         khistc24abcd_4[i] = new TH1D(Form("khistc24abcd_4_%d",i), "", 330,-11,11);
         khistc24efgh_4[i] = new TH1D(Form("khistc24efgh_4_%d",i), "", 330,-11,11);
      }
      TH1D *histXY_4tmp[num_bins];
      TH1D *histX_4tmp[num_bins];
      for(int i=0; i<num_bins; i++){
         histXY_4tmp[i] = new TH1D(Form("histXY_4tmp_%d",i), "", 330,-11,11);
         histX_4tmp[i] = new TH1D(Form("histX_4tmp_%d",i), "", 330,-11,11);
      }
    //}



    while( flist >> ifile ){
        
	cout << "OPEN: " << ifile << endl;

	TFile *infile = new TFile(ifile,"read");

        TTree *t1 = (TTree*)infile->Get("demo/trackTree");
        t1->SetBranchAddress("nTrk", &nParticle);
        t1->SetBranchAddress("trackPhi", &phi);
        t1->SetBranchAddress("trackPt", &pt);
        t1->SetBranchAddress("trackEta", &eta);
        

        nEvt = t1->GetEntries();
        //nEvt = 1000;
        
	for(int ne=0; ne<nEvt; ne++){
	    t1->GetEntry(ne);
            if(ne%100000==0)  cout<<"Run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;

            // find Nch
            Nch = 0;
	    for(int i=0; i<nParticle; i++){
		if(pt[i]>pt_Nch_min && pt[i]<pt_Nch_max){
                    if(fabs(eta[i])<2.4){    
                     Nch++; 
                    }
                }
            }
	    if(Nch>10000) continue;


            for(int imult=0;imult<num_bins;imult++){
              if((Nch>minNchCut[imult]&&Nch<=maxNchCut[imult])){
                multBin=imult;
              }
            }
            if(Nch==0) multBin=0;

            ptsum=0; Mpt=0; cksum_1=0; cksum_2=0; cksum_3=0; cksum_4=0; Mck=0;
            if(one_sub_trigger){Q2a_1=0; Q4a_1=0; Ma_1=0;}
            if(two_sub_trigger){Q2a_2=0; Q4a_2=0; Q2b_2=0; Q4b_2=0; Ma_2=0; Mb_2=0;}
            if(three_sub_trigger){Q2a_3=0; Q4a_3=0; Q6a_3=0; Q8a_3=0; Q2b_3=0; Q4b_3=0; Q2c_3=0; Q4c_3=0; Ma_3=0; Mb_3=0; Mc_3=0;
                                  vQ2a_3=0; vQ4a_3=0; vQ2b_3=0; vQ4b_3=0; vQ2c_3=0; vQ4c_3=0; vMa_3=0; vMb_3=0; vMc_3=0;
                                  vQ2d_3=0; vQ4d_3=0; vQ2e_3=0; vQ4e_3=0; vQ2f_3=0; vQ4f_3=0; vMd_3=0; vMe_3=0; vMf_3=0;}
            if(four_sub_trigger){Q2a_4=0; Q4a_4=0; Q2b_4=0; Q4b_4=0; Q2c_4=0; Q4c_4=0; Q2d_4=0; Q4d_4=0; Ma_4=0; Mb_4=0; Mc_4=0; Md_4=0;
                                 vQ2a_4=0; vQ4a_4=0; vQ2b_4=0; vQ4b_4=0; vQ2c_4=0; vQ4c_4=0; vQ2d_4=0; vQ4d_4=0; vMa_4=0; vMb_4=0; vMc_4=0; vMd_4=0;
                                 vQ2e_4=0; vQ4e_4=0; vQ2f_4=0; vQ4f_4=0; vQ2g_4=0; vQ4g_4=0; vQ2h_4=0; vQ4h_4=0; vMe_4=0; vMf_4=0; vMg_4=0; vMh_4=0;}
            //particle loop
            for(int ip=0; ip<nParticle; ip++){
		if(pt[ip]>pt_min && pt[ip]<pt_max){
                if(fabs(eta[ip])<2.4){
                if(eta[ip]>-0.5 && eta[ip]<0.5){
                    ptsum += pt[ip];
                    Mpt += 1.;
                    for(int jp=0; jp<nParticle; jp++){
                        if(pt[jp]>pt_min && pt[jp]<pt_max){
                         if(ip==jp) continue;
                         if(fabs(eta[jp])<2.4){
                          if(eta[jp]>-0.5 && eta[jp]<0.5){
                            //cksum_1 += (pt[ip]-MeanPT_1[multBin])*(pt[jp]-MeanPT_1[multBin]);
                            //cksum_2 += (pt[ip]-MeanPT_2[multBin])*(pt[jp]-MeanPT_2[multBin]);
                            cksum_3 += (pt[ip]-MeanPT_3[multBin])*(pt[jp]-MeanPT_3[multBin]);
                            cksum_4 += (pt[ip]-MeanPT_4[multBin])*(pt[jp]-MeanPT_4[multBin]);
                            Mck += 1.;
                          }
                         }
                        }
                    }
                    continue;
                }

                e_2iphi=TComplex::Exp(TComplex(0,2*phi[ip]));
                e_4iphi=TComplex::Exp(TComplex(0,4*phi[ip]));

                if(one_sub_trigger){
                  if(fabs(eta[ip])>0.75){
                    Q2a_1 += e_2iphi;
                    Q4a_1 += e_4iphi;
                    Ma_1+=1.;
                  }
                }

                if(two_sub_trigger){
		  if(eta[ip]<-0.75){
		    Q2a_2 += e_2iphi;
		    Q4a_2 += e_4iphi;
                    Ma_2+=1.;
		  } else if(eta[ip]>0.75){
                    Q2b_2 += e_2iphi;
                    Q4b_2 += e_4iphi;
                    Mb_2+=1.;
                  }
                }

                if(three_sub_trigger){
                  if(eta[ip]>-2.4 && eta[ip]<-1.85){
                    Q2b_3 += e_2iphi;
                    Q4b_3 += e_4iphi;
                    Mb_3+=1.;
                    vQ2b_3 += e_2iphi;
                    vQ4b_3 += e_4iphi;
                    vMb_3 += 1.;
                  } else if(eta[ip]>-1.85 && eta[ip]<-1.3){
                    Q2b_3 += e_2iphi;
                    Q4b_3 += e_4iphi;
                    Mb_3+=1.;
                    vQ2e_3 += e_2iphi;
                    vQ4e_3 += e_4iphi;
                    vMe_3 += 1.;
                  } else if(eta[ip]>-1.3 && eta[ip]<-0.75){
                    Q2a_3 += e_2iphi;
                    Q4a_3 += e_4iphi;
                    Ma_3+=1.;
                    vQ2a_3 += e_2iphi;
                    vQ4a_3 += e_4iphi;
                    vMa_3 += 1.;
                  } else if(eta[ip]>0.75 && eta[ip]<1.3){
                    Q2a_3 += e_2iphi;
                    Q4a_3 += e_4iphi;
                    Ma_3+=1.;
                    vQ2d_3 += e_2iphi;
                    vQ4d_3 += e_4iphi;
                    vMd_3 += 1.;
                  } else if(eta[ip]>1.3 && eta[ip]<1.85){
                    Q2c_3 += e_2iphi;
                    Q4c_3 += e_4iphi;
                    Mc_3+=1.;
                    vQ2c_3 += e_2iphi;
                    vQ4c_3 += e_4iphi;
                    vMc_3 += 1.;
                  } else if(eta[ip]>1.85 && eta[ip]<2.4){
                    Q2c_3 += e_2iphi;
                    Q4c_3 += e_4iphi;
                    Mc_3+=1.;
                    vQ2f_3 += e_2iphi;
                    vQ4f_3 += e_4iphi;
                    vMf_3 += 1.;
                  }
                }

                if(four_sub_trigger){
                  if(eta[ip]>-2.4 && eta[ip]<-1.9875){
                    Q2a_4 += e_2iphi;
                    Q4a_4 += e_4iphi;
                    Ma_4+=1.;
                    vQ2a_4 += e_2iphi;
                    vQ4a_4 += e_4iphi;
                    vMa_4 += 1.;
                  } else if(eta[ip]>-1.9875 && eta[ip]<-1.575){
                    Q2a_4 += e_2iphi;
                    Q4a_4 += e_4iphi;
                    Ma_4+=1.;
                    vQ2e_4 += e_2iphi;
                    vQ4e_4 += e_4iphi;
                    vMe_4 += 1.;
                  } else if(eta[ip]>-1.575 && eta[ip]<-1.1625){
                    Q2b_4 += e_2iphi;
                    Q4b_4 += e_4iphi;
                    Mb_4+=1.;
                    vQ2b_4 += e_2iphi;
                    vQ4b_4 += e_4iphi;
                    vMb_4 += 1.;
                  } else if(eta[ip]>-1.1625 && eta[ip]<-0.75){
                    Q2b_4 += e_2iphi;
                    Q4b_4 += e_4iphi;
                    Mb_4+=1.;
                    vQ2f_4 += e_2iphi;
                    vQ4f_4 += e_4iphi;
                    vMf_4 += 1.;
                  } else if(eta[ip]>0.75 && eta[ip]<1.1625){
                    Q2c_4 += e_2iphi;
                    Q4c_4 += e_4iphi;
                    Mc_4+=1.;
                    vQ2c_4 += e_2iphi;
                    vQ4c_4 += e_4iphi;
                    vMc_4 += 1.;
                  } else if(eta[ip]>1.1625 && eta[ip]<1.575){
                    Q2c_4 += e_2iphi;
                    Q4c_4 += e_4iphi;
                    Mc_4+=1.;
                    vQ2g_4 += e_2iphi;
                    vQ4g_4 += e_4iphi;
                    vMg_4 += 1.;
                  } else if(eta[ip]>1.575 && eta[ip]<1.9875){
                    Q2d_4 += e_2iphi;
                    Q4d_4 += e_4iphi;
                    Md_4+=1.;
                    vQ2d_4 += e_2iphi;
                    vQ4d_4 += e_4iphi;
                    vMd_4 += 1.;
                  } else if(eta[ip]>1.9875 && eta[ip]<2.4){
                    Q2d_4 += e_2iphi;
                    Q4d_4 += e_4iphi;
                    Md_4+=1.;
                    vQ2h_4 += e_2iphi;
                    vQ4h_4 += e_4iphi;
                    vMh_4 += 1.;
                  }
                }

               }
              }
            }
            if(one_sub_trigger && Ma_1>3.9 && Mpt>1.9){
                corr_4aaaa_1 = ( pow(TComplex::Abs(Q2a_1),4) + pow(TComplex::Abs(Q4a_1),2) - 2.*(Q4a_1*TComplex::Conjugate(Q2a_1*Q2a_1))  -2.*( 2.*(Ma_1-2.)*pow(TComplex::Abs(Q2a_1),2) - Ma_1*(Ma_1-3.)  )  ).Re()  / (Ma_1*(Ma_1-1)*(Ma_1-2)*(Ma_1-3)  );
                corr_2aa_1 = ( pow(TComplex::Abs(Q2a_1),2) - Ma_1) / (Ma_1*(Ma_1-1)  );
                meanpt = ptsum/Mpt;
                c2_4_1sub = corr_4aaaa_1 - 2*corr_2aa_1*corr_2aa_1;

                histXY_1[multBin]->Fill(c2_4_1sub*meanpt);
                histX_1[multBin]->Fill(c2_4_1sub);
                histY_1[multBin]->Fill(meanpt);
                histNch_1[multBin]->Fill(Nch);
                histCK_1[multBin]->Fill(cksum_1/Mck);
            }
            if(two_sub_trigger && Ma_2>1.9 && Mpt>1.9 && Mb_2>1.9){
                corr_4aabb_2 = ( (Q2a_2*Q2a_2 - Q4a_2)*TComplex::Conjugate(Q2b_2*Q2b_2 - Q4b_2) ).Re() / ( Ma_2*(Ma_2-1.)*Mb_2*(Mb_2-1.)  );
                corr_2ab_2 = ( Q2a_2*TComplex::Conjugate(Q2b_2) ).Re() / (Ma_2*Mb_2);
                meanpt = ptsum/Mpt;
                c2_4_2sub = corr_4aabb_2 - 2*corr_2ab_2*corr_2ab_2;

                histXY_2[multBin]->Fill(c2_4_2sub*meanpt);
                histX_2[multBin]->Fill(c2_4_2sub);
                histY_2[multBin]->Fill(meanpt);
		histNch_2[multBin]->Fill(Nch);
                histCK_2[multBin]->Fill(cksum_2/Mck);
	    }
            if(three_sub_trigger && Mpt>1.9 && vMa_3>1.9 && vMd_3>1.9 && vMb_3>0.1 && vMc_3>0.1 && vMe_3>0.1 && vMf_3>0.1){
                corr_4aabc_3 = ( (Q2a_3*Q2a_3 - Q4a_3)*TComplex::Conjugate(Q2b_3*Q2c_3) ).Re() / ( Ma_3*(Ma_3-1)*Mb_3*Mc_3 );
                corr_2ab_3 = ( Q2a_3*TComplex::Conjugate(Q2b_3) ).Re() / (Ma_3*Mb_3);
                corr_2ac_3 = ( Q2a_3*TComplex::Conjugate(Q2c_3) ).Re() / (Ma_3*Mc_3);
                meanpt = ptsum/Mpt;
                c2_4_3sub = corr_4aabc_3 - 2*corr_2ab_3*corr_2ac_3;
                k2_4_3sub = corr_4aabc_3 - 2*corr_2ab_3*corr_2ac_3 + 2.*Cov_2ab_2ac_3[multBin];

                histXY_3[multBin]->Fill(c2_4_3sub*meanpt);
                histX_3[multBin]->Fill(c2_4_3sub);
                khistXY_3[multBin]->Fill(k2_4_3sub*meanpt);
                khistX_3[multBin]->Fill(k2_4_3sub);
                histY_3[multBin]->Fill(meanpt);
                histNch_3[multBin]->Fill(Nch);
                histCK_3[multBin]->Fill(cksum_3/Mck);

                vcorr_4aabc_3 = ( (vQ2a_3*vQ2a_3 - vQ4a_3)*TComplex::Conjugate(vQ2b_3*vQ2c_3) ).Re() / ( vMa_3*(vMa_3-1)*vMb_3*vMc_3 );
                vcorr_2ab_3 = ( vQ2a_3*TComplex::Conjugate(vQ2b_3) ).Re() / (vMa_3*vMb_3);
                vcorr_2ac_3 = ( vQ2a_3*TComplex::Conjugate(vQ2c_3) ).Re() / (vMa_3*vMc_3); 
                vcorr_4ddef_3 = ( (vQ2d_3*vQ2d_3 - vQ4d_3)*TComplex::Conjugate(vQ2e_3*vQ2f_3) ).Re() / ( vMd_3*(vMd_3-1)*vMe_3*vMf_3 );
                vcorr_2de_3 = ( vQ2d_3*TComplex::Conjugate(vQ2e_3) ).Re() / (vMd_3*vMe_3);
                vcorr_2df_3 = ( vQ2d_3*TComplex::Conjugate(vQ2f_3) ).Re() / (vMd_3*vMf_3);

                c2_4abc_3sub = vcorr_4aabc_3 - 2*vcorr_2ab_3*vcorr_2ac_3;    
                k2_4abc_3sub = vcorr_4aabc_3 - 2*vcorr_2ab_3*vcorr_2ac_3 + 2.*cCov_2ab_2ac_3[multBin];
                c2_4def_3sub = vcorr_4ddef_3 - 2*vcorr_2de_3*vcorr_2df_3;    
                k2_4def_3sub = vcorr_4ddef_3 - 2*vcorr_2de_3*vcorr_2df_3 + 2.*cCov_2de_2df_3[multBin];

                histc24abcdef_3[multBin]->Fill(c2_4abc_3sub*c2_4def_3sub);
                histc24abc_3[multBin]->Fill(c2_4abc_3sub);
                histc24def_3[multBin]->Fill(c2_4def_3sub);
                khistc24abcdef_3[multBin]->Fill(k2_4abc_3sub*k2_4def_3sub);
                khistc24abc_3[multBin]->Fill(k2_4abc_3sub);
                khistc24def_3[multBin]->Fill(k2_4def_3sub);
            }
            if(four_sub_trigger && Mpt>1.9 && vMa_4>0.1 && vMb_4>0.1 && vMc_4>0.1 && vMd_4>0.1 && vMe_4>0.1 && vMf_4>0.1 && vMg_4>0.1 && vMh_4>0.1){
                corr_4abcd_4 = ( Q2a_4*Q2b_4*TComplex::Conjugate(Q2c_4*Q2d_4) ).Re() / ( Ma_4*Mb_4*Mc_4*Md_4 );
                corr_2ad_4 = ( Q2a_4*TComplex::Conjugate(Q2d_4) ).Re() / ( Ma_4*Md_4 );
                corr_2bc_4 = ( Q2b_4*TComplex::Conjugate(Q2c_4) ).Re() / ( Mb_4*Mc_4 );
                corr_2ac_4 = ( Q2a_4*TComplex::Conjugate(Q2c_4) ).Re() / ( Ma_4*Mc_4 );
                corr_2bd_4 = ( Q2b_4*TComplex::Conjugate(Q2d_4) ).Re() / ( Mb_4*Md_4 );
                meanpt = ptsum/Mpt;
                c2_4_4sub = corr_4abcd_4 - corr_2ac_4*corr_2bd_4 - corr_2ad_4*corr_2bc_4;
                k2_4_4sub = corr_4abcd_4 - corr_2ac_4*corr_2bd_4 - corr_2ad_4*corr_2bc_4 + (Cov_2ac_2bd_4[multBin] + Cov_2ad_2bc_4[multBin]);

                histXY_4[multBin]->Fill(c2_4_4sub*meanpt);
                histX_4[multBin]->Fill(c2_4_4sub);
                khistXY_4[multBin]->Fill(k2_4_4sub*meanpt);
                khistX_4[multBin]->Fill(k2_4_4sub);
                histY_4[multBin]->Fill(meanpt);
                histNch_4[multBin]->Fill(Nch);
                histCK_4[multBin]->Fill(cksum_4/Mck);

                vcorr_4abcd_4 = ( vQ2a_4*vQ2b_4*TComplex::Conjugate(vQ2c_4*vQ2d_4) ).Re() / ( vMa_4*vMb_4*vMc_4*vMd_4 );
                vcorr_2ad_4 = ( vQ2a_4*TComplex::Conjugate(vQ2d_4) ).Re() / ( vMa_4*vMd_4 );
                vcorr_2bc_4 = ( vQ2b_4*TComplex::Conjugate(vQ2c_4) ).Re() / ( vMb_4*vMc_4 );
                vcorr_2ac_4 = ( vQ2a_4*TComplex::Conjugate(vQ2c_4) ).Re() / ( vMa_4*vMc_4 );
                vcorr_2bd_4 = ( vQ2b_4*TComplex::Conjugate(vQ2d_4) ).Re() / ( vMb_4*vMd_4 );
                vcorr_4efgh_4 = ( vQ2e_4*vQ2f_4*TComplex::Conjugate(vQ2g_4*vQ2h_4) ).Re() / ( vMe_4*vMf_4*vMg_4*vMh_4 );
                vcorr_2eh_4 = ( vQ2e_4*TComplex::Conjugate(vQ2h_4) ).Re() / ( vMe_4*vMh_4 );
                vcorr_2fg_4 = ( vQ2f_4*TComplex::Conjugate(vQ2g_4) ).Re() / ( vMf_4*vMg_4 );
                vcorr_2eg_4 = ( vQ2e_4*TComplex::Conjugate(vQ2g_4) ).Re() / ( vMe_4*vMg_4 );
                vcorr_2fh_4 = ( vQ2f_4*TComplex::Conjugate(vQ2h_4) ).Re() / ( vMf_4*vMh_4 );

                c2_4abcd_4sub = vcorr_4abcd_4 - vcorr_2ac_4*vcorr_2bd_4 - vcorr_2ad_4*vcorr_2bc_4; 
                k2_4abcd_4sub = vcorr_4abcd_4 - vcorr_2ac_4*vcorr_2bd_4 - vcorr_2ad_4*vcorr_2bc_4 + (cCov_2ac_2bd_4[multBin] + cCov_2ad_2bc_4[multBin]); 
                c2_4efgh_4sub = vcorr_4efgh_4 - vcorr_2eg_4*vcorr_2fh_4 - vcorr_2eh_4*vcorr_2fg_4; 
                k2_4efgh_4sub = vcorr_4efgh_4 - vcorr_2eg_4*vcorr_2fh_4 - vcorr_2eh_4*vcorr_2fg_4 + (cCov_2eg_2fh_4[multBin] + cCov_2eh_2fg_4[multBin]); 

                histc24abcdefgh_4[multBin]->Fill(c2_4abcd_4sub*c2_4efgh_4sub);
                histc24abcd_4[multBin]->Fill(c2_4abcd_4sub);
                histc24efgh_4[multBin]->Fill(c2_4efgh_4sub);
                khistc24abcdefgh_4[multBin]->Fill(k2_4abcd_4sub*k2_4efgh_4sub);
                khistc24abcd_4[multBin]->Fill(k2_4abcd_4sub);
                khistc24efgh_4[multBin]->Fill(k2_4efgh_4sub);
            }



        }    
    }

    TFile *f = new TFile("outputROOT_c2_4_correlator_vs_Nch_allsub.root","recreate");
    f->cd(); 

    if(one_sub_trigger){
      for(int i=0; i<num_bins; i++){
        histXY_1[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histX_1[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histY_1[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histNch_1[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histCK_1[i]->Write();
      }
    }
    if(two_sub_trigger){
      for(int i=0; i<num_bins; i++){
        histXY_2[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histX_2[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histY_2[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histNch_2[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histCK_2[i]->Write();
      }
    }
    if(three_sub_trigger){
      for(int i=0; i<num_bins; i++){
        histXY_3[i]->Write();
        histX_3[i]->Write();
        histY_3[i]->Write();
        histNch_3[i]->Write();
        histCK_3[i]->Write();
        khistXY_3[i]->Write();
        khistX_3[i]->Write();
        histc24abcdef_3[i]->Write();
        histc24abc_3[i]->Write();
        histc24def_3[i]->Write();
        khistc24abcdef_3[i]->Write();
        khistc24abc_3[i]->Write();
        khistc24def_3[i]->Write();
      }
    }
    if(four_sub_trigger){
      for(int i=0; i<num_bins; i++){
        histXY_4[i]->Write();
        histX_4[i]->Write();
        histY_4[i]->Write();
        histNch_4[i]->Write();
        histCK_4[i]->Write();
        khistXY_4[i]->Write();
        khistX_4[i]->Write();
        histc24abcdefgh_4[i]->Write();
        histc24abcd_4[i]->Write();
        histc24efgh_4[i]->Write();
        khistc24abcdefgh_4[i]->Write();
        khistc24abcd_4[i]->Write();
        khistc24efgh_4[i]->Write();
      }
    }


     f->Write();
     f->Close();

     ofstream output1;
     output1.open("outputTEXT_c2_4_correlator_vs_Nch_allsub.txt");
 

     for(int i=0; i<num_bins; i++){
         Float_t tmp_EXY_1 = histXY_1[i]->GetMean();
         Float_t tmp_EX_1 = histX_1[i]->GetMean();
         Float_t tmp_EY_1 = histY_1[i]->GetMean();
         Float_t tmp_sigmaX_1 = histX_1[i]->GetRMS();
         Float_t tmp_sigmaY_1 = histY_1[i]->GetRMS();
         Float_t tmp_ck_1 = histCK_1[i]->GetMean();
 
         Float_t tmp_EXY_2 = histXY_2[i]->GetMean();
         Float_t tmp_EX_2 = histX_2[i]->GetMean();
         Float_t tmp_EY_2 = histY_2[i]->GetMean();
         Float_t tmp_sigmaX_2 = histX_2[i]->GetRMS();
         Float_t tmp_sigmaY_2 = histY_2[i]->GetRMS();
         Float_t tmp_ck_2 = histCK_2[i]->GetMean();
         
         Float_t tmp_EXY_3 = histXY_3[i]->GetMean();
         Float_t tmp_EX_3 = histX_3[i]->GetMean();
         Float_t tmp2_EXY_3 = khistXY_3[i]->GetMean();
         Float_t tmp2_EX_3 = khistX_3[i]->GetMean();
         Float_t tmp_EY_3 = histY_3[i]->GetMean();
         Float_t tmp_sigmaX_3 = sqrt(histc24abcdef_3[i]->GetMean() - histc24abc_3[i]->GetMean()*histc24def_3[i]->GetMean());
         Float_t tmp_sigmaY_3 = sqrt(histCK_3[i]->GetMean());
         //Float_t tmp_ck_3 = histCK_3[i]->GetMean();

         Float_t tmp_EXY_4 = histXY_4[i]->GetMean();
         Float_t tmp_EX_4 = histX_4[i]->GetMean();
         Float_t tmp2_EXY_4 = khistXY_4[i]->GetMean();
         Float_t tmp2_EX_4 = khistX_4[i]->GetMean();
         Float_t tmp_EY_4 = histY_4[i]->GetMean();
         Float_t tmp_sigmaX_4 = sqrt(histc24abcdefgh_4[i]->GetMean() - histc24abcd_4[i]->GetMean()*histc24efgh_4[i]->GetMean());
         Float_t tmp_sigmaY_4 = sqrt(histCK_4[i]->GetMean());
         //Float_t tmp_ck_4 = histCK_4[i]->GetMean();

//cout<<histDynVarFirstTerm_3[i]->GetMean() - pow(histDynVarSecondTerm_3[i]->GetMean(),2)<<"   "<<histDynVarFirstTerm_4[i]->GetMean() - pow(histDynVarSecondTerm_4[i]->GetMean(),2)<<endl;
       //cout<<histNch_3[i]->GetEntries()<<"   "<<histNch_3[i]->GetMean()<<"   "<<histCorr8_3[i]->GetMean() - tmp_EX_3<<"   "<< histDynVarFirstTerm_3[i]->GetMean() - pow(histDynVarSecondTerm_3[i]->GetMean(),2)<< "   "<< histDynVarFirstTerm_3[i]->GetMean() - pow(histDynVarSecondTerm_3[i]->GetMean(),2) - (histCorr8_3[i]->GetMean() - tmp_EX_3)<<endl;
       //cout<<tmp_EXY_3 - tmp_EX_3*tmp_EY_3<<"   "<<histXY_3tmp[i]->GetMean() - histX_3tmp[i]->GetMean()*tmp_EY_3<<"   "<<histXY_3tmp[i]->GetMean() - histX_3tmp[i]->GetMean()*tmp_EY_3-(tmp_EXY_3 - tmp_EX_3*tmp_EY_3)<<endl;
       //cout<<histNch_4[i]->GetEntries()<<"   "<<histNch_4[i]->GetMean()<<"   "<<histCorr8_4[i]->GetMean() - tmp_EX_4<<"   "<< histDynVarFirstTerm_4[i]->GetMean() - pow(histDynVarSecondTerm_4[i]->GetMean(),2)<< "   "<< histDynVarFirstTerm_4[i]->GetMean() - pow(histDynVarSecondTerm_4[i]->GetMean(),2) - (histCorr8_4[i]->GetMean() - tmp_EX_4)<<endl;
       //cout<<tmp_EXY_4 - tmp_EX_4*tmp_EY_4<<"   "<<histXY_4tmp[i]->GetMean() - histX_4tmp[i]->GetMean()*tmp_EY_4<<"   "<<histXY_4tmp[i]->GetMean() - histX_4tmp[i]->GetMean()*tmp_EY_4-(tmp_EXY_4 - tmp_EX_4*tmp_EY_4)<<endl;
       cout<<histNch_3[i]->GetEntries()<<"   "<<histNch_3[i]->GetMean()<<"   "<< tmp_EXY_3 - tmp_EX_3*tmp_EY_3 <<"   "<< tmp2_EXY_3 - tmp2_EX_3*tmp_EY_3 <<"   "<< (tmp_EXY_3 - tmp_EX_3*tmp_EY_3) / (tmp_sigmaX_3*tmp_sigmaY_3)<<"   "<< (tmp2_EXY_3 - tmp2_EX_3*tmp_EY_3) / (tmp_sigmaX_3*tmp_sigmaY_3) <<"   "<<histNch_4[i]->GetEntries()<<"   "<<histNch_4[i]->GetMean()<<"   "<< tmp_EXY_4 - tmp_EX_4*tmp_EY_4 <<"   "<< tmp2_EXY_4 - tmp2_EX_4*tmp_EY_4 <<"   "<< (tmp_EXY_4 - tmp_EX_4*tmp_EY_4) / (tmp_sigmaX_4*tmp_sigmaY_4)<<"   "<< (tmp2_EXY_4 - tmp2_EX_4*tmp_EY_4) / (tmp_sigmaX_4*tmp_sigmaY_4) <<endl;
       output1<<histNch_3[i]->GetEntries()<<"   "<<histNch_3[i]->GetMean()<<"   "<< tmp_EXY_3 - tmp_EX_3*tmp_EY_3 <<"   "<< tmp2_EXY_3 - tmp2_EX_3*tmp_EY_3 <<"   "<< (tmp_EXY_3 - tmp_EX_3*tmp_EY_3) / (tmp_sigmaX_3*tmp_sigmaY_3)<<"   "<< (tmp2_EXY_3 - tmp2_EX_3*tmp_EY_3) / (tmp_sigmaX_3*tmp_sigmaY_3) <<"   "<<histNch_4[i]->GetEntries()<<"   "<<histNch_4[i]->GetMean()<<"   "<< tmp_EXY_4 - tmp_EX_4*tmp_EY_4 <<"   "<< tmp2_EXY_4 - tmp2_EX_4*tmp_EY_4 <<"   "<< (tmp_EXY_4 - tmp_EX_4*tmp_EY_4) / (tmp_sigmaX_4*tmp_sigmaY_4)<<"   "<< (tmp2_EXY_4 - tmp2_EX_4*tmp_EY_4) / (tmp_sigmaX_4*tmp_sigmaY_4) <<endl;
    }

}
