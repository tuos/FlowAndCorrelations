import hepdata_lib
from hepdata_lib import Submission

#Creating the Submission
submission = Submission()
submission.read_abstract("/afs/cern.ch/user/t/tuos/work/private/hepdata/hin16013_abstract.txt")
submission.add_link("Webpage with all figures and tables", "https://cms-results.web.cern.ch/cms-results/public-results/publications/HIN-16-013/")
submission.add_link("arXiv", "https://arxiv.org/abs/1910.04812")
submission.add_record_id(1758692, "inspire")


from hepdata_lib import Table
import numpy as np
from hepdata_lib import Variable
from hepdata_lib import Uncertainty


#####Adding Table 1#####
table1 = Table("data1")
table1.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -1.8 to 0 in pp collisions"
table1.location = "Data from panel 1 of Figure 2"
table1.keywords["reactions"] = ["P P --> K0S X"]
table1.keywords["cmenergies"] = ["5.02"]
table1.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data1 = np.loadtxt("../data_hin16013/fig2_a1.txt", skiprows=0)
xValue1 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue1.values = list(zip(data1[:,0], data1[:,1]))
yValue1 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue1.values = data1[:,3]
yValue1.add_qualifier("RE", "P P --> K0S X")
yValue1.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue1.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat1 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat1.values = data1[:,4]
yValue1.add_uncertainty(unc_stat1)
table1.add_variable(xValue1)
table1.add_variable(yValue1)
submission.add_table(table1)

#####Adding Table 2#####
table2 = Table("data2")
table2.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -1.8 to 1.8 in pp collisions"
table2.location = "Data from panel 1 of Figure 2"
table2.keywords["reactions"] = ["P P --> K0S X"]
table2.keywords["cmenergies"] = ["5.02"]
table2.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data2 = np.loadtxt("../data_hin16013/fig2_a2.txt", skiprows=0)
xValue2 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue2.values = list(zip(data2[:,0], data2[:,1]))
yValue2 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue2.values = data2[:,3]
yValue2.add_qualifier("RE", "P P --> K0S X")
yValue2.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue2.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat2 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat2.values = data2[:,4]
yValue2.add_uncertainty(unc_stat2)
table2.add_variable(xValue2)
table2.add_variable(yValue2)
submission.add_table(table2)

#####Adding Table 3#####
table3 = Table("data3")
table3.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from 0 to 1.8 in pp collisions"
table3.location = "Data from panel 1 of Figure 2"
table3.keywords["reactions"] = ["P P --> K0S X"]
table3.keywords["cmenergies"] = ["5.02"]
table3.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data3 = np.loadtxt("../data_hin16013/fig2_a3.txt", skiprows=0)
xValue3 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue3.values = list(zip(data3[:,0], data3[:,1]))
yValue3 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue3.values = data3[:,3]
yValue3.add_qualifier("RE", "P P --> K0S X")
yValue3.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue3.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat3 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat3.values = data3[:,4]
yValue3.add_uncertainty(unc_stat3)
table3.add_variable(xValue3)
table3.add_variable(yValue3)
submission.add_table(table3)

#####Adding Table 4#####
table4 = Table("data4")
table4.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -1.8 to 0 in pPb collisions"
table4.location = "Data from panel 1 of Figure 2"
table4.keywords["reactions"] = ["P Pb --> K0S X"]
table4.keywords["cmenergies"] = ["5.02"]
table4.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data4 = np.loadtxt("../data_hin16013/fig2_a4.txt", skiprows=0)
xValue4 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue4.values = list(zip(data4[:,0], data4[:,1]))
yValue4 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue4.values = data4[:,3]
yValue4.add_qualifier("RE", "P Pb --> K0S X")
yValue4.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue4.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat4 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat4.values = data4[:,4]
yValue4.add_uncertainty(unc_stat4)
table4.add_variable(xValue4)
table4.add_variable(yValue4)
submission.add_table(table4)

#####Adding Table 5#####
table5 = Table("data5")
table5.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -1.8 to 1.8 in pPb collisions"
table5.location = "Data from panel 1 of Figure 2"
table5.keywords["reactions"] = ["P Pb --> K0S X"]
table5.keywords["cmenergies"] = ["5.02"]
table5.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data5 = np.loadtxt("../data_hin16013/fig2_a5.txt", skiprows=0)
xValue5 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue5.values = list(zip(data5[:,0], data5[:,1]))
yValue5 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue5.values = data5[:,3]
yValue5.add_qualifier("RE", "P Pb --> K0S X")
yValue5.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue5.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat5 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat5.values = data5[:,4]
yValue5.add_uncertainty(unc_stat5)
table5.add_variable(xValue5)
table5.add_variable(yValue5)
submission.add_table(table5)

#####Adding Table 6#####
table6 = Table("data6")
table6.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from 0 to 1.8 in pPb collisions"
table6.location = "Data from panel 1 of Figure 2"
table6.keywords["reactions"] = ["P Pb --> K0S X"]
table6.keywords["cmenergies"] = ["5.02"]
table6.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data6 = np.loadtxt("../data_hin16013/fig2_a6.txt", skiprows=0)
xValue6 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue6.values = list(zip(data6[:,0], data6[:,1]))
yValue6 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue6.values = data6[:,3]
yValue6.add_qualifier("RE", "P Pb --> K0S X")
yValue6.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue6.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat6 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat6.values = data6[:,4]
yValue6.add_uncertainty(unc_stat6)
table6.add_variable(xValue6)
table6.add_variable(yValue6)
submission.add_table(table6)

#####Adding Table 7#####
table7 = Table("data7")
table7.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to 0 in pp collisions"
table7.location = "Data from panel 2 of Figure 2"
table7.keywords["reactions"] = ["P P --> Lambda + anti-Lambda X"]
table7.keywords["cmenergies"] = ["5.02"]
table7.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data7 = np.loadtxt("../data_hin16013/fig2_b1.txt", skiprows=0)
xValue7 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue7.values = list(zip(data7[:,0], data7[:,1]))
yValue7 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue7.values = data7[:,3]
yValue7.add_qualifier("RE", "P P --> Lambda + anti-Lambda X")
yValue7.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue7.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat7 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat7.values = data7[:,4]
yValue7.add_uncertainty(unc_stat7)
table7.add_variable(xValue7)
table7.add_variable(yValue7)
submission.add_table(table7)

