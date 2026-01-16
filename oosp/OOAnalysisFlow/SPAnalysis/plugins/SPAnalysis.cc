// -*- C++ -*-
//
// Package:    OOAnalysisFlow/SPAnalsis
// Class:      SPAnalsis
//
/**\class SPAnalsis SPAnalsis.cc OOAnalysisFlow/SPAnalsis/plugins/SPAnalsis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Thu, 01 May 2025 12:40:17 GMT
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "OOAnalysisFlow/SPAnalysis/plugins/SPAnalysis.h"


using namespace std;
using namespace reco;
using namespace edm;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;

class SPAnalysis : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit SPAnalysis(const edm::ParameterSet&);
  ~SPAnalysis() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT< edm::View< pat::PackedCandidate > > tracksToken_;
  edm::EDGetTokenT< pat::PackedCandidateCollection > pfToken_;
  edm::EDGetTokenT< reco::VertexCollection > vertexToken_;
  edm::EDGetTokenT<reco::GenParticleCollection> genTracksToken_;
  //edm::EDGetTokenT< edm::View< pat::PackedCandidate > > tracksTokenMiniAOD_;
  //edm::EDGetTokenT< edm::ValueMap< float > > chi2Map_;
//  edm::EDGetTokenT< reco::Centrality > centralityTag_;
  edm::EDGetTokenT< int > centralityBinTag_;
  //edm::EDGetTokenT< std::vector<reco::EvtPlane> > eventPlane_;
  bool isPixelTracks_;

  double etaCutHF_;
  double etaCutTrk_;
  double etaCutTrkNonC_;

  edm::Service<TFileService> fs;


  TComplex QhfPlus[nCentBin][nHarmonics];
  TComplex QhfMinus[nCentBin][nHarmonics];
  TComplex QhfMinusPlus[nCentBin][nHarmonics];
  TComplex QDEMinusPlus[nCentBin][nHarmonics];
  TComplex QtrkPtPlus[nCentBin][nHarmonics][nPtBin];
  TComplex QtrkPtMinus[nCentBin][nHarmonics][nPtBin];
  TComplex QtrkMid[nCentBin][nHarmonics];
  TComplex QtrkPtMid[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnPlusQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnMinusQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hQnPlusQnMinusStar[nCentBin][nHarmonics]; //Minus:A; Plus:B; Mid:C
  TH1D* hQnMinusQnPlusStar[nCentBin][nHarmonics];
  TH1D* hQnMinusQnMidStar[nCentBin][nHarmonics];
  TH1D* hQnPlusQnMidStar[nCentBin][nHarmonics];
  TH1D* hqnQnPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnQnMinusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hqnQnMinusPlusStar[nCentBin][nHarmonics][nPtBin];
  TH1D* hQnMinusPlusQnDEStar[nCentBin][nHarmonics];
  TH1D* hQnMinusPlusQnMidStar[nCentBin][nHarmonics];
  TH1D* hQnDEQnMidStar[nCentBin][nHarmonics];

  TH1D* hMeanPt[nCentBin][nPtBin];
  TH1D* hMeanPtMid[nCentBin][nPtBin];
  TH1D* hPtCent[nCentBin];
  TH1D* hPtCentCorr[nCentBin];
  TH1D *histcent;


  double sumwPlus[nCentBin];
  double sumwMinus[nCentBin];
  double sumwMinusPlus[nCentBin];
  double sumwDEMinusPlus[nCentBin];
  double sumwPlusTrk[nCentBin][nPtBin];
  double sumwMinusTrk[nCentBin][nPtBin];
  double sumwMidTrk[nCentBin];
  double sumwMidTrkPt[nCentBin][nPtBin];

  // ## track selection ##
  double etamin_;    //min eta of the tracks
  double etamax_;    //max eta of the tracks
  double ptmin_;     //min pt of the tracks
  double ptmax_;     //max pt of the tracks
  double dzdzerror_; //cut on dz/dzerror of the tracks
  double d0d0error_; //cut on d0/d0error of the tracks
  double pterrorpt_; //cut on pterror/pt of the tracks
  // ## vertex selection ##
  double  minvz_;         //minimum z distance wrt (0,0,0) for the vertex
  double  maxvz_;         //maximum z distance wrt (0,0,0) for the vertex
  // ## file acc & eff & fake ##
  bool cweight_; //use particle weight to correct from acc X eff
  edm::InputTag fname_;   //file name that contains acc X eff corrections
  TFile* feff_;                 //TFile that contains 2D histos (pt, eta) with eff/(1-fak)
  //std::vector<TH2D*> heff_;     //TH2D histograms used for correction
  TH3F* hEff_3D;
  TH3F* hFak_3D;
  TH3F* hMul_3D;
  TH3F* hSec_3D;
  bool doOO_;
  bool doNeNe_;
  bool runreco_;
  bool rungen_;

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SPAnalysis::SPAnalysis(const edm::ParameterSet& iConfig) :
      tracksToken_( consumes< edm::View< pat::PackedCandidate > >( iConfig.getParameter< edm::InputTag >( "tracks" ) ) ),
      pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
      vertexToken_( consumes< reco::VertexCollection >( iConfig.getParameter< edm:: InputTag >( "vertices" ) ) ),
      genTracksToken_(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genTracks"))),
      etaCutHF_(iConfig.getUntrackedParameter<double>("etaCutHF")),
      etaCutTrk_(iConfig.getUntrackedParameter<double>("etaCutTrk")),
      etaCutTrkNonC_(iConfig.getUntrackedParameter<double>("etaCutTrkNonC")),

  //track selection
  etamin_(iConfig.getUntrackedParameter<double>("etamin")),
  etamax_(iConfig.getUntrackedParameter<double>("etamax")),
  ptmin_(iConfig.getUntrackedParameter<double>("ptmin")),
  ptmax_(iConfig.getUntrackedParameter<double>("ptmax")),
  dzdzerror_(iConfig.getUntrackedParameter<double>("dzdzerror")),
  d0d0error_(iConfig.getUntrackedParameter<double>("d0d0error")),
  pterrorpt_(iConfig.getUntrackedParameter<double>("pterrorpt")),
  //vertex selection
  minvz_(iConfig.getUntrackedParameter<double>("minvz")),
  maxvz_(iConfig.getUntrackedParameter<double>("maxvz")),
  //file acc & eff & fake
  cweight_(iConfig.getUntrackedParameter<bool>("cweight")),
  fname_(iConfig.getUntrackedParameter<edm::InputTag>("fname")),
  doOO_(iConfig.getUntrackedParameter<bool>("doOO")),
  doNeNe_(iConfig.getUntrackedParameter<bool>("doNeNe")),
  runreco_(iConfig.getUntrackedParameter<bool>("runreco")),
  rungen_(iConfig.getUntrackedParameter<bool>("rungen"))
{

   TString filename(fname_.label().c_str());
   feff_ = 0x0;
   if(cweight_ && !filename.IsNull()){
      edm::FileInPath fip(Form("OOAnalysisFlow/SPAnalysis/data/%s",filename.Data()));
      feff_ = new TFile(fip.fullPath().c_str(),"READ");
      //heff_.resize(feff_->GetNkeys());
      //for(unsigned short ik = 0; ik < heff_.size(); ++ik)
      //{
         //heff_[ik] = (TH2D*) feff_->Get(feff_->GetListOfKeys()->At(ik)->GetName());
         //cout<<"hist eff: "<<feff_->GetListOfKeys()->At(ik)->GetName()<<endl;
      //}
      
      hEff_3D = (TH3F*)feff_->Get("hEff_3D");
      hFak_3D = (TH3F*)feff_->Get("hFak_3D");
      hMul_3D = (TH3F*)feff_->Get("hMul_3D");
      hSec_3D = (TH3F*)feff_->Get("hSec_3D");      

      feff_->Close();

   }

  TH1::SetDefaultSumw2();

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

SPAnalysis::~SPAnalysis() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void SPAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

  //re-centering parameters
    for(int ibin=0; ibin<nCentBin; ibin++){
      for(int iH=0; iH<nHarmonics; iH++){
        if(doOO_){ 
          meanQhfPlusX[ibin][iH] = OOmeanQhfPlusX[ibin][iH];
          meanQhfPlusY[ibin][iH] = OOmeanQhfPlusY[ibin][iH];
          meanQhfMinusX[ibin][iH] = OOmeanQhfMinusX[ibin][iH];
          meanQhfMinusY[ibin][iH] = OOmeanQhfMinusY[ibin][iH];
          meanQhfMinusPlusX[ibin][iH] = OOmeanQhfMinusPlusX[ibin][iH];
          meanQhfMinusPlusY[ibin][iH] = OOmeanQhfMinusPlusY[ibin][iH];
          meanQDEMinusPlusX[ibin][iH] = OOmeanQDEMinusPlusX[ibin][iH];
          meanQDEMinusPlusY[ibin][iH] = OOmeanQDEMinusPlusY[ibin][iH];
          meanQtrkMidX[ibin][iH] = OOmeanQtrkMidX[ibin][iH];
          meanQtrkMidY[ibin][iH] = OOmeanQtrkMidY[ibin][iH];
          for(int iPt=0; iPt<nPtBin; iPt++){
            meanQtrkPtPlusX[ibin][iH][iPt] = OOmeanQtrkPtPlusX[ibin][iH][iPt];
            meanQtrkPtPlusY[ibin][iH][iPt] = OOmeanQtrkPtPlusY[ibin][iH][iPt];
            meanQtrkPtMinusX[ibin][iH][iPt] = OOmeanQtrkPtMinusX[ibin][iH][iPt];
            meanQtrkPtMinusY[ibin][iH][iPt] = OOmeanQtrkPtMinusY[ibin][iH][iPt];
            meanQtrkPtMidX[ibin][iH][iPt] = OOmeanQtrkPtMidX[ibin][iH][iPt];
            meanQtrkPtMidY[ibin][iH][iPt] = OOmeanQtrkPtMidY[ibin][iH][iPt];
          }
        } //doOO
        if(doNeNe_){
          meanQhfPlusX[ibin][iH] = NeNemeanQhfPlusX[ibin][iH];
          meanQhfPlusY[ibin][iH] = NeNemeanQhfPlusY[ibin][iH];
          meanQhfMinusX[ibin][iH] = NeNemeanQhfMinusX[ibin][iH];
          meanQhfMinusY[ibin][iH] = NeNemeanQhfMinusY[ibin][iH];
          meanQhfMinusPlusX[ibin][iH] = NeNemeanQhfMinusPlusX[ibin][iH];
          meanQhfMinusPlusY[ibin][iH] = NeNemeanQhfMinusPlusY[ibin][iH];
          meanQDEMinusPlusX[ibin][iH] = NeNemeanQDEMinusPlusX[ibin][iH];
          meanQDEMinusPlusY[ibin][iH] = NeNemeanQDEMinusPlusY[ibin][iH];
          meanQtrkMidX[ibin][iH] = NeNemeanQtrkMidX[ibin][iH];
          meanQtrkMidY[ibin][iH] = NeNemeanQtrkMidY[ibin][iH];
          for(int iPt=0; iPt<nPtBin; iPt++){
            meanQtrkPtPlusX[ibin][iH][iPt] = NeNemeanQtrkPtPlusX[ibin][iH][iPt];
            meanQtrkPtPlusY[ibin][iH][iPt] = NeNemeanQtrkPtPlusY[ibin][iH][iPt];
            meanQtrkPtMinusX[ibin][iH][iPt] = NeNemeanQtrkPtMinusX[ibin][iH][iPt];
            meanQtrkPtMinusY[ibin][iH][iPt] = NeNemeanQtrkPtMinusY[ibin][iH][iPt];
            meanQtrkPtMidX[ibin][iH][iPt] = NeNemeanQtrkPtMidX[ibin][iH][iPt];
            meanQtrkPtMidY[ibin][iH][iPt] = NeNemeanQtrkPtMidY[ibin][iH][iPt];
          }
        } //doNeNe
      } //iH
    } //ibin

//hfpf for centrality
    double etHFtowerSumPlus = 0;
    double etHFtowerSumMinus = 0;
    double etHFtowerSum = 0;
  edm::Handle<pat::PackedCandidateCollection> pfs;
  iEvent.getByToken(pfToken_, pfs);
  for(unsigned int i = 0, n = pfs->size(); i < n; ++i) {
    const pat::PackedCandidate &pf = (*pfs)[i];
    // pdfId 1 and 2 for hadronic and em particles in HF
    if(pf.pdgId() == 1 || pf.pdgId() == 2){
      //if(pf.et()<0.01 || pf.et()>30) continue;

      if(pf.eta()>3.0 && pf.eta()<5.2){
        etHFtowerSumPlus += pf.et();
      }
      if(pf.eta()<-3.0 && pf.eta()>-5.2){
        etHFtowerSumMinus += pf.et();
      }

    } // end pf hf
  } // end pf
    etHFtowerSum = etHFtowerSumPlus + etHFtowerSumMinus;
    //cout<<"etHFtowerSum = "<<etHFtowerSum<<endl;

    // get centrality bins [0, 200)
    int cent = -1;
    if(doOO_){
      for (int ic=0; ic < nCentTableBins; ic++){
        if(etHFtowerSum>oo_binBoundaries[ic] && etHFtowerSum<=oo_binBoundaries[ic+1]){
          cent = nCentTableBins -1 - ic;
        }
      }
   } else if (doNeNe_){
      for (int ic=0; ic < nCentTableBins; ic++){
        if(etHFtowerSum>nene_binBoundaries[ic] && etHFtowerSum<=nene_binBoundaries[ic+1]){
          cent = nCentTableBins -1 - ic;
        }
      }
   }

   int ibin=-1;
   for(int j=0;j<nCentBin;j++){
     if(cent>=2*cBin[j]&&cent<2*cBin[j+1]){
       ibin=j;
     } 
   }
   //if(ibin<0 || ibin==nCentBin) return;
   //cout<<"etHFtowerSum = "<<etHFtowerSum<<"  cent = "<<cent<<"  ibin = "<<ibin<<endl;
   if(cent<0 || cent>119) return; //may need to change if the ranges are changed
   histcent->Fill(cent);


  for(int iC=0;iC<nCentBin;iC++){
     sumwPlus[iC] = 0.0;
     sumwMinus[iC] = 0.0;
     sumwMinusPlus[iC] = 0.0;
     sumwDEMinusPlus[iC] = 0.0;
     sumwMidTrk[iC] = 0.0;
     for(int iPt=0; iPt<nPtBin; iPt++){
       sumwPlusTrk[iC][iPt] = 0.0;
       sumwMinusTrk[iC][iPt] = 0.0;
       sumwMidTrkPt[iC][iPt] = 0.0;
     }
     for(int iH=0; iH<nHarmonics; iH++){
       QhfPlus[iC][iH] = 0;
       QhfMinus[iC][iH] = 0;
       QhfMinusPlus[iC][iH] = 0;
       QDEMinusPlus[iC][iH] = 0;
       QtrkMid[iC][iH] = 0;
       for(int iPt=0; iPt<nPtBin; iPt++){
         QtrkPtPlus[iC][iH][iPt] = 0;
         QtrkPtMinus[iC][iH][iPt] = 0;
         QtrkPtMid[iC][iH][iPt] = 0;
       }
     }
   }


   //track collection
   auto trks = iEvent.getHandle( tracksToken_ );

   //access tracks chi2/ndf
   //auto chi2Map = iEvent.getHandle( chi2Map_ );

   //vtx collection
   auto pvs = iEvent.getHandle( vertexToken_ );

   //best vertex
   double bestvzError;
   math::XYZPoint bestvtx;
   math::Error<3>::type vtx_cov;
   if ( !pvs->empty() ) {
      const reco::Vertex& vtx = (*pvs)[0];
      bestvzError = vtx.zError();
      bestvtx = vtx.position();
      vtx_cov = vtx.covariance();
   }else {
      return;
   }

   //cout<<"nVertex = "<<pvs->size()<<endl;
   if (pvs->size() > 1) return;

   if ( std::abs( bestvtx.z() ) > 15. ) return;
   //if (  std::sqrt(bestvtx.x()*bestvtx.x() + bestvtx.y()*bestvtx.y())  > 0.2 ) return;



if(runreco_){
   for (auto const& trk : *trks) {
      if ( !trk.hasTrackDetails() ) continue;
      auto iter_tk = trk.pseudoTrack();


     if ( iter_tk.charge() == 0 ) continue;
     if ( !iter_tk.quality(reco::TrackBase::highPurity) ) continue;
     if ( iter_tk.eta() > etamax_ ) continue;
     if ( iter_tk.eta() < etamin_ ) continue;
     if ( iter_tk.pt() > ptmax_ ) continue;
     if ( iter_tk.pt() < ptmin_ ) continue;
      double dzvtx = iter_tk.dz( bestvtx );
      double dxyvtx = iter_tk.dxy( bestvtx );
      double dzerror = std::hypot( iter_tk.dzError(), bestvzError );
      double dxyerror = iter_tk.dxyError( bestvtx, vtx_cov );
      if ( std::abs( iter_tk.ptError() ) / iter_tk.pt() >= pterrorpt_ ) continue; //default 0.1/loose 0.15
      if ( std::abs( dzvtx / dzerror ) >= dzdzerror_ ) continue; //default 3/loose 5
      if ( std::abs( dxyvtx / dxyerror ) >= d0d0error_ ) continue; //default 3/loose 5

      int cpt=-1;
      for(int ipt=0; ipt<nPtBin; ipt++){
        if(iter_tk.pt()>ptBins[ipt] && iter_tk.pt()<=ptBins[ipt+1])
          cpt=ipt;
      }
      if(cpt<0) cpt=nPtBin-1;
      //cout<<" cpt = "<<cpt<<" pt = "<<track.pt()<<endl;
   
     double weight = 1.0;
     if( cweight_ ){
       /*int idx = 0;
       if( feff_ && heff_[idx] ) {
         double eff = heff_[idx]->GetBinContent(heff_[idx]->FindBin(iter_tk.eta(),iter_tk.pt()));
         if( eff != 0. ){
           weight = 1./eff;
         }
       }*/
       double eff = hEff_3D->GetBinContent(hEff_3D->GetXaxis()->FindBin(iter_tk.eta()), hEff_3D->GetYaxis()->FindBin(iter_tk.pt()), hEff_3D->GetZaxis()->FindBin(cent));
       double fake = hFak_3D->GetBinContent(hFak_3D->GetXaxis()->FindBin(iter_tk.eta()), hFak_3D->GetYaxis()->FindBin(iter_tk.pt()), hFak_3D->GetZaxis()->FindBin(cent)) ;
       double mult = hMul_3D->GetBinContent(hMul_3D->GetXaxis()->FindBin(iter_tk.eta()), hMul_3D->GetYaxis()->FindBin(iter_tk.pt()), hMul_3D->GetZaxis()->FindBin(cent));
       double sec = hSec_3D->GetBinContent(hSec_3D->GetXaxis()->FindBin(iter_tk.eta()), hSec_3D->GetYaxis()->FindBin(iter_tk.pt()), hSec_3D->GetZaxis()->FindBin(cent));    
     if(eff > 0.001){
       weight = (1 - fake)*(1 - sec)/eff/(1 + mult) ;
     }else{
       weight = 1.0 ;
     }
     if((iter_tk.pt() < 0 || iter_tk.pt() > 500) || (fabs(iter_tk.eta()) > 2.4)){
      weight = 0 ;
     }   
     //cout<<"cent ="<<cent<<" , pt ="<<iter_tk.pt()<<"  eff ="<<eff<<"  fake ="<<fake<<" , weight ="<<weight<<endl;
    }


      //hMeanPt[ibin][cpt]->Fill(iter_tk.pt(), weight);

      double pt_weight = 1.0; 
      if(iter_tk.eta() > 1.0*etaCutTrkNonC_ && iter_tk.eta() < 1.0*etaCutTrk_){
        sumwPlusTrk[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtPlus[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));        
        }
      }
      if(iter_tk.eta() < -1.0*etaCutTrkNonC_ && iter_tk.eta() > -1.0*etaCutTrk_){
        sumwMinusTrk[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtMinus[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
        }
      }
      if(iter_tk.eta() > -1.0 && iter_tk.eta() < 1.0 && iter_tk.pt() > 0.3 && iter_tk.pt() < 3.0){ //Q_nC 3sub
        sumwMidTrk[ibin] += iter_tk.pt();
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkMid[ibin][iH]+= iter_tk.pt() * TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
        }
      }
      //pT, Trk, Qvector
      //if(iter_tk.eta() > -1.0*etaCutTrk_ && iter_tk.eta() < 1.0*etaCutTrk_ ){
      if( iter_tk.eta() < -1.0*etaCutTrkNonC_ && iter_tk.eta() > -1.0*etaCutTrk_   ||   iter_tk.eta() > 1.0*etaCutTrkNonC_ && iter_tk.eta() < 1.0*etaCutTrk_ ){
        hMeanPt[ibin][cpt]->Fill(iter_tk.pt(), weight);
        hPtCent[ibin]->Fill(iter_tk.pt());
        hPtCentCorr[ibin]->Fill(iter_tk.pt(), weight);
        hMeanPtMid[ibin][cpt]->Fill(iter_tk.pt(), weight);
        sumwMidTrkPt[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtMid[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
        }
      }

  } // end trk
}

