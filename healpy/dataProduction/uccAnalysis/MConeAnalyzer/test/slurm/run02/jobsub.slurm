#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=2G
#SBATCH --time=0-20:00:00
#SBATCH --output=job02.out
#SBATCH --job-name="job02"

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
export X509_USER_PROXY=/home/tuos/x509up_u126986
cd /scratch/tuos/PbPb2015/ana2015/rereco2016/aps/CMSSW_10_3_0/src/uccAnalysis/MConeAnalyzer/test/slurm/run02
eval `scramv1 runtime -sh`

cmsRun ConfFile_cfg.py

echo "Done!"

exit 0


