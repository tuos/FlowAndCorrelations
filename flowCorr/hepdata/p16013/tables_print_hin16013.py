#python script for HIN16013 hepdata uploading 
# running the script to create the python macro:
# 'python tables_print_hin16013.py > submit_hin16013.py'


print('import hepdata_lib')
print('from hepdata_lib import Submission')
print('')
print('#Creating the Submission')
print('submission = Submission()')
print('submission.read_abstract("/afs/cern.ch/user/t/tuos/work/private/hepdata/hin16013_abstract.txt")')
print('submission.add_link("Webpage with all figures and tables", "https://cms-results.web.cern.ch/cms-results/public-results/publications/HIN-16-013/")')
print('submission.add_link("arXiv", "https://arxiv.org/abs/1910.04812")')
print('submission.add_record_id(1758692, "inspire")')
print('')
print('')

print('from hepdata_lib import Table')
print('import numpy as np')
print('from hepdata_lib import Variable')
print('from hepdata_lib import Uncertainty')

print('')


nTables = 51

print('')
for i in range(nTables):
    print('#####Adding Table '+str(i+1)+'#####')
    print('table'+str(i+1)+' = Table("data'+str(i+1)+'")')
    if i+1<21 :
        print('table'+str(i+1)+'.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from XX to XX in pp collisions"')
    if i+1>30 and i+1<43 :
        print('table'+str(i+1)+'.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from XX to XX in pp collisions"')
    if i+1>20 and i+1<31 :
        print('table'+str(i+1)+'.description = "The $R_{pPb}$ of K0s for $y_{CM}$ from XX to XX"')
    if i+1>42 :
        print('table'+str(i+1)+'.description = "The $Y_{asym}$ of K0s for $|y_{CM}|$ from XX to XX in pPb collisions"')

    print('table'+str(i+1)+'.location = "Data from panel X of Figure X"')
    print('table'+str(i+1)+'.keywords["reactions"] = ["P P --> K0S X"]')
    print('table'+str(i+1)+'.keywords["cmenergies"] = ["5.02"]')
    if i+1<21 :
        print('table'+str(i+1)+'.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]')
    if i+1>30 and i+1<43 :
        print('table'+str(i+1)+'.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]')
    if i+1>20 and i+1<31 :
        print('table'+str(i+1)+'.keywords["observables"] = ["$R_{pPb}$"]')
    if i+1>42 :
        print('table'+str(i+1)+'.keywords["observables"] = ["$Y_{asym}$"]')

    print('data'+str(i+1)+' = np.loadtxt("../data_hin16013/figX_X.txt", skiprows=0)')
    print('xValue'+str(i+1)+' = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")')
    print('xValue'+str(i+1)+'.values = list(zip(data'+str(i+1)+'[:,0], data'+str(i+1)+'[:,1]))')
    if i+1<21 :
        print('yValue'+str(i+1)+' = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")')
    if i+1>30 and i+1<43 :
        print('yValue'+str(i+1)+' = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")')
    if i+1>20 and i+1<31 :
        print('yValue'+str(i+1)+' = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")')
    if i+1>42 :
        print('yValue'+str(i+1)+' = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")')

    print('yValue'+str(i+1)+'.values = data'+str(i+1)+'[:,3]')
    print('yValue'+str(i+1)+'.add_qualifier("RE", "P P --> K0S X")')
    print('yValue'+str(i+1)+'.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")')
    print('yValue'+str(i+1)+'.add_qualifier("RAPIDITY YCM", "X TO Y")')
    print('unc_stat'+str(i+1)+' = Uncertainty("Statistical uncertainty", is_symmetric=True)')
    print('unc_stat'+str(i+1)+'.values = data'+str(i+1)+'[:,4]')
    print('yValue'+str(i+1)+'.add_uncertainty(unc_stat'+str(i+1)+')')

    if i+1>20 and i+1<31 : 
        print('unc_syst'+str(i+1)+' = Uncertainty("Systematic uncertainty", is_symmetric=True)')
        print('unc_syst'+str(i+1)+'.values = data'+str(i+1)+'[:,5]')
        print('yValue'+str(i+1)+'.add_uncertainty(unc_syst'+str(i+1)+')')
    if i+1>42 :
        print('unc_syst'+str(i+1)+' = Uncertainty("Systematic uncertainty", is_symmetric=True)')
        print('unc_syst'+str(i+1)+'.values = data'+str(i+1)+'[:,5]')
        print('yValue'+str(i+1)+'.add_uncertainty(unc_syst'+str(i+1)+')')

    print('table'+str(i+1)+'.add_variable(xValue'+str(i+1)+')')
    print('table'+str(i+1)+'.add_variable(yValue'+str(i+1)+')')
    print('submission.add_table(table'+str(i+1)+')')
    print('')

print('')
print('')
 
print('#Adding Output')
print('outdir = "hin16013hepdata_output"')
print('submission.create_files(outdir)')
print('')
print('')




