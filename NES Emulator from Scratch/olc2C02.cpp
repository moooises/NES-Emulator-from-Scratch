#include "olc2C02.h"

olc2C02::olc2C02()
{
	// Paletter entries

	palScreen[0x00] = olc::Pixel(84, 84, 84);
	palScreen[0x01] = olc::Pixel(0, 30, 116);
	palScreen[0x02] = olc::Pixel(8, 16, 144);
	palScreen[0x03] = olc::Pixel(48, 0, 136);
	palScreen[0x04] = olc::Pixel(68, 0, 100);
	palScreen[0x05] = olc::Pixel(92, 0, 48);
	palScreen[0x06] = olc::Pixel(84, 4, 0);
	palScreen[0x07] = olc::Pixel(60, 24, 0);
	palScreen[0x08] = olc::Pixel(32, 42, 0);
	palScreen[0x09] = olc::Pixel(8, 58, 0);
	palScreen[0x0A] = olc::Pixel(0, 64, 0);
	palScreen[0x0B] = olc::Pixel(0, 60, 0);
	palScreen[0x0C] = olc::Pixel(0, 50, 60);
	palScreen[0x0D] = olc::Pixel(0, 0, 0);
	palScreen[0x0E] = olc::Pixel(0, 0, 0);
	palScreen[0x0F] = olc::Pixel(0, 0, 0);

	palScreen[0x10] = olc::Pixel(152, 150, 152);
	palScreen[0x11] = olc::Pixel(8, 76, 196);
	palScreen[0x12] = olc::Pixel(48, 50, 236);
	palScreen[0x13] = olc::Pixel(92, 30, 228);
	palScreen[0x14] = olc::Pixel(136, 20, 176);
	palScreen[0x15] = olc::Pixel(160, 20, 100);
	palScreen[0x16] = olc::Pixel(152, 34, 32);
	palScreen[0x17] = olc::Pixel(120, 60, 0);
	palScreen[0x18] = olc::Pixel(84, 90, 0);
	palScreen[0x19] = olc::Pixel(40, 114, 0);
	palScreen[0x1A] = olc::Pixel(8, 124, 0);
	palScreen[0x1B] = olc::Pixel(0, 118, 40);
	palScreen[0x1C] = olc::Pixel(0, 102, 120);
	palScreen[0x1D] = olc::Pixel(0, 0, 0);
	palScreen[0x1E] = olc::Pixel(0, 0, 0);
	palScreen[0x1F] = olc::Pixel(0, 0, 0);

	palScreen[0x20] = olc::Pixel(236, 238, 236);
	palScreen[0x21] = olc::Pixel(76, 154, 236);
	palScreen[0x22] = olc::Pixel(120, 124, 236);
	palScreen[0x23] = olc::Pixel(176, 98, 236);
	palScreen[0x24] = olc::Pixel(228, 84, 236);
	palScreen[0x25] = olc::Pixel(236, 88, 180);
	palScreen[0x26] = olc::Pixel(236, 106, 100);
	palScreen[0x27] = olc::Pixel(212, 136, 32);
	palScreen[0x28] = olc::Pixel(160, 170, 0);
	palScreen[0x29] = olc::Pixel(116, 196, 0);
	palScreen[0x2A] = olc::Pixel(76, 208, 32);
	palScreen[0x2B] = olc::Pixel(56, 204, 108);
	palScreen[0x2C] = olc::Pixel(56, 180, 204);
	palScreen[0x2D] = olc::Pixel(60, 60, 60);
	palScreen[0x2E] = olc::Pixel(0, 0, 0);
	palScreen[0x2F] = olc::Pixel(0, 0, 0);

	palScreen[0x30] = olc::Pixel(236, 238, 236);
	palScreen[0x31] = olc::Pixel(168, 204, 236);
	palScreen[0x32] = olc::Pixel(188, 188, 236);
	palScreen[0x33] = olc::Pixel(212, 178, 236);
	palScreen[0x34] = olc::Pixel(236, 174, 236);
	palScreen[0x35] = olc::Pixel(236, 174, 212);
	palScreen[0x36] = olc::Pixel(236, 180, 176);
	palScreen[0x37] = olc::Pixel(228, 196, 144);
	palScreen[0x38] = olc::Pixel(204, 210, 120);
	palScreen[0x39] = olc::Pixel(180, 222, 120);
	palScreen[0x3A] = olc::Pixel(168, 226, 144);
	palScreen[0x3B] = olc::Pixel(152, 226, 180);
	palScreen[0x3C] = olc::Pixel(160, 214, 228);
	palScreen[0x3D] = olc::Pixel(160, 162, 160);
	palScreen[0x3E] = olc::Pixel(0, 0, 0);
	palScreen[0x3F] = olc::Pixel(0, 0, 0);
}

