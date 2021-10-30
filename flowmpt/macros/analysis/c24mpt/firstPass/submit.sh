#!/bin/sh
njobs=155
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi


cp covariance_2pc_and_meanpt.C $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/covariance_2pc_and_meanpt.C > $jbi/tmp.C
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm
mv $jbi/tmp.C $jbi/covariance_2pc_and_meanpt.C

cd $jbi
sbatch -J c24m$i -o out_job$i.out jobsub$i.slurm
cd ..

done




