//
//  receiver.c
//  receiver
//
//  Created by Artanis Wang on 2021/10/30.
//

#include "receiver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
    printf("Begin receive frame!\n");
    printf("My mac address      : ");
    show_addr(my_addr, 6);
    receive_frame();
    return 0;
}