olc2C02::~olc2C02()
{
}

olc::Sprite& olc2C02::GetScreen()
{
	return sprScreen;
}

olc::Sprite& olc2C02::GetNameTable(uint8_t i)
{
	return sprNameTable[i];
}

olc::Sprite& olc2C02::GetPatternTable(uint8_t i, uint8_t palette)
{
	for (uint16_t nTileY = 0; nTileY < 16; nTileY++)
	{
		for (uint16_t nTileX = 0; nTileX < 16; nTileX++)
		{
			// Convert the 2D tile coordinate into a 1D offset into the pattern
			// table memory. Y*widthY +X*widthX
			uint16_t nOffSet = nTileY * 256 + nTileX * 16; // Each tile has 16 bytes, each patter row has 16 tiles of them, 16*16 = 256 

			// Each tile has 8 rows of 8 pixels
			for (uint16_t row = 0; row < 8; row++)
			{
				// To read from Patter memory
				// In the CHR ROM, each character
				// is stored as 64 bits of lsb, followed by 64 bits of msb. This
				// conveniently means that two corresponding rows are always 8
				// bytes apart in memory.

				uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffSet + row + 0x0000); // Read the lest significant bit plane 
				uint8_t tile_msb = ppuRead(i * 0x1000 + nOffSet + row + 0x0008); // +8 to access msb plane

				for (uint16_t col = 0; col < 8; col++)
				{
					// We combien both byte to the get the bitmap colour
					uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01); // Only the lsb of each byte
					tile_lsb >>= 1; tile_msb >>= 1;

					// We draw that pixel value into the sprite 
					sprPatternTable[i].SetPixel
					(

						nTileX * 8 + (7 - col),						// Because we are using the lsb of the row word first
						nTileY * 8 + row,							// we are effectively reading the row from right
						GetColourFromPaletteRam(palette, pixel)	// to left, so we need to draw the row "backwards"

					);
				}
			}

		}
	}

	return sprPatternTable[i];
}

olc::Pixel& olc2C02::GetColourFromPaletteRam(uint8_t palette, uint8_t pixel)
{
	// This is a convenience function that takes a specified palette and pixel
	// index and returns the appropriate screen colour.
	// "0x3F00"       - Offset into PPU addressable range where palettes are stored
	// "palette << 2" - Each palette is 4 bytes in size
	// "pixel"        - Each pixel index is either 0, 1, 2 or 3
	// "& 0x3F"       - Stops us reading beyond the bounds of the palScreen array
	return palScreen[ppuRead(0x3F00 + (palette << 2) + pixel) & 0x3F];

	// Note: We dont access tblPalette directly here, instead we know that ppuRead()
	// will map the address onto the seperate small RAM attached to the PPU bus.
}

