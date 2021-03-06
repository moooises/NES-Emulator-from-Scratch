#pragma once
#include<cstdint>

class Mapper // abstract base class
{
public:
	Mapper(uint8_t prgBanks, uint8_t chrBanks);
	virtual ~Mapper();

public:
	// Transform CPU bus address into PRG ROM offset
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0; // The =0 means, that the fuction needs to be overwritten in a subclass
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0; // It means that these functions are pure virtual  
	// Transform PPU bus address into CHR ROM offset
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) = 0; // and cant be defined in the parent class, cannot be instantiated,   
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) = 0; 

protected:
	// These are stored locally as many of the mappers require this information
	uint8_t nPRGBanks = 0;
	uint8_t nCHRBanks = 0;
};