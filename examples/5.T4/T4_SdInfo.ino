/*
 * This program attempts to initialize an SD card and analyze its structure.
 */

#include <GD23ZUTX.h>
char LoadTime[40], Interface[40];
uint32_t startJPG=0, endJPG=0, drawT=0;
 
#include "SdFat.h"
#include "sdios.h"

int Test=1;

/*
  Set DISABLE_CS_PIN to disable a second SPI device.
  For example, with the Ethernet shield, set DISABLE_CS_PIN
  to 10 to disable the Ethernet controller.
*/
const int8_t DISABLE_CS_PIN = -1;
/*
  Change the value of SD_CS_PIN if you are using SPI
  and your hardware does not use the default value, SS.
  Common values are:
  Arduino Ethernet shield: pin 4
  Sparkfun SD shield: pin 8
  Adafruit SD shields and modules: pin 10
*/
// SDCARD_SS_PIN is defined for the built-in SD on some boards.
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif  // SDCARD_SS_PIN

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16))
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SD_SCK_MHZ(16))
#endif  // HAS_SDIO_CLASS

//------------------------------------------------------------------------------
SdFs sd;
cid_t m_cid;
csd_t m_csd;
uint32_t m_eraseSize;
uint32_t m_ocr;
static ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
bool cidDmp() {
  cout << F("\nManufacturer ID: ");
  cout << uppercase << showbase << hex << int(m_cid.mid) << dec << endl;
  cout << F("OEM ID: ") << m_cid.oid[0] << m_cid.oid[1] << endl;
  cout << F("Product: ");
  for (uint8_t i = 0; i < 5; i++) {
    cout << m_cid.pnm[i];
  }
  cout << F("\nVersion: ");
  cout << int(m_cid.prv_n) << '.' << int(m_cid.prv_m) << endl;
  cout << F("Serial number: ") << hex << m_cid.psn << dec << endl;
  cout << F("Manufacturing date: ");
  cout << int(m_cid.mdt_month) << '/';
  cout << (2000 + m_cid.mdt_year_low + 10 * m_cid.mdt_year_high) << endl;
  cout << endl;
  return true;
}
//------------------------------------------------------------------------------
bool csdDmp() {
  bool eraseSingleBlock;
  if (m_csd.v1.csd_ver == 0) {
    eraseSingleBlock = m_csd.v1.erase_blk_en;
    m_eraseSize = (m_csd.v1.sector_size_high << 1) | m_csd.v1.sector_size_low;
  } else if (m_csd.v2.csd_ver == 1) {
    eraseSingleBlock = m_csd.v2.erase_blk_en;
    m_eraseSize = (m_csd.v2.sector_size_high << 1) | m_csd.v2.sector_size_low;
  } else {
    cout << F("m_csd version error\n");
    return false;
  }
  m_eraseSize++;
  cout << F("cardSize: ") << 0.000512 * sdCardCapacity(&m_csd);
  cout << F(" MB (MB = 1,000,000 bytes)\n");

  cout << F("flashEraseSize: ") << int(m_eraseSize) << F(" blocks\n");
  cout << F("eraseSingleBlock: ");
  if (eraseSingleBlock) {
    cout << F("true\n");
  } else {
    cout << F("false\n");
  }
  return true;
}
//------------------------------------------------------------------------------
void errorPrint() {
  if (sd.sdErrorCode()) {
    cout << F("SD errorCode: ") << hex << showbase;
    printSdErrorSymbol(&Serial, sd.sdErrorCode());
    cout << F(" = ") << int(sd.sdErrorCode()) << endl;
    cout << F("SD errorData = ") << int(sd.sdErrorData()) << endl;
  }
}
//------------------------------------------------------------------------------
bool mbrDmp() {
  MbrSector_t mbr;
  bool valid = true;
  if (!sd.card()->readSector(0, (uint8_t*)&mbr)) {
    cout << F("\nread MBR failed.\n");
    errorPrint();
    return false;
  }
  cout << F("\nSD Partition Table\n");
  cout << F("part,boot,bgnCHS[3],type,endCHS[3],start,length\n");
  for (uint8_t ip = 1; ip < 5; ip++) {
    MbrPart_t *pt = &mbr.part[ip - 1];
    if ((pt->boot != 0 && pt->boot != 0X80) ||
        getLe32(pt->relativeSectors) > sdCardCapacity(&m_csd)) {
      valid = false;
    }
    cout << int(ip) << ',' << uppercase << showbase << hex;
    cout << int(pt->boot) << ',';
    for (int i = 0; i < 3; i++ ) {
      cout << int(pt->beginCHS[i]) << ',';
    }
    cout << int(pt->type) << ',';
    for (int i = 0; i < 3; i++ ) {
      cout << int(pt->endCHS[i]) << ',';
    }
    cout << dec << getLe32(pt->relativeSectors) << ',';
    cout << getLe32(pt->totalSectors) << endl;
  }
  if (!valid) {
    cout << F("\nMBR not valid, assuming Super Floppy format.\n");
  }
  return true;
}
//------------------------------------------------------------------------------
void dmpVol() {
  cout << F("\nScanning FAT, please wait.\n");
  uint32_t freeClusterCount = sd.freeClusterCount();
  if (sd.fatType() <= 32) {
    cout << F("\nVolume is FAT") << int(sd.fatType()) << endl;
  } else {
    cout << F("\nVolume is exFAT\n");
  }
  cout << F("sectorsPerCluster: ") << sd.sectorsPerCluster() << endl;
  cout << F("clusterCount:      ") << sd.clusterCount() << endl;
  cout << F("freeClusterCount:  ") << freeClusterCount << endl;
  cout << F("fatStartSector:    ") << sd.fatStartSector() << endl;
  cout << F("dataStartSector:   ") << sd.dataStartSector() << endl;

  Test=0;
  
  if (sd.dataStartSector() % m_eraseSize) {
    cout << F("Data area is not aligned on flash erase boundary!\n");
    cout << F("Download and use formatter from www.sdcard.org!\n");
  }
}
//------------------------------------------------------------------------------
void printCardType() {

  cout << F("\nCard type: ");

  switch (sd.card()->type()) {
    case SD_CARD_TYPE_SD1:
      cout << F("SD1\n");
      break;

    case SD_CARD_TYPE_SD2:
      cout << F("SD2\n");
      break;

    case SD_CARD_TYPE_SDHC:
      if (sdCardCapacity(&m_csd) < 70000000) {
        cout << F("SDHC\n");
      } else {
        cout << F("SDXC\n");
      }
      break;

    default:
      cout << F("Unknown\n");
  }
}
//------------------------------------------------------------------------------
void printConfig(SdSpiConfig config) {
  if (DISABLE_CS_PIN < 0) {
    cout << F(
           "\nAssuming the SD is the only SPI device.\n"
           "Edit DISABLE_CS_PIN to disable an SPI device.\n");
  } else {
    cout << F("\nDisabling SPI device on pin ");
    cout << int(DISABLE_CS_PIN) << endl;
    pinMode(DISABLE_CS_PIN, OUTPUT);
    digitalWrite(DISABLE_CS_PIN, HIGH);
  }
  cout << F("\nAssuming the SD chip select pin is: ") << int(config.csPin);
  cout << F("\nEdit SD_CS_PIN to change the SD chip select pin.\n");
}
//------------------------------------------------------------------------------
void printConfig(SdioConfig config) {
  (void)config;
  cout << F("Assuming an SDIO interface.\n");
  sprintf(Interface, "SDIO interface.");
}
//-----------------------------------------------------------------------------
void setup() {

  GD.begin();

  GD.Clear();
  startJPG = millis();
   GD.cmd_loadimage(0, 0);
   GD.load("FondoX01.jpg");
  endJPG = millis();
  drawT=endJPG-startJPG;
  sprintf(LoadTime, "JPG load time: %d millis", drawT);
 
  GD.SaveContext();
    GD.Begin(BITMAPS);
    GD.Vertex2f(0*16, 0*16);
  GD.RestoreContext();

  GD.SaveContext();
   GD.ColorRGB(0xff,0xff,0x00);
   GD.cmd_text(55, 30, 20, OPT_CENTER, LoadTime);

   sprintf(LoadTime, "SdInfo test...");
   GD.cmd_text(60, 15, 28, OPT_CENTER, LoadTime);
   GD.cmd_number(10, GD.h-35, 30, 0, Test);
  GD.RestoreContext();
  GD.swap();
  
  Serial.begin(9600);
  // Wait for USB Serial
  //while (!Serial) {
  //  SysCall::yield();
  //}
  cout << F("SdFat version: ") << SD_FAT_VERSION << endl;
  printConfig(SD_CONFIG);

}
//------------------------------------------------------------------------------
void loop() {
  // Read any existing Serial data.
//  do {
//    delay(10);
//  } while (Serial.available() && Serial.read() >= 0);

  // F stores strings in flash to save RAM
//  cout << F("\ntype any character to start\n");
//  while (!Serial.available()) {
//    SysCall::yield();
//  }

if (Test==1)  
{
  
  uint32_t t = millis();
  if (!sd.cardBegin(SD_CONFIG)) {
    cout << F(
           "\nSD initialization failed.\n"
           "Do not reformat the card!\n"
           "Is the card correctly inserted?\n"
           "Is there a wiring/soldering problem?\n");
    if (isSpi(SD_CONFIG)) {
      cout << F(
           "Is SD_CS_PIN set to the correct value?\n"
           "Does another SPI device need to be disabled?\n"
           );
    }
    errorPrint();
    return;
  }
  t = millis() - t;
  cout << F("init time: ") << t << " ms" << endl;

  if (!sd.card()->readCID(&m_cid) ||
      !sd.card()->readCSD(&m_csd) ||
      !sd.card()->readOCR(&m_ocr)) {
    cout << F("readInfo failed\n");
    errorPrint();
    return;
  }
  printCardType();
  cidDmp();
  csdDmp();
  cout << F("\nOCR: ") << uppercase << showbase;
  cout << hex << m_ocr << dec << endl;
  if (!mbrDmp()) {
    return;
  }
  if (!sd.volumeBegin()) {
    cout << F("\nvolumeBegin failed. Is the card formatted?\n");
    errorPrint();
    return;
  }
  dmpVol();
}

  GD.ClearColorRGB(0x000025); //fondo de pantalla
  GD.Clear();

  GD.SaveContext();
    GD.Begin(BITMAPS);
    GD.Vertex2f(0*16, 0*16);
  GD.RestoreContext();

   GD.ColorRGB(0xffffff);  GD.cmd_text(10, 5, 18, 0,"SdFat version: ");
   GD.ColorRGB(0x00ff00);  GD.cmd_text(130, 5, 18, 0, SD_FAT_VERSION);  
   
   GD.ColorRGB(0xffffff);  GD.cmd_text(10, 20, 18, 0, "SD card is present.");  GD.cmd_text(168, 20, 18, 0,Interface);
   GD.cmd_text(10, 43, 18, 0, "Card size(MB): ");
   GD.ColorRGB(0xff,0xff,0x00);
   
   GD.cmd_number(150, 50, 18, OPT_CENTER, 0.000512 * sdCardCapacity(&m_csd));

              //GD.cmd_text(170, 50, 18, 0, "Free space(MB):"); GD.cmd_number(255+25+35, 58, 18, OPT_CENTER, fs);
              //GD.cmd_text(170, 65, 18, 0, "Used space(MB):"); GD.cmd_number(255+25+35, 73, 18, OPT_CENTER, 0.000512*cardSize-fs);
  GD.cmd_number(10, GD.h-35, 30, 0, Test);
  GD.swap();
}
