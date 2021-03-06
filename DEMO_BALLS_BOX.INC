SUB TESTE

 LOCAL T

 MAXBALLS=5

 FOR T=1 TO MAXBALLS
  RESET_JUMPING_BALL(T)
  SZ(T)=RND(T)*28
 NEXT T

 IF DEMOSEC=1 THEN PLAY MODFILE "./ASSETS/Excellate_pt4.mod",22050

 PAGE WRITE 1

 PAUSETIMER=0: TIMENOW=0: Timer=0

 DO WHILE 1=1

  'CLEAR MAIN BUFFER
  BOX 0,0,MAXX,MAXY,0,,RGB(0,0,0) 

  SORT_BALLS_DEPTH
  FOR T=1 TO MAXBALLS
   JUMPING_BALL(T)
  NEXT T

  FPS(600)

  'FIX SCREEN BORDERS
  BOX 0,0,MAXX,MAXY,1,RGB(0,0,0)

  PAGE COPY 1 TO 0,I

  'PAUSE(100)
  
 LOOP

END SUB

'-- SORT BALLS DEPTH
SUB SORT_BALLS_DEPTH

 LOCAL OK,SW,N

 OK=0

 DO WHILE OK=0

  OK=1
  FOR N=1 TO MAXBALLS-1
   IF SZ(N)>SZ(N+1) THEN
    SW=SZ(N): SZ(N)=SZ(N+1): SZ(N+1)=SW
    SW=SP(N): SP(N)=SP(N+1): SP(N+1)=SW
    SW=XX(N): XX(N)=XX(N+1): XX(N+1)=SW
    SW=YY(N): YY(N)=YY(N+1): YY(N+1)=SW
    SW= X(N):  X(N)= X(N+1):  X(N+1)=SW
    SW= Y(N):  Y(N)= Y(N+1):  Y(N+1)=SW
    SW=TR(N): TR(N)=TR(N+1): TR(N+1)=SW
    SW=TG(N): TG(N)=TG(N+1): TG(N+1)=SW
    SW=TB(N): TB(N)=TB(N+1): TB(N+1)=SW
    OK=0
   ENDIF
  NEXT N

 LOOP 

END SUB


'-- JUMPING BALL! --
SUB JUMPING_BALL(N)

 LOCAL CO,P

 'JUMPING SPEED
 Y(N)=Y(N)+YY(N)

 'HORIZONTAL MOVEMENT
 X(N)=X(N)+XX(N)

 'GRAVITY
 YY(N)=YY(N)+0.4

 'PERSPECTIVE
 P=(30-SZ(N))*10

 'BOUNCING BALLS WITH OTHERS
 SN=SZ(N)
 FOR T=1 TO MAXBALLS
  IF T<>N THEN
   ST=SZ(T)
   'COMPARE X AND Y
   IF X(N)+SN>X(T)-ST AND X(N)-SN<X(T)+ST AND Y(N)+SN>Y(T)-ST AND Y(N)-SN<Y(T)+ST THEN
    'COMPARE DEPTH
    IF SZ(N)+1>SZ(T)-1 AND SZ(N)-1<SZ(T)+1 THEN
     SP(N)=-SP(N)
     SP(T)=-SP(T)
     IF SZ(N)<SZ(T) THEN
      SZ(N)=SZ(N)-2: SZ(T)=SZ(T)+2
     ELSE 
      SZ(N)=SZ(N)+2: SZ(T)=SZ(T)-2
     ENDIF
     XX(N)=-XX(N)*1.1: YY(N)=-YY(N)*1.1
     XX(T)=-XX(T)*1.1: YY(T)=-YY(T)*1.1

     'COLISION SPEED LIMITS
     IF XX(N)<-12 THEN XX(N)=-12
     IF XX(N)> 12 THEN XX(N)= 12
     IF YY(N)<-16 THEN YY(N)=-16
     IF YY(N)> 12 THEN YY(N)= 12

    ENDIF
   ENDIF
  ENDIF
 NEXT T

 'MAKE THE BALL JUMP WHEN TOUCHING FLOOR
 IF Y(N)>MAXY-P-20 THEN YY(N)=-ABS(YY(N))
 IF YY(N)<-16 THEN YY(N)=-16

 'BOUNCE THE BALL WHEN TOUCHING WALLS
 IF X(N)<0+P THEN XX(N)=ABS(XX(N))
 IF X(N)>MAXX-P THEN XX(N)=-ABS(XX(N))
 IF SZ(N)>=29 THEN SP(N)=-ABS(SP(N))/1.01
 IF SZ(N)<=1 THEN SP(N)=ABS(SP(N))/1.01

 'DISTANCE
 SZ(N)=SZ(N)+SP(N) 
 IF SZ(N)<=1 THEN SZ(N)=1
 IF SZ(N)>=29 THEN SZ(N)=29

 T=((30-SZ(N))/10)+1
 CO=RGB(TR(N)/T,TG(N)/T,TB(N)/T)
 CIRCLE X(N),Y(N),SZ(N)+3,0,1,CO,CO

END SUB


SUB RESET_JUMPING_BALL(N)

 X(N)=MAXX/4+RND(1)*MAXX/2
 Y(N)=RND(1)*(MAXY/2)
 SZ(N)=0

 TR(N)=100+RND(1)*150
 TG(N)=100+RND(2)*150
 TB(N)=100+RND(3)*150

 DO WHILE SP(N)>=-0.2 AND SP(N)<=0.2
  SP(N)=(RND(1)*1000)/1000
 LOOP

 DO WHILE XX(N)>=-1 AND XX(N)<=1
  XX(N)=RND(1)*8-4
 LOOP

 DO WHILE YY(N)>=-1 AND YY(N)<=1
  YY(N)=-RND(1)*3+1  
 LOOP

END SUB


