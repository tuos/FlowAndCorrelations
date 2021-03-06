import hepdata_lib
from hepdata_lib import Submission

#Creating the Submission
submission = Submission()
submission.read_abstract("/afs/cern.ch/user/t/tuos/work/private/hepdata/hin17005_abstract.txt")
submission.add_link("Webpage with all figures and tables", "https://cms-results.web.cern.ch/cms-results/public-results/publications/HIN-17-005/")
submission.add_link("arXiv", "https://arxiv.org/abs/1910.08789")
submission.add_record_id(1759853, "inspire")


from hepdata_lib import Table
import numpy as np
from hepdata_lib import Variable
from hepdata_lib import Uncertainty


#####Adding Table 1#####
table1 = Table("data1")
table1.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table1.location = "Data from Figure 1 a"
table1.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table1.keywords["cmenergies"] = ["5.02"]
table1.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data1 = np.loadtxt("../data_hin17005/fig1_a1.txt", skiprows=0)
xValue1 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue1.values = list(zip(data1[:,0], data1[:,1]))
yValue1 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue1.values = data1[:,3]
yValue1.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue1.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat1 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat1.values = data1[:,4]
unc_syst1 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst1.values = data1[:,5]
yValue1.add_uncertainty(unc_stat1)
yValue1.add_uncertainty(unc_syst1)
table1.add_variable(xValue1)
table1.add_variable(yValue1)
submission.add_table(table1)

#####Adding Table 2#####
table2 = Table("data2")
table2.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table2.location = "Data from Figure 1 b"
table2.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table2.keywords["cmenergies"] = ["5.02"]
table2.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data2 = np.loadtxt("../data_hin17005/fig1_b1.txt", skiprows=0)
xValue2 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue2.values = list(zip(data2[:,0], data2[:,1]))
yValue2 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue2.values = data2[:,3]
yValue2.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue2.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat2 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat2.values = data2[:,4]
unc_syst2 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst2.values = data2[:,5]
yValue2.add_uncertainty(unc_stat2)
yValue2.add_uncertainty(unc_syst2)
table2.add_variable(xValue2)
table2.add_variable(yValue2)
submission.add_table(table2)

#####Adding Table 3#####
table3 = Table("data3")
table3.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table3.location = "Data from Figure 1 c"
table3.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table3.keywords["cmenergies"] = ["5.02"]
table3.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data3 = np.loadtxt("../data_hin17005/fig1_c1.txt", skiprows=0)
xValue3 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue3.values = list(zip(data3[:,0], data3[:,1]))
yValue3 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue3.values = data3[:,3]
yValue3.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue3.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat3 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat3.values = data3[:,4]
unc_syst3 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst3.values = data3[:,5]
yValue3.add_uncertainty(unc_stat3)
yValue3.add_uncertainty(unc_syst3)
table3.add_variable(xValue3)
table3.add_variable(yValue3)
submission.add_table(table3)

#####Adding Table 4#####
table4 = Table("data4")
table4.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table4.location = "Data from Figure 1 d"
table4.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table4.keywords["cmenergies"] = ["5.02"]
table4.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data4 = np.loadtxt("../data_hin17005/fig1_d1.txt", skiprows=0)
xValue4 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue4.values = list(zip(data4[:,0], data4[:,1]))
yValue4 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue4.values = data4[:,3]
yValue4.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue4.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat4 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat4.values = data4[:,4]
unc_syst4 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst4.values = data4[:,5]
yValue4.add_uncertainty(unc_stat4)
yValue4.add_uncertainty(unc_syst4)
table4.add_variable(xValue4)
table4.add_variable(yValue4)
submission.add_table(table4)

#####Adding Table 5#####
table5 = Table("data5")
table5.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table5.location = "Data from Figure 1 e"
table5.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table5.keywords["cmenergies"] = ["5.02"]
table5.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data5 = np.loadtxt("../data_hin17005/fig1_e1.txt", skiprows=0)
xValue5 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue5.values = list(zip(data5[:,0], data5[:,1]))
yValue5 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue5.values = data5[:,3]
yValue5.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue5.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat5 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat5.values = data5[:,4]
unc_syst5 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst5.values = data5[:,5]
yValue5.add_uncertainty(unc_stat5)
yValue5.add_uncertainty(unc_syst5)
table5.add_variable(xValue5)
table5.add_variable(yValue5)
submission.add_table(table5)

#####Adding Table 6#####
table6 = Table("data6")
table6.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table6.location = "Data from Figure 1 f"
table6.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table6.keywords["cmenergies"] = ["5.02"]
table6.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data6 = np.loadtxt("../data_hin17005/fig1_f1.txt", skiprows=0)
xValue6 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue6.values = list(zip(data6[:,0], data6[:,1]))
yValue6 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue6.values = data6[:,3]
yValue6.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue6.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat6 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat6.values = data6[:,4]
unc_syst6 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst6.values = data6[:,5]
yValue6.add_uncertainty(unc_stat6)
yValue6.add_uncertainty(unc_syst6)
table6.add_variable(xValue6)
table6.add_variable(yValue6)
submission.add_table(table6)

#####Adding Table 7#####
table7 = Table("data7")
table7.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table7.location = "Data from Figure 1 g"
table7.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table7.keywords["cmenergies"] = ["5.02"]
table7.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data7 = np.loadtxt("../data_hin17005/fig1_g1.txt", skiprows=0)
xValue7 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue7.values = list(zip(data7[:,0], data7[:,1]))
yValue7 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue7.values = data7[:,3]
yValue7.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue7.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat7 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat7.values = data7[:,4]
unc_syst7 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst7.values = data7[:,5]
yValue7.add_uncertainty(unc_stat7)
yValue7.add_uncertainty(unc_syst7)
table7.add_variable(xValue7)
table7.add_variable(yValue7)
submission.add_table(table7)

#####Adding Table 8#####
table8 = Table("data8")
table8.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table8.location = "Data from Figure 1 h"
table8.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table8.keywords["cmenergies"] = ["5.02"]
table8.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data8 = np.loadtxt("../data_hin17005/fig1_h1.txt", skiprows=0)
xValue8 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue8.values = list(zip(data8[:,0], data8[:,1]))
yValue8 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue8.values = data8[:,3]
yValue8.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue8.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat8 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat8.values = data8[:,4]
unc_syst8 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst8.values = data8[:,5]
yValue8.add_uncertainty(unc_stat8)
yValue8.add_uncertainty(unc_syst8)
table8.add_variable(xValue8)
table8.add_variable(yValue8)
submission.add_table(table8)

#####Adding Table 9#####
table9 = Table("data9")
table9.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table9.location = "Data from Figure 1 i"
table9.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table9.keywords["cmenergies"] = ["5.02"]
table9.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data9 = np.loadtxt("../data_hin17005/fig1_i1.txt", skiprows=0)
xValue9 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue9.values = list(zip(data9[:,0], data9[:,1]))
yValue9 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue9.values = data9[:,3]
yValue9.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue9.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat9 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat9.values = data9[:,4]
unc_syst9 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst9.values = data9[:,5]
yValue9.add_uncertainty(unc_stat9)
yValue9.add_uncertainty(unc_syst9)
table9.add_variable(xValue9)
table9.add_variable(yValue9)
submission.add_table(table9)

#####Adding Table 10#####
table10 = Table("data10")
table10.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table10.location = "Data from Figure 1 j"
table10.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table10.keywords["cmenergies"] = ["5.02"]
table10.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data10 = np.loadtxt("../data_hin17005/fig1_j1.txt", skiprows=0)
xValue10 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue10.values = list(zip(data10[:,0], data10[:,1]))
yValue10 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue10.values = data10[:,3]
yValue10.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue10.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat10 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat10.values = data10[:,4]
unc_syst10 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst10.values = data10[:,5]
yValue10.add_uncertainty(unc_stat10)
yValue10.add_uncertainty(unc_syst10)
table10.add_variable(xValue10)
table10.add_variable(yValue10)
submission.add_table(table10)

#####Adding Table 11#####
table11 = Table("data11")
table11.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table11.location = "Data from Figure 1 a"
table11.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table11.keywords["cmenergies"] = ["2.76"]
table11.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data11 = np.loadtxt("../data_hin17005/fig1_a2.txt", skiprows=0)
xValue11 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue11.values = list(zip(data11[:,0], data11[:,1]))
yValue11 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue11.values = data11[:,3]
yValue11.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue11.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat11 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat11.values = data11[:,4]
unc_syst11 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst11.values = data11[:,5]
yValue11.add_uncertainty(unc_stat11)
yValue11.add_uncertainty(unc_syst11)
table11.add_variable(xValue11)
table11.add_variable(yValue11)
submission.add_table(table11)

#####Adding Table 12#####
table12 = Table("data12")
table12.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table12.location = "Data from Figure 1 b"
table12.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table12.keywords["cmenergies"] = ["2.76"]
table12.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data12 = np.loadtxt("../data_hin17005/fig1_b2.txt", skiprows=0)
xValue12 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue12.values = list(zip(data12[:,0], data12[:,1]))
yValue12 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue12.values = data12[:,3]
yValue12.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue12.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat12 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat12.values = data12[:,4]
unc_syst12 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst12.values = data12[:,5]
yValue12.add_uncertainty(unc_stat12)
yValue12.add_uncertainty(unc_syst12)
table12.add_variable(xValue12)
table12.add_variable(yValue12)
submission.add_table(table12)

