#include <GD23ZU.h>

#include "SpaceXb.h"

//                            0            1             2            3            4
char GrupoFondo[21][15]={"SW0031.jpg","SW0400.jpg","Fondo003.jpeg","zx13.jpg","selfie.jpg"};
int IDJPG=0;

void setup(){
  GD.begin(GD_STORAGE);
  //GD.cmd_setrotate(1);  
  //GD.self_calibrate();  
  
  //MP();
  Nivel1();
}
void loop(){}
