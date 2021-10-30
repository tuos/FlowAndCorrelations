#!/bin/sh
njobs=232
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi


cp v2_meanpt_correlator.C $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/v2_meanpt_correlator.C > $jbi/tmp.C
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm
mv $jbi/tmp.C $jbi/v2_meanpt_correlator.C

cd $jbi
sbatch -J c22c$i -o out_job$i.out jobsub$i.slurm
cd ..

done




