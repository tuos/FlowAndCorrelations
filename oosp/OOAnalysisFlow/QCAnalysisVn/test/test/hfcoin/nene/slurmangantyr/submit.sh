#!/bin/sh
njobs=77
for i in `seq 0 $(($njobs-1))`
do

echo $i
jobi=job$i
mkdir $jobi

filex=output_job$i.txt
cp $filex $jobi
cp config_analyzer_MiniAOD_cfg.py $jobi
cp jbsub.slurm $jobi
sed "s/job0/$jobi/g" $jobi/config_analyzer_MiniAOD_cfg.py > $jobi/config_analyzer_MiniAOD_cfg$i.py
sed "s/job0/$jobi/g" $jobi/jbsub.slurm > $jobi/jbsub$i.slurm
rm $jobi/jbsub.slurm
mv $jobi/config_analyzer_MiniAOD_cfg$i.py $jobi/config_analyzer_MiniAOD_cfg.py

cd $jobi
sbatch -J nenejb$i -o out_job$i.out jbsub$i.slurm
cd ..

done
