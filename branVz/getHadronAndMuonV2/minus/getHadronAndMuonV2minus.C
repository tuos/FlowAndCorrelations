
// return error of (fA*v2A-fB*v2B)/(fA*fC-fB*fD)
double calculateV2Error(double fA, double fAe, double fB, double fBe, double fC, double fCe, double fD, double fDe, double v2A, double v2Ae, double v2B, double v2Be){
  double numerator = fA*v2A-fB*v2B;
  double numeratorError = sqrt(fabs( (fA*v2A*fA*v2A)*(fAe*fAe/fA/fA+v2Ae*v2Ae/v2A/v2A) + (fB*v2B*fB*v2B)*(fBe*fBe/fB/fB+v2Be*v2Be/v2B/v2B) ));
  double denominator = fA*fC-fB*fD;
  double denominatorError = sqrt( (fA*fC*fA*fC)*(fAe*fAe/fA/fA+fCe*fCe/fC/fC) + (fB*fD*fB*fD)*(fBe*fBe/fB/fB+fDe*fDe/fD/fD) );

  double v2Error = numerator/denominator*sqrt(numeratorError*numeratorError/numerator/numerator + denominatorError*denominatorError/denominator/denominator);

  return v2Error;
}

void getHadronAndMuonV2minus(){

// variables
const int nCentBin=4;
const int nPtBin=10;
double centCuts[nCentBin+1]={0, 10, 20, 40, 60};
double ptCuts[nPtBin+1]={0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0};
double tmp;

double v2LG23[nCentBin][nPtBin];
double v2LG23Error[nCentBin][nPtBin];
double v2LG4[nCentBin][nPtBin];
double v2LG4Error[nCentBin][nPtBin];

double yieldPiLG23[nCentBin][nPtBin];
double yieldKaonLG23[nCentBin][nPtBin];
double yieldMuonLG23[nCentBin][nPtBin];
double fractionHadronLG23[nCentBin][nPtBin];
double fractionMuonLG23[nCentBin][nPtBin];
double fractionHadronLG23Error[nCentBin][nPtBin];
double fractionMuonLG23Error[nCentBin][nPtBin];
double yieldPiLG4[nCentBin][nPtBin];
double yieldKaonLG4[nCentBin][nPtBin];
double yieldMuonLG4[nCentBin][nPtBin];
double fractionHadronLG4[nCentBin][nPtBin];
double fractionMuonLG4[nCentBin][nPtBin];
double fractionHadronLG4Error[nCentBin][nPtBin];
double fractionMuonLG4Error[nCentBin][nPtBin];

// read 
  ifstream inputFile;
  inputFile.open("txt_cent_pt_v2_LG23_S_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>v2LG23[i][j];
        inputFile>>v2LG23Error[i][j];
      }
    }
    inputFile.close();
  inputFile.open("txt_cent_pt_v2_LG4_S_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>v2LG4[i][j];
        inputFile>>v2LG4Error[i][j];
      }
    }
    inputFile.close();

// read yields
  inputFile.open("txt_cent_pt_hadronmuonyield_LG23_S_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>yieldPiLG23[i][j];
        inputFile>>tmp;
        inputFile>>yieldKaonLG23[i][j];
        inputFile>>tmp;
        inputFile>>yieldMuonLG23[i][j];
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
      }
    }
    inputFile.close();
  inputFile.open("txt_cent_pt_hadronmuonyield_LG4_S_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>yieldPiLG4[i][j];
        inputFile>>tmp;
        inputFile>>yieldKaonLG4[i][j];
        inputFile>>tmp;
        inputFile>>yieldMuonLG4[i][j];
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
      }
    }
    inputFile.close();

// calculate fraction and fractionError
// assume num/den completed correlated for error calculations
// https://twiki.cern.ch/twiki/pub/CMS/HeavyIonsSysts/lara.02-008.errors.pdf
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){

        // LG23
        double hadrons = yieldPiLG23[i][j]+yieldKaonLG23[i][j];
        double muons = yieldMuonLG23[i][j];
        if(hadrons+muons<1.0){
          fractionHadronLG23[i][j] = 0;
          fractionMuonLG23[i][j] = 0;
        } 
        else {
          fractionHadronLG23[i][j] = (hadrons)/(hadrons+muons);
          fractionMuonLG23[i][j] = (muons)/(hadrons+muons);
        }
        if(hadrons<1.0){
          fractionHadronLG23Error[i][j] = 0;
        }
        else {
          fractionHadronLG23Error[i][j] = fractionHadronLG23[i][j]*sqrt(1.0/hadrons + 1.0/(hadrons+muons) - 2.0/(hadrons+muons)/hadrons*(hadrons)); //error
        }
        if(muons<1.0){
          fractionMuonLG23Error[i][j] = 0;
        }
        else {
          fractionMuonLG23Error[i][j] = fractionMuonLG23[i][j]*sqrt(1.0/muons + 1.0/(hadrons+muons) - 2.0/(hadrons+muons)/muons*(muons)); //error
        }

        // LG4
        double hadrons4 = yieldPiLG4[i][j]+yieldKaonLG4[i][j];
        double muons4 = yieldMuonLG4[i][j];
        if(hadrons4+muons4<1.0){
          fractionHadronLG4[i][j] = 0;
          fractionMuonLG4[i][j] = 0;
        } 
        else {
          fractionHadronLG4[i][j] = (hadrons4)/(hadrons4+muons4);
          fractionMuonLG4[i][j] = (muons4)/(hadrons4+muons4);
        }
        if(hadrons4<1.0){
          fractionHadronLG4Error[i][j] = 0;
        }
        else {
          fractionHadronLG4Error[i][j] = fractionHadronLG4[i][j]*sqrt(1.0/hadrons4 + 1.0/(hadrons4+muons4) - 2.0/(hadrons4+muons4)/hadrons4*(hadrons4)); //error
        }
        if(muons4<1.0){
          fractionMuonLG4Error[i][j] = 0;
        }
        else {
          fractionMuonLG4Error[i][j] = fractionMuonLG4[i][j]*sqrt(1.0/muons4 + 1.0/(hadrons4+muons4) - 2.0/(hadrons4+muons4)/muons4*(muons4)); // error
        }

      }
    }

