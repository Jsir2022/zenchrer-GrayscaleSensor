#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>
#include <stdbool.h>

//λ��F103C6T6A�����1KB��ҳ
#define FLASH_SAVE_START        0x08007C00
#define FLASH_SAVE_END          0x08007FFF

#define FLASH_DATA_ADDR_MIN         FLASH_SAVE_START
#define FLASH_DATA_ADDR_MAX         FLASH_SAVE_END

#define FLASH_WAITETIME             1000

void Flash_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead);
void Flash_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);

#endif
