void fromCountsToV2(){

// variables
const int nCentBin=4;
const int nPtBin=10;
double centCuts[nCentBin+1]={0, 10, 20, 40, 60};
double ptCuts[nPtBin+1]={0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2.0, 2.5, 3.0, 4.0, 5.0};
double tmp;
double countsIn[nCentBin][nPtBin];
double countsInError[nCentBin][nPtBin];
double countsOut[nCentBin][nPtBin];
double countsOutError[nCentBin][nPtBin];

// read In plane
  ifstream inputCountsIn;
  inputCountsIn.open("txt_cent_pt_Nin_LG4_standard.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputCountsIn>>tmp;
        inputCountsIn>>tmp;
        inputCountsIn>>countsIn[i][j];
        inputCountsIn>>countsInError[i][j];
      }
    }
    inputCountsIn.close();

// read Out plane
  ifstream inputCountsOut;
  inputCountsOut.open("txt_cent_pt_Nout_LG4_standard.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        inputCountsOut>>tmp;
        inputCountsOut>>tmp;
        inputCountsOut>>countsOut[i][j];
        inputCountsOut>>countsOutError[i][j];
      }
    }
    inputCountsOut.close();

// calculate v2 and v2Error from counts and countsError
double v2Obs[nCentBin][nPtBin];
double v2ObsError[nCentBin][nPtBin];
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        v2Obs[i][j]=(TMath::Pi()/4.0)*(countsIn[i][j]-countsOut[i][j])/(countsIn[i][j]+countsOut[i][j]);
        v2ObsError[i][j]=(TMath::Pi()/(2.0*(countsIn[i][j]+countsOut[i][j])*(countsIn[i][j]+countsOut[i][j])))*sqrt(countsOut[i][j]*countsOut[i][j]*countsInError[i][j]*countsInError[i][j] + countsIn[i][j]*countsIn[i][j]*countsOutError[i][j]*countsOutError[i][j]);
      }
    }

// save outputs
    ofstream outV2;
    outV2.open("txt_cent_pt_v2_error.txt");
    for(int i=0; i<nCentBin; i++){
      for(int j=0; j<nPtBin; j++){
        outV2<<i<<"   "<<(ptCuts[j]+ptCuts[j+1])/2.0<<"   "<<v2Obs[i][j]<<"   "<<v2ObsError[i][j]<<endl;
        cout<<i<<"   "<<(ptCuts[j]+ptCuts[j+1])/2.0<<"   "<<v2Obs[i][j]<<"   "<<v2ObsError[i][j]<<endl;
      }
    }

}


