// Run this macro first. It calculates the meanpt for each bin (which is required for the dynamic variance of meanpt variable in the next macro).
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

void meanpt_vs_Nch(){

     const int num_bins = 20;
     int minNchCut[num_bins] = {0,5,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150, 180, 220};
     int maxNchCut[num_bins] = {5,10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 150, 180, 220, 10000};


    ifstream flist;
    flist.open("/scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src/treeInput/oct22/c22/slurm/files/listFiles_jb0.txt");

    char ifile[300];

    long  nEvt;
    const float pt_min = 0.5; //0.3
    const float pt_max = 5.; //2.0
    const float pt_Nch_min = 0.5;
    const float pt_Nch_max = 5.;


    Float_t pt[20000], eta[20000], phi[20000], b;
    Int_t nParticle, Nch;
    int multBin = -1;

    Float_t ptsum, Mpt, meanpt;
      Float_t Ma_2, Mb_2;
      TH1D *histMeanPT_2[num_bins];
      for(int i=0; i<num_bins; i++){
         histMeanPT_2[i] = new TH1D(Form("histMeanPT_2_%d",i), "", 330,-11,1000);
      }

    while( flist >> ifile ){

        cout << "OPEN: " << ifile << endl;

        TFile *infile = new TFile(ifile,"read");

        TTree *t1 = (TTree*)infile->Get("demo/trackTree");
        t1->SetBranchAddress("nTrk", &nParticle);
        t1->SetBranchAddress("trackPhi", &phi);
        t1->SetBranchAddress("trackPt", &pt);
        t1->SetBranchAddress("trackEta", &eta);



        nEvt = t1->GetEntries();
        //nEvt = 100000;

        for(int ne=0; ne<nEvt; ne++){
	    t1->GetEntry(ne);


            if(ne%10000==0)  cout<<"Run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;

            // find Nch
            Nch = 0;
	    for(int i=0; i<nParticle; i++){
		if(pt[i]>pt_Nch_min && pt[i]<pt_Nch_max){
                    if(fabs(eta[i])>2.4) continue;    
                    Nch++; 
                }
            }
	    if(Nch>10000) continue;

            for(int imult=0;imult<num_bins;imult++){
              if((Nch>minNchCut[imult]&&Nch<=maxNchCut[imult])){
                multBin=imult;
              }
            }
            if(Nch==0) multBin=0;

            ptsum=0; Mpt=0;
            Ma_2=0; Mb_2=0;
            //particle loop
            for(int ip=0; ip<nParticle; ip++){
		if(pt[ip]>pt_min && pt[ip]<pt_max){
                if(fabs(eta[ip])<2.4){

                if(eta[ip]>-0.5 && eta[ip]<0.5){
                    ptsum += pt[ip];
                    Mpt += 1.;
                    continue;
                }

		  if(eta[ip]<-0.75){
                    Ma_2+=1.;
		  } else if(eta[ip]>0.75){
                    Mb_2+=1.;
                  }
              }
             }
            }

            if(Ma_2>1.9 && Mpt>1.9 && Mb_2>1.9){
                meanpt = ptsum/Mpt;
                histMeanPT_2[multBin]->Fill(meanpt);
            }

        }    
     } 



    TFile *f = new TFile("outputROOT_meanpt.root","recreate");
    f->cd();

      for(int i=0; i<num_bins; i++){
        histMeanPT_2[i]->Write();
      }

     f->Write();
     f->Close();
 }

