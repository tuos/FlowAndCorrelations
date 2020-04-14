#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=2G
#SBATCH --time=0-20:00:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
export X509_USER_PROXY=/home/tuos/x509up_u126986
cd /home/tuos/run2015/CMSSW_5_3_20/src/Analysis/TestAnalysis/test/jobsFirstHalf/jb0
eval `scramv1 runtime -sh`

cmsRun confFile_cfg.py


echo "Done!"

exit 0