//do we want to include error for fraction?
bool includeErrorFraction = true;
  if(includeErrorFraction==false){
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        fractionHadronLG23Error[i][j] = 0;
        fractionMuonLG23Error[i][j] = 0;
        fractionHadronLG4Error[i][j] = 0;
        fractionMuonLG4Error[i][j] = 0;
      }
    }
  }

// calculate v2hadron and v2muon
double v2Hadron[nCentBin][nPtBin];
double v2HadronError[nCentBin][nPtBin];
double v2Muon[nCentBin][nPtBin];
double v2MuonError[nCentBin][nPtBin];
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        double numeratorHadron = fractionMuonLG4[i][j]*v2LG23[i][j] - fractionMuonLG23[i][j]*v2LG4[i][j];
        double denominatorHadron = fractionMuonLG4[i][j]*fractionHadronLG23[i][j] - fractionMuonLG23[i][j]*fractionHadronLG4[i][j];
        if(fabs(denominatorHadron)<0.00000001){
          v2Hadron[i][j] = 0;
          v2HadronError[i][j] = 0;
        }
        else {
          v2Hadron[i][j] = numeratorHadron/denominatorHadron;
          v2HadronError[i][j] = calculateV2Error(fractionMuonLG4[i][j], fractionMuonLG4Error[i][j],  fractionMuonLG23[i][j], fractionMuonLG23Error[i][j],  fractionHadronLG23[i][j], fractionHadronLG23Error[i][j],  fractionHadronLG4[i][j], fractionHadronLG4Error[i][j],  v2LG23[i][j], v2LG23Error[i][j],  v2LG4[i][j], v2LG4Error[i][j]);
        }
        double numeratorMuon = fractionHadronLG4[i][j]*v2LG23[i][j] - fractionHadronLG23[i][j]*v2LG4[i][j];
        double denominatorMuon = fractionHadronLG4[i][j]*fractionMuonLG23[i][j] - fractionHadronLG23[i][j]*fractionMuonLG4[i][j];
        if(fabs(denominatorMuon)<0.00000001){
          v2Muon[i][j] = 0;
          v2MuonError[i][j] = 0;
        } 
        else {
          v2Muon[i][j] = numeratorMuon/denominatorMuon;
          v2MuonError[i][j] = calculateV2Error(fractionHadronLG4[i][j], fractionHadronLG4Error[i][j], fractionHadronLG23[i][j], fractionHadronLG23Error[i][j], fractionMuonLG23[i][j], fractionMuonLG23Error[i][j], fractionMuonLG4[i][j], fractionMuonLG4Error[i][j], v2LG23[i][j], v2LG23Error[i][j],  v2LG4[i][j], v2LG4Error[i][j]);
        } 

      }
    }


// save outputs
    ofstream outV2;
    outV2.open("txt_cent_pt_v2hadron_v2muon_error_minus.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        if(isnan(v2HadronError[i][j])) v2HadronError[i][j]=0;
        if(isnan(v2MuonError[i][j])) v2MuonError[i][j]=0;

        if(v2HadronError[i][j]<0) v2HadronError[i][j]=-v2HadronError[i][j];
        if(v2MuonError[i][j]<0) v2MuonError[i][j]=-v2MuonError[i][j];

        outV2<<i<<"   "<<(ptCuts[j]+ptCuts[j+1])/2.0<<"   "<<v2Hadron[i][j]<<"   "<<v2HadronError[i][j]<<"   "<<v2Muon[i][j]<<"   "<<v2MuonError[i][j]<<endl;
        cout<<i<<"   "<<(ptCuts[j]+ptCuts[j+1])/2.0<<"   "<<v2Hadron[i][j]<<"   "<<v2HadronError[i][j]<<"   "<<v2Muon[i][j]<<"   "<<v2MuonError[i][j]<<endl;
      }
    }

}


