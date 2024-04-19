#!/usr/bin/bash
filename="$1"
while read -r line; do
    dirpath="$line"
    newpath="${dirpath//\//_}"
    mergedfilename="merged${newpath}.root"

    cd $dirpath
    hadd $mergedfilename *.root
    cp $mergedfilename /store/user/tuos/forSayan/rpradhan/dataMerged/ 
   
done < "$filename"