uint8_t olc2C02::cpuRead(uint16_t addr, bool rdonly)
{
	uint8_t data = 0x00;

	if (rdonly)
	{
		// Reading from PPU registers can affect their contents
		// so this read only option is used for examining the
		// state of the PPU without changing its state. This is
		// really only used in debug mode.
		switch (addr)
		{
		case 0x0000: // Control
			data = control.reg;
			break;
		case 0x0001: // Mask
			data = mask.reg;
			break;
		case 0x0002: // Status
			data = status.reg;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
		}
	}
	else
	{

		switch (addr)
		{
		case 0x0000: // Control
			break;
		case 0x0001: // Mask
			break;
		case 0x0002: // Status
			data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
			status.vertical_blank = 0;
			address_latch = 0;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			data = ppu_data_buffer;
			ppu_data_buffer = ppuRead(vram_addr.reg);

			if (vram_addr.reg > 0x3f00) data = ppu_data_buffer; // Just for palette adresses
			vram_addr.reg += (control.increment_mode ? 32 : 1);
			break;
		}
	}
	return data;
}

void olc2C02::cpuWrite(uint16_t addr, uint8_t data)
{
	switch (addr)
	{
	case 0x0000: // Control
		control.reg = data;
		tram_addr.nametable_x = control.nametable_x;
		tram_addr.nametable_y = control.nametable_y;
		break;
	case 0x0001: // Mask
		mask.reg = data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		if (address_latch == 0)
		{
			fine_x = data & 0x07;
			tram_addr.coarse_x = data >> 3;
			address_latch = 1;
		}
		else
		{
			tram_addr.fine_y = data & 0x07;
			tram_addr.coarse_y = data >> 3;
			address_latch = 0;
		}
		break;
	case 0x0006: // PPU Address
		if (address_latch == 0)
		{
			tram_addr.reg = (uint16_t)((tram_addr.reg & 0x00FF) | ((data & 0x3F) << 8)); // the hight 8 bits of the ppu address
			address_latch = 1;
		}
		else
		{
			tram_addr.reg = (tram_addr.reg & 0xFF00) | data; // the lower 8 bits of the ppu adress
			vram_addr = tram_addr;
			address_latch = 0;
		}
		break;
	case 0x0007: // PPU Data
		ppuWrite(vram_addr.reg, data);
		vram_addr.reg += (control.increment_mode ? 32 : 1);
		break;
	}
}

uint8_t olc2C02::ppuRead(uint16_t addr, bool rdonly)
{
	uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (cart->ppuWrite(addr, data)) 
	{

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF) // Pattern Memory Addresses
	{
		data = tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF]; // The table is decided by MSB of the addr and the position the Offset
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) // Nametable Memory Adresses
	{
		addr &= 0x0FFF;

		if (cart->mirror == Cartridge::MIRROR::VERTICAL)
		{
			// Vertical Nametable mode
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
		else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal Nametable mode
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) // Palette Memory Adresses
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		data = tblPalette[addr] & (mask.grayscale ? 0x30 : 0x3F);
	}

	return data;

}

void olc2C02::ppuWrite(uint16_t addr, uint8_t data)
{
	addr &= 0x3FFF;

	if (cart->ppuWrite(addr, data))
	{

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF) // Pattern Memory Addresses
	{
		// It is usually a ROM, but some games use it as RAM
		tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data; // The table is decided by MSB of the addr and the position the Offset
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) // Nametable Memory Adresses
	{
		if (cart->mirror == Cartridge::MIRROR::VERTICAL)
		{
			// Vertical Nametable mode
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
		else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal Nametable mode
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) // Palette Memory Adresses
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		tblPalette[addr] = data;
	}
}

void olc2C02::ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
}

void olc2C02::reset()
{
	fine_x = 0x00;
	address_latch = 0x00;
	ppu_data_buffer = 0x00;
	scanline = 0;
	cycle = 0;
	bg_next_tile_id = 0x00;
	bg_next_tile_attrib = 0x00;
	bg_next_tile_lsb = 0x00;
	bg_next_tile_msb = 0x00;
	bg_shifter_pattern_lo = 0x0000;
	bg_shifter_pattern_hi = 0x0000;
	bg_shifter_attrib_lo = 0x0000;
	bg_shifter_attrib_hi = 0x0000;
	status.reg = 0x00;
	mask.reg = 0x00;
	control.reg = 0x00;
	vram_addr.reg = 0x0000;
	tram_addr.reg = 0x0000;
}

