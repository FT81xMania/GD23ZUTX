//#include <GD23ZU.h>

#include <SPI.h>
#include <STM32_GD2.h>

void setup()
{
  //GD.begin(GD_STORAGE);
  GD.begin();
}
void loop()
{
  MoviePlayer mp;

  mp.begin("JS_Cndy.avi");
  mp.play();
}
