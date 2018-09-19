{
 
/*
 root -l Dateiname.root

 und dann dein macro ausführen:

 .x macro.C

 */
 
 
X_vs_Y->SetXTitle("x from MCFD (cm)");
X_vs_Y->SetYTitle("y from MCFD (cm)");
X_vs_Y->SetTitle("Position from MCFD");
X1_vs_Y1->GetXaxis()->SetRangeUser(-5,5); 
X1_vs_Y1->GetYaxis()->SetRangeUser(-5,5);  
X1_vs_Y1->SetXTitle("x1 from MCFD (cm)");
X1_vs_Y1->SetYTitle("y1 from MCFD (cm)");
X1_vs_Y1->SetTitle("Position from MCFD");
X1_vs_Y1->GetXaxis()->SetRangeUser(-5,5); 
X1_vs_Y1->GetYaxis()->SetRangeUser(-5,5);  
X2_vs_Y2->SetXTitle("x2 from MCFD (cm)");
X2_vs_Y2->SetYTitle("y2 from MCFD (cm)");
X2_vs_Y2->SetTitle("Position from MCFD");
X2_vs_Y2->GetXaxis()->SetRangeUser(-5,5); 
X2_vs_Y2->GetYaxis()->SetRangeUser(-5,5);  

X_vs_Y_ToT->SetXTitle("x from ToT / cm");
X_vs_Y_ToT->SetYTitle("y from ToT / cm");
X_vs_Y_ToT->SetTitle("Position from ToT");
X_vs_Y_ToT->GetXaxis()->SetRangeUser(-5,5); 
X_vs_Y_ToT->GetYaxis()->SetRangeUser(-5,5);  
X1_vs_Y1_ToT->SetXTitle("x1 from ToT / cm");
X1_vs_Y1_ToT->SetYTitle("y1 from ToT / cm");
X1_vs_Y1_ToT->SetTitle("Position from ToT");
X1_vs_Y1_ToT->GetXaxis()->SetRangeUser(-5,5); 
X1_vs_Y1_ToT->GetYaxis()->SetRangeUser(-5,5);  
X2_vs_Y2_ToT->SetXTitle("x2 from ToT / cm");
X2_vs_Y2_ToT->GetXaxis()->SetRangeUser(-5,5); 
X2_vs_Y2_ToT->GetYaxis()->SetRangeUser(-5,5);  
X2_vs_Y2_ToT->SetYTitle("y2 from ToT / cm");
X2_vs_Y2_ToT->SetTitle("Position from ToT");


X_vs_Y_TAMEX->SetXTitle("x from TAMEX / cm");
X_vs_Y_TAMEX->SetYTitle("y from TAMEX / cm");
X_vs_Y_TAMEX->SetTitle("Position from TAMEX");
X_vs_Y_TAMEX->GetXaxis()->SetRangeUser(-5,5); 
X_vs_Y_TAMEX->GetYaxis()->SetRangeUser(-5,5);  
X1_vs_Y1_TAMEX->SetXTitle("x1 from TAMEX / cm");
X1_vs_Y1_TAMEX->SetYTitle("y1 from TAMEX / cm");
X1_vs_Y1_TAMEX->SetTitle("Position from TAMEX");
X1_vs_Y1_TAMEX->GetXaxis()->SetRangeUser(-5,5); 
X1_vs_Y1_TAMEX->GetYaxis()->SetRangeUser(-5,5);  
X2_vs_Y2_TAMEX->SetXTitle("x2 from TAMEX / cm");
X2_vs_Y2_TAMEX->GetXaxis()->SetRangeUser(-5,5); 
X2_vs_Y2_TAMEX->GetYaxis()->SetRangeUser(-5,5);  
X2_vs_Y2_TAMEX->SetYTitle("y2 from TAMEX / cm");
X2_vs_Y2_TAMEX->SetTitle("Position from TAMEX");

X2_vs_Y2_proj->SetXTitle("x (cm)");
X2_vs_Y2_proj->SetYTitle("y  (cm)");
X2_vs_Y2_proj->SetTitle("Average of ToT, MCFD and Tamex");

X_vs_Y_mean->SetXTitle("x (cm)");
X_vs_Y_mean->SetYTitle("y (cm)");
X_vs_Y_mean->SetTitle("Average of MCFD and ToT");
X_vs_Y_mean->GetXaxis()->SetRangeUser(-5,5); 
X_vs_Y_mean->GetYaxis()->SetRangeUser(-5,5); 

X_vs_Y_ToT_corr->SetXTitle("x (cm)");
X_vs_Y_ToT_corr->SetYTitle("y (cm)");
X_vs_Y_ToT_corr->SetTitle("ToT corrected"); 
X_vs_Y_ToT_corr->GetXaxis()->SetRangeUser(-5,5); 
X_vs_Y_ToT_corr->GetYaxis()->SetRangeUser(-5,5); 

X1_vs_Y1_ToT_corr->SetXTitle("x1 (cm)");
X1_vs_Y1_ToT_corr->SetYTitle("y1 (cm)");
X1_vs_Y1_ToT_corr->SetTitle("ToT corrected"); 
X1_vs_Y1_ToT_corr->GetXaxis()->SetRangeUser(-5,5); 
X1_vs_Y1_ToT_corr->GetYaxis()->SetRangeUser(-5,5); 

X2_vs_Y2_ToT_corr->SetXTitle("x2 (cm)");
X2_vs_Y2_ToT_corr->SetYTitle("y2 (cm)");
X2_vs_Y2_ToT_corr->SetTitle("ToT corrected"); 
X2_vs_Y2_ToT_corr->GetXaxis()->SetRangeUser(-5,5); 
X2_vs_Y2_ToT_corr->GetYaxis()->SetRangeUser(-5,5); 

X_vs_Y_wc->SetXTitle("x from MCFD (cm)");
X_vs_Y_wc->SetYTitle("y from MCFD (cm)");
X_vs_Y_wc->SetTitle("Position from MCFD walk corrected");
X_vs_Y_wc->GetXaxis()->SetRangeUser(-5,5); 
X_vs_Y_wc->GetYaxis()->SetRangeUser(-5,5);   
X1_vs_Y1_wc->SetXTitle("x1 (cm)");
X1_vs_Y1_wc->SetYTitle("y1  (cm)");
X1_vs_Y1_wc->SetTitle("x1,y1 walk corrected"); 
X1_vs_Y1_wc->GetXaxis()->SetRangeUser(-5,5); 
X1_vs_Y1_wc->GetYaxis()->SetRangeUser(-5,5);  
X2_vs_Y2_wc->SetXTitle("x2  (cm)");
X2_vs_Y2_wc->SetYTitle("y2 (cm)");
X2_vs_Y2_wc->SetTitle("x2,y2 walk corrected"); 
X2_vs_Y2_wc->GetXaxis()->SetRangeUser(-5,5); 
X2_vs_Y2_wc->GetYaxis()->SetRangeUser(-5,5);  

LOS_dt_MCFD->SetXTitle("t (ns)");
LOS_dt_MCFD->SetYTitle("Counts");
LOS_dt_MCFD->SetTitle("Time resolution MCFD");

LOS_dt_MCFD_oddCh->SetXTitle("t (ns)");
LOS_dt_MCFD_oddCh->SetYTitle("Counts");
LOS_dt_MCFD_oddCh->SetTitle("Time resolution MCFD odd channels");

LOS_dt_MCFD_evenCh->SetXTitle("t (ns)");
LOS_dt_MCFD_evenCh->SetYTitle("Counts");
LOS_dt_MCFD_evenCh->SetTitle("Time resolution MCFD even channels");

LOS_dt_MCFD_wc->SetXTitle("t (ns)");
LOS_dt_MCFD_wc->SetYTitle("Counts");
LOS_dt_MCFD_wc->SetTitle("Time resolution MCFD walk corrected");

LOS_dt_MCFD_oddCh_wc->SetXTitle("t (ns)");
LOS_dt_MCFD_oddCh_wc->SetYTitle("Counts");
LOS_dt_MCFD_oddCh_wc->SetTitle("Time resolution MCFD walk corr odd channels");

LOS_dt_MCFD_evenCh_wc->SetXTitle("t (ns)");
LOS_dt_MCFD_evenCh_wc->SetYTitle("Counts");
LOS_dt_MCFD_evenCh_wc->SetTitle("Time resolution MCFD walk corr even channels");

LOS_dt_TAMEX->SetXTitle("t (ns)");
LOS_dt_TAMEX->SetYTitle("Counts");
LOS_dt_TAMEX->SetTitle("Time resolution TAMEX");

LOS_dt_TAMEX_wc->SetXTitle("t (ns)");
LOS_dt_TAMEX_wc->SetYTitle("Counts");
LOS_dt_TAMEX_wc->SetTitle("Time resolution TAMEX walk corrected");

LOS_dt_TAMEX_evenCh->SetXTitle("t (ns)");
LOS_dt_TAMEX_evenCh->SetYTitle("Counts");
LOS_dt_TAMEX_evenCh->SetTitle("Time resolution TAMEX even channels");

LOS_dt_TAMEX_evenCh_wc->SetXTitle("t (ns)");
LOS_dt_TAMEX_evenCh_wc->SetYTitle("Counts");
LOS_dt_TAMEX_evenCh_wc->SetTitle("Time resolution TAMEX walk corr eveb channels");

LOS_dt_TAMEX_oddCh->SetXTitle("t (ns)");
LOS_dt_TAMEX_oddCh->SetYTitle("Counts");
LOS_dt_TAMEX_oddCh->SetTitle("Time resolution TAMEX odd channels");

LOS_dt_TAMEX_oddCh_wc->SetXTitle("t (ns)");
LOS_dt_TAMEX_oddCh_wc->SetYTitle("Counts");
LOS_dt_TAMEX_oddCh_wc->SetTitle("Time resolution TAMEX walk corr odd channels");

LOS_dt_MCFD_TAMEX_wc->SetXTitle("t (ns)");
LOS_dt_MCFD_TAMEX_wc->SetYTitle("Counts");
LOS_dt_MCFD_TAMEX_wc->SetTitle("Time resolution <MCFD+TAMEX> walk corrected");

TMCFD_vs_Q->SetXTitle("LOS charge (arb. u.)");
TMCFD_vs_Q->SetYTitle("t (ns)");
TMCFD_vs_Q->SetTitle("MCFD time vs charge");

TMCFD_vs_Q_wc->SetXTitle("LOS charge (arb. u.)");
TMCFD_vs_Q_wc->SetYTitle("t (ns)");
TMCFD_vs_Q_wc->SetTitle("MCFD walk-corrected time vs charge");

TTAMEX_vs_Q->SetXTitle("LOS charge (arb. u.)");
TTAMEX_vs_Q->SetYTitle("t (ns)");
TTAMEX_vs_Q->SetTitle("TAMEX time vs charge");

TTAMEX_vs_Q_wc->SetXTitle("LOS charge (arb. u.)");
TTAMEX_vs_Q_wc->SetYTitle("t (ns)");
TTAMEX_vs_Q_wc->SetTitle("TAMEX walk-corrected time vs charge");

Tres_vs_X_MCFD->SetXTitle("X / cm");
Tres_vs_X_MCFD->SetYTitle(" Tres (ns)");
Tres_vs_X_MCFD->SetTitle("MCFD");

Tres_vs_Y_MCFD->SetXTitle("Y / cm");
Tres_vs_Y_MCFD->SetYTitle(" Tres (ns)");
Tres_vs_Y_MCFD->SetTitle("MCFD");

Tres_vs_X_MCFD_wc->SetXTitle("X / cm");
Tres_vs_X_MCFD_wc->SetYTitle(" Tres (ns)");
Tres_vs_X_MCFD_wc->SetTitle("MCFD walk corrected");

Tres_vs_Y_MCFD_wc->SetXTitle("Y / cm");
Tres_vs_Y_MCFD_wc->SetYTitle(" Tres (ns)");
Tres_vs_Y_MCFD_wc->SetTitle("MCFD walk corrected");

Tres_vs_X_TAMEX->SetXTitle("X / cm");
Tres_vs_X_TAMEX->SetYTitle(" Tres (ns)");
Tres_vs_X_TAMEX->SetTitle("TAMEX");

Tres_vs_Y_TAMEX->SetXTitle("Y / cm");
Tres_vs_Y_TAMEX->SetYTitle(" Tres (ns)");
Tres_vs_Y_TAMEX->SetTitle("TAMEX");

Tres_vs_X_TAMEX_wc->SetXTitle("X / cm");
Tres_vs_X_TAMEX_wc->SetYTitle(" Tres (ns)");
Tres_vs_X_TAMEX_wc->SetTitle("TAMEX walk corrected");

Tres_vs_Y_TAMEX_wc->SetXTitle("Y / cm");
Tres_vs_Y_TAMEX_wc->SetYTitle(" Tres (ns)");
Tres_vs_Y_TAMEX_wc->SetTitle("TAMEX walk corrected");

LOS_Q->SetXTitle("LOS charge (arb. u.)");
LOS_Q->SetYTitle("Counts");
LOS_Q->SetTitle("ToT mean");

LOS_Q_test->SetXTitle("LOS charge (arb. u.)");
LOS_Q_test->SetYTitle("Counts");
LOS_Q_test->SetTitle("ToT corrected");

LOS_Q_oddCh->SetXTitle("LOS charge of odd channels (arb. u.)");
LOS_Q_oddCh->SetYTitle("Counts");
LOS_Q_oddCh->SetTitle("Mean ToT of odd channels");

LOS_Q_evenCh->SetXTitle("LOS charge of even channels (arb. u.)");
LOS_Q_evenCh->SetYTitle("Counts");
LOS_Q_evenCh->SetTitle("Corrected mean ToT of even channels");

LOS_Q_evenCh_corr->SetXTitle("LOS charge of even channels (arb. u.)");
LOS_Q_evenCh_corr->SetYTitle("Counts");
LOS_Q_evenCh_corr->SetTitle("Corrected mean ToT of even channels");

LOS_Q_oddCh_corr->SetXTitle("LOS charge of odd channels (arb. u.)");
LOS_Q_oddCh_corr->SetYTitle("Counts");
LOS_Q_oddCh_corr->SetTitle("Corrected mean ToT of even channels");


LOS_QL_vs_X1->SetXTitle("x / cm");
LOS_QL_vs_X1->SetYTitle("LOS charge (arb. u.)");
LOS_QL_vs_X1->SetTitle("Ch. 2 Time-over-threshold");

LOS_QB_vs_Y1->SetXTitle("y / cm");
LOS_QB_vs_Y1->SetYTitle("LOS charge (arb. u.)");
LOS_QB_vs_Y1->SetTitle("Ch. 4 Time-over-threshold");

LOS_QR_vs_X1->SetXTitle("x / cm");
LOS_QR_vs_X1->SetYTitle("LOS charge (arb. u.)");
LOS_QR_vs_X1->SetTitle("Ch. 6 Time-over-threshold");

LOS_QT_vs_Y1->SetXTitle("y / cm");
LOS_QT_vs_Y1->SetYTitle("LOS charge (arb. u.)");
LOS_QT_vs_Y1->SetTitle("Ch. 8 Time-over-threshold");

LOS_QLT_vs_X2->SetXTitle("x / cm");
LOS_QLT_vs_X2->SetYTitle("LOS charge (arb. u.)");
LOS_QLT_vs_X2->SetTitle("Ch. 1 Time-over-threshold");

LOS_QLB_vs_Y2->SetXTitle("y / cm");
LOS_QLB_vs_Y2->SetYTitle("LOS charge (arb. u.)");
LOS_QLB_vs_Y2->SetTitle("Ch. 3 Time-over-threshold");

LOS_QRB_vs_X2->SetXTitle("x / cm");
LOS_QRB_vs_X2->SetYTitle("LOS charge (arb. u.)");
LOS_QRB_vs_X2->SetTitle("Ch. 5 Time-over-threshold");

LOS_QRT_vs_Y2->SetXTitle("y / cm");
LOS_QRT_vs_Y2->SetYTitle("LOS charge (arb. u.)");
LOS_QRT_vs_Y2->SetTitle("Ch. 7 Time-over-threshold");

LOS_QL_vs_X1_corr->SetXTitle("R / cm");
LOS_QL_vs_X1_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QL_vs_X1_corr->SetTitle("Ch. 3 ToT corrected");

LOS_QB_vs_Y1_corr->SetXTitle("R / cm");
LOS_QB_vs_Y1_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QB_vs_Y1_corr->SetTitle("Ch. 5 ToT corrected");

LOS_QR_vs_X1_corr->SetXTitle("R / cm");
LOS_QR_vs_X1_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QR_vs_X1_corr->SetTitle("Ch. 7 ToT corrected");

LOS_QT_vs_Y1_corr->SetXTitle("R / cm");
LOS_QT_vs_Y1_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QT_vs_Y1_corr->SetTitle("Ch. 1 ToT corrected");

LOS_QLT_vs_X2_corr->SetXTitle("R / cm");
LOS_QLT_vs_X2_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QLT_vs_X2_corr->SetTitle("Ch. 2 ToT corrected");

LOS_QLB_vs_Y2_corr->SetXTitle("R / cm");
LOS_QLB_vs_Y2_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QLB_vs_Y2_corr->SetTitle("Ch. 4 ToT corrected");

LOS_QRB_vs_X2_corr->SetXTitle("R / cm");
LOS_QRB_vs_X2_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QRB_vs_X2_corr->SetTitle("Ch. 6 ToT corrected");

LOS_QRT_vs_Y2_corr->SetXTitle("R / cm");
LOS_QRT_vs_Y2_corr->SetYTitle("LOS charge (arb. u.)");
LOS_QRT_vs_Y2_corr->SetTitle("Ch. 8 ToT corrected");


t1_vs_Q1_M_wc->SetXTitle("ToT / ns");
t1_vs_Q1_M_wc->SetYTitle("Time / ns");
t1_vs_Q1_M_wc->SetTitle("Ch.1 walk corrected MCFD");
t1_vs_Q1_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t1_vs_Q1_M->SetXTitle("ToT / ns");
t1_vs_Q1_M->SetYTitle("Time / ns");
t1_vs_Q1_M->SetTitle("Ch.1 MCFD");

t2_vs_Q2_M_wc->SetXTitle("ToT / ns");
t2_vs_Q2_M_wc->SetYTitle("Time / ns");
t2_vs_Q2_M_wc->SetTitle("Ch.2 walk corrected MCFD");
t2_vs_Q2_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t2_vs_Q2_M->SetXTitle("ToT / ns");
t2_vs_Q2_M->SetYTitle("Time / ns");
t2_vs_Q2_M->SetTitle("Ch.2 MCFD");

t3_vs_Q3_M_wc->SetXTitle("ToT / ns");
t3_vs_Q3_M_wc->SetYTitle("Time / ns");
t3_vs_Q3_M_wc->SetTitle("Ch.3 walk corrected MCFD");
t3_vs_Q3_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t3_vs_Q3_M->SetXTitle("ToT / ns");
t3_vs_Q3_M->SetYTitle("Time / ns");
t3_vs_Q3_M->SetTitle("Ch.3 MCFD");

t4_vs_Q4_M_wc->SetXTitle("ToT / ns");
t4_vs_Q4_M_wc->SetYTitle("Time / ns");
t4_vs_Q4_M_wc->SetTitle("Ch.4 walk corrected MCFD");
t4_vs_Q4_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t4_vs_Q4_M->SetXTitle("ToT / ns");
t4_vs_Q4_M->SetYTitle("Time / ns");
t4_vs_Q4_M->SetTitle("Ch.4 MCFD");

t5_vs_Q5_M_wc->SetXTitle("ToT / ns");
t5_vs_Q5_M_wc->SetYTitle("Time / ns");
t5_vs_Q5_M_wc->SetTitle("Ch.5 walk corrected MCFD");
t5_vs_Q5_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t5_vs_Q5_M->SetXTitle("ToT / ns");
t5_vs_Q5_M->SetYTitle("Time / ns");
t5_vs_Q5_M->SetTitle("Ch.5 MCFD");

t6_vs_Q6_M_wc->SetXTitle("ToT / ns");
t6_vs_Q6_M_wc->SetYTitle("Time / ns");
t6_vs_Q6_M_wc->SetTitle("Ch.6 walk corrected MCFD");
t6_vs_Q6_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t6_vs_Q6_M->SetXTitle("ToT / ns");
t6_vs_Q6_M->SetYTitle("Time / ns");
t6_vs_Q6_M->SetTitle("Ch.6 MCFD");

t7_vs_Q7_M_wc->SetXTitle("ToT / ns");
t7_vs_Q7_M_wc->SetYTitle("Time / ns");
t7_vs_Q7_M_wc->SetTitle("Ch.7 walk corrected MCFD");
t7_vs_Q7_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t7_vs_Q7_M->SetXTitle("ToT / ns");
t7_vs_Q7_M->SetYTitle("Time / ns");
t7_vs_Q7_M->SetTitle("Ch.7 MCFD");

t8_vs_Q8_M_wc->SetXTitle("ToT / ns");
t8_vs_Q8_M_wc->SetYTitle("Time / ns");
t8_vs_Q8_M_wc->SetTitle("Ch.8 walk corrected MCFD");
t8_vs_Q8_M_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t8_vs_Q8_M->SetXTitle("ToT / ns");
t8_vs_Q8_M->SetYTitle("Time / ns");
t8_vs_Q8_M->SetTitle("Ch.8 MCFD");

t1_vs_Q1_T_wc->SetXTitle("ToT / ns");
t1_vs_Q1_T_wc->SetYTitle("Time / ns");
t1_vs_Q1_T_wc->SetTitle("Ch.1 walk corrected TAMEX");
t1_vs_Q1_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5); 
t1_vs_Q1_T->SetXTitle("ToT / ns");
t1_vs_Q1_T->SetYTitle("Time / ns");
t1_vs_Q1_T->SetTitle("Ch.1 TAMEX");

