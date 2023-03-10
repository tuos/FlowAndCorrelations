#define Fitv2_cxx
#include "Fitv2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TF1.h>
TH1D *hchi2_nsw_out = NULL;
TH1D *hchi2_sw_out = NULL;
TH1D *hdphi_nsw = NULL;
TH1D *hdphi_sw = NULL;

//centrality and pT setup
const int nCentBin=4;
const int nPtBin=10;
double centCuts[nCentBin+1]={0, 10, 20, 40, 60};
double ptCuts[nPtBin+1]={0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0};
//histograms for all centrality and pt ranges
TH1D *hchi2_nsw_out_All[nCentBin][nPtBin];
TH1D *hchi2_sw_out_All[nCentBin][nPtBin];

//Define fit function
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

void Fitv2::Loop()
{

//Setup histograms for all centrality and pt ranges
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
         hchi2_nsw_out_All[i][j] = new TH1D(Form("hchi2_nsw_out_cent%d_pt%d",i,j), "", 100,0,10);
         hchi2_sw_out_All[i][j] = new TH1D(Form("hchi2_sw_out_cent%d_pt%d",i,j), "", 100,0,10);
      }
    }

//Create Histograms
hchi2_nsw_out = new TH1D("hchi2_nsw_out", ";chi2;Counts", 100, 0, 10);
//hchi2_nsw_in = new TH1D("hchi2_nsw_in", ";chi2;Counts", 100, 0, 10);
hchi2_sw_out = new TH1D("hchi2_sw_out", ";chi2;Counts", 100, 0, 10);
//hchi2_sw_in = new TH1D("hchi2_sw_in", ";chi2;Counts", 100, 0, 10);
hdphi_nsw = new TH1D("hdphi_nsw", ";chi2;Counts", 100, -3.2, 3.2);
hdphi_sw = new TH1D("hdphi_sw", ";chi2;Counts", 100, -3.2, 3.2);