#####Adding Table 8#####
table8 = Table("data8")
table8.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to 1.8 in pp collisions"
table8.location = "Data from panel 2 of Figure 2"
table8.keywords["reactions"] = ["P P --> Lambda + anti-Lambda X"]
table8.keywords["cmenergies"] = ["5.02"]
table8.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data8 = np.loadtxt("../data_hin16013/fig2_b2.txt", skiprows=0)
xValue8 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue8.values = list(zip(data8[:,0], data8[:,1]))
yValue8 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue8.values = data8[:,3]
yValue8.add_qualifier("RE", "P P --> Lambda + anti-Lambda X")
yValue8.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue8.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat8 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat8.values = data8[:,4]
yValue8.add_uncertainty(unc_stat8)
table8.add_variable(xValue8)
table8.add_variable(yValue8)
submission.add_table(table8)

#####Adding Table 9#####
table9 = Table("data9")
table9.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from 0 to 1.8 in pp collisions"
table9.location = "Data from panel 2 of Figure 2"
table9.keywords["reactions"] = ["P P --> Lambda + anti-Lambda X"]
table9.keywords["cmenergies"] = ["5.02"]
table9.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data9 = np.loadtxt("../data_hin16013/fig2_b3.txt", skiprows=0)
xValue9 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue9.values = list(zip(data9[:,0], data9[:,1]))
yValue9 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue9.values = data9[:,3]
yValue9.add_qualifier("RE", "P P --> Lambda + anti-Lambda X")
yValue9.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue9.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat9 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat9.values = data9[:,4]
yValue9.add_uncertainty(unc_stat9)
table9.add_variable(xValue9)
table9.add_variable(yValue9)
submission.add_table(table9)

#####Adding Table 10#####
table10 = Table("data10")
table10.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to 0 in pPb collisions"
table10.location = "Data from panel 2 of Figure 2"
table10.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table10.keywords["cmenergies"] = ["5.02"]
table10.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data10 = np.loadtxt("../data_hin16013/fig2_b4.txt", skiprows=0)
xValue10 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue10.values = list(zip(data10[:,0], data10[:,1]))
yValue10 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue10.values = data10[:,3]
yValue10.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue10.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue10.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat10 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat10.values = data10[:,4]
yValue10.add_uncertainty(unc_stat10)
table10.add_variable(xValue10)
table10.add_variable(yValue10)
submission.add_table(table10)

#####Adding Table 11#####
table11 = Table("data11")
table11.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to 1.8 in pPb collisions"
table11.location = "Data from panel 2 of Figure 2"
table11.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table11.keywords["cmenergies"] = ["5.02"]
table11.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data11 = np.loadtxt("../data_hin16013/fig2_b5.txt", skiprows=0)
xValue11 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue11.values = list(zip(data11[:,0], data11[:,1]))
yValue11 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue11.values = data11[:,3]
yValue11.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue11.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue11.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat11 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat11.values = data11[:,4]
yValue11.add_uncertainty(unc_stat11)
table11.add_variable(xValue11)
table11.add_variable(yValue11)
submission.add_table(table11)

#####Adding Table 12#####
table12 = Table("data12")
table12.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from 0 to 1.8 in pPb collisions"
table12.location = "Data from panel 2 of Figure 2"
table12.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table12.keywords["cmenergies"] = ["5.02"]
table12.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data12 = np.loadtxt("../data_hin16013/fig2_b6.txt", skiprows=0)
xValue12 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue12.values = list(zip(data12[:,0], data12[:,1]))
yValue12 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue12.values = data12[:,3]
yValue12.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue12.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue12.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat12 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat12.values = data12[:,4]
yValue12.add_uncertainty(unc_stat12)
table12.add_variable(xValue12)
table12.add_variable(yValue12)
submission.add_table(table12)

#####Adding Table 13#####
table13 = Table("data13")
table13.description = "The invariant $p_{T}$-differential spectra of Xi+ + Xi- for $y_{CM}$ from -1.8 to 0 in pp collisions"
table13.location = "Data from panel 3 of Figure 2"
table13.keywords["reactions"] = ["P P --> Xi+ + Xi- X"]
table13.keywords["cmenergies"] = ["5.02"]
table13.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data13 = np.loadtxt("../data_hin16013/fig2_c1.txt", skiprows=0)
xValue13 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue13.values = list(zip(data13[:,0], data13[:,1]))
yValue13 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue13.values = data13[:,3]
yValue13.add_qualifier("RE", "P P --> Xi+ + Xi- X")
yValue13.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue13.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat13 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat13.values = data13[:,4]
yValue13.add_uncertainty(unc_stat13)
table13.add_variable(xValue13)
table13.add_variable(yValue13)
submission.add_table(table13)

#####Adding Table 14#####
table14 = Table("data14")
table14.description = "The invariant $p_{T}$-differential spectra of Xi+ + Xi- for $y_{CM}$ from -1.8 to 1.8 in pp collisions"
table14.location = "Data from panel 3 of Figure 2"
table14.keywords["reactions"] = ["P P --> Xi+ + Xi- X"]
table14.keywords["cmenergies"] = ["5.02"]
table14.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data14 = np.loadtxt("../data_hin16013/fig2_c2.txt", skiprows=0)
xValue14 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue14.values = list(zip(data14[:,0], data14[:,1]))
yValue14 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue14.values = data14[:,3]
yValue14.add_qualifier("RE", "P P --> Xi+ + Xi- X")
yValue14.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue14.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat14 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat14.values = data14[:,4]
yValue14.add_uncertainty(unc_stat14)
table14.add_variable(xValue14)
table14.add_variable(yValue14)
submission.add_table(table14)

