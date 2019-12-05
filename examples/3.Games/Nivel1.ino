#define TAG_TOGGLE1    202
static uint16_t value1, value2, value3, value4=65535 ;
static uint16_t options = OPT_FLAT;
int XPixeles = 100, DY= 100;
int LED1, LED2, LED3, LED4;
int apertura1,apertura2,apertura3,apertura4=128;

float dato;
int Centro=75/2;   //75x78 px, Centro=75/2
float AnguloG=0;  //angulo base de la imagen
float avance, rapidez=1.5;

float dato1;
int Centro1=70/2;   //75x78 px, Centro=75/2
float AnguloG1=0;  //angulo base de la imagen
float avance1, rapidez1=3.5;

float dato2;
int Centro2=100/2;   //180x178 px, Centro=178/2
float AnguloG2=180;  //angulo base de la imagen
float avance2, rapidez2=2.5;

float dato3;
int Centro3=100/2;   //180x178 px, Centro=178/2
float AnguloG3=0;  //angulo base de la imagen
float avance3, rapidez3=1.5;

float dato4;
int Centro4=70/2;   //75x78 px, Centro=75/2
float AnguloG4=0;  //angulo base de la imagen
float avance4, rapidez4=2.5;

float dato5;
int Centro5=70/2;   //75x78 px, Centro=75/2
float AnguloG5=180;  //angulo base de la imagen
float avance5, rapidez5=1.0;




