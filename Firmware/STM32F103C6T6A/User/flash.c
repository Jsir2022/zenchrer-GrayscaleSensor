#include "flash.h"
#include "app_main.h"
#include <string.h>
#include <stdio.h>

/*************************************************************
** Function name:       STMFLASH_ReadWord
** Descriptions:        ������
** Input parameters:    Ҫ��ȡ�ĵ�ַ
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
uint32_t Flash_ReadWord(uint32_t faddr)
{
    return *(uint32_t *)faddr;
}

/*************************************************************
** Function name:       STMFLASH_Read
** Descriptions:        ������ȡ����
** Input parameters:    NumToRead Ҫ��ȡ�����ݸ�������λΪuint32
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Flash_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead)
{
    uint32_t i;
    for (i = 0; i < NumToRead; i++)
    {
        pBuffer[i] = Flash_ReadWord(ReadAddr);    //��ȡ4���ֽ�.
        ReadAddr += 4;                            //ƫ��4���ֽ�.
    }
}

/*************************************************************
** Function name:       STMFLASH_Write
** Descriptions:        STM32д����
** Input parameters:    pBuffer ������Ҫ�洢��ָ�롢 NumToWrite ��Ҫд����ֽ�����/8(��������д��˫�ִ�С 8�ֽ�)
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Flash_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)
{
    FLASH_EraseInitTypeDef FlashEraseInit;
    HAL_StatusTypeDef FlashStatus = HAL_OK;
    uint32_t PageError            = 0;
    uint32_t addrx                = 0;
    uint32_t endaddr              = 0;
    if (WriteAddr < FLASH_DATA_ADDR_MIN || WriteAddr % 4) return; //�Ƿ���ַ ��ֹд��ķ�Χ
    HAL_FLASH_Unlock();                                           //����
    addrx   = WriteAddr;                                          //д�����ʼ��ַ
    endaddr = WriteAddr + NumToWrite * 8;                         //д��Ľ�����ַ
    if (addrx < FLASH_DATA_ADDR_MAX)
    {
        while (addrx < endaddr) //ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
        {
            if (Flash_ReadWord(addrx) != 0XFFFFFFFF) //�з�0XFFFFFFFF�ĵط�,Ҫ�����������
            {
                FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;         //�������ͣ�ҳ����
								//��G0��ͬ���ǣ�F0�����ǲ���ҳ����ʼ��ַ������������Sector��15
								FlashEraseInit.PageAddress=WriteAddr;
				
                FlashEraseInit.NbPages   = 1;                             //һ��ֻ����һҳ
                printf("Flash Erase page is %d\r\n", FlashEraseInit.PageAddress);
                if (HAL_FLASHEx_Erase(&FlashEraseInit, &PageError) != HAL_OK)
                {
                    printf("Flash Erase err\r\n");
                    break; //����������
                }
                FLASH_WaitForLastOperation(FLASH_WAITETIME); //�ȴ��ϴβ������
            }
            else
            {
                addrx += 4;
            }
        }
    }
    FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME); //�ȴ��ϴβ������
    if (FlashStatus == HAL_OK)
    {
        while (WriteAddr < endaddr) //д����
        {
            if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, WriteAddr, *(uint64_t *)pBuffer) != HAL_OK) //д������
            {
                break; //д���쳣
            }
            WriteAddr += 8; //��ַ��8
            pBuffer += 2;   // buff����������32λ��,�������2 ����8���ֽ�
        }
        printf("Flash write ok\r\n");
    }
    FLASH_WaitForLastOperation(FLASH_WAITETIME); //�ȴ��ϴβ������
    HAL_FLASH_Lock();                            //����
}