#####Adding Table 15#####
table15 = Table("data15")
table15.description = "The invariant $p_{T}$-differential spectra of Xi+ + Xi- for $y_{CM}$ from 0 to 1.8 in pp collisions"
table15.location = "Data from panel 3 of Figure 2"
table15.keywords["reactions"] = ["P P --> Xi+ + Xi- X"]
table15.keywords["cmenergies"] = ["5.02"]
table15.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data15 = np.loadtxt("../data_hin16013/fig2_c3.txt", skiprows=0)
xValue15 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue15.values = list(zip(data15[:,0], data15[:,1]))
yValue15 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue15.values = data15[:,3]
yValue15.add_qualifier("RE", "P P --> Xi+ + Xi- X")
yValue15.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue15.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat15 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat15.values = data15[:,4]
yValue15.add_uncertainty(unc_stat15)
table15.add_variable(xValue15)
table15.add_variable(yValue15)
submission.add_table(table15)

#####Adding Table 16#####
table16 = Table("data16")
table16.description = "The invariant $p_{T}$-differential spectra of Xi+ + Xi- for $y_{CM}$ from -1.8 to 0 in pPb collisions"
table16.location = "Data from panel 3 of Figure 2"
table16.keywords["reactions"] = ["P Pb --> Xi+ + Xi- X"]
table16.keywords["cmenergies"] = ["5.02"]
table16.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data16 = np.loadtxt("../data_hin16013/fig2_c4.txt", skiprows=0)
xValue16 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue16.values = list(zip(data16[:,0], data16[:,1]))
yValue16 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue16.values = data16[:,3]
yValue16.add_qualifier("RE", "P Pb --> Xi+ + Xi- X")
yValue16.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue16.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat16 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat16.values = data16[:,4]
yValue16.add_uncertainty(unc_stat16)
table16.add_variable(xValue16)
table16.add_variable(yValue16)
submission.add_table(table16)

#####Adding Table 17#####
table17 = Table("data17")
table17.description = "The invariant $p_{T}$-differential spectra of Xi+ + Xi- for $y_{CM}$ from -1.8 to 1.8 in pPb collisions"
table17.location = "Data from panel 3 of Figure 2"
table17.keywords["reactions"] = ["P Pb --> Xi+ + Xi- X"]
table17.keywords["cmenergies"] = ["5.02"]
table17.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data17 = np.loadtxt("../data_hin16013/fig2_c5.txt", skiprows=0)
xValue17 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue17.values = list(zip(data17[:,0], data17[:,1]))
yValue17 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue17.values = data17[:,3]
yValue17.add_qualifier("RE", "P Pb --> Xi+ + Xi- X")
yValue17.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue17.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat17 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat17.values = data17[:,4]
yValue17.add_uncertainty(unc_stat17)
table17.add_variable(xValue17)
table17.add_variable(yValue17)
submission.add_table(table17)

#####Adding Table 18#####
table18 = Table("data18")
table18.description = "The invariant $p_{T}$-differential spectra of Xi+ + Xi- for $y_{CM}$ from 0 to 1.8 in pPb collisions"
table18.location = "Data from panel 3 of Figure 2"
table18.keywords["reactions"] = ["P Pb --> Xi+ + Xi- X"]
table18.keywords["cmenergies"] = ["5.02"]
table18.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data18 = np.loadtxt("../data_hin16013/fig2_c6.txt", skiprows=0)
xValue18 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue18.values = list(zip(data18[:,0], data18[:,1]))
yValue18 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue18.values = data18[:,3]
yValue18.add_qualifier("RE", "P Pb --> Xi+ + Xi- X")
yValue18.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue18.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat18 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat18.values = data18[:,4]
yValue18.add_uncertainty(unc_stat18)
table18.add_variable(xValue18)
table18.add_variable(yValue18)
submission.add_table(table18)

#####Adding Table 19#####
table19 = Table("data19")
table19.description = "The invariant $p_{T}$-differential spectra of Omega- + anti-Omega+ for $y_{CM}$ from -1.8 to 1.8 in pp collisions"
table19.location = "Data from panel 4 of Figure 2"
table19.keywords["reactions"] = ["P P --> Omega- + anti-Omega+ X"]
table19.keywords["cmenergies"] = ["5.02"]
table19.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data19 = np.loadtxt("../data_hin16013/fig2_d1.txt", skiprows=0)
xValue19 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue19.values = list(zip(data19[:,0], data19[:,1]))
yValue19 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue19.values = data19[:,3]
yValue19.add_qualifier("RE", "P P --> Omega- + anti-Omega+ X")
yValue19.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue19.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat19 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat19.values = data19[:,4]
yValue19.add_uncertainty(unc_stat19)
table19.add_variable(xValue19)
table19.add_variable(yValue19)
submission.add_table(table19)

#####Adding Table 20#####
table20 = Table("data20")
table20.description = "The invariant $p_{T}$-differential spectra of Omega- + anti-Omega+ for $y_{CM}$ from -1.8 to 1.8 in pPb collisions"
table20.location = "Data from panel 4 of Figure 2"
table20.keywords["reactions"] = ["P Pb --> Omega- + anti-Omega+ X"]
table20.keywords["cmenergies"] = ["5.02"]
table20.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data20 = np.loadtxt("../data_hin16013/fig2_d2.txt", skiprows=0)
xValue20 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue20.values = list(zip(data20[:,0], data20[:,1]))
yValue20 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue20.values = data20[:,3]
yValue20.add_qualifier("RE", "P Pb --> Omega- + anti-Omega+ X")
yValue20.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue20.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat20 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat20.values = data20[:,4]
yValue20.add_uncertainty(unc_stat20)
table20.add_variable(xValue20)
table20.add_variable(yValue20)
submission.add_table(table20)

#####Adding Table 21#####
table21 = Table("data21")
table21.description = "The $R_{pPb}$ of K0s for $y_{CM}$ from -1.8 to 1.8"
table21.location = "Data from Figure 3"
table21.keywords["reactions"] = ["P Pb --> K0S X"]
table21.keywords["cmenergies"] = ["5.02"]
table21.keywords["observables"] = ["$R_{pPb}$"]
data21 = np.loadtxt("../data_hin16013/fig3_a1.txt", skiprows=0)
xValue21 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue21.values = list(zip(data21[:,0], data21[:,1]))
yValue21 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue21.values = data21[:,3]
yValue21.add_qualifier("RE", "P Pb --> K0S X")
yValue21.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue21.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat21 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat21.values = data21[:,4]
yValue21.add_uncertainty(unc_stat21)
unc_syst21 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst21.values = data21[:,5]
yValue21.add_uncertainty(unc_syst21)
table21.add_variable(xValue21)
table21.add_variable(yValue21)
submission.add_table(table21)

