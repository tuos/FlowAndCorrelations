//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 16 12:20:30 2022 by ROOT version 5.34/36
// from TTree T/titled by PHOOL
// found on file: pDSTall.root
//////////////////////////////////////////////////////////

#ifndef AllFit_h
#define AllFit_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxCompactEPArray = 20;
   const Int_t kMaxSingleMuons = 353;

class AllFit {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //CompactEventPlane *DST/COMPACTEPTREE;
   Int_t           evt_cent;
   Float_t         evt_bbcz;
   Int_t           evt_trig;
   Int_t           CompactEPArray_;
   Int_t           CompactEPArray_idcode[kMaxCompactEPArray];   //[CompactEPArray_]
   Float_t         CompactEPArray_psi[kMaxCompactEPArray];   //[CompactEPArray_]
 //SingleMuonContainer_Compact_v1 *DST/SingleMuonContainer_Compact;
   UInt_t          nSingleMuons;
   Int_t           SingleMuons_;
   Short_t         SingleMuons_vtx_index[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_px[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_py[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_pz[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_rapidity[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_charge[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_lastgap[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_MUID1D[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_MUID1S[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dca_z[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dca_r[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_dca_phi[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_best_fvtxmutr_match[kMaxSingleMuons];   //[SingleMuons_]
   Bool_t          SingleMuons_is_sfvtx[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_chi2_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   UShort_t        SingleMuons_hit_pattern[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_x0_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_y0_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_z0_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_px_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_py_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_pz_fvtxmutr[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_DG0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_DDG0[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_trchi2[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         SingleMuons_idchi2[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_ntrhits[kMaxSingleMuons];   //[SingleMuons_]
   Short_t         SingleMuons_nidhits[kMaxSingleMuons];   //[SingleMuons_]
   Float_t         Evt_fvtxX;
   Float_t         Evt_fvtxX_Err;
   Float_t         Evt_fvtxY;
   Float_t         Evt_fvtxY_Err;
   Float_t         Evt_fvtxZ;
   Float_t         Evt_fvtxZ_Err;
   Float_t         Evt_Cent;
   Int_t           Evt_Mult_FVTXN;
   Int_t           Evt_Mult_FVTXS;
   Int_t           Evt_Mult_SVX;
   Int_t           Evt_Mult_sFVTXN;
   Int_t           Evt_Mult_sFVTXS;
 //EventHeaderv3   *DST/EventHeader;
   Int_t           EvtSequence;
   Int_t           EvtType;
   Long_t          TimeStamp;
 //set<unsigned int> badpackets;
 //TrigLvl1v3      *DST/TrigLvl1;
   UInt_t          lvl1_trigraw;
   UInt_t          lvl1_triglive;
   UInt_t          lvl1_trigscaled;
   UInt_t          lvl1_clock_cross;
   UInt_t          lvl1_rbits[5];
   UInt_t          beamclk[2];
 //SyncObjectv2    *DST/Sync;
   Int_t           eventcounter;
   Int_t           eventnumber;
   Int_t           runnumber;
   Int_t           segmentnumber;

   // List of branches
   TBranch        *b_DST_COMPACTEPTREE_evt_cent;   //!
   TBranch        *b_DST_COMPACTEPTREE_evt_bbcz;   //!
   TBranch        *b_DST_COMPACTEPTREE_evt_trig;   //!
   TBranch        *b_DST_COMPACTEPTREE_CompactEPArray_;   //!
   TBranch        *b_CompactEPArray_idcode;   //!
   TBranch        *b_CompactEPArray_psi;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_nSingleMuons;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_SingleMuons_;   //!
   TBranch        *b_SingleMuons_vtx_index;   //!
   TBranch        *b_SingleMuons_px;   //!
   TBranch        *b_SingleMuons_py;   //!
   TBranch        *b_SingleMuons_pz;   //!
   TBranch        *b_SingleMuons_rapidity;   //!
   TBranch        *b_SingleMuons_charge;   //!
   TBranch        *b_SingleMuons_lastgap;   //!
   TBranch        *b_SingleMuons_MUID1D;   //!
   TBranch        *b_SingleMuons_MUID1S;   //!
   TBranch        *b_SingleMuons_dca_z;   //!
   TBranch        *b_SingleMuons_dca_r;   //!
   TBranch        *b_SingleMuons_dca_phi;   //!
   TBranch        *b_SingleMuons_best_fvtxmutr_match;   //!
   TBranch        *b_SingleMuons_is_sfvtx;   //!
   TBranch        *b_SingleMuons_chi2_fvtxmutr;   //!
   TBranch        *b_SingleMuons_hit_pattern;   //!
   TBranch        *b_SingleMuons_x0_fvtxmutr;   //!
   TBranch        *b_SingleMuons_y0_fvtxmutr;   //!
   TBranch        *b_SingleMuons_z0_fvtxmutr;   //!
   TBranch        *b_SingleMuons_px_fvtxmutr;   //!
   TBranch        *b_SingleMuons_py_fvtxmutr;   //!
   TBranch        *b_SingleMuons_pz_fvtxmutr;   //!
   TBranch        *b_SingleMuons_DG0;   //!
   TBranch        *b_SingleMuons_DDG0;   //!
   TBranch        *b_SingleMuons_trchi2;   //!
   TBranch        *b_SingleMuons_idchi2;   //!
   TBranch        *b_SingleMuons_ntrhits;   //!
   TBranch        *b_SingleMuons_nidhits;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_fvtxX;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_fvtxX_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_fvtxY;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_fvtxY_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_fvtxZ;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_fvtxZ_Err;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_Cent;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_Mult_FVTXN;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_Mult_FVTXS;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_Mult_SVX;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_Mult_sFVTXN;   //!
   TBranch        *b_DST_SingleMuonContainer_Compact_Evt_Mult_sFVTXS;   //!
   TBranch        *b_DST_EventHeader_EvtSequence;   //!
   TBranch        *b_DST_EventHeader_EvtType;   //!
   TBranch        *b_DST_EventHeader_TimeStamp;   //!
   TBranch        *b_DST_TrigLvl1_lvl1_trigraw;   //!
   TBranch        *b_DST_TrigLvl1_lvl1_triglive;   //!
   TBranch        *b_DST_TrigLvl1_lvl1_trigscaled;   //!
   TBranch        *b_DST_TrigLvl1_lvl1_clock_cross;   //!
   TBranch        *b_DST_TrigLvl1_lvl1_rbits;   //!
   TBranch        *b_DST_TrigLvl1_beamclk;   //!
   TBranch        *b_DST_Sync_eventcounter;   //!
   TBranch        *b_DST_Sync_eventnumber;   //!
   TBranch        *b_DST_Sync_runnumber;   //!
   TBranch        *b_DST_Sync_segmentnumber;   //!

   AllFit(TTree *tree=0);
   virtual ~AllFit();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AllFit_cxx
AllFit::AllFit(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("414635_7.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("414635_7.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

AllFit::~AllFit()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AllFit::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AllFit::LoadTree(Long64_t entry)
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

void AllFit::Init(TTree *tree)
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

   fChain->SetBranchAddress("evt_cent", &evt_cent, &b_DST_COMPACTEPTREE_evt_cent);
   fChain->SetBranchAddress("evt_bbcz", &evt_bbcz, &b_DST_COMPACTEPTREE_evt_bbcz);
   fChain->SetBranchAddress("evt_trig", &evt_trig, &b_DST_COMPACTEPTREE_evt_trig);
   fChain->SetBranchAddress("CompactEPArray", &CompactEPArray_, &b_DST_COMPACTEPTREE_CompactEPArray_);
   fChain->SetBranchAddress("CompactEPArray.idcode", CompactEPArray_idcode, &b_CompactEPArray_idcode);
   fChain->SetBranchAddress("CompactEPArray.psi", CompactEPArray_psi, &b_CompactEPArray_psi);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_DST/SingleMuonContainer_Compact_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_DST/SingleMuonContainer_Compact_fBits);
   fChain->SetBranchAddress("nSingleMuons", &nSingleMuons, &b_DST_SingleMuonContainer_Compact_nSingleMuons);
   fChain->SetBranchAddress("SingleMuons", &SingleMuons_, &b_DST_SingleMuonContainer_Compact_SingleMuons_);
   fChain->SetBranchAddress("SingleMuons.vtx_index", SingleMuons_vtx_index, &b_SingleMuons_vtx_index);
   fChain->SetBranchAddress("SingleMuons.px", SingleMuons_px, &b_SingleMuons_px);
   fChain->SetBranchAddress("SingleMuons.py", SingleMuons_py, &b_SingleMuons_py);
   fChain->SetBranchAddress("SingleMuons.pz", SingleMuons_pz, &b_SingleMuons_pz);
   fChain->SetBranchAddress("SingleMuons.rapidity", SingleMuons_rapidity, &b_SingleMuons_rapidity);
   fChain->SetBranchAddress("SingleMuons.charge", SingleMuons_charge, &b_SingleMuons_charge);
   fChain->SetBranchAddress("SingleMuons.lastgap", SingleMuons_lastgap, &b_SingleMuons_lastgap);
   fChain->SetBranchAddress("SingleMuons.MUID1D", SingleMuons_MUID1D, &b_SingleMuons_MUID1D);
   fChain->SetBranchAddress("SingleMuons.MUID1S", SingleMuons_MUID1S, &b_SingleMuons_MUID1S);
   fChain->SetBranchAddress("SingleMuons.dca_z", SingleMuons_dca_z, &b_SingleMuons_dca_z);
   fChain->SetBranchAddress("SingleMuons.dca_r", SingleMuons_dca_r, &b_SingleMuons_dca_r);
   fChain->SetBranchAddress("SingleMuons.dca_phi", SingleMuons_dca_phi, &b_SingleMuons_dca_phi);
   fChain->SetBranchAddress("SingleMuons.best_fvtxmutr_match", SingleMuons_best_fvtxmutr_match, &b_SingleMuons_best_fvtxmutr_match);
   fChain->SetBranchAddress("SingleMuons.is_sfvtx", SingleMuons_is_sfvtx, &b_SingleMuons_is_sfvtx);
   fChain->SetBranchAddress("SingleMuons.chi2_fvtxmutr", SingleMuons_chi2_fvtxmutr, &b_SingleMuons_chi2_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.hit_pattern", SingleMuons_hit_pattern, &b_SingleMuons_hit_pattern);
   fChain->SetBranchAddress("SingleMuons.x0_fvtxmutr", SingleMuons_x0_fvtxmutr, &b_SingleMuons_x0_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.y0_fvtxmutr", SingleMuons_y0_fvtxmutr, &b_SingleMuons_y0_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.z0_fvtxmutr", SingleMuons_z0_fvtxmutr, &b_SingleMuons_z0_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.px_fvtxmutr", SingleMuons_px_fvtxmutr, &b_SingleMuons_px_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.py_fvtxmutr", SingleMuons_py_fvtxmutr, &b_SingleMuons_py_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.pz_fvtxmutr", SingleMuons_pz_fvtxmutr, &b_SingleMuons_pz_fvtxmutr);
   fChain->SetBranchAddress("SingleMuons.DG0", SingleMuons_DG0, &b_SingleMuons_DG0);
   fChain->SetBranchAddress("SingleMuons.DDG0", SingleMuons_DDG0, &b_SingleMuons_DDG0);
   fChain->SetBranchAddress("SingleMuons.trchi2", SingleMuons_trchi2, &b_SingleMuons_trchi2);
   fChain->SetBranchAddress("SingleMuons.idchi2", SingleMuons_idchi2, &b_SingleMuons_idchi2);
   fChain->SetBranchAddress("SingleMuons.ntrhits", SingleMuons_ntrhits, &b_SingleMuons_ntrhits);
   fChain->SetBranchAddress("SingleMuons.nidhits", SingleMuons_nidhits, &b_SingleMuons_nidhits);
   fChain->SetBranchAddress("Evt_fvtxX", &Evt_fvtxX, &b_DST_SingleMuonContainer_Compact_Evt_fvtxX);
   fChain->SetBranchAddress("Evt_fvtxX_Err", &Evt_fvtxX_Err, &b_DST_SingleMuonContainer_Compact_Evt_fvtxX_Err);
   fChain->SetBranchAddress("Evt_fvtxY", &Evt_fvtxY, &b_DST_SingleMuonContainer_Compact_Evt_fvtxY);
   fChain->SetBranchAddress("Evt_fvtxY_Err", &Evt_fvtxY_Err, &b_DST_SingleMuonContainer_Compact_Evt_fvtxY_Err);
   fChain->SetBranchAddress("Evt_fvtxZ", &Evt_fvtxZ, &b_DST_SingleMuonContainer_Compact_Evt_fvtxZ);
   fChain->SetBranchAddress("Evt_fvtxZ_Err", &Evt_fvtxZ_Err, &b_DST_SingleMuonContainer_Compact_Evt_fvtxZ_Err);
   fChain->SetBranchAddress("Evt_Cent", &Evt_Cent, &b_DST_SingleMuonContainer_Compact_Evt_Cent);
   fChain->SetBranchAddress("Evt_Mult_FVTXN", &Evt_Mult_FVTXN, &b_DST_SingleMuonContainer_Compact_Evt_Mult_FVTXN);
   fChain->SetBranchAddress("Evt_Mult_FVTXS", &Evt_Mult_FVTXS, &b_DST_SingleMuonContainer_Compact_Evt_Mult_FVTXS);
   fChain->SetBranchAddress("Evt_Mult_SVX", &Evt_Mult_SVX, &b_DST_SingleMuonContainer_Compact_Evt_Mult_SVX);
   fChain->SetBranchAddress("Evt_Mult_sFVTXN", &Evt_Mult_sFVTXN, &b_DST_SingleMuonContainer_Compact_Evt_Mult_sFVTXN);
   fChain->SetBranchAddress("Evt_Mult_sFVTXS", &Evt_Mult_sFVTXS, &b_DST_SingleMuonContainer_Compact_Evt_Mult_sFVTXS);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_DST/EventHeader_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_DST/EventHeader_fBits);
   fChain->SetBranchAddress("EvtSequence", &EvtSequence, &b_DST_EventHeader_EvtSequence);
   fChain->SetBranchAddress("EvtType", &EvtType, &b_DST_EventHeader_EvtType);
   fChain->SetBranchAddress("TimeStamp", &TimeStamp, &b_DST_EventHeader_TimeStamp);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_DST/TrigLvl1_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_DST/TrigLvl1_fBits);
   fChain->SetBranchAddress("lvl1_trigraw", &lvl1_trigraw, &b_DST_TrigLvl1_lvl1_trigraw);
   fChain->SetBranchAddress("lvl1_triglive", &lvl1_triglive, &b_DST_TrigLvl1_lvl1_triglive);
   fChain->SetBranchAddress("lvl1_trigscaled", &lvl1_trigscaled, &b_DST_TrigLvl1_lvl1_trigscaled);
   fChain->SetBranchAddress("lvl1_clock_cross", &lvl1_clock_cross, &b_DST_TrigLvl1_lvl1_clock_cross);
   fChain->SetBranchAddress("lvl1_rbits[5]", lvl1_rbits, &b_DST_TrigLvl1_lvl1_rbits);
   fChain->SetBranchAddress("beamclk[2]", beamclk, &b_DST_TrigLvl1_beamclk);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_DST/Sync_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_DST/Sync_fBits);
   fChain->SetBranchAddress("eventcounter", &eventcounter, &b_DST_Sync_eventcounter);
   fChain->SetBranchAddress("eventnumber", &eventnumber, &b_DST_Sync_eventnumber);
   fChain->SetBranchAddress("runnumber", &runnumber, &b_DST_Sync_runnumber);
   fChain->SetBranchAddress("segmentnumber", &segmentnumber, &b_DST_Sync_segmentnumber);
   Notify();
}

Bool_t AllFit::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AllFit::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AllFit::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AllFit_cxx
