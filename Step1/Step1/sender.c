//
//  sender.c
//  Step1
//
//  Created by Artanis Wang on 2021/10/30.
//

#include <stdio.h>
#include "sender.h"
unsigned char sta_addr[6] = {0xf8,0xe4,0x3b,0x02,0x72,0x79};
unsigned char des_addr[6] = {0x74,0x8f,0x3c,0xc4,0x4c,0x94};
unsigned char frame[1550];
unsigned char data[] = "This is a frame payload from 20194195 ZiyuWang.";
unsigned short protocol = 1;

int main()
{
    FILE *out = fopen("data.bin","wb+");
    unsigned int frame_len = get_frame(frame, sta_addr, des_addr, protocol, data, sizeof(data));
    sendFrame(frame, frame_len, out);
    fclose(out);
    return 0;
}
