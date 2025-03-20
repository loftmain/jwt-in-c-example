#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define SERVER "IT.srvd_new"
#define PORT "7705"
#else
#define SERVER "IT.srvd"
#define PORT "it_srvd"
#endif

#include "srvd_newfunc.hpp"

int main(int argc, char* argv[])
{
    srvd_newfunct();
    return 0;
}