t2_vs_Q2_T_wc->SetXTitle("ToT / ns");
t2_vs_Q2_T_wc->SetYTitle("Time / ns");
t2_vs_Q2_T_wc->SetTitle("Ch.2 walk corrected TAMEX");
t2_vs_Q2_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t2_vs_Q2_T->SetXTitle("ToT / ns");
t2_vs_Q2_T->SetYTitle("Time / ns");
t2_vs_Q2_T->SetTitle("Ch.2 TAMEX");

t3_vs_Q3_T_wc->SetXTitle("ToT / ns");
t3_vs_Q3_T_wc->SetYTitle("Time / ns");
t3_vs_Q3_T_wc->SetTitle("Ch.3 walk corrected TAMEX");
t3_vs_Q3_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t3_vs_Q3_T->SetXTitle("ToT / ns");
t3_vs_Q3_T->SetYTitle("Time / ns");
t3_vs_Q3_T->SetTitle("Ch.3 TAMEX");

t4_vs_Q4_T_wc->SetXTitle("ToT / ns");
t4_vs_Q4_T_wc->SetYTitle("Time / ns");
t4_vs_Q4_T_wc->SetTitle("Ch.4 walk corrected TAMEX");
t4_vs_Q4_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t4_vs_Q4_T->SetXTitle("ToT / ns");
t4_vs_Q4_T->SetYTitle("Time / ns");
t4_vs_Q4_T->SetTitle("Ch.4 TAMEX");