void Nivel1()
{
  loadImages(1);
  
  int vida=100, mejora=1;
  int DispX=0;
  int DispY=5, velDisp=0, extra=0;
  int poder=3;
  int puntaje=0;
  int CaidaXMPeq=GD.random(720), CaidaYMPeq=50, velcaida=1;
  int CaidaXAster=GD.random(720), CaidaYAster=-85, velcaidaAster=2;
  int CaidaXAster2=GD.random(720), CaidaYAster2=-85, velcaidaAster2=3;
  int CaidaXAster3=GD.random(720), CaidaYAster3=-85, velcaidaAster3=4;
  int CaidaXAster4=GD.random(720), CaidaYAster4=-85, velcaidaAster4=5;
  int CaidaXAster5=GD.random(720), CaidaYAster5=-85, velcaidaAster5=1;
  int campo=55;
  int MotherX=-150, velMotherX=2;
  int PosXNave;
  int radar=0;

  while(1){
    //GD.wr(REG_PWM_DUTY,10);
    //GD.wr(REG_PWM_HZ, 5000);
     GD.play(0); //detiene sonido en altavoz
  GD.Clear();

//fondo de pantalla
  GD.SaveContext();
   GD.Begin(BITMAPS);  
   GD.ColorA(25);
    GD.Vertex2ii(0, 0, 15);
   GD.End();
  GD.RestoreContext();
//fondo de pantalla  

  GD.get_inputs();

//Marco verde
  GD.SaveContext();
   GD.ColorRGB(0x00ff00);  
   GD.LineWidth(1 * 16);
   GD.Begin(LINES);
   GD.Vertex2f(0*16, 0*16);   GD.Vertex2f(800*16, 0*16);
   GD.Vertex2f(0*16, 0*16);   GD.Vertex2f(0*16, 480*16);
   GD.Vertex2f(799*16, 0*16);   GD.Vertex2f(799*16, 480*16);
   GD.Vertex2f(0*16, 479*16);   GD.Vertex2f(799*16, 479*16);

   GD.Vertex2f(8*16, 26*16);   GD.Vertex2f((8+vida)*16, 26*16);
   
   GD.ColorRGB(0x0045ff);
   GD.Vertex2f((MotherX+90)*16, 130*16);  GD.Vertex2f((CaidaXMPeq+40)*16, (CaidaYMPeq+40)*16);

   if(radar==1)
   {
    GD.ColorRGB(0x450000);
    GD.Vertex2f((PosXNave+51)*16, 385*16);  GD.Vertex2f((CaidaXMPeq+40)*16, (CaidaYMPeq+40)*16);
    GD.Vertex2f((PosXNave+51)*16, 385*16);  GD.Vertex2f((CaidaXAster3+40)*16, (CaidaYAster3+40)*16);
    GD.Vertex2f((PosXNave+51)*16, 385*16);  GD.Vertex2f((CaidaXAster5+40)*16, (CaidaYAster5+40)*16);
   }

   GD.ColorRGB(0xff0000);
   GD.Vertex2f((160)*16, 26*16);   GD.Vertex2f((160-(100-vida))*16, 26*16);
  GD.RestoreContext();
//Marco verde  

//linea de vida
GD.SaveContext();
  if(vida<=0){vida=100; poder=1; campo=55; extra=0; puntaje=0; radar=0;}
  GD.Begin(BITMAPS);
  GD.Vertex2ii((10+vida), 5, 11); 
GD.RestoreContext();  
//linea de vida


//disparo y aumento de poder de disparo
  GD.SaveContext();
  GD.VertexTranslateX(16*DispX);
  if(DispY<=5){GD.ColorA(0); DispY=5; velDisp=0;}else{GD.ColorA(255); DispY=DispY-velDisp;}

  if (puntaje==0){poder=1; extra=0;}
  if (puntaje==5){poder=3; extra=10; campo=85; mejora=5;}
  if (puntaje==10){poder=4; extra=20; campo=85; mejora=7; radar=1;}
  
  if(poder==1){GD.Vertex2ii((43), DispY, 3);}   //laser beam
  if(poder==3){
     GD.Vertex2ii((20), DispY, 3);
     GD.Vertex2ii((43), DispY, 3);
     GD.Vertex2ii((63), DispY, 3);
    }
  if(poder==4){GD.Vertex2ii((43), DispY, 13);}   //laser beam
  GD.RestoreContext();

  GD.SaveContext();
  if(value1>=58253){value1=58253;}
  //GD.cmd_number(100, 50+DY*1, 31, OPT_SIGNED|OPT_RIGHTX, DispX);
  //GD.cmd_number(200, 50+DY*1, 31, OPT_SIGNED|OPT_RIGHTX, DispY);
  //GD.cmd_number(200+100, 50+DY*1, 31, OPT_SIGNED|OPT_RIGHTX, velDisp);
  GD.cmd_number(190, 14, 28, OPT_SIGNED|OPT_RIGHTX, vida);
  GD.cmd_number(700, 14, 28, OPT_SIGNED|OPT_RIGHTX, puntaje);
  
  GD.VertexTranslateX(16*800*value1/65535);
  PosXNave=800*value1/65535;
    //GD.Tag(100);  GD.Vertex2ii(0, 380, 6);  GD.Tag(255);  //F16
    GD.Tag(100);  GD.Vertex2ii(0, 380, 12);  GD.Tag(255);  //Mig29

    if (GD.inputs.tag==100){
      
     //GD.Vertex2ii(0, 0, 15);   //fondo de pantalla
   
    //GD.Vertex2ii(100, 0, 0);    //asteroide café
    //GD.Vertex2ii(100, 60, 1);   //asteroide gigante
    //GD.Vertex2ii(100, 120, 2);  //explosion
    //GD.Vertex2ii(100, 180, 3);  //laser1
    //GD.Vertex2ii(100, 240, 4);   //signo radiacion
   // GD.Vertex2ii(100, 300, 5);   //escudo de energía/laser3
   // GD.Vertex2ii(100, 360, 6);   //nave
    
    //GD.Vertex2ii(400, 0, 7);     //ufo Gigante 1
    //GD.Vertex2ii(400, 120, 8);   //ufo gigante 2
    //GD.Vertex2ii(300, 220, 9);  //alien
    //GD.Vertex2ii(400, 320, 10);  //asteroide verde
    //GD.Vertex2ii(400, 380, 11);  //vida

    //GD.Vertex2ii(300, 120, 12);  //Mig29
    //GD.Vertex2ii(300, 200, 13);  //laser2

        DispX=800*value1/65535;
        DispY=400;
        velDisp=20+extra;
        
      } 
      
  GD.End();
  GD.RestoreContext();
//disparo y aumento de poder de disparo  

//Objeto en caída




//asteroides en caída
  GD.SaveContext();
  GD.Begin(BITMAPS);

   avance2 = 1 + dato2;
   dato2 = dato2 + rapidez2;
   if((AnguloG2+avance2)>=0){rapidez2=2.5;}
   //if((AnguloG+avance)<=-179){rapidez=1.5;}
   //if((AnguloG+avance)<=0){rapidez=1.5;}
   rotate_Center(DEGREES(AnguloG2+avance2), Centro2);
   GD.cmd_setmatrix();
  
   CaidaYAster2=CaidaYAster2+velcaidaAster2;
   if(CaidaYAster2>=470)
    {
      CaidaYAster2=-85; 
      CaidaXAster2=GD.random(700); 
      if(CaidaXAster2<=45){CaidaXAster2=GD.random(700);}
    }

   GD.VertexTranslateX(16*CaidaXAster2);
   GD.VertexTranslateY(16*CaidaYAster2);

   GD.cmd_loadidentity();   
   
   GD.Vertex2ii(0, 0, 1); //asteroide gigante
  GD.End();
  GD.RestoreContext(); 
//asteroides en caída


//asteroides en caída
  GD.SaveContext();
  GD.Begin(BITMAPS);

   avance1 = 1 + dato1;
   dato1 = dato1 + rapidez1;
   if((AnguloG1+avance1)>=0){rapidez1=3.5;}
   //if((AnguloG+avance)<=-179){rapidez=1.5;}
   //if((AnguloG+avance)<=0){rapidez=1.5;}
   rotate_Center(DEGREES(AnguloG1+avance1), Centro1);
   GD.cmd_setmatrix();  
  
   CaidaYAster4=CaidaYAster4+velcaidaAster4;
   if(CaidaYAster4>=470)
    {
      CaidaYAster4=-85; 
      CaidaXAster4=GD.random(700); 
      if(CaidaXAster4<=45){CaidaXAster4=GD.random(700);}
    }

   GD.VertexTranslateX(16*CaidaXAster4);
   GD.VertexTranslateY(16*CaidaYAster4);

   GD.cmd_loadidentity();   
   
   GD.Vertex2ii(0, 0, 0); //asteroide café
  GD.End();
  GD.RestoreContext(); 
//asteroides en caída


  GD.SaveContext();
  GD.Begin(BITMAPS);
  
  CaidaYMPeq=CaidaYMPeq+velcaida;
  if(CaidaYMPeq>=470)
    {
      CaidaYMPeq=50; 
      CaidaXMPeq=GD.random(700); 
      if(CaidaXMPeq<=45){CaidaXMPeq=GD.random(700);}
    }
  
   avance = 1 + dato;
   dato = dato + rapidez;
   if((AnguloG+avance)>=0){rapidez=1.5;}
   //if((AnguloG+avance)<=-179){rapidez=1.5;}
   //if((AnguloG+avance)<=0){rapidez=1.5;}
   rotate_Center(DEGREES(AnguloG+avance), Centro);
   GD.cmd_setmatrix();
   GD.VertexTranslateX(16*CaidaXMPeq);
   //GD.Vertex2ii(0, CaidaYMPeq, 10); //asteroide verde
   GD.Vertex2ii(0, CaidaYMPeq, 9); //alien
  GD.cmd_loadidentity();   

   if ((DispX>=CaidaXMPeq-campo) && (DispX<=CaidaXMPeq+campo)) 
            {
            if ((DispY>=CaidaYMPeq-campo) && (DispY<=CaidaYMPeq)) 
               {
                GD.Vertex2ii(0, CaidaYMPeq, 2); 
                
                CaidaYMPeq=50; 
                CaidaXMPeq=GD.random(700);
                if(CaidaXMPeq<=45){CaidaXMPeq=GD.random(700);}
                puntaje++;
                vida=vida+mejora;
                
                if(vida>=101){vida=100;}
               }
            }
 
   if(CaidaYMPeq>=400)
     {
      GD.Vertex2ii(0, CaidaYMPeq, 2);  vida=vida-(random(5,20)); CaidaYMPeq=50; 
      CaidaXMPeq=GD.random(700);
      if(CaidaXMPeq<=45){CaidaXMPeq=GD.random(700);}
     }
  GD.End();
  GD.RestoreContext();

 
//Objeto en caída

//Control deslizante nave
  GD.SaveContext();
  GD.ColorA(0);
  switch (GD.inputs.track_tag & 0xff) {
  case TAG_TOGGLE1:
    value1 = GD.inputs.track_val;
  }

  GD.Tag(TAG_TOGGLE1);

  GD.cmd_toggle(50, 450, 800, 31, options, value1,
                "  " "\xff" "  ");
  GD.cmd_track(50, 450, 800, 31, TAG_TOGGLE1);
  GD.Tag(255);

  GD.cmd_text(450, 50+DY*0, 31, 0, "LED 1 = ");
  GD.cmd_number(650, 50+DY*0, 31, OPT_SIGNED|OPT_RIGHTX, LED1);

  if (value1>=65000){LED1 = 1;}
  if (value1<=0){LED1 = 0;}

  apertura1 =  100*value1/65535; 
  GD.cmd_number(200, 50+DY*0, 31, OPT_SIGNED|OPT_RIGHTX, apertura1);
  GD.cmd_number(200, 50+DY*1, 31, OPT_SIGNED|OPT_RIGHTX, value1);
  GD.cmd_number(200, 50+DY*2, 31, OPT_SIGNED|OPT_RIGHTX, 800*value1/65535);
  GD.RestoreContext();
//Control deslizante nave


  GD.SaveContext();
  if ((CaidaYMPeq>=50) && (CaidaYMPeq<=55))
  {
   GD.Begin(BITMAPS); 
   GD.SaveContext();
    GD.VertexTranslateX(16*(CaidaXMPeq-20)); GD.Vertex2ii(0+5, 0+15, 5);
   GD.RestoreContext();
   
   GD.SaveContext();
    GD.VertexTranslateX(16*(MotherX+25)); GD.Vertex2ii(0+5, 0+80, 5);
   GD.RestoreContext();
    //GD.Vertex2ii(0, 0+50, 8);
   GD.End();

   
  }
  GD.RestoreContext();

  GD.SaveContext();
   GD.Begin(BITMAPS); 

    MotherX=MotherX+velMotherX;
    if(MotherX<=-150){velMotherX=2;}
    if(MotherX>= 830){velMotherX=-2;}

    //if (CaidaXMPeq==MotherX){GD.Vertex2ii(0+5, 0+63, 5);}

    GD.VertexTranslateX(16*MotherX);
    GD.Vertex2ii(0, 0+50, 8);
   GD.End();
  GD.RestoreContext();


//asteroides en caída
  GD.SaveContext();
  GD.Begin(BITMAPS);

   avance3 = 1 + dato3;
   dato3 = dato3 + rapidez3;
   if((AnguloG3+avance3)>=0){rapidez3=1.5;}
   //if((AnguloG+avance)<=-179){rapidez=1.5;}
   //if((AnguloG+avance)<=0){rapidez=1.5;}
   rotate_Center(DEGREES(AnguloG3+avance3), Centro3);
   GD.cmd_setmatrix();
  
   CaidaYAster=CaidaYAster+velcaidaAster;
   if(CaidaYAster>=470)
    {
      CaidaYAster=-85; 
      CaidaXAster=GD.random(700); 
      if(CaidaXAster<=45){CaidaXAster=GD.random(700);}
    }

   GD.VertexTranslateX(16*CaidaXAster);
   GD.VertexTranslateY(16*CaidaYAster);

   GD.cmd_loadidentity();
   
   GD.Vertex2ii(0, 0, 1); //asteroide gigante
  GD.End();
  GD.RestoreContext(); 
//asteroides en caída


//asteroides en caída
  GD.SaveContext();
  GD.Begin(BITMAPS);

   avance4 = 1 + dato4;
   dato4 = dato4 + rapidez4;
   if((AnguloG4+avance4)>=0){rapidez4=2.5;}
   //if((AnguloG+avance)<=-179){rapidez=1.5;}
   //if((AnguloG+avance)<=0){rapidez=1.5;}
   rotate_Center(DEGREES(AnguloG4+avance4), Centro4);
   GD.cmd_setmatrix();

  
   CaidaYAster3=CaidaYAster3+velcaidaAster3;
   if(CaidaYAster3>=470)
    {
      CaidaYAster3=-85; 
      CaidaXAster3=GD.random(700); 
      if(CaidaXAster3<=45){CaidaXAster3=GD.random(700);}
    }

   GD.VertexTranslateX(16*CaidaXAster3);
   GD.VertexTranslateY(16*CaidaYAster3);

   GD.cmd_loadidentity();

   if ((PosXNave>=CaidaXAster3-70) && (PosXNave<=CaidaXAster3+25)) 
            {
            if ((380<=CaidaYAster3) && (380<=CaidaYAster3+25)) 
               {
                GD.Vertex2ii(0, 0, 2); CaidaYAster3=-85; CaidaXAster3=GD.random(700);  vida=vida-(random(5,20));
               }
            }


 
   GD.Vertex2ii(0, 0, 10); //asteroide verde
  GD.End();
  GD.RestoreContext(); 
//asteroides en caída



//asteroides en caída
  GD.SaveContext();
  GD.Begin(BITMAPS);

   avance5 = 1 + dato5;
   dato5 = dato5 + rapidez5;
   if((AnguloG5+avance5)>=0){rapidez5=1.5;}
   //if((AnguloG+avance)<=-179){rapidez=1.5;}
   //if((AnguloG+avance)<=0){rapidez=1.5;}
   rotate_Center(DEGREES(AnguloG5+avance5), Centro5);
   GD.cmd_setmatrix();
  
   CaidaYAster5=CaidaYAster5+velcaidaAster5;
   if(CaidaYAster5>=470)
    {
      CaidaYAster5=-85; 
      CaidaXAster5=GD.random(700); 
      if(CaidaXAster5<=45){CaidaXAster5=GD.random(700);}
    }

   GD.VertexTranslateX(16*CaidaXAster5);
   GD.VertexTranslateY(16*CaidaYAster5);

   GD.cmd_loadidentity();

  if ((PosXNave>=CaidaXAster5-70) && (PosXNave<=CaidaXAster5+25)) 
            {
            if ((380<=CaidaYAster5) && (380<=CaidaYAster5+25)) 
               {
                GD.Vertex2ii(0, 0, 2); CaidaYAster5=-85;  CaidaXAster5=GD.random(700); vida=vida-(random(5,20));
               }
            }


   GD.Vertex2ii(0, 0, 10); //asteroide verde
  GD.End();
  GD.RestoreContext(); 
//asteroides en caída

  //GD.cmd_number(100, 375, 28, OPT_SIGNED|OPT_RIGHTX, PosXNave);
  GD.cmd_number(100, 375, 28, OPT_SIGNED|OPT_RIGHTX, radar);
 
  GD.swap();
  }
}