#####Adding Table 13#####
table13 = Table("data13")
table13.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table13.location = "Data from Figure 1 c"
table13.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table13.keywords["cmenergies"] = ["2.76"]
table13.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data13 = np.loadtxt("../data_hin17005/fig1_c2.txt", skiprows=0)
xValue13 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue13.values = list(zip(data13[:,0], data13[:,1]))
yValue13 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue13.values = data13[:,3]
yValue13.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue13.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat13 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat13.values = data13[:,4]
unc_syst13 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst13.values = data13[:,5]
yValue13.add_uncertainty(unc_stat13)
yValue13.add_uncertainty(unc_syst13)
table13.add_variable(xValue13)
table13.add_variable(yValue13)
submission.add_table(table13)

#####Adding Table 14#####
table14 = Table("data14")
table14.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table14.location = "Data from Figure 1 d"
table14.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table14.keywords["cmenergies"] = ["2.76"]
table14.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data14 = np.loadtxt("../data_hin17005/fig1_d2.txt", skiprows=0)
xValue14 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue14.values = list(zip(data14[:,0], data14[:,1]))
yValue14 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue14.values = data14[:,3]
yValue14.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue14.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat14 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat14.values = data14[:,4]
unc_syst14 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst14.values = data14[:,5]
yValue14.add_uncertainty(unc_stat14)
yValue14.add_uncertainty(unc_syst14)
table14.add_variable(xValue14)
table14.add_variable(yValue14)
submission.add_table(table14)

#####Adding Table 15#####
table15 = Table("data15")
table15.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table15.location = "Data from Figure 1 e"
table15.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table15.keywords["cmenergies"] = ["2.76"]
table15.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data15 = np.loadtxt("../data_hin17005/fig1_e2.txt", skiprows=0)
xValue15 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue15.values = list(zip(data15[:,0], data15[:,1]))
yValue15 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue15.values = data15[:,3]
yValue15.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue15.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat15 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat15.values = data15[:,4]
unc_syst15 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst15.values = data15[:,5]
yValue15.add_uncertainty(unc_stat15)
yValue15.add_uncertainty(unc_syst15)
table15.add_variable(xValue15)
table15.add_variable(yValue15)
submission.add_table(table15)

#####Adding Table 16#####
table16 = Table("data16")
table16.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table16.location = "Data from Figure 1 f"
table16.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table16.keywords["cmenergies"] = ["2.76"]
table16.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data16 = np.loadtxt("../data_hin17005/fig1_f2.txt", skiprows=0)
xValue16 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue16.values = list(zip(data16[:,0], data16[:,1]))
yValue16 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue16.values = data16[:,3]
yValue16.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue16.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat16 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat16.values = data16[:,4]
unc_syst16 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst16.values = data16[:,5]
yValue16.add_uncertainty(unc_stat16)
yValue16.add_uncertainty(unc_syst16)
table16.add_variable(xValue16)
table16.add_variable(yValue16)
submission.add_table(table16)

#####Adding Table 17#####
table17 = Table("data17")
table17.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table17.location = "Data from Figure 1 g"
table17.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table17.keywords["cmenergies"] = ["2.76"]
table17.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data17 = np.loadtxt("../data_hin17005/fig1_g2.txt", skiprows=0)
xValue17 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue17.values = list(zip(data17[:,0], data17[:,1]))
yValue17 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue17.values = data17[:,3]
yValue17.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue17.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat17 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat17.values = data17[:,4]
unc_syst17 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst17.values = data17[:,5]
yValue17.add_uncertainty(unc_stat17)
yValue17.add_uncertainty(unc_syst17)
table17.add_variable(xValue17)
table17.add_variable(yValue17)
submission.add_table(table17)

#####Adding Table 18#####
table18 = Table("data18")
table18.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table18.location = "Data from Figure 1 h"
table18.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table18.keywords["cmenergies"] = ["2.76"]
table18.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data18 = np.loadtxt("../data_hin17005/fig1_h2.txt", skiprows=0)
xValue18 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue18.values = list(zip(data18[:,0], data18[:,1]))
yValue18 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue18.values = data18[:,3]
yValue18.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue18.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat18 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat18.values = data18[:,4]
unc_syst18 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst18.values = data18[:,5]
yValue18.add_uncertainty(unc_stat18)
yValue18.add_uncertainty(unc_syst18)
table18.add_variable(xValue18)
table18.add_variable(yValue18)
submission.add_table(table18)

#####Adding Table 19#####
table19 = Table("data19")
table19.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table19.location = "Data from Figure 1 i"
table19.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table19.keywords["cmenergies"] = ["2.76"]
table19.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data19 = np.loadtxt("../data_hin17005/fig1_i2.txt", skiprows=0)
xValue19 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue19.values = list(zip(data19[:,0], data19[:,1]))
yValue19 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue19.values = data19[:,3]
yValue19.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue19.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat19 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat19.values = data19[:,4]
unc_syst19 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst19.values = data19[:,5]
yValue19.add_uncertainty(unc_stat19)
yValue19.add_uncertainty(unc_syst19)
table19.add_variable(xValue19)
table19.add_variable(yValue19)
submission.add_table(table19)

#####Adding Table 20#####
table20 = Table("data20")
table20.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table20.location = "Data from Figure 1 j"
table20.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table20.keywords["cmenergies"] = ["2.76"]
table20.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data20 = np.loadtxt("../data_hin17005/fig1_j2.txt", skiprows=0)
xValue20 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue20.values = list(zip(data20[:,0], data20[:,1]))
yValue20 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue20.values = data20[:,3]
yValue20.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue20.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat20 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat20.values = data20[:,4]
unc_syst20 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst20.values = data20[:,5]
yValue20.add_uncertainty(unc_stat20)
yValue20.add_uncertainty(unc_syst20)
table20.add_variable(xValue20)
table20.add_variable(yValue20)
submission.add_table(table20)

#####Adding Table 21#####
table21 = Table("data21")
table21.description = "The overall flow harmonic $v_4\{\Psi_{4}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table21.location = "Data from Figure 2 a"
table21.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table21.keywords["cmenergies"] = ["5.02"]
table21.keywords["observables"] = ["$v_4\{\Psi_{4}\}$"]
data21 = np.loadtxt("../data_hin17005/fig2_a1.txt", skiprows=0)
xValue21 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue21.values = list(zip(data21[:,0], data21[:,1]))
yValue21 = Variable("$v_4\{\Psi_{4}\}$", is_independent=False, is_binned=False, units="")
yValue21.values = data21[:,3]
yValue21.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue21.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat21 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat21.values = data21[:,4]
unc_syst21 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst21.values = data21[:,5]
yValue21.add_uncertainty(unc_stat21)
yValue21.add_uncertainty(unc_syst21)
table21.add_variable(xValue21)
table21.add_variable(yValue21)
submission.add_table(table21)

#####Adding Table 22#####
table22 = Table("data22")
table22.description = "The overall flow harmonic $v_5\{\Psi_{5}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table22.location = "Data from Figure 2 b"
table22.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table22.keywords["cmenergies"] = ["5.02"]
table22.keywords["observables"] = ["$v_5\{\Psi_{5}\}$"]
data22 = np.loadtxt("../data_hin17005/fig2_b1.txt", skiprows=0)
xValue22 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue22.values = list(zip(data22[:,0], data22[:,1]))
yValue22 = Variable("$v_5\{\Psi_{5}\}$", is_independent=False, is_binned=False, units="")
yValue22.values = data22[:,3]
yValue22.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue22.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat22 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat22.values = data22[:,4]
unc_syst22 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst22.values = data22[:,5]
yValue22.add_uncertainty(unc_stat22)
yValue22.add_uncertainty(unc_syst22)
table22.add_variable(xValue22)
table22.add_variable(yValue22)
submission.add_table(table22)

#####Adding Table 23#####
table23 = Table("data23")
table23.description = "The overall flow harmonic $v_6\{\Psi_{6}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table23.location = "Data from Figure 2 c"
table23.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table23.keywords["cmenergies"] = ["5.02"]
table23.keywords["observables"] = ["$v_6\{\Psi_{6}\}$"]
data23 = np.loadtxt("../data_hin17005/fig2_c1.txt", skiprows=0)
xValue23 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue23.values = list(zip(data23[:,0], data23[:,1]))
yValue23 = Variable("$v_6\{\Psi_{6}\}$", is_independent=False, is_binned=False, units="")
yValue23.values = data23[:,3]
yValue23.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue23.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat23 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat23.values = data23[:,4]
unc_syst23 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst23.values = data23[:,5]
yValue23.add_uncertainty(unc_stat23)
yValue23.add_uncertainty(unc_syst23)
table23.add_variable(xValue23)
table23.add_variable(yValue23)
submission.add_table(table23)

