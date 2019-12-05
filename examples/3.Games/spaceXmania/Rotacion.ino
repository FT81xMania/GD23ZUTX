static void rotate_Center(float a, int CXY)
{
  GD.cmd_translate(F16(CXY),F16(CXY));
  GD.cmd_rotate(a);
  GD.cmd_translate(F16(-CXY), F16(-CXY));
}
