// Run this macro second. It computes the c22/v2^2 using the three and four subevent methods. It stores is results in histograms in an output root file which can then be converted into text files to be plotted. 
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

void v2_meanpt_correlator(){

     const int num_bins = 20;
     int minNchCut[num_bins] = {0,5,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150, 180, 220};
     int maxNchCut[num_bins] = {5,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150, 180, 220, 10000};


    ifstream flist;
    flist.open("/scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src/treeInput/oct22/c22/slurmstep2/files/listFiles_jb0.txt");

    char ifile[300];

    long  nEvt;
    const float pt_min = 0.5; //0.3
    const float pt_max = 5.; //2.
    const float pt_Nch_min = 0.5;
    const float pt_Nch_max = 5.;


    Float_t pt[20000], eta[20000], phi[20000], b;
    Int_t nParticle, Nch;
    int multBin = -1;


    Float_t ptsum, Mpt, meanpt, Mck;
    Float_t cksum_2; 
    TComplex e_2iphi, e_4iphi;


    Float_t MeanPT_2[num_bins];
    TFile inFile("/scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src/treeInput/oct22/c22/slurm/outputROOT_meanpt_mergedAll.root", "read");
    for(int i=0; i<num_bins; i++){
       TH1D *histMeanPT_2 = (TH1D*)inFile.Get(Form("histMeanPT_2_%d",i));
       MeanPT_2[i] = histMeanPT_2->GetMean();
    }

      TComplex Q2a_2, Q4a_2, Q2b_2, Q4b_2;
      Float_t Ma_2, Mb_2, corr_4aabb_2, corr_2ab_2;

      TH1D *histXY_2[num_bins];
      TH1D *histX_2[num_bins];
      TH1D *histY_2[num_bins];
      TH1D *histNch_2[num_bins];
      TH1D *histCK_2[num_bins];
      TH1D *histCorr2_2[num_bins];
      TH1D *histCorr4_2[num_bins];
      TH1D *histCovV2PT_2[num_bins];
      for(int i=0; i<num_bins; i++){
         histNch_2[i] = new TH1D(Form("histNch_2_%d",i), "", 2000,0,2000);
         histXY_2[i] = new TH1D(Form("histXY_2_%d",i), "", 330,-11,11);
         histX_2[i] = new TH1D(Form("histX_2_%d",i), "", 330,-11,11);
         histY_2[i] = new TH1D(Form("histY_2_%d",i), "", 330,-11,11);
         histCK_2[i] = new TH1D(Form("histCK_2_%d",i), "", 330,-11,11); 
         histCorr2_2[i] = new TH1D(Form("histCorr2_2_%d",i), "", 330,-11,11);
         histCorr4_2[i] = new TH1D(Form("histCorr4_2_%d",i), "", 330,-11,11);
         histCovV2PT_2[i] = new TH1D(Form("histCovV2PT_2_%d",i), "", 330,-11,11);
      }

    int nFiles=0;
    double nEventsInput=0;
    while( flist >> ifile ){
        nFiles++;
        cout << nFiles << ", OPEN: " << ifile << endl;

        TFile *infile = new TFile(ifile,"read");

        TTree *t1 = (TTree*)infile->Get("demo/trackTree");
        t1->SetBranchAddress("nTrk", &nParticle);
        t1->SetBranchAddress("trackPhi", &phi);
        t1->SetBranchAddress("trackPt", &pt);
        t1->SetBranchAddress("trackEta", &eta);



        nEvt = t1->GetEntries();
        nEventsInput += nEvt;
        //nEvt = 1000;
        for(int ne=0; ne<nEvt; ne++){
	    t1->GetEntry(ne);


            if(ne%10000==0)  cout<<"Run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;

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

             if(Nch==0){
               multBin=0;
             } else{
             for(int imult=0;imult<num_bins;imult++){
              if((Nch>minNchCut[imult]&&Nch<=maxNchCut[imult])){
                multBin=imult;
              }
             }
            }

            ptsum=0; Mpt=0; cksum_2=0; Mck=0;
            Q2a_2=0; Q4a_2=0; Q2b_2=0; Q4b_2=0; Ma_2=0; Mb_2=0;
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
                         if(eta[jp]>-0.5 && eta[jp]<0.5){
                            cksum_2 += (pt[ip]-MeanPT_2[multBin])*(pt[jp]-MeanPT_2[multBin]);
                            Mck += 1.;
                         }
                        }
                    }
                    continue;
                }

                e_2iphi=TComplex::Exp(TComplex(0,2*phi[ip]));
                e_4iphi=TComplex::Exp(TComplex(0,4*phi[ip]));

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
             }
            }
          

            if(Ma_2>1.9 && Mpt>1.9 && Mb_2>1.9){
                corr_4aabb_2 = ( (Q2a_2*Q2a_2 - Q4a_2)*TComplex::Conjugate(Q2b_2*Q2b_2 - Q4b_2) ).Re() / ( Ma_2*(Ma_2-1.)*Mb_2*(Mb_2-1.)  );
                corr_2ab_2 = ( Q2a_2*TComplex::Conjugate(Q2b_2) ).Re() / (Ma_2*Mb_2);
                meanpt = ptsum/Mpt;

                histXY_2[multBin]->Fill(corr_2ab_2*meanpt);
                histX_2[multBin]->Fill(corr_2ab_2);
                histY_2[multBin]->Fill(meanpt);

                histCovV2PT_2[multBin]->Fill(corr_2ab_2*(meanpt-MeanPT_2[multBin]));
                histNch_2[multBin]->Fill(Nch);
                histCK_2[multBin]->Fill(cksum_2/Mck);
                histCorr2_2[multBin]->Fill(corr_2ab_2);
                histCorr4_2[multBin]->Fill(corr_4aabb_2);
            }

        }    
   }


    TFile *f = new TFile("outputROOT_v2_meanpt_correlator_vs_Nch.root","recreate");
    f->cd(); 

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
      for(int i=0; i<num_bins; i++){
        histCorr2_2[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histCorr4_2[i]->Write();
      }
      for(int i=0; i<num_bins; i++){
        histCovV2PT_2[i]->Write();
      }

     f->Write();
     f->Close();

     ofstream output1;
     output1.open("outputTEXT_v2_meanpt_correlator_vs_Nch.txt");
 
     double nEvtAllBins=0;
     for(int i=0; i<num_bins; i++){
         Float_t tmp_EXY_2 = histXY_2[i]->GetMean();
         Float_t tmp_EX_2 = histX_2[i]->GetMean();
         Float_t tmp_EY_2 = histY_2[i]->GetMean();
         Float_t tmp_sigmaX_2 = histX_2[i]->GetRMS();
         Float_t tmp_sigmaY_2 = histY_2[i]->GetRMS();
         Float_t tmp_ck_2 = histCK_2[i]->GetMean();
         Float_t tmp_dynvarv2_2 = histCorr4_2[i]->GetMean() - pow(histCorr2_2[i]->GetMean(),2);
       
 
       cout<<histNch_2[i]->GetEntries()<<"   "<<histNch_2[i]->GetMean()<<"   "<< tmp_EXY_2 - tmp_EX_2*tmp_EY_2 <<"   "<< histCovV2PT_2[i]->GetMean() <<"   "<< (tmp_EXY_2 - tmp_EX_2*tmp_EY_2) / (tmp_sigmaX_2*tmp_sigmaY_2) <<"   "<<(histCovV2PT_2[i]->GetMean()) / (sqrt(tmp_dynvarv2_2)*sqrt(tmp_ck_2))<<endl; 
       output1<<histNch_2[i]->GetEntries()<<"   "<<histNch_2[i]->GetMean()<<"   "<< tmp_EXY_2 - tmp_EX_2*tmp_EY_2 <<"   "<< histCovV2PT_2[i]->GetMean() <<"   "<< (tmp_EXY_2 - tmp_EX_2*tmp_EY_2) / (tmp_sigmaX_2*tmp_sigmaY_2) <<"   "<<(histCovV2PT_2[i]->GetMean()) / (sqrt(tmp_dynvarv2_2)*sqrt(tmp_ck_2))<<endl; 

       nEvtAllBins += histNch_2[i]->GetEntries();

    }
    cout<<"Total Number of events analyzed: "<<nEvtAllBins<<" ,  Total Input: "<<nEventsInput<<endl;
    output1<<"Total Number of events analyzed: "<<nEvtAllBins<<" ,  Total Input: "<<nEventsInput<<endl;

}
