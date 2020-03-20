#include <GD23ZUTX.h>

char TXP[50];
char LoadTime[40];
uint32_t startJPG=0, endJPG=0, drawT=0;

void setup()
{
  GD.begin();

  startJPG = millis();
   GD.cmd_loadimage(0, 0);
   GD.load("tree.jpg");
  endJPG = millis();
  
  drawT=endJPG-startJPG;
  sprintf(LoadTime, "Load time: %d millis", drawT);

   MP();
}
void loop(){}

void MP()
{
  while(1)
 {
   GD.Clear();
   
   GD.SaveContext();
    GD.Begin(BITMAPS);
    GD.Vertex2f(0*16, 0*16);
   GD.RestoreContext();

   GD.SaveContext();
    GD.ColorRGB(0xff,0x00,0x00);
    GD.cmd_text(GD.w/2, (GD.h)-20, 29, OPT_CENTER, LoadTime);
   GD.RestoreContext();    

sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w-43, (GD.h)-20, 20, OPT_CENTER, TXP);
sprintf(TXP,"F_BUS: %d MHz", (F_BUS/1000000));  GD.cmd_text(GD.w-43, (GD.h)-7, 20, OPT_CENTER, TXP);

sprintf(TXP,"SPI speed: %d MHz", (SetSPISpeed/1000000));  GD.cmd_text(GD.w-45, (GD.h)-36, 20, OPT_CENTER, TXP);

   
   GD.swap();
 }
}
