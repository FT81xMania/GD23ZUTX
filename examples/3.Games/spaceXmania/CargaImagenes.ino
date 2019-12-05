void loadImages(int ImagenID)
{
//imagen de fondo y grupo de assets
  LOAD_ASSETS();
  GD.BitmapHandle(15);
  GD.cmd_loadimage(ASSETS_END, 0);
  //GD.load("SW0400.jpg");
  GD.load(GrupoFondo[ImagenID]);
//imagen de fondo y grupo de assets
}
