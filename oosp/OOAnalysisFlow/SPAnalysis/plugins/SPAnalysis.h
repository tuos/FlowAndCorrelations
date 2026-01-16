#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"

#include "TComplex.h"
#include <vector>
#include <TVector3.h>

  static const int nCentTableBins = 200;
  //static const int nCentBin = 17;
  static const int nCentBin = 7;
  static const int nHarmonics = 5;
  static const int nPtBin = 32;
  //double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  //double cBin[nCentBin+1]={0, 1, 2, 5, 10, 15, 20, 25, 30, 35,40,45,50,55,60, 65,70,80};
  double cBin[nCentBin+1]={0, 5, 10, 20, 30, 40, 50, 60};
  double ptBins[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0, 70.0, 90.0, 110.0, 20000.0};
//oo hijing
double oo_binBoundaries[nCentTableBins+1] ={0, 1.48778, 2.11134, 2.63475, 3.07932, 3.48943, 3.88112, 4.25075, 4.60703, 4.95012, 5.27315, 5.59052,5.89827, 6.20616, 6.50119, 6.78709, 7.06618, 7.34564, 7.62605, 7.90199, 8.17862, 8.46188, 8.7397, 9.01025,9.28914, 9.56577, 9.85825, 10.1514, 10.4491, 10.7428, 11.0476, 11.3478, 11.6658, 11.9788, 12.2991, 12.626,12.9566, 13.2916, 13.6314, 13.9789, 14.3345, 14.6983, 15.0743, 15.4565, 15.8397, 16.2349, 16.6283,17.0423, 17.4618, 17.8919, 18.3214, 18.7681, 19.2346, 19.7038, 20.1688, 20.6487, 21.134, 21.6248, 22.1428,22.6653, 23.1957, 23.735, 24.2847, 24.8467, 25.4301, 26.0071, 26.6183, 27.2169, 27.8177, 28.4655, 29.1053,29.7524, 30.422, 31.1124, 31.7932, 32.4958, 33.2328, 33.9646, 34.7249, 35.5107, 36.2898, 37.1023, 37.9366,38.7735, 39.6324, 40.4903, 41.3676, 42.2762, 43.2068, 44.1519, 45.1307, 46.0988, 47.0835, 48.0923,49.1266, 50.1996, 51.2809, 52.3689, 53.468, 54.587, 55.7205, 56.9057, 58.1209, 59.3641, 60.6206, 61.8839,63.1496, 64.45, 65.7896, 67.1494, 68.5295, 69.9441, 71.3659, 72.799, 74.3073, 75.7982, 77.3601, 78.9258,80.5263, 82.1334, 83.7936, 85.4469, 87.1689, 88.9109, 90.6333, 92.4374, 94.3349, 96.1966, 98.0939,100.062, 102.046, 104.079, 106.106, 108.194, 110.364, 112.559, 114.748, 116.972, 119.272, 121.668,124.048, 126.473, 128.896, 131.478, 134.103, 136.75, 139.435, 142.103, 144.89, 147.796, 150.691, 153.576,156.543, 159.561, 162.656, 165.754, 168.968, 172.187, 175.542, 178.951, 182.362, 185.887, 189.462,193.229, 196.866, 200.631, 204.426, 208.312, 212.38, 216.417, 220.553, 224.778, 229.143, 233.608, 238.205,242.805, 247.531, 252.414, 257.439, 262.605, 267.889, 273.314, 278.883, 284.563, 290.464, 296.645,302.985, 309.823, 316.77, 324.201, 332.174, 340.578, 349.474, 359.268, 369.81, 382.073, 396.549, 413.756,436.379, 471.255, 10752.978};
//new oo
//double oo_binBoundaries[nCentTableBins+1] ={0,0.717572,1.43514,2.15272,2.87029,3.58786,4.30543,5.023,5.74057,6.45815,7.17572,7.89329,8.61086,9.32843,10.046,10.5615,10.9358,11.3222,11.7114,12.1054,12.5071,12.9114,13.3242,13.7529,14.1895,14.6323,15.0788,15.5384,16.0017,16.4718,16.954,17.4529,17.965,18.4818,19.0081,19.5384,20.0798,20.6295,21.1904,21.7624,22.3333,22.9144,23.5082,24.108,24.7103,25.3327,25.9643,26.6021,27.2404,27.8889,28.551,29.2201,29.8838,30.5609,31.2582,31.959,32.6755,33.3996,34.127,34.8736,35.624,36.3835,37.1513,37.9462,38.7306,39.5312,40.3522,41.1784,41.9996,42.8382,43.7007,44.5735,45.4614,46.3438,47.2291,48.1364,49.0614,49.9993,50.9485,51.9135,52.8921,53.8808,54.8964,55.893,56.9136,57.9568,59.0177,60.0888,61.1833,62.2824,63.399,64.5337,65.6807,66.8337,68.0214,69.219,70.4243,71.651,72.9014,74.165,75.4546,76.7537,78.0703,79.4045,80.7569,82.1322,83.5298,84.9421,86.3744,87.8423,89.3304,90.8548,92.361,93.9159,95.4992,97.0799,98.6655,100.303,101.96,103.647,105.32,107.036,108.77,110.55,112.332,114.116,115.936,117.785,119.708,121.683,123.605,125.589,127.588,129.583,131.654,133.746,135.887,138.016,140.191,142.401,144.623,146.867,149.14,151.514,153.909,156.277,158.74,161.209,163.662,166.177,168.728,171.298,173.901,176.575,179.302,182.038,184.793,187.576,190.47,193.355,196.279,199.296,202.355,205.406,208.567,211.746,215.007,218.296,221.624,224.981,228.464,231.972,235.5,239.147,242.785,246.538,250.308,254.2,258.246,262.353,266.531,270.819,275.228,279.794,284.51,289.356,294.368,299.561,305.114,310.888,316.984,323.451,330.516,337.981,346.265,355.527,366.193,379.001,395.659,421.298,10000};
//new nene
double nene_binBoundaries[nCentTableBins+1] ={0,0.796165,1.59233,2.3885,3.18466,3.98083,4.77699,5.57316,6.36932,7.16549,7.96165,8.75782,9.55398,10.3419,10.7459,11.1487,11.5557,11.9765,12.3958,12.8224,13.2575,13.7055,14.169,14.6409,15.131,15.6285,16.1319,16.6369,17.1592,17.6922,18.2389,18.7954,19.3801,19.9707,20.5712,21.181,21.795,22.4167,23.0559,23.688,24.3333,25.0232,25.6847,26.366,27.0754,27.7975,28.5169,29.2585,30.0149,30.7655,31.5565,32.3414,33.1446,33.9552,34.7554,35.5799,36.4235,37.2709,38.1186,38.9817,39.876,40.7619,41.6532,42.5763,43.5095,44.4509,45.441,46.4229,47.4092,48.4152,49.4382,50.4775,51.5114,52.5722,53.6107,54.7073,55.8258,56.9313,58.0735,59.2244,60.3905,61.5803,62.7754,63.9791,65.207,66.4599,67.7295,69,70.2905,71.5994,72.9536,74.3647,75.7388,77.1391,78.6117,80.0714,81.5776,83.0758,84.5599,86.1067,87.6935,89.2532,90.8864,92.5324,94.1888,95.8598,97.5337,99.3035,101.063,102.856,104.653,106.51,108.354,110.208,112.087,113.988,116.017,118.019,120.009,122.028,124.098,126.204,128.262,130.478,132.636,134.851,137.051,139.344,141.672,143.971,146.403,148.866,151.302,153.751,156.341,158.886,161.498,164.124,166.743,169.48,172.182,174.888,177.683,180.585,183.401,186.342,189.27,192.243,195.327,198.388,201.58,204.781,208.052,211.405,214.7,217.998,221.41,224.906,228.41,231.989,235.662,239.378,243.093,246.897,250.762,254.688,258.664,262.633,266.688,270.844,274.934,279.274,283.731,288.117,292.555,297.233,302.007,306.79,311.65,316.716,321.818,327.039,332.417,337.989,343.573,349.285,355.543,362.012,368.619,375.276,382.614,390.501,398.567,407.709,417.137,428.164,440.928,456.362,476.098,505.708,10000};

  TH1D* hQhfPlusX[nCentBin][nHarmonics];
  TH1D* hQhfPlusY[nCentBin][nHarmonics];
  TH1D* hQhfMinusX[nCentBin][nHarmonics];
  TH1D* hQhfMinusY[nCentBin][nHarmonics];
  TH1D* hQhfMinusPlusX[nCentBin][nHarmonics];
  TH1D* hQhfMinusPlusY[nCentBin][nHarmonics];
  TH1D* hQDEMinusPlusX[nCentBin][nHarmonics];
  TH1D* hQDEMinusPlusY[nCentBin][nHarmonics];
  TH1D* hQtrkPtPlusX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtPlusY[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtMinusX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtMinusY[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkMidX[nCentBin][nHarmonics];
  TH1D* hQtrkMidY[nCentBin][nHarmonics];
  TH1D* hQtrkPtMidX[nCentBin][nHarmonics][nPtBin];
  TH1D* hQtrkPtMidY[nCentBin][nHarmonics][nPtBin];

double meanQhfPlusX[nCentBin][nHarmonics];
double meanQhfPlusY[nCentBin][nHarmonics];
double meanQhfMinusX[nCentBin][nHarmonics];
double meanQhfMinusY[nCentBin][nHarmonics];
double meanQhfMinusPlusX[nCentBin][nHarmonics];
double meanQhfMinusPlusY[nCentBin][nHarmonics];
double meanQDEMinusPlusX[nCentBin][nHarmonics];
double meanQDEMinusPlusY[nCentBin][nHarmonics];
double meanQtrkPtPlusX[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtPlusY[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtMinusX[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtMinusY[nCentBin][nHarmonics][nPtBin];
double meanQtrkMidX[nCentBin][nHarmonics];
double meanQtrkMidY[nCentBin][nHarmonics];
double meanQtrkPtMidX[nCentBin][nHarmonics][nPtBin];
double meanQtrkPtMidY[nCentBin][nHarmonics][nPtBin];
// comment out below if don't need re-centering

double OOmeanQhfPlusX[nCentBin][nHarmonics]={{0}};
double OOmeanQhfPlusY[nCentBin][nHarmonics]={{0}};
double OOmeanQhfMinusX[nCentBin][nHarmonics]={{0}};
double OOmeanQhfMinusY[nCentBin][nHarmonics]={{0}};
double OOmeanQhfMinusPlusX[nCentBin][nHarmonics]={{0}};
double OOmeanQhfMinusPlusY[nCentBin][nHarmonics]={{0}};
double OOmeanQDEMinusPlusX[nCentBin][nHarmonics]={{0}};
double OOmeanQDEMinusPlusY[nCentBin][nHarmonics]={{0}};
double OOmeanQtrkPtPlusX[nCentBin][nHarmonics][nPtBin]={{{0}}};
double OOmeanQtrkPtPlusY[nCentBin][nHarmonics][nPtBin]={{{0}}};
double OOmeanQtrkPtMinusX[nCentBin][nHarmonics][nPtBin]={{{0}}};
double OOmeanQtrkPtMinusY[nCentBin][nHarmonics][nPtBin]={{{0}}};
double OOmeanQtrkMidX[nCentBin][nHarmonics]={{0}};
double OOmeanQtrkMidY[nCentBin][nHarmonics]={{0}};
double OOmeanQtrkPtMidX[nCentBin][nHarmonics][nPtBin]={{{0}}};
double OOmeanQtrkPtMidY[nCentBin][nHarmonics][nPtBin]={{{0}}};

double NeNemeanQhfPlusX[nCentBin][nHarmonics]={{0}};
double NeNemeanQhfPlusY[nCentBin][nHarmonics]={{0}};
double NeNemeanQhfMinusX[nCentBin][nHarmonics]={{0}};
double NeNemeanQhfMinusY[nCentBin][nHarmonics]={{0}};
double NeNemeanQhfMinusPlusX[nCentBin][nHarmonics]={{0}};
double NeNemeanQhfMinusPlusY[nCentBin][nHarmonics]={{0}};
double NeNemeanQDEMinusPlusX[nCentBin][nHarmonics]={{0}};
double NeNemeanQDEMinusPlusY[nCentBin][nHarmonics]={{0}};
double NeNemeanQtrkPtPlusX[nCentBin][nHarmonics][nPtBin]={{{0}}};
double NeNemeanQtrkPtPlusY[nCentBin][nHarmonics][nPtBin]={{{0}}};
double NeNemeanQtrkPtMinusX[nCentBin][nHarmonics][nPtBin]={{{0}}};
double NeNemeanQtrkPtMinusY[nCentBin][nHarmonics][nPtBin]={{{0}}};
double NeNemeanQtrkMidX[nCentBin][nHarmonics]={{0}};
double NeNemeanQtrkMidY[nCentBin][nHarmonics]={{0}};
double NeNemeanQtrkPtMidX[nCentBin][nHarmonics][nPtBin]={{{0}}};
double NeNemeanQtrkPtMidY[nCentBin][nHarmonics][nPtBin]={{{0}}};

// end of comment out

//#include "OOAnalysisFlow/SPAnalysis/plugins/ReCenteringOO.h"    //need to add meanQhfMinusPlusX and meanQhfMinusPlusY values in the header file, also DE
//#include "OOAnalysisFlow/SPAnalysis/plugins/ReCenteringNeNe.h"  //need to add meanQhfMinusPlusX and meanQhfMinusPlusY values in the header file, also DE



