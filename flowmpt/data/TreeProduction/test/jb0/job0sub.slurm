#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=4G
#SBATCH --time=2-20:00:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc900
export X509_USER_PROXY=/home/tuos/x509up_u126986
cd /scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src
#cmsenv
eval `scramv1 runtime -sh`

cd /scratch/tuos/i_ana2021/pbpb/miniAOD/CMSSW_11_2_2/src/C2nMeanPtAnalysis/MeanPtAnalyzer/test/jb0

cmsRun Config_analyzer_MiniAOD_cfg.py

echo "Done!"

exit 0


