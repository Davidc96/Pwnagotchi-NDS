#ifndef SPI_CONTROLLER_H
#define SPI_CONTROLLER_H

#include <nds.h>
#include <stdio.h>
#include "spi_commands.h"
#include "utils.h"

// Extracted from DSBrut https://github.com/gohai/dsbrut/blob/master/libdsbrut/arm9/source/spi_internals.h
/** Enable the SPI controller */
#define CARD_SPI_ENABLE_BIT (1 << 15)
/** Generate an interrupt request when the transfer is complete */
#define CARD_SPI_IRQ_BIT (1 << 14)
/** The Chip Select signal for the DS Slot */
#define CARD_SPI_SLOT_CS_BIT (1 << 13)
/** The busy bit in the control register (0 idle, 1 busy) */
#define CARD_SPI_BUSY_BIT (1 << 7)
/** The Chip Select Hold bit */
#define CARD_SPI_CS_HOLD_BIT (1 << 6)


/** Test if the SPI bus is busy (0 is idle, non-zero busy)*/
#define CARD_SPI_BUSY_TEST (REG_AUXSPICNT & CARD_SPI_BUSY_BIT)

/** Wait for the SPI bus to become idle */
#define CARD_SPI_WAIT_IDLE() while ( CARD_SPI_BUSY_TEST);

// Extracted from DSBrut https://github.com/gohai/dsbrut/blob/master/libdsbrut/arm9/source/spi.h
enum SPI_FREQ {
  /** 4 MHz */
  CARD_SPI_4_MHZ_CLOCK = 0,
  /** 2 MHz */
  CARD_SPI_2_MHZ_CLOCK = 1,
  /** 1 MHz */
  CARD_SPI_1_MHZ_CLOCK = 2,
  /** 524 KHz */
  CARD_SPI_524_KHZ_CLOCK = 3
};

class SPIController
{
    public:
        SPIController();
        ~SPIController();
        void init();
        void sendCommand(uint command, u8 * response, uint command_length, uint response_length);
        void sendCommand(uint command);
        void readByte(uint * response);
        int getTotalAPs();
        int sendPing();
        GiveAPResponse getAP(GiveAPResponse * apstr);


    private:
        void waitSPIBusy();
        void resetSPI();
        uint16_t m_config;
        uint32_t m_blocksize; 
};


#endif