#!/bin/sh
njobs=232
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi


cp c2_4_correlator.C $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/c2_4_correlator.C > $jbi/tmp.C
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm
mv $jbi/tmp.C $jbi/c2_4_correlator.C

cd $jbi
sbatch -J c24c$i -o out_job$i.out jobsub$i.slurm
cd ..

done




