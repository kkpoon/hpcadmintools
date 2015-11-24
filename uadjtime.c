#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	struct timeval delta, olddelta;
	if (argc == 2)  {
		delta.tv_sec = atoi(argv[1]);
		printf("Detla: %d\n\r", (int)delta.tv_sec);
		adjtime(&delta, &olddelta);
		printf("Old delta: %d %d\n\r", (int)olddelta.tv_sec, (int)olddelta.tv_usec);
	}
	else {
		adjtime(0, &olddelta);
		printf("Old delta: %d %d\n\r", (int)olddelta.tv_sec, (int)olddelta.tv_usec);
	}
	return 0;
}
