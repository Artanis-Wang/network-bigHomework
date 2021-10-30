//
//  receiver.h
//  receiver
//
//  Created by Artanis Wang on 2021/10/30.
//

#ifndef receiver_h
#define receiver_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#endif /* receiver_h */

unsigned char frame[65535];
unsigned char sta_addr[6];
unsigned char des_addr[6];
unsigned short protocol;
unsigned char *payload;
unsigned int frame_len;
unsigned int payload_len;
unsigned char my_addr[6] = {0x74,0x8f,0x3c,0xc4,0x4c,0x94};
unsigned char crc_receive[4];
unsigned char crc_send[4];

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

int check_addr(unsigned char my_addr[6],unsigned char des_addr[6])
{
    int flag = 1;
    for(int i = 0;i<6;i++) if(des_addr[i]!=my_addr[i]) flag=0;
    if(flag) printf("Address right!\n");
    else{
        printf("Exception! Address wrong!\n");
        printf("Destination Address: ");
        show_addr(des_addr, 6);
        printf("my Address         : ");
        show_addr(my_addr, 6);
    }
    return flag;
}

long get_file_size(FILE *file)
{
    long current_read_position = ftell(file);
    long size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, current_read_position, SEEK_SET);
    return size;
}
int receive_frame(void)
{
    FILE *in = fopen("data.bin", "r");
    frame_len = 0;
    long frame_len = get_file_size(in);
    printf("Get frame length: %ld\n",frame_len);
    if(frame_len<64)
    {
        printf("Exception! Payload length: %ld is too small!",frame_len);
        exit(1);
        
    }
    else if(frame_len > 1518)
    {
        printf("Exception! payload length: %ld is too big!",frame_len);
        exit(1);
    }
    fread(&frame, sizeof(char), frame_len, in);
    memcpy(&des_addr, &frame[0], 6);
    memcpy(&sta_addr, &frame[6], 6);
    memcpy(&protocol, &frame[12], sizeof(protocol));
    payload = &frame[14];
    if (!check_addr(my_addr, des_addr)) {
        exit(1);
    }
    unsigned int crc_re = crc32(frame,frame_len-4);
    memcpy(crc_receive, &crc_re, 4);
    memcpy(crc_send, &frame[frame_len-4], 4);
    if(
       crc_send[0]!=crc_receive[0]||
       crc_send[1]!=crc_receive[1]||
       crc_send[2]!=crc_receive[2]||
       crc_send[3]!=crc_receive[3]
       )
    {
        printf("Exception! CRC32 wrong!");
        printf("CRC_send   : ");
        show_addr(crc_send, 4);
        printf("CRC_receive: ");
        show_addr(crc_receive, 4);
        exit(1);
    }
    printf("CRC32 check successfully!\n");
    printf("*********Receive frame********\n");
    printf("Start address       : ");
    show_addr(sta_addr, 6);
    printf("Destination address : ");
    show_addr(des_addr, 6);
    printf("protocol            : %d\n",protocol);
    printf("payload             : %s\n",payload);
    printf("CRC32 send          : ");
    show_addr(crc_send, 4);
    printf("CRC32 receive       : ");
    show_addr(crc_receive, 4);
    printf("******************************\n");
    printf("Successfully receive frame!\n");
    return 0;
}
