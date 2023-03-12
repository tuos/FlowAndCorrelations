#define NewSimv2_cxx
#include "NewSimv2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TF1.h>
#include <TRandom3.h>

TH1D *hdphi = NULL;
TH1D *hdphi_p = NULL;
TH1D *hv2 = NULL;
TH1D *hv2_p = NULL;

//centrality and pT setup
const int nCentBin=4;
const int nPtBin=11;
double centCuts[nCentBin+1]={0, 10, 20, 40, 60};
double ptCuts[nPtBin+1]={0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0, 100.0};
//histograms for all centrality and pt ranges
TH1D *hv2_All[nCentBin][nPtBin];
TH1D *hv2_p_All[nCentBin][nPtBin];
TH1D *hpt_All[nCentBin][nPtBin];

void NewSimv2::Loop()
{

//Setup histograms for all centrality and pt ranges
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
         hv2_All[i][j] = new TH1D(Form("hv2_cent%d_pt%d",i,j), "", 110,-1.1,1.1);
         hv2_p_All[i][j] = new TH1D(Form("hv2_p_cent%d_pt%d",i,j), "", 110,-1.1,1.1);
         hpt_All[i][j] = new TH1D(Form("hpt_cent%d_pt%d",i,j), "", 110,0,11);
      }
    }

//Hadron v2
  double hadronV2[nCentBin][nPtBin]={ //4 cent bins, and 11 (NOT 10 since need to consider pT>5GeV) pt bins, assuming v2=0.0601 for pT>5 GeV here
            {0.0323, 0.0373, 0.0435, 0.0573, 0.0672, 0.0677, 0.0698, 0.0903, 0.1173, 0.1006, 0.0601},
            {0.0323, 0.0373, 0.0435, 0.0573, 0.0672, 0.0677, 0.0698, 0.0903, 0.1173, 0.1006, 0.0601},
            {0.0323, 0.0373, 0.0435, 0.0573, 0.0672, 0.0677, 0.0698, 0.0903, 0.1173, 0.1006, 0.0601},
            {0.0323, 0.0373, 0.0435, 0.0573, 0.0672, 0.0677, 0.0698, 0.0903, 0.1173, 0.1006, 0.0601}
         };

hdphi = new TH1D("hdphi", ";dphi;Counts", 100, -6.2, 6.2);
hdphi_p = new TH1D("hdphi_p", ";dphi;Counts", 100, -6.2, 6.2);
hv2 = new TH1D("hv2", ";v2;Counts", 100, -1, 1);
hv2_p = new TH1D("hv2_p", ";v2;Counts", 100, -1, 1);

