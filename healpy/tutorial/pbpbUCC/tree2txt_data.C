void tree2txt_data(){

    TFile *eventFile = new TFile("/scratch/tuos/PbPb2015/ana2015/rereco2016/lxplusOutPut/aps_ucc_analyzer_data.root","read");
    TTree *tree = (TTree*)eventFile->Get("flowCorr/eventTree");
 
    Float_t pt[20000];
    Float_t eta[20000];
    Float_t phi[20000];
    int nParticles=0;
    int nEvents;

    tree->SetBranchAddress("nTracks", &nParticles);
    tree->SetBranchAddress("pt", &pt);
    tree->SetBranchAddress("eta", &eta);
    tree->SetBranchAddress("phi", &phi);

    ofstream outputFile;
    outputFile.open("eventFile_data_noHead_eta08.txt");
    nEvents=tree->GetEntries();
    for(int i=0; i<nEvents; i++){
      if(i%10==0)  cout<<"Have run "<<i<<" of all the "<<nEvents<<" events; "<<endl;
      tree->GetEntry(i);
      //outputFile<<i<<"   "<<nParticles<<endl;
      for(int j=0; j<nParticles; j++){
        if(eta[j]>0.8 || eta[j]<-0.8) continue;
        //outputFile<<pt[j]<<"   "<<eta[j]<<"   "<<phi[j]<<endl;
        outputFile<<pt[j]<<"   "<<2*TMath::ATan(exp(-eta[j]))<<"   "<<phi[j]<<endl;
      }

    }

}

