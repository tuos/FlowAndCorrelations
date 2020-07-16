#include "TMinuit.h"
Float_t z[14] = {0.6, 0.57, 0.6, 0.52, 0.49, 0.4, 0.34, 0.289, 0.236, 0.195, 0.16, 0.129, 0.109, 0.089};
Float_t x[14] = {0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95, 1.05, 1.15, 1.25, 1.35, 1.45}; //,y[14],
Float_t errorz[14] = {0.049, 0.034, 0.018, 0.01, 0.0071, 0.0051, 0.0039, 0.0031, 0.0024, 0.002, 0.0017, 0.0014, 0.0012, 0.001};

Float_t z2[12] = {0.131, 0.114, 0.097, 0.08, 0.064, 0.051, 0.04, 0.0314, 0.0237, 0.0187, 0.0135, 0.0108};
Float_t x2[12] = {0.7, 0.9, 1.1, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 2.9};
Float_t errorz2[12] = {0.0062, 0.0031, 0.002, 0.0015, 0.0011, 0.00086, 0.00067, 0.00053, 0.00042, 0.00035, 0.00028, 0.00023};

const double R = 1.0;
const double dr = 1e-2; // FIXME
//______________________________________________________________________________
double integral(double beta_T, double T, double n, double pt, double mt)
{

  double s = 0.;
  for(double r = dr/2; r < R; r += dr)
  {
    double beta_r = (beta_T*(n+2)/2) * TMath::Power((r/R),n);
    double rho = TMath::ATanH(beta_r);

    s += r * dr * TMath::BesselK1((mt*cosh(rho))/T) * TMath::BesselI0((pt*sinh(rho))/T);
    if((mt*cosh(rho))/T<0){
      cout<<"pt = "<<pt<<" ;  r = "<<r<<" ;  par inside K1 = "<<(mt*cosh(rho))/T<<" ; beta_T = "<<beta_T<<" ;  T = "<<T<<endl;
    }

  }

  return s;
}
//______________________________________________________________________________
void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
   const Int_t nbins = 14;
   Int_t i;

  double aka    = par[0];
  double aka1   = par[4];
  double T      = par[2];
  double beta_T = par[1];
  double n = par[3];

  double chi2 = 0.;

//calculate chisquare
   Double_t chisq = 0;
   Double_t delta;
   for (i=0;i<nbins; i++) {

    double m = 0.497;

    double pt = x[i];
    double mt = sqrt(m*m + pt*pt);

    double a = 0.;
    a = aka;

    double theo = a * mt * integral(beta_T, T, n, pt, mt);
    double q = (z[i] - theo)/errorz[i];

    chi2 += q*q;

    cout<<"pt = "<<pt<<" ; theo = "<<theo<<endl;

   }

///la:
   const Int_t nbins2 = 12;
   for (i=0;i<nbins2; i++) {

    double m = 1.115;

    double pt = x2[i];
    double mt = sqrt(m*m + pt*pt);

    double a = 0.;
    a = aka1;

    double theo = a * mt * integral(beta_T, T, n, pt, mt);
    double q = (z2[i] - theo)/errorz2[i];

    chi2 += q*q;

   }


   f = chi2;
}
//______________________________________________________________________________
void gl_ffit()
{
/*
// The z values
   z[0]=0.6;
   z[1]=0.57;
   z[2]=0.6;
   z[3]=0.52;
   z[4]=0.49;
   z[5]=0.4;
   z[6]=0.34;
// The errors on z values
   Float_t error = 0.01;
   errorz[0]=0.049;
   errorz[1]=0.034;
   errorz[2]=0.018;
   errorz[3]=0.01;
   errorz[4]=0.0071;
   errorz[5]=0.0051;
   errorz[6]=0.0039;
// the x values
   x[0]=0.15;
   x[1]=0.25;
   x[2]=0.35;
   x[3]=0.45;
   x[4]=0.55;
   x[5]=0.65;
   x[6]=0.75;
*/


   TMinuit *gMinuit = new TMinuit(5);  //initialize TMinuit with a maximum of 5 params
   gMinuit->SetFCN(fcn);
   Double_t arglist[10];
   Int_t ierflg = 0;
   arglist[0] = 1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
// Set starting values and step sizes for parameters
   static Double_t vstart[5] = {10, 0.3 , 0.16 , 1.0, 1};
   static Double_t step[5] = {0.1 , 0.001 , 0.001 , 0.01, 0.1};
   gMinuit->mnparm(0, "aka", vstart[0], step[0], 0,0,ierflg);
   gMinuit->mnparm(1, "beta_T", vstart[1], step[1], 0,0,ierflg);
   gMinuit->mnparm(2, "Tkin", vstart[2], step[2], 0.001,10.0,ierflg);
   gMinuit->mnparm(3, "n", vstart[3], step[3], 0,0,ierflg);
   gMinuit->mnparm(4, "aka1", vstart[4], step[4], 0,0,ierflg);
// Now ready for minimization step
   arglist[0] = 500;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
// Print results
   Double_t amin,edm,errdef;
   Int_t nvpar,nparx,icstat;
   gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);

   //gMinuit->mnprin(3,amin);

}

