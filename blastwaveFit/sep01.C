
const double R = 1.0;
const double dr = 1e-3; // FIXME

double integral(double beta_T, double T, double n, double pt, double mt)
{
  
  double s = 0.;
  for(double r = dr/2; r < R; r += dr)
  {
    double beta_r = (beta_T*(n+2)/2) * TMath::Power((r/R),n);
    double rho = TMath::ATanH(beta_r);

    s += r * dr * TMath::BesselK1((mt*cosh(rho))/T) * TMath::BesselI0((pt*sinh(rho))/T);
  }

  return s;
}

double parBesselK1(double mt, double beta_T, double n, double T)
{

  double s = 0.;
  for(double r = dr/2; r < R; r += dr)
  {
    double beta_r = (beta_T*(n+2)/2) * TMath::Power((r/R),n);
    double rho = TMath::ATanH(beta_r);

    //s += r * dr * TMath::BesselK1((mt*cosh(rho))/T) * TMath::BesselI0((pt*sinh(rho))/T);
    if((mt*cosh(rho))/T<1){
      cout<<"mt = "<<mt<<"  ; r = "<<r<<"  ;  Parameter inside K1 = "<<(mt*cosh(rho))/T<<endl;
    }
    s += TMath::BesselK1((mt*cosh(rho))/T);
  }

  //double s = (mt*cosh(rho))/T;

  return s;
}

void sep01(){

  double T      = 0.16;
  double beta_T = 0.6;
  double n = 1;
  double pt = 0.35;

  const int nPt = 30;
  double newPt[nPt];
  for(int i=0; i<nPt; i++){
    newPt[i]=0.1+i*0.1; //pt from 0.1 to 3.0;
  }

  double yKs = 0.6;
  double eYks = 0.018;
  double m = 0.497;
  //double m = 1.115;
  double mt = sqrt(m*m + pt*pt);

  double aka = 1000;

  double theo = aka * mt * integral(beta_T, T, n, pt, mt);

  double newMt[nPt];
  double newTheo[nPt];
  //cout<<"theo = "<<theo<<"   yKs = "<<yKs<<"   eyKs = "<<eYks<<endl;
  for(int i=0; i<nPt; i++){
    newMt[i] = sqrt(m*m + newPt[i]*newPt[i]);
    //cout<<"pt = "<<newPt[i]<<"  mt = "<<newMt[i]<<endl;
    newTheo[i] = aka * newMt[i] * integral(beta_T, T, n, newPt[i], newMt[i]);
    //cout<<"pt = "<<newPt[i]<<"   theo = "<<newTheo[i]<<endl;

    //cout<<"par inside BesselK1 = "<<parBesselK1(newMt[i], beta_T, n, T)<<endl;
    //cout<<"par inside BesselK1 = "<<parBesselK1(newMt[i], beta_T, n, T)<<endl;

    cout<<"pt = "<<newPt[i]<<endl;
    double tmp = parBesselK1(newMt[i], beta_T, n, T);

  }

}

