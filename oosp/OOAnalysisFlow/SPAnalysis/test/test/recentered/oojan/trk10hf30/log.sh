
#hadd merged_oo_tmp.root /store/user/tuos/OO/data/SP/OOIP*_v2SP_GoTable/IonPhysics*/v2SP_Aug28ReCentered/*/*/*.root

find /store/user/tuos/OO/data/SP/OOIP*_v2SP_GoTable/IonPhysics*/v2SP_Nov29_trk10hf30/*/*/*.root > filelist.txt
bash merge_in_batches.sh merged_oo_tmp.root filelist.txt

