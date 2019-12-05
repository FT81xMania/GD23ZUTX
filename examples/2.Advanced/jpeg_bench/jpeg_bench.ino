#include <GD23ZU.h>

int MCUID;
                    //    0             1             2              3          4            5          6            7            8            9              10               11           12             13         14            15             16            17           18          19         20           21         22          23      24
char FondoJPG[25][20]={"angry_16.jpg","Baboon40.jpg","bapa.jpg","betty_8.jpg","CnG.jpg", "dog.jpg","EagleEye.jpg","flower.jpg","flower3.jpg","flower4.jpg","hibiscus.jpg","lena20k.jpg","Mouse480.jpg","MrLyn.jpg","MtoX.jpg","Parrot2.jpg","Penguins.jpg","purple.jpg","rose.jpg","sunfl.jpg","Tgre.jpg","tiger.jpg","WtrLy.jpg","woof.jpg", "Fn1.jpg" };
int BaseJPGMAX = 23;
int IDJPG=0;

int timetest[24];

uint32_t startJPG=0, endJPG=0, drawT=0;

int Test=1;

void setup()
{
  GD.begin();
  IDEMCU();
}

void loop()
{
  GD.Clear();
  GD.get_inputs();
  
  if (Test==1){
   GD.SaveContext();  
    GD.Begin(BITMAPS);
    startJPG = millis();
    GD.cmd_loadimage(0, 0);
    GD.load(FondoJPG[IDJPG]);
    endJPG = millis();
    drawT=endJPG-startJPG;  timetest[IDJPG]=drawT;
    GD.Vertex2f(0*16, 0*16);
   GD.RestoreContext();
 
   GD.SaveContext();
    GD.ColorRGB(0xff,0x00,0x00);
    GD.cmd_number(GD.w/2, GD.h/2, 31, OPT_CENTER, drawT);
   GD.RestoreContext();
   
   IDJPG=IDJPG+1;
   if(IDJPG>=BaseJPGMAX+1){IDJPG=0; Test=0;}
   }

   GD.SaveContext();
   GD.cmd_fgcolor(0x505000);    GD.ColorRGB(0x000000);   GD.Tag(26);    GD.cmd_button(GD.w-130, (GD.h/2)-30, 120, 60, 29, 0,  "Test"); GD.Tag(255);
   if (GD.inputs.tag==26){
       //delay(75);
       Test=1;
      }
   
   if (Test==1){GD.cmd_fgcolor(0x005000);    GD.ColorRGB(0x000000);   GD.cmd_button(GD.w-130, (GD.h/2)-30, 120, 60, 29, 0,  "Running"); GD.Tag(255);}
   GD.RestoreContext();
  
  int delta=15;
  GD.SaveContext();
  for (int j=0; j<24; j++)
  {
    GD.ColorRGB(0xffffff);  GD.cmd_text(GD.w *0.55, 15+delta*j, 26, OPT_CENTER, FondoJPG[j]);
    GD.ColorRGB(0xffff00);  GD.cmd_number(GD.w *0.73, 8+delta*j, 26, 0, timetest[j]);
  }
  GD.RestoreContext();
  Parametros();
  GD.swap();
} 
