int XProtector=0, velXProtector=1;
void Protector01()
{
 XProtector=XProtector+velXProtector;
 if(XProtector>=(GD.w-1)){velXProtector=-1;}
 if(XProtector<=0){velXProtector=1;}
 GD.SaveContext();
   GD.ColorRGB(0x00ff00);  
   GD.LineWidth(1 * 16);
   GD.Begin(LINES);
   GD.Vertex2f((XProtector)*16,(0)*16);  GD.Vertex2f((XProtector)*16,(GD.h)*16);
 GD.RestoreContext();
}
