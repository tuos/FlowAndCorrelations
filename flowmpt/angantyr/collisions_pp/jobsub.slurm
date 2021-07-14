#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=2G
#SBATCH --time=2-20:00:00


echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc700

cd /scratch/tuos/trigger/CMSSW_10_3_0_pre5/src

#cmsenv
eval `scramv1 runtime -sh`

export PYTHIA8DATA=/scratch/tuos/models/angantyr/root/dev/ppb_pp/pythia8305/share/Pythia8/xmldoc

cd /gpfs23/scratch/tuos/models/angantyr/root/dev/ppb_pp/pythia8305/production/collisions_pp/ba500/jb0


./pp_angantyr_13tev batchNum jobNum

echo "Done!"

exit 0


