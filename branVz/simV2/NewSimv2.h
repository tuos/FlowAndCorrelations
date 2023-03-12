//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 10 12:09:42 2023 by ROOT version 5.34/36
// from TTree T/titled by PHOOL
// found on file: singlemuon_hadrons-MB_hadrons_and_decays_mutr5hits_skip0.root
//////////////////////////////////////////////////////////

#ifndef NewSimv2_h
#define NewSimv2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxSingleMuons = 425;
   const Int_t kMaxMCSingleMuonFvtxs = 425;

class NewSimv2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //SingleMuonContainer_v17 *DST/SingleMuonContainer_filtered;
   UInt_t          nSingleMuons;
   Int_t           SingleMuons_;
   Float_t         SingleMuons_px[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_py[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_pz[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_rapidity[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_trhits[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_idhits[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_DG0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_DDG0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_DS3[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_trchi2[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_idchi2[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_ntrhits[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_nidhits[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_lastgap[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_xst1[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_xst2[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_xst3[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_yst1[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_yst2[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_yst3[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_idx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_idy[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_st1px[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_st1py[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_st1pz[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_MUID1D[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_MUID1S[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dca_z[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dca_r[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_charge[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_x0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_y0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_z0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_cov[kMaxSingleMuons][5][5];   //[SingleMuons_]
   Float_t         SingleMuons_x0_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_y0_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_z0_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_px_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_py_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_pz_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_x0_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_y0_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_z0_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_px_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_py_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_pz_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   UInt_t          SingleMuons_nhits_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dphi_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dtheta_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dr_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_chi2_fvtx[kMaxSingleMuons];   //[SingleMuons_]
   UInt_t          SingleMuons_fvtx_strip[kMaxSingleMuons][4];   //[SingleMuons_]
   Float_t         SingleMuons_cov_fvtx[kMaxSingleMuons][5][5];   //[SingleMuons_]
   Float_t         SingleMuons_cov_fvtxmutr[kMaxSingleMuons][5][5];   //[SingleMuons_]
   Float_t         SingleMuons_fvtx_charge[kMaxSingleMuons][4];   //[SingleMuons_]
   Long64_t        SingleMuons_nfvtx_trks[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_mutoo_trk_index[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_chi2_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dca_phi[kMaxSingleMuons];   //[SingleMuons_]
   UShort_t        SingleMuons_clusters_size1[kMaxSingleMuons];   //[SingleMuons_]
   ULong_t         SingleMuons_nfvtx_tracklets_cone[kMaxSingleMuons];   //[SingleMuons_]
   UInt_t          SingleMuons_nfvtx_tracklets[kMaxSingleMuons];   //[SingleMuons_]
   ULong_t         SingleMuons_nfvtx_clusters_cone[kMaxSingleMuons];   //[SingleMuons_]
   Int_t           SingleMuons_fvtxtrack_id[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_vtx_index[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_n_matchings[kMaxSingleMuons];   //[SingleMuons_]
   UShort_t        SingleMuons_hit_pattern[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_cov_mutsta1[kMaxSingleMuons][5][5];   //[SingleMuons_]
   Float_t         SingleMuons_x_fvtxproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_y_fvtxproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_x_mutproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_y_mutproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_px_fvtxproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_py_fvtxproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_px_mutproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_py_mutproj[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_dr_fvtxmutr_sigma[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_dphi_fvtxmutr_sigma[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_dpr_fvtxmutr_sigma[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_dpphi_fvtxmutr_sigma[kMaxSingleMuons][3];   //[SingleMuons_]
   Float_t         SingleMuons_maxres_sigma[kMaxSingleMuons];   //[SingleMuons_]
   ULong_t         SingleMuons_track_id[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_best_fvtxmutr_match[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_is_sfvtx[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_idpanel[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         Evt_bbcZ;
   Float_t         Evt_bbcZ_Err;
   Float_t         Evt_vtxX;
   Float_t         Evt_vtxX_Err;
   Float_t         Evt_vtxY;
   Float_t         Evt_vtxY_Err;
   Float_t         Evt_vtxZ;
   Float_t         Evt_vtxZ_Err;
   Float_t         Evt_fvtxX;
   Float_t         Evt_fvtxX_Err;
   Float_t         Evt_fvtxY;
   Float_t         Evt_fvtxY_Err;
   Float_t         Evt_fvtxZ;
   Float_t         Evt_fvtxZ_Err;
   Float_t         Evt_fvtxX2;
   Float_t         Evt_fvtxY2;
   Float_t         Evt_fvtxZ2;
   Float_t         Evt_Cent;
   Int_t           Evt_Mult_FVTXN;
   Int_t           Evt_Mult_FVTXS;
   Int_t           Evt_Mult_SVX;
   Int_t           Evt_Mult_sFVTXN;
   Int_t           Evt_Mult_sFVTXS;
   Float_t         Evt_BbcTdcMean_S;
   Float_t         Evt_BbcTdcMean_N;
   Float_t         Evt_BbcTdcRMS_S;
   Float_t         Evt_BbcTdcRMS_N;
   Float_t         Evt_BbcTdcMode_S;
   Float_t         Evt_BbcTdcMode_N;
   Short_t         Evt_BbcTdcnPeaks_S;
   Short_t         Evt_BbcTdcnPeaks_N;
 //MCSingleMuonFvtxContainer_v3 *DST/MCSingleMuonFvtxContainer_filtered;
   UInt_t          nMCSingleMuonFvtxs;
   Int_t           MCSingleMuonFvtxs_;
   Float_t         MCSingleMuonFvtxs_mc_n_part[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_px[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_py[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_pz[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_ptot[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_x[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_y[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_z[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_pid[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_trk[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_p_pid[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_p_px[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_p_py[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_p_pz[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_p_ptot[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_p_z[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_g_pid[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_g_px[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_g_py[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_g_pz[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_g_ptot[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_g_z[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_pid[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_px[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_py[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_pz[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_ptot[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_z[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_d_n[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_px_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_py_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_pz_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_pid_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_coords_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_trk_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits_fvtx_true[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_trks_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Int_t           MCSingleMuonFvtxs_mc_nomchits_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_dca_r[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_dca_phi[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_dca_z[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits_svx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits_svx_true[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits_mutr_true[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_hits_muid_true[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_x_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_y_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]
   Float_t         MCSingleMuonFvtxs_mc_z_fvtx[kMaxMCSingleMuonFvtxs];   //[MCSingleMuonFvtxs_]

   // List of branches
   TBranch        *b_DST_SingleMuonContainer_filtered_nSingleMuons;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_SingleMuons_;   //!
   TBranch        *b_SingleMuons_px;   //!
   TBranch        *b_SingleMuons_py;   //!
   TBranch        *b_SingleMuons_pz;   //!
   TBranch        *b_SingleMuons_rapidity;   //!
   TBranch        *b_SingleMuons_trhits;   //!
   TBranch        *b_SingleMuons_idhits;   //!
   TBranch        *b_SingleMuons_DG0;   //!
   TBranch        *b_SingleMuons_DDG0;   //!
   TBranch        *b_SingleMuons_DS3;   //!
   TBranch        *b_SingleMuons_trchi2;   //!
   TBranch        *b_SingleMuons_idchi2;   //!
   TBranch        *b_SingleMuons_ntrhits;   //!
   TBranch        *b_SingleMuons_nidhits;   //!
   TBranch        *b_SingleMuons_lastgap;   //!
   TBranch        *b_SingleMuons_xst1;   //!
   TBranch        *b_SingleMuons_xst2;   //!
   TBranch        *b_SingleMuons_xst3;   //!
   TBranch        *b_SingleMuons_yst1;   //!
   TBranch        *b_SingleMuons_yst2;   //!
   TBranch        *b_SingleMuons_yst3;   //!
   TBranch        *b_SingleMuons_idx;   //!
   TBranch        *b_SingleMuons_idy;   //!
   TBranch        *b_SingleMuons_st1px;   //!
   TBranch        *b_SingleMuons_st1py;   //!
   TBranch        *b_SingleMuons_st1pz;   //!
   TBranch        *b_SingleMuons_MUID1D;   //!
   TBranch        *b_SingleMuons_MUID1S;   //!
   TBranch        *b_SingleMuons_dca_z;   //!
   TBranch        *b_SingleMuons_dca_r;   //!
   TBranch        *b_SingleMuons_charge;   //!
   TBranch        *b_SingleMuons_x0;   //!
   TBranch        *b_SingleMuons_y0;   //!
   TBranch        *b_SingleMuons_z0;   //!
   TBranch        *b_SingleMuons_cov;   //!
   TBranch        *b_SingleMuons_x0_fvtx;   //!
   TBranch        *b_SingleMuons_y0_fvtx;   //!
   TBranch        *b_SingleMuons_z0_fvtx;   //!
   TBranch        *b_SingleMuons_px_fvtx;   //!
   TBranch        *b_SingleMuons_py_fvtx;   //!
   TBranch        *b_SingleMuons_pz_fvtx;   //!
   TBranch        *b_SingleMuons_x0_fvtxmutr;   //!
   TBranch        *b_SingleMuons_y0_fvtxmutr;   //!
   TBranch        *b_SingleMuons_z0_fvtxmutr;   //!
   TBranch        *b_SingleMuons_px_fvtxmutr;   //!
   TBranch        *b_SingleMuons_py_fvtxmutr;   //!
   TBranch        *b_SingleMuons_pz_fvtxmutr;   //!
   TBranch        *b_SingleMuons_nhits_fvtx;   //!
   TBranch        *b_SingleMuons_dphi_fvtx;   //!
   TBranch        *b_SingleMuons_dtheta_fvtx;   //!
   TBranch        *b_SingleMuons_dr_fvtx;   //!
   TBranch        *b_SingleMuons_chi2_fvtx;   //!
   TBranch        *b_SingleMuons_fvtx_strip;   //!
   TBranch        *b_SingleMuons_cov_fvtx;   //!
   TBranch        *b_SingleMuons_cov_fvtxmutr;   //!
   TBranch        *b_SingleMuons_fvtx_charge;   //!
   TBranch        *b_SingleMuons_nfvtx_trks;   //!
   TBranch        *b_SingleMuons_mutoo_trk_index;   //!
   TBranch        *b_SingleMuons_chi2_fvtxmutr;   //!
   TBranch        *b_SingleMuons_dca_phi;   //!
   TBranch        *b_SingleMuons_clusters_size1;   //!
   TBranch        *b_SingleMuons_nfvtx_tracklets_cone;   //!
   TBranch        *b_SingleMuons_nfvtx_tracklets;   //!
   TBranch        *b_SingleMuons_nfvtx_clusters_cone;   //!
   TBranch        *b_SingleMuons_fvtxtrack_id;   //!
   TBranch        *b_SingleMuons_vtx_index;   //!
   TBranch        *b_SingleMuons_n_matchings;   //!
   TBranch        *b_SingleMuons_hit_pattern;   //!
   TBranch        *b_SingleMuons_cov_mutsta1;   //!
   TBranch        *b_SingleMuons_x_fvtxproj;   //!
   TBranch        *b_SingleMuons_y_fvtxproj;   //!
   TBranch        *b_SingleMuons_x_mutproj;   //!
   TBranch        *b_SingleMuons_y_mutproj;   //!
   TBranch        *b_SingleMuons_px_fvtxproj;   //!
   TBranch        *b_SingleMuons_py_fvtxproj;   //!
   TBranch        *b_SingleMuons_px_mutproj;   //!
   TBranch        *b_SingleMuons_py_mutproj;   //!
   TBranch        *b_SingleMuons_dr_fvtxmutr_sigma;   //!
   TBranch        *b_SingleMuons_dphi_fvtxmutr_sigma;   //!
   TBranch        *b_SingleMuons_dpr_fvtxmutr_sigma;   //!
   TBranch        *b_SingleMuons_dpphi_fvtxmutr_sigma;   //!
   TBranch        *b_SingleMuons_maxres_sigma;   //!
   TBranch        *b_SingleMuons_track_id;   //!
   TBranch        *b_SingleMuons_best_fvtxmutr_match;   //!
   TBranch        *b_SingleMuons_is_sfvtx;   //!
   TBranch        *b_SingleMuons_idpanel;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_bbcZ;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_bbcZ_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_vtxX;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_vtxX_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_vtxY;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_vtxY_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_vtxZ;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_vtxZ_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxX;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxX_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxY;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxY_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxZ;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxZ_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxX2;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxY2;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_fvtxZ2;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_Cent;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_Mult_FVTXN;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_Mult_FVTXS;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_Mult_SVX;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_Mult_sFVTXN;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_Mult_sFVTXS;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMean_S;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMean_N;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcRMS_S;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcRMS_N;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMode_S;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMode_N;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcnPeaks_S;   //!
   TBranch        *b_DST_SingleMuonContainer_filtered_Evt_BbcTdcnPeaks_N;   //!
   TBranch        *b_DST_MCSingleMuonFvtxContainer_filtered_nMCSingleMuonFvtxs;   //!
   TBranch        *b_DST_MCSingleMuonFvtxContainer_filtered_MCSingleMuonFvtxs_;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_n_part;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_px;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_py;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_pz;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_ptot;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_x;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_y;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_z;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_pid;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_trk;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_p_pid;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_p_px;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_p_py;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_p_pz;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_p_ptot;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_p_z;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_g_pid;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_g_px;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_g_py;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_g_pz;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_g_ptot;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_g_z;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_pid;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_px;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_py;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_pz;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_ptot;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_z;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_d_n;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_px_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_py_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_pz_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_pid_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_coords_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_trk_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits_fvtx_true;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_trks_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_nomchits_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_dca_r;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_dca_phi;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_dca_z;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits_svx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits_svx_true;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits_mutr_true;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_hits_muid_true;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_x_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_y_fvtx;   //!
   TBranch        *b_MCSingleMuonFvtxs_mc_z_fvtx;   //!

   NewSimv2(TTree *tree=0);
   virtual ~NewSimv2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef NewSimv2_cxx
NewSimv2::NewSimv2(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Simtest.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Simtest.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

NewSimv2::~NewSimv2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NewSimv2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NewSimv2::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void NewSimv2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nSingleMuons", &nSingleMuons, &b_DST_SingleMuonContainer_filtered_nSingleMuons);
   fChain->SetBranchAddress("SingleMuons", &SingleMuons_, &b_DST_SingleMuonContainer_filtered_SingleMuons_);
   fChain->SetBranchAddress("SingleMuons.px", SingleMuons_px, &b_SingleMuons_px);
   fChain->SetBranchAddress("SingleMuons.py", SingleMuons_py, &b_SingleMuons_py);
   fChain->SetBranchAddress("SingleMuons.pz", SingleMuons_pz, &b_SingleMuons_pz);
   fChain->SetBranchAddress("SingleMuons.rapidity", SingleMuons_rapidity, &b_SingleMuons_rapidity);
   fChain->SetBranchAddress("SingleMuons.trhits", SingleMuons_trhits, &b_SingleMuons_trhits);
   fChain->SetBranchAddress("SingleMuons.idhits", SingleMuons_idhits, &b_SingleMuons_idhits);
   fChain->SetBranchAddress("SingleMuons.DG0", SingleMuons_DG0, &b_SingleMuons_DG0);
   fChain->SetBranchAddress("SingleMuons.DDG0", SingleMuons_DDG0, &b_SingleMuons_DDG0);
   fChain->SetBranchAddress("SingleMuons.DS3", SingleMuons_DS3, &b_SingleMuons_DS3);
   fChain->SetBranchAddress("SingleMuons.trchi2", SingleMuons_trchi2, &b_SingleMuons_trchi2);
   fChain->SetBranchAddress("SingleMuons.idchi2", SingleMuons_idchi2, &b_SingleMuons_idchi2);
   fChain->SetBranchAddress("SingleMuons.ntrhits", SingleMuons_ntrhits, &b_SingleMuons_ntrhits);
   fChain->SetBranchAddress("SingleMuons.nidhits", SingleMuons_nidhits, &b_SingleMuons_nidhits);
   fChain->SetBranchAddress("SingleMuons.lastgap", SingleMuons_lastgap, &b_SingleMuons_lastgap);
   fChain->SetBranchAddress("SingleMuons.xst1", SingleMuons_xst1, &b_SingleMuons_xst1);
   fChain->SetBranchAddress("SingleMuons.xst2", SingleMuons_xst2, &b_SingleMuons_xst2);
   fChain->SetBranchAddress("SingleMuons.xst3", SingleMuons_xst3, &b_SingleMuons_xst3);
   fChain->SetBranchAddress("SingleMuons.yst1", SingleMuons_yst1, &b_SingleMuons_yst1);
   fChain->SetBranchAddress("SingleMuons.yst2", SingleMuons_yst2, &b_SingleMuons_yst2);
   fChain->SetBranchAddress("SingleMuons.yst3", SingleMuons_yst3, &b_SingleMuons_yst3);
   fChain->SetBranchAddress("SingleMuons.idx", SingleMuons_idx, &b_SingleMuons_idx);
   fChain->SetBranchAddress("SingleMuons.idy", SingleMuons_idy, &b_SingleMuons_idy);
   fChain->SetBranchAddress("SingleMuons.st1px", SingleMuons_st1px, &b_SingleMuons_st1px);
   fChain->SetBranchAddress("SingleMuons.st1py", SingleMuons_st1py, &b_SingleMuons_st1py);
   fChain->SetBranchAddress("SingleMuons.st1pz", SingleMuons_st1pz, &b_SingleMuons_st1pz);
   fChain->SetBranchAddress("SingleMuons.MUID1D", SingleMuons_MUID1D, &b_SingleMuons_MUID1D);
   fChain->SetBranchAddress("SingleMuons.MUID1S", SingleMuons_MUID1S, &b_SingleMuons_MUID1S);
   fChain->SetBranchAddress("SingleMuons.dca_z", SingleMuons_dca_z, &b_SingleMuons_dca_z);
   fChain->SetBranchAddress("SingleMuons.dca_r", SingleMuons_dca_r, &b_SingleMuons_dca_r);
   fChain->SetBranchAddress("SingleMuons.charge", SingleMuons_charge, &b_SingleMuons_charge);
   fChain->SetBranchAddress("SingleMuons.x0", SingleMuons_x0, &b_SingleMuons_x0);
   fChain->SetBranchAddress("SingleMuons.y0", SingleMuons_y0, &b_SingleMuons_y0);
   fChain->SetBranchAddress("SingleMuons.z0", SingleMuons_z0, &b_SingleMuons_z0);
   fChain->SetBranchAddress("SingleMuons.cov[5][5]", SingleMuons_cov, &b_SingleMuons_cov);
   fChain->SetBranchAddress("SingleMuons.x0_fvtx", SingleMuons_x0_fvtx, &b_SingleMuons_x0_fvtx);
   fChain->SetBranchAddress("SingleMuons.y0_fvtx", SingleMuons_y0_fvtx, &b_SingleMuons_y0_fvtx);
   fChain->SetBranchAddress("SingleMuons.z0_fvtx", SingleMuons_z0_fvtx, &b_SingleMuons_z0_fvtx);
   fChain->SetBranchAddress("SingleMuons.px_fvtx", SingleMuons_px_fvtx, &b_SingleMuons_px_fvtx);
   fChain->SetBranchAddress("SingleMuons.py_fvtx", SingleMuons_py_fvtx, &b_SingleMuons_py_fvtx);
   fChain->SetBranchAddress("SingleMuons.pz_fvtx", SingleMuons_pz_fvtx, &b_SingleMuons_pz_fvtx);
   fChain->SetBranchAddress("SingleMuons.x0_fvtxmutr", SingleMuons_x0_fvtxmutr, &b_SingleMuons_x0_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.y0_fvtxmutr", SingleMuons_y0_fvtxmutr, &b_SingleMuons_y0_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.z0_fvtxmutr", SingleMuons_z0_fvtxmutr, &b_SingleMuons_z0_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.px_fvtxmutr", SingleMuons_px_fvtxmutr, &b_SingleMuons_px_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.py_fvtxmutr", SingleMuons_py_fvtxmutr, &b_SingleMuons_py_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.pz_fvtxmutr", SingleMuons_pz_fvtxmutr, &b_SingleMuons_pz_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.nhits_fvtx", SingleMuons_nhits_fvtx, &b_SingleMuons_nhits_fvtx);
   fChain->SetBranchAddress("SingleMuons.dphi_fvtx", SingleMuons_dphi_fvtx, &b_SingleMuons_dphi_fvtx);
   fChain->SetBranchAddress("SingleMuons.dtheta_fvtx", SingleMuons_dtheta_fvtx, &b_SingleMuons_dtheta_fvtx);
   fChain->SetBranchAddress("SingleMuons.dr_fvtx", SingleMuons_dr_fvtx, &b_SingleMuons_dr_fvtx);
   fChain->SetBranchAddress("SingleMuons.chi2_fvtx", SingleMuons_chi2_fvtx, &b_SingleMuons_chi2_fvtx);
   fChain->SetBranchAddress("SingleMuons.fvtx_strip[4]", SingleMuons_fvtx_strip, &b_SingleMuons_fvtx_strip);
   fChain->SetBranchAddress("SingleMuons.cov_fvtx[5][5]", SingleMuons_cov_fvtx, &b_SingleMuons_cov_fvtx);
   fChain->SetBranchAddress("SingleMuons.cov_fvtxmutr[5][5]", SingleMuons_cov_fvtxmutr, &b_SingleMuons_cov_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.fvtx_charge[4]", SingleMuons_fvtx_charge, &b_SingleMuons_fvtx_charge);
   fChain->SetBranchAddress("SingleMuons.nfvtx_trks", SingleMuons_nfvtx_trks, &b_SingleMuons_nfvtx_trks);
   fChain->SetBranchAddress("SingleMuons.mutoo_trk_index", SingleMuons_mutoo_trk_index, &b_SingleMuons_mutoo_trk_index);
   fChain->SetBranchAddress("SingleMuons.chi2_fvtxmutr", SingleMuons_chi2_fvtxmutr, &b_SingleMuons_chi2_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.dca_phi", SingleMuons_dca_phi, &b_SingleMuons_dca_phi);
   fChain->SetBranchAddress("SingleMuons.clusters_size1", SingleMuons_clusters_size1, &b_SingleMuons_clusters_size1);
   fChain->SetBranchAddress("SingleMuons.nfvtx_tracklets_cone", SingleMuons_nfvtx_tracklets_cone, &b_SingleMuons_nfvtx_tracklets_cone);
   fChain->SetBranchAddress("SingleMuons.nfvtx_tracklets", SingleMuons_nfvtx_tracklets, &b_SingleMuons_nfvtx_tracklets);
   fChain->SetBranchAddress("SingleMuons.nfvtx_clusters_cone", SingleMuons_nfvtx_clusters_cone, &b_SingleMuons_nfvtx_clusters_cone);
   fChain->SetBranchAddress("SingleMuons.fvtxtrack_id", SingleMuons_fvtxtrack_id, &b_SingleMuons_fvtxtrack_id);
   fChain->SetBranchAddress("SingleMuons.vtx_index", SingleMuons_vtx_index, &b_SingleMuons_vtx_index);
   fChain->SetBranchAddress("SingleMuons.n_matchings", SingleMuons_n_matchings, &b_SingleMuons_n_matchings);
   fChain->SetBranchAddress("SingleMuons.hit_pattern", SingleMuons_hit_pattern, &b_SingleMuons_hit_pattern);
   fChain->SetBranchAddress("SingleMuons.cov_mutsta1[5][5]", SingleMuons_cov_mutsta1, &b_SingleMuons_cov_mutsta1);
   fChain->SetBranchAddress("SingleMuons.x_fvtxproj[3]", SingleMuons_x_fvtxproj, &b_SingleMuons_x_fvtxproj);
   fChain->SetBranchAddress("SingleMuons.y_fvtxproj[3]", SingleMuons_y_fvtxproj, &b_SingleMuons_y_fvtxproj);
   fChain->SetBranchAddress("SingleMuons.x_mutproj[3]", SingleMuons_x_mutproj, &b_SingleMuons_x_mutproj);
   fChain->SetBranchAddress("SingleMuons.y_mutproj[3]", SingleMuons_y_mutproj, &b_SingleMuons_y_mutproj);
   fChain->SetBranchAddress("SingleMuons.px_fvtxproj[3]", SingleMuons_px_fvtxproj, &b_SingleMuons_px_fvtxproj);
   fChain->SetBranchAddress("SingleMuons.py_fvtxproj[3]", SingleMuons_py_fvtxproj, &b_SingleMuons_py_fvtxproj);
   fChain->SetBranchAddress("SingleMuons.px_mutproj[3]", SingleMuons_px_mutproj, &b_SingleMuons_px_mutproj);
   fChain->SetBranchAddress("SingleMuons.py_mutproj[3]", SingleMuons_py_mutproj, &b_SingleMuons_py_mutproj);
   fChain->SetBranchAddress("SingleMuons.dr_fvtxmutr_sigma[3]", SingleMuons_dr_fvtxmutr_sigma, &b_SingleMuons_dr_fvtxmutr_sigma);
   fChain->SetBranchAddress("SingleMuons.dphi_fvtxmutr_sigma[3]", SingleMuons_dphi_fvtxmutr_sigma, &b_SingleMuons_dphi_fvtxmutr_sigma);
   fChain->SetBranchAddress("SingleMuons.dpr_fvtxmutr_sigma[3]", SingleMuons_dpr_fvtxmutr_sigma, &b_SingleMuons_dpr_fvtxmutr_sigma);
   fChain->SetBranchAddress("SingleMuons.dpphi_fvtxmutr_sigma[3]", SingleMuons_dpphi_fvtxmutr_sigma, &b_SingleMuons_dpphi_fvtxmutr_sigma);
   fChain->SetBranchAddress("SingleMuons.maxres_sigma", SingleMuons_maxres_sigma, &b_SingleMuons_maxres_sigma);
   fChain->SetBranchAddress("SingleMuons.track_id", SingleMuons_track_id, &b_SingleMuons_track_id);
   fChain->SetBranchAddress("SingleMuons.best_fvtxmutr_match", SingleMuons_best_fvtxmutr_match, &b_SingleMuons_best_fvtxmutr_match);
   fChain->SetBranchAddress("SingleMuons.is_sfvtx", SingleMuons_is_sfvtx, &b_SingleMuons_is_sfvtx);
   fChain->SetBranchAddress("SingleMuons.idpanel", SingleMuons_idpanel, &b_SingleMuons_idpanel);
   fChain->SetBranchAddress("Evt_bbcZ", &Evt_bbcZ, &b_DST_SingleMuonContainer_filtered_Evt_bbcZ);
   fChain->SetBranchAddress("Evt_bbcZ_Err", &Evt_bbcZ_Err, &b_DST_SingleMuonContainer_filtered_Evt_bbcZ_Err);
   fChain->SetBranchAddress("Evt_vtxX", &Evt_vtxX, &b_DST_SingleMuonContainer_filtered_Evt_vtxX);
   fChain->SetBranchAddress("Evt_vtxX_Err", &Evt_vtxX_Err, &b_DST_SingleMuonContainer_filtered_Evt_vtxX_Err);
   fChain->SetBranchAddress("Evt_vtxY", &Evt_vtxY, &b_DST_SingleMuonContainer_filtered_Evt_vtxY);
   fChain->SetBranchAddress("Evt_vtxY_Err", &Evt_vtxY_Err, &b_DST_SingleMuonContainer_filtered_Evt_vtxY_Err);
   fChain->SetBranchAddress("Evt_vtxZ", &Evt_vtxZ, &b_DST_SingleMuonContainer_filtered_Evt_vtxZ);
   fChain->SetBranchAddress("Evt_vtxZ_Err", &Evt_vtxZ_Err, &b_DST_SingleMuonContainer_filtered_Evt_vtxZ_Err);
   fChain->SetBranchAddress("Evt_fvtxX", &Evt_fvtxX, &b_DST_SingleMuonContainer_filtered_Evt_fvtxX);
   fChain->SetBranchAddress("Evt_fvtxX_Err", &Evt_fvtxX_Err, &b_DST_SingleMuonContainer_filtered_Evt_fvtxX_Err);
   fChain->SetBranchAddress("Evt_fvtxY", &Evt_fvtxY, &b_DST_SingleMuonContainer_filtered_Evt_fvtxY);
   fChain->SetBranchAddress("Evt_fvtxY_Err", &Evt_fvtxY_Err, &b_DST_SingleMuonContainer_filtered_Evt_fvtxY_Err);
   fChain->SetBranchAddress("Evt_fvtxZ", &Evt_fvtxZ, &b_DST_SingleMuonContainer_filtered_Evt_fvtxZ);
   fChain->SetBranchAddress("Evt_fvtxZ_Err", &Evt_fvtxZ_Err, &b_DST_SingleMuonContainer_filtered_Evt_fvtxZ_Err);
   fChain->SetBranchAddress("Evt_fvtxX2", &Evt_fvtxX2, &b_DST_SingleMuonContainer_filtered_Evt_fvtxX2);
   fChain->SetBranchAddress("Evt_fvtxY2", &Evt_fvtxY2, &b_DST_SingleMuonContainer_filtered_Evt_fvtxY2);
   fChain->SetBranchAddress("Evt_fvtxZ2", &Evt_fvtxZ2, &b_DST_SingleMuonContainer_filtered_Evt_fvtxZ2);
   fChain->SetBranchAddress("Evt_Cent", &Evt_Cent, &b_DST_SingleMuonContainer_filtered_Evt_Cent);
   fChain->SetBranchAddress("Evt_Mult_FVTXN", &Evt_Mult_FVTXN, &b_DST_SingleMuonContainer_filtered_Evt_Mult_FVTXN);
   fChain->SetBranchAddress("Evt_Mult_FVTXS", &Evt_Mult_FVTXS, &b_DST_SingleMuonContainer_filtered_Evt_Mult_FVTXS);
   fChain->SetBranchAddress("Evt_Mult_SVX", &Evt_Mult_SVX, &b_DST_SingleMuonContainer_filtered_Evt_Mult_SVX);
   fChain->SetBranchAddress("Evt_Mult_sFVTXN", &Evt_Mult_sFVTXN, &b_DST_SingleMuonContainer_filtered_Evt_Mult_sFVTXN);
   fChain->SetBranchAddress("Evt_Mult_sFVTXS", &Evt_Mult_sFVTXS, &b_DST_SingleMuonContainer_filtered_Evt_Mult_sFVTXS);
   fChain->SetBranchAddress("Evt_BbcTdcMean_S", &Evt_BbcTdcMean_S, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMean_S);
   fChain->SetBranchAddress("Evt_BbcTdcMean_N", &Evt_BbcTdcMean_N, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMean_N);
   fChain->SetBranchAddress("Evt_BbcTdcRMS_S", &Evt_BbcTdcRMS_S, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcRMS_S);
   fChain->SetBranchAddress("Evt_BbcTdcRMS_N", &Evt_BbcTdcRMS_N, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcRMS_N);
   fChain->SetBranchAddress("Evt_BbcTdcMode_S", &Evt_BbcTdcMode_S, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMode_S);
   fChain->SetBranchAddress("Evt_BbcTdcMode_N", &Evt_BbcTdcMode_N, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcMode_N);
   fChain->SetBranchAddress("Evt_BbcTdcnPeaks_S", &Evt_BbcTdcnPeaks_S, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcnPeaks_S);
   fChain->SetBranchAddress("Evt_BbcTdcnPeaks_N", &Evt_BbcTdcnPeaks_N, &b_DST_SingleMuonContainer_filtered_Evt_BbcTdcnPeaks_N);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_DST/MCSingleMuonFvtxContainer_filtered_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_DST/MCSingleMuonFvtxContainer_filtered_fBits);
   fChain->SetBranchAddress("nMCSingleMuonFvtxs", &nMCSingleMuonFvtxs, &b_DST_MCSingleMuonFvtxContainer_filtered_nMCSingleMuonFvtxs);
   fChain->SetBranchAddress("MCSingleMuonFvtxs", &MCSingleMuonFvtxs_, &b_DST_MCSingleMuonFvtxContainer_filtered_MCSingleMuonFvtxs_);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_n_part", MCSingleMuonFvtxs_mc_n_part, &b_MCSingleMuonFvtxs_mc_n_part);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_px", MCSingleMuonFvtxs_mc_px, &b_MCSingleMuonFvtxs_mc_px);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_py", MCSingleMuonFvtxs_mc_py, &b_MCSingleMuonFvtxs_mc_py);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_pz", MCSingleMuonFvtxs_mc_pz, &b_MCSingleMuonFvtxs_mc_pz);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_ptot", MCSingleMuonFvtxs_mc_ptot, &b_MCSingleMuonFvtxs_mc_ptot);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_x", MCSingleMuonFvtxs_mc_x, &b_MCSingleMuonFvtxs_mc_x);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_y", MCSingleMuonFvtxs_mc_y, &b_MCSingleMuonFvtxs_mc_y);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_z", MCSingleMuonFvtxs_mc_z, &b_MCSingleMuonFvtxs_mc_z);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_pid", MCSingleMuonFvtxs_mc_pid, &b_MCSingleMuonFvtxs_mc_pid);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits", MCSingleMuonFvtxs_mc_hits, &b_MCSingleMuonFvtxs_mc_hits);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_trk", MCSingleMuonFvtxs_mc_trk, &b_MCSingleMuonFvtxs_mc_trk);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_p_pid", MCSingleMuonFvtxs_mc_p_pid, &b_MCSingleMuonFvtxs_mc_p_pid);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_p_px", MCSingleMuonFvtxs_mc_p_px, &b_MCSingleMuonFvtxs_mc_p_px);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_p_py", MCSingleMuonFvtxs_mc_p_py, &b_MCSingleMuonFvtxs_mc_p_py);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_p_pz", MCSingleMuonFvtxs_mc_p_pz, &b_MCSingleMuonFvtxs_mc_p_pz);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_p_ptot", MCSingleMuonFvtxs_mc_p_ptot, &b_MCSingleMuonFvtxs_mc_p_ptot);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_p_z", MCSingleMuonFvtxs_mc_p_z, &b_MCSingleMuonFvtxs_mc_p_z);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_g_pid", MCSingleMuonFvtxs_mc_g_pid, &b_MCSingleMuonFvtxs_mc_g_pid);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_g_px", MCSingleMuonFvtxs_mc_g_px, &b_MCSingleMuonFvtxs_mc_g_px);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_g_py", MCSingleMuonFvtxs_mc_g_py, &b_MCSingleMuonFvtxs_mc_g_py);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_g_pz", MCSingleMuonFvtxs_mc_g_pz, &b_MCSingleMuonFvtxs_mc_g_pz);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_g_ptot", MCSingleMuonFvtxs_mc_g_ptot, &b_MCSingleMuonFvtxs_mc_g_ptot);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_g_z", MCSingleMuonFvtxs_mc_g_z, &b_MCSingleMuonFvtxs_mc_g_z);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_pid", MCSingleMuonFvtxs_mc_d_pid, &b_MCSingleMuonFvtxs_mc_d_pid);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_px", MCSingleMuonFvtxs_mc_d_px, &b_MCSingleMuonFvtxs_mc_d_px);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_py", MCSingleMuonFvtxs_mc_d_py, &b_MCSingleMuonFvtxs_mc_d_py);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_pz", MCSingleMuonFvtxs_mc_d_pz, &b_MCSingleMuonFvtxs_mc_d_pz);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_ptot", MCSingleMuonFvtxs_mc_d_ptot, &b_MCSingleMuonFvtxs_mc_d_ptot);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_z", MCSingleMuonFvtxs_mc_d_z, &b_MCSingleMuonFvtxs_mc_d_z);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_d_n", MCSingleMuonFvtxs_mc_d_n, &b_MCSingleMuonFvtxs_mc_d_n);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_px_fvtx", MCSingleMuonFvtxs_mc_px_fvtx, &b_MCSingleMuonFvtxs_mc_px_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_py_fvtx", MCSingleMuonFvtxs_mc_py_fvtx, &b_MCSingleMuonFvtxs_mc_py_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_pz_fvtx", MCSingleMuonFvtxs_mc_pz_fvtx, &b_MCSingleMuonFvtxs_mc_pz_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_pid_fvtx", MCSingleMuonFvtxs_mc_pid_fvtx, &b_MCSingleMuonFvtxs_mc_pid_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits_fvtx", MCSingleMuonFvtxs_mc_hits_fvtx, &b_MCSingleMuonFvtxs_mc_hits_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_coords_fvtx", MCSingleMuonFvtxs_mc_coords_fvtx, &b_MCSingleMuonFvtxs_mc_coords_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_trk_fvtx", MCSingleMuonFvtxs_mc_trk_fvtx, &b_MCSingleMuonFvtxs_mc_trk_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits_fvtx_true", MCSingleMuonFvtxs_mc_hits_fvtx_true, &b_MCSingleMuonFvtxs_mc_hits_fvtx_true);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_trks_fvtx", MCSingleMuonFvtxs_mc_trks_fvtx, &b_MCSingleMuonFvtxs_mc_trks_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_nomchits_fvtx", MCSingleMuonFvtxs_mc_nomchits_fvtx, &b_MCSingleMuonFvtxs_mc_nomchits_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_dca_r", MCSingleMuonFvtxs_mc_dca_r, &b_MCSingleMuonFvtxs_mc_dca_r);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_dca_phi", MCSingleMuonFvtxs_mc_dca_phi, &b_MCSingleMuonFvtxs_mc_dca_phi);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_dca_z", MCSingleMuonFvtxs_mc_dca_z, &b_MCSingleMuonFvtxs_mc_dca_z);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits_svx", MCSingleMuonFvtxs_mc_hits_svx, &b_MCSingleMuonFvtxs_mc_hits_svx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits_svx_true", MCSingleMuonFvtxs_mc_hits_svx_true, &b_MCSingleMuonFvtxs_mc_hits_svx_true);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits_mutr_true", MCSingleMuonFvtxs_mc_hits_mutr_true, &b_MCSingleMuonFvtxs_mc_hits_mutr_true);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_hits_muid_true", MCSingleMuonFvtxs_mc_hits_muid_true, &b_MCSingleMuonFvtxs_mc_hits_muid_true);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_x_fvtx", MCSingleMuonFvtxs_mc_x_fvtx, &b_MCSingleMuonFvtxs_mc_x_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_y_fvtx", MCSingleMuonFvtxs_mc_y_fvtx, &b_MCSingleMuonFvtxs_mc_y_fvtx);
   fChain->SetBranchAddress("MCSingleMuonFvtxs.mc_z_fvtx", MCSingleMuonFvtxs_mc_z_fvtx, &b_MCSingleMuonFvtxs_mc_z_fvtx);
   Notify();
}

Bool_t NewSimv2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NewSimv2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NewSimv2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NewSimv2_cxx