t5_vs_Q5_T_wc->SetXTitle("ToT / ns");
t5_vs_Q5_T_wc->SetYTitle("Time / ns");
t5_vs_Q5_T_wc->SetTitle("Ch.5 walk corrected TAMEX");
t5_vs_Q5_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t5_vs_Q5_T->SetXTitle("ToT / ns");
t5_vs_Q5_T->SetYTitle("Time / ns");
t5_vs_Q5_T->SetTitle("Ch.5 TAMEX");

t6_vs_Q6_T_wc->SetXTitle("ToT / ns");
t6_vs_Q6_T_wc->SetYTitle("Time / ns");
t6_vs_Q6_T_wc->SetTitle("Ch.6 walk corrected TAMEX");
t6_vs_Q6_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t6_vs_Q6_T->SetXTitle("ToT / ns");
t6_vs_Q6_T->SetYTitle("Time / ns");
t6_vs_Q6_T->SetTitle("Ch.6 TAMEX");

t7_vs_Q7_T_wc->SetXTitle("ToT / ns");
t7_vs_Q7_T_wc->SetYTitle("Time / ns");
t7_vs_Q7_T_wc->SetTitle("Ch.7 walk corrected TAMEX");
t7_vs_Q7_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t7_vs_Q7_T->SetXTitle("ToT / ns");
t7_vs_Q7_T->SetYTitle("Time / ns");
t7_vs_Q7_T->SetTitle("Ch.7 TAMEX");

