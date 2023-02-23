#include "spi_controller.h"

SPIController::SPIController()
{
    sysSetBusOwners(true, true);
}

SPIController::~SPIController()
{

}
void SPIController::init()
{
    resetSPI();
    m_config = CARD_SPI_ENABLE_BIT | CARD_SPI_IRQ_BIT | CARD_SPI_524_KHZ_CLOCK | CARD_SPI_SLOT_CS_BIT;
    m_blocksize = 0;
}

void SPIController::sendCommand(uint command, u8 * response, uint command_length, uint response_length)
{
    REG_AUXSPICNT = /*E*/0x8000 | /*SEL*/0x2000 | /*MODE*/0x40;
    REG_AUXSPIDATA = command;
    waitSPIBusy();

    while (response_length > 0) 
    {
		REG_AUXSPIDATA = 0;
		waitSPIBusy();
		*response++ = REG_AUXSPIDATA;
		response_length--;
	}
    REG_AUXSPIDATA = 0;
    REG_AUXSPICNT = /*MODE*/0x40;

}

void SPIController::sendCommand(uint command)
{
    waitSPIBusy();
    REG_AUXSPICNT = m_config;
    REG_AUXSPIDATA = command;

}

void SPIController::readByte(uint * response)
{
    waitSPIBusy();
    *response = REG_AUXSPIDATA;
}

int SPIController::getTotalAPs()
{
    //int i;
    
	//REG_AUXSPICNT = /*E*/0x8000 | /*SEL*/0x2000 | /*MODE*/0x40;

	//REG_AUXSPIDATA = SPI_GETAPCOUNT;

	//waitSPIBusy();
	//REG_AUXSPIDATA = 0;
    //waitSPIBusy();
    //int id = (int)REG_AUXSPIDATA;
	/*for ( i=0; i<3; i++) {
		REG_AUXSPIDATA = 0;
		waitSPIBusy();
		id = (id << 8) | REG_AUXSPIDATA;
	}*/

    //REG_AUXSPIDATA = 0;
	//REG_AUXSPICNT = /*MODE*/0x40;
    uint id;
    sendCommand(SPI_GETAPCOUNT);
    waitSPIBusy();
    REG_AUXSPIDATA = 0;
    waitSPIBusy();
    readByte(&id);
	return 4;
}

int SPIController::sendPing()
{
    /*
    int i = 0;
    int id = 0;
    REG_AUXSPICNT = 0x8000 | 0x2000 | 0x40;

	REG_AUXSPIDATA = SPI_PING;

	waitSPIBusy();

	for ( i=0; i<3; i++) {
		REG_AUXSPIDATA = 0;
		waitSPIBusy();
		id = (id << 8) | REG_AUXSPIDATA;
	}


	REG_AUXSPICNT = 0x40;

	return id >> 16;*/

    uint response;
    
    sendCommand(SPI_PING);
    readByte(&response);
    
    return response;
    
}

GiveAPResponse SPIController::getAP(GiveAPResponse * ap)
{
    sendCommand(SPI_GIVEMEAP);

    char random_ssid[255];
    sprintf(random_ssid, "MOVISTAR_%d", getRandomNumber());
    ap->ssid = random_ssid;
    ap->connected_clients = getRandomNumber();
    ap->signal_strength = getRandomNumber();

    return *(ap);

}


void SPIController::waitSPIBusy()
{
    while (REG_AUXSPICNT & CARD_SPI_BUSY);
}

void SPIController::resetSPI()
{
    REG_AUXSPICNT = 0;
}