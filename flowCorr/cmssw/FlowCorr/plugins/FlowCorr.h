#include "TComplex.h"
#include <vector>
#include <TVector3.h>

#define nCentBin 14
#define nHarmonics 8
#define nPtBin 20 

using namespace std;
using namespace reco;
using namespace edm;

  bool useReDenominator = true;
  bool useRe = true;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double ptBin[nPtBin+1]={0.3, 0.4, 0.5, 0.6, 0.8, 1.0, 1.25, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0, 20.0};
  const int nPtEffBin=53;
  double effValues[nPtEffBin]={1.75224e-06, 1.75224e-06, 1.75224e-06, 2.81152e-06, 0.0161021, 0.404592, 0.512024, 0.567472, 0.609648, 0.641969, 0.667275, 0.686959, 0.701743, 0.714321, 0.724036, 0.731289, 0.737636, 0.742844, 0.747634, 0.751305, 0.754174, 0.756644, 0.759267, 0.760998, 0.763125, 0.765678, 0.771412, 0.791967, 0.818874, 0.828377, 0.758442, 0.742433, 0.734321, 0.724238, 0.714218, 0.707938, 0.703684, 0.698056, 0.698776, 0.69683, 0.694334, 0.687844, 0.688473, 0.689227, 0.681, 0.683338, 0.687782, 0.671698, 0.680891, 0.673665, 0.669277, 0.681149, 0.681149};
  double ptBinValues[nPtEffBin+1] = {0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.05, 1.1, 1.15, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.8, 3.2, 3.6, 4, 4.4, 4.8, 5.2, 5.6, 6, 6.4, 6.8, 7.2, 8.4, 9.6, 10.8, 10000};
  TH1D *EffVsPtHist = new TH1D("EffVsPtHist","",nPtEffBin, ptBinValues);
  TComplex QhfPlus[nCentBin][nHarmonics];
  TComplex QhfMinus[nCentBin][nHarmonics];
  TComplex Qhf2p2Plus[nCentBin];
  TComplex Qhf2p2Minus[nCentBin];
  TComplex Qhf2p3Plus[nCentBin];
  TComplex Qhf2p3Minus[nCentBin];
  TComplex Qhf3p3Plus[nCentBin];
  TComplex Qhf3p3Minus[nCentBin];
  TComplex Qhf2p2p2Plus[nCentBin];
  TComplex Qhf2p2p2Minus[nCentBin];
  TComplex Qhf2p2p3Plus[nCentBin];
  TComplex Qhf2p2p3Minus[nCentBin];
  double sumWPlus[nCentBin];
  double sumW2Plus[nCentBin];
  double sumW3Plus[nCentBin];
  double sumWMinus[nCentBin];
  double sumW2Minus[nCentBin];
  double sumW3Minus[nCentBin];
  TComplex QtrkPlus[nCentBin][nHarmonics];
  TComplex QtrkMinus[nCentBin][nHarmonics];
  TComplex QtrkAll[nCentBin][nHarmonics];
  TComplex QtrkPlus1[nCentBin][nHarmonics];
  TComplex QtrkMinus1[nCentBin][nHarmonics];
  double VnAbs2[nCentBin][nHarmonics]={{0.0},{0.0}};
  double VnAbs4[nCentBin][nHarmonics]={{0.0},{0.0}};
  double VnAbs6[nCentBin][nHarmonics]={{0.0},{0.0}};
  double V2Abs2V3Abs2[nCentBin]={0.0};
  double V2Abs4V3Abs2[nCentBin]={0.0};
  double V4V2starV2star[nCentBin]={0.0};
  double V6V2starV2starV2star[nCentBin]={0.0};
  double V6V3starV3star[nCentBin]={0.0};
  double V5V2starV3star[nCentBin]={0.0};
  double V7V2starV2starV3star[nCentBin]={0.0};
  double v2Psi2[nCentBin]={0.0};
  double v3Psi3[nCentBin]={0.0};
  double v4Psi2[nCentBin]={0.0};
  double v4Psi4[nCentBin]={0.0};
  double v6Psi2[nCentBin]={0.0};
  double v6Psi3[nCentBin]={0.0};
  double v6Psi6[nCentBin]={0.0};
  double v5Psi2Psi3[nCentBin]={0.0};
  double v7Psi2Psi3[nCentBin]={0.0};
  int nEvent[nCentBin]={0};

  vector<TVector3> *pVect_trkEtaPlus;
  vector<TVector3> *pVect_trkEtaMinus;  
  vector<TVector3> *pVect_hfEtaPlus;
  vector<TVector3> *pVect_hfEtaMinus;  

  TH1D* hMultTrkEtaPlus;
  TH1D* hMultTrkEtaMinus;
  TH1D* hMultHFEtaPlus;
  TH1D* hMultHFEtaMinus;
  TH1D* hQhfPlusX[nCentBin][nHarmonics];
  TH1D* hQhfPlusY[nCentBin][nHarmonics];
  TH1D* hQhfPlusQ[nCentBin][nHarmonics];
  TH1D* hQhfMinusX[nCentBin][nHarmonics];
  TH1D* hQhfMinusY[nCentBin][nHarmonics];
  TH1D* hQhfMinusQ[nCentBin][nHarmonics];
  TH1D* hVnAbs2[nCentBin][nHarmonics];
  TH1D* hVnAbs4[nCentBin][nHarmonics];
  TH1D* hVnAbs6[nCentBin][nHarmonics];
  TH1D* hVnAbs8[nCentBin][nHarmonics];
  TH1D* hV2Abs2V3Abs2[nCentBin];
  TH1D* hV2Abs4V3Abs2[nCentBin];
  TH1D* hV2Abs2V3Abs4[nCentBin];
  //trk 
  TH1D* hV2Abs4trk1[nCentBin];
  TH1D* hV2Abs6trk1[nCentBin];
  TH1D* hV3Abs4trk1[nCentBin];
  TH1D* hV2Abs2V3Abs2trk1[nCentBin];
  TH1D* hV2Abs4V3Abs2trk1[nCentBin];
  TH1D* hV2Abs4trk12[nCentBin];
  TH1D* hV2Abs6trk12[nCentBin];
  TH1D* hV3Abs4trk12[nCentBin];
  TH1D* hV2Abs2V3Abs2trk12[nCentBin];
  TH1D* hV2Abs4V3Abs2trk12[nCentBin];
  TH1D* hV2Abs4trk2[nCentBin];
  TH1D* hV2Abs6trk2[nCentBin];
  TH1D* hV3Abs4trk2[nCentBin];
  TH1D* hV2Abs2V3Abs2trk2[nCentBin];
  TH1D* hV2Abs4V3Abs2trk2[nCentBin];

  //only Qtrk
  TH1D* hV2V2starQtrk[nCentBin];
  TH1D* hV4V2starV2starQtrk[nCentBin];
  TH1D* hV6V2starV2starV2starQtrk[nCentBin];
  TH1D* hV6V3starV3starQtrk[nCentBin];
  TH1D* hV5V2starV3starQtrk[nCentBin];
  TH1D* hV7V2starV2starV3starQtrk[nCentBin];
  TH1D* hV2Abs2Qtrk[nCentBin];
  TH1D* hV2Abs4Qtrk[nCentBin];
  TH1D* hV2Abs6Qtrk[nCentBin];
  TH1D* hV3Abs4Qtrk[nCentBin];
  TH1D* hV2Abs2V3Abs2Qtrk[nCentBin];
  TH1D* hV2Abs4V3Abs2Qtrk[nCentBin];

  TH1D* hV2V2star[nCentBin];
  TH1D* hV4V2starV2star[nCentBin];
  TH1D* hV6V2starV2starV2star[nCentBin];
  TH1D* hV6V3starV3star[nCentBin];
  TH1D* hV5V2starV3star[nCentBin];
  TH1D* hV7V2starV2starV3star[nCentBin];

  TH1D* hv2V2star[nCentBin][nPtBin];
  TH1D* hv3V3star[nCentBin][nPtBin];
  TH1D* hv4V4star[nCentBin][nPtBin];
  TH1D* hv5V5star[nCentBin][nPtBin];
  TH1D* hv6V6star[nCentBin][nPtBin];
  TH1D* hv7V7star[nCentBin][nPtBin];
  TH1D* hv8V8star[nCentBin][nPtBin];
  TH1D* hv4V2starV2star[nCentBin][nPtBin];
  TH1D* hv4V2starV2starAB[nCentBin][nPtBin];
  TH1D* hv4V2starV2starSub[nCentBin][nPtBin];
  TH1D* hv6V2starV2starV2star[nCentBin][nPtBin];
  TH1D* hv6V2starV2starV2starAB[nCentBin][nPtBin];
  TH1D* hv6V2starV2starV2starSub[nCentBin][nPtBin];
  TH1D* hv6V3starV3star[nCentBin][nPtBin];
  TH1D* hv6V3starV3starAB[nCentBin][nPtBin];
  TH1D* hv6V3starV3starSub[nCentBin][nPtBin];
  TH1D* hv5V2starV3star[nCentBin][nPtBin];
  TH1D* hv5V2starV3starAB[nCentBin][nPtBin];
  TH1D* hv5V2starV3starSub[nCentBin][nPtBin];
  TH1D* hv7V2starV2starV3star[nCentBin][nPtBin];
  TH1D* hv7V2starV2starV3starAB[nCentBin][nPtBin];
  TH1D* hv7V2starV2starV3starSub[nCentBin][nPtBin];
  TH1D* hv8V2starV2starV2starV2star[nCentBin][nPtBin];
  TH1D* hv8V2starV3starV3star[nCentBin][nPtBin];

  TH1D* hMeanPt[nCentBin][nPtBin];


   TH1D* hCent;
   TH1D* hHF;
   TH1D* hAngle;
   TH1D* hAngleFlat;
   TH1D* hvz;
   TH1D* hvx;
   TH1D* hvy;
   TH1D* hNtrks;
   TH1D* hpt;
   TH1D* heta;
   TH1D* hphi;
   TH1D* hHFcal;



