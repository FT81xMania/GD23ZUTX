#include <GD23ZUTX.h>

void setup()
{
  GD.begin();
}
void loop()
{
  MoviePlayer mp;

  mp.begin("oficial.avi");
  mp.play();
}