Float_t px_p;
Float_t py_p;
Float_t pz_p;
Float_t pt_p;
Float_t px;
Float_t py;
Float_t pz;
Float_t pt;
Float_t p;
Float_t chi2_fvtxmutr;
Float_t lastgap;
Float_t cent;
Float_t phi_p;
Float_t phi;
Float_t pid_p;
Float_t pid;
Float_t dphi;
Float_t dphi_p;
Float_t had_v2;
Float_t wv2;
Float_t Psi = 0;
TRandom3 *rnd;
rnd = new TRandom3(0);
Float_t DG0;
Float_t DDG0;
Float_t trchi2;
Float_t pddg0;
Float_t pdg0;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      cent = Evt_Cent;

      for (unsigned int ismu = 0; ismu<nSingleMuons; ismu++){
      px_p = MCSingleMuonFvtxs_mc_p_px[ismu];
      py_p = MCSingleMuonFvtxs_mc_p_py[ismu];
      pz_p = MCSingleMuonFvtxs_mc_p_pz[ismu];
      pt_p = sqrt((px_p*px_p)+(py_p*py_p));
      px = SingleMuons_px_fvtxmutr[ismu];
      py = SingleMuons_py_fvtxmutr[ismu];
      pz = SingleMuons_pz_fvtxmutr[ismu];
      pt = sqrt((px*px)+(py*py));
      p = sqrt((px*px)+(py*py)+(pz*pz));
      chi2_fvtxmutr = SingleMuons_chi2_fvtxmutr[ismu];
      lastgap = SingleMuons_lastgap[ismu];
      phi_p = atan2(py_p,px_p);
      phi = atan2(py,px);
      pid_p = MCSingleMuonFvtxs_mc_p_pid[ismu];
      pid = MCSingleMuonFvtxs_mc_pid[ismu];

      int iCentBin=-1;
      int iPtBin=-1;
      for(int i=0; i<nCentBin; i++){
        for(int j=0; j<nPtBin; j++){
          if (pt_p>=ptCuts[j] && pt_p<ptCuts[j+1] && cent>=centCuts[i] && cent<centCuts[i+1]) {
            iCentBin = i;
            iPtBin = j;
          }
        }
      }
      if(iCentBin==-1 ||iPtBin==-1){
        had_v2 = 0.0;
      } 
      else {
        had_v2 = hadronV2[iCentBin][iPtBin];
      }

      Psi = rnd->Uniform(-3.14,3.14);
      wv2 = (1+2*(had_v2)*cos(2*(phi_p-Psi)));

      DG0 = SingleMuons_DG0[ismu];
      DDG0 = SingleMuons_DDG0[ismu];
      trchi2 = SingleMuons_trchi2[ismu];
      pdg0 = p*DDG0;
      pddg0 = p*DDG0;

      //daughters
      for(int i=0; i<nCentBin; i++){
        for(int j=0; j<nPtBin; j++){
          if (pt>=ptCuts[j] && pt<ptCuts[j+1] && cent>=centCuts[i] && cent<centCuts[i+1]  &&  trchi2<4 && pdg0<60 && pddg0<40 && chi2_fvtxmutr<4 && (abs(pid_p)==211 || abs(pid_p)==321) && abs(pid)==13 && lastgap==4) {
            dphi = phi - Psi;
            hv2_All[i][j]->Fill(cos(2*dphi), wv2);
            hpt_All[i][j]->Fill(pt);
          }
        }
      }

      //parents
      for(int i=0; i<nCentBin; i++){
        for(int j=0; j<nPtBin; j++){
          if (pt_p>=ptCuts[j] && pt_p<ptCuts[j+1] && cent>=centCuts[i] && cent<centCuts[i+1]  &&  trchi2<4 && pdg0<60 && pddg0<40 && chi2_fvtxmutr<4 && (abs(pid_p)==211 || abs(pid_p)==321) && abs(pid)==13 && lastgap==4) {
            dphi_p = phi_p - Psi;
            hv2_p_All[i][j]->Fill(cos(2*dphi_p), wv2);
          }
        }
      }
}
}

    ofstream outTXTdaughters;
    outTXTdaughters.open("txt_cent_pt_simv2_daughters.txt");
    ofstream outTXTparents;
    outTXTparents.open("txt_cent_pt_simv2_parents.txt");
    cout<<" Centrality | pT | integral | error | entries "<<endl;
    //Saving histograms to ROOT file
    TFile *outFile = new TFile("output_cent_pt_simv2_histograms.root","recreate");
    outFile->cd(); 
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        hv2_All[i][j]->Write();
        hv2_p_All[i][j]->Write();
        hpt_All[i][j]->Write();
        outTXTparents<<i<<"   "<<j<<"   "<<hv2_p_All[i][j]->GetMean()<<"   "<<hv2_p_All[i][j]->GetMeanError()<<endl;
        outTXTdaughters<<i<<"   "<<j<<"   "<<hpt_All[i][j]->GetMean()<<"   "<<hv2_All[i][j]->GetMean()<<"   "<<hv2_All[i][j]->GetMeanError()<<endl;
        cout<<i<<"   "<<j<<"   "<<hv2_p_All[i][j]->GetMean()<<"   "<<hv2_p_All[i][j]->GetMeanError()<<"   "<<hpt_All[i][j]->GetMean()<<"   "<<hv2_All[i][j]->GetMean()<<"   "<<hv2_All[i][j]->GetMeanError()<<"   "<<hpt_All[i][j]->GetEntries()<<endl;
      }
    }
    outFile->Write();
    outFile->Close();

      //std::cout << " v2 = " << hv2->GetMean() << " Error = " << hv2->GetMeanError() << " Parent v2 = " << hv2_p->GetMean() << " Parent Error = " << hv2_p->GetMeanError() << std::endl;

}
