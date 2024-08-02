#pragma once

#define VIAL_KEYBOARD_UID {0xBB, 0x17, 0xF0, 0x5B, 0x02, 0x80, 0x1D, 0x1D}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 2 }

/* SPI config for display/touchpad*/
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

#define ADNS9800_CS_PIN GP9

//#define ADNS9800_SPI_MODE 1
#define  POINTING_DEVICE_INVERT_X
//#define  POINTING_DEVICE_INVERT_Y
