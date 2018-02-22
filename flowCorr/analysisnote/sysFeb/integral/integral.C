
double combineError(int n, double error[], double nParticle[]){
  double err=0;
  double sumParticle=0;
  for (int i=0; i<n; i++) sumParticle+=nParticle[i];
  for (int i=0; i<n; i++){
    if(sumParticle>0)
      err+=error[i]*error[i]*nParticle[i]/sumParticle*nParticle[i]/sumParticle;
    else err+=0;
  }
  return sqrt(err);
}

double combineValue(int n, double value[], double nParticle[]){
  double sumValue=0;
  double sumParticle=0;
  for(int i=0; i<n; i++){
    sumValue+=value[i]*nParticle[i];
    sumParticle+=nParticle[i];
  }
  if(sumParticle>0) return sumValue/sumParticle;
  else return 0;
}

void doIntegral(string inFile, string outFile){

  const int nCentBin = 14;
  const int nPtIntegral = 10;
  const int nPtBin = 20;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  // eff is 1d vs pt for now, can use 2d vs cent and pt later
  //double effVSpt[nPtIntegral]={0.624944, 0.703495, 0.746352, 0.771617, 0.793430, 0.803476, 0.810035, 0.794746, 0.672228, 0.678857}; //HIN10002
  //double effVSpt[nPtIntegral]={0.486027, 0.530978, 0.596191, 0.657659, 0.701080, 0.730717, 0.736170, 0.790044, 0.700629, 0.676537};  //2760GeV
  ///double effVSpt[nPtIntegral]={0.567472, 0.609648, 0.667275, 0.714321, 0.742844, 0.759267, 0.765678, 0.818874, 0.724238, 0.698056};  //5020GeV
  double effVSpt[nPtIntegral]={0.493128, 0.540638, 0.609759, 0.671302, 0.71296, 0.738311, 0.749449, 0.815777, 0.724155, 0.697706}; //5020GeV new in jun
  //double effVSpt[nPtIntegral]={1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};  //no eff. corr
  double nParticle[nCentBin][nPtIntegral], value[nCentBin][nPtIntegral], error[nCentBin][nPtIntegral];
  double tmp;
  ifstream inSP; inSP.open(inFile.c_str());
  for(int i=0; i<nCentBin; i++){
      inSP>>tmp; inSP>>tmp;
    for(int j=0; j<nPtIntegral; j++){
      inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>nParticle[i][j]; inSP>>value[i][j]; inSP>>error[i][j];
      nParticle[i][j]=nParticle[i][j]/effVSpt[j];
    }
    for(int j=0; j<nPtBin-nPtIntegral; j++){
      inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>tmp;
    }
  }
  inSP.close();

///
  ifstream spectraIn;
  spectraIn.open("/Users/shengquantuo/Dropbox/HIN_16_XXX/doc/macro/pbpbFlowCorr/2760GeV/v06Jan08/v3/mar10/jul3/aug13/aug13N/integral/values/spectra.txt");
  for(int i=0; i<nCentBin; i++){
    for(int j=0; j<nPtIntegral; j++){
      spectraIn>>nParticle[i][j];
    }
  }
///

  ofstream outFiles;
  outFiles.open(outFile.c_str());
  for(int i=0; i<nCentBin; i++){    
    outFiles<<(cBin[i]+cBin[i+1])*1.0/2<<"   "<<combineValue(nPtIntegral, value[i], nParticle[i])<<"   "<<combineError(nPtIntegral, error[i], nParticle[i])<<endl;
  }

}

void getIntegralChi(string inFileNum, string inFileDen, string outFile){

  const int nCentBin = 14;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double valueNum[nCentBin], errorNum[nCentBin], valueDen[nCentBin], errorDen[nCentBin];
  double tmp;
  ifstream inSP; inSP.open(inFileNum.c_str());
  for(int i=0; i<nCentBin; i++){
      inSP>>tmp; inSP>>valueNum[i]; inSP>>errorNum[i];
    }
  inSP.close();
  inSP.open(inFileDen.c_str());
  for(int i=0; i<nCentBin; i++){
      inSP>>tmp; inSP>>valueDen[i]; inSP>>errorDen[i];
    }
  inSP.close();

  ofstream outFiles;
  outFiles.open(outFile.c_str());
  for(int i=0; i<nCentBin; i++){
    outFiles<<(cBin[i]+cBin[i+1])*1.0/2<<"   "<<valueNum[i]/valueDen[i]<<"   "<<valueNum[i]/valueDen[i]*sqrt(errorNum[i]*errorNum[i]/valueNum[i]/valueNum[i] + errorDen[i]*errorDen[i]/valueDen[i]/valueDen[i])<<endl;
  }

}

void integral(){

  doIntegral("../outv22_corrFlow.txt", "./values/v22_integral.txt");
  doIntegral("../outv33_corrFlow.txt", "./values/v33_integral.txt");
  doIntegral("../outv44_corrFlow.txt", "./values/v44_integral.txt");
  doIntegral("../outv55_corrFlow.txt", "./values/v55_integral.txt");
  doIntegral("../outv66_corrFlow.txt", "./values/v66_integral.txt");
  doIntegral("../outv77_corrFlow.txt", "./values/v77_integral.txt");
  doIntegral("../outv88_corrFlow.txt", "./values/v88_integral.txt");

  doIntegral("../outv42_corrFlow.txt", "./values/v42_integral.txt");
  doIntegral("../outv62_corrFlow.txt", "./values/v62_integral.txt");
  doIntegral("../outv63_corrFlow.txt", "./values/v63_integral.txt");
  doIntegral("../outv523_corrFlow.txt", "./values/v523_integral.txt");
  doIntegral("../outv723_corrFlow.txt", "./values/v723_integral.txt");

  doIntegral("../outchi422Den_corrFlow.txt", "./values/chi422Den_integral.txt");
  doIntegral("../outchi523Den_corrFlow.txt", "./values/chi523Den_integral.txt");
  doIntegral("../outchi6222Den_corrFlow.txt", "./values/chi6222Den_integral.txt");
  doIntegral("../outchi633Den_corrFlow.txt", "./values/chi633Den_integral.txt");
  doIntegral("../outchi7223Den_corrFlow.txt", "./values/chi7223Den_integral.txt");

  doIntegral("../outchi422D_corrFlow.txt", "./values/chi422v0_integral.txt");
  doIntegral("../outchi523D_corrFlow.txt", "./values/chi523v0_integral.txt");
  doIntegral("../outchi6222D_corrFlow.txt", "./values/chi6222v0_integral.txt");
  doIntegral("../outchi633D_corrFlow.txt", "./values/chi633v0_integral.txt");
  doIntegral("../outchi7223D_corrFlow.txt", "./values/chi7223v0_integral.txt");

  getIntegralChi("./values/v42_integral.txt", "./values/chi422Den_integral.txt", "./values/chi422_integral.txt");
  getIntegralChi("./values/v523_integral.txt", "./values/chi523Den_integral.txt", "./values/chi523_integral.txt");
  getIntegralChi("./values/v62_integral.txt", "./values/chi6222Den_integral.txt", "./values/chi6222_integral.txt");
  getIntegralChi("./values/v63_integral.txt", "./values/chi633Den_integral.txt", "./values/chi633_integral.txt");
  getIntegralChi("./values/v723_integral.txt", "./values/chi7223Den_integral.txt", "./values/chi7223_integral.txt");


}


