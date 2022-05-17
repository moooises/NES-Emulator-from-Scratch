#pragma once
#include <cstdint>
#include <array>

#include "olc6502.h"
#include "olc2C02.h"
#include "Cartridge.h"

class Bus
{
public: 
	Bus();
	~Bus();

public: //Devices on Bus
	olc6502 cpu;

	// The 2C02 Picture Processing Unit
	olc2C02 ppu;

	//Fake RAM 
	std::array<uint8_t, 2048> cpuRam;

	// The Cartridge or "GamePak"
	std::shared_ptr<Cartridge> cart;

public: //Bus Read & Write
	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

public: //System Interface
	void insertCartridge(const std::shared_ptr<Cartridge>& cartridge); // Load the cartrige in memory before inserting it into the NES
	void reset(); 
	void clock(); // Perform 1 system tick of the emulation

private:
	// A count of how many clocks have passed
	uint32_t nSystemClockCounter = 0;
};