#####Adding Table 24#####
table24 = Table("data24")
table24.description = "The overall flow harmonic $v_6\{\Psi_{6}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table24.location = "Data from Figure 2 d"
table24.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table24.keywords["cmenergies"] = ["5.02"]
table24.keywords["observables"] = ["$v_6\{\Psi_{6}\}$"]
data24 = np.loadtxt("../data_hin17005/fig2_d1.txt", skiprows=0)
xValue24 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue24.values = list(zip(data24[:,0], data24[:,1]))
yValue24 = Variable("$v_6\{\Psi_{6}\}$", is_independent=False, is_binned=False, units="")
yValue24.values = data24[:,3]
yValue24.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue24.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat24 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat24.values = data24[:,4]
unc_syst24 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst24.values = data24[:,5]
yValue24.add_uncertainty(unc_stat24)
yValue24.add_uncertainty(unc_syst24)
table24.add_variable(xValue24)
table24.add_variable(yValue24)
submission.add_table(table24)

#####Adding Table 25#####
table25 = Table("data25")
table25.description = "The overall flow harmonic $v_7\{\Psi_{7}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table25.location = "Data from Figure 2 e"
table25.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table25.keywords["cmenergies"] = ["5.02"]
table25.keywords["observables"] = ["$v_7\{\Psi_{7}\}$"]
data25 = np.loadtxt("../data_hin17005/fig2_e1.txt", skiprows=0)
xValue25 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue25.values = list(zip(data25[:,0], data25[:,1]))
yValue25 = Variable("$v_7\{\Psi_{7}\}$", is_independent=False, is_binned=False, units="")
yValue25.values = data25[:,3]
yValue25.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue25.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat25 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat25.values = data25[:,4]
unc_syst25 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst25.values = data25[:,5]
yValue25.add_uncertainty(unc_stat25)
yValue25.add_uncertainty(unc_syst25)
table25.add_variable(xValue25)
table25.add_variable(yValue25)
submission.add_table(table25)

#####Adding Table 26#####
table26 = Table("data26")
table26.description = "The overall flow harmonic $v_4\{\Psi_{4}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table26.location = "Data from Figure 2 f"
table26.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table26.keywords["cmenergies"] = ["5.02"]
table26.keywords["observables"] = ["$v_4\{\Psi_{4}\}$"]
data26 = np.loadtxt("../data_hin17005/fig2_f1.txt", skiprows=0)
xValue26 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue26.values = list(zip(data26[:,0], data26[:,1]))
yValue26 = Variable("$v_4\{\Psi_{4}\}$", is_independent=False, is_binned=False, units="")
yValue26.values = data26[:,3]
yValue26.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue26.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat26 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat26.values = data26[:,4]
unc_syst26 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst26.values = data26[:,5]
yValue26.add_uncertainty(unc_stat26)
yValue26.add_uncertainty(unc_syst26)
table26.add_variable(xValue26)
table26.add_variable(yValue26)
submission.add_table(table26)

#####Adding Table 27#####
table27 = Table("data27")
table27.description = "The overall flow harmonic $v_5\{\Psi_{5}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table27.location = "Data from Figure 2 g"
table27.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table27.keywords["cmenergies"] = ["5.02"]
table27.keywords["observables"] = ["$v_5\{\Psi_{5}\}$"]
data27 = np.loadtxt("../data_hin17005/fig2_g1.txt", skiprows=0)
xValue27 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue27.values = list(zip(data27[:,0], data27[:,1]))
yValue27 = Variable("$v_5\{\Psi_{5}\}$", is_independent=False, is_binned=False, units="")
yValue27.values = data27[:,3]
yValue27.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue27.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat27 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat27.values = data27[:,4]
unc_syst27 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst27.values = data27[:,5]
yValue27.add_uncertainty(unc_stat27)
yValue27.add_uncertainty(unc_syst27)
table27.add_variable(xValue27)
table27.add_variable(yValue27)
submission.add_table(table27)

#####Adding Table 28#####
table28 = Table("data28")
table28.description = "The overall flow harmonic $v_6\{\Psi_{6}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table28.location = "Data from Figure 2 h"
table28.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table28.keywords["cmenergies"] = ["5.02"]
table28.keywords["observables"] = ["$v_6\{\Psi_{6}\}$"]
data28 = np.loadtxt("../data_hin17005/fig2_h1.txt", skiprows=0)
xValue28 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue28.values = list(zip(data28[:,0], data28[:,1]))
yValue28 = Variable("$v_6\{\Psi_{6}\}$", is_independent=False, is_binned=False, units="")
yValue28.values = data28[:,3]
yValue28.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue28.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat28 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat28.values = data28[:,4]
unc_syst28 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst28.values = data28[:,5]
yValue28.add_uncertainty(unc_stat28)
yValue28.add_uncertainty(unc_syst28)
table28.add_variable(xValue28)
table28.add_variable(yValue28)
submission.add_table(table28)

#####Adding Table 29#####
table29 = Table("data29")
table29.description = "The overall flow harmonic $v_6\{\Psi_{6}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table29.location = "Data from Figure 2 i"
table29.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table29.keywords["cmenergies"] = ["5.02"]
table29.keywords["observables"] = ["$v_6\{\Psi_{6}\}$"]
data29 = np.loadtxt("../data_hin17005/fig2_i1.txt", skiprows=0)
xValue29 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue29.values = list(zip(data29[:,0], data29[:,1]))
yValue29 = Variable("$v_6\{\Psi_{6}\}$", is_independent=False, is_binned=False, units="")
yValue29.values = data29[:,3]
yValue29.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue29.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat29 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat29.values = data29[:,4]
unc_syst29 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst29.values = data29[:,5]
yValue29.add_uncertainty(unc_stat29)
yValue29.add_uncertainty(unc_syst29)
table29.add_variable(xValue29)
table29.add_variable(yValue29)
submission.add_table(table29)

#####Adding Table 30#####
table30 = Table("data30")
table30.description = "The overall flow harmonic $v_7\{\Psi_{7}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table30.location = "Data from Figure 2 j"
table30.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table30.keywords["cmenergies"] = ["5.02"]
table30.keywords["observables"] = ["$v_7\{\Psi_{7}\}$"]
data30 = np.loadtxt("../data_hin17005/fig2_j1.txt", skiprows=0)
xValue30 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue30.values = list(zip(data30[:,0], data30[:,1]))
yValue30 = Variable("$v_7\{\Psi_{7}\}$", is_independent=False, is_binned=False, units="")
yValue30.values = data30[:,3]
yValue30.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue30.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat30 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat30.values = data30[:,4]
unc_syst30 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst30.values = data30[:,5]
yValue30.add_uncertainty(unc_stat30)
yValue30.add_uncertainty(unc_syst30)
table30.add_variable(xValue30)
table30.add_variable(yValue30)
submission.add_table(table30)

#####Adding Table 31#####
table31 = Table("data31")
table31.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table31.location = "Data from Figure 2 a"
table31.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table31.keywords["cmenergies"] = ["5.02"]
table31.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data31 = np.loadtxt("../data_hin17005/fig2_a2.txt", skiprows=0)
xValue31 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue31.values = list(zip(data31[:,0], data31[:,1]))
yValue31 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue31.values = data31[:,3]
yValue31.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue31.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat31 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat31.values = data31[:,4]
unc_syst31 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst31.values = data31[:,5]
yValue31.add_uncertainty(unc_stat31)
yValue31.add_uncertainty(unc_syst31)
table31.add_variable(xValue31)
table31.add_variable(yValue31)
submission.add_table(table31)

#####Adding Table 32#####
table32 = Table("data32")
table32.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table32.location = "Data from Figure 2 b"
table32.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table32.keywords["cmenergies"] = ["5.02"]
table32.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data32 = np.loadtxt("../data_hin17005/fig2_b2.txt", skiprows=0)
xValue32 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue32.values = list(zip(data32[:,0], data32[:,1]))
yValue32 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue32.values = data32[:,3]
yValue32.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue32.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat32 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat32.values = data32[:,4]
unc_syst32 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst32.values = data32[:,5]
yValue32.add_uncertainty(unc_stat32)
yValue32.add_uncertainty(unc_syst32)
table32.add_variable(xValue32)
table32.add_variable(yValue32)
submission.add_table(table32)

#####Adding Table 33#####
table33 = Table("data33")
table33.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table33.location = "Data from Figure 2 c"
table33.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table33.keywords["cmenergies"] = ["5.02"]
table33.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data33 = np.loadtxt("../data_hin17005/fig2_c2.txt", skiprows=0)
xValue33 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue33.values = list(zip(data33[:,0], data33[:,1]))
yValue33 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue33.values = data33[:,3]
yValue33.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue33.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat33 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat33.values = data33[:,4]
unc_syst33 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst33.values = data33[:,5]
yValue33.add_uncertainty(unc_stat33)
yValue33.add_uncertainty(unc_syst33)
table33.add_variable(xValue33)
table33.add_variable(yValue33)
submission.add_table(table33)

#####Adding Table 34#####
table34 = Table("data34")
table34.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table34.location = "Data from Figure 2 d"
table34.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table34.keywords["cmenergies"] = ["5.02"]
table34.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data34 = np.loadtxt("../data_hin17005/fig2_d2.txt", skiprows=0)
xValue34 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue34.values = list(zip(data34[:,0], data34[:,1]))
yValue34 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue34.values = data34[:,3]
yValue34.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue34.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat34 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat34.values = data34[:,4]
unc_syst34 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst34.values = data34[:,5]
yValue34.add_uncertainty(unc_stat34)
yValue34.add_uncertainty(unc_syst34)
table34.add_variable(xValue34)
table34.add_variable(yValue34)
submission.add_table(table34)

