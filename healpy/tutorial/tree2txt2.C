void tree2txt2(){

    TFile *eventFile = new TFile("./aps_ucc_analyzer_data.root","read");
    TTree *tree = (TTree*)eventFile->Get("flowCorr/eventTree");
	
    Float_t pt[2664002];
    Float_t eta[2664002];
    Float_t phi[2664002];
    int nParticles=0;
    int nEvents;
	
    tree->SetBranchAddress("nTracks", &nParticles);
    tree->SetBranchAddress("pt", &pt);
    tree->SetBranchAddress("eta", &eta);
    tree->SetBranchAddress("phi", &phi);
	
    ofstream outputFile;
    outputFile.open("eventFile3.txt");
    nEvents=tree->GetEntries();
	outputFile<<nEvents<<endl;
    for(int i=0; i<nEvents; i++){
      if(i%2==0)  cout<<"Have run "<<i<<" of all the "<<nEvents<<" events; "<<endl;
      tree->GetEntry(i);
      //outputFile<<i<<"   "<<nParticles<<endl;
	  outputFile<<i<<endl;
      for(int j=0; j<nParticles; j++){
        //outputFile<<pt[j]<<"   "<<eta[j]<<"   "<<phi[j]<<endl;
        outputFile<<pt[j]<<"   "<<2*TMath::ATan(exp(-eta[j]))<<"   "<<phi[j]<<endl;
      }

    }
	
}


