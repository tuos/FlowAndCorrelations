void sysError(){

const int nFlow=5;
double vnCuts[nFlow]={3, 5, 6, 6, 10};
double trkCuts[nFlow]={3, 3, 3, 3, 3};
double eff[nFlow]={3, 3, 3, 3, 3};

double totalSys[nFlow]={0.0};
for(int i=0; i<nFlow; i++){
 totalSys[i]=0.0;
 totalSys[i]+=vnCuts[i]*vnCuts[i] + trkCuts[i]*trkCuts[i] + eff[i]*eff[i];
 cout<<sqrt(totalSys[i])<<endl;
}


}


