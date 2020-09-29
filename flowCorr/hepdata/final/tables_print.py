#python script for HIN17005 hepdata uploading 
# running the script to create the python macro:
# 'python tables_print.py > submit_hin17005.py'


print('import hepdata_lib')
print('from hepdata_lib import Submission')
print('')
print('#Creating the Submission')
print('submission = Submission()')
print('submission.read_abstract("/afs/cern.ch/user/t/tuos/work/private/hepdata/hin17005_abstract.txt")')
print('submission.add_link("Webpage with all figures and tables", "https://cms-results.web.cern.ch/cms-results/public-results/publications/HIN-17-005/")')
print('submission.add_link("arXiv", "https://arxiv.org/abs/1910.08789")')
print('submission.add_record_id(1759853, "inspire")')
print('')
print('')

print('from hepdata_lib import Table')
print('import numpy as np')
print('from hepdata_lib import Variable')
print('from hepdata_lib import Uncertainty')

print('')


nTables = 90

print('')
for i in range(nTables):
    print('#####Adding Table '+str(i+1)+'#####')
    print('table'+str(i+1)+' = Table("data'+str(i+1)+'")')
    print('table'+str(i+1)+'.description = "XX"')
    print('table'+str(i+1)+'.location = "Data from Figure XX X"')
    print('table'+str(i+1)+'.keywords["reactions"] = ["Pb Pb --> CHARGED X"]')
    print('table'+str(i+1)+'.keywords["cmenergies"] = ["5.02"]')
    print('table'+str(i+1)+'.keywords["observables"] = ["XX"]')
    print('data'+str(i+1)+' = np.loadtxt("../data_hin17005/figX_X.txt", skiprows=0)')
    if i>=60 :
        print('xValue'+str(i+1)+' = Variable("Centrality", is_independent=True, is_binned=True, units="%")')
    else :
        print('xValue'+str(i+1)+' = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")')

#    print('xValue'+str(i+1)+'.digits = 2')
    print('xValue'+str(i+1)+'.values = list(zip(data'+str(i+1)+'[:,0], data'+str(i+1)+'[:,1]))')

    if i<20 :
        print('yValue'+str(i+1)+' = Variable("XX", is_independent=False, is_binned=False, units="")')
    elif i>=20 and i<30 :
        print('yValue'+str(i+1)+' = Variable("XX", is_independent=False, is_binned=False, units="")')
    elif i>=30 and i<40 :
        print('yValue'+str(i+1)+' = Variable("XX", is_independent=False, is_binned=False, units="")')
    elif i>=40 and i<60 :
        print('yValue'+str(i+1)+' = Variable("XX", is_independent=False, is_binned=False, units="")')
    elif i>=60 and i<70 :
        print('yValue'+str(i+1)+' = Variable("XX", is_independent=False, is_binned=False, units="")')
    else :
        print('yValue'+str(i+1)+' = Variable("XX", is_independent=False, is_binned=False, units="")')

#    print('yValue'+str(i+1)+'.digits = 2')
    print('yValue'+str(i+1)+'.values = data'+str(i+1)+'[:,3]')
    print('yValue'+str(i+1)+'.add_qualifier("RE", "Pb Pb --> CHARGED X")')
    print('yValue'+str(i+1)+'.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")')
    print('unc_stat'+str(i+1)+' = Uncertainty("Statistical uncertainty", is_symmetric=True)')
    print('unc_stat'+str(i+1)+'.values = data'+str(i+1)+'[:,4]')
    print('unc_syst'+str(i+1)+' = Uncertainty("Systematic uncertainty", is_symmetric=True)')
    print('unc_syst'+str(i+1)+'.values = data'+str(i+1)+'[:,5]')
    print('yValue'+str(i+1)+'.add_uncertainty(unc_stat'+str(i+1)+')')
    print('yValue'+str(i+1)+'.add_uncertainty(unc_syst'+str(i+1)+')')
    print('table'+str(i+1)+'.add_variable(xValue'+str(i+1)+')')
    print('table'+str(i+1)+'.add_variable(yValue'+str(i+1)+')')
    print('submission.add_table(table'+str(i+1)+')')
    print('')

print('')
print('')
 
print('#Adding Output')
print('outdir = "hin17005hepdata_output"')
print('submission.create_files(outdir)')
print('')
print('')




