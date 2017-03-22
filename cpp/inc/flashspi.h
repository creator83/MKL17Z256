#include "MKL17Z4.h"
#include "pin.h"
#include "spi.h"
#include "delay.h"

#ifndef FLASHSPI_H
#define FLASHSPI_H

const uint8_t WriteEnable = 0x06;
const uint8_t WriteDisable = 0x04;
const uint8_t ReadStatusReg = 0x05;
const uint8_t WriteStatusReg = 0x01;
const uint8_t ReadData = 0x03;
const uint8_t FastReadData = 0x0B;
const uint8_t FastReadDual = 0x3B;
const uint8_t PageProgram = 0x02;
const uint8_t BlockErase = 0xD8;
const uint8_t SectorErase = 0x20;
const uint8_t ChipErase = 0xC7;
const uint8_t PowerDown = 0xB9;
const uint8_t ReleasePowerDown = 0xAB;
const uint8_t DeviceID = 0xAB;
const uint8_t ManufactDeviceID = 0x90;
const uint8_t JedecDeviceID = 0x9F;

class Flash
{
private:
  Spi * driver;
  Pin cs;
  uint16_t deviceId;
  uint8_t manufacturId;

public:

  Flash (Spi &, Gpio::Port p, uint8_t pin);
  void writeByte (uint8_t);
  void writePage (uint8_t * buffer, uint32_t addr, uint16_t n);
  void write (uint8_t * buffer, uint32_t addr, uint16_t n);
  void readID ();
  uint16_t readStatus ();
  void writeStatus (uint8_t);
  void writeEnable ();
  void writeDisable ();
  void read (uint8_t * buffer, uint32_t addr, uint16_t n);
  void eraseSector (uint32_t addr);
  void eraseChip ();
  bool flagBusy ();

  void powerDown ();
  void powerUp ();
  void getCapacity ();



};


#endif
