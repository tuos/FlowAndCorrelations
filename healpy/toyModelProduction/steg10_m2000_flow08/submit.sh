#!/bin/sh
njobs=10
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi


cp proSTEGvn.C $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm

sed "s/jb0/$jbi/g" $jbi/proSTEGvn.C > $jbi/proSTEGvn$i.C
mv $jbi/proSTEGvn$i.C $jbi/proSTEGvn.C

cd $jbi
sbatch -J Toyjb$i -o out_job$i.out jobsub$i.slurm
cd ..

done




