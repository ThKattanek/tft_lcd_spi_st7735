/*
 * Project Name: tft_st7735_example
 * File: main.cpp
 * Description: library from https://github.com/gavinlyonsrepo/ST7735_TFT_PICO
 * Author: thorsten kattanek
 * Created: December 2022
 */

#include "pico/time.h"
#include "hardware/spi.h"
#include "st7735/ST7735_TFT.hpp"

void Setup(ST7735_TFT *tft)
{
	sleep_ms(20);	// wait to tft 20ms

//*************** USER OPTION 0 SPI_SPEED + TYPE ***********
	bool bhardwareSPI = true; // true for hardware spi,

	if (bhardwareSPI == true) { // hw spi
		uint32_t TFT_SCLK_FREQ =  40000 ; // Spi freq in KiloHertz , 1000 = 1Mhz
		tft->TFTInitSPIType(TFT_SCLK_FREQ, spi0);
	} else { // sw spi
		tft->TFTInitSPIType();
	}

// ******** USER OPTION 1 GPIO *********
// NOTE if using Hardware SPI clock and data pins will be tied to
// the chosen interface eg Spi0 CLK=18 DIN=19)
	int8_t SDIN_TFT = 19;
	int8_t SCLK_TFT = 18;
	int8_t DC_TFT = 3;
	int8_t CS_TFT = 2 ;
	int8_t RST_TFT = 17;
	tft->TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);

// ****** USER OPTION 2 Screen Setup ******
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with screen manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128;// Screen width in pixels
	uint16_t TFT_HEIGHT = 160; // Screen height in pixels
	tft->TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);

// ******** USER OPTION 3 PCB_TYPE  **************************
	tft->TFTInitPCBType(TFT_PCBtype_e::TFT_ST7735S_Black); // pass enum,4 choices,see README
}

int main(void) 
{
	ST7735_TFT tft;

	Setup(&tft);

	tft.TFTFontNum(TFTFont_Default);
	tft.TFTfillScreen(ST7735_BLACK);
	tft.setTextColor(rand() % 0x10000);
	tft.TFTsetCursor(0,0);
	tft.TFTsetScrollDefinition(0,160,1);

	// main loop
	while(1)
	{

tft.setTextColor(rand() % 0x10000);

		tft.print("Hello World!");

		sleep_ms(40);
	}

	return 0;
}
