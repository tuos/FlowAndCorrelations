#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=2G
#SBATCH --time=2-20:00:00


echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=el9_amd64_gcc12

cd /home/tuos/oopo/data/CMSSW_15_0_9_patch3/src

#cmsenv
eval `scramv1 runtime -sh`

cd /home/tuos/oopo/data/CMSSW_15_0_9_patch3/src/OOAnalysisFlow/QCAnalysisVn/test/test/hfcoin/nene/slurm/job0

cmsRun config_analyzer_MiniAOD_cfg.py

echo "Done!"

exit 0
