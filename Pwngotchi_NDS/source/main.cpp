/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
#include <nds.h>

#include <stdio.h>

#include "pwngotchi.h"


volatile int frame = 0;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	irqSet(IRQ_VBLANK, Vblank);
	defaultExceptionHandler();

	Pwngotchi * pwngotchi = new Pwngotchi();
	pwngotchi->init();
	//spicontroller->sendCommand(SPI_ATTACK, 0, sizeof(SPI_ATTACK), 0);
	
	while(1) 
	{ 
		pwngotchi->run();
		pwngotchi->setDebugFrame(frame);
		swiWaitForVBlank(); 
	}

	return 0;
}