t8_vs_Q8_T_wc->SetXTitle("ToT / ns");
t8_vs_Q8_T_wc->SetYTitle("Time / ns");
t8_vs_Q8_T_wc->SetTitle("Ch.3 walk corrected TAMEX");
t8_vs_Q8_T_wc->GetYaxis()->SetRangeUser(-0.5,0.5);
t8_vs_Q8_T->SetXTitle("ToT / ns");
t8_vs_Q8_T->SetYTitle("Time / ns");
t8_vs_Q8_T->SetTitle("Ch.8 TAMEX");

QPM1_vs_QPM5->SetXTitle("ToT PM1 / ns");
QPM1_vs_QPM5->SetYTitle("ToT PM5 / ns");
QPM1_vs_QPM5->SetTitle("Q1 vs Q5");
QPM1_vs_QPM5_corr->SetXTitle("ToT PM1 / ns");
QPM1_vs_QPM5_corr->SetYTitle("ToT PM5 / ns");
QPM1_vs_QPM5_corr->SetTitle("Q1 vs Q5 corrected");

QPM2_vs_QPM6->SetXTitle("ToT PM2 / ns");
QPM2_vs_QPM6->SetYTitle("ToT PM6 / ns");
QPM2_vs_QPM6->SetTitle("Q2 vs Q6");
QPM2_vs_QPM6_corr->SetXTitle("ToT PM2 / ns");
QPM2_vs_QPM6_corr->SetYTitle("ToT PM6 / ns");
QPM2_vs_QPM6_corr->SetTitle("Q2 vs Q6 corrected");

