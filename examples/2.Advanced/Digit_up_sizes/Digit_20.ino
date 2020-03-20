char Num20[20];
int N20=0, PYN20=0;
char Num20C[20];
int N20C=1, PYN20C=-11;
int Decenas20=0, PYDecenas20=0, Centenas20=0, Milenio20=0;

long previousMillis20=0, refresco20=30;
void digit20(int PX, int PY)
{
  int siseTX=20;
 sprintf(Num20, "%d ", N20);   sprintf(Num20C, "%d ", N20C); 
 
 unsigned long currentMillis20 = millis(); 
 if(currentMillis20 - previousMillis20 >= refresco20)
 {
  previousMillis20 = currentMillis20;

    PYN20=PYN20+1;
    PYN20C=PYN20C+1;
   
  if(PYN20>=11){PYN20=-11; N20=N20+2; if(N20>=10){N20=0; Decenas20=Decenas20+1; if(Decenas20>=10){Decenas20=0; Centenas20=Centenas20+1; if(Centenas20>=10){Centenas20=0; Milenio20=Milenio20+1;if(Milenio20>=10){Milenio20=0; Centenas20=0; Decenas20=0;}}}}}
  if(PYN20C>=11){PYN20C=-11; N20C=N20C+2; if(N20C>=10){N20C=1;}}
 }
 
  GD.cmd_text(PX+45, PY-PYN20, siseTX, OPT_CENTER, Num20); 
  GD.cmd_text(PX+45, PY-PYN20C, siseTX, OPT_CENTER, Num20C);
  GD.cmd_number(PX+45-10, PY, 20, OPT_CENTER, Decenas20);
  GD.cmd_number(PX+45-18, PY, 20, OPT_CENTER, Centenas20);
  GD.cmd_number(PX+45-26, PY, 20, OPT_CENTER, Milenio20);
  
  GD.ColorA(255);
  GD.cmd_fgcolor(0x000000);  GD.cmd_button(PX+38, PY-17, 10, 12, siseTX, OPT_FLAT, "");
  GD.cmd_fgcolor(0x000000);  GD.cmd_button(PX+38, PY+6, 10, 12, siseTX, OPT_FLAT, "");
  GD.ColorA(255);
}