/*
if(rungen_){
   edm::Handle< reco::GenParticleCollection > tracks;
   iEvent.getByToken(genTracksToken_, tracks);
   for( reco::GenParticleCollection::const_iterator itTrk = tracks->begin() ; itTrk != tracks->end() ; ++itTrk ) {
     double eta    = itTrk->eta();
     double pt     = itTrk->pt();
     double phi     = itTrk->phi();

      if(eta>2.4 || eta<-2.4) continue;

      int cpt=-1;
      for(int ipt=0; ipt<nPtBin; ipt++){
        if(pt>ptBins[ipt] && pt<ptBins[ipt+1])
          cpt=ipt;
      }
      if(cpt<0) cpt=nPtBin-1;
      //cout<<" cpt = "<<cpt<<" pt = "<<track.pt()<<endl;

      hMeanPt[ibin][cpt]->Fill(pt);

      double pt_weight = 1.0;
      if(eta > 0 && eta < 1.0*etaCutTrk_){
        sumwPlusTrk[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtPlus[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*phi));
        }
      }
      if(eta < 0 && eta > -1.0*etaCutTrk_){
        sumwMinusTrk[ibin][cpt]+= pt_weight;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkPtMinus[ibin][iH][cpt]+= pt_weight * TComplex::Exp(TComplex(0,(iH+1)*phi));
        }
      }
      if(eta > -0.75 && eta < 0.75 && pt > 0.3 && pt < 3.0){
        sumwMidTrk[ibin] += pt;
        for(int iH=0; iH<nHarmonics; iH++){
          QtrkMid[ibin][iH]+= pt * TComplex::Exp(TComplex(0,(iH+1)*phi));
        }
      }

   } // gen trk
}
*/

    for(int iH=0; iH<nHarmonics; iH++){
      for(int iPt=0; iPt<nPtBin; iPt++){
        if(sumwPlusTrk[ibin][iPt]>0) { QtrkPtPlus[ibin][iH][iPt]=QtrkPtPlus[ibin][iH][iPt]/sumwPlusTrk[ibin][iPt] - TComplex(meanQtrkPtPlusX[ibin][iH][iPt], meanQtrkPtPlusY[ibin][iH][iPt]); }
        else {QtrkPtPlus[ibin][iH][iPt]=0; }
        if(sumwMinusTrk[ibin][iPt]>0) { QtrkPtMinus[ibin][iH][iPt]=QtrkPtMinus[ibin][iH][iPt]/sumwMinusTrk[ibin][iPt] - TComplex(meanQtrkPtMinusX[ibin][iH][iPt], meanQtrkPtMinusY[ibin][iH][iPt]); }
        else { QtrkPtMinus[ibin][iH][iPt]=0; }
        if(sumwMidTrkPt[ibin][iPt]>0) {
          QtrkPtMid[ibin][iH][iPt] = QtrkPtMid[ibin][iH][iPt]/sumwMidTrkPt[ibin][iPt] - TComplex(meanQtrkPtMidX[ibin][iH][iPt], meanQtrkPtMidY[ibin][iH][iPt]); 
        } else { QtrkPtMid[ibin][iH][iPt] = 0; }
      }
      if(sumwMidTrk[ibin]>0){
        QtrkMid[ibin][iH] = QtrkMid[ibin][iH]/sumwMidTrk[ibin] - TComplex(meanQtrkMidX[ibin][iH], meanQtrkMidY[ibin][iH]);
      } else { QtrkMid[ibin][iH]=0; }
    }//iH
 //cout<<"end of trk"<<endl;

    // hfpf
  for(unsigned int i = 0, n = pfs->size(); i < n; ++i) {
    const pat::PackedCandidate &pf = (*pfs)[i];
    // pdfId 1 and 2 for hadronic and em particles in HF
    if(pf.pdgId() == 1 || pf.pdgId() == 2){
       double eta = pf.eta();
          if(eta>3.0 && eta<5.2 && eta > 1.0*etaCutHF_){
            sumwPlus[ibin]+= pf.et();
            for(int iH=0; iH<nHarmonics; iH++){
              QhfPlus[ibin][iH]+= pf.et() * TComplex::Exp(TComplex(0,(iH+1)*pf.phi()));
            }
          }
          if(eta<-3.0 && eta>-5.2 && eta < -1.0*etaCutHF_){
            sumwMinus[ibin]+= pf.et();
            for(int iH=0; iH<nHarmonics; iH++){
              QhfMinus[ibin][iH]+= pf.et() * TComplex::Exp(TComplex(0,(iH+1)*pf.phi()));
            }
          }
          if( (eta>-5.2 && eta < -1.0*etaCutHF_) || (eta > 1.0*etaCutHF_ && eta<5.2) ){
            sumwMinusPlus[ibin]+= pf.et();
            for(int iH=0; iH<nHarmonics; iH++){
              QhfMinusPlus[ibin][iH]+= pf.et() * TComplex::Exp(TComplex(0,(iH+1)*pf.phi()));
            }
          }
      } // end hf
          double eta = pf.eta();
          if( (eta>-3.0 && eta < -1.0) || (eta > 1.0 && eta<3.0) ){
            sumwDEMinusPlus[ibin]+= pf.et();
            for(int iH=0; iH<nHarmonics; iH++){
              QDEMinusPlus[ibin][iH]+= pf.et() * TComplex::Exp(TComplex(0,(iH+1)*pf.phi()));
            }
          }
      //} // end hf
    } // end hfpf
    for(int iH=0; iH<nHarmonics; iH++){
      if(sumwPlus[ibin]>0) { QhfPlus[ibin][iH]=QhfPlus[ibin][iH]/sumwPlus[ibin] - TComplex(meanQhfPlusX[ibin][iH], meanQhfPlusY[ibin][iH]); }
      else { QhfPlus[ibin][iH]=0; }
      if(sumwMinus[ibin]>0) { QhfMinus[ibin][iH]=QhfMinus[ibin][iH]/sumwMinus[ibin] - TComplex(meanQhfMinusX[ibin][iH], meanQhfMinusY[ibin][iH]); }
      else { QhfMinus[ibin][iH]=0; }
      if(sumwMinusPlus[ibin]>0) { QhfMinusPlus[ibin][iH]=QhfMinusPlus[ibin][iH]/sumwMinusPlus[ibin] - TComplex(meanQhfMinusPlusX[ibin][iH], meanQhfMinusPlusY[ibin][iH]); }
      else { QhfMinusPlus[ibin][iH]=0; }
      if(sumwDEMinusPlus[ibin]>0) { QDEMinusPlus[ibin][iH]=QDEMinusPlus[ibin][iH]/sumwDEMinusPlus[ibin] - TComplex(meanQDEMinusPlusX[ibin][iH], meanQDEMinusPlusY[ibin][iH]); }
      else { QDEMinusPlus[ibin][iH]=0; }
      //cout<<"sumwDEMinusPlus = "<<sumwPlus[ibin]<<"  "<<QhfPlus[ibin][iH]<<"  "<<sumwMinusPlus[ibin]<<"  "<<sumwDEMinusPlus[ibin]<<"  "<<QDEMinusPlus[ibin][iH]<<endl;
    }//iH

    // final histograms for flow
    for(int iH=0; iH<nHarmonics; iH++){
      if(sumwPlus[ibin]>0 && sumwMinus[ibin]>0) {
        hQnPlusQnMinusStar[ibin][iH]->Fill((QhfPlus[ibin][iH]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re());
        hQnMinusQnPlusStar[ibin][iH]->Fill((QhfMinus[ibin][iH]*TComplex::Conjugate(QhfPlus[ibin][iH])).Re());
      }
      if(sumwMinus[ibin]>0 && sumwMidTrk[ibin]>0) {
        hQnMinusQnMidStar[ibin][iH]->Fill((QhfMinus[ibin][iH]*TComplex::Conjugate(QtrkMid[ibin][iH])).Re());
      }
      if(sumwPlus[ibin]>0 && sumwMidTrk[ibin]>0) {
        hQnPlusQnMidStar[ibin][iH]->Fill((QhfPlus[ibin][iH]*TComplex::Conjugate(QtrkMid[ibin][iH])).Re());
      }
      if(sumwMinusPlus[ibin]>0 && sumwDEMinusPlus[ibin]>0) {
        hQnMinusPlusQnDEStar[ibin][iH]->Fill((QhfMinusPlus[ibin][iH]*TComplex::Conjugate(QDEMinusPlus[ibin][iH])).Re());
      }
      if(sumwMinusPlus[ibin]>0 && sumwMidTrk[ibin]>0) {
        hQnMinusPlusQnMidStar[ibin][iH]->Fill((QhfMinusPlus[ibin][iH]*TComplex::Conjugate(QtrkMid[ibin][iH])).Re());
      }
      if(sumwDEMinusPlus[ibin]>0 && sumwMidTrk[ibin]>0) {
        hQnDEQnMidStar[ibin][iH]->Fill((QDEMinusPlus[ibin][iH]*TComplex::Conjugate(QtrkMid[ibin][iH])).Re());
      }

      for(int iPt=0; iPt<nPtBin; iPt++){ //do we need to fill 0 if there is no particles in a pT bin? A: No
        if(sumwPlusTrk[ibin][iPt]>0 && sumwMinus[ibin]>0){
          hqnPlusQnMinusStar[ibin][iH][iPt]->Fill((QtrkPtPlus[ibin][iH][iPt]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re());
        }
        if(sumwMinusTrk[ibin][iPt]>0 && sumwPlus[ibin]>0){
          hqnMinusQnPlusStar[ibin][iH][iPt]->Fill((QtrkPtMinus[ibin][iH][iPt]*TComplex::Conjugate(QhfPlus[ibin][iH])).Re());
        }
        if(sumwMidTrkPt[ibin][iPt]>0 && sumwPlus[ibin]>0) {
          hqnQnPlusStar[ibin][iH][iPt]->Fill((QtrkPtMid[ibin][iH][iPt]*TComplex::Conjugate(QhfPlus[ibin][iH])).Re());
        }
        if(sumwMidTrkPt[ibin][iPt]>0 && sumwMinus[ibin]>0) {
          hqnQnMinusStar[ibin][iH][iPt]->Fill((QtrkPtMid[ibin][iH][iPt]*TComplex::Conjugate(QhfMinus[ibin][iH])).Re());
        }
        if(sumwMidTrkPt[ibin][iPt]>0 && sumwMinusPlus[ibin]>0) {
          hqnQnMinusPlusStar[ibin][iH][iPt]->Fill((QtrkPtMid[ibin][iH][iPt]*TComplex::Conjugate(QhfMinusPlus[ibin][iH])).Re());
        }
      }
    }//iH

  //Histograms for recentering
    for(int iH=0; iH<nHarmonics; iH++){
      if(sumwPlus[ibin]>0) {
        hQhfPlusX[ibin][iH]->Fill(QhfPlus[ibin][iH].Re());      
        hQhfPlusY[ibin][iH]->Fill(QhfPlus[ibin][iH].Im());      
      }
      if(sumwMinus[ibin]>0) {
        hQhfMinusX[ibin][iH]->Fill(QhfMinus[ibin][iH].Re());      
        hQhfMinusY[ibin][iH]->Fill(QhfMinus[ibin][iH].Im());      
      }
      if(sumwMinusPlus[ibin]>0) {
        hQhfMinusPlusX[ibin][iH]->Fill(QhfMinusPlus[ibin][iH].Re());      
        hQhfMinusPlusY[ibin][iH]->Fill(QhfMinusPlus[ibin][iH].Im());      
      }
      if(sumwDEMinusPlus[ibin]>0) {
        hQDEMinusPlusX[ibin][iH]->Fill(QDEMinusPlus[ibin][iH].Re());      
        hQDEMinusPlusY[ibin][iH]->Fill(QDEMinusPlus[ibin][iH].Im());      
      }
      for(int iPt=0; iPt<nPtBin; iPt++){
        if(sumwPlusTrk[ibin][iPt]>0){
          hQtrkPtPlusX[ibin][iH][iPt]->Fill(QtrkPtPlus[ibin][iH][iPt].Re());
          hQtrkPtPlusY[ibin][iH][iPt]->Fill(QtrkPtPlus[ibin][iH][iPt].Im());
        }
        if(sumwMinusTrk[ibin][iPt]>0){
          hQtrkPtMinusX[ibin][iH][iPt]->Fill(QtrkPtMinus[ibin][iH][iPt].Re());
          hQtrkPtMinusY[ibin][iH][iPt]->Fill(QtrkPtMinus[ibin][iH][iPt].Im());
        }
        if(sumwMidTrkPt[ibin][iPt]>0) {
          hQtrkPtMidX[ibin][iH][iPt]->Fill(QtrkPtMid[ibin][iH][iPt].Re());
          hQtrkPtMidY[ibin][iH][iPt]->Fill(QtrkPtMid[ibin][iH][iPt].Im());
        }
      }
      if(sumwMidTrk[ibin]>0){
        hQtrkMidX[ibin][iH]->Fill(QtrkMid[ibin][iH].Re());
        hQtrkMidY[ibin][iH]->Fill(QtrkMid[ibin][iH].Im());
      }
    }//iH


#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void SPAnalysis::beginJob() {
  // please remove this method if not needed

  TH1D::SetDefaultSumw2();
  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0; iH<nHarmonics; iH++){
      hQnPlusQnMinusStar[iC][iH] = fs->make<TH1D>(Form("hQnPlusQnMinusStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQnMinusQnPlusStar[iC][iH] = fs->make<TH1D>(Form("hQnMinusQnPlusStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQnMinusQnMidStar[iC][iH] = fs->make<TH1D>(Form("hQnMinusQnMidStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQnPlusQnMidStar[iC][iH] = fs->make<TH1D>(Form("hQnPlusQnMidStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQnMinusPlusQnDEStar[iC][iH] = fs->make<TH1D>(Form("hQnMinusPlusQnDEStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQnMinusPlusQnMidStar[iC][iH] = fs->make<TH1D>(Form("hQnMinusPlusQnMidStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQnDEQnMidStar[iC][iH] = fs->make<TH1D>(Form("hQnDEQnMidStar_iC%d_iH%d",iC,iH),"",10,-1000,1000);
     
      hQhfPlusX[iC][iH] = fs->make<TH1D>(Form("hQhfPlusX_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQhfPlusY[iC][iH] = fs->make<TH1D>(Form("hQhfPlusY_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQhfMinusX[iC][iH] = fs->make<TH1D>(Form("hQhfMinusX_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQhfMinusY[iC][iH] = fs->make<TH1D>(Form("hQhfMinusY_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQhfMinusPlusX[iC][iH] = fs->make<TH1D>(Form("hQhfMinusPlusX_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQhfMinusPlusY[iC][iH] = fs->make<TH1D>(Form("hQhfMinusPlusY_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQDEMinusPlusX[iC][iH] = fs->make<TH1D>(Form("hQDEMinusPlusX_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQDEMinusPlusY[iC][iH] = fs->make<TH1D>(Form("hQDEMinusPlusY_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQtrkMidX[iC][iH] = fs->make<TH1D>(Form("hQtrkMidX_iC%d_iH%d",iC,iH),"",10,-1000,1000);
      hQtrkMidY[iC][iH] = fs->make<TH1D>(Form("hQtrkMidY_iC%d_iH%d",iC,iH),"",10,-1000,1000);

      for(int iPt=0; iPt<nPtBin; iPt++){
        hqnPlusQnMinusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnPlusQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hqnMinusQnPlusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnMinusQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hqnQnPlusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnQnPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000); 
        hqnQnMinusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnQnMinusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000); 
        hqnQnMinusPlusStar[iC][iH][iPt] = fs->make<TH1D>(Form("hqnQnMinusPlusStar_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000); 
   
        hQtrkPtPlusX[iC][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtPlusX_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hQtrkPtPlusY[iC][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtPlusY_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hQtrkPtMinusX[iC][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtMinusX_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hQtrkPtMinusY[iC][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtMinusY_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hQtrkPtMidX[iC][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtMidX_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);
        hQtrkPtMidY[iC][iH][iPt] = fs->make<TH1D>(Form("hQtrkPtMidY_iC%d_iH%d_iPt%d",iC,iH,iPt),"",10,-1000,1000);

      }
    }//iH
    for(int iPt=0; iPt<nPtBin; iPt++){
      hMeanPt[iC][iPt] = fs->make<TH1D>(Form("hMeanPt_iC%d_iPt%d",iC,iPt),"",20,0,200);
      hMeanPtMid[iC][iPt] = fs->make<TH1D>(Form("hMeanPtMid_iC%d_iPt%d",iC,iPt),"",20,0,200);
    }
    hPtCent[iC] = fs->make<TH1D>(Form("hPtCent_iC%d",iC),"",2000,0,200);
    hPtCentCorr[iC] = fs->make<TH1D>(Form("hPtCentCorr_iC%d",iC),"",2000,0,200);
  }
  histcent = fs->make<TH1D>(Form("histcent"),"",200,0,200); 

}

// ------------ method called once each job just after ending the event loop  ------------
void SPAnalysis::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void SPAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //edm::ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks", edm::InputTag("ctfWithMaterialTracks"));
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SPAnalysis);
