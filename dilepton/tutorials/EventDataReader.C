// program to test treereader functionality
//Running the code
//[tuos@gw341 test]$ root -l
//root [0] .L EventDataReader.C+
//root [1] .x EventDataReader.C 
//

#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "Math/LorentzVector.h"
//#include "Math/Vector4d.h"
#include "Math/Vector4D.h"
#include <iostream>

#include "TStopwatch.h"

#include "TCanvas.h"
#include "EventData.h"

void EventDataReader() {

   TH1 * h1 = new TH1F("h1","inv mass neutrals",1000,0,1);
   TH1 * h2 = new TH1F("h2","inv mass charged",1000,0,1);
   TH1 * h3 = new TH1F("h3","inv mass leptons",1000,0,10);

   TFile *myFile = TFile::Open("./eventdata_s99_500k.root");

   TTreeReader myReader("tree", myFile);

   TTreeReaderValue<std::vector< Particle> > particles_value(myReader, "fParticles");


   std::cout << myReader.GetEntries(1) << std::endl;

   TStopwatch w; 
   w. Start(); 
   int iEvents = 0;
   while (myReader.Next()) {
      std::vector< Particle>  & fParticles = *particles_value; 
      int npart = fParticles.size(); 

      iEvents++;
      if(iEvents%1000==0) cout<<"iEvents = "<<iEvents<<endl;

      for (int i = 0; i< npart; ++i) { 
         for (int j = i+1; j< npart; ++j) { 
            if (fParticles[j].fType == 0 && fParticles[i].fType == 0) 
               h1->Fill( (fParticles[i].fVector + fParticles[j].fVector).M() );
            if (fParticles[i].fCharge * fParticles[j].fCharge  == -1 ) 
               h2->Fill( (fParticles[i].fVector + fParticles[j].fVector).M() );
            if ( (fParticles[i].fCharge * fParticles[j].fCharge  == -1 ) &&
                 ( (fParticles[i].fType == 1 && fParticles[j].fType == 1 ) ||
                   (fParticles[i].fType == 2 && fParticles[j].fType == 2 ) ) )
               h3->Fill( (fParticles[i].fVector + fParticles[j].fVector).M() );

         }
      }

      
   }

   std::cout << "Time to read the tree:  ";
   w.Print();
   TCanvas * c1 = new TCanvas(); 
   c1->Divide(1,3);
   c1->cd(1);
   h1->Draw();
   c1->cd(2);
   h2->Draw();
   c1->cd(3);
   h3->Draw();

}
