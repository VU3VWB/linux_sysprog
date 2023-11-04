#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "ftd2xx.h"
#include "libft4222.h"

int main()
{
    FT_HANDLE ftHandle = NULL;
    FT_STATUS ftStatus;
    FT4222_STATUS ft4222Status;
    ftStatus = FT_Open(0, &ftHandle);
    if (FT_OK == ftStatus)
    {
        printf("Success ! \n");
    }
    ft4222Status = FT4222_SPIMaster_Init(ftHandle, SPI_IO_SINGLE, CLK_DIV_4, CLK_IDLE_LOW, CLK_LEADING, 0x01);
    if (FT4222_OK == ft4222Status)
    {
        printf("Success ! \n");
    }
    FT4222_UnInitialize(ftHandle);
    FT_Close(ftHandle);
    return 0;
}