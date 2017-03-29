reWriteForSteve(){

  double tmp, mPt, value, err;
  const int nFile=5;
  const int nCent=10;
  const int nPt=20;

// Den
  char inFilesD[nFile][200]={"outchi422Den_corrFlow.txt","outchi523Den_corrFlow.txt","outchi6222Den_corrFlow.txt","outchi633Den_corrFlow.txt","outchi7223Den_corrFlow.txt"};
  char outFilesD[nFile][nCent][200]={
{"D24_0_5.txt", "D24_5_10.txt","D24_10_15.txt","D24_15_20.txt","D24_20_25.txt","D24_25_30.txt","D24_30_35.txt","D24_35_40.txt","D24_40_50.txt","D24_50_60.txt"},
{"D2232_0_5.txt", "D2232_5_10.txt","D2232_10_15.txt","D2232_15_20.txt","D2232_20_25.txt","D2232_25_30.txt","D2232_30_35.txt","D2232_35_40.txt","D2232_40_50.txt","D2232_50_60.txt"},
{"D26_0_5.txt", "D26_5_10.txt","D26_10_15.txt","D26_15_20.txt","D26_20_25.txt","D26_25_30.txt","D26_30_35.txt","D26_35_40.txt","D26_40_50.txt","D26_50_60.txt"},
{"D36_0_5.txt", "D36_5_10.txt","D36_10_15.txt","D36_15_20.txt","D36_20_25.txt","D36_25_30.txt","D36_30_35.txt","D36_35_40.txt","D36_40_50.txt","D36_50_60.txt"},
{"D2432_0_5.txt", "D2432_5_10.txt","D2432_10_15.txt","D2432_15_20.txt","D2432_20_25.txt","D2432_25_30.txt","D2432_30_35.txt","D2432_35_40.txt","D2432_40_50.txt","D2432_50_60.txt"}
};
  for(int i=0; i<nFile; i++){
    ifstream inFile;
    inFile.open(inFilesD[i]);
    for(int j=0; j<nCent; j++){
      ofstream outFile;
      outFile.open(outFilesD[i][j]);     
      inFile>>tmp; inFile>>tmp;
      for(int k=0; k<nPt; k++){
        inFile>>tmp; inFile>>tmp; inFile>>mPt; inFile>>tmp; inFile>>value; inFile>>err;
        if(k<16)
          outFile<<mPt<<"     "<<value<<"     "<<err<<endl;
      }
      outFile.close();
    }
    inFile.close();
  }

// Num
  char inFilesN[nFile][200]={"outchi422Num_corrFlow.txt","outchi523Num_corrFlow.txt","outchi6222Num_corrFlow.txt","outchi633Num_corrFlow.txt","outchi7223Num_corrFlow.txt"};
  char outFilesN[nFile][nCent][200]={
{"N42_0_5.txt", "N42_5_10.txt","N42_10_15.txt","N42_15_20.txt","N42_20_25.txt","N42_25_30.txt","N42_30_35.txt","N42_35_40.txt","N42_40_50.txt","N42_50_60.txt"},
{"N523_0_5.txt", "N523_5_10.txt","N523_10_15.txt","N523_15_20.txt","N523_20_25.txt","N523_25_30.txt","N523_30_35.txt","N523_35_40.txt","N523_40_50.txt","N523_50_60.txt"},
{"N62_0_5.txt", "N62_5_10.txt","N62_10_15.txt","N62_15_20.txt","N62_20_25.txt","N62_25_30.txt","N62_30_35.txt","N62_35_40.txt","N62_40_50.txt","N62_50_60.txt"},
{"N63_0_5.txt", "N63_5_10.txt","N63_10_15.txt","N63_15_20.txt","N63_20_25.txt","N63_25_30.txt","N63_30_35.txt","N63_35_40.txt","N63_40_50.txt","N63_50_60.txt"},
{"N723_0_5.txt", "N723_5_10.txt","N723_10_15.txt","N723_15_20.txt","N723_20_25.txt","N723_25_30.txt","N723_30_35.txt","N723_35_40.txt","N723_40_50.txt","N723_50_60.txt"}
};
  for(int i=0; i<nFile; i++){
    ifstream inFile;
    inFile.open(inFilesN[i]);
    for(int j=0; j<nCent; j++){
      ofstream outFile;
      outFile.open(outFilesN[i][j]);
      inFile>>tmp; inFile>>tmp;
      for(int k=0; k<nPt; k++){
        inFile>>tmp; inFile>>tmp; inFile>>mPt; inFile>>tmp; inFile>>value; inFile>>err;
        if(k<16)
          outFile<<mPt<<"     "<<value<<"     "<<err<<endl;
      }
      outFile.close();
    }
    inFile.close();
  }

// Chi

}

