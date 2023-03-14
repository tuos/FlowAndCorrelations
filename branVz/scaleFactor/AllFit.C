#define AllFit_cxx
#include "AllFit.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>
#include <fstream>
#include "TMath.h"

TH1D *hchi2_0_10_sw = NULL;
TH1D *hchi2_0_10_nsw = NULL;

//centrality and pT setup
const int nCentBin=4;
const int nPtBin=10;
double centCuts[nCentBin+1]={0, 10, 20, 40, 60};
double ptCuts[nPtBin+1]={0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0};
//histograms for all centrality and pt ranges
TH1D *hchi2_nsw_out_All[nCentBin][nPtBin];
TH1D *hchi2_sw_out_All[nCentBin][nPtBin];

double func(double* x, double* pars)
{
     double chi2 = x[0];

     int icent = (int)pars[0];
     int ipt = (int)pars[1];

     double landau_norm = pars[2];
     double landau_mu = pars[3];
     double landau_sigma = pars[4];
     double background_norm = pars[5];
     double landau = TMath::Landau(chi2, landau_mu, landau_sigma);
     int ibin = hchi2_sw_out_All[icent][ipt]->GetXaxis()->FindBin(chi2);
     double background_out = hchi2_sw_out_All[icent][ipt]->GetBinContent(ibin);
     return landau_norm*landau + background_norm*background_out;
}

void AllFit::Loop()
{
hchi2_0_10_sw = new TH1D("hchi2_0_10_sw", ";chi2;Counts", 100, 0, 10);
hchi2_0_10_nsw = new TH1D("hchi2_0_10_nsw", ";chi2;Counts", 100, 0, 10);

//Setup histograms for all centrality and pt ranges
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
         hchi2_nsw_out_All[i][j] = new TH1D(Form("hchi2_nsw_out_cent%d_pt%d",i,j), "", 100,0,10);
         hchi2_sw_out_All[i][j] = new TH1D(Form("hchi2_sw_out_cent%d_pt%d",i,j), "", 100,0,10);
      }
    }

Float_t px;
Float_t py;
Float_t pz;
Float_t pt;
Float_t chi2_fvtxmutr;
Float_t trhits;
Float_t trchi2;
Bool_t is_sfvtx;
Float_t lastgap;
Float_t rapidity;
Float_t idchi2;
Float_t idhits;
Float_t p;
Float_t pdg0;
Float_t pddg0;
Float_t dg0;
Float_t ddg0;
Float_t dcar;
Float_t cent;
Float_t ibin;
Float_t fvtxz;
Float_t charge;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cent = evt_cent;
      fvtxz = Evt_fvtxZ;

      for (unsigned int ismu = 0; ismu<nSingleMuons; ismu++){

      px = SingleMuons_px_fvtxmutr[ismu];
      py = SingleMuons_py_fvtxmutr[ismu];
      pz = SingleMuons_pz_fvtxmutr[ismu];
      pt = sqrt((px*px)+(py*py));
      chi2_fvtxmutr = SingleMuons_chi2_fvtxmutr[ismu];
      trhits = SingleMuons_ntrhits[ismu];
      trchi2 = SingleMuons_trchi2[ismu];
      is_sfvtx = SingleMuons_is_sfvtx[ismu];
      lastgap = SingleMuons_lastgap[ismu];
      rapidity = SingleMuons_rapidity[ismu];
      p = sqrt((px*px)+(py*py)+(pz*pz));
      dg0 = SingleMuons_DG0[ismu];
      ddg0 = SingleMuons_DDG0[ismu];
      dcar = SingleMuons_dca_r[ismu];
      idchi2 = SingleMuons_idchi2[ismu];
      idhits = SingleMuons_nidhits[ismu];
      pdg0 = p*dg0;
      pddg0 = p*ddg0;
      charge = SingleMuons_charge[ismu];

  //Apply cut and calcuate v2
      if (rapidity<-1.4 && rapidity>-2.0 && (lastgap==2 || lastgap==3)) {

      //loop for cent and pt
      for(int i=0; i<nCentBin; i++){
        for(int j=0; j<nPtBin; j++){
        
          if (pt>=ptCuts[j] && pt<ptCuts[j+1] && cent>=centCuts[i] && cent<centCuts[i+1]) {
              if(is_sfvtx==false){
                hchi2_nsw_out_All[i][j]->Fill(chi2_fvtxmutr);
              }
              else if(is_sfvtx==true){
                hchi2_sw_out_All[i][j]->Fill(chi2_fvtxmutr);
              }
          }//end for pt and cent if

        }//pt for loop
      }//cent for loop

      }

   } // end of particle loop
}

  double savedScaleFactor[nCentBin][nPtBin];
  double savedScaleFactorError[nCentBin][nPtBin];
  for(int i=0; i<nCentBin; i++){
    for(int j=0; j<nPtBin; j++){
      //hchi2_0_10_sw->Draw();
      //hchi2_0_10_nsw->Draw("same");
      TF1* FitFunc2 = new TF1("FitFunc2", func, 0, 10, 6);
      FitFunc2->SetParameters(i,j,2000/hchi2_sw_out_All[i][j]->GetBinWidth(1), 0.85, 0.2, 1.0);
      FitFunc2->SetParLimits(2,0,1000000000);
      FitFunc2->SetParLimits(4,0,5);
      FitFunc2->SetParLimits(5,0,1);
      FitFunc2->FixParameter(0,i);
      FitFunc2->FixParameter(1,j);
      hchi2_nsw_out_All[i][j]->Fit(FitFunc2, "rl", "", 0, 10);
      //FitFunc2->Draw("same");
      TF1* fLandau = new TF1("fLandau", func, 0,10,6);
      fLandau->SetParameters(FitFunc2->GetParameters());
      //fLandau->SetParameters(3,0);
      //fLandau->Draw("same");
      double params = FitFunc2->GetParameter(3);
      double parErrors = FitFunc2->GetParError(3);
      cout<<i<<"       "<<j<<"       "<<params<<"      "<<parErrors<<endl;   
      savedScaleFactor[i][j] = params;
      savedScaleFactorError[i][j] = parErrors;

    }
  }

    ofstream outTXT;
    outTXT.open("txt_cent_pt_scalefactor_error.txt");
    cout<<" Centrality | pT | scalefactor | error | entries "<<endl;
    //Saving histograms to ROOT file
    TFile *outFile = new TFile("output_cent_pt_scalefactor_histograms.root","recreate");
    outFile->cd(); 
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        hchi2_nsw_out_All[i][j]->Write();
        hchi2_sw_out_All[i][j]->Write();
        outTXT<<i<<"   "<<j<<"   "<<savedScaleFactor[i][j]<<"   "<<savedScaleFactorError[i][j]<<endl;
        cout<<i<<"       "<<j<<"       "<<savedScaleFactor[i][j]<<"      "<<savedScaleFactorError[i][j]<<"   "<<hchi2_nsw_out_All[i][j]->GetEntries()<<endl;
      }
    }
    outFile->Write();
    outFile->Close();

}
