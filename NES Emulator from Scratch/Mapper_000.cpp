#include "Mapper_000.h"

Mapper_000::Mapper_000(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{

}

Mapper_000::~Mapper_000()
{

}

bool Mapper_000::cpuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF); // If the bank is 2, we change the last 16 bits of the address in PRG Memory
		return true;											// The last 16 bits, because the Memory is mirrored
	}
	return false;
}

bool Mapper_000::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		mapped_addr = addr & (nPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		mapped_addr = addr; // The are is no bank switching in the ppu
		return true;
	}
	return false;
}

bool Mapper_000::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		if (nCHRBanks == 0)
		{
			// Treat as RAM
			mapped_addr = addr;
			return true;
		}
	}

	return false;

	// We can't write to a ROM

	/*if (addr >= 0x0000 && addr <= 0x1FFF) 
	{

		return true;
	}*/
	// return false;
	// Sometimes, Cartridge can have RAM, so it is important to declare this funcion in the parent class Mapper
}
