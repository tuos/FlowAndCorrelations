
// return error of (v2A-fB*v2B)/(fC)
double calculateV2Error(double fB, double fBe, double fC, double fCe, double v2A, double v2Ae, double v2B, double v2Be){
  double numerator = v2A-fB*v2B;
  double numeratorError = sqrt(fabs( (v2Ae*v2Ae) + (fB*v2B*fB*v2B)*(fBe*fBe/fB/fB+v2Be*v2Be/v2B/v2B) ));
  double denominator = fC;
  double denominatorError = fCe;

  double v2Error = numerator/denominator*sqrt(numeratorError*numeratorError/numerator/numerator + denominatorError*denominatorError/denominator/denominator);

  return v2Error;
}

void extractHFMuonV2plus(){

// variables
const int nCentBin=4;
const int nPtBin=10;
double centCuts[nCentBin+1]={0, 10, 20, 40, 60};
double ptCuts[nPtBin+1]={0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0};
double tmp;

double v2Muon[nCentBin][nPtBin];
double v2MuonError[nCentBin][nPtBin];
double v2LFMuon[nCentBin][nPtBin];
double v2LFMuonError[nCentBin][nPtBin];

double yieldLF[nCentBin][nPtBin];
double yieldHF[nCentBin][nPtBin];
double fractionLF[nCentBin][nPtBin];
double fractionHF[nCentBin][nPtBin];
double fractionLFError[nCentBin][nPtBin];
double fractionHFError[nCentBin][nPtBin];


// read 
  ifstream inputFile;
  inputFile.open("txt_cent_pt_v2hadron_v2muon_S_error_plus.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>v2Muon[i][j];
        inputFile>>v2MuonError[i][j];
      }
    }
    inputFile.close();
  inputFile.open("txt_cent_pt_v2LFmuon_S_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>v2LFMuon[i][j];
        inputFile>>v2LFMuonError[i][j];
      }
    }
    inputFile.close();

// read yields
  inputFile.open("txt_cent_pt_hadronmuonyield_LG4_S_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>tmp;
        inputFile>>yieldLF[i][j];
        inputFile>>tmp;
        inputFile>>yieldHF[i][j];
        inputFile>>tmp;
      }
    }
    inputFile.close();

// calculate fraction and fractionError
// assume num/den completed correlated for error calculations
// https://twiki.cern.ch/twiki/pub/CMS/HeavyIonsSysts/lara.02-008.errors.pdf
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){

        double lightflavor = yieldLF[i][j];
        double heavyflavor = yieldHF[i][j];
        if(lightflavor+heavyflavor<1.0){
          fractionLF[i][j] = 0;
          fractionHF[i][j] = 0;
        } 
        else {
          fractionLF[i][j] = (lightflavor)/(lightflavor+heavyflavor);
          fractionHF[i][j] = (heavyflavor)/(lightflavor+heavyflavor);
        }
        if(lightflavor<1.0){
          fractionLFError[i][j] = 0;
        }
        else {
          fractionLFError[i][j] = fractionLF[i][j]*sqrt(1.0/lightflavor + 1.0/(lightflavor+heavyflavor) - 2.0/(lightflavor+heavyflavor)/lightflavor*(lightflavor)); //error
        }
        if(heavyflavor<1.0){
          fractionHFError[i][j] = 0;
        }
        else {
          fractionHFError[i][j] = fractionHF[i][j]*sqrt(1.0/heavyflavor + 1.0/(lightflavor+heavyflavor) - 2.0/(lightflavor+heavyflavor)/heavyflavor*(heavyflavor)); //error
        }


      }
    }

//do we want to include error for fraction?
bool includeErrorFraction = true;
  if(includeErrorFraction==false){
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        fractionLFError[i][j] = 0;
        fractionHFError[i][j] = 0;
      }
    }
  }

// calculate HFmuonv2
double v2HFMuon[nCentBin][nPtBin];
double v2HFMuonError[nCentBin][nPtBin];
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        double numeratorHFMuon = v2Muon[i][j] - fractionLF[i][j]*v2LFMuon[i][j];
        double denominatorHFMuon = fractionHF[i][j]; 
        if(fabs(denominatorHFMuon)<0.00000001){
          v2HFMuon[i][j] = 0;
          v2HFMuonError[i][j] = 0;
        }
        else {
          v2HFMuon[i][j] = numeratorHFMuon/denominatorHFMuon;
          v2HFMuonError[i][j] = calculateV2Error(fractionLF[i][j], fractionLFError[i][j],  fractionHF[i][j], fractionHFError[i][j], v2Muon[i][j], v2MuonError[i][j],  v2LFMuon[i][j], v2LFMuonError[i][j]);
        }

      }
    }


// save outputs
    ofstream outV2;
    outV2.open("txt_cent_pt_hfmuonv2_error_plus.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        if(isnan(v2HFMuonError[i][j])) v2HFMuonError[i][j]=0;

        if(v2HFMuonError[i][j]<0) v2HFMuonError[i][j]=-v2HFMuonError[i][j];

        outV2<<i<<"   "<<(ptCuts[j]+ptCuts[j+1])/2.0<<"   "<<v2HFMuon[i][j]<<"   "<<v2HFMuonError[i][j]<<endl;
        cout<<i<<"   "<<(ptCuts[j]+ptCuts[j+1])/2.0<<"   "<<v2HFMuon[i][j]<<"   "<<v2HFMuonError[i][j]<<endl;
      }
    }

}