#####Adding Table 35#####
table35 = Table("data35")
table35.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table35.location = "Data from Figure 2 e"
table35.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table35.keywords["cmenergies"] = ["5.02"]
table35.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data35 = np.loadtxt("../data_hin17005/fig2_e2.txt", skiprows=0)
xValue35 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue35.values = list(zip(data35[:,0], data35[:,1]))
yValue35 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue35.values = data35[:,3]
yValue35.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue35.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat35 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat35.values = data35[:,4]
unc_syst35 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst35.values = data35[:,5]
yValue35.add_uncertainty(unc_stat35)
yValue35.add_uncertainty(unc_syst35)
table35.add_variable(xValue35)
table35.add_variable(yValue35)
submission.add_table(table35)

#####Adding Table 36#####
table36 = Table("data36")
table36.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table36.location = "Data from Figure 2 f"
table36.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table36.keywords["cmenergies"] = ["5.02"]
table36.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data36 = np.loadtxt("../data_hin17005/fig2_f2.txt", skiprows=0)
xValue36 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue36.values = list(zip(data36[:,0], data36[:,1]))
yValue36 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue36.values = data36[:,3]
yValue36.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue36.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat36 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat36.values = data36[:,4]
unc_syst36 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst36.values = data36[:,5]
yValue36.add_uncertainty(unc_stat36)
yValue36.add_uncertainty(unc_syst36)
table36.add_variable(xValue36)
table36.add_variable(yValue36)
submission.add_table(table36)

#####Adding Table 37#####
table37 = Table("data37")
table37.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table37.location = "Data from Figure 2 g"
table37.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table37.keywords["cmenergies"] = ["5.02"]
table37.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data37 = np.loadtxt("../data_hin17005/fig2_g2.txt", skiprows=0)
xValue37 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue37.values = list(zip(data37[:,0], data37[:,1]))
yValue37 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue37.values = data37[:,3]
yValue37.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue37.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat37 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat37.values = data37[:,4]
unc_syst37 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst37.values = data37[:,5]
yValue37.add_uncertainty(unc_stat37)
yValue37.add_uncertainty(unc_syst37)
table37.add_variable(xValue37)
table37.add_variable(yValue37)
submission.add_table(table37)

#####Adding Table 38#####
table38 = Table("data38")
table38.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table38.location = "Data from Figure 2 h"
table38.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table38.keywords["cmenergies"] = ["5.02"]
table38.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data38 = np.loadtxt("../data_hin17005/fig2_h2.txt", skiprows=0)
xValue38 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue38.values = list(zip(data38[:,0], data38[:,1]))
yValue38 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue38.values = data38[:,3]
yValue38.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue38.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat38 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat38.values = data38[:,4]
unc_syst38 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst38.values = data38[:,5]
yValue38.add_uncertainty(unc_stat38)
yValue38.add_uncertainty(unc_syst38)
table38.add_variable(xValue38)
table38.add_variable(yValue38)
submission.add_table(table38)

#####Adding Table 39#####
table39 = Table("data39")
table39.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table39.location = "Data from Figure 2 i"
table39.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table39.keywords["cmenergies"] = ["5.02"]
table39.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data39 = np.loadtxt("../data_hin17005/fig2_i2.txt", skiprows=0)
xValue39 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue39.values = list(zip(data39[:,0], data39[:,1]))
yValue39 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue39.values = data39[:,3]
yValue39.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue39.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat39 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat39.values = data39[:,4]
unc_syst39 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst39.values = data39[:,5]
yValue39.add_uncertainty(unc_stat39)
yValue39.add_uncertainty(unc_syst39)
table39.add_variable(xValue39)
table39.add_variable(yValue39)
submission.add_table(table39)

#####Adding Table 40#####
table40 = Table("data40")
table40.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table40.location = "Data from Figure 2 j"
table40.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table40.keywords["cmenergies"] = ["5.02"]
table40.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data40 = np.loadtxt("../data_hin17005/fig2_j2.txt", skiprows=0)
xValue40 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue40.values = list(zip(data40[:,0], data40[:,1]))
yValue40 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue40.values = data40[:,3]
yValue40.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue40.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat40 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat40.values = data40[:,4]
unc_syst40 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst40.values = data40[:,5]
yValue40.add_uncertainty(unc_stat40)
yValue40.add_uncertainty(unc_syst40)
table40.add_variable(xValue40)
table40.add_variable(yValue40)
submission.add_table(table40)

#####Adding Table 41#####
table41 = Table("data41")
table41.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table41.location = "Data from Figure 3 a"
table41.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table41.keywords["cmenergies"] = ["5.02"]
table41.keywords["observables"] = ["$\chi_{422}$"]
data41 = np.loadtxt("../data_hin17005/fig3_a1.txt", skiprows=0)
xValue41 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue41.values = list(zip(data41[:,0], data41[:,1]))
yValue41 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue41.values = data41[:,3]
yValue41.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue41.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat41 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat41.values = data41[:,4]
unc_syst41 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst41.values = data41[:,5]
yValue41.add_uncertainty(unc_stat41)
yValue41.add_uncertainty(unc_syst41)
table41.add_variable(xValue41)
table41.add_variable(yValue41)
submission.add_table(table41)

#####Adding Table 42#####
table42 = Table("data42")
table42.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table42.location = "Data from Figure 3 b"
table42.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table42.keywords["cmenergies"] = ["5.02"]
table42.keywords["observables"] = ["$\chi_{523}$"]
data42 = np.loadtxt("../data_hin17005/fig3_b1.txt", skiprows=0)
xValue42 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue42.values = list(zip(data42[:,0], data42[:,1]))
yValue42 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue42.values = data42[:,3]
yValue42.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue42.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat42 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat42.values = data42[:,4]
unc_syst42 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst42.values = data42[:,5]
yValue42.add_uncertainty(unc_stat42)
yValue42.add_uncertainty(unc_syst42)
table42.add_variable(xValue42)
table42.add_variable(yValue42)
submission.add_table(table42)

#####Adding Table 43#####
table43 = Table("data43")
table43.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table43.location = "Data from Figure 3 c"
table43.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table43.keywords["cmenergies"] = ["5.02"]
table43.keywords["observables"] = ["$\chi_{6222}$"]
data43 = np.loadtxt("../data_hin17005/fig3_c1.txt", skiprows=0)
xValue43 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue43.values = list(zip(data43[:,0], data43[:,1]))
yValue43 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue43.values = data43[:,3]
yValue43.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue43.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat43 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat43.values = data43[:,4]
unc_syst43 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst43.values = data43[:,5]
yValue43.add_uncertainty(unc_stat43)
yValue43.add_uncertainty(unc_syst43)
table43.add_variable(xValue43)
table43.add_variable(yValue43)
submission.add_table(table43)

#####Adding Table 44#####
table44 = Table("data44")
table44.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table44.location = "Data from Figure 3 d"
table44.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table44.keywords["cmenergies"] = ["5.02"]
table44.keywords["observables"] = ["$\chi_{633}$"]
data44 = np.loadtxt("../data_hin17005/fig3_d1.txt", skiprows=0)
xValue44 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue44.values = list(zip(data44[:,0], data44[:,1]))
yValue44 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue44.values = data44[:,3]
yValue44.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue44.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat44 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat44.values = data44[:,4]
unc_syst44 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst44.values = data44[:,5]
yValue44.add_uncertainty(unc_stat44)
yValue44.add_uncertainty(unc_syst44)
table44.add_variable(xValue44)
table44.add_variable(yValue44)
submission.add_table(table44)

#####Adding Table 45#####
table45 = Table("data45")
table45.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 5.02 TeV as a function of PT in the 0-20% centrality range."
table45.location = "Data from Figure 3 e"
table45.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table45.keywords["cmenergies"] = ["5.02"]
table45.keywords["observables"] = ["$\chi_{7223}$"]
data45 = np.loadtxt("../data_hin17005/fig3_e1.txt", skiprows=0)
xValue45 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue45.values = list(zip(data45[:,0], data45[:,1]))
yValue45 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue45.values = data45[:,3]
yValue45.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue45.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat45 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat45.values = data45[:,4]
unc_syst45 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst45.values = data45[:,5]
yValue45.add_uncertainty(unc_stat45)
yValue45.add_uncertainty(unc_syst45)
table45.add_variable(xValue45)
table45.add_variable(yValue45)
submission.add_table(table45)

#####Adding Table 46#####
table46 = Table("data46")
table46.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table46.location = "Data from Figure 3 f"
table46.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table46.keywords["cmenergies"] = ["5.02"]
table46.keywords["observables"] = ["$\chi_{422}$"]
data46 = np.loadtxt("../data_hin17005/fig3_f1.txt", skiprows=0)
xValue46 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue46.values = list(zip(data46[:,0], data46[:,1]))
yValue46 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue46.values = data46[:,3]
yValue46.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue46.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat46 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat46.values = data46[:,4]
unc_syst46 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst46.values = data46[:,5]
yValue46.add_uncertainty(unc_stat46)
yValue46.add_uncertainty(unc_syst46)
table46.add_variable(xValue46)
table46.add_variable(yValue46)
submission.add_table(table46)

