char TXP[50];

void Parametros()
{
  GD.SaveContext();
  
  GD.ColorRGB(0x00ff00);

  GD.cmd_text(GD.w-283, (GD.h)-20, 20, OPT_CENTER, Board);
  sprintf(TXP,"F_CPU: %d MHz", (F_CPU/1000000));  GD.cmd_text(GD.w-43, (GD.h)-20, 20, OPT_CENTER, TXP);

  #if defined(ARDUINO_ARCH_STM32)  
  if(GD.model==815){
  sprintf(TXP,"EVE chip: BT%d ", GD.model);  GD.cmd_text(GD.w-85, (GD.h)-15, 20, 0, TXP);}else{
  sprintf(TXP,"EVE chip: FT%d ", GD.model);  GD.cmd_text(GD.w-85, (GD.h)-15, 20, 0, TXP);  
  }
  #endif
  
  if(SizeFT813==35){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: FT813@NHD-3.5-320240FT-CSXN-CTP");}
  if(SizeFT813==43){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: FT813@NHD-4.3-480272FT-CSXN-CTP");}
  if(SizeFT813==5){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: FT813@NHD-5.0-800480FT-CTXL-CTP");}
  if(SizeFT813==7){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: FT813@NHD-7.0-800480FT-CSXN-CTP");}
  if(SizeFT813==51){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: FT813@Riverdi RVT50UQFNWC000");}
  if(SizeFT813==71){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: FT813@Riverdi RVT70UQFNWC000");}
  if(SizeFT813==52){GD.cmd_text(GD.w-350, (GD.h)-15, 20, 0, "EVE chip: BT815@Matrix Orbital EVE3-50G");}
  
  
  GD.RestoreContext();
}
