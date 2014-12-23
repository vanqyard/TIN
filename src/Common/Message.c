#include <stdio.h>
#define TRANSMISSION_CONTROL 	0
#define DATA_TRANSIMSSION 		1
#define TRACEROUTE_INFO 		2

struct Message {
	const char* dst;
	const char* src;
	const char* data;
	int ctrl;
}
