
'-- INITIALIZE DEMO RACING --

SUB INIT_DEMO_RACING

 LOCAL T

 'DEBUG=1

 IF DEMOSEC=1 THEN
  PAGE WRITE 6:CLS
  LOAD PNG "./ASSETS/paint_car_3d.png"
 ENDIF

 'PAGE 4 USED FOR CAR ZOOM
 PAGE WRITE 4:CLS

 maxy = MM.VRES
 roadW=1500 'road width
 segL=500   'segment lenght
 camD=0.35  'camera depth

 xpl=0 
 dx=0: N=2000: posi=30
 Li=30
 H=1500

 wdiv=MM.HRES/2
 hdiv=MM.VRES/2

 MAXX=MM.HRES
 MAXY=MM.VRES

 Dim spa(10)
 Dim curve(N),clip(N),scale(N)
 Dim sqArc(N),tree(N)
 Dim polx%(4),poly%(4)

 For t=0 To N
  xx(t)=0
  yy(t)=0
  zz(t)=0
  curve(t)=0
  scale(t)=0
  X(t)=0
  Y(t)=0
  W(t)=0
 Next t

 'CREATE ROAD
 ytemp = yy(0)
 adj=1.14 'FPS=19
 'adj=1 'FPS=17
 t=adj
 For i = 0 To N
  zz(i) = i*segL
  SELECT CASE i
   CASE 20*t TO 75*t: curve(i)=0.7*90
   CASE 76*t TO 116*t: curve(i)=-0.7*90
   CASE 117*t TO 148*t: curve(i)=0.7*90
   CASE 149*t TO 170*t: curve(i)=0
   CASE 171*t TO 341*t: yy(i)=Sin((i/t)/11-34.2)*3000
   CASE 400*t TO 460*t: curve(i)=-0.9*90
   CASE 470*t TO 550*t: curve(i)=0.9*90
   CASE 564*t TO 599*t: yy(i)=Sin((i/t)/11-45)*3000: curve(i)=-1*90
   CASE 633*t TO 737*t: yy(i)=Sin((i/t)/11-45)*3000: curve(i)=1*90
   CASE 750*t TO 830*t: curve(i)=-1*90
   CASE 851*t TO 890*t: curve(i)=0.9*90
   CASE 901*t TO 950*t: curve(i)=-0.7*90
   CASE >1010*t: curve(i)=0
  END SELECT
  if not(i>165*t and i<195*t) then
   if (i=>165*t and i<=360*t) or (i>=565*t and i<=640*t) then
    if i mod 36 then sqArc(i)=0 else sqArc(i)=1
   else
    if i mod 16 then sqArc(i)=0 else sqArc(i)=1 
   endif
  endif
  if i>1050*t then if i mod 16 then sqArc(i)=2 else sqArc(i)=3
 Next i
 yy(0)=ytemp

END SUB


