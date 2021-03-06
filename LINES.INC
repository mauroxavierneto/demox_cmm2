'---- GENERAL LINES ROUTINES ----

'---- HORIZONTAL LINES ----

SUB HLINE(A,R,G,B,XA,XB)

 LOCAL T,TT,SI,CO

 SELECT CASE A
  CASE 1: SI=SIN(SN)     :CO=COS(SN)
  CASE 2: SI=SIN(SN-0.5) :CO=COS(SN-0.5)
  CASE 3: SI=SIN(SN-1)   :CO=COS(SN-1)
 END SELECT

 IF CO>0 THEN SLINE(A)=1 ELSE SLINE(A)=0

 TT=60+CO*30

 FOR T=180 TO 0 STEP -TT
  RR=R-T-TT: IF RR<0 THEN RR=0
  GG=G-T-TT: IF GG<0 THEN GG=0
  BB=B-T-TT: IF BB<0 THEN BB=0
  BOX XA,MAXY/2+SI*80+T\TT,XB-XA,2,0,,RGB(RR,GG,BB)
  BOX XA,MAXY/2+SI*80-T\TT,XB-XA,2,0,,RGB(RR,GG,BB)
 NEXT T

END SUB



