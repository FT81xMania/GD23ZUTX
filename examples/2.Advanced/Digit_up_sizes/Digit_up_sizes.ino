#include <GD23ZUTX.h>
int MCUID;

void setup()
{
  GD.begin();
  IDEMCU();
}

void loop()
{
GD.Clear();

digit31(150,25);

GD.Begin(LINES);
  GD.ColorRGB(255,255,255);
  GD.Vertex2f(0*16, 0*16);    GD.Vertex2f((GD.w)*16, 0*16);  //Superior
  GD.Vertex2f(0*16, (GD.h-1)*16);  GD.Vertex2f((GD.w)*16, (GD.h-1)*16); //inferior
  GD.Vertex2f(0*16, 0*16);  GD.Vertex2f(0*16, (GD.h-1)*16); //izquierda
  GD.Vertex2f((GD.w-1)*16, 0*16);  GD.Vertex2f((GD.w-1)*16, (GD.h-1)*16); //derecha  

//  int PXT=400; int PYT=154; int AlturaTipo=29;
//  GD.Vertex2f(PXT*16, PYT*16);    GD.Vertex2f(PXT*16, (PYT-AlturaTipo)*16);
//  GD.Vertex2f((PXT-28)*16, PYT*16);    GD.Vertex2f((PXT-28)*16, (PYT-AlturaTipo)*16);  //Altura en pixeles
Parametros();

digit20(GD.w/2-35,GD.h/2-25);
digit20(-10,20);



//GD.cmd_text(GD.w / 2, (GD.h / 2)-100, 31, OPT_CENTER, "0 1 2 3 4 5 6 7 8 9");
  GD.cmd_text(GD.w / 2, GD.h / 2, 31, OPT_CENTER, "Hello world");
  
GD.swap();
}
