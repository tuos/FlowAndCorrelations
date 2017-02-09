#include "TString.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include <fstream>
#include <Riostream.h>
#include <sstream>
#include <fstream>
using namespace std;

TGraphErrors* GetGraphWithSymmYErrorsFromFile(TString txtFileName, Color_t markerColor=1, Style_t markerStyle=20, Size_t markerSize=1, Style_t lineStyle=1,Width_t lineWidth=2, bool IsNoErr=0)
{
  Float_t x_array[400],ex_array[400],y_array[400],ey_array[400];
  Char_t buffer[2048];
  Float_t x,y,ex,ey;
  Int_t nlines = 0;
  ifstream infile(txtFileName.Data());

  if (!infile.is_open()) {
    cout << "Error opening file. Exiting." << endl;
  } else {
    while (!infile.eof()) {
      infile.getline(buffer,2048);
      sscanf(buffer,"%f %f %f\n",&x,&y,&ey);
      x_array[nlines] = x;
      ex_array[nlines] = 0;
      y_array[nlines] = y;
      ey_array[nlines] = ey;
      if(IsNoErr) ey_array[nlines]=0;
      nlines++;
    }
  }
  TGraphErrors *graph =
    new TGraphErrors(nlines-1,x_array,y_array,ex_array,ey_array);
  txtFileName.Remove(txtFileName.Index(".txt"),4);
  graph->SetName(txtFileName.Data());
  graph->SetMarkerStyle(markerStyle);
  graph->SetMarkerColor(markerColor);
  graph->SetLineStyle(lineStyle);
  graph->SetLineColor(markerColor);
  graph->SetMarkerSize(markerSize);
  graph->SetLineWidth(3);
  return graph;
}


void drawSysBoxValue(TGraph* gr, int fillcolor=TColor::GetColor("#ffff00"), double xwidth=0.3, double *percent, double xshift=0)
{
  TBox* box;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);
    double yerr = percent[n];
    box = new TBox(x+xshift-xwidth,y-fabs(yerr),x+xwidth,y+fabs(yerr));
    box->SetLineWidth(0);
    box->SetFillColor(kGray);
    box->Draw("Fsame");
  }

}

