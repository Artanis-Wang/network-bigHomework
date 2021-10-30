//
//  main.c
//  senderTest
//
//  Created by Artanis Wang on 2021/10/30.
//

#include <stdio.h>
#include "sender.h"


unsigned char frame[1546];
unsigned char data[] = "Hello! This is 20194195 ZiyuWang's message. It's a farme payload data.";
unsigned char sta_Mac_addr[6] = {0xf8,0xe4,0x3b,0x02,0x72,0x79};
int main(int argc, const char * argv[]) {
    // insert code here...
    show();
    printf("Hello, World!\n");
    show_addr(sta_Mac_addr, 6);
    return 0;
}

int get_frame(unsigned char frame[)
