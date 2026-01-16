// -*- C++ -*-
//
// Package:    OOAnalysisFlow/VnMptAnalysis
// Class:      VnMptAnalysis
//
/**\class VnMptAnalysis VnMptAnalysis.cc OOAnalysisFlow/VnMptAnalysis/plugins/VnMptAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Fri, 15 Jun 2025 18:45:46 GMT
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

class VnMptAnalysis : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit VnMptAnalysis(const edm::ParameterSet&);
  ~VnMptAnalysis();

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

//  static const int nCentBin = 17;
  //double cBin[nCentBin+1]={0,0.5,1,2,5,10,15,20,25,30,35,40,45,50,55,60,70,80};
//  double cBin[nCentBin+1]={0, 1, 2, 5, 10, 15, 20, 25, 30, 35,40,45,50,55,60, 65,70,80};
  static const int nCentTableBins = 200; 
  //OO HIJING centrality table: 
  //double binBoundaries[nCentTableBins+1]={0, 6.3001, 7.13057, 7.70962, 8.21613, 8.66242, 9.09091, 9.47615, 9.86487, 10.2341, 10.5986, 10.9659, 11.3217, 11.6825, 12.0364, 12.41, 12.7813, 13.1588, 13.5367, 13.9152, 14.3296, 14.7389, 15.1436, 15.5538, 15.9485, 16.3635, 16.7772, 17.2032, 17.6336, 18.0644, 18.5021, 18.9341, 19.407, 19.8818, 20.3653, 20.8724, 21.3778, 21.8833, 22.3785, 22.8692, 23.3766, 23.8907, 24.4356, 24.9814, 25.5499, 26.1281, 26.6729, 27.2151, 27.7801, 28.3647, 28.9836, 29.5836, 30.1697, 30.7425, 31.3325, 31.9313, 32.583, 33.2323, 33.8543, 34.5307, 35.2181, 35.9333, 36.6216, 37.3148, 38.0189, 38.7402, 39.4722, 40.2238, 40.999, 41.727, 42.4761, 43.2031, 44.0191, 44.8595, 45.6214, 46.3781, 47.1921, 48.0047, 48.8638, 49.6999, 50.5448, 51.4153, 52.297, 53.1974, 54.0732, 55.034, 55.9939, 56.9114, 57.8072, 58.7552, 59.6815, 60.6325, 61.5624, 62.5473, 63.613, 64.6638, 65.6895, 66.6933, 67.7693, 68.8656, 69.9956, 71.1721, 72.3021, 73.4473, 74.6121, 75.8068, 76.9958, 78.2384, 79.4669, 80.7119, 82.0729, 83.3979, 84.6671, 85.953, 87.2368, 88.6348, 90.0819, 91.5066, 92.9948, 94.5071, 96.0272, 97.6763, 99.2236, 100.775, 102.38, 104.031, 105.581, 107.181, 108.801, 110.35, 111.99, 113.787, 115.632, 117.503, 119.451, 121.328, 123.159, 125.072, 126.963, 128.959, 131.102, 133.236, 135.348, 137.528, 139.723, 141.99, 144.496, 146.903, 149.26, 151.532, 153.93, 156.187, 158.691, 161.232, 163.799, 166.407, 169.033, 171.821, 174.715, 177.624, 180.401, 183.277, 186.154, 189.168, 192.077, 195.255, 198.37, 201.568, 204.791, 208.298, 211.817, 215.423, 218.828, 222.204, 226.027, 229.857, 233.917, 238.012, 242.119, 246.234, 250.615, 254.994, 259.526, 264.501, 269.742, 274.927, 280.131, 285.572, 291.029, 297.21, 303.535, 310.285, 317.396, 325.399, 334.131, 343.799, 355.777, 369.298, 385.341, 411.371, 10000.0}; 
  //OO ANGANTYR centrality table: 
  //double binBoundaries[nCentTableBins+1]={0, 6.24735, 7.09477, 7.65907, 8.1739, 8.61813, 9.05307, 9.43186, 9.81568, 10.1855, 10.5456, 10.9021, 11.2568, 11.6118, 11.9691, 12.3351, 12.7092, 13.0776, 13.4528, 13.8322, 14.2393, 14.6534, 15.0591, 15.4575, 15.8526, 16.2654, 16.689, 17.1122, 17.5416, 17.966, 18.405, 18.8479, 19.3054, 19.7803, 20.2707, 20.779, 21.28, 21.7844, 22.2814, 22.7687, 23.277, 23.7881, 24.3229, 24.8758, 25.4393, 26.013, 26.5624, 27.1053, 27.667, 28.2504, 28.8809, 29.4773, 30.0702, 30.644, 31.2437, 31.8424, 32.4853, 33.1392, 33.7653, 34.4335, 35.1162, 35.8366, 36.5279, 37.217, 37.9294, 38.6364, 39.3586, 40.1125, 40.8834, 41.6207, 42.3612, 43.112, 43.897, 44.7381, 45.5233, 46.2798, 47.0892, 47.9076, 48.7532, 49.5882, 50.4415, 51.3117, 52.2077, 53.0913, 53.9641, 54.9212, 55.883, 56.7888, 57.6876, 58.629, 59.5798, 60.514, 61.4542, 62.463, 63.5335, 64.58, 65.6077, 66.6151, 67.6997, 68.8106, 69.9308, 71.1127, 72.2437, 73.394, 74.5516, 75.7338, 76.9275, 78.1769, 79.4114, 80.6464, 81.9806, 83.3037, 84.5937, 85.8611, 87.1341, 88.5379, 89.9981, 91.3965, 92.8784, 94.4058, 95.9348, 97.595, 99.1441, 100.696, 102.311, 103.936, 105.481, 107.087, 108.737, 110.314, 111.943, 113.749, 115.584, 117.472, 119.433, 121.298, 123.119, 125.025, 126.928, 128.922, 131.039, 133.178, 135.311, 137.467, 139.673, 141.91, 144.424, 146.843, 149.213, 151.492, 153.918, 156.18, 158.643, 161.175, 163.782, 166.411, 169.065, 171.839, 174.711, 177.616, 180.429, 183.289, 186.187, 189.179, 192.115, 195.305, 198.441, 201.674, 204.848, 208.346, 211.812, 215.439, 218.853, 222.288, 226.084, 229.936, 233.962, 238.061, 242.141, 246.231, 250.633, 255.049, 259.58, 264.547, 269.83, 274.959, 280.228, 285.613, 291.123, 297.255, 303.547, 310.379, 317.402, 325.208, 333.834, 343.575, 355.543, 369.181, 385.26, 410.786, 10000.0};

  //NeNe HIJING centrality table: 
  //double binBoundaries[nCentTableBins+1]={0, 6.31488, 7.12588, 7.7275, 8.24452, 8.7024, 9.14064, 9.55405, 9.97121, 10.3709, 10.7727, 11.169, 11.5489, 11.9349, 12.33, 12.733, 13.1384, 13.558, 13.9747, 14.3924, 14.8212, 15.26, 15.7162, 16.1901, 16.6485, 17.1105, 17.581, 18.0641, 18.5659, 19.067, 19.5696, 20.0664, 20.5834, 21.103, 21.635, 22.1936, 22.7705, 23.3517, 23.9265, 24.5203, 25.122, 25.7209, 26.3367, 26.9564, 27.5775, 28.222, 28.8676, 29.4847, 30.1119, 30.7558, 31.4431, 32.1531, 32.8437, 33.5629, 34.2947, 35.0148, 35.7573, 36.4937, 37.2233, 37.9615, 38.7213, 39.5147, 40.3284, 41.154, 42.0035, 42.8577, 43.71, 44.592, 45.4872, 46.329, 47.1918, 48.0421, 48.9601, 49.8728, 50.7826, 51.7198, 52.701, 53.6253, 54.6086, 55.623, 56.6189, 57.6336, 58.6542, 59.7393, 60.7733, 61.8463, 62.9675, 64.0924, 65.209, 66.3394, 67.4669, 68.6262, 69.7462, 70.8787, 72.1424, 73.3887, 74.7029, 75.9867, 77.2752, 78.5643, 79.9069, 81.293, 82.7244, 84.0992, 85.563, 87.0793, 88.5103, 89.9453, 91.4802, 93.0497, 94.6074, 96.1923, 97.7948, 99.4569, 101.036, 102.743, 104.551, 106.287, 107.997, 109.781, 111.597, 113.482, 115.344, 117.326, 119.353, 121.387, 123.337, 125.388, 127.382, 129.458, 131.577, 133.666, 135.896, 138.095, 140.351, 142.652, 144.79, 147.124, 149.36, 151.801, 154.326, 156.854, 159.493, 162.119, 164.686, 167.276, 170.039, 172.871, 175.601, 178.504, 181.308, 184.267, 187.298, 190.353, 193.532, 196.795, 200, 203.513, 206.826, 210.261, 213.782, 217.345, 220.827, 224.539, 228.173, 232.035, 235.904, 240.02, 244.472, 248.682, 252.907, 257.092, 261.339, 265.79, 270.584, 275.34, 280.306, 285.396, 290.443, 295.703, 300.538, 305.925, 311.559, 317.166, 323.493, 329.927, 336.413, 343.624, 350.628, 358.366, 365.607, 373.535, 382.043, 392.137, 402.109, 413.901, 426.79, 442.949, 462.951, 494.589, 10000.0};

//NeNe ANGANTYR centrality table: 
//double binBoundaries[nCentTableBins+1]={0, 6.27884, 7.09805, 7.6818, 8.20482, 8.65703, 9.09717, 9.50091, 9.9076, 10.3027, 10.6953, 11.0825, 11.4551, 11.8343, 12.2225, 12.6154, 13.0173, 13.4257, 13.8394, 14.2556, 14.6805, 15.1084, 15.5621, 16.0174, 16.4766, 16.9386, 17.4151, 17.8915, 18.3899, 18.8834, 19.3866, 19.8931, 20.4015, 20.9122, 21.4542, 22.0018, 22.5742, 23.149, 23.7286, 24.3094, 24.9119, 25.5124, 26.1126, 26.7405, 27.3648, 27.9901, 28.6449, 29.2704, 29.8892, 30.5357, 31.2207, 31.9231, 32.6247, 33.3293, 34.0851, 34.8022, 35.5368, 36.2817, 37.0176, 37.7486, 38.5057, 39.2946, 40.1035, 40.9242, 41.7815, 42.6173, 43.4622, 44.3484, 45.2397, 46.0929, 46.9407, 47.8297, 48.7092, 49.6272, 50.5547, 51.4809, 52.4663, 53.403, 54.3532, 55.3579, 56.3824, 57.3933, 58.4305, 59.4776, 60.5288, 61.592, 62.7069, 63.8167, 64.9288, 66.0663, 67.2118, 68.3642, 69.4917, 70.6638, 71.9113, 73.1432, 74.473, 75.7602, 77.054, 78.3647, 79.7049, 81.0852, 82.5138, 83.8974, 85.3417, 86.843, 88.2792, 89.7321, 91.2555, 92.8235, 94.3551, 95.9249, 97.5696, 99.196, 100.788, 102.474, 104.303, 105.986, 107.734, 109.522, 111.336, 113.25, 115.09, 117.073, 119.121, 121.12, 123.059, 125.1, 127.167, 129.248, 131.38, 133.477, 135.681, 137.902, 140.183, 142.479, 144.59, 146.923, 149.186, 151.605, 154.107, 156.645, 159.294, 161.905, 164.467, 167.03, 169.811, 172.65, 175.404, 178.315, 181.148, 184.123, 187.079, 190.116, 193.357, 196.648, 199.889, 203.417, 206.665, 210.082, 213.676, 217.219, 220.727, 224.426, 228.084, 231.962, 235.874, 240.011, 244.409, 248.623, 252.768, 257.001, 261.248, 265.767, 270.516, 275.326, 280.243, 285.336, 290.361, 295.586, 300.472, 305.881, 311.517, 317.122, 323.515, 329.87, 336.421, 343.601, 350.643, 358.34, 365.539, 373.557, 381.969, 391.875, 401.703, 413.612, 426.43, 442.698, 462.788, 493.921, 10000.0};

//new oo
double binBoundaries[nCentTableBins+1] ={0,0.717572,1.43514,2.15272,2.87029,3.58786,4.30543,5.023,5.74057,6.45815,7.17572,7.89329,8.61086,9.32843,10.046,10.5615,10.9358,11.3222,11.7114,12.1054,12.5071,12.9114,13.3242,13.7529,14.1895,14.6323,15.0788,15.5384,16.0017,16.4718,16.954,17.4529,17.965,18.4818,19.0081,19.5384,20.0798,20.6295,21.1904,21.7624,22.3333,22.9144,23.5082,24.108,24.7103,25.3327,25.9643,26.6021,27.2404,27.8889,28.551,29.2201,29.8838,30.5609,31.2582,31.959,32.6755,33.3996,34.127,34.8736,35.624,36.3835,37.1513,37.9462,38.7306,39.5312,40.3522,41.1784,41.9996,42.8382,43.7007,44.5735,45.4614,46.3438,47.2291,48.1364,49.0614,49.9993,50.9485,51.9135,52.8921,53.8808,54.8964,55.893,56.9136,57.9568,59.0177,60.0888,61.1833,62.2824,63.399,64.5337,65.6807,66.8337,68.0214,69.219,70.4243,71.651,72.9014,74.165,75.4546,76.7537,78.0703,79.4045,80.7569,82.1322,83.5298,84.9421,86.3744,87.8423,89.3304,90.8548,92.361,93.9159,95.4992,97.0799,98.6655,100.303,101.96,103.647,105.32,107.036,108.77,110.55,112.332,114.116,115.936,117.785,119.708,121.683,123.605,125.589,127.588,129.583,131.654,133.746,135.887,138.016,140.191,142.401,144.623,146.867,149.14,151.514,153.909,156.277,158.74,161.209,163.662,166.177,168.728,171.298,173.901,176.575,179.302,182.038,184.793,187.576,190.47,193.355,196.279,199.296,202.355,205.406,208.567,211.746,215.007,218.296,221.624,224.981,228.464,231.972,235.5,239.147,242.785,246.538,250.308,254.2,258.246,262.353,266.531,270.819,275.228,279.794,284.51,289.356,294.368,299.561,305.114,310.888,316.984,323.451,330.516,337.981,346.265,355.527,366.193,379.001,395.659,421.298,10000};

//new nene
//double binBoundaries[nCentTableBins+1] = {0, 0.719255, 1.4342, 2.15771, 2.88021, 3.60442, 4.32898, 5.06429, 5.80245, 6.54448, 7.29359, 8.03948, 8.78366, 9.52997, 10.291, 10.8364, 11.2413, 11.6657, 12.0903, 12.5205, 12.9362, 13.3679, 13.828, 14.3155, 14.8123, 15.3003, 15.8012, 16.316, 16.8477, 17.386, 17.9322, 18.4966, 19.054, 19.617, 20.1932, 20.7752, 21.3879, 22.0138, 22.6562, 23.3336, 24.0008, 24.6698, 25.3371, 26.014, 26.6713, 27.3629, 28.1007, 28.8206, 29.5269, 30.2399, 30.9738, 31.758, 32.5325, 33.3646, 34.2134, 35.0452, 35.8588, 36.6774, 37.5231, 38.3385, 39.1676, 40.0098, 40.9117, 41.8504, 42.7898, 43.7328, 44.6845, 45.6503, 46.5973, 47.5628, 48.5524, 49.566, 50.5643, 51.523, 52.5722, 53.6806, 54.7885, 55.8534, 56.9384, 58.1004, 59.2483, 60.3973, 61.5696, 62.7664, 63.9656, 65.1309, 66.3679, 67.6707, 69.0174, 70.3219, 71.6693, 73.0417, 74.412, 75.7361, 77.1419, 78.5585, 80.0874, 81.6352, 83.1272, 84.61, 86.1389, 87.6683, 89.3241, 90.9204, 92.6097, 94.3453, 96.0214, 97.6521, 99.4319, 101.27, 102.973, 104.793, 106.682, 108.671, 110.605, 112.532, 114.513, 116.504, 118.408, 120.398, 122.397, 124.356, 126.441, 128.706, 130.955, 133.155, 135.433, 137.793, 140.152, 142.753, 145.223, 147.53, 149.947, 152.292, 154.689, 157.253, 159.753, 162.35, 164.921, 167.624, 170.242, 172.901, 175.745, 178.606, 181.406, 184.107, 186.801, 189.706, 192.545, 195.756, 198.738, 202.095, 205.25, 208.467, 211.849, 215.28, 218.647, 222.174, 225.477, 228.882, 232.598, 236.342, 240.046, 243.813, 247.762, 251.632, 255.689, 259.939, 264.567, 268.599, 272.783, 276.842, 281.25, 286.056, 290.646, 295.322, 299.948, 304.807, 309.789, 315.06, 319.624, 324.911, 330.409, 335.504, 341.204, 347.243, 353.51, 360.457, 367.597, 374.858, 381.806, 389.385, 397.835, 407.3, 416.712, 428.02, 439.285, 454.587, 475.347, 506.524, 10000};




//ntrkbin
  static const int nCentBin = 17;
  double cBin[nCentBin+1]={0, 20, 40, 60, 80, 100, 120, 150, 180, 210, 250, 300, 350, 400, 450, 500, 550, 600};


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
VnMptAnalysis::VnMptAnalysis(const edm::ParameterSet& iConfig) : 
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
      edm::FileInPath fip(Form("OOAnalysisFlow/VnMptAnalysis/data/%s",filename.Data()));
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

VnMptAnalysis::~VnMptAnalysis() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void VnMptAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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

/*
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
*/


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


  int ibin=-1;
   for(int j=0;j<nCentBin;j++){
     if(ntrkoffline>=1*cBin[j]&&ntrkoffline<1*cBin[j+1]){
       ibin=j;
     }
   }
   if(ibin<0 || ibin==nCentBin) return;


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
void VnMptAnalysis::beginJob() {
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
void VnMptAnalysis::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void VnMptAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(VnMptAnalysis);
