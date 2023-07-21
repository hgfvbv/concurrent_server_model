#include "client.h"

void main(int argc, const char *argv[])
{
	client_init();
	subscribe("hello");
	while(1);
}
