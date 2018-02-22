
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
  const int nCentIntegralA = 4;
  const int nCentIntegralB = 6;
  const int nPtIntegral = 10;
  const int nPtBin = 20;
  double cBin[nCentBin+1]={0,5,10,15,20,25,30,35,40,50,60,70,80,90,100};
  double cBinCombined[nCentBin+1]={0,20,60,70,80,81,82,84,86,88,90,92,94,96,100};
  double effVSpt[nPtIntegral]={0.493128, 0.540638, 0.609759, 0.671302, 0.71296, 0.738311, 0.749449, 0.815777, 0.724155, 0.697706}; //5020GeV new in jun
  //double effVSpt[nPtIntegral]={1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};  //no eff. corr
  double nParticleA[nPtBin][nCentIntegralA], valueA[nPtBin][nCentIntegralA], errorA[nPtBin][nCentIntegralA];
  double ptLowA[nPtBin][nCentIntegralA], ptHighA[nPtBin][nCentIntegralA], meanPtA[nPtBin][nCentIntegralA];
  double nParticleB[nPtBin][nCentIntegralB], valueB[nPtBin][nCentIntegralB], errorB[nPtBin][nCentIntegralB];
  double ptLowB[nPtBin][nCentIntegralB], ptHighB[nPtBin][nCentIntegralB], meanPtB[nPtBin][nCentIntegralB];
  double constValueA[nPtBin][nCentIntegralA], constValueB[nPtBin][nCentIntegralB];
  double tmp;
  ifstream inSP; inSP.open(inFile.c_str());
  for(int i=0; i<nCentIntegralA; i++){
      inSP>>tmp; inSP>>tmp;
    for(int j=0; j<nPtBin; j++){
      inSP>>ptLowA[j][i]; inSP>>ptHighA[j][i]; inSP>>meanPtA[j][i];
      inSP>>nParticleA[j][i]; inSP>>valueA[j][i]; inSP>>errorA[j][i];
      constValueA[j][i]=1.0;
    }
  }
  for(int i=0; i<nCentIntegralB; i++){
      inSP>>tmp; inSP>>tmp;
    for(int j=0; j<nPtBin; j++){
      inSP>>ptLowB[j][i]; inSP>>ptHighB[j][i]; inSP>>meanPtB[j][i];
      inSP>>nParticleB[j][i]; inSP>>valueB[j][i]; inSP>>errorB[j][i];
      constValueB[j][i]=1.0;
    }
  }
  inSP.close();


  ofstream outFiles;
  outFiles.open(outFile.c_str());
  outFiles<<cBinCombined[0]<<"   "<<cBinCombined[1]<<endl;
  for(int i=0; i<nPtBin; i++){    
    outFiles<<combineValue(nCentIntegralA, ptLowA[i], constValueA[i])<<"  "<<combineValue(nCentIntegralA, ptHighA[i], constValueA[i])<<"   "<<combineValue(nCentIntegralA, meanPtA[i], nParticleA[i])<<"  "<<nCentIntegralA*combineValue(nCentIntegralA, nParticleA[i], constValueA[i])<<"  "<<combineValue(nCentIntegralA, valueA[i], nParticleA[i])<<"  "<<combineError(nCentIntegralA, errorA[i], nParticleA[i])<<endl;
  }
  outFiles<<cBinCombined[1]<<"   "<<cBinCombined[2]<<endl;
  for(int i=0; i<nPtBin; i++){
    outFiles<<combineValue(nCentIntegralB, ptLowB[i], constValueB[i])<<"  "<<combineValue(nCentIntegralB, ptHighB[i], constValueB[i])<<"   "<<combineValue(nCentIntegralB, meanPtB[i], nParticleB[i])<<"  "<<combineValue(nCentIntegralB, nParticleB[i], constValueB[i])<<"  "<<combineValue(nCentIntegralB, valueB[i], nParticleB[i])<<"  "<<combineError(nCentIntegralB, errorB[i], nParticleB[i])<<endl;
  }

}


void combineCentrality(){

  doIntegral("../outv22_corrFlow.txt", "./values/v22_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv33_corrFlow.txt", "./values/v33_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv44_corrFlow.txt", "./values/v44_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv55_corrFlow.txt", "./values/v55_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv66_corrFlow.txt", "./values/v66_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv77_corrFlow.txt", "./values/v77_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv88_corrFlow.txt", "./values/v88_combinedFromSmallCentralityBins.txt");

  doIntegral("../outv42_corrFlow.txt", "./values/v42_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv62_corrFlow.txt", "./values/v62_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv63_corrFlow.txt", "./values/v63_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv523_corrFlow.txt", "./values/v523_combinedFromSmallCentralityBins.txt");
  doIntegral("../outv723_corrFlow.txt", "./values/v723_combinedFromSmallCentralityBins.txt");

//  doIntegral("../outchi422Den_corrFlow.txt", "./values/chi422Den_combinedFromSmallCentralityBins.txt");
//  doIntegral("../outchi523Den_corrFlow.txt", "./values/chi523Den_combinedFromSmallCentralityBins.txt");
//  doIntegral("../outchi6222Den_corrFlow.txt", "./values/chi6222Den_combinedFromSmallCentralityBins.txt");
//  doIntegral("../outchi633Den_corrFlow.txt", "./values/chi633Den_combinedFromSmallCentralityBins.txt");
//  doIntegral("../outchi7223Den_corrFlow.txt", "./values/chi7223Den_combinedFromSmallCentralityBins.txt");

  doIntegral("../outchi422D_corrFlow.txt", "./values/chi422v0_combinedFromSmallCentralityBins.txt");
  doIntegral("../outchi523D_corrFlow.txt", "./values/chi523v0_combinedFromSmallCentralityBins.txt");
  doIntegral("../outchi6222D_corrFlow.txt", "./values/chi6222v0_combinedFromSmallCentralityBins.txt");
  doIntegral("../outchi633D_corrFlow.txt", "./values/chi633v0_combinedFromSmallCentralityBins.txt");
  doIntegral("../outchi7223D_corrFlow.txt", "./values/chi7223v0_combinedFromSmallCentralityBins.txt");



}


