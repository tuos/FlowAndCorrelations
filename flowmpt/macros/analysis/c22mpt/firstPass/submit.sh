#!/bin/sh
njobs=155
for i in `seq 0 $(($njobs-1))`
do

echo $i
jbi=jb$i
mkdir $jbi


cp meanpt_vs_Nch.C $jbi
cp jobsub.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/meanpt_vs_Nch.C > $jbi/tmp.C
sed "s/jb0/$jbi/g" $jbi/jobsub.slurm > $jbi/jobsub$i.slurm
rm $jbi/jobsub.slurm
mv $jbi/tmp.C $jbi/meanpt_vs_Nch.C

cd $jbi
sbatch -J c22m$i -o out_job$i.out jobsub$i.slurm
cd ..

done