//Create Variables
Float_t px;
Float_t py;
Float_t pz;
Float_t pt;
Float_t p;
Float_t chi2_fvtxmutr;
Float_t trchi2;
Bool_t is_sfvtx;
Float_t lastgap;
Float_t rapidity;
Float_t idchi2;
Float_t dg0;
Float_t ddg0;
Float_t pdg0;
Float_t pddg0;
Float_t dcar;
Float_t cent;
Float_t ibin;
Float_t cnt;
Float_t phi;
Float_t trhits;
Float_t dphi_nsw;
Float_t dphi_sw;
Float_t fvtxz;
Float_t bbcz;
Float_t integral;
Float_t error;
Float_t qx;
Float_t qy;
Float_t fvtxs;
Float_t fvtxn;
Float_t idhits;
Float_t bbcs;
Float_t bbcn;
Float_t charge;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      //Define Variables
      cnt = CompactEPArray_psi[16];
      fvtxs = CompactEPArray_psi[17];
      fvtxn = CompactEPArray_psi[18];
      bbcs = CompactEPArray_psi[10];
      bbcn = CompactEPArray_psi[11];
      cent = evt_cent;
      fvtxz = Evt_fvtxZ;
      bbcz = evt_bbcz;

      for (unsigned int ismu = 0; ismu<nSingleMuons; ismu++){
      px = SingleMuons_px_fvtxmutr[ismu];
      py = SingleMuons_py_fvtxmutr[ismu];
      pz = SingleMuons_pz_fvtxmutr[ismu];
      pt = sqrt((px*px)+(py*py));
      p = sqrt((px*px)+(py*py)+(pz*pz));
      chi2_fvtxmutr = SingleMuons_chi2_fvtxmutr[ismu];
      trchi2 = SingleMuons_trchi2[ismu];
      is_sfvtx = SingleMuons_is_sfvtx[ismu];
      lastgap = SingleMuons_lastgap[ismu];
      rapidity = SingleMuons_rapidity[ismu];
      idchi2 = SingleMuons_idchi2[ismu];
      dg0 = SingleMuons_DG0[ismu];
      ddg0 = SingleMuons_DDG0[ismu];
      pdg0 = p*dg0;
      pddg0 = p*ddg0;
      dcar = SingleMuons_dca_r[ismu];
      trhits = SingleMuons_ntrhits[ismu];
      phi = atan2(py,px);
      qx = cos(2*(phi-cnt));
      qy = sin(2*(phi-cnt));
      idhits = SingleMuons_nidhits[ismu];
      charge = SingleMuons_charge[ismu];

      //Apply cut and calcuate v2
      if (pdg0<60 && pddg0<40 && rapidity<-1.4 && rapidity>-2.0 && abs(cnt)<4 && abs(dcar)<0.1 && abs(bbcz)<10 && trhits>11 && chi2_fvtxmutr<4 && trchi2<4 && pz<-3 && (lastgap==2 || lastgap==3)) {

      dphi_nsw = phi - cnt;
      hdphi_nsw->Fill(dphi_nsw);
      if (dphi_nsw < - TMath::Pi()/2){
      dphi_nsw = TMath::Abs(dphi_nsw + TMath::Pi());
      } else if (dphi_nsw > TMath::Pi()/2){
      dphi_nsw = TMath::Abs(dphi_nsw - TMath::Pi());
      } else if (TMath::Abs(dphi_nsw) <= TMath::Pi()/2){
      dphi_nsw = TMath::Abs(dphi_nsw);
      }

      //loop for cent and pt
      for(int i=0; i<nCentBin; i++){
        for(int j=0; j<nPtBin; j++){
        
          if (pt>=ptCuts[j] && pt<ptCuts[j+1] && cent>=centCuts[i] && cent<centCuts[i+1]) {
            if (dphi_nsw <= TMath::Pi()/4){
              if(is_sfvtx==false){
                hchi2_nsw_out_All[i][j]->Fill(chi2_fvtxmutr);
              }
              else if(is_sfvtx==true){
                hchi2_sw_out_All[i][j]->Fill(chi2_fvtxmutr);
              }
            }
          }//end for pt and cent if

        }//pt for loop
      }//cent for loop

      }//track and other cuts

/*
      if (pt>=0 && pt<4 && cent>=0 && cent<100 && pdg0<60 && pddg0<40 && rapidity<-1.4 && rapidity>-2.0 && abs(cnt)<4 && abs(dcar)<0.1 && abs(bbcz)<10 && is_sfvtx==true && trhits>11 && chi2_fvtxmutr<4 && trchi2<4 && pz<-3 && (lastgap==2 || lastgap==3)) {
      dphi_sw = phi - cnt;
      hdphi_sw->Fill(dphi_sw);
      if (dphi_sw < - TMath::Pi()/2){
      dphi_sw = TMath::Abs(dphi_sw + TMath::Pi());
      } else if (dphi_sw > TMath::Pi()/2){
      dphi_sw = TMath::Abs(dphi_sw - TMath::Pi());
      } else if (TMath::Abs(dphi_sw) <= TMath::Pi()/2){
      dphi_sw = TMath::Abs(dphi_nsw);
      }
      if (dphi_sw <= TMath::Pi()/4){
      hchi2_sw_out->Fill(chi2_fvtxmutr);
      }
   }
*/
}
 }

  double scaleFactor[nCentBin][nPtBin]={ //4 cent bins, and 10 pt bins
            {0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240},
            {0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240},
            {0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240},
            {0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240,0.2240},
         };

  double savedIntegral[nCentBin][nPtBin];
  double savedError[nCentBin][nPtBin];
  for(int i=0; i<nCentBin; i++){
    for(int j=0; j<nPtBin; j++){
      hchi2_sw_out_All[i][j]->Scale(scaleFactor[i][j]);
      //hchi2_sw_out->Draw();
      //hchi2_nsw_out->Draw("same");
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
      integral = fLandau->Integral(0,4);
      error = fLandau->IntegralError(0,4);
      //std::cout << "integral = " << integral << "+/-" << error << std::endl;
      cout<<i<<"       "<<j<<"       "<<integral<<"      "<<error<<endl;   
      savedIntegral[i][j]=integral;
      savedError[i][j]=error;

    }
  }

    ofstream outTXT;
    outTXT.open("txt_cent_pt_integral_error.txt");
    cout<<" Centrality | pT | integral | error | entries "<<endl;
    //Saving histograms to ROOT file
    TFile *outFile = new TFile("output_cent_pt_histograms.root","recreate");
    outFile->cd(); 
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        hchi2_nsw_out_All[i][j]->Write();
        hchi2_sw_out_All[i][j]->Write();
        outTXT<<i<<"   "<<j<<"   "<<savedIntegral[i][j]<<"   "<<savedError[i][j]<<endl;
        cout<<i<<"       "<<j<<"       "<<savedIntegral[i][j]<<"      "<<savedError[i][j]<<"   "<<hchi2_nsw_out_All[i][j]->GetEntries()<<endl;
      }
    }
    outFile->Write();
    outFile->Close();


}      
   

