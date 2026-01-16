#!/bin/sh
njobs=77
for i in `seq 0 $(($njobs-1))`
do

echo $i
jobi=job$i
mkdir $jobi

filex=output_part_$i.txt
cp filex $jobi
cp config_analyzer_MiniAOD_cfg.py $jobi
cp job.slurm $jobi
sed "s/job0/$jobi/g" $jobi/job.slurm > $jobi/job$i.slurm
rm $jobi/job.slurm

cd $j0bi
#sbatch -J oo01jb$i -o out_job$i.out job$i.slurm
cd ..

done
