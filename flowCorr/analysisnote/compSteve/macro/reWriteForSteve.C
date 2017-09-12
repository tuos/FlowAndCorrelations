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
  char inFiles[nFile][200]={"outchi422D_corrFlow.txt","outchi523D_corrFlow.txt","outchi6222D_corrFlow.txt","outchi633D_corrFlow.txt","outchi7223D_corrFlow.txt"};
  char outFiles[nFile][nCent][200]={
{"Chi42_0_5.txt", "Chi42_5_10.txt","Chi42_10_15.txt","Chi42_15_20.txt","Chi42_20_25.txt","Chi42_25_30.txt","Chi42_30_35.txt","Chi42_35_40.txt","Chi42_40_50.txt","Chi42_50_60.txt"},
{"Chi523_0_5.txt", "Chi523_5_10.txt","Chi523_10_15.txt","Chi523_15_20.txt","Chi523_20_25.txt","Chi523_25_30.txt","Chi523_30_35.txt","Chi523_35_40.txt","Chi523_40_50.txt","Chi523_50_60.txt"},
{"Chi62_0_5.txt", "Chi62_5_10.txt","Chi62_10_15.txt","Chi62_15_20.txt","Chi62_20_25.txt","Chi62_25_30.txt","Chi62_30_35.txt","Chi62_35_40.txt","Chi62_40_50.txt","Chi62_50_60.txt"},
{"Chi63_0_5.txt", "Chi63_5_10.txt","Chi63_10_15.txt","Chi63_15_20.txt","Chi63_20_25.txt","Chi63_25_30.txt","Chi63_30_35.txt","Chi63_35_40.txt","Chi63_40_50.txt","Chi63_50_60.txt"},
{"Chi723_0_5.txt", "Chi723_5_10.txt","Chi723_10_15.txt","Chi723_15_20.txt","Chi723_20_25.txt","Chi723_25_30.txt","Chi723_30_35.txt","Chi723_35_40.txt","Chi723_40_50.txt","Chi723_50_60.txt"}
};
  for(int i=0; i<nFile; i++){
    ifstream inFile;
    inFile.open(inFiles[i]);
    for(int j=0; j<nCent; j++){
      ofstream outFile;
      outFile.open(outFiles[i][j]);
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

// mixed harmonics
  char inFilesV[nFile][200]={"outv42_corrFlow.txt","outv523_corrFlow.txt","outv62_corrFlow.txt","outv63_corrFlow.txt","outv723_corrFlow.txt"};
  char outFilesV[nFile][nCent][200]={
{"v42_0_5.txt", "v42_5_10.txt","v42_10_15.txt","v42_15_20.txt","v42_20_25.txt","v42_25_30.txt","v42_30_35.txt","v42_35_40.txt","v42_40_50.txt","v42_50_60.txt"},
{"v523_0_5.txt", "v523_5_10.txt","v523_10_15.txt","v523_15_20.txt","v523_20_25.txt","v523_25_30.txt","v523_30_35.txt","v523_35_40.txt","v523_40_50.txt","v523_50_60.txt"},
{"v62_0_5.txt", "v62_5_10.txt","v62_10_15.txt","v62_15_20.txt","v62_20_25.txt","v62_25_30.txt","v62_30_35.txt","v62_35_40.txt","v62_40_50.txt","v62_50_60.txt"},
{"v63_0_5.txt", "v63_5_10.txt","v63_10_15.txt","v63_15_20.txt","v63_20_25.txt","v63_25_30.txt","v63_30_35.txt","v63_35_40.txt","v63_40_50.txt","v63_50_60.txt"},
{"v723_0_5.txt", "v723_5_10.txt","v723_10_15.txt","v723_15_20.txt","v723_20_25.txt","v723_25_30.txt","v723_30_35.txt","v723_35_40.txt","v723_40_50.txt","v723_50_60.txt"}
};
  for(int i=0; i<nFile; i++){
    ifstream inFileV;
    inFileV.open(inFilesV[i]);
    for(int j=0; j<nCent; j++){
      ofstream outFileV;
      outFileV.open(outFilesV[i][j]);
      inFileV>>tmp; inFileV>>tmp;
      for(int k=0; k<nPt; k++){
        inFileV>>tmp; inFileV>>tmp; inFileV>>mPt; inFileV>>tmp; inFileV>>value; inFileV>>err;
        if(k<16)
          outFileV<<mPt<<"     "<<value<<"     "<<err<<endl;
      }
      outFileV.close();
    }
    inFileV.close();
  }


// vn{Psi_n}
  char inFilesVn[nFile][200]={"outv22_corrFlow.txt","outv33_corrFlow.txt","outv44_corrFlow.txt","outv55_corrFlow.txt","outv66_corrFlow.txt"};
  char outFilesVn[nFile][nCent][200]={
{"v22_0_5.txt", "v22_5_10.txt","v22_10_15.txt","v22_15_20.txt","v22_20_25.txt","v22_25_30.txt","v22_30_35.txt","v22_35_40.txt","v22_40_50.txt","v22_50_60.txt"},
{"v33_0_5.txt", "v33_5_10.txt","v33_10_15.txt","v33_15_20.txt","v33_20_25.txt","v33_25_30.txt","v33_30_35.txt","v33_35_40.txt","v33_40_50.txt","v33_50_60.txt"},
{"v44_0_5.txt", "v44_5_10.txt","v44_10_15.txt","v44_15_20.txt","v44_20_25.txt","v44_25_30.txt","v44_30_35.txt","v44_35_40.txt","v44_40_50.txt","v44_50_60.txt"},
{"v55_0_5.txt", "v55_5_10.txt","v55_10_15.txt","v55_15_20.txt","v55_20_25.txt","v55_25_30.txt","v55_30_35.txt","v55_35_40.txt","v55_40_50.txt","v55_50_60.txt"},
{"v66_0_5.txt", "v66_5_10.txt","v66_10_15.txt","v66_15_20.txt","v66_20_25.txt","v66_25_30.txt","v66_30_35.txt","v66_35_40.txt","v66_40_50.txt","v66_50_60.txt"}
};
  for(int i=0; i<nFile; i++){
    ifstream inFileVn;
    inFileVn.open(inFilesVn[i]);
    for(int j=0; j<nCent; j++){
      ofstream outFileVn;
      outFileVn.open(outFilesVn[i][j]);
      inFileVn>>tmp; inFileVn>>tmp;
      for(int k=0; k<nPt; k++){
        inFileVn>>tmp; inFileVn>>tmp; inFileVn>>mPt; inFileVn>>tmp; inFileVn>>value; inFileVn>>err;
        if(k<16)
          outFileVn<<mPt<<"     "<<value<<"     "<<err<<endl;
      }
      outFileVn.close();
    }
    inFileVn.close();
  }



}

