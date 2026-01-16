// -*- C++ -*-
//
// Package:    OOAnalysisFlow/TransmutationAna
// Class:      TransmutationAna
//
/**\class TransmutationAna TransmutationAna.cc OOAnalysisFlow/TransmutationAna/plugins/TransmutationAna.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Sat, 23 Aug 2025 22:12:52 GMT
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
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "RecoHI/HiEvtPlaneAlgos/interface/HiEvtPlaneList.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"

#include "TComplex.h"
#include <vector>
#include <TVector3.h>

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

class TransmutationAna : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit TransmutationAna(const edm::ParameterSet&);
  ~TransmutationAna();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT< edm::View< pat::PackedCandidate > > tracksToken_;
  edm::EDGetTokenT< pat::PackedCandidateCollection > pfToken_;
  edm::EDGetTokenT< reco::VertexCollection > vertexToken_;
  edm::EDGetTokenT< edm::ValueMap< float > > chi2Map_;
  edm::EDGetTokenT< reco::Centrality > centralityTag_;
  edm::EDGetTokenT< int > centralityBinTag_;
  //edm::EDGetTokenT< std::vector<reco::EvtPlane> > eventPlane_;
  bool isPixelTracks_;

  edm::Service<TFileService> fs;

  static const int nCentBin = 17;
  double cBin[nCentBin+1]={0,0.5,1,2,5,10,15,20,25,30,35,40,45,50,55,60,70,80};
  static const int nCentTableBins = 200; 

//new oo
double binBoundaries[nCentTableBins+1] ={0,0.717572,1.43514,2.15272,2.87029,3.58786,4.30543,5.023,5.74057,6.45815,7.17572,7.89329,8.61086,9.32843,10.046,10.5615,10.9358,11.3222,11.7114,12.1054,12.5071,12.9114,13.3242,13.7529,14.1895,14.6323,15.0788,15.5384,16.0017,16.4718,16.954,17.4529,17.965,18.4818,19.0081,19.5384,20.0798,20.6295,21.1904,21.7624,22.3333,22.9144,23.5082,24.108,24.7103,25.3327,25.9643,26.6021,27.2404,27.8889,28.551,29.2201,29.8838,30.5609,31.2582,31.959,32.6755,33.3996,34.127,34.8736,35.624,36.3835,37.1513,37.9462,38.7306,39.5312,40.3522,41.1784,41.9996,42.8382,43.7007,44.5735,45.4614,46.3438,47.2291,48.1364,49.0614,49.9993,50.9485,51.9135,52.8921,53.8808,54.8964,55.893,56.9136,57.9568,59.0177,60.0888,61.1833,62.2824,63.399,64.5337,65.6807,66.8337,68.0214,69.219,70.4243,71.651,72.9014,74.165,75.4546,76.7537,78.0703,79.4045,80.7569,82.1322,83.5298,84.9421,86.3744,87.8423,89.3304,90.8548,92.361,93.9159,95.4992,97.0799,98.6655,100.303,101.96,103.647,105.32,107.036,108.77,110.55,112.332,114.116,115.936,117.785,119.708,121.683,123.605,125.589,127.588,129.583,131.654,133.746,135.887,138.016,140.191,142.401,144.623,146.867,149.14,151.514,153.909,156.277,158.74,161.209,163.662,166.177,168.728,171.298,173.901,176.575,179.302,182.038,184.793,187.576,190.47,193.355,196.279,199.296,202.355,205.406,208.567,211.746,215.007,218.296,221.624,224.981,228.464,231.972,235.5,239.147,242.785,246.538,250.308,254.2,258.246,262.353,266.531,270.819,275.228,279.794,284.51,289.356,294.368,299.561,305.114,310.888,316.984,323.451,330.516,337.981,346.265,355.527,366.193,379.001,395.659,421.298,10000};

//new nene
//double binBoundaries[nCentTableBins+1] = {0, 0.719255, 1.4342, 2.15771, 2.88021, 3.60442, 4.32898, 5.06429, 5.80245, 6.54448, 7.29359, 8.03948, 8.78366, 9.52997, 10.291, 10.8364, 11.2413, 11.6657, 12.0903, 12.5205, 12.9362, 13.3679, 13.828, 14.3155, 14.8123, 15.3003, 15.8012, 16.316, 16.8477, 17.386, 17.9322, 18.4966, 19.054, 19.617, 20.1932, 20.7752, 21.3879, 22.0138, 22.6562, 23.3336, 24.0008, 24.6698, 25.3371, 26.014, 26.6713, 27.3629, 28.1007, 28.8206, 29.5269, 30.2399, 30.9738, 31.758, 32.5325, 33.3646, 34.2134, 35.0452, 35.8588, 36.6774, 37.5231, 38.3385, 39.1676, 40.0098, 40.9117, 41.8504, 42.7898, 43.7328, 44.6845, 45.6503, 46.5973, 47.5628, 48.5524, 49.566, 50.5643, 51.523, 52.5722, 53.6806, 54.7885, 55.8534, 56.9384, 58.1004, 59.2483, 60.3973, 61.5696, 62.7664, 63.9656, 65.1309, 66.3679, 67.6707, 69.0174, 70.3219, 71.6693, 73.0417, 74.412, 75.7361, 77.1419, 78.5585, 80.0874, 81.6352, 83.1272, 84.61, 86.1389, 87.6683, 89.3241, 90.9204, 92.6097, 94.3453, 96.0214, 97.6521, 99.4319, 101.27, 102.973, 104.793, 106.682, 108.671, 110.605, 112.532, 114.513, 116.504, 118.408, 120.398, 122.397, 124.356, 126.441, 128.706, 130.955, 133.155, 135.433, 137.793, 140.152, 142.753, 145.223, 147.53, 149.947, 152.292, 154.689, 157.253, 159.753, 162.35, 164.921, 167.624, 170.242, 172.901, 175.745, 178.606, 181.406, 184.107, 186.801, 189.706, 192.545, 195.756, 198.738, 202.095, 205.25, 208.467, 211.849, 215.28, 218.647, 222.174, 225.477, 228.882, 232.598, 236.342, 240.046, 243.813, 247.762, 251.632, 255.689, 259.939, 264.567, 268.599, 272.783, 276.842, 281.25, 286.056, 290.646, 295.322, 299.948, 304.807, 309.789, 315.06, 319.624, 324.911, 330.409, 335.504, 341.204, 347.243, 353.51, 360.457, 367.597, 374.858, 381.806, 389.385, 397.835, 407.3, 416.712, 428.02, 439.285, 454.587, 475.347, 506.524, 10000};


  //ntrkbin
  //static const int nCentBin = 17;
  //double cBin[nCentBin+1]={0, 20, 40, 60, 80, 100, 120, 150, 180, 210, 250, 300, 350, 400, 450, 500, 550, 600};


  //static const int nCentBinEff = 8;
  //double cBinEff[nCentBinEff+1]={0,5,10,20,30,40,50,70,90};
  static const int nCentBinEff = 1;
  double cBinEff[nCentBinEff+1]={0,100};

  static const int nHarmonics = 5;

      TH1D *histCorr2_2[nCentBin][nHarmonics];
      TH1D *histCorr4_2[nCentBin][nHarmonics];
      TH1D *histwCorr2_2[nCentBin][nHarmonics];
      TH1D *histwCorr4_2[nCentBin][nHarmonics];
      TH1D *histwCorr2_2_AB00[nCentBin][nHarmonics];
      TH1D *histwCorr2_2_AB05[nCentBin][nHarmonics];
      TH1D *histwCorr2_2_AB10[nCentBin][nHarmonics];
      TH1D *histwCorr2_2_AB15[nCentBin][nHarmonics];
  TH1D *histcent;
  TH1D *histntrkOffline;
  TH1D *histntrkOfflineCorr;
  TH1D *histntrkpt03;
  TH1D *histntrkpt03Corr;
  TH1D *histeta;
  TH1D *histpt;
  TH1D *histetareco;
  TH1D *histptreco;
TH1D* hNtrkOffline[nCentBin];
  TH2D *hNtrkOfflineCent;

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
  std::vector<TH2D*> heff_;     //TH2D histograms used for correction
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
TransmutationAna::TransmutationAna(const edm::ParameterSet& iConfig) : 
      tracksToken_( consumes< edm::View< pat::PackedCandidate > >( iConfig.         getParameter< edm::InputTag >( "tracks" ) ) ),
      pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
      vertexToken_( consumes< reco::VertexCollection >( iConfig.getParameter< edm:: InputTag >( "vertices" ) ) ),
      chi2Map_( consumes< edm::ValueMap< float > >( iConfig.getParameter< edm::     InputTag >( "trackschi2" ) ) ),
      centralityTag_( consumes< reco::Centrality >( iConfig.getParameter< edm::     InputTag >( "centrality" ) ) ),
      centralityBinTag_( consumes< int >( iConfig.getParameter< edm::InputTag >(    "centralityBin" ) ) ),
//      eventPlane_( consumes< std::vector< reco::EvtPlane > >( iConfig.getParameter< edm::InputTag >( "eventPlane" ) ) ),
      isPixelTracks_( iConfig.getParameter< bool >( "isPixelTracks" ) ),
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
  runreco_(iConfig.getUntrackedParameter<bool>("runreco")),
  rungen_(iConfig.getUntrackedParameter<bool>("rungen"))
{

   TString filename(fname_.label().c_str());
   feff_ = 0x0;
   if(cweight_ && !filename.IsNull()){
      edm::FileInPath fip(Form("OOAnalysisFlow/TransmutationAna/data/%s",filename.Data()));
      feff_ = new TFile(fip.fullPath().c_str(),"READ");
      heff_.resize(feff_->GetNkeys());
      for(unsigned short ik = 0; ik < heff_.size(); ++ik)
      {
         heff_[ik] = (TH2D*) feff_->Get(feff_->GetListOfKeys()->At(ik)->GetName());
         //cout<<"hist eff: "<<feff_->GetListOfKeys()->At(ik)->GetName()<<endl;
      }
      feff_->Close();

   }

  TH1::SetDefaultSumw2();


#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

TransmutationAna::~TransmutationAna() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void TransmutationAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
/*
   //access centrality bins
   auto cbin = iEvent.getHandle( centralityBinTag_ );
   int cent = -1;
   cent = ( int ) (*cbin);
   //hist_cent_->Fill(cent);
   //if(cent>38 && cent<62) cout<<" cent = "<<cent<<endl;
   // 5-60 -> 0-80
   //if(cent<10 || cent>119) return;
   if(cent<0 || cent>159) return;

    edm::Handle<reco::Centrality> centrality;
    iEvent.getByToken(centralityTag_, centrality);
    //cout<<" cent = "<<cent<<" ;  hiNtracks = "<<centrality->Ntracks()<<endl;

   histcent->Fill(cent);

   int ibin=-1;
   for(int j=0;j<nCentBin;j++){
     if(cent>=2*cBin[j]&&cent<2*cBin[j+1]){
       ibin=j;
     }
   }
   if(ibin<0 || ibin==nCentBin) return;

   //if(cent>38 && cent<62) cout<<" cent = "<<cent<<endl;

  // find eff hist for the proper cent bin
   int idx = 2;
   for(int j=0;j<nCentBinEff;j++){
     if(cent>=2*cBinEff[j]&&cent<2*cBinEff[j+1]){
       idx=2*j+2;
     }
   }
   if(idx<2 || idx>17) return;
   //cout<<" cent = "<<cent<<" ;  ibin = "<<ibin<<" ; idx = "<<idx<<endl;
   //if(cent>38 && cent<62) cout<<" cent 2nd = "<<cent<<endl;
*/


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
    for (int ic=0; ic < nCentTableBins; ic++){
      if(etHFtowerSum>binBoundaries[ic] && etHFtowerSum<binBoundaries[ic+1]){
        cent = nCentTableBins -1 - ic;
      }
    }

   int ibin=-1;
   for(int j=0;j<nCentBin;j++){
     if(cent>=2*cBin[j]&&cent<2*cBin[j+1]){
       ibin=j;
     }
   }
   histcent->Fill(cent);
   //if(ibin<0 || ibin==nCentBin) return;
   //cout<<"etHFtowerSum = "<<etHFtowerSum<<"  cent = "<<cent<<"  ibin = "<<ibin<<endl;
   if(cent<0 || cent>159) return;


   //track collection
   auto trks = iEvent.getHandle( tracksToken_ );

   //access tracks chi2/ndf
   auto chi2Map = iEvent.getHandle( chi2Map_ );

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

  TComplex Q2_2[nHarmonics] = {0.0};
  TComplex Q4_2[nHarmonics] = {0.0};
  double corr_4_2[nHarmonics], corr_2_2[nHarmonics];
  double nW2 = 0;
  double nW4 = 0;
  double nM = 0;

  double S21, S12;
  double S41, S13, S11, S22, S14;
  double M11, M1111;
  double wsum1 = 0;
  double wsum2 = 0;
  double wsum3 = 0;
  double wsum4 = 0;
  TComplex wQ21[nHarmonics] = {0.0};
  TComplex wQ42[nHarmonics] = {0.0};
  TComplex wQ23[nHarmonics] = {0.0};
  double wcorr_4_2[nHarmonics], wcorr_2_2[nHarmonics];

  // gap for vn{2}
  TComplex wQA00[nHarmonics] = {0.0};
  TComplex wQA05[nHarmonics] = {0.0};
  TComplex wQA10[nHarmonics] = {0.0};
  TComplex wQA15[nHarmonics] = {0.0};
  TComplex wQB00[nHarmonics] = {0.0};
  TComplex wQB05[nHarmonics] = {0.0};
  TComplex wQB10[nHarmonics] = {0.0};
  TComplex wQB15[nHarmonics] = {0.0};
  double wsumA00 = 0;
  double wsumA05 = 0;
  double wsumA10 = 0;
  double wsumA15 = 0;
  double wsumB00 = 0;
  double wsumB05 = 0;
  double wsumB10 = 0;
  double wsumB15 = 0;
  double MAB00, MAB05, MAB10, MAB15;
  double wcorr_2_2_AB00[nHarmonics], wcorr_2_2_AB05[nHarmonics];
  double wcorr_2_2_AB10[nHarmonics], wcorr_2_2_AB15[nHarmonics];

  int ntrkoffline = 0;
  int ntrkpt03 = 0;
   for (auto const& trk : *trks) {

      //trkIndx++;

      if ( !trk.hasTrackDetails() ) continue;
      auto iter_tk = trk.pseudoTrack();

      double pTcut = -1.;
      if( !isPixelTracks_ ) {
         pTcut = 0.3;
      } else {
         pTcut = 0.3;
      }

      if ( iter_tk.pt() <= pTcut ) continue;
      if ( std::abs( iter_tk.eta() ) >= 2.4 ) continue;

      double dzvtx = iter_tk.dz( bestvtx );
      double dxyvtx = iter_tk.dxy( bestvtx );
      double dzerror = std::hypot( iter_tk.dzError(), bestvzError );
      double dxyerror = iter_tk.dxyError( bestvtx, vtx_cov );

      //auto hit_pattern = iter_tk.hitPattern();

      //double chi2ndof = 999.9;

      if ( !isPixelTracks_ ) {
         //general tracks selection for 2018 PbPb data
         //chi2ndof = ( double ) ( *chi2Map )[ trks->ptrAt( trkIndx ) ];
         if ( std::abs( iter_tk.ptError() ) / iter_tk.pt() >= 0.1 ) continue; //default 0.1/loose 0.15
         if ( std::abs( dzvtx / dzerror ) >= 3 ) continue; //default 3/loose 5
         if ( std::abs( dxyvtx / dxyerror ) >= 3 ) continue; //default 3/loose 5
         //if ( ( chi2ndof / hit_pattern.trackerLayersWithMeasurement() ) >= 0.18 ) continue;
         //if ( iter_tk.numberOfValidHits() < 11 ) continue;
         if ( iter_tk.charge() == 0 ) continue; //adding charge requirement
      } else {
         //pixel tracks selection for 2018 PbPb data
         //chi2ndof = iter_tk.normalizedChi2();
         if ( std::abs( dzvtx / dzerror ) >= 7 ) continue;
         if ( std::abs( dxyvtx / dxyerror ) >= 7 ) continue;
      }

      //if(iter_tk.eta()>etamax_ || iter_tk.eta()<etamin_) continue;

     if(iter_tk.pt()>0.4 && iter_tk.eta()<2.4 && iter_tk.eta()>-2.4){
       ntrkoffline += 1;
     }
     if(iter_tk.pt()>0.3 && iter_tk.eta()<2.4 && iter_tk.eta()>-2.4){
       ntrkpt03 += 1;
     }

   } // ntrkoffline

   histntrkOffline->Fill(ntrkoffline);
   histntrkpt03->Fill(ntrkpt03);
   ///hNtrkOfflineCent->Fill(cent, ntrkoffline);

   double ntrkofflineCorr = 0;
   double ntrkpt03Corr = 0;
   int ntracks = 0;
   int trkIndx = -1;
   for (auto const& trk : *trks) {

      trkIndx++;

      if ( !trk.hasTrackDetails() ) continue;
      auto iter_tk = trk.pseudoTrack();

      double pTcut = -1.;
      if( !isPixelTracks_ ) {
         pTcut = 0.3;
      } else {
         pTcut = 0.3;
      }

      if ( iter_tk.pt() <= pTcut ) continue;
      if ( std::abs( iter_tk.eta() ) >= 2.4 ) continue;

      double dzvtx = iter_tk.dz( bestvtx );
      double dxyvtx = iter_tk.dxy( bestvtx );
      double dzerror = std::hypot( iter_tk.dzError(), bestvzError );
      double dxyerror = iter_tk.dxyError( bestvtx, vtx_cov );

      //auto hit_pattern = iter_tk.hitPattern();

      //double chi2ndof = 999.9;

      if ( !isPixelTracks_ ) {
         //general tracks selection for 2018 PbPb data
         //chi2ndof = ( double ) ( *chi2Map )[ trks->ptrAt( trkIndx ) ];
         if ( std::abs( iter_tk.ptError() ) / iter_tk.pt() >= 0.1 ) continue; //default 0.1/loose 0.15
         if ( std::abs( dzvtx / dzerror ) >= 3 ) continue; //default 3/loose 5
         if ( std::abs( dxyvtx / dxyerror ) >= 3 ) continue; //default 3/loose 5
         //if ( ( chi2ndof / hit_pattern.trackerLayersWithMeasurement() ) >= 0.18 ) continue;
         //if ( iter_tk.numberOfValidHits() < 11 ) continue;
         if ( iter_tk.charge() == 0 ) continue; //adding charge requirement
      } else {
         //pixel tracks selection for 2018 PbPb data
         //chi2ndof = iter_tk.normalizedChi2();
         if ( std::abs( dzvtx / dzerror ) >= 7 ) continue;
         if ( std::abs( dxyvtx / dxyerror ) >= 7 ) continue;
      }

      if(iter_tk.eta()>etamax_ || iter_tk.eta()<etamin_) continue;


     double weight = 1.0;
     if( cweight_ ){
       int idx = 0;
       if( feff_ && heff_[idx] ) {
         double eff = heff_[idx]->GetBinContent(heff_[idx]->FindBin(iter_tk.eta(),iter_tk.pt()));
         if( eff != 0. ){
           weight = 1./eff;
         }
       }

     }
     //cout<<" pt = "<<iter_tk.pt()<<"  eta = "<<iter_tk.eta()<<"  weight = "<<weight<<endl;

     if(iter_tk.pt()>0.4 && iter_tk.eta()<2.4 && iter_tk.eta()>-2.4){
       ntrkofflineCorr += weight;
     }
     if(iter_tk.pt()>0.3 && iter_tk.eta()<2.4 && iter_tk.eta()>-2.4){
       ntrkpt03Corr += weight;
     }

     histeta->Fill(iter_tk.eta(), weight);
     histpt->Fill(iter_tk.pt(), weight);

      if(iter_tk.pt() > ptmin_ && iter_tk.pt() < ptmax_ ){
        nM += weight;
        ntracks += 1;

        wsum1 += weight;
        wsum2 += weight*weight;
        wsum3 += weight*weight*weight;
        wsum4 += weight*weight*weight*weight;

        for(int iH=0;iH<nHarmonics;iH++){
          Q2_2[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          Q4_2[iH] += weight*TComplex::Exp(TComplex(0,2*(iH+1)*iter_tk.phi()));
          wQ21[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          wQ42[iH] += weight*weight*TComplex::Exp(TComplex(0,2*(iH+1)*iter_tk.phi()));
          wQ23[iH] += weight*weight*weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
        }

        if(iter_tk.eta() < 0.0 ){
          wsumA00 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQA00[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //A00
        if(iter_tk.eta() < -0.5 ){
          wsumA05 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQA05[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //A05
        if(iter_tk.eta() < -1.0 ){
          wsumA10 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQA10[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //A10
        if(iter_tk.eta() < -1.5 ){
          wsumA15 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQA15[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //A15
        if(iter_tk.eta() > 0.0 ){
          wsumB00 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQB00[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //B00
        if(iter_tk.eta() > 0.5 ){
          wsumB05 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQB05[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //B05
        if(iter_tk.eta() > 1.0 ){
          wsumB10 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQB10[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //B10
        if(iter_tk.eta() > 1.5 ){
          wsumB15 += weight;
          for(int iH=0;iH<nHarmonics;iH++){
            wQB15[iH] += weight*TComplex::Exp(TComplex(0,(iH+1)*iter_tk.phi()));
          }
        } //B15

      } // pt cut

   } // end of reco trk

/*
  int ibin=-1;
   for(int j=0;j<nCentBin;j++){
     if(ntrkoffline>=1*cBin[j]&&ntrkoffline<1*cBin[j+1]){
       ibin=j;
     }
   }
   if(ibin<0 || ibin==nCentBin) return;
*/
   hNtrkOffline[ibin]->Fill(ntrkoffline);

   histntrkOfflineCorr->Fill(ntrkofflineCorr);
   histntrkpt03Corr->Fill(ntrkpt03Corr);


  if(ntracks<4) return;
  nW2 = nM*(nM-1);
  nW4 = nM*(nM-1)*(nM-2)*(nM-3);
  for(int iH=0;iH<nHarmonics;iH++){
    corr_2_2[iH] = (Q2_2[iH]*TComplex::Conjugate(Q2_2[iH]) - nM)/nW2;
    corr_4_2[iH] = ( Q2_2[iH]*Q2_2[iH]*TComplex::Conjugate(Q2_2[iH])*TComplex::Conjugate(Q2_2[iH]) + Q4_2[iH]*TComplex::Conjugate(Q4_2[iH]) -2*(Q4_2[iH]*TComplex::Conjugate(Q2_2[iH])*TComplex::Conjugate(Q2_2[iH])).Re() ).Re()/nW4 - 2*( 2*(nM-2)*Q2_2[iH]*TComplex::Conjugate(Q2_2[iH]) -nM*(nM-3) ).Re()/nW4;
  }

  S21 = wsum1*wsum1;
  S12 = wsum2;
  S41 = wsum1*wsum1*wsum1*wsum1;
  S13 = wsum3;
  S11 = wsum1;
  S22 = wsum2*wsum2;
  S14 = wsum4;
  M11 = S21 - S12;
  M1111 = S41 - 6*S12*S21 + 8*S13*S11 + 3*S22 - 6*S14;
  for(int iH=0;iH<nHarmonics;iH++){
    wcorr_2_2[iH] = (wQ21[iH]*TComplex::Conjugate(wQ21[iH]) - S12)/M11;
    wcorr_4_2[iH] = ( wQ21[iH]*wQ21[iH]*TComplex::Conjugate(wQ21[iH])*TComplex::Conjugate(wQ21[iH]) + wQ42[iH]*TComplex::Conjugate(wQ42[iH]) - 2*(wQ42[iH]*TComplex::Conjugate(wQ21[iH])*TComplex::Conjugate(wQ21[iH])).Re() + 8*(wQ23[iH]*TComplex::Conjugate(wQ21[iH])).Re() - 4*S12*wQ21[iH]*TComplex::Conjugate(wQ21[iH]) - 6*S14 + 2*S22 ).Re()/M1111;
  }
  //"- 2*S22" or "+ 2*S22" ? should be "+"; this is a bug in 1010.0233 (Phys.Rev.C83:044913,2011)

  for(int iH=0;iH<nHarmonics;iH++){
    histCorr2_2[ibin][iH]->Fill(corr_2_2[iH], nW2);
    histCorr4_2[ibin][iH]->Fill(corr_4_2[iH], nW4);
    histwCorr2_2[ibin][iH]->Fill(wcorr_2_2[iH], M11);
    histwCorr4_2[ibin][iH]->Fill(wcorr_4_2[iH], M1111);
  }

  MAB00 = wsumA00*wsumB00;
  MAB05 = wsumA05*wsumB05;
  MAB10 = wsumA10*wsumB10;
  MAB15 = wsumA15*wsumB15;
  for(int iH=0;iH<nHarmonics;iH++){
    wcorr_2_2_AB00[iH] = (wQA00[iH]*TComplex::Conjugate(wQB00[iH]))/MAB00;
    wcorr_2_2_AB05[iH] = (wQA05[iH]*TComplex::Conjugate(wQB05[iH]))/MAB05;
    wcorr_2_2_AB10[iH] = (wQA10[iH]*TComplex::Conjugate(wQB10[iH]))/MAB10;
    wcorr_2_2_AB15[iH] = (wQA15[iH]*TComplex::Conjugate(wQB15[iH]))/MAB15;
  }
  for(int iH=0;iH<nHarmonics;iH++){
    histwCorr2_2_AB00[ibin][iH]->Fill(wcorr_2_2_AB00[iH], MAB00);
    histwCorr2_2_AB05[ibin][iH]->Fill(wcorr_2_2_AB05[iH], MAB05);
    histwCorr2_2_AB10[ibin][iH]->Fill(wcorr_2_2_AB10[iH], MAB10);
    histwCorr2_2_AB15[ibin][iH]->Fill(wcorr_2_2_AB15[iH], MAB15);
  }


#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void TransmutationAna::beginJob() {
  // please remove this method if not needed

  for(int iC=0;iC<nCentBin;iC++){
    for(int iH=0;iH<nHarmonics;iH++){
      histCorr2_2[iC][iH] = fs->make<TH1D>(Form("histCorr2_2_iC%d_iH%d", iC, iH),"",220,-11,11);
      histCorr4_2[iC][iH] = fs->make<TH1D>(Form("histCorr4_2_iC%d_iH%d", iC, iH),"",220,-11,11);
      histwCorr2_2[iC][iH] = fs->make<TH1D>(Form("histwCorr2_2_iC%d_iH%d", iC, iH),"",220,-11,11);
      histwCorr4_2[iC][iH] = fs->make<TH1D>(Form("histwCorr4_2_iC%d_iH%d", iC, iH),"",220,-11,11);
      histwCorr2_2_AB00[iC][iH] = fs->make<TH1D>(Form("histwCorr2_2_AB00_iC%d_iH%d", iC, iH),"",220,-11,11);
      histwCorr2_2_AB05[iC][iH] = fs->make<TH1D>(Form("histwCorr2_2_AB05_iC%d_iH%d", iC, iH),"",220,-11,11);
      histwCorr2_2_AB10[iC][iH] = fs->make<TH1D>(Form("histwCorr2_2_AB10_iC%d_iH%d", iC, iH),"",220,-11,11);
      histwCorr2_2_AB15[iC][iH] = fs->make<TH1D>(Form("histwCorr2_2_AB15_iC%d_iH%d", iC, iH),"",220,-11,11);

      hNtrkOffline[iC] = fs->make<TH1D>(Form("hNtrkOffline_%d", iC),"",700,0,700);

    }
  }

  histcent = fs->make<TH1D>(Form("histcent"),"",200,0,200);
  histntrkOffline = fs->make<TH1D>(Form("histntrkOffline"),"",700,0,700);
  histntrkOfflineCorr = fs->make<TH1D>(Form("histntrkOfflineCorr"),"",700,0,700);
  histntrkpt03 = fs->make<TH1D>(Form("histntrkpt03"),"",700,0,700);
  histntrkpt03Corr = fs->make<TH1D>(Form("histntrkpt03Corr"),"",700,0,700);
  histeta = fs->make<TH1D>(Form("histeta"),"",60,-3,3);
  histpt = fs->make<TH1D>(Form("histpt"),"",50,0,5);
  histetareco = fs->make<TH1D>(Form("histetareco"),"",60,-3,3);
  histptreco = fs->make<TH1D>(Form("histptreco"),"",50,0,5);
  hNtrkOfflineCent = fs->make<TH2D>(Form("hNtrkOfflineCent"),"",200,0,200, 700,0,700);

}

// ------------ method called once each job just after ending the event loop  ------------
void TransmutationAna::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void TransmutationAna::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TransmutationAna);
