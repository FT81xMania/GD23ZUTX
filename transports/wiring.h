class GDTransport {
private:
  byte model;

public:
void begin0() {


#if (SizeFT813==35)
    //por(); // Funcion ON the POWER ON RESET by @lightcalamar
    pinMode(POR_INT, OUTPUT);
    pinMode(POR_PIN, OUTPUT);       // CONTROL P.O.R. Power On Reset

    digitalWrite(POR_INT, HIGH);
    digitalWrite(POR_PIN, HIGH);    // Pantalla FT81x comprada
    delay(100);                     // en http://HotMCU.com
    digitalWrite(POR_INT, LOW);
    digitalWrite(POR_PIN, LOW);     //           |
    delay(100);                     //           |
    digitalWrite(POR_INT, HIGH);    
    digitalWrite(POR_PIN, HIGH);    //           |
    delay(100);
#endif

#if (SizeFT813==52)
    //por(); // Funcion ON the POWER ON RESET by @lightcalamar
    pinMode(POR_INT, OUTPUT);
    pinMode(POR_PIN, OUTPUT);       // CONTROL P.O.R. Power On Reset

    digitalWrite(POR_INT, HIGH);
    digitalWrite(POR_PIN, HIGH);    // Pantalla FT81x comprada
    delay(100);                     // en http://HotMCU.com
    digitalWrite(POR_INT, LOW);
    digitalWrite(POR_PIN, LOW);     //           |
    delay(100);                     //           |
    digitalWrite(POR_INT, HIGH);    
    digitalWrite(POR_PIN, HIGH);    //           |
    delay(100);
#endif
    //ios();
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);

    SPI.begin();

//test zone
    //SPI.beginTransaction(SPISettings(36000000, MSBFIRST, SPI_MODE0));  //SPI1  36.0 MHz
    //SPI.beginTransaction(SPISettings(10500000, MSBFIRST, SPI_MODE0));  //SPI1  10.5 MHz
    //SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));  //SPI1    5.0 MHz
    //SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));  //SPI1    8.0 MHz
    //SPI.beginTransaction(SPISettings(18000000, MSBFIRST, SPI_MODE0));  //SPI1  18.0 MHz
    //SPI.beginTransaction(SPISettings(28000000, MSBFIRST, SPI_MODE0));  //SPI1  28.0 MHz
    //SPI.beginTransaction(SPISettings(48000000, MSBFIRST, SPI_MODE0));  //SPI1  48.0 MHz, unestable
//test zone

    SPI.beginTransaction(SPISettings(45000000, MSBFIRST, SPI_MODE0));  //SPI1  45.0 MHz, stable

#if (SizeFT813==51)
    SPI.beginTransaction(SPISettings(SetSPISpeed, MSBFIRST, SPI_MODE0));  //SPI1 to SetSPISpeed, Riverdi TFT
#endif


    hostcmd(0x00);
#if 0
    hostcmd(0x44); // from external crystal
#endif
    hostcmd(0x68);
  }



uint16_t begin1() {
    while ((__rd16(0xc0000UL) & 0xff) != 0x08)
      ;
    // Test point: saturate SPI
    while (0) {
      digitalWrite(TFT_CS, LOW);
      SPI.transfer(0x55);
      digitalWrite(TFT_CS, HIGH);
    }

    // So that FT800,801      FT81x
    // model       0            1
    uint16_t __model = __rd16(0x0c0000);  

    ft8xx_model = __rd16(0x0c0000) >> 12;  

    wp = 0;
    freespace = 4096 - 4;

    stream();
    return (__model >> 8);
  }

void cmd32(uint32_t x) {
    if (freespace < 4) {
      getfree(4);
    }
    wp += 4;
    freespace -= 4;
    union {
      uint32_t c;
      uint8_t b[4];
    };
    c = x;
    SPI.transfer(b[0]);
    SPI.transfer(b[1]);
    SPI.transfer(b[2]);
    SPI.transfer(b[3]);
  }

