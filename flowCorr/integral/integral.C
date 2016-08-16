
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
  const int nPtBin = 19;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double nParticle[nCentBin][nPtIntegral], value[nCentBin][nPtIntegral], error[nCentBin][nPtIntegral];
  double tmp;
  ifstream inSP; inSP.open(inFile.c_str());
  for(int i=0; i<nCentBin; i++){
      inSP>>tmp; inSP>>tmp;
    for(int j=0; j<nPtIntegral; j++){
      inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>nParticle[i][j]; inSP>>value[i][j]; inSP>>error[i][j];
    }
    for(int j=0; j<nPtBin-nPtIntegral; j++){
      inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>tmp; inSP>>tmp;
    }
  }
  inSP.close();
  ofstream outFiles;
  outFiles.open(outFile.c_str());
  for(int i=0; i<nCentBin; i++){
    outFiles<<(cBin[i]+cBin[i+1])*1.0/2<<"   "<<combineValue(nPtIntegral, value[i], nParticle[i])<<"   "<<combineError(nPtIntegral, error[i], nParticle[i])<<endl;
  }

}

void integral(){

  doIntegral("../outv22_corrFlow.txt", "./values/v22_integral.txt");
  doIntegral("../outv33_corrFlow.txt", "./values/v33_integral.txt");
  doIntegral("../outv44_corrFlow.txt", "./values/v44_integral.txt");
  doIntegral("../outv55_corrFlow.txt", "./values/v55_integral.txt");
  doIntegral("../../v03Aug15/outv66_corrFlow.txt", "./values/v66_integral.txt");
  doIntegral("../outv77_corrFlow.txt", "./values/v77_integral.txt");



}


