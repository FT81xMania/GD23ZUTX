void MP()
{
  loadImages(0);

  while(1){
  GD.Clear();

//fondo de pantalla
  GD.SaveContext();
   GD.Begin(BITMAPS);  
   GD.ColorA(25);
    GD.Vertex2ii(0, 0, 15);
   GD.End();
  GD.RestoreContext();
//fondo de pantalla  
  GD.swap();
  }
}
