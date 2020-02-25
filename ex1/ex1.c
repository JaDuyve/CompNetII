#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

char get_char() {
	return 'a'+rand()%26;
}


int main(int argc, char **argv) {
	//srand(time(0)); // This is uniek if randomness is not required at really short intervals (based on cpu clock)
	srand(getpid()); // getpid makes sure that it wil be the most random
	int fd;
	if ( ( fd=open("bigfile",O_CREAT | O_WRONLY)) < 0 ) { // create if file not exist, if exist only write to file
		// argv[0] komt altijd overeen met naam van programma
		// schrijft automatisch waarde van erno naar scherm
		perror(argv[0]);
		exit(1); // stop programma want er is een probleem
	}

	// bigfile is now created if it not already existed and ready to write to
	
	int i;
	for (i = 0; i< 10* 1024 * 1024; i++) {
		// The hard disk will be consulted more frequently as the buffer becomes smaller. 
		// The solution to this problem is to make the buffer larger but this has also its limits
		char ch=get_char(); // buffer
		int n;
		if ( ( n = write(fd, &ch, 1)) != 1) { // The second variable contains the address of the buffer
			perror(argv[0]);
			exit(1);
		}
	}
	
	if (close(fd) < 0) { // close file descriptor
		perror(argv[0]);
		exit(1);
	}
	exit(0);

}