#####Adding Table 22#####
table22 = Table("data22")
table22.description = "The $R_{pPb}$ of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to 1.8"
table22.location = "Data from Figure 3"
table22.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table22.keywords["cmenergies"] = ["5.02"]
table22.keywords["observables"] = ["$R_{pPb}$"]
data22 = np.loadtxt("../data_hin16013/fig3_a2.txt", skiprows=0)
xValue22 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue22.values = list(zip(data22[:,0], data22[:,1]))
yValue22 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue22.values = data22[:,3]
yValue22.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue22.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue22.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat22 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat22.values = data22[:,4]
yValue22.add_uncertainty(unc_stat22)
unc_syst22 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst22.values = data22[:,5]
yValue22.add_uncertainty(unc_syst22)
table22.add_variable(xValue22)
table22.add_variable(yValue22)
submission.add_table(table22)

#####Adding Table 23#####
table23 = Table("data23")
table23.description = "The $R_{pPb}$ of Xi+ + Xi- for $y_{CM}$ from -1.8 to 1.8"
table23.location = "Data from Figure 3"
table23.keywords["reactions"] = ["P P --> Xi+ + Xi- X"]
table23.keywords["cmenergies"] = ["5.02"]
table23.keywords["observables"] = ["$R_{pPb}$"]
data23 = np.loadtxt("../data_hin16013/fig3_a3.txt", skiprows=0)
xValue23 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue23.values = list(zip(data23[:,0], data23[:,1]))
yValue23 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue23.values = data23[:,3]
yValue23.add_qualifier("RE", "P Pb --> Xi+ + Xi- X")
yValue23.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue23.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat23 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat23.values = data23[:,4]
yValue23.add_uncertainty(unc_stat23)
unc_syst23 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst23.values = data23[:,5]
yValue23.add_uncertainty(unc_syst23)
table23.add_variable(xValue23)
table23.add_variable(yValue23)
submission.add_table(table23)

#####Adding Table 24#####
table24 = Table("data24")
table24.description = "The $R_{pPb}$ of Omega- + anti-Omega+ for $y_{CM}$ from -1.8 to 1.8"
table24.location = "Data from Figure 3"
table24.keywords["reactions"] = ["P Pb --> Omega- + anti-Omega+ X"]
table24.keywords["cmenergies"] = ["5.02"]
table24.keywords["observables"] = ["$R_{pPb}$"]
data24 = np.loadtxt("../data_hin16013/fig3_a4.txt", skiprows=0)
xValue24 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue24.values = list(zip(data24[:,0], data24[:,1]))
yValue24 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue24.values = data24[:,3]
yValue24.add_qualifier("RE", "P Pb --> Omega- + anti-Omega+ X")
yValue24.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue24.add_qualifier("RAPIDITY YCM", "-1.8 TO 1.8")
unc_stat24 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat24.values = data24[:,4]
yValue24.add_uncertainty(unc_stat24)
unc_syst24 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst24.values = data24[:,5]
yValue24.add_uncertainty(unc_syst24)
table24.add_variable(xValue24)
table24.add_variable(yValue24)
submission.add_table(table24)

#####Adding Table 25#####
table25 = Table("data25")
table25.description = "The $R_{pPb}$ of K0s for $y_{CM}$ from -1.8 to 0"
table25.location = "Data from panel 1 of Figure 4"
table25.keywords["reactions"] = ["P Pb --> K0S X"]
table25.keywords["cmenergies"] = ["5.02"]
table25.keywords["observables"] = ["$R_{pPb}$"]
data25 = np.loadtxt("../data_hin16013/fig4_a1.txt", skiprows=0)
xValue25 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue25.values = list(zip(data25[:,0], data25[:,1]))
yValue25 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue25.values = data25[:,3]
yValue25.add_qualifier("RE", "P Pb --> K0S X")
yValue25.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue25.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat25 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat25.values = data25[:,4]
yValue25.add_uncertainty(unc_stat25)
unc_syst25 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst25.values = data25[:,5]
yValue25.add_uncertainty(unc_syst25)
table25.add_variable(xValue25)
table25.add_variable(yValue25)
submission.add_table(table25)

#####Adding Table 26#####
table26 = Table("data26")
table26.description = "The $R_{pPb}$ of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to 0"
table26.location = "Data from panel 1 of Figure 4"
table26.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table26.keywords["cmenergies"] = ["5.02"]
table26.keywords["observables"] = ["$R_{pPb}$"]
data26 = np.loadtxt("../data_hin16013/fig4_a2.txt", skiprows=0)
xValue26 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue26.values = list(zip(data26[:,0], data26[:,1]))
yValue26 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue26.values = data26[:,3]
yValue26.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue26.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue26.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat26 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat26.values = data26[:,4]
yValue26.add_uncertainty(unc_stat26)
unc_syst26 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst26.values = data26[:,5]
yValue26.add_uncertainty(unc_syst26)
table26.add_variable(xValue26)
table26.add_variable(yValue26)
submission.add_table(table26)

#####Adding Table 27#####
table27 = Table("data27")
table27.description = "The $R_{pPb}$ of Xi+ + Xi- for $y_{CM}$ from -1.8 to 0"
table27.location = "Data from panel 1 of Figure 4"
table27.keywords["reactions"] = ["P Pb --> Xi+ + Xi- X"]
table27.keywords["cmenergies"] = ["5.02"]
table27.keywords["observables"] = ["$R_{pPb}$"]
data27 = np.loadtxt("../data_hin16013/fig4_a3.txt", skiprows=0)
xValue27 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue27.values = list(zip(data27[:,0], data27[:,1]))
yValue27 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue27.values = data27[:,3]
yValue27.add_qualifier("RE", "P Pb --> Xi+ + Xi- X")
yValue27.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue27.add_qualifier("RAPIDITY YCM", "-1.8 TO 0")
unc_stat27 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat27.values = data27[:,4]
yValue27.add_uncertainty(unc_stat27)
unc_syst27 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst27.values = data27[:,5]
yValue27.add_uncertainty(unc_syst27)
table27.add_variable(xValue27)
table27.add_variable(yValue27)
submission.add_table(table27)