'-- DRAW SPRITE CAR --
Sub spriteCar (x,y,yc,n,S,ZC)

 LOCAL XX,YY,SX,SY,T

 'CUT IMAGES 
 SELECT CASE n
  'CENTERED
  CASE  1: XX=  2: YY=  0: SX=119: SY= 65 
  CASE  2: XX=  2: YY= 65: SX=119: SY= 68
  CASE  3: XX=  2: YY=133: SX=119: SY= 76 
  CASE  4: XX=  2: YY=209: SX=119: SY= 89 
  'SIDE
  CASE  5: XX=121: YY=  0: SX=128: SY= 65 
  CASE  6: XX=121: YY= 65: SX=128: SY= 68 
  CASE  7: XX=121: YY=133: SX=128: SY= 76 
  CASE  8: XX=121: YY=209: SX=128: SY= 89 
  CASE  9: XX=249: YY=  0: SX=146: SY= 65 
  CASE 10: XX=249: YY= 65: SX=146: SY= 68 
  CASE 11: XX=249: YY=133: SX=146: SY= 76 
  CASE 12: XX=249: YY=209: SX=146: SY= 89 
 END SELECT

 'SHADOW
 SELECT CASE n
  CASE 1 TO 4:   'CENTER
   polx%(0)=x-SX/4: poly%(0)=y-SY/2.5
   polx%(1)=x+SX/4: poly%(1)=y-SY/2.5
   polx%(2)=x+SX/2.2: poly%(2)=y+SY/2
   polx%(3)=x-SX/2.2: poly%(3)=y+SY/2
  CASE 5 TO 12:  'LEFT
   IF S=5 THEN
    polx%(0)=x-SX/2:   poly%(0)=y-SY*1+75
    polx%(1)=x+SX/3.9: poly%(1)=y-SY*1+75
    polx%(2)=x+SX/2.2: poly%(2)=y+SY/2
    polx%(3)=x-SX/4.2: poly%(3)=y+SY/2
   ELSE          'RIGHT
    polx%(0)=x-SX/3.9: poly%(0)=y-SY*1+75
    polx%(1)=x+SX/2:   poly%(1)=y-SY*1+75
    polx%(2)=x+SX/4.2: poly%(2)=y+SY/2
    polx%(3)=x-SX/2.2: poly%(3)=y+SY/2
   ENDIF
 END SELECT
 'DRAW SHADOW
 if y<>0 then
  T=RGB(SW*20,SW*20,SW*20)
  polygon (4),polx%(),poly%(),T,T
 endif

 IF ZC=0 THEN
  'DRAW STANDARD CAR
  BLIT XX,YY,x-SX/2,yc-SY/2,SX,SY,6,S
  IF n>8 THEN
   IF SIDE=5 THEN T=-1 ELSE T=1
   IF SW=1 THEN
    CIRCLE x+(SX/2.25)*T,yc-SY/6.3,9,1,0.5,RGB(255,127,75),RGB(255,127,75)
   ELSE
    CIRCLE x+(SX/5.2)*T,yc+SY/3.9,9,1,0.5,RGB(255,127,75),RGB(255,127,75)
   ENDIF
  ENDIF
 ELSE
  'ZOOMED CAR
  PAGE WRITE 1
  IF ZC<-95 THEN ZC=-95
  IMAGE RESIZE_FAST XX,YY,SX,SY, x-SX/2-ZC/2,yc-SY/2-(ZC/1.5211)/2, SX+ZC,SY+ZC/1.5211,6,1
 ENDIF
End Sub


'-- RENDER POLYGON --
Sub drawQuad (c,x1,y1,w1,x2,y2,w2)

 polx%(0)=x1-w1: poly%(0)=y1
 polx%(1)=x1+w1: poly%(1)=y1
 polx%(2)=x2+w2: poly%(2)=y2
 polx%(3)=x2-w2: poly%(3)=y2
 polx%(4)=x1-w1: poly%(4)=y1
 polygon (4),polx%(),poly%(),c,c

End Sub


'PROJECT ROAD
Sub project(camX,camY,camZ,n)
 If zz(n)-camZ <> 0 Then scale(n) = camD/(zz(n)-camZ) Else scale(n)=0
 X(n) = (1 + scale(n)*(xx(n) - camX)) * wdiv
 Y(n) = (1 - scale(n)*(yy(n) - camY)) * hdiv
 W(n) = scale(n) * roadW * wdiv
End Sub


'-- RUN RACING DEMO --