void cmdbyte(byte x) {
    if (freespace == 0) {
      getfree(1);
    }
    wp++;
    freespace--;
    SPI.transfer(x);
  }
  void cmd_n(byte *s, uint16_t n) {
    if (freespace < n) {
      getfree(n);
    }
    wp += n;
    freespace -= n;
    while (n > 8) {
      n -= 8;
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
      SPI.transfer(*s++);
    }
    while (n--)
      SPI.transfer(*s++);
  }

  void flush() {
    getfree(0);
  }
  uint16_t rp() {
    uint16_t r = __rd16(REG_CMD_READ);
    if (r == 0xfff) {
      GD.alert("COPROCESSOR EXCEPTION");
    }
    return r;
  }
  void finish() {
    wp &= 0xffc;
    __end();
    __wr16(REG_CMD_WRITE, wp);
    while (rp() != wp)
      ;
    stream();
  }

  byte rd(uint32_t addr)
  {
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);  // dummy
    byte r = SPI.transfer(0);
    stream();
    return r;
  }

  void wr(uint32_t addr, byte v)
  {
    __end(); // stop streaming
    __wstart(addr);
    SPI.transfer(v);
    stream();
  }

  uint16_t rd16(uint32_t addr)
  {
    uint16_t r = 0;
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    r = SPI.transfer(0);
    r |= (SPI.transfer(0) << 8);
    stream();
    return r;
  }

  void wr16(uint32_t addr, uint32_t v)
  {
    __end(); // stop streaming
    __wstart(addr);
    SPI.transfer(v);
    SPI.transfer(v >> 8);
    stream();
  }

  uint32_t rd32(uint32_t addr)
  {
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    union {
      uint32_t c;
      uint8_t b[4];
    };
    b[0] = SPI.transfer(0);
    b[1] = SPI.transfer(0);
    b[2] = SPI.transfer(0);
    b[3] = SPI.transfer(0);
    stream();
    return c;
  }
  void rd_n(byte *dst, uint32_t addr, uint16_t n)
  {
    __end(); // stop streaming
    __start(addr);
    SPI.transfer(0);
    while (n--)
      *dst++ = SPI.transfer(0);
    stream();
  }

#if 0

#if defined(ARDUINO) && !defined(__DUE__)
  void wr_n(uint32_t addr, byte *src, uint16_t n)
  {
    __end(); // stop streaming
    __wstart(addr);
    while (n--) {
      //SPDR = *src++;
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
    }
    //while (!(SPSR & _BV(SPIF))) ;
    stream();
  }
#endif

#endif

  void wr_n(uint32_t addr, byte *src, uint16_t n)
  {
    __end(); // stop streaming
    __wstart(addr);
    while (n--)
      SPI.transfer(*src++);
    stream();
  }



  void wr32(uint32_t addr, unsigned long v)
  {
    __end(); // stop streaming
    __wstart(addr);
    SPI.transfer(v);
    SPI.transfer(v >> 8);
    SPI.transfer(v >> 16);
    SPI.transfer(v >> 24);
    stream();
  }

  uint32_t getwp(void) {
    return RAM_CMD + (wp & 0xffc);
  }

  void bulk(uint32_t addr) {
    __end(); // stop streaming
    __start(addr);
  }
  void resume(void) {
    stream();
  }

  static void __start(uint32_t addr) // start an SPI transaction to addr
  {
    digitalWrite(TFT_CS, LOW);
    SPI.transfer(addr >> 16);
    SPI.transfer(highByte(addr));
    SPI.transfer(lowByte(addr));  
  }

  static void __wstart(uint32_t addr) // start an SPI write transaction to addr
  {
    digitalWrite(TFT_CS, LOW);
    SPI.transfer(0x80 | (addr >> 16));
    SPI.transfer(highByte(addr));
    SPI.transfer(lowByte(addr));  
  }

  static void __end() // end the SPI transaction
  {
    digitalWrite(TFT_CS, HIGH);
  }

  void stop() // end the SPI transaction
  {
    wp &= 0xffc;
    __end();
    __wr16(REG_CMD_WRITE, wp);
  }

  void stream(void) {
    __end();
    __wstart(RAM_CMD + (wp & 0xfff));
  }

  static unsigned int __rd16(uint32_t addr)
  {
    unsigned int r;

    __start(addr);
    SPI.transfer(0);  // dummy
    r = SPI.transfer(0);
    r |= (SPI.transfer(0) << 8);
    __end();
    return r;
  }

  static uint32_t __rd32(uint32_t addr)
  {
    __start(addr);
    SPI.transfer(0);
    union {
      uint32_t c;
      uint8_t b[4];
    };
    b[0] = SPI.transfer(0);
    b[1] = SPI.transfer(0);
    b[2] = SPI.transfer(0);
    b[3] = SPI.transfer(0);
    __end(); // stop streaming
    return c;
  }

  static void __wr16(uint32_t addr, unsigned int v)
  {
    __wstart(addr);
    SPI.transfer(lowByte(v));
    SPI.transfer(highByte(v));
    __end();
  }

  static void hostcmd(byte a)
  {
    digitalWrite(TFT_CS, LOW);
    SPI.transfer(a);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    digitalWrite(TFT_CS, HIGH);
  }

  void getfree(uint16_t n)
  {
    wp &= 0xfff;
    __end();
    __wr16(REG_CMD_WRITE, wp & 0xffc);
    do {
      uint16_t fullness = (wp - rp()) & 4095;
      freespace = (4096 - 4) - fullness;
    } while (freespace < n);
    stream();
  }

  byte streaming;
  uint16_t wp;
  uint16_t freespace;
};