#####Adding Table 47#####
table47 = Table("data47")
table47.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table47.location = "Data from Figure 3 g"
table47.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table47.keywords["cmenergies"] = ["5.02"]
table47.keywords["observables"] = ["$\chi_{523}$"]
data47 = np.loadtxt("../data_hin17005/fig3_g1.txt", skiprows=0)
xValue47 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue47.values = list(zip(data47[:,0], data47[:,1]))
yValue47 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue47.values = data47[:,3]
yValue47.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue47.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat47 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat47.values = data47[:,4]
unc_syst47 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst47.values = data47[:,5]
yValue47.add_uncertainty(unc_stat47)
yValue47.add_uncertainty(unc_syst47)
table47.add_variable(xValue47)
table47.add_variable(yValue47)
submission.add_table(table47)

#####Adding Table 48#####
table48 = Table("data48")
table48.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table48.location = "Data from Figure 3 h"
table48.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table48.keywords["cmenergies"] = ["5.02"]
table48.keywords["observables"] = ["$\chi_{6222}$"]
data48 = np.loadtxt("../data_hin17005/fig3_h1.txt", skiprows=0)
xValue48 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue48.values = list(zip(data48[:,0], data48[:,1]))
yValue48 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue48.values = data48[:,3]
yValue48.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue48.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat48 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat48.values = data48[:,4]
unc_syst48 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst48.values = data48[:,5]
yValue48.add_uncertainty(unc_stat48)
yValue48.add_uncertainty(unc_syst48)
table48.add_variable(xValue48)
table48.add_variable(yValue48)
submission.add_table(table48)

#####Adding Table 49#####
table49 = Table("data49")
table49.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table49.location = "Data from Figure 3 i"
table49.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table49.keywords["cmenergies"] = ["5.02"]
table49.keywords["observables"] = ["$\chi_{633}$"]
data49 = np.loadtxt("../data_hin17005/fig3_i1.txt", skiprows=0)
xValue49 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue49.values = list(zip(data49[:,0], data49[:,1]))
yValue49 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue49.values = data49[:,3]
yValue49.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue49.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat49 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat49.values = data49[:,4]
unc_syst49 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst49.values = data49[:,5]
yValue49.add_uncertainty(unc_stat49)
yValue49.add_uncertainty(unc_syst49)
table49.add_variable(xValue49)
table49.add_variable(yValue49)
submission.add_table(table49)

#####Adding Table 50#####
table50 = Table("data50")
table50.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 5.02 TeV as a function of PT in the 20-60% centrality range."
table50.location = "Data from Figure 3 j"
table50.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table50.keywords["cmenergies"] = ["5.02"]
table50.keywords["observables"] = ["$\chi_{7223}$"]
data50 = np.loadtxt("../data_hin17005/fig3_j1.txt", skiprows=0)
xValue50 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue50.values = list(zip(data50[:,0], data50[:,1]))
yValue50 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue50.values = data50[:,3]
yValue50.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue50.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat50 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat50.values = data50[:,4]
unc_syst50 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst50.values = data50[:,5]
yValue50.add_uncertainty(unc_stat50)
yValue50.add_uncertainty(unc_syst50)
table50.add_variable(xValue50)
table50.add_variable(yValue50)
submission.add_table(table50)

#####Adding Table 51#####
table51 = Table("data51")
table51.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table51.location = "Data from Figure 3 a"
table51.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table51.keywords["cmenergies"] = ["2.76"]
table51.keywords["observables"] = ["$\chi_{422}$"]
data51 = np.loadtxt("../data_hin17005/fig3_a2.txt", skiprows=0)
xValue51 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue51.values = list(zip(data51[:,0], data51[:,1]))
yValue51 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue51.values = data51[:,3]
yValue51.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue51.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat51 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat51.values = data51[:,4]
unc_syst51 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst51.values = data51[:,5]
yValue51.add_uncertainty(unc_stat51)
yValue51.add_uncertainty(unc_syst51)
table51.add_variable(xValue51)
table51.add_variable(yValue51)
submission.add_table(table51)

#####Adding Table 52#####
table52 = Table("data52")
table52.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table52.location = "Data from Figure 3 b"
table52.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table52.keywords["cmenergies"] = ["2.76"]
table52.keywords["observables"] = ["$\chi_{523}$"]
data52 = np.loadtxt("../data_hin17005/fig3_b2.txt", skiprows=0)
xValue52 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue52.values = list(zip(data52[:,0], data52[:,1]))
yValue52 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue52.values = data52[:,3]
yValue52.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue52.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat52 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat52.values = data52[:,4]
unc_syst52 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst52.values = data52[:,5]
yValue52.add_uncertainty(unc_stat52)
yValue52.add_uncertainty(unc_syst52)
table52.add_variable(xValue52)
table52.add_variable(yValue52)
submission.add_table(table52)

#####Adding Table 53#####
table53 = Table("data53")
table53.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table53.location = "Data from Figure 3 c"
table53.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table53.keywords["cmenergies"] = ["2.76"]
table53.keywords["observables"] = ["$\chi_{6222}$"]
data53 = np.loadtxt("../data_hin17005/fig3_c2.txt", skiprows=0)
xValue53 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue53.values = list(zip(data53[:,0], data53[:,1]))
yValue53 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue53.values = data53[:,3]
yValue53.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue53.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat53 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat53.values = data53[:,4]
unc_syst53 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst53.values = data53[:,5]
yValue53.add_uncertainty(unc_stat53)
yValue53.add_uncertainty(unc_syst53)
table53.add_variable(xValue53)
table53.add_variable(yValue53)
submission.add_table(table53)

#####Adding Table 54#####
table54 = Table("data54")
table54.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table54.location = "Data from Figure 3 d"
table54.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table54.keywords["cmenergies"] = ["2.76"]
table54.keywords["observables"] = ["$\chi_{633}$"]
data54 = np.loadtxt("../data_hin17005/fig3_d2.txt", skiprows=0)
xValue54 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue54.values = list(zip(data54[:,0], data54[:,1]))
yValue54 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue54.values = data54[:,3]
yValue54.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue54.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat54 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat54.values = data54[:,4]
unc_syst54 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst54.values = data54[:,5]
yValue54.add_uncertainty(unc_stat54)
yValue54.add_uncertainty(unc_syst54)
table54.add_variable(xValue54)
table54.add_variable(yValue54)
submission.add_table(table54)

#####Adding Table 55#####
table55 = Table("data55")
table55.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 2.76 TeV as a function of PT in the 0-20% centrality range."
table55.location = "Data from Figure 3 e"
table55.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table55.keywords["cmenergies"] = ["2.76"]
table55.keywords["observables"] = ["$\chi_{7223}$"]
data55 = np.loadtxt("../data_hin17005/fig3_e2.txt", skiprows=0)
xValue55 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue55.values = list(zip(data55[:,0], data55[:,1]))
yValue55 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue55.values = data55[:,3]
yValue55.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue55.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat55 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat55.values = data55[:,4]
unc_syst55 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst55.values = data55[:,5]
yValue55.add_uncertainty(unc_stat55)
yValue55.add_uncertainty(unc_syst55)
table55.add_variable(xValue55)
table55.add_variable(yValue55)
submission.add_table(table55)

#####Adding Table 56#####
table56 = Table("data56")
table56.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table56.location = "Data from Figure 3 f"
table56.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table56.keywords["cmenergies"] = ["2.76"]
table56.keywords["observables"] = ["$\chi_{422}$"]
data56 = np.loadtxt("../data_hin17005/fig3_f2.txt", skiprows=0)
xValue56 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue56.values = list(zip(data56[:,0], data56[:,1]))
yValue56 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue56.values = data56[:,3]
yValue56.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue56.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat56 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat56.values = data56[:,4]
unc_syst56 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst56.values = data56[:,5]
yValue56.add_uncertainty(unc_stat56)
yValue56.add_uncertainty(unc_syst56)
table56.add_variable(xValue56)
table56.add_variable(yValue56)
submission.add_table(table56)

#####Adding Table 57#####
table57 = Table("data57")
table57.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table57.location = "Data from Figure 3 g"
table57.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table57.keywords["cmenergies"] = ["2.76"]
table57.keywords["observables"] = ["$\chi_{523}$"]
data57 = np.loadtxt("../data_hin17005/fig3_g2.txt", skiprows=0)
xValue57 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue57.values = list(zip(data57[:,0], data57[:,1]))
yValue57 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue57.values = data57[:,3]
yValue57.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue57.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat57 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat57.values = data57[:,4]
unc_syst57 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst57.values = data57[:,5]
yValue57.add_uncertainty(unc_stat57)
yValue57.add_uncertainty(unc_syst57)
table57.add_variable(xValue57)
table57.add_variable(yValue57)
submission.add_table(table57)

#####Adding Table 58#####
table58 = Table("data58")
table58.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table58.location = "Data from Figure 3 h"
table58.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table58.keywords["cmenergies"] = ["2.76"]
table58.keywords["observables"] = ["$\chi_{6222}$"]
data58 = np.loadtxt("../data_hin17005/fig3_h2.txt", skiprows=0)
xValue58 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue58.values = list(zip(data58[:,0], data58[:,1]))
yValue58 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue58.values = data58[:,3]
yValue58.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue58.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat58 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat58.values = data58[:,4]
unc_syst58 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst58.values = data58[:,5]
yValue58.add_uncertainty(unc_stat58)
yValue58.add_uncertainty(unc_syst58)
table58.add_variable(xValue58)
table58.add_variable(yValue58)
submission.add_table(table58)

#####Adding Table 59#####
table59 = Table("data59")
table59.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table59.location = "Data from Figure 3 i"
table59.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table59.keywords["cmenergies"] = ["2.76"]
table59.keywords["observables"] = ["$\chi_{633}$"]
data59 = np.loadtxt("../data_hin17005/fig3_i2.txt", skiprows=0)
xValue59 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue59.values = list(zip(data59[:,0], data59[:,1]))
yValue59 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue59.values = data59[:,3]
yValue59.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue59.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat59 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat59.values = data59[:,4]
unc_syst59 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst59.values = data59[:,5]
yValue59.add_uncertainty(unc_stat59)
yValue59.add_uncertainty(unc_syst59)
table59.add_variable(xValue59)
table59.add_variable(yValue59)
submission.add_table(table59)

#####Adding Table 60#####
table60 = Table("data60")
table60.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 2.76 TeV as a function of PT in the 20-60% centrality range."
table60.location = "Data from Figure 3 j"
table60.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table60.keywords["cmenergies"] = ["2.76"]
table60.keywords["observables"] = ["$\chi_{7223}$"]
data60 = np.loadtxt("../data_hin17005/fig3_j2.txt", skiprows=0)
xValue60 = Variable("PT", is_independent=True, is_binned=True, units="GeV/c")
xValue60.values = list(zip(data60[:,0], data60[:,1]))
yValue60 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue60.values = data60[:,3]
yValue60.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue60.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat60 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat60.values = data60[:,4]
unc_syst60 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst60.values = data60[:,5]
yValue60.add_uncertainty(unc_stat60)
yValue60.add_uncertainty(unc_syst60)
table60.add_variable(xValue60)
table60.add_variable(yValue60)
submission.add_table(table60)

#####Adding Table 61#####
table61 = Table("data61")
table61.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table61.location = "Data from Figure 4 a"
table61.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table61.keywords["cmenergies"] = ["5.02"]
table61.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data61 = np.loadtxt("../data_hin17005/fig4_a1.txt", skiprows=0)
xValue61 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue61.values = list(zip(data61[:,0], data61[:,1]))
yValue61 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue61.values = data61[:,3]
yValue61.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue61.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat61 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat61.values = data61[:,4]
unc_syst61 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst61.values = data61[:,5]
yValue61.add_uncertainty(unc_stat61)
yValue61.add_uncertainty(unc_syst61)
table61.add_variable(xValue61)
table61.add_variable(yValue61)
submission.add_table(table61)

#####Adding Table 62#####
table62 = Table("data62")
table62.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table62.location = "Data from Figure 4 b"
table62.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table62.keywords["cmenergies"] = ["5.02"]
table62.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data62 = np.loadtxt("../data_hin17005/fig4_b1.txt", skiprows=0)
xValue62 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue62.values = list(zip(data62[:,0], data62[:,1]))
yValue62 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue62.values = data62[:,3]
yValue62.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue62.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat62 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat62.values = data62[:,4]
unc_syst62 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst62.values = data62[:,5]
yValue62.add_uncertainty(unc_stat62)
yValue62.add_uncertainty(unc_syst62)
table62.add_variable(xValue62)
table62.add_variable(yValue62)
submission.add_table(table62)

#####Adding Table 63#####
table63 = Table("data63")
table63.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table63.location = "Data from Figure 4 c"
table63.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table63.keywords["cmenergies"] = ["5.02"]
table63.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data63 = np.loadtxt("../data_hin17005/fig4_c1.txt", skiprows=0)
xValue63 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue63.values = list(zip(data63[:,0], data63[:,1]))
yValue63 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue63.values = data63[:,3]
yValue63.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue63.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat63 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat63.values = data63[:,4]
unc_syst63 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst63.values = data63[:,5]
yValue63.add_uncertainty(unc_stat63)
yValue63.add_uncertainty(unc_syst63)
table63.add_variable(xValue63)
table63.add_variable(yValue63)
submission.add_table(table63)

#####Adding Table 64#####
table64 = Table("data64")
table64.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table64.location = "Data from Figure 4 d"
table64.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table64.keywords["cmenergies"] = ["5.02"]
table64.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data64 = np.loadtxt("../data_hin17005/fig4_d1.txt", skiprows=0)
xValue64 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue64.values = list(zip(data64[:,0], data64[:,1]))
yValue64 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue64.values = data64[:,3]
yValue64.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue64.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat64 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat64.values = data64[:,4]
unc_syst64 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst64.values = data64[:,5]
yValue64.add_uncertainty(unc_stat64)
yValue64.add_uncertainty(unc_syst64)
table64.add_variable(xValue64)
table64.add_variable(yValue64)
submission.add_table(table64)

#####Adding Table 65#####
table65 = Table("data65")
table65.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table65.location = "Data from Figure 4 e"
table65.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table65.keywords["cmenergies"] = ["5.02"]
table65.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data65 = np.loadtxt("../data_hin17005/fig4_e1.txt", skiprows=0)
xValue65 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue65.values = list(zip(data65[:,0], data65[:,1]))
yValue65 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue65.values = data65[:,3]
yValue65.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue65.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat65 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat65.values = data65[:,4]
unc_syst65 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst65.values = data65[:,5]
yValue65.add_uncertainty(unc_stat65)
yValue65.add_uncertainty(unc_syst65)
table65.add_variable(xValue65)
table65.add_variable(yValue65)
submission.add_table(table65)

#####Adding Table 66#####
table66 = Table("data66")
table66.description = "Mixed higher-order flow harmonic $v_4\{\Psi_{22}\}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table66.location = "Data from Figure 4 a"
table66.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table66.keywords["cmenergies"] = ["2.76"]
table66.keywords["observables"] = ["$v_4\{\Psi_{22}\}$"]
data66 = np.loadtxt("../data_hin17005/fig4_a2.txt", skiprows=0)
xValue66 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue66.values = list(zip(data66[:,0], data66[:,1]))
yValue66 = Variable("$v_4\{\Psi_{22}\}$", is_independent=False, is_binned=False, units="")
yValue66.values = data66[:,3]
yValue66.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue66.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat66 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat66.values = data66[:,4]
unc_syst66 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst66.values = data66[:,5]
yValue66.add_uncertainty(unc_stat66)
yValue66.add_uncertainty(unc_syst66)
table66.add_variable(xValue66)
table66.add_variable(yValue66)
submission.add_table(table66)

#####Adding Table 67#####
table67 = Table("data67")
table67.description = "Mixed higher-order flow harmonic $v_5\{\Psi_{23}\}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table67.location = "Data from Figure 4 b"
table67.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table67.keywords["cmenergies"] = ["2.76"]
table67.keywords["observables"] = ["$v_5\{\Psi_{23}\}$"]
data67 = np.loadtxt("../data_hin17005/fig4_b2.txt", skiprows=0)
xValue67 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue67.values = list(zip(data67[:,0], data67[:,1]))
yValue67 = Variable("$v_5\{\Psi_{23}\}$", is_independent=False, is_binned=False, units="")
yValue67.values = data67[:,3]
yValue67.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue67.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat67 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat67.values = data67[:,4]
unc_syst67 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst67.values = data67[:,5]
yValue67.add_uncertainty(unc_stat67)
yValue67.add_uncertainty(unc_syst67)
table67.add_variable(xValue67)
table67.add_variable(yValue67)
submission.add_table(table67)

#####Adding Table 68#####
table68 = Table("data68")
table68.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{222}\}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table68.location = "Data from Figure 4 c"
table68.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table68.keywords["cmenergies"] = ["2.76"]
table68.keywords["observables"] = ["$v_6\{\Psi_{222}\}$"]
data68 = np.loadtxt("../data_hin17005/fig4_c2.txt", skiprows=0)
xValue68 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue68.values = list(zip(data68[:,0], data68[:,1]))
yValue68 = Variable("$v_6\{\Psi_{222}\}$", is_independent=False, is_binned=False, units="")
yValue68.values = data68[:,3]
yValue68.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue68.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat68 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat68.values = data68[:,4]
unc_syst68 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst68.values = data68[:,5]
yValue68.add_uncertainty(unc_stat68)
yValue68.add_uncertainty(unc_syst68)
table68.add_variable(xValue68)
table68.add_variable(yValue68)
submission.add_table(table68)

#####Adding Table 69#####
table69 = Table("data69")
table69.description = "Mixed higher-order flow harmonic $v_6\{\Psi_{33}\}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table69.location = "Data from Figure 4 d"
table69.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table69.keywords["cmenergies"] = ["2.76"]
table69.keywords["observables"] = ["$v_6\{\Psi_{33}\}$"]
data69 = np.loadtxt("../data_hin17005/fig4_d2.txt", skiprows=0)
xValue69 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue69.values = list(zip(data69[:,0], data69[:,1]))
yValue69 = Variable("$v_6\{\Psi_{33}\}$", is_independent=False, is_binned=False, units="")
yValue69.values = data69[:,3]
yValue69.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue69.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat69 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat69.values = data69[:,4]
unc_syst69 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst69.values = data69[:,5]
yValue69.add_uncertainty(unc_stat69)
yValue69.add_uncertainty(unc_syst69)
table69.add_variable(xValue69)
table69.add_variable(yValue69)
submission.add_table(table69)