SUB RUN_DEMO_RACING

 LOCAL T,TT,XP,TR,TL,CO,TSIZE,XTXT,YTXT,GOCREDIT,CREDIT,FTXTA,FTXTB,ENDING,ZC,STOPTXT,CJUMP

 DIM A$(30) LENGTH 25

 TSIZE=0
 GOCREDIT=1
 CREDIT=0
 ENDING=0
 STOPTXT=0
 
 FTXTA=-44
 FTXTB=-44
 ZC=0

 INIT_FONT_K

 XP=0

 PAGE WRITE 1

 'IF DEMOSEC=1 THEN 
 PLAY STOP: PLAY MODFILE "./ASSETS/excellate_pt4.mod",22050
 TIMERNOW=0:PAUSETIMER=0:TIMER=0
 
 'RUN DEMO UNTIL 35 SECONDS
 DO WHILE SEC<=35

  SEC=TIMER/1000

  speed=1000

  IF MM.INFO(CPUSPEED)=400000000 THEN FPS(19) ELSE FPS(17)

  posi = posi + speed
  If posi >= N*segL Then posi=posi-N*segL
  If posi <0 Then posi=posi+N*segL

  startPos = posi/segL
  camH = yy(startPos)+H

  dx=0: xpl=0
  maxyC=MM.VRES

  'print@(0,0) startPos

  T=startPos
  if (T>168*adj and T<188*adj) then cjump=3: spdY=-8

  'DRAW ROAD
  For nn = startPos+1 To startPos+Li

   'CALL PROJECTION ROUTINE
   If nn>=N Then
    Project(XP*roadW-xpl,camH,startPos*segL - N*segL, nn Mod N)
   Else
    Project(XP*roadW-xpl,camH,startPos*segL, nn Mod N)
   EndIf

   'SET CURVES 
   xpl=xpl+dx
   dx=dx+curve(nn)

   'CLIPPING ROAD
   clip(nn)=maxyC
   If (Y(nn)<=maxyC) Then
    maxyC = Y(nn)
    no=(nn-1) Mod N
    'ALTERNATE COLORS
    if ((nn/3) mod 2)=0 then
     cGrass = rgb(16,200,16)
     cRumble = rgb(255,255,255)
     cRoad = rgb(40,40,40)
     IF sqArc(nn)>=2 then
      CO=W(nn)/5
      cGrass = rgb(CO/2,20+CO/2,CO/2)
      cRumble = rgb(10+CO/2,30+CO/2,10+CO/2)
      cRoad = rgb(CO,CO,CO)
     ENDIF
    else
     cGrass = rgb(0,154,0)
     cRumble = rgb(255,0,0)
     cRoad = rgb(20,20,20)
     IF sqArc(nn)>=2 then
      CO=W(nn)/5
      cGrass = rgb(10+CO/2,40+CO/2,10+CO/2)
      cRumble = rgb(30+CO/2,50+CO/2,30+CO/2)
      cRoad = rgb(10+CO,10+CO,10+CO)
     ENDIF
    endif

    'DRAW ROAD  
    'box 0,Y(nn),MM.HRES,int(Y(no)-Y(nn))+1,0,,cGrass
    t=int(Y(no)-Y(nn))+1
    if Y(nn)+t>mm.vres then t=mm.vres-Y(nn)-1
   
    'FAKE TEXTURES
    if t>0 and X(no)+20>0 and Y(nn)<mm.vres then
     image resize_fast 100-(X(no)+20)/(mm.hres/100),350-(nn mod 3)*(6+Y(nn)\80),100,10+Y(nn)\10, 0,Y(nn),X(no)+20,t, 6,0
    endif
    if t>0 and X(nn)<mm.hres and Y(nn)<mm.vres then
     image resize_fast 100-X(nn)/(mm.hres/100),     350-(nn mod 3)*(6+Y(nn)\80),100,10+Y(nn)\10, X(nn),Y(nn),mm.hres-X(nn),t, 6,0
    endif

    drawQuad(cRumble,X(no),Y(no),W(no)*1.2,X(nn),Y(nn),W(nn)*1.2)
    drawQuad(cRoad,X(no),Y(no),W(no),X(nn),Y(nn),W(nn))

    'if t>0 and X(no)+20>0 and Y(nn)<mm.vres and Y(nn)>mm.vres-150 then
    ' image warp_v 0,300+(nn mod 10)*10,200,10, X(nn)-W(nn)/2,Y(nn),W(nn), X(no)-W(no)/2,Y(nn)+t,W(no), 6,0
     'image resize_fast X(nn)-W(nn)/1.2,Y(nn),W(nn)*1.3,Y(nn)+t, 0,Y(nn),mm.hres/2,Y(nn)+t
   ' endif

   EndIf
  Next nn 
  box 0,y(startpos+1)+1,MM.HRES,MM.VRES-y(startpos+1)+1,0,,RGB(0,0,0)

  'ARCH ROAD / TUNNEL
  sizeX=1
  For nn = startPos+Li to startPos+1 step -1
   sizeX=sizeX+0.45
   if sqArc(nn)>0 then 
    no=(nn-1) Mod N
    size=(W(nn)-5)/0.75
    TL=X(nn)-W(nn)*1.5-sizeX/2
    TR=X(nn)+W(nn)*1.5-sizeX/2
    CO=100+W(nn): IF co>255 then co=255  
    YT=Y(nn)-size-2
    IF sqArc(nn)=1 THEN
     'ARCH
     'if TL>0 then 
     ' box TL,YT,sizeX,size+1,0,,RGB(CO,CO,CO)        'LEFT
     ' box TL,YT,TR-TL+1,sizeX/1.5-1,0,,RGB(CO,CO,CO) 'UPPER
     'endif
     'if TR<MAXX then box TR,YT,sizeX,size+1,0,,RGB(CO,CO,CO)  'RIGHT

     IF YT+SIZE+1>MM.VRES THEN YT=MM.VRES-SIZE-1
     IF YT<0 THEN YT=0
     IF SIZE<0 THEN SIZE=0

     'LEFT TREE
     T=TL-size/6
     TT=0
     IF T<0 THEN TT=ABS(T): T=0
     IF TT<100 THEN IMAGE RESIZE_FAST 540+TT,172,100-TT,228, T,YT,5+size/3,size+1,6,1

     'RIGHT TREE
     T=TR-size/6
     TT=0
     IF T>=mm.hres-(5+size/3+1) THEN TT=ABS(T-(mm.hres-(5+size/3+1)))
     IF T>0 AND T<mm.hres AND TT<100 THEN IMAGE RESIZE_FAST 540+TT,172,100-TT,228, T,YT,5+size/3,size+1,6,1

    ELSE IF sqArc(nn)>=2 THEN
     'ENDING TUNNEL
     ENDING=1
     CO=CO-120+sqArc(nn)*20
     IF TL<=0 THEN TL=0
     IF TR>=MAXX THEN TR=MAXX  
     box 0,YT,TL,size+1,0,,RGB(CO,CO,CO)            'LEFT
     box TR,YT,MAXX-TR,size+1,0,,RGB(CO,CO,CO)      'RIGHT
     box 0,YT-sizex*8,MAXX,sizeX*8,0,,RGB(CO,CO,CO) 'UPPER
     oldtl=TL: oldtr=TR: oldsize=size: oldyt=YT
     no=(nn-2) Mod N
     size=(W(nn-1)-5)/0.75
     TL=X(nn-1)-W(nn-1)*1.5-sizeX/2
     TR=X(nn-1)+W(nn-1)*1.5-sizeX/2
     YT=Y(nn-1)-size+0.45-2
     IF TL<=0 THEN TL=0
     IF TR>=MAXX THEN TR=MAXX
     'TRIANGLE TL,YT+SIZE,TL-SIZE,oldyt+oldsize,oldtl,oldyt+oldsize,RGB(CO,CO,CO),RGB(CO,CO,CO)
     'TRIANGLE TR,YT+SIZE,TR+SIZE,oldyt+oldsize,oldtr,oldyt+oldsize,RGB(CO,CO,CO),RGB(CO,CO,CO)
    ENDIF
   endif
  next nn

  'HORIZON LINE AXYS
  YC = (Y(Startpos+Li)-MM.VRES/2+180)

  'CAR SPRITE FOLLOW ROAD HEIGHT
  Side=4
  SprN = INT(ABS(SIN(RAD(YC/3+95))*10))
  if SprN<2 then SprN=2
  if SprN>4 then SprN=4

  'CAR SPRITE FOLLOW ROAD CURVES
  T=INT(X(Startpos+Li))-MAXX/2
   IF CJUMP=0 THEN
   SELECT CASE T
    CASE <-95 : SprN=SprN+8: Side=5
    CASE <-40 : SprN=SprN+4: Side=5
    CASE > 40 : SprN=SprN+8: Side=4
    CASE > 95 : SprN=SprN+4: Side=4
   END SELECT
  ELSE
   'CAR SPRITE FOLLOW JUMP
   if spdY<0 then SprN=Ycar\50 else SprN=4-Ycar\100
   if spdY<0 then SprN=-SpdY\2 else SprN=3-cjump+SpdY\3
   if SprN>4 then SprN=4
   if SprN<1 then SprN=1
  ENDIF

  'SHADOW AXYS
  ShadY = MM.VRES-60+COS(RAD(YC-40))*10+SW

  'CAR Y - JUMPING?
  if cjump=0 then
   Ycar = Shady: SpdY=0
  else
   Ycar = Ycar + spdY
   spdY=spdY+1
  endif

  'CAR LIMIT
  if Ycar > ShadY+3 then cjump=cjump-1: spdY=-spdY/2

  IF SEC>=30 THEN Ycar=Ycar-(SEC-30)*56: ShadY=0: ZC=ZC-2.8

  'DRAW CAR
  SpriteCar(MM.HRES/2-T/2,ShadY,Ycar,SprN,Side,ZC)

  'GENERAL SWAP (USED FOR SHADOW)
  IF SW=0 THEN SW=1 ELSE SW=0

  'ENDING
  IF SEC>=32 THEN T=(MAXX/2)*(SEC-32): BOX MAXX/2-T,MAXY/2-T/1.77, T*2,(T*2)/1.77, 0,,RGB(0,0,0)

  'TEXT ZOOM
  IF TSIZE>1 AND STOPTXT=0 THEN
   IF TSIZE<=1 THEN TSIZE=1
   XTXT=MAXX/2-((52*12)/TSIZE)/2
   SIZEX=(52*12)/TSIZE
   SIZEY=(60*2)/TSIZE
   IF XTXT<0 THEN XTXT=0
   PAGE WRITE 1
   IMAGE RESIZE_FAST 0,0,52*12,60*2, XTXT,90-SIZEY/2,SIZEX,SIZEY,5,1
   TSIZE=TSIZE-0.30
  ENDIF

  IF CREDIT>0 THEN
   'WHEN FINISH SET THE REAL TEXT TO KEEP PERFORMANCE   
   IF CREDIT >= 2 THEN
    PRINTK(FTXTA,30,A$(CREDIT*2-3),4)
    PRINTK(FTXTB,94,A$(CREDIT*2-2),4)
   ENDIF
   'DISMISS TEXT TO SIDES
   IF CREDIT<=11 THEN FTXTA=FTXTA-48: FTXTB=FTXTB+48
   'IF FTXTA<-52*28 THEN IF CREDIT>9 THEN TSIZE=1 ELSE TSIZE=0
   IF FTXTA<-52*22 THEN 
    STOPTXT=STOPTXT+1
    IF STOPTXT>26*ADJ THEN
     STOPTXT=0
     PRINTK(-44,30,A$(CREDIT*2-1),4)
     PRINTK(-44,94,A$(CREDIT*2),4)
     IF CREDIT>11 THEN TSIZE=1 ELSE TSIZE=0
    ENDIF
   ENDIF
  ENDIF

  IF STOPTXT>0 THEN
   PRINTK(-44,30,A$(CREDIT*2-1),4)
   PRINTK(-44,94,A$(CREDIT*2),4)
  ENDIF

  'ROLL CREDIT TEXT
  IF GOCREDIT>0 AND TSIZE=0 THEN
   CREDIT=CREDIT+1  
   FTXTA=-44
   FTXTB=-44
   SELECT CASE CREDIT
    CASE 1: 
     A$(1)="THIS DEMO IS"
     A$(2)="DEDICATED TO"
    CASE 2: 
     A$(3)=" ALL PEOPLE "
     A$(4)=" THAT DON'T "
    CASE 3: 
     A$(5)=" LEAVE  THE "
     A$(6)="  FEELINGS  "
    CASE 4: 
     A$(7)=" OF A RETRO "
     A$(8)=" WORLD  DIE "
    CASE 5: 
     A$(9)= "IF YOU  MISS"
     A$(10)="  THE PAST  "
    CASE 6: 
     A$(11)="  BUT LIKE  "
     A$(12)=" THE FUTURE "
    CASE 7: 
     A$(13)="THE  CMM2 IS"
     A$(14)="  FOR YOU!  "
    CASE 8: 
     A$(15)="  JOIN THE  "
     A$(16)=" COMMUNITY! "
    CASE 9: 
     A$(17)="            "
     A$(18)="            "    
    CASE 10: 
     A$(19)=" THIS  DEMO "
     A$(20)=" IS PROUDLY "
    CASE 11: 
     A$(21)="DEVELOPED BY"
     A$(22)="MAURO XAVIER"
   END SELECT  

   PAGE WRITE 5: CLS
   PRINTK(-52, 0,A$(CREDIT*2-1),4)
   PRINTK(-52,64,A$(CREDIT*2  ),4)
   TSIZE=7.5
   PAGE WRITE 1
  ENDIF

  'COPY TO MAIN PAGE
  PAGE COPY 1 TO 0,I

  'BACKGROUND
  BOX 0,0,MAXX,Y(startPos+Li),0,,RGB(0,0,255)

  'BLACK ENDING OF THE TUNNEL
  IF ENDING=1 THEN BOX MAXX/2-30,Y(startPos+Li)-30,60,30,0,,RGB(0,0,0)

 LOOP

 'SCROLL UP
 FOR T=1 TO 200
  PAGE SCROLL 0,0,1,0
  PAUSE(5)
 NEXT T

 PLAY STOP

END SUB