double meanQxPlus[nCentBin][nHarmonics] = {{0.00825394, -0.002366, 0.00335968, -0.00403341, 0.00142318, -0.00130036, 0.00346142, 0.000684958}, 
{0.00821248, -0.00228186, 0.00350078, -0.00392578, 0.00141706, -0.00126484, 0.0035313, 0.000631731}, 
{0.00802684, -0.00241586, 0.00360015, -0.00409037, 0.00123659, -0.00122714, 0.00354833, 0.000702675}, 
{0.00772891, -0.00230305, 0.00333725, -0.00394181, 0.00118928, -0.00107683, 0.00342684, 0.000962489}, 
{0.00755016, -0.00250065, 0.00330241, -0.00393604, 0.000971704, -0.00091989, 0.00319015, 0.0011866}, 
{0.00715301, -0.00214753, 0.00308202, -0.0038082, 0.000807681, -0.000972679, 0.00312581, 0.00134877}, 
{0.00688948, -0.00209304, 0.00307493, -0.00373098, 0.000672834, -0.000980074, 0.00299581, 0.00151541}, 
{0.00678849, -0.00153857, 0.00291358, -0.00372597, 0.000461928, -0.000814222, 0.0028087, 0.00172561}, 
{0.00662455, -0.00217182, 0.00279903, -0.00363684, 0.000424378, -0.000873318, 0.00275034, 0.00177762}, 
{0.00572529, -0.00217481, 0.00280419, -0.00364667, 0.000161109, -0.000830263, 0.00282107, 0.00206669}, 
{0.00352201, -0.00185944, 0.00252855, -0.00387377, -0.000225997, -0.000487015, 0.00300284, 0.00222908}, 
{-0.0025091, -0.0020536, 0.00175728, -0.00413418, -0.000478443, -0.000747381, 0.00431191, 0.00317806}, 
{-0.0185561, -0.00145745, 0.000393003, -0.00460496, -0.00193557, -0.000727914, 0.00722696, 0.00556809}, 
{-0.0539439, -0.00228496, -0.00453094, -0.00780458, -0.00473595, -0.00209567, 0.0144135, 0.0134676}}; 
double meanQyPlus[nCentBin][nHarmonics] = {{0.000853807, 0.00338912, 0.000123405, -0.000903224, -0.000487368, 0.00164252, 4.68952e-05, -0.00124349}, 
{0.000774647, 0.00326898, 1.71096e-05, -0.000961292, -0.000468216, 0.00170991, -3.32751e-05, -0.00124456}, 
{0.000780184, 0.00353734, -8.77253e-05, -0.000896559, -0.000537728, 0.00172954, 3.88672e-05, -0.00131614}, 
{0.000810164, 0.00370246, -8.81957e-05, -0.000912929, -0.000507316, 0.00175774, 3.07574e-05, -0.0013003}, 
{0.000873367, 0.00357137, -9.0159e-05, -0.000754254, -0.000755728, 0.00188127, -5.16098e-05, -0.00124455}, 
{0.000931246, 0.00353463, -5.28202e-05, -0.000766815, -0.000770215, 0.00189163, -7.28184e-05, -0.00125452}, 
{0.000871922, 0.00380573, -0.000146393, -0.000499213, -0.000779248, 0.0018427, -7.86888e-05, -0.00116451}, 
{0.000923782, 0.00330544, -0.000221435, -0.000564833, -0.000806315, 0.00189411, 8.95343e-06, -0.00119226}, 
{0.000947836, 0.00330317, -0.000115992, -0.000587581, -0.000949847, 0.00195275, -5.8407e-06, -0.00121416}, 
{0.00100757, 0.00347709, -0.000468096, -0.000247977, -0.00101118, 0.00194951, -5.70735e-05, -0.0012104}, 
{0.00151354, 0.00399394, -0.000926107, 0.000384378, -0.00153113, 0.00229448, 0.000110595, -0.00149846}, 
{0.00253182, 0.00487042, -0.0030094, 0.00321655, -0.00221606, 0.00258449, -0.000133109, -0.00159166}, 
{0.00483283, 0.0066609, -0.00817489, 0.0102161, -0.00518031, 0.00333167, -5.5228e-05, -0.00341771}, 
{0.00861601, 0.0132066, -0.0218834, 0.028991, -0.0131016, 0.00801028, -0.00138513, -0.00648065}}; 
double meanQxMinus[nCentBin][nHarmonics] = {{0.000367623, -0.000396775, -0.00255542, 0.00183041, 0.00497812, 0.00144106, -0.000992025, 0.00337599}, 
{0.000339931, -0.000574211, -0.00261224, 0.00193917, 0.00496885, 0.00144753, -0.000989453, 0.003364}, 
{0.000394793, -0.000984313, -0.00250344, 0.00180223, 0.00487028, 0.00133591, -0.00103118, 0.00327784}, 
{0.000226472, -0.000659498, -0.00248596, 0.00187075, 0.0047971, 0.00114224, -0.00118232, 0.00336487}, 
{0.000352493, -0.000965479, -0.00256093, 0.00194078, 0.00476508, 0.00111325, -0.00133635, 0.00322326}, 
{0.000562677, -0.000978021, -0.00230447, 0.00198161, 0.00478299, 0.00101104, -0.00146034, 0.00326786}, 
{0.000652915, -0.00074356, -0.00232129, 0.00181265, 0.00472065, 0.000879209, -0.00161044, 0.0032845}, 
{0.000374491, -0.000557318, -0.00251656, 0.00171577, 0.0046655, 0.000905176, -0.00162108, 0.00318634}, 
{0.00057752, -0.00125904, -0.00238193, 0.00166537, 0.00470355, 0.000858608, -0.00159721, 0.00313372}, 
{0.000895883, -0.00128502, -0.00238087, 0.00151699, 0.00460741, 0.000980912, -0.00168895, 0.00304164}, 
{0.00119245, -0.00120936, -0.00253136, 0.00208682, 0.00503844, 0.000552683, -0.0023967, 0.0024476}, 
{0.00257131, -0.00064836, -0.00243171, 0.00310766, 0.00516948, -0.00090835, -0.00407312, 0.000886138}, 
{0.0060449, -0.00115584, -0.0021168, 0.00478062, 0.00590748, -0.0050053, -0.00879196, -0.00415559}, 
{0.0171483, 0.00108035, -0.00260911, 0.0100075, 0.00729902, -0.0161897, -0.0212577, -0.01637}}; 
double meanQyMinus[nCentBin][nHarmonics] = {{0.00651846, 0.00786588, -0.00251221, -0.00474672, -6.90493e-05, 0.00108944, 0.000213995, -0.000558446}, 
{0.0065313, 0.00778668, -0.00249774, -0.00465478, -0.000221549, 0.00112631, 0.000216963, -0.000515507}, 
{0.00651355, 0.00783839, -0.00239277, -0.00481627, -0.000196016, 0.00112233, 0.000217789, -0.000499042}, 
{0.00647077, 0.0079431, -0.00239997, -0.00472915, -0.000396242, 0.00118541, 0.00021449, -0.000491442}, 
{0.00643805, 0.00786383, -0.00229265, -0.00470812, -0.000399872, 0.00113968, 0.000227184, -0.000485224}, 
{0.00636614, 0.007727, -0.00221351, -0.00463593, -0.000552865, 0.00134063, 0.000164249, -0.000396152}, 
{0.00616243, 0.00820101, -0.00205563, -0.00467614, -0.000548071, 0.00127942, 0.000263524, -0.000360969}, 
{0.00602162, 0.00769187, -0.00201571, -0.00460549, -0.000546797, 0.00131549, 0.000404643, -0.000477046}, 
{0.00594368, 0.00797652, -0.00206774, -0.00439194, -0.000567623, 0.0013474, 0.000442478, -0.000637359}, 
{0.00602396, 0.00807164, -0.00193697, -0.00429522, -0.00081565, 0.00123243, 0.000789198, -0.000569603}, 
{0.00541504, 0.00774029, -0.00194282, -0.00390616, -0.000912159, 0.0013692, 0.0017405, -0.000406498}, 
{0.00443733, 0.00691973, -0.00134292, -0.00257662, -0.0015492, 0.00193349, 0.00379215, 0.000440876}, 
{0.000865541, 0.00456732, 0.000811075, 0.000273825, -0.00413492, 0.00316962, 0.0107342, 0.00372371}, 
{-0.00915591, -0.00167818, 0.00415703, 0.00744897, -0.00948634, 0.00700091, 0.0282342, 0.010784}};