QPM4_vs_QPM8->SetXTitle("ToT PM4 / ns");
QPM4_vs_QPM8->SetYTitle("ToT PM8 / ns");
QPM4_vs_QPM8->SetTitle("Q4 vs Q8");
QPM4_vs_QPM8_corr->SetXTitle("ToT PM4 / ns");
QPM4_vs_QPM8_corr->SetYTitle("ToT PM8 / ns");
QPM4_vs_QPM8_corr->SetTitle("Q4 vs Q8 corrected");

QPM3_vs_QPM7->SetXTitle("ToT PM3 / ns");
QPM3_vs_QPM7->SetYTitle("ToT PM7 / ns");
QPM3_vs_QPM7->SetTitle("Q3 vs Q7");
QPM3_vs_QPM7_corr->SetXTitle("ToT PM3 / ns");
QPM3_vs_QPM7_corr->SetYTitle("ToT PM7 / ns");
QPM3_vs_QPM7_corr->SetTitle("Q3 vs Q7 corrected");

Q1_vs_Icount->SetXTitle("Event number");
Q1_vs_Icount->SetYTitle("ToT PM1 / ns");
Q1_vs_Icount->SetTitle("ToT vs event number Ch.1");

Q3_vs_Icount->SetXTitle("Event number");
Q3_vs_Icount->SetYTitle("ToT PM3 / ns");
Q3_vs_Icount->SetTitle("ToT vs event number Ch.3");

