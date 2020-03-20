#include <GD23ZUTX.h>
#include "pez1.h"
#include "icoX35.h"

int MCUID;
char TX[50];

void setup()
{
  GD.begin();

  IDEMCU();

  LOAD_ASSETS();
  GD.BitmapLayout(ARGB4, 2 * 16, 16); // override the bitmap layout

  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  GD.load("Ab5.jpg");
}

int PX = 400, VelX=0;
int BX = random(50,750), BY=400, Burb=3, AY=25;
long previousMillisB = 0;
long intervalB = 5000;
int Pez=2;

int SEPx=20, SEPy=20;

void loop()
{
  GD.ClearColorRGB(0x000070);
  GD.Clear();

  GD.SaveContext();  
  GD.Begin(BITMAPS);
  GD.Vertex2ii(0, 20, 15);

   GD.Vertex2ii(0, AY+SEPy*0, 0, 0);
   GD.Vertex2ii(0, AY+SEPy*1, 0, 1);
   GD.Vertex2ii(0, AY+SEPy*2, 0, 2);
   GD.Vertex2ii(0, AY+SEPy*3, 0, 3);
   GD.Vertex2ii(0, AY+SEPy*4, 0, 4);
   GD.Vertex2ii(0, AY+SEPy*5, 0, 5);
   
   GD.Vertex2ii(SEPx*1, AY+SEPy*0, 0, 6);
   GD.Vertex2ii(SEPx*1, AY+SEPy*1, 0, 7);
   GD.Vertex2ii(SEPx*1, AY+SEPy*2, 0, 8);
   GD.Vertex2ii(SEPx*1, AY+SEPy*3, 0, 9);
   GD.Vertex2ii(SEPx*1, AY+SEPy*4, 0, 10);
   GD.Vertex2ii(SEPx*1, AY+SEPy*5, 0, 11);
   
   GD.Vertex2ii(SEPx*2, AY+SEPy*0, 0, 12);
   GD.Vertex2ii(SEPx*2, AY+SEPy*1, 0, 13);
   GD.Vertex2ii(SEPx*2, AY+SEPy*2, 0, 14);
   GD.Vertex2ii(SEPx*2, AY+SEPy*3, 0, 15);
   GD.Vertex2ii(SEPx*2, AY+SEPy*4, 0, 16);
   GD.Vertex2ii(SEPx*2, AY+SEPy*5, 0, 17);
   
   GD.Vertex2ii(SEPx*3, AY+SEPy*0, 0, 18);
   GD.Vertex2ii(SEPx*3, AY+SEPy*1, 0, 19);
   GD.Vertex2ii(SEPx*3, AY+SEPy*2, 0, 20);
   GD.Vertex2ii(SEPx*3, AY+SEPy*3, 0, 21);
   GD.Vertex2ii(SEPx*3, AY+SEPy*4, 0, 22);
   GD.Vertex2ii(SEPx*3, AY+SEPy*5, 0, 23);
   
   GD.Vertex2ii(SEPx*4, AY+SEPy*0, 0, 24);
   GD.Vertex2ii(SEPx*4, AY+SEPy*1, 0, 25);
   GD.Vertex2ii(SEPx*4, AY+SEPy*2, 0, 26);
   GD.Vertex2ii(SEPx*4, AY+SEPy*3, 0, 27);
   GD.Vertex2ii(SEPx*4, AY+SEPy*4, 0, 28);
   GD.Vertex2ii(SEPx*4, AY+SEPy*5, 0, 29);

   GD.Vertex2ii(SEPx*5, AY+SEPy*0, 0, 30);
   GD.Vertex2ii(SEPx*5, AY+SEPy*1, 0, 31);
   GD.Vertex2ii(SEPx*5, AY+SEPy*2, 0, 32);
   GD.Vertex2ii(SEPx*5, AY+SEPy*3, 0, 33);
   GD.Vertex2ii(SEPx*5, AY+SEPy*4, 0, 34);   

//Pez
   GD.SaveContext();
      GD.VertexTranslateX(16*(PX));
      //GD.Vertex2ii(0, 300, 0, Pez);
   GD.RestoreContext();

      PX = PX + VelX;
      if (VelX==0){Pez=2;}
      if (VelX>0){Pez=0;}
      if (VelX<0){Pez=1;}
        
       if(PX>=850){PX = -200;}
       if(PX<=-201){PX = 850;}
//Pez

//Burbujas
  GD.SaveContext();
    GD.VertexTranslateX(16*(BX));
    GD.Vertex2ii(0, BY, 0, Burb);
  GD.RestoreContext();    
      BY = BY - 10;
    
  unsigned long currentMillisB = millis();        
  if(currentMillisB - previousMillisB > intervalB)
  {
    previousMillisB= currentMillisB;       
      //BX = random(50,750);
      BX = random(40,320);
      //Burb=random(0,26);
      Burb=random(0,34);
      BY=400;
  }
//Burbujas
  
  GD.SaveContext();   
    sprintf(TX, "Size: %dx%d px", GD.w, GD.h);
    GD.cmd_text(GD.w-82, 3, 20, 0, TX);
  GD.RestoreContext();

  Parametros();
    
  GD.swap();
}
