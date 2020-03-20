#include <GD23ZUTX.h>

char TXP[50];
#define PNGTAG1 129
#define PNGTAG2 130

  static int16_t xTouch1, xDelta1, xCar1;
  static int16_t yTouch1, yDelta1, yCar1;
  static byte oldTag1;

  static int16_t xTouch2, xDelta2, xCar2;
  static int16_t yTouch2, yDelta2, yCar2;
  static byte oldTag2;

void setup()
{
  GD.begin();
  yCar2=GD.h-110;

   GD.BitmapHandle(0);
   GD.cmd_loadimage(0, 0);
   GD.load("Fn1.jpg");

   GD.BitmapHandle(1);
   GD.cmd_loadimage(-1, 0);
   GD.load("Rad1a.png");
  
   MP();
}
void loop(){}



void MP()
{
 while(1)
 {
 GD.Clear();
 GD.get_inputs();

  if(GD.inputs.tag==PNGTAG1)
  {
    if (oldTag1==0)
    {
      xDelta1 = GD.inputs.tag_x -xCar1;
      yDelta1 = GD.inputs.tag_y -yCar1;
    }
  xCar1=GD.inputs.tag_x - xDelta1;
  yCar1=GD.inputs.tag_y - yDelta1;

  if(xCar1<0) xCar1=0;
  if(yCar1<0) yCar1=0;
  if(xCar1>GD.w-110) xCar1=GD.w-110;
  if(yCar1>GD.h-110) yCar1=GD.h-110;
  }

  if(GD.inputs.tag==PNGTAG2)
  {
    if (oldTag2==0)
    {
      xDelta2 = GD.inputs.tag_x -xCar2;
      yDelta2 = GD.inputs.tag_y -yCar2;
    }
  xCar2=GD.inputs.tag_x - xDelta2;
  yCar2=GD.inputs.tag_y - yDelta2;

  if(xCar2<0) xCar2=0;
  if(yCar2<0) yCar2=0;
  if(xCar2>GD.w-110) xCar2=GD.w-110;
  if(yCar2>GD.h-110) yCar2=GD.h-110;
  }

  oldTag1=GD.inputs.tag;
  oldTag2=GD.inputs.tag;
   
   GD.SaveContext();
   GD.Begin(BITMAPS);
    GD.Vertex2ii(0,0,0);
//    GD.Tag(PNGTAG1); GD.VertexTranslateX(xCar1*16); GD.Vertex2ii(0,yCar1,1); GD.Tag(255);
//    GD.Tag(PNGTAG2); GD.VertexTranslateX(xCar2*16); GD.Vertex2ii(0,yCar2,1); GD.Tag(255);

     GD.BitmapHandle(1);
     GD.Tag(PNGTAG1); GD.Vertex2f(xCar1*16,yCar1*16); GD.Tag(255);
     GD.Tag(PNGTAG2); GD.Vertex2f(xCar2*16,yCar2*16); GD.Tag(255);

   GD.RestoreContext();

   GD.SaveContext();
    GD.ColorRGB(0xff,0x00,0x00);
    sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w-43, (GD.h)-20, 20, OPT_CENTER, TXP);
    sprintf(TXP,"SPI1 speed: %d MHz", (SetSPISpeed/1000000));  GD.cmd_text(GD.w-49, (GD.h)-7, 20, OPT_CENTER, TXP);
   GD.RestoreContext();    

  Protector01();

 GD.swap();
 }
}
