#pragma once
#include "Mapper.h"

class Mapper_000 : public Mapper //Polimorfismo y Herencias
{
// We dereive the Mapper Class becasuse each Mapper can have different rules, register or methods/implementations
// There are many kinds of Mappers https://www.nesdev.org/wiki/Mapper
	Mapper_000();
	~Mapper_000();

public: 
	bool cpuMapRead(uint16_t addr, uint32_t& mapped_addr) override; // Sobreescribimos el metodo virtualizado en la clase Mapper
	bool cpuMapWrite(uint16_t addr, uint32_t& mapped_addr) override; // añadirmos override al final para indicarlo
	bool ppuMapRead(uint16_t addr, uint32_t& mapped_addr) override; // y eliminamos la palabra "virtual" de la función
	bool ppuMapWrite(uint16_t addr, uint32_t& mapped_addr) override;
};