#####Adding Table 28#####
table28 = Table("data28")
table28.description = "The $R_{pPb}$ of K0s for $y_{CM}$ from 0 to 1.8"
table28.location = "Data from panel 2 of Figure 4"
table28.keywords["reactions"] = ["P Pb --> K0S X"]
table28.keywords["cmenergies"] = ["5.02"]
table28.keywords["observables"] = ["$R_{pPb}$"]
data28 = np.loadtxt("../data_hin16013/fig4_b1.txt", skiprows=0)
xValue28 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue28.values = list(zip(data28[:,0], data28[:,1]))
yValue28 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue28.values = data28[:,3]
yValue28.add_qualifier("RE", "P Pb --> K0S X")
yValue28.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue28.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat28 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat28.values = data28[:,4]
yValue28.add_uncertainty(unc_stat28)
unc_syst28 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst28.values = data28[:,5]
yValue28.add_uncertainty(unc_syst28)
table28.add_variable(xValue28)
table28.add_variable(yValue28)
submission.add_table(table28)

#####Adding Table 29#####
table29 = Table("data29")
table29.description = "The $R_{pPb}$ of Lambda + anti-Lambda for $y_{CM}$ from 0 to 1.8"
table29.location = "Data from panel 2 of Figure 4"
table29.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table29.keywords["cmenergies"] = ["5.02"]
table29.keywords["observables"] = ["$R_{pPb}$"]
data29 = np.loadtxt("../data_hin16013/fig4_b2.txt", skiprows=0)
xValue29 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue29.values = list(zip(data29[:,0], data29[:,1]))
yValue29 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue29.values = data29[:,3]
yValue29.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue29.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue29.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat29 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat29.values = data29[:,4]
yValue29.add_uncertainty(unc_stat29)
unc_syst29 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst29.values = data29[:,5]
yValue29.add_uncertainty(unc_syst29)
table29.add_variable(xValue29)
table29.add_variable(yValue29)
submission.add_table(table29)

#####Adding Table 30#####
table30 = Table("data30")
table30.description = "The $R_{pPb}$ of Xi+ + Xi- for $y_{CM}$ from 0 to 1.8"
table30.location = "Data from panel 2 of Figure 4"
table30.keywords["reactions"] = ["P Pb --> Xi+ + Xi- X"]
table30.keywords["cmenergies"] = ["5.02"]
table30.keywords["observables"] = ["$R_{pPb}$"]
data30 = np.loadtxt("../data_hin16013/fig4_b3.txt", skiprows=0)
xValue30 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue30.values = list(zip(data30[:,0], data30[:,1]))
yValue30 = Variable("$R_{pPb}$", is_independent=False, is_binned=False, units="")
yValue30.values = data30[:,3]
yValue30.add_qualifier("RE", "P Pb --> Xi+ + Xi- X")
yValue30.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue30.add_qualifier("RAPIDITY YCM", "0 TO 1.8")
unc_stat30 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat30.values = data30[:,4]
yValue30.add_uncertainty(unc_stat30)
unc_syst30 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst30.values = data30[:,5]
yValue30.add_uncertainty(unc_syst30)
table30.add_variable(xValue30)
table30.add_variable(yValue30)
submission.add_table(table30)

#####Adding Table 31#####
table31 = Table("data31")
table31.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -1.8 to -1.3 in pPb collisions"
table31.location = "Data from panel 1 of Figure 5"
table31.keywords["reactions"] = ["P Pb --> K0S X"]
table31.keywords["cmenergies"] = ["5.02"]
table31.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data31 = np.loadtxt("../data_hin16013/fig5_a1.txt", skiprows=0)
xValue31 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue31.values = list(zip(data31[:,0], data31[:,1]))
yValue31 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue31.values = data31[:,3]
yValue31.add_qualifier("RE", "P Pb --> K0S X")
yValue31.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue31.add_qualifier("RAPIDITY YCM", "-1.8 TO -1.3")
unc_stat31 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat31.values = data31[:,4]
yValue31.add_uncertainty(unc_stat31)
table31.add_variable(xValue31)
table31.add_variable(yValue31)
submission.add_table(table31)

#####Adding Table 32#####
table32 = Table("data32")
table32.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -1.3 to -0.8 in pPb collisions"
table32.location = "Data from panel 1 of Figure 5"
table32.keywords["reactions"] = ["P Pb --> K0S X"]
table32.keywords["cmenergies"] = ["5.02"]
table32.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data32 = np.loadtxt("../data_hin16013/fig5_a2.txt", skiprows=0)
xValue32 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue32.values = list(zip(data32[:,0], data32[:,1]))
yValue32 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue32.values = data32[:,3]
yValue32.add_qualifier("RE", "P Pb --> K0S X")
yValue32.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue32.add_qualifier("RAPIDITY YCM", "-1.3 TO -0.8")
unc_stat32 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat32.values = data32[:,4]
yValue32.add_uncertainty(unc_stat32)
table32.add_variable(xValue32)
table32.add_variable(yValue32)
submission.add_table(table32)

#####Adding Table 33#####
table33 = Table("data33")
table33.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from -0.8 to -0.3 in pPb collisions"
table33.location = "Data from panel 1 of Figure 5"
table33.keywords["reactions"] = ["P Pb --> K0S X"]
table33.keywords["cmenergies"] = ["5.02"]
table33.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data33 = np.loadtxt("../data_hin16013/fig5_a3.txt", skiprows=0)
xValue33 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue33.values = list(zip(data33[:,0], data33[:,1]))
yValue33 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue33.values = data33[:,3]
yValue33.add_qualifier("RE", "P Pb --> K0S X")
yValue33.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue33.add_qualifier("RAPIDITY YCM", "-0.8 TO -0.3")
unc_stat33 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat33.values = data33[:,4]
yValue33.add_uncertainty(unc_stat33)
table33.add_variable(xValue33)
table33.add_variable(yValue33)
submission.add_table(table33)

#####Adding Table 34#####
table34 = Table("data34")
table34.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from 0.3 to 0.8 in pPb collisions"
table34.location = "Data from panel 1 of Figure 5"
table34.keywords["reactions"] = ["P Pb --> K0S X"]
table34.keywords["cmenergies"] = ["5.02"]
table34.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data34 = np.loadtxt("../data_hin16013/fig5_a4.txt", skiprows=0)
xValue34 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue34.values = list(zip(data34[:,0], data34[:,1]))
yValue34 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue34.values = data34[:,3]
yValue34.add_qualifier("RE", "P Pb --> K0S X")
yValue34.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue34.add_qualifier("RAPIDITY YCM", "0.3 TO 0.8")
unc_stat34 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat34.values = data34[:,4]
yValue34.add_uncertainty(unc_stat34)
table34.add_variable(xValue34)
table34.add_variable(yValue34)
submission.add_table(table34)

#####Adding Table 35#####
table35 = Table("data35")
table35.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from 0.8 to 1.3 in pPb collisions"
table35.location = "Data from panel 1 of Figure 5"
table35.keywords["reactions"] = ["P Pb --> K0S X"]
table35.keywords["cmenergies"] = ["5.02"]
table35.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data35 = np.loadtxt("../data_hin16013/fig5_a5.txt", skiprows=0)
xValue35 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue35.values = list(zip(data35[:,0], data35[:,1]))
yValue35 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue35.values = data35[:,3]
yValue35.add_qualifier("RE", "P Pb --> K0S X")
yValue35.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue35.add_qualifier("RAPIDITY YCM", "0.8 TO 1.3")
unc_stat35 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat35.values = data35[:,4]
yValue35.add_uncertainty(unc_stat35)
table35.add_variable(xValue35)
table35.add_variable(yValue35)
submission.add_table(table35)

#####Adding Table 36#####
table36 = Table("data36")
table36.description = "The invariant $p_{T}$-differential spectra of K0s for $y_{CM}$ from 1.3 to 1.8 in pPb collisions"
table36.location = "Data from panel 1 of Figure 5"
table36.keywords["reactions"] = ["P Pb --> K0S X"]
table36.keywords["cmenergies"] = ["5.02"]
table36.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data36 = np.loadtxt("../data_hin16013/fig5_a6.txt", skiprows=0)
xValue36 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue36.values = list(zip(data36[:,0], data36[:,1]))
yValue36 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue36.values = data36[:,3]
yValue36.add_qualifier("RE", "P Pb --> K0S X")
yValue36.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue36.add_qualifier("RAPIDITY YCM", "1.3 TO 1.8")
unc_stat36 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat36.values = data36[:,4]
yValue36.add_uncertainty(unc_stat36)
table36.add_variable(xValue36)
table36.add_variable(yValue36)
submission.add_table(table36)

#####Adding Table 37#####
table37 = Table("data37")
table37.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -1.8 to -1.3 in pPb collisions"
table37.location = "Data from panel 2 of Figure 5"
table37.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table37.keywords["cmenergies"] = ["5.02"]
table37.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data37 = np.loadtxt("../data_hin16013/fig5_b1.txt", skiprows=0)
xValue37 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue37.values = list(zip(data37[:,0], data37[:,1]))
yValue37 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue37.values = data37[:,3]
yValue37.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue37.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue37.add_qualifier("RAPIDITY YCM", "-1.8 TO -1.3")
unc_stat37 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat37.values = data37[:,4]
yValue37.add_uncertainty(unc_stat37)
table37.add_variable(xValue37)
table37.add_variable(yValue37)
submission.add_table(table37)

#####Adding Table 38#####
table38 = Table("data38")
table38.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -1.3 to -0.8 in pPb collisions"
table38.location = "Data from panel 2 of Figure 5"
table38.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table38.keywords["cmenergies"] = ["5.02"]
table38.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data38 = np.loadtxt("../data_hin16013/fig5_b2.txt", skiprows=0)
xValue38 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue38.values = list(zip(data38[:,0], data38[:,1]))
yValue38 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue38.values = data38[:,3]
yValue38.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue38.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue38.add_qualifier("RAPIDITY YCM", "-1.3 TO -0.8")
unc_stat38 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat38.values = data38[:,4]
yValue38.add_uncertainty(unc_stat38)
table38.add_variable(xValue38)
table38.add_variable(yValue38)
submission.add_table(table38)

#####Adding Table 39#####
table39 = Table("data39")
table39.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from -0.8 to -0.3 in pPb collisions"
table39.location = "Data from panel 2 of Figure 5"
table39.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table39.keywords["cmenergies"] = ["5.02"]
table39.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data39 = np.loadtxt("../data_hin16013/fig5_b3.txt", skiprows=0)
xValue39 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue39.values = list(zip(data39[:,0], data39[:,1]))
yValue39 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue39.values = data39[:,3]
yValue39.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue39.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue39.add_qualifier("RAPIDITY YCM", "-0.8 TO -0.3")
unc_stat39 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat39.values = data39[:,4]
yValue39.add_uncertainty(unc_stat39)
table39.add_variable(xValue39)
table39.add_variable(yValue39)
submission.add_table(table39)

#####Adding Table 40#####
table40 = Table("data40")
table40.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from 0.3 to 0.8 in pPb collisions"
table40.location = "Data from panel 2 of Figure 5"
table40.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table40.keywords["cmenergies"] = ["5.02"]
table40.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data40 = np.loadtxt("../data_hin16013/fig5_b4.txt", skiprows=0)
xValue40 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue40.values = list(zip(data40[:,0], data40[:,1]))
yValue40 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue40.values = data40[:,3]
yValue40.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue40.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue40.add_qualifier("RAPIDITY YCM", "0.3 TO 0.8")
unc_stat40 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat40.values = data40[:,4]
yValue40.add_uncertainty(unc_stat40)
table40.add_variable(xValue40)
table40.add_variable(yValue40)
submission.add_table(table40)

