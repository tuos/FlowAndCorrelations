// main113.cc is a part of the PYTHIA event generator.
// Copyright (C) 2021 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Authors: Leif Lonnblad <leif.lonnblad@thep.lu.se>.
// 	    Robert Pierrard <rpierrard3@gatech.edu>.
// 	    Shengquan Tuo <shengquan.tuo@vanderbilt.edu>.
// Keywords: heavy ions; charged multiplicity; centrality;
// angantyr;

// This test program will generate Pb-Pb collisions at
// sqrt(S_NN)=2.76TeV using the Angantyr model for Heavy Ion
// collisions. The analysis will divide the event in centrality
// classes using the same observable as was used for p-Pb in the ATLAS
// analysis in arXiv:1508.00848 [hep-ex] (see main112.cc). The
// centrality classes are same as in the ALICE analysis in
// arXiv:1012.1657 [nucl-ex] although the actual observable used is
// not the same. Histograms of multiplicity distributions are measured
// for each centrality percentile.

// Note that heavy ion collisions are computationally quite CPU
// intensive and generating a single event will take around a second
// on a reasonable desktop. To get reasonable statistics, this program
// will take a couple of hours to run.

// Stdlib header file for input and output.
#include <iostream>
#include <cstring>
#include <ctime>
#include <string>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"
#include "TTree.h"

// You need to include this to get access to the HIInfo object for
// HeavyIons.
#include "Pythia8/HeavyIons.h"

using namespace std;
using namespace Pythia8;