void olc2C02::clock()
{

	// lambda functions

	auto IncrementScrollX = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			// A name table is 32x30 tiles. 31 is part of the neighbour tile 
			if (vram_addr.coarse_x == 31) // If we go beyond the edge of the nametable
			{
				vram_addr.coarse_x = 0; //  Reset the coarse_x
				vram_addr.nametable_x = ~vram_addr.nametable_x; // And flip targe nametable bit to go to the other nametable
			}
			else // We increase normally, until we go beyond the edge
			{
				vram_addr.coarse_x++;
			}
		}
	};

	auto IncrementScrollY = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			// Scanline are one pixel height, no tiles
			if (vram_addr.fine_y < 7)
			{
				vram_addr.fine_y++;
			}
			else // if we surpass the height of a pixel, we increment the row, taking care of vertical nametables
			{
				vram_addr.fine_y = 0; // Reset fine y offset

				// Check if we need to swap vertical nametable targets
				if (vram_addr.coarse_y == 29) 
				{
					vram_addr.coarse_y = 0;
					vram_addr.nametable_y = ~vram_addr.nametable_y;
				}
				else if (vram_addr.coarse_y == 31) 
				{
					// If pointer is in the attribute memory, we just wrap around the current nametable
					vram_addr.coarse_y = 0;
				}
				else
				{
					// If none of the previous conditions applied, just increase 
					vram_addr.coarse_y++;
				}
			}
		}

	};

	auto TransferAddressX = [&]()
	{
		// Only if rendering is enable
		if (mask.render_background || mask.render_sprites)
		{
			vram_addr.nametable_x = tram_addr.nametable_x;
			vram_addr.coarse_x = tram_addr.coarse_x;
		}

	};

	auto TransferAddressY = [&]()
	{
		// Only if rendering is enable
		if (mask.render_background || mask.render_sprites)
		{
			vram_addr.fine_y = tram_addr.fine_y;
			vram_addr.nametable_y = tram_addr.nametable_y;
			vram_addr.coarse_y = tram_addr.coarse_y;
		}
	};

	// Prepare the shifter to rendering
	auto LoadBackgroudShifters = [&]()
	{
		// we load the whole 8bit word into the botton of the 16 bit shifter
		bg_shifter_pattern_lo = (bg_shifter_pattern_lo & 0xFF00) | bg_next_tile_lsb;
		bg_shifter_pattern_hi = (bg_shifter_pattern_hi & 0xFF00) | bg_next_tile_msb;
		// For the paletter, we take the indiduall binary bit and inflate them to a full 8 bit (0xFF)
		bg_shifter_attrib_lo = (bg_shifter_attrib_lo & 0xFF00) | ((bg_next_tile_attrib & 0b01) ? 0xFF : 0x00);
		bg_shifter_attrib_hi = (bg_shifter_attrib_hi & 0xFF00) | ((bg_next_tile_attrib & 0b10) ? 0xFF : 0x00);

	};

	auto UpdateShifters = [&]()
	{
		if (mask.render_background)
		{
			// Move to the right the pixels and paletes
			bg_shifter_pattern_lo <<= 1;
			bg_shifter_pattern_hi <<= 1;
			bg_shifter_attrib_lo <<= 1;
			bg_shifter_attrib_hi <<= 1;
		}
	};


	if (scanline >= -1 && scanline < 240) // All visible scanlines (horizontal tv lines)
	{
		if (scanline == 0 && cycle == 0)
		{
			cycle = 1;
		}

		if (scanline == -1 && cycle == 1)
		{
			status.vertical_blank = 0;
		}

		if ((cycle >= 2 && cycle < 258) || (cycle >= 321 && cycle < 338)) // (vertical tvlines)
		{
			UpdateShifters();


			// Look at the original source code to understands much better what each case do
			switch ((cycle - 1) % 8) // 8 cycles per tile
			{						 // This is used to preload the ppu with the information to render the next 8 pixels
			case 0:
				LoadBackgroudShifters();
				bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF)); // First read the tile id
				break;
			case 2:
				bg_next_tile_attrib = ppuRead(0x23C0 | (vram_addr.nametable_y << 11) // Then the atribute id
													 | (vram_addr.nametable_x << 10)
													 | ((vram_addr.coarse_y >> 2) << 3)
													 | (vram_addr.coarse_x >> 2));
				if (vram_addr.coarse_y & 0x02) bg_next_tile_attrib >>= 4;
				if (vram_addr.coarse_x & 0x02) bg_next_tile_attrib >>= 2;
				bg_next_tile_attrib &= 0x03;
				break;
			case 4:
				bg_next_tile_lsb = ppuRead((control.pattern_background << 12)
											+ ((uint16_t)bg_next_tile_id << 4)
											+ (vram_addr.fine_y) + 0);
				break;
			case 6:
				bg_next_tile_msb = ppuRead((control.pattern_background << 12)
											+ ((uint16_t)bg_next_tile_id << 4)
											+ (vram_addr.fine_y) + 8);
				break;
			case 7:
				IncrementScrollX();
				break;
			}

		}

		if (cycle == 256) // End of the scanline
		{
			IncrementScrollY();
		}


		if (cycle == 257) // To restar our X coordante
		{
			LoadBackgroudShifters();
			TransferAddressX();
		}

		// Superfluous reads of tile id at end of scanline
		if (cycle == 338 || cycle == 340)
		{
			bg_next_tile_id = ppuRead(0x2000 | (vram_addr.reg & 0x0FFF));
		}

		if(scanline == -1 && cycle >= 280 && cycle < 305)
		{
			TransferAddressY();
		}
	}

	if (scanline == 240)
	{
		// Post Render Scanline - Do Nothing
	}

	if (scanline >= 241 && scanline < 261)
	{
		if (scanline == 241 && cycle == 1)
		{
			status.vertical_blank = 1;
			if (control.enable_nmi)
				nmi = true;
		}
	}


	// Composition - We now have background pixel information for this cycle
	// At this point we are only interested in background

	uint8_t bg_pixel = 0x00; // The 2-bit pixel to be rendered
	uint8_t bg_palette = 0x00; // The 3-bit index of the palette the pixel indexes

	// Draw background only if we can draw background in the mask register
	if (mask.render_background)
	{
		// Handle Pixel Selection by selecting the relevant bit
		// depending upon fine x scolling. This has the effect of
		// offsetting ALL background rendering by a set number
		// of pixels, permitting smooth scrolling
		uint16_t bit_mux = 0x8000 >> fine_x;

		// Select Plane pixels by extracting from the shifter 
		// at the required location. 
		uint8_t p0_pixel = (bg_shifter_pattern_lo & bit_mux) > 0;
		uint8_t p1_pixel = (bg_shifter_pattern_hi & bit_mux) > 0;

		// Combine to form pixel index
		bg_pixel = (p1_pixel << 1) | p0_pixel;

		// The same, but with the palette
		uint8_t bg_pal0 = (bg_shifter_attrib_lo & bit_mux) > 0;
		uint8_t bg_pal1 = (bg_shifter_attrib_hi & bit_mux) > 0;
		bg_palette = (bg_pal1 << 1) | bg_pal0;

	}



	// Fake some noise for now
	//sprScreen.SetPixel(cycle - 1, scanline, palScreen[(rand() % 2) ? 0x3F : 0x30]);

	sprScreen.SetPixel(cycle - 1, scanline, GetColourFromPaletteRam(bg_palette, bg_pixel));

	// Advance renderer - it never stops, it's relentless
	cycle++;
	if (cycle >= 341) // These numbers are hardcore to represent NES hardware
	{
		cycle = 0;
		scanline++;
		if (scanline >= 261)
		{
			scanline = -1;
			frame_complete = true;
		}
	}
}
