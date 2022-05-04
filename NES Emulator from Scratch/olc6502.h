#pragma once

class Bus;

class olc6502 //archive.6502.org/datasheets/rockwell_r650x_r651x.pdf
{
public:
	olc6502();
	~olc6502();

public:
	enum FLAGS6502
	{
		C = (1 << 0), // Carry Bit
		Z = (1 << 1), // Zero
		I = (1 << 2), // Disable Interrupts
		D = (1 << 3), // Decimal Mode (unused in this implementation)
		B = (1 << 4), // Break
		U = (1 << 5), // Unused
		V = (1 << 6), // Overflow
		N = (1 << 7), // Negative
	};

	uint8_t a = 0x00; // Accumulator Register
	uint8_t x = 0x00; // X Register
	uint8_t y = 0x00; // Y Register
	uint8_t stkp = 0x00; // Stack Pointer (points to location on bus)
	uint16_t pc = 0x0000; // Program Counter
	uint8_t status = 0x00; // Status Register

	void ConnectBus(Bus* n) { bus = n; }

	// Addressing Modes

	uint8_t IMP();	uint8_t IMM();
	uint8_t ZP0();	uint8_t ZPX();
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();
	uint8_t ABY();	uint8_t IND();
	uint8_t IZX();	uint8_t IZY();

	// Opcodes
	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	uint8_t XXX(); // Ilegal Opcode

	void clock(); // Clock cycles
	void reset(); // Reset Signal
	void irq(); // Interruption Request Signal
	void nmi(); // Non Maskeble Interrupt Signal

	uint8_t fetch(); //Fetch data from a source
	uint8_t fetched = 0x00; // Where we save de fetched data

	uint16_t addr_abs = 0x0000; // To store location of a memory
	uint16_t addr_rel = 0x00; // To save relative address, on 6502 branch intrucctions only jumps 
							  // certain distance from the location the where call
							  // they jump to a relative address, so we store it
	uint8_t opcode = 0x00; // To store the opcode
	uint8_t cycles = 0; // Number of cycles left for the current intruction

private:
	Bus* bus = nullptr;
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);

	// Funcions to access status register
	uint8_t GetFlag(FLAGS6502 f);
	void SetFlag(FLAGS6502, bool v);

	struct INSTRUCTION //Contatins the data of the current instrucction
	{
		std::string name; // Name of the instruction
		uint8_t(olc6502::*operate)(void) = nullptr; // Pointer to the operation to be performed
		uint8_t(olc6502::*addrmode)(void) = nullptr; // Pointer to the address mode
		uint8_t cycles = 0; // Number of clock cycles to exectue
	};

	std::vector<INSTRUCTION> lookup; // the vector of all instructions

};

