// These header files will be linked in the compilations step
#include <unistd.h> // important imports
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 16 * 1024


int main(int argc, char **argv) {
	// BUFFSIZE is een global constante containing a optimal size for a buffer	
	int i;
	char buffer[MAX];
	for (i = 1; i < 32*1024;i<<=1) {
		double start = clock();
		int fd;
		// if ( a == 7) checks if value a equal is to 7
		// if (a = 7) chekcs if the operation of setting a equal to 7 was succesfull
		if ( ( fd=open(argv[1], O_RDONLY)) < 0 ) {
			// argv[0] contains always the program name
			// prints 'erno' to display
			perror(argv[0]);
			exit(1); // stop program with fail status
		}
	
		
		int n;

		// zolang n gelijk is aan i blijf inlezen, als dit niet zo is dan komt aan einde lijn aan.
		while ( ( n =read(fd, buffer, i)) == i); // geen '&' plaatsen omdat het al address is van het eerste element van de array
		if (n< 0) { // problem when smaller than 0
			perror(argv[0]);
			close(fd); // a additional check for if file really closed is not needed because program is going to stop anyway
			exit(1);
			
		}	
		if (close(fd) < 0) { // close file descriptor
			perror(argv[0]);
			exit(1);
		}
		double time = (clock() - start)/CLOCKS_PER_SEC;
		printf("BUF_SIZ=%d\tTime=%.2f\n", i, time);
	}
	exit(0);

}
