char Num31[31];
int N31=0, PYN31=0;
char Num31C[31];
int N31C=1, PYN31C=-33;
int Decenas31=0, PYDecenas31=0, Centenas31=0, Milenio31=0;

long previousMillis31=0, refresco31=0;
void digit31(int PX, int PY)
{
  int siseTX=31;
 sprintf(Num31, "%d ", N31);   sprintf(Num31C, "%d ", N31C); 
 
 unsigned long currentMillis31 = millis(); 
 if(currentMillis31 - previousMillis31 >= refresco31)
 {
  previousMillis31 = currentMillis31;

    PYN31=PYN31+1;
    PYN31C=PYN31C+1;
   
  if(PYN31>=33){PYN31=-33; N31=N31+2; if(N31>=10){N31=0; Decenas31=Decenas31+1; if(Decenas31>=10){Decenas31=0; Centenas31=Centenas31+1; if(Centenas31>=10){Centenas31=0; Milenio31=Milenio31+1;if(Milenio31>=10){Milenio31=0; Centenas31=0; Decenas31=0;}}}}}
  if(PYN31C>=33){PYN31C=-33; N31C=N31C+2; if(N31C>=10){N31C=1;}}
 }
 
  GD.cmd_text(PX+46, PY-PYN31, siseTX, OPT_CENTER, Num31); 
  GD.cmd_text(PX+46, PY-PYN31C, siseTX, OPT_CENTER, Num31C);
  GD.cmd_number(PX+45-27, PY, 31, OPT_CENTER, Decenas31);
  GD.cmd_number(PX+45-51, PY, 31, OPT_CENTER, Centenas31);
  GD.cmd_number(PX+45-74, PY, 31, OPT_CENTER, Milenio31);
  
  GD.ColorA(255);
  GD.cmd_fgcolor(0x000000);  GD.cmd_button(PX+14, PY-51, 42, 35, siseTX, OPT_FLAT, "");
  GD.cmd_fgcolor(0x000000);  GD.cmd_button(PX+14, PY+15, 42, 35, siseTX, OPT_FLAT, "");
  GD.ColorA(255);
}