#####Adding Table 41#####
table41 = Table("data41")
table41.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from 0.8 to 1.3 in pPb collisions"
table41.location = "Data from panel 2 of Figure 5"
table41.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table41.keywords["cmenergies"] = ["5.02"]
table41.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data41 = np.loadtxt("../data_hin16013/fig5_b5.txt", skiprows=0)
xValue41 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue41.values = list(zip(data41[:,0], data41[:,1]))
yValue41 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue41.values = data41[:,3]
yValue41.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue41.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue41.add_qualifier("RAPIDITY YCM", "0.8 TO 1.3")
unc_stat41 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat41.values = data41[:,4]
yValue41.add_uncertainty(unc_stat41)
table41.add_variable(xValue41)
table41.add_variable(yValue41)
submission.add_table(table41)

#####Adding Table 42#####
table42 = Table("data42")
table42.description = "The invariant $p_{T}$-differential spectra of Lambda + anti-Lambda for $y_{CM}$ from 1.3 to 1.8 in pPb collisions"
table42.location = "Data from panel 2 of Figure 5"
table42.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table42.keywords["cmenergies"] = ["5.02"]
table42.keywords["observables"] = ["$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$"]
data42 = np.loadtxt("../data_hin16013/fig5_b6.txt", skiprows=0)
xValue42 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue42.values = list(zip(data42[:,0], data42[:,1]))
yValue42 = Variable("$1/(N_{ev}2\pi p_{T})d^{2}N/dydp_{T}$", is_independent=False, is_binned=False, units="$GeV^{-2}$")
yValue42.values = data42[:,3]
yValue42.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue42.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue42.add_qualifier("RAPIDITY YCM", "1.3 TO 1.8")
unc_stat42 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat42.values = data42[:,4]
yValue42.add_uncertainty(unc_stat42)
table42.add_variable(xValue42)
table42.add_variable(yValue42)
submission.add_table(table42)

#####Adding Table 43#####
table43 = Table("data43")
table43.description = "The $Y_{asym}$ of K0s for $|y_{CM}|$ from 0.3 to 0.8 in pPb collisions"
table43.location = "Data from panel 1 of Figure 6"
table43.keywords["reactions"] = ["P Pb --> K0S X"]
table43.keywords["cmenergies"] = ["5.02"]
table43.keywords["observables"] = ["$Y_{asym}$"]
data43 = np.loadtxt("../data_hin16013/fig6_a1.txt", skiprows=0)
xValue43 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue43.values = list(zip(data43[:,0], data43[:,1]))
yValue43 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue43.values = data43[:,3]
yValue43.add_qualifier("RE", "P Pb --> K0S X")
yValue43.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue43.add_qualifier("RAPIDITY YCM", "0.3 TO 0.8")
unc_stat43 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat43.values = data43[:,4]
yValue43.add_uncertainty(unc_stat43)
unc_syst43 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst43.values = data43[:,5]
yValue43.add_uncertainty(unc_syst43)
table43.add_variable(xValue43)
table43.add_variable(yValue43)
submission.add_table(table43)

#####Adding Table 44#####
table44 = Table("data44")
table44.description = "The $Y_{asym}$ of Lambda + anti-Lambda for $|y_{CM}|$ from 0.3 to 0.8 in pPb collisions"
table44.location = "Data from panel 1 of Figure 6"
table44.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table44.keywords["cmenergies"] = ["5.02"]
table44.keywords["observables"] = ["$Y_{asym}$"]
data44 = np.loadtxt("../data_hin16013/fig6_a2.txt", skiprows=0)
xValue44 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue44.values = list(zip(data44[:,0], data44[:,1]))
yValue44 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue44.values = data44[:,3]
yValue44.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue44.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue44.add_qualifier("RAPIDITY YCM", "0.3 TO 0.8")
unc_stat44 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat44.values = data44[:,4]
yValue44.add_uncertainty(unc_stat44)
unc_syst44 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst44.values = data44[:,5]
yValue44.add_uncertainty(unc_syst44)
table44.add_variable(xValue44)
table44.add_variable(yValue44)
submission.add_table(table44)

#####Adding Table 45#####
table45 = Table("data45")
table45.description = "The $Y_{asym}$ of h+/- for $|y_{CM}|$ from 0.3 to 0.8 in pPb collisions"
table45.location = "Data from panel 1 of Figure 6"
table45.keywords["reactions"] = ["P Pb --> h+/- X"]
table45.keywords["cmenergies"] = ["5.02"]
table45.keywords["observables"] = ["$Y_{asym}$"]
data45 = np.loadtxt("../data_hin16013/fig6_a3.txt", skiprows=0)
xValue45 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue45.values = list(zip(data45[:,0], data45[:,1]))
yValue45 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue45.values = data45[:,3]
yValue45.add_qualifier("RE", "P Pb --> h+/- X")
yValue45.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue45.add_qualifier("RAPIDITY YCM", "0.3 TO 0.8")
unc_stat45 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat45.values = data45[:,4]
yValue45.add_uncertainty(unc_stat45)
unc_syst45 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst45.values = data45[:,5]
yValue45.add_uncertainty(unc_syst45)
table45.add_variable(xValue45)
table45.add_variable(yValue45)
submission.add_table(table45)

#####Adding Table 46#####
table46 = Table("data46")
table46.description = "The $Y_{asym}$ of K0s for $|y_{CM}|$ from 0.8 to 1.3 in pPb collisions"
table46.location = "Data from panel 2 of Figure 6"
table46.keywords["reactions"] = ["P Pb --> K0S X"]
table46.keywords["cmenergies"] = ["5.02"]
table46.keywords["observables"] = ["$Y_{asym}$"]
data46 = np.loadtxt("../data_hin16013/fig6_b1.txt", skiprows=0)
xValue46 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue46.values = list(zip(data46[:,0], data46[:,1]))
yValue46 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue46.values = data46[:,3]
yValue46.add_qualifier("RE", "P Pb --> K0S X")
yValue46.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue46.add_qualifier("RAPIDITY YCM", "0.8 TO 1.3")
unc_stat46 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat46.values = data46[:,4]
yValue46.add_uncertainty(unc_stat46)
unc_syst46 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst46.values = data46[:,5]
yValue46.add_uncertainty(unc_syst46)
table46.add_variable(xValue46)
table46.add_variable(yValue46)
submission.add_table(table46)

#####Adding Table 47#####
table47 = Table("data47")
table47.description = "The $Y_{asym}$ of Lambda + anti-Lambda for $|y_{CM}|$ from 0.8 to 1.3 in pPb collisions"
table47.location = "Data from panel 2 of Figure 6"
table47.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table47.keywords["cmenergies"] = ["5.02"]
table47.keywords["observables"] = ["$Y_{asym}$"]
data47 = np.loadtxt("../data_hin16013/fig6_b2.txt", skiprows=0)
xValue47 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue47.values = list(zip(data47[:,0], data47[:,1]))
yValue47 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue47.values = data47[:,3]
yValue47.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue47.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue47.add_qualifier("RAPIDITY YCM", "0.8 TO 1.3")
unc_stat47 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat47.values = data47[:,4]
yValue47.add_uncertainty(unc_stat47)
unc_syst47 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst47.values = data47[:,5]
yValue47.add_uncertainty(unc_syst47)
table47.add_variable(xValue47)
table47.add_variable(yValue47)
submission.add_table(table47)

#####Adding Table 48#####
table48 = Table("data48")
table48.description = "The $Y_{asym}$ of h+/- for $|y_{CM}|$ from 0.8 to 1.3 in pPb collisions"
table48.location = "Data from panel 2 of Figure 6"
table48.keywords["reactions"] = ["P Pb --> h+/- X"]
table48.keywords["cmenergies"] = ["5.02"]
table48.keywords["observables"] = ["$Y_{asym}$"]
data48 = np.loadtxt("../data_hin16013/fig6_b3.txt", skiprows=0)
xValue48 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue48.values = list(zip(data48[:,0], data48[:,1]))
yValue48 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue48.values = data48[:,3]
yValue48.add_qualifier("RE", "P Pb --> h+/- X")
yValue48.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue48.add_qualifier("RAPIDITY YCM", "0.8 TO 1.3")
unc_stat48 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat48.values = data48[:,4]
yValue48.add_uncertainty(unc_stat48)
unc_syst48 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst48.values = data48[:,5]
yValue48.add_uncertainty(unc_syst48)
table48.add_variable(xValue48)
table48.add_variable(yValue48)
submission.add_table(table48)

#####Adding Table 49#####
table49 = Table("data49")
table49.description = "The $Y_{asym}$ of K0s for $|y_{CM}|$ from 1.3 to 1.8 in pPb collisions"
table49.location = "Data from panel 3 of Figure 6"
table49.keywords["reactions"] = ["P Pb --> K0S X"]
table49.keywords["cmenergies"] = ["5.02"]
table49.keywords["observables"] = ["$Y_{asym}$"]
data49 = np.loadtxt("../data_hin16013/fig6_c1.txt", skiprows=0)
xValue49 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue49.values = list(zip(data49[:,0], data49[:,1]))
yValue49 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue49.values = data49[:,3]
yValue49.add_qualifier("RE", "P Pb --> K0S X")
yValue49.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue49.add_qualifier("RAPIDITY YCM", "1.3 TO 1.8")
unc_stat49 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat49.values = data49[:,4]
yValue49.add_uncertainty(unc_stat49)
unc_syst49 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst49.values = data49[:,5]
yValue49.add_uncertainty(unc_syst49)
table49.add_variable(xValue49)
table49.add_variable(yValue49)
submission.add_table(table49)

#####Adding Table 50#####
table50 = Table("data50")
table50.description = "The $Y_{asym}$ of Lambda + anti-Lambda for $|y_{CM}|$ from 1.3 to 1.8 in pPb collisions"
table50.location = "Data from panel 3 of Figure 6"
table50.keywords["reactions"] = ["P Pb --> Lambda + anti-Lambda X"]
table50.keywords["cmenergies"] = ["5.02"]
table50.keywords["observables"] = ["$Y_{asym}$"]
data50 = np.loadtxt("../data_hin16013/fig6_c2.txt", skiprows=0)
xValue50 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue50.values = list(zip(data50[:,0], data50[:,1]))
yValue50 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue50.values = data50[:,3]
yValue50.add_qualifier("RE", "P Pb --> Lambda + anti-Lambda X")
yValue50.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue50.add_qualifier("RAPIDITY YCM", "1.3 TO 1.8")
unc_stat50 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat50.values = data50[:,4]
yValue50.add_uncertainty(unc_stat50)
unc_syst50 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst50.values = data50[:,5]
yValue50.add_uncertainty(unc_syst50)
table50.add_variable(xValue50)
table50.add_variable(yValue50)
submission.add_table(table50)

#####Adding Table 51#####
table51 = Table("data51")
table51.description = "The $Y_{asym}$ of h+/- for $|y_{CM}|$ from 1.3 to 1.8 in pPb collisions"
table51.location = "Data from panel 3 of Figure 6"
table51.keywords["reactions"] = ["P Pb --> h+/- X"]
table51.keywords["cmenergies"] = ["5.02"]
table51.keywords["observables"] = ["$Y_{asym}$"]
data51 = np.loadtxt("../data_hin16013/fig6_c3.txt", skiprows=0)
xValue51 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue51.values = list(zip(data51[:,0], data51[:,1]))
yValue51 = Variable("$Y_{asym}$", is_independent=False, is_binned=False, units="")
yValue51.values = data51[:,3]
yValue51.add_qualifier("RE", "P Pb --> h+/- X")
yValue51.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
yValue51.add_qualifier("RAPIDITY YCM", "1.3 TO 1.8")
unc_stat51 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat51.values = data51[:,4]
yValue51.add_uncertainty(unc_stat51)
unc_syst51 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst51.values = data51[:,5]
yValue51.add_uncertainty(unc_syst51)
table51.add_variable(xValue51)
table51.add_variable(yValue51)
submission.add_table(table51)



#Adding Output
outdir = "hin16013hepdata_output"
submission.create_files(outdir)


