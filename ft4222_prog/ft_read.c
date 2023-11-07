#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
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
    ft4222Status = FT4222_SPIMaster_Init(ftHandle, SPI_IO_SINGLE, CLK_DIV_512, CLK_IDLE_LOW, CLK_LEADING, 0x01);
    if (FT4222_OK == ft4222Status)
    {
        printf("Success ! \n");
    }

    int n_bytes = 65536;
    uint8 recvData[n_bytes*2];
    uint8 dummy_buffer[10];
    uint16 sizeTransferred;

    for (int i=0; i<n_bytes; i++)
    {
        ft4222Status = FT4222_SPIMaster_SingleRead(ftHandle, &recvData[i*2], 2, &sizeTransferred, true);
    }

    // ft4222Status =  FT4222_SPIMaster_MultiReadWrite(ftHandle, &recvData[0], &dummy_buffer[0], 0, 0, n_bytes, &sizeTransferred);
    if (FT4222_OK != ft4222Status)
    {
        printf ("Can't read \n");
        printf ("%d\n",ft4222Status);
        return 0;
    }
    printf ("Reached here \n");
    // for (int i=0; i<n_bytes; i++)
    // {
    //     printf ("%d,", (int)recvData[i]);
    // }

    FILE *write_ptr;
    write_ptr = fopen("spidata.bin","wb");
    fwrite(recvData,sizeof(recvData),1,write_ptr);
    fclose(write_ptr);

    FT4222_UnInitialize(ftHandle);
    FT_Close(ftHandle);
    return 0;
}