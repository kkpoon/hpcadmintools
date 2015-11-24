#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	struct timeval delta, olddelta;
	if (argc == 1)  {
		adjtime(0, &olddelta);
		printf("Old delta: %d sec %d usec \n\r", (int)olddelta.tv_sec, (int)olddelta.tv_usec);
	}
	if (argc == 3)  {
		delta.tv_sec = atoi(argv[1]);
		delta.tv_usec = atoi(argv[2]);
		printf("Delta: %d sec %d usec\n\r", (int)delta.tv_sec, (int)delta.tv_usec);
		adjtime(&delta, &olddelta);
		printf("Old delta: %d sec %d usec\n\r", (int)olddelta.tv_sec, (int)olddelta.tv_usec);
	}
	else {
		printf("Usage: uadjtime [<delta in sec> <delta in usec>]")
	}
	return 0;
}