Q5_vs_Icount->SetXTitle("Event number");
Q5_vs_Icount->SetYTitle("ToT PM5 / ns");
Q5_vs_Icount->SetTitle("ToT vs event number Ch.5");

Q7_vs_Icount->SetXTitle("Event number");
Q7_vs_Icount->SetYTitle("ToT PM7 / ns");
Q7_vs_Icount->SetTitle("ToT vs event number Ch.7");

Q2_vs_Icount->SetXTitle("Event number");
Q2_vs_Icount->SetYTitle("ToT PM2 / ns");
Q2_vs_Icount->SetTitle("ToT vs event number Ch.2");

Q4_vs_Icount->SetXTitle("Event number");
Q4_vs_Icount->SetYTitle("ToT PM4 / ns");
Q4_vs_Icount->SetTitle("ToT vs event number Ch.4");

Q6_vs_Icount->SetXTitle("Event number");
Q6_vs_Icount->SetYTitle("ToT PM6 / ns");
Q6_vs_Icount->SetTitle("ToT vs event number Ch.6");

Q8_vs_Icount->SetXTitle("Event number");
Q8_vs_Icount->SetYTitle("ToT PM8 / ns");
Q8_vs_Icount->SetTitle("ToT vs event number Ch.8");

RaumWinkel->SetXTitle("Angle / deg");

TresM_vs_Icount->SetXTitle("Event number");
TresM_vs_Icount->SetYTitle("Time Resolution / ns");
TresM_vs_Icount->SetTitle("MCFD");

TreswcM_vs_Icount->SetXTitle("Event number");
TreswcM_vs_Icount->SetYTitle("Time Resolution / ns");
TreswcM_vs_Icount->SetTitle("MCFD Walk corrected");

TresT_vs_Icount->SetXTitle("Event number");
TresT_vs_Icount->SetYTitle("Time Resolution / ns");
TresT_vs_Icount->SetTitle("TAMEX");

TreswcT_vs_Icount->SetXTitle("Event number");
TreswcT_vs_Icount->SetYTitle("Time Resolution / ns");
TreswcT_vs_Icount->SetTitle("TAMEX Walk corrected");

Q_vs_X->SetYTitle("ToT (ns)");
Q_vs_X->SetXTitle("x (cm)");
Q_vs_X->SetTitle("ToT vs X");

Qcorr_vs_X->SetYTitle("ToT (ns)");
Qcorr_vs_X->SetXTitle("x (cm)");
Qcorr_vs_X->SetTitle("Corrected ToT vs X");

Q_vs_Y->SetYTitle("ToT (ns)");
Q_vs_Y->SetXTitle("y (cm)");
Q_vs_Y->SetTitle("ToT vs Y");

Qcorr_vs_Y->SetYTitle("ToT (ns)");
Qcorr_vs_Y->SetXTitle("y f (cm)");
Qcorr_vs_Y->SetTitle("Corrected ToT vs Y");


/* One can also use:
 * histo->SetAxisRange(a,b,"X");
 * histo->SetAxisRange(c,d,"Y");
 */
 
TCanvas *c2 = new TCanvas("c2","LOS Times",0,0,850,950);
c2->Clear();
c2->Divide(3,4);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   /* X position */
gStyle->SetStatY(0.99);   /* Y position */
gStyle->SetStatW(0.25);  /* Width of the box */
gStyle->SetStatH(0.3);  /* hight of the bos */
c2->cd(1);
LOS_dt_MCFD->Draw();
c2->cd(2);
LOS_dt_MCFD_oddCh->Draw();
c2->cd(3);
LOS_dt_MCFD_evenCh->Draw();
c2->cd(4);
LOS_dt_TAMEX->Draw();
c2->cd(5);
LOS_dt_TAMEX_oddCh->Draw();
c2->cd(6);
LOS_dt_TAMEX_evenCh->Draw();
c2->cd(7);gPad->SetLogz();
TMCFD_vs_Q->Draw("colz");
c2->cd(8); gPad->SetLogz();
Tres_vs_X_MCFD->Draw("colz");
c2->cd(9); gPad->SetLogz();
Tres_vs_Y_MCFD->Draw("colz");
c2->cd(10);gPad->SetLogz();
TTAMEX_vs_Q->Draw("colz");
c2->cd(11); gPad->SetLogz();
Tres_vs_X_TAMEX->Draw("colz");
c2->cd(12); gPad->SetLogz();
Tres_vs_Y_TAMEX->Draw("colz");

TCanvas *c5 = new TCanvas("c5","LOS Times walk corrected",0,0,850,950);
c5->Clear();
c5->Divide(3,5);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   /* X position */
gStyle->SetStatY(0.99);   /* Y position */
gStyle->SetStatW(0.25);  /* Width of the box */
gStyle->SetStatH(0.3);  /* hight of the bos */
c5->cd(1);
LOS_dt_MCFD_wc->Draw();
c5->cd(2);
LOS_dt_MCFD_oddCh_wc->Draw();
c5->cd(3);
LOS_dt_MCFD_evenCh_wc->Draw();
c5->cd(4);
LOS_dt_TAMEX_wc->Draw();
c5->cd(5);
LOS_dt_TAMEX_oddCh_wc->Draw();
c5->cd(6);
LOS_dt_TAMEX_evenCh_wc->Draw();
c5->cd(7);
LOS_dt_MCFD_TAMEX_wc->Draw();
c5->cd(10);gPad->SetLogz();
TMCFD_vs_Q_wc->Draw("colz");
c5->cd(11); gPad->SetLogz();
Tres_vs_X_MCFD_wc->Draw("colz");
c5->cd(12); gPad->SetLogz();
Tres_vs_Y_MCFD_wc->Draw("colz");
c5->cd(13);gPad->SetLogz();
TTAMEX_vs_Q_wc->Draw("colz");
c5->cd(14); gPad->SetLogz();
Tres_vs_X_TAMEX_wc->Draw("colz");
c5->cd(15); gPad->SetLogz();
Tres_vs_Y_TAMEX_wc->Draw("colz");