#####Adding Table 70#####
table70 = Table("data70")
table70.description = "Mixed higher-order flow harmonic $v_7\{\Psi_{223}\}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table70.location = "Data from Figure 4 e"
table70.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table70.keywords["cmenergies"] = ["2.76"]
table70.keywords["observables"] = ["$v_7\{\Psi_{223}\}$"]
data70 = np.loadtxt("../data_hin17005/fig4_e2.txt", skiprows=0)
xValue70 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue70.values = list(zip(data70[:,0], data70[:,1]))
yValue70 = Variable("$v_7\{\Psi_{223}\}$", is_independent=False, is_binned=False, units="")
yValue70.values = data70[:,3]
yValue70.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue70.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat70 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat70.values = data70[:,4]
unc_syst70 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst70.values = data70[:,5]
yValue70.add_uncertainty(unc_stat70)
yValue70.add_uncertainty(unc_syst70)
table70.add_variable(xValue70)
table70.add_variable(yValue70)
submission.add_table(table70)

#####Adding Table 71#####
table71 = Table("data71")
table71.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table71.location = "Data from Figure 5 a"
table71.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table71.keywords["cmenergies"] = ["5.02"]
table71.keywords["observables"] = ["$\chi_{422}$"]
data71 = np.loadtxt("../data_hin17005/fig5_a1.txt", skiprows=0)
xValue71 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue71.values = list(zip(data71[:,0], data71[:,1]))
yValue71 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue71.values = data71[:,3]
yValue71.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue71.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat71 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat71.values = data71[:,4]
unc_syst71 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst71.values = data71[:,5]
yValue71.add_uncertainty(unc_stat71)
yValue71.add_uncertainty(unc_syst71)
table71.add_variable(xValue71)
table71.add_variable(yValue71)
submission.add_table(table71)

#####Adding Table 72#####
table72 = Table("data72")
table72.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table72.location = "Data from Figure 5 b"
table72.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table72.keywords["cmenergies"] = ["5.02"]
table72.keywords["observables"] = ["$\chi_{523}$"]
data72 = np.loadtxt("../data_hin17005/fig5_b1.txt", skiprows=0)
xValue72 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue72.values = list(zip(data72[:,0], data72[:,1]))
yValue72 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue72.values = data72[:,3]
yValue72.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue72.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat72 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat72.values = data72[:,4]
unc_syst72 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst72.values = data72[:,5]
yValue72.add_uncertainty(unc_stat72)
yValue72.add_uncertainty(unc_syst72)
table72.add_variable(xValue72)
table72.add_variable(yValue72)
submission.add_table(table72)

#####Adding Table 73#####
table73 = Table("data73")
table73.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table73.location = "Data from Figure 5 c"
table73.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table73.keywords["cmenergies"] = ["5.02"]
table73.keywords["observables"] = ["$\chi_{6222}$"]
data73 = np.loadtxt("../data_hin17005/fig5_c1.txt", skiprows=0)
xValue73 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue73.values = list(zip(data73[:,0], data73[:,1]))
yValue73 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue73.values = data73[:,3]
yValue73.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue73.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat73 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat73.values = data73[:,4]
unc_syst73 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst73.values = data73[:,5]
yValue73.add_uncertainty(unc_stat73)
yValue73.add_uncertainty(unc_syst73)
table73.add_variable(xValue73)
table73.add_variable(yValue73)
submission.add_table(table73)

#####Adding Table 74#####
table74 = Table("data74")
table74.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table74.location = "Data from Figure 5 d"
table74.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table74.keywords["cmenergies"] = ["5.02"]
table74.keywords["observables"] = ["$\chi_{633}$"]
data74 = np.loadtxt("../data_hin17005/fig5_d1.txt", skiprows=0)
xValue74 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue74.values = list(zip(data74[:,0], data74[:,1]))
yValue74 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue74.values = data74[:,3]
yValue74.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue74.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat74 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat74.values = data74[:,4]
unc_syst74 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst74.values = data74[:,5]
yValue74.add_uncertainty(unc_stat74)
yValue74.add_uncertainty(unc_syst74)
table74.add_variable(xValue74)
table74.add_variable(yValue74)
submission.add_table(table74)

#####Adding Table 75#####
table75 = Table("data75")
table75.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table75.location = "Data from Figure 5 e"
table75.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table75.keywords["cmenergies"] = ["5.02"]
table75.keywords["observables"] = ["$\chi_{7223}$"]
data75 = np.loadtxt("../data_hin17005/fig5_e1.txt", skiprows=0)
xValue75 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue75.values = list(zip(data75[:,0], data75[:,1]))
yValue75 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue75.values = data75[:,3]
yValue75.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue75.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat75 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat75.values = data75[:,4]
unc_syst75 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst75.values = data75[:,5]
yValue75.add_uncertainty(unc_stat75)
yValue75.add_uncertainty(unc_syst75)
table75.add_variable(xValue75)
table75.add_variable(yValue75)
submission.add_table(table75)

#####Adding Table 76#####
table76 = Table("data76")
table76.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table76.location = "Data from Figure 5 a2"
table76.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table76.keywords["cmenergies"] = ["2.76"]
table76.keywords["observables"] = ["$\chi_{422}$"]
data76 = np.loadtxt("../data_hin17005/fig5_a2.txt", skiprows=0)
xValue76 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue76.values = list(zip(data76[:,0], data76[:,1]))
yValue76 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue76.values = data76[:,3]
yValue76.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue76.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat76 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat76.values = data76[:,4]
unc_syst76 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst76.values = data76[:,5]
yValue76.add_uncertainty(unc_stat76)
yValue76.add_uncertainty(unc_syst76)
table76.add_variable(xValue76)
table76.add_variable(yValue76)
submission.add_table(table76)

#####Adding Table 77#####
table77 = Table("data77")
table77.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table77.location = "Data from Figure 5 b"
table77.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table77.keywords["cmenergies"] = ["2.76"]
table77.keywords["observables"] = ["$\chi_{523}$"]
data77 = np.loadtxt("../data_hin17005/fig5_b2.txt", skiprows=0)
xValue77 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue77.values = list(zip(data77[:,0], data77[:,1]))
yValue77 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue77.values = data77[:,3]
yValue77.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue77.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat77 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat77.values = data77[:,4]
unc_syst77 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst77.values = data77[:,5]
yValue77.add_uncertainty(unc_stat77)
yValue77.add_uncertainty(unc_syst77)
table77.add_variable(xValue77)
table77.add_variable(yValue77)
submission.add_table(table77)

#####Adding Table 78#####
table78 = Table("data78")
table78.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table78.location = "Data from Figure 5 c"
table78.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table78.keywords["cmenergies"] = ["2.76"]
table78.keywords["observables"] = ["$\chi_{6222}$"]
data78 = np.loadtxt("../data_hin17005/fig5_c2.txt", skiprows=0)
xValue78 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue78.values = list(zip(data78[:,0], data78[:,1]))
yValue78 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue78.values = data78[:,3]
yValue78.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue78.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat78 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat78.values = data78[:,4]
unc_syst78 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst78.values = data78[:,5]
yValue78.add_uncertainty(unc_stat78)
yValue78.add_uncertainty(unc_syst78)
table78.add_variable(xValue78)
table78.add_variable(yValue78)
submission.add_table(table78)

#####Adding Table 79#####
table79 = Table("data79")
table79.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table79.location = "Data from Figure 5 d"
table79.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table79.keywords["cmenergies"] = ["2.76"]
table79.keywords["observables"] = ["$\chi_{633}$"]
data79 = np.loadtxt("../data_hin17005/fig5_d2.txt", skiprows=0)
xValue79 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue79.values = list(zip(data79[:,0], data79[:,1]))
yValue79 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue79.values = data79[:,3]
yValue79.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue79.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat79 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat79.values = data79[:,4]
unc_syst79 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst79.values = data79[:,5]
yValue79.add_uncertainty(unc_stat79)
yValue79.add_uncertainty(unc_syst79)
table79.add_variable(xValue79)
table79.add_variable(yValue79)
submission.add_table(table79)

#####Adding Table 80#####
table80 = Table("data80")
table80.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table80.location = "Data from Figure 5 e"
table80.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table80.keywords["cmenergies"] = ["2.76"]
table80.keywords["observables"] = ["$\chi_{7223}$"]
data80 = np.loadtxt("../data_hin17005/fig5_e2.txt", skiprows=0)
xValue80 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue80.values = list(zip(data80[:,0], data80[:,1]))
yValue80 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue80.values = data80[:,3]
yValue80.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue80.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat80 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat80.values = data80[:,4]
unc_syst80 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst80.values = data80[:,5]
yValue80.add_uncertainty(unc_stat80)
yValue80.add_uncertainty(unc_syst80)
table80.add_variable(xValue80)
table80.add_variable(yValue80)
submission.add_table(table80)

#####Adding Table 81#####
table81 = Table("data81")
table81.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table81.location = "Data from Figure 6 a"
table81.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table81.keywords["cmenergies"] = ["5.02"]
table81.keywords["observables"] = ["$\chi_{422}$"]
data81 = np.loadtxt("../data_hin17005/fig6_a1.txt", skiprows=0)
xValue81 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue81.values = list(zip(data81[:,0], data81[:,1]))
yValue81 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue81.values = data81[:,3]
yValue81.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue81.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat81 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat81.values = data81[:,4]
unc_syst81 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst81.values = data81[:,5]
yValue81.add_uncertainty(unc_stat81)
yValue81.add_uncertainty(unc_syst81)
table81.add_variable(xValue81)
table81.add_variable(yValue81)
submission.add_table(table81)

#####Adding Table 82#####
table82 = Table("data82")
table82.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table82.location = "Data from Figure 6 b"
table82.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table82.keywords["cmenergies"] = ["5.02"]
table82.keywords["observables"] = ["$\chi_{523}$"]
data82 = np.loadtxt("../data_hin17005/fig6_b1.txt", skiprows=0)
xValue82 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue82.values = list(zip(data82[:,0], data82[:,1]))
yValue82 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue82.values = data82[:,3]
yValue82.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue82.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat82 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat82.values = data82[:,4]
unc_syst82 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst82.values = data82[:,5]
yValue82.add_uncertainty(unc_stat82)
yValue82.add_uncertainty(unc_syst82)
table82.add_variable(xValue82)
table82.add_variable(yValue82)
submission.add_table(table82)

#####Adding Table 83#####
table83 = Table("data83")
table83.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table83.location = "Data from Figure 6 c"
table83.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table83.keywords["cmenergies"] = ["5.02"]
table83.keywords["observables"] = ["$\chi_{6222}$"]
data83 = np.loadtxt("../data_hin17005/fig6_c1.txt", skiprows=0)
xValue83 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue83.values = list(zip(data83[:,0], data83[:,1]))
yValue83 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue83.values = data83[:,3]
yValue83.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue83.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat83 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat83.values = data83[:,4]
unc_syst83 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst83.values = data83[:,5]
yValue83.add_uncertainty(unc_stat83)
yValue83.add_uncertainty(unc_syst83)
table83.add_variable(xValue83)
table83.add_variable(yValue83)
submission.add_table(table83)

#####Adding Table 84#####
table84 = Table("data84")
table84.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table84.location = "Data from Figure 6 c"
table84.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table84.keywords["cmenergies"] = ["5.02"]
table84.keywords["observables"] = ["$\chi_{633}$"]
data84 = np.loadtxt("../data_hin17005/fig6_c1.txt", skiprows=0)
xValue84 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue84.values = list(zip(data84[:,0], data84[:,1]))
yValue84 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue84.values = data84[:,3]
yValue84.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue84.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat84 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat84.values = data84[:,4]
unc_syst84 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst84.values = data84[:,5]
yValue84.add_uncertainty(unc_stat84)
yValue84.add_uncertainty(unc_syst84)
table84.add_variable(xValue84)
table84.add_variable(yValue84)
submission.add_table(table84)

#####Adding Table 85#####
table85 = Table("data85")
table85.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 5.02 TeV as a function of centrality."
table85.location = "Data from Figure 6 e"
table85.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table85.keywords["cmenergies"] = ["5.02"]
table85.keywords["observables"] = ["$\chi_{7223}$"]
data85 = np.loadtxt("../data_hin17005/fig6_e1.txt", skiprows=0)
xValue85 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue85.values = list(zip(data85[:,0], data85[:,1]))
yValue85 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue85.values = data85[:,3]
yValue85.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue85.add_qualifier("SQRT(S)/NUCLEON", 5.02, "TeV")
unc_stat85 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat85.values = data85[:,4]
unc_syst85 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst85.values = data85[:,5]
yValue85.add_uncertainty(unc_stat85)
yValue85.add_uncertainty(unc_syst85)
table85.add_variable(xValue85)
table85.add_variable(yValue85)
submission.add_table(table85)

#####Adding Table 86#####
table86 = Table("data86")
table86.description = "Nonlinear response coefficient $\chi_{422}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table86.location = "Data from Figure 6 a"
table86.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table86.keywords["cmenergies"] = ["2.76"]
table86.keywords["observables"] = ["$\chi_{422}$"]
data86 = np.loadtxt("../data_hin17005/fig6_a2.txt", skiprows=0)
xValue86 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue86.values = list(zip(data86[:,0], data86[:,1]))
yValue86 = Variable("$\chi_{422}$", is_independent=False, is_binned=False, units="")
yValue86.values = data86[:,3]
yValue86.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue86.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat86 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat86.values = data86[:,4]
unc_syst86 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst86.values = data86[:,5]
yValue86.add_uncertainty(unc_stat86)
yValue86.add_uncertainty(unc_syst86)
table86.add_variable(xValue86)
table86.add_variable(yValue86)
submission.add_table(table86)

#####Adding Table 87#####
table87 = Table("data87")
table87.description = "Nonlinear response coefficient $\chi_{523}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table87.location = "Data from Figure 6 b"
table87.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table87.keywords["cmenergies"] = ["2.76"]
table87.keywords["observables"] = ["$\chi_{523}$"]
data87 = np.loadtxt("../data_hin17005/fig6_b2.txt", skiprows=0)
xValue87 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue87.values = list(zip(data87[:,0], data87[:,1]))
yValue87 = Variable("$\chi_{523}$", is_independent=False, is_binned=False, units="")
yValue87.values = data87[:,3]
yValue87.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue87.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat87 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat87.values = data87[:,4]
unc_syst87 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst87.values = data87[:,5]
yValue87.add_uncertainty(unc_stat87)
yValue87.add_uncertainty(unc_syst87)
table87.add_variable(xValue87)
table87.add_variable(yValue87)
submission.add_table(table87)

#####Adding Table 88#####
table88 = Table("data88")
table88.description = "Nonlinear response coefficient $\chi_{6222}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table88.location = "Data from Figure 6 c"
table88.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table88.keywords["cmenergies"] = ["2.76"]
table88.keywords["observables"] = ["$\chi_{6222}$"]
data88 = np.loadtxt("../data_hin17005/fig6_c2.txt", skiprows=0)
xValue88 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue88.values = list(zip(data88[:,0], data88[:,1]))
yValue88 = Variable("$\chi_{6222}$", is_independent=False, is_binned=False, units="")
yValue88.values = data88[:,3]
yValue88.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue88.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat88 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat88.values = data88[:,4]
unc_syst88 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst88.values = data88[:,5]
yValue88.add_uncertainty(unc_stat88)
yValue88.add_uncertainty(unc_syst88)
table88.add_variable(xValue88)
table88.add_variable(yValue88)
submission.add_table(table88)

#####Adding Table 89#####
table89 = Table("data89")
table89.description = "Nonlinear response coefficient $\chi_{633}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table89.location = "Data from Figure 6 d"
table89.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table89.keywords["cmenergies"] = ["2.76"]
table89.keywords["observables"] = ["$\chi_{633}$"]
data89 = np.loadtxt("../data_hin17005/fig6_d2.txt", skiprows=0)
xValue89 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue89.values = list(zip(data89[:,0], data89[:,1]))
yValue89 = Variable("$\chi_{633}$", is_independent=False, is_binned=False, units="")
yValue89.values = data89[:,3]
yValue89.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue89.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat89 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat89.values = data89[:,4]
unc_syst89 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst89.values = data89[:,5]
yValue89.add_uncertainty(unc_stat89)
yValue89.add_uncertainty(unc_syst89)
table89.add_variable(xValue89)
table89.add_variable(yValue89)
submission.add_table(table89)

#####Adding Table 90#####
table90 = Table("data90")
table90.description = "Nonlinear response coefficient $\chi_{7223}$ from the scalar-product method at 2.76 TeV as a function of centrality."
table90.location = "Data from Figure 6 e"
table90.keywords["reactions"] = ["Pb Pb --> CHARGED X"]
table90.keywords["cmenergies"] = ["2.76"]
table90.keywords["observables"] = ["$\chi_{7223}$"]
data90 = np.loadtxt("../data_hin17005/fig6_e2.txt", skiprows=0)
xValue90 = Variable("Centrality", is_independent=True, is_binned=True, units="%")
xValue90.values = list(zip(data90[:,0], data90[:,1]))
yValue90 = Variable("$\chi_{7223}$", is_independent=False, is_binned=False, units="")
yValue90.values = data90[:,3]
yValue90.add_qualifier("RE", "Pb Pb --> CHARGED X")
yValue90.add_qualifier("SQRT(S)/NUCLEON", 2.76, "TeV")
unc_stat90 = Uncertainty("Statistical uncertainty", is_symmetric=True)
unc_stat90.values = data90[:,4]
unc_syst90 = Uncertainty("Systematic uncertainty", is_symmetric=True)
unc_syst90.values = data90[:,5]
yValue90.add_uncertainty(unc_stat90)
yValue90.add_uncertainty(unc_syst90)
table90.add_variable(xValue90)
table90.add_variable(yValue90)
submission.add_table(table90)



#Adding Output
outdir = "hin17005hepdata_output"
submission.create_files(outdir)


