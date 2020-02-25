#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>


void in_to_out() {
	char buffer[8192];
	if (argc==1) {
		int n = read(0, buffer, 8192); // 8kb is the most optimal buffer size
		while(n!=0) {
			write (1, buffer, n); // only the number of bytes read from console rewriten to display
						// write not the full buffer size to console because this wil give some strange content
			n=read(0, buffer, 8192);

		}
	}
}

main(int argc, char **argv) {
	char buffer[8192];
	if (argc == 1) {
		in_to_out();

	} else {
		int i;
		for (i=0; i< argc; i++) {
			if (strcmp(argv[i], "-") == 0) {
				in_to_out();
				continue;
			}
			int fd;
			/* struct stat s;
			
			if (fstat(argv[i], &s) <0) {
				
			}
			if ((fd=open(argv[i], O_RDONLY))<0) {
				perror(argv[i]);
				continue; // if error pops op up while opening file
					// don't stop program but start printing following file, imput, ...
			}
			
			if (!S_ISREG(s.st_mode)){ // checks if file is a regular file
				perror(argv[i]);
				continue;	// if not continue to following param
			}
			
*/
			if ((fd=open(argv[i], O_RDONLY))<0) {
                                perror(argv[i]);
                                continue; 
                        }

			unsigned char buffer[8192]; // Tip: it's recommanded when using a textbuffer to use a unsigned char data type because this lays closed with to a byte datatype
			int n;
			while ((n = read(fd, buffer, 8192)) > 0) {
 				write(1, buffer, n);
			}
			

			close(fd); // Try to always close af file before ending a program
				// even if the compiler adds it automatically 

		}
	}

	
	return 0;	
}	
