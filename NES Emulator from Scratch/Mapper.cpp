#include "Mapper.h"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
	nPRGBanks = prgBanks;
	nCHRBanks = chrBanks;
}

Mapper::~Mapper()
{
}

// THis is an abstract class, so there aren't anything else to implement