TCanvas *c3 = new TCanvas("c3","LOS ToT1 ",0,0,850,750);
c3->Clear();
c3->Divide(4,3);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c3->cd(1);
LOS_Q->Draw();
c3->cd(2);
LOS_Q_test->Draw();
c3->cd(3); gPad->SetLogz();
Q_vs_X->Draw("colz");
c3->cd(4); gPad->SetLogz();
Q_vs_Y->Draw("colz");
c3->cd(6);
RaumWinkel->Draw();
c3->cd(7); gPad->SetLogz();
Qcorr_vs_X->Draw("colz");
c3->cd(8); gPad->SetLogz();
Qcorr_vs_Y->Draw("colz");
c3->cd(9);
LOS_Q_oddCh->Draw();
c3->cd(10);
LOS_Q_evenCh->Draw();
c3->cd(11);
LOS_Q_oddCh_corr->Draw();
c3->cd(12);
LOS_Q_evenCh_corr->Draw();

TCanvas *c13 = new TCanvas("c13","LOS ToT corr ",0,0,850,550);
c13->Clear();
c13->Divide(4,2);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c13->cd(1); gPad->SetLogz();
QPM1_vs_QPM5->Draw("colz");
c13->cd(2); gPad->SetLogz();
QPM2_vs_QPM6->Draw("colz"); 
c13->cd(3); gPad->SetLogz();
QPM3_vs_QPM7->Draw("colz");
c13->cd(4); gPad->SetLogz();
QPM4_vs_QPM8->Draw("colz"); 
c13->cd(5); gPad->SetLogz();
QPM1_vs_QPM5_corr->Draw("colz");
c13->cd(6); gPad->SetLogz();
QPM2_vs_QPM6_corr->Draw("colz"); 
c13->cd(7); gPad->SetLogz();
QPM3_vs_QPM7_corr->Draw("colz");
c13->cd(8); gPad->SetLogz();
QPM4_vs_QPM8_corr->Draw("colz"); 

TCanvas *c7 = new TCanvas("c7","LOS ToT vs Pos ",0,0,850,950);
c7->Clear();
c7->Divide(4,4);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c7->cd(1); gPad->SetLogz();
LOS_QT_vs_Y1->Draw("colz");
c7->cd(2); gPad->SetLogz();
LOS_QL_vs_X1->Draw("colz");
c7->cd(3); gPad->SetLogz(); 
LOS_QB_vs_Y1->Draw("colz");
c7->cd(4); gPad->SetLogz(); 
LOS_QR_vs_X1->Draw("colz");
c7->cd(5); gPad->SetLogz(); 
LOS_QT_vs_Y1_corr->Draw("colz");
c7->cd(6); gPad->SetLogz(); 
LOS_QL_vs_X1_corr->Draw("colz");
c7->cd(7); gPad->SetLogz(); 
LOS_QB_vs_Y1_corr->Draw("colz");
c7->cd(8); gPad->SetLogz(); 
LOS_QR_vs_X1_corr->Draw("colz");
c7->cd(9); gPad->SetLogz();
LOS_QLT_vs_X2->Draw("colz");
c7->cd(10); gPad->SetLogz();
LOS_QLB_vs_Y2->Draw("colz");
c7->cd(11); gPad->SetLogz(); 
LOS_QRB_vs_X2->Draw("colz");
c7->cd(12); gPad->SetLogz(); 
LOS_QRT_vs_Y2->Draw("colz");
c7->cd(13); gPad->SetLogz(); 
LOS_QLT_vs_X2_corr->Draw("colz");
c7->cd(14); gPad->SetLogz(); 
LOS_QLB_vs_Y2_corr->Draw("colz");
c7->cd(15); gPad->SetLogz(); 
LOS_QRB_vs_X2_corr->Draw("colz");
c7->cd(16); gPad->SetLogz(); 
LOS_QRT_vs_Y2_corr->Draw("colz");

TCanvas *c8 = new TCanvas("c8","LOS ToT vs Event ",0,0,850,950);
c8->Clear();
c8->Divide(2,4);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c8->cd(1); gPad->SetLogz();
Q1_vs_Icount->Draw("colz");
c8->cd(2); gPad->SetLogz();
Q5_vs_Icount->Draw("colz");
c8->cd(3); gPad->SetLogz();
Q2_vs_Icount->Draw("colz");
c8->cd(4); gPad->SetLogz();
Q6_vs_Icount->Draw("colz");
c8->cd(5); gPad->SetLogz();
Q3_vs_Icount->Draw("colz");
c8->cd(6); gPad->SetLogz();
Q7_vs_Icount->Draw("colz");
c8->cd(7); gPad->SetLogz();
Q4_vs_Icount->Draw("colz");
c8->cd(8); gPad->SetLogz();
Q8_vs_Icount->Draw("colz");

TCanvas *c4 = new TCanvas("c4","LOS Position ",0,0,850,1050);
c4->Clear();
c4->Divide(3,6);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c4->cd(1); gPad->SetLogz();
X_vs_Y->Draw("colz");
c4->cd(2); gPad->SetLogz();
X1_vs_Y1->Draw("colz");
c4->cd(3); gPad->SetLogz();
X2_vs_Y2->Draw("colz");
c4->cd(4); gPad->SetLogz();
X_vs_Y_TAMEX->Draw("colz");
c4->cd(5); gPad->SetLogz();
X1_vs_Y1_TAMEX->Draw("colz");
c4->cd(6); gPad->SetLogz();
X2_vs_Y2_TAMEX->Draw("colz");
c4->cd(7); gPad->SetLogz();
X_vs_Y_ToT->Draw("colz");
c4->cd(8); gPad->SetLogz();
X1_vs_Y1_ToT->Draw("colz");
c4->cd(9); gPad->SetLogz();
X2_vs_Y2_ToT->Draw("colz");
c4->cd(10); gPad->SetLogz();
X_vs_Y_wc->Draw("colz");
c4->cd(11); gPad->SetLogz();
X1_vs_Y1_wc->Draw("colz");
c4->cd(12); gPad->SetLogz();
X2_vs_Y2_wc->Draw("colz");
c4->cd(13); gPad->SetLogz();
X_vs_Y_ToT_corr->Draw("colz");
c4->cd(14); gPad->SetLogz();
X1_vs_Y1_ToT_corr->Draw("colz");
c4->cd(15); gPad->SetLogz();
X2_vs_Y2_ToT_corr->Draw("colz");
c4->cd(16); gPad->SetLogz();
X_vs_Y_mean->Draw("colz");
c4->cd(17); gPad->SetLogz();
X2_vs_Y2_proj->Draw("colz");

/*
TCanvas *c6 = new TCanvas("c6","Walk corrections MCFD",0,0,950,950);
c6->Clear();
c6->Divide(4,4);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c6->cd(1); gPad->SetLogz();
t1_vs_Q1_M->Draw("colz");
c6->cd(2); gPad->SetLogz();
t3_vs_Q3_M->Draw("colz");
c6->cd(3); gPad->SetLogz();
t5_vs_Q5_M->Draw("colz");
c6->cd(4); gPad->SetLogz();
t7_vs_Q7_M->Draw("colz");
c6->cd(5); gPad->SetLogz();
t1_vs_Q1_M_wc->Draw("colz");
c6->cd(6); gPad->SetLogz();
t3_vs_Q3_M_wc->Draw("colz");
c6->cd(7); gPad->SetLogz();
t5_vs_Q5_M_wc->Draw("colz");
c6->cd(8); gPad->SetLogz();
t7_vs_Q7_M_wc->Draw("colz");
c6->cd(9); gPad->SetLogz();
t2_vs_Q2_M->Draw("colz");
c6->cd(10); gPad->SetLogz();
t4_vs_Q4_M->Draw("colz");
c6->cd(11); gPad->SetLogz();
t6_vs_Q6_M->Draw("colz");
c6->cd(12); gPad->SetLogz();
t8_vs_Q8_M->Draw("colz");
c6->cd(13); gPad->SetLogz();
t2_vs_Q2_M_wc->Draw("colz");
c6->cd(14); gPad->SetLogz();
t4_vs_Q4_M_wc->Draw("colz");
c6->cd(15); gPad->SetLogz();
t6_vs_Q6_M_wc->Draw("colz");
c6->cd(16); gPad->SetLogz();
t8_vs_Q8_M_wc->Draw("colz");


TCanvas *c9 = new TCanvas("c9","Walk corrections TAMEX",0,0,950,950);
c9->Clear();
c9->Divide(4,4);
gStyle->SetTitleFontSize(0.07);
gStyle->SetOptStat(1111);
gStyle->SetStatX(0.99);   
gStyle->SetStatY(0.99);  
gStyle->SetStatW(0.25);  
gStyle->SetStatH(0.3);  
c9->cd(1); gPad->SetLogz();
t1_vs_Q1_T->Draw("colz");
c9->cd(2); gPad->SetLogz();
t3_vs_Q3_T->Draw("colz");
c9->cd(3); gPad->SetLogz();
t5_vs_Q5_T->Draw("colz");
c9->cd(4); gPad->SetLogz();
t7_vs_Q7_T->Draw("colz");
c9->cd(5); gPad->SetLogz();
t1_vs_Q1_T_wc->Draw("colz");
c9->cd(6); gPad->SetLogz();
t3_vs_Q3_T_wc->Draw("colz");
c9->cd(7); gPad->SetLogz();
t5_vs_Q5_T_wc->Draw("colz");
c9->cd(8); gPad->SetLogz();
t7_vs_Q7_T_wc->Draw("colz");
c9->cd(9); gPad->SetLogz();
t2_vs_Q2_T->Draw("colz");
c9->cd(10); gPad->SetLogz();
t4_vs_Q4_T->Draw("colz");
c9->cd(11); gPad->SetLogz();
t6_vs_Q6_T->Draw("colz");
c9->cd(12); gPad->SetLogz();
t8_vs_Q8_T->Draw("colz");
c9->cd(13); gPad->SetLogz();
t2_vs_Q2_T_wc->Draw("colz");
c9->cd(14); gPad->SetLogz();
t4_vs_Q4_T_wc->Draw("colz");
c9->cd(15); gPad->SetLogz();
t6_vs_Q6_T_wc->Draw("colz");
c9->cd(16); gPad->SetLogz();
t8_vs_Q8_T_wc->Draw("colz");
*/


}