int main(int argc, char* argv[]) {
  // Create string for output file name, must include job number when executing program. Ex: ./pbpb_angantyr_5tev 5
  string outFileString; 
  if(argc > 1){ //includes number in file name
	outFileString.append("/store/user/tuos/angantyr/pp/batch500/tree_hadrons_ba");
	outFileString.append(argv[1]);
	outFileString.append("jb");
	outFileString.append(argv[2]);
	outFileString.append("_angantyr_pp13tev.root");
  }else{ //default output file name.
	cout << "Missing input argument for batch and job number!" << endl;
	return 1;
  }

  int n = outFileString.length();
  char outFileName[n+1];
  strcpy(outFileName, outFileString.c_str());


  // Create the ROOT application environment.
  TApplication theApp("hist", &argc, argv);

  Pythia pythia;

  // This forces the HeavyIons model to be used even for pp collisons.
  pythia.readString("HeavyIon:mode = 2");

  pythia.readString("Beams:eCM = 13000.");

  // Generate minimum-bias events, with or without double diffraction.
  pythia.readString("SoftQCD:nonDiffractive = on");
  //pythia.readString("SoftQCD:doubleDiffractive = on");

  // Only do a couple generations in the fitting to cross sections.
  pythia.readString("HeavyIon:SigFitNGen = 4");


  // Set seed for event generation. Based on system time and input parameter argv[1]
  //time_t timer;
  //time(&timer);
  string sBatchNum(argv[1]);
  string sJobNum(argv[2]);
  long int seed  = 1000000*stol(sBatchNum) + stol(sJobNum) + 1; //get random number using time and input value
  //seed %= 900000000; //modulo by 900,000,000 as specified by Random:seed in the Pythia library //remnant of using time for seed
  string pythiaSeed("Random:seed = ");
  pythiaSeed.append(to_string(seed));
    
  cout << "------------------------------------------" << endl;
  cout << "Batch Number: " << sBatchNum << endl << "Job Num: " << sJobNum << endl << pythiaSeed << endl;
  cout << "------------------------------------------" << endl;

  pythia.readString("Random:setSeed = on");
  pythia.readString(pythiaSeed);

  // Initialize the Angantyr model to fit the total and semi-includive
  
  // master switch for heavy ions - should be set to 2 for pp collisions
  //pythia.readString("HeavyIon:mode = 1");

  // show initialization of angantyr model
  pythia.readString("HeavyIon:ShowInit = on");

  // cross sections in Pythia within some tolerance.
  //pythia.readString("HeavyIon:SigFitErr = "
  //                  "0.02,0.02,0.1,0.05,0.05,0.0,0.1,0.0");
  // These parameters are typicall suitable for sqrt(S_NN)=5TeV
  //pythia.readString("HeavyIon:SigFitDefPar = "
  //                  "17.24,2.15,0.33,0.0,0.0,0.0,0.0,0.0");
  // A simple genetic algorithm is run for 20 generations to fit the
  // parameters.
  //pythia.readString("HeavyIon:SigFitNGen = 20");

  // set the bWidth to be very small: 1
  //pythia.readString("HeavyIon:bWidth = 1");

  // Initialise Pythia.
  pythia.init();

    const int maxMultiplicity = 50000;
    Int_t nMultiplicityTree, nPartTree, nCollTree, nCollHardTree;
    Int_t pidTree[maxMultiplicity];
    Float_t ptTree[maxMultiplicity], etaTree[maxMultiplicity], phiTree[maxMultiplicity];
    Double_t weightTree;
    Double_t etfwdTree;
    Double_t bTree;
    int savedMultiplicity;

    TFile *outTreeFile = new TFile(outFileName, "RECREATE");
    TTree *hadronTree = new TTree("hadronTree", "Tree with hadron output from PYTHIA8");
    hadronTree->Branch("nMultiplicityTree", &nMultiplicityTree, "nMultiplicityTree/I");
    hadronTree->Branch("nPartTree", &nPartTree, "nPartTree/I");
    hadronTree->Branch("nCollTree", &nCollTree, "nCollTree/I");
    hadronTree->Branch("nCollHardTree", &nCollHardTree, "nCollHardTree/I");
    hadronTree->Branch("weightTree", &weightTree, "weightTree/D");
    hadronTree->Branch("etfwdTree", &etfwdTree, "etfwdTree/D");
    hadronTree->Branch("bTree", &bTree, "bTree/D");
    hadronTree->Branch("pidTree", &pidTree, "pidTree[nMultiplicityTree]/I");
    hadronTree->Branch("ptTree", &ptTree, "ptTree[nMultiplicityTree]/F");
    hadronTree->Branch("etaTree", &etaTree, "etaTree[nMultiplicityTree]/F");
    hadronTree->Branch("phiTree", &phiTree, "phiTree[nMultiplicityTree]/F");

  // Loop over events.
  int nEvents = 5000000;
  for ( int iEvent = 0; iEvent < nEvents; ++iEvent ) {
    if ( !pythia.next() ) continue;

    if(iEvent%1000==0) cout<<"Running event number: "<<iEvent<<endl;

    double weight = pythia.info.weight();
    savedMultiplicity = 0;
    bool trigfwd = false;
    bool trigbwd = false;
    double etfwd = 0.0;
    for (int i = 0; i < pythia.event.size(); ++i){
      Particle & p = pythia.event[i];
/*
      if ( p.isFinal() ) {
        double eta = p.eta();
        if ( p.isCharged() && p.pT() > 0.1 && eta < -3.0 && eta > -5.0 )
          trigfwd = true;
        if ( p.isCharged() && p.pT() > 0.1 && eta > 3.0 && eta < 5.0 )
          trigbwd = true;
        if ( p.pT() > 0.1 && abs(eta) > 3.0 && abs(eta) < 5.0 )
          etfwd += p.eT();
      }
*/
      if (p.isFinal() && p.isCharged() && abs(p.id())>40 &&
          abs(p.eta()) < 2.4 && p.pT() > 0.3){
        ptTree[savedMultiplicity] = p.pT();
        etaTree[savedMultiplicity] = p.eta();
        phiTree[savedMultiplicity] = p.phi();
        pidTree[savedMultiplicity] = p.id();
	//cout << "pdg_id = " << p.id() << " pt = " << p.pT() << endl;
	savedMultiplicity++;
      }

    }
    weightTree = weight;
    //etfwdTree = etfwd;
    etfwdTree = 0;
    nMultiplicityTree = savedMultiplicity;

    nPartTree = pythia.info.hiInfo->nAbsTarg() +
      pythia.info.hiInfo->nDiffTarg() +
      pythia.info.hiInfo->nAbsProj() +
      pythia.info.hiInfo->nDiffProj();

    nCollTree = pythia.info.hiInfo->nAbsProj() +
      pythia.info.hiInfo->nDiffProj() +
      pythia.info.hiInfo->nAbsTarg() +
      pythia.info.hiInfo->nDiffTarg() +
      pythia.info.hiInfo->nCollND() +
      pythia.info.hiInfo->nCollDD();
    
    nCollHardTree = pythia.info.hiInfo->nCollNDTot();

    //cout<<"impact parameter b = "<<pythia.info.hiInfo->b()<<endl;

    //if ( !(trigfwd && trigbwd) ) continue;

    bTree = pythia.info.hiInfo->b();

    hadronTree->Fill();

  }

  //pythia.stat();

  outTreeFile->cd();

  hadronTree->Write();
  outTreeFile->Write();

  // And we're done!
  return 0;
}
