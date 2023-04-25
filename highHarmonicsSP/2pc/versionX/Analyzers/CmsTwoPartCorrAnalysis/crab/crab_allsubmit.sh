crab_submit() {
for ((i=$1; i<$2; i++))
    do
    crab submit -c crab_2022Data_AOD.py General.requestName=PbPb_AllCent_Raw"$i"_MB_JSON_newEventSelections_GeneralTrack_vnpT_Feb19_new Data.inputDataset=/HITestRaw"$i"/HIRun2022A-PromptReco-v1/AOD Data.outputDatasetTag=PbPb_AllCent_Raw"$i"_MB_JSON_newEventSelections_GeneralTrack_vnpT_Feb19_new
    done
}
