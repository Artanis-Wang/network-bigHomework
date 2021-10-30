//
//  sender.h
//  Step1
//
//  Created by Artanis Wang on 2021/10/28.
//

#ifndef sender_h
#define sender_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#endif /* sender_h */

unsigned int crc32(unsigned char *data,int len) {
    unsigned int crc = 0xFFFFFFFF;
    for (int i=0;i<len;i++) {
        crc = crc ^ data[i];
        for (int j=7;j>=0;j--) {
            crc = (crc >> 1) ^ (0xEDB88320 & (-(crc & 1)));
        }
    }
    return ~crc;
}
void show(void)
{
    printf("This is just a test.\n");
}

void show_addr(unsigned char *x,unsigned int len)
{
    unsigned int i;
    for(i = 0;i<len;i++)
    {
        printf("%02x",x[i]);
        if (i!=len-1) printf(" ");
    }
    printf("\n");
}

int get_frame(unsigned char frame[1546],unsigned char *sta_addr,unsigned char *des_addr,
              unsigned short protocol,unsigned char* payload, unsigned int payload_len)
{
    if(payload_len < 46)
    {
        printf("Exception! The length of payload must greater than 46!");
        exit(1);
    }
    else if(payload_len > 1500)
    {
        printf("Exception! The length of payload must smaller than 1500");
        exit(1);
    }
    memcpy(&frame[0], des_addr, 6);
    memcpy(&frame[6], sta_addr, 6);
    memcpy(&frame[12], &protocol, sizeof(protocol));
    memcpy(&frame[14], payload, payload_len);
    unsigned int crc = crc32(frame, 14+payload_len);
    memcpy(&frame[14+payload_len], &crc, sizeof(crc));
    
    unsigned int length = payload_len + 18;
    printf("*****Begin create frame*****\n");
    printf("Start address: ");
    show_addr(sta_addr, 6);
    printf("Des   address: ");
    show_addr(des_addr, 6);
    printf("protocol     : %d\n",protocol);
    printf("payload      : %s\n",payload);
    printf("CRC32        : ");
    printf("Frame length : %d\n",length);
    printf("****************************\n");
    printf("Successfully create frame!\n");
    return length;
}

void sendFrame(unsigned char *frame,unsigned short len,FILE *file)
{
    fwrite(frame,sizeof(char),len,file);
}

