#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

// This is a program that can be used for eather parent and child process
//

int main() {
	int pid;
	if ((pid = fork())==0) { // The program knows if it's running in a parent or child process via the pid.
		// child --> child pid will always be 0
		printf("Child has PID=%d\n", getpid());
		return 0;
	} else {
		 // Parent
		 printf("Parent has PID=%d\n", getpid());	
	}
	
	return 0;
}
