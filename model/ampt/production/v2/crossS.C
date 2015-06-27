void crossS(){

const int nC=3;

double fragA[nC]={2.2, 0.5, 0.55};
double fragB[nC]={0.5, 0.9, 0.15};
double alphaS[nC]={0.47, 0.33, 0.47140452};
double muon[nC]={1.8, 3.2, 3.2264};
double sigma[nC]={0.0, 0.0, 0.0};
for(int i=0; i<nC; i++){
sigma[i]=9*3.14159*alphaS[i]*alphaS[i]/(2*muon[i]*muon[i]);
cout<<"sigma[i] = "<<sigma[i]<<endl;
} 



}


