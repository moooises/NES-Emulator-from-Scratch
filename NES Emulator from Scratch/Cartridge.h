#pragma once
#include<cstdint>
#include<vector>
#include<fstream>
#include<string>

#include "Mapper_000.h"

class Cartridge
{
public:
	Cartridge(const std::string& sFileName); // path to the file/Rom/.Nes
	~Cartridge();

private:
	std::vector<uint8_t> vPRGMemory; // The program of the cartridge
	std::vector<uint8_t> vCHRMemory; // The Patter/Assets of the cartridge

	uint8_t nMapperID = 0; // What Mapper are we using
	uint8_t nPRGBanks = 0; // The banks of memory that we are using
	uint8_t nCHRBanks = 0; // ''

	std::shared_ptr<Mapper> pMapper;

public: 
	// Communications with Main Bus
	bool cpuRead(uint16_t addr, uint8_t &data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	// Communications with PPU Bus
	bool ppuRead(uint16_t addr, uint8_t &data);
	bool ppuWrite(uint16_t addr, uint8_t data);
};