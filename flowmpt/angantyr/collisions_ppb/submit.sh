#!/bin/sh
nbatch=300 #batch number
njobs=100 #number of jobs in batch

ban=ba$nbatch
mkdir $ban

for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $ban/$jbi

cp ppb_angantyr_5tev $ban/$jbi
cp jobsub.slurm $ban/$jbi
sed "s/jb0/$jbi/g" $ban/$jbi/jobsub.slurm > $ban/$jbi/jobsub_${ban}_$jbi.slurm
sed -i "s/ba0/$ban/g" $ban/$jbi/jobsub_${ban}_$jbi.slurm
sed -i "s/batchNum/$nbatch/g" $ban/$jbi/jobsub_${ban}_$jbi.slurm
sed -i "s/jobNum/$i/g" $ban/$jbi/jobsub_${ban}_$jbi.slurm
rm $ban/$jbi/jobsub.slurm

cd $ban/$jbi
sbatch -J ${ban}j$i -o out_job_${ban}_$jbi.out jobsub_${ban}_$jbi.slurm
cd ../..

done
