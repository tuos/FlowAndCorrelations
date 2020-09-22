#!/bin/bash
#SBATCH --nodes=1
#SBATCH --mem-per-cpu=4G
#SBATCH --time=1-20:00:00

echo $SLURM_JOB_ID
echo $SLURM_JOB_NAME
echo $SLURM_JOB_NODELIST

module load GCC/8.2.0 OpenMPI Python
cd /home/tuos/aps_hic/vm_setup
. venv/bin/activate

cd /home/tuos/aps_hic/Healpix_3.60/isotropic/spectrum/new/slurm
python analysis_iso_ClError.py

echo "Done!"

exit 0


