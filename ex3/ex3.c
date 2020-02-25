#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 128 * 1024

void vul(char *tab, int n) {
	int i;
	for (i = 0;i<n;i++){ 
		tab[i] = 'a'+rand()%26;		
	}
	
	return;
}

int main(int argc, char **argv) {
	srand(time(0)); 	
	int i;
	char buffer[MAX];
	for (i = 1; i < MAX;i<<=1) {
		double start = clock();
		int fd;

		// hdparm -W0 /dev/sda -> disabled buffering on the phisical harddisk
		if ( ( fd=open(argv[1], O_CREAT | O_WRONLY | O_SYNC, S_IRWXU)) < 0 ) { // O_SYNC makes sure that every change to the buffer go's straight to the disk (makes the program really slow)
		
			perror(argv[0]);
			exit(1); 
		}
	
		int tot = 0;
		vul(buffer, i);
		int n = write(fd, buffer, i);
		// aslong tot is smaller than the maximum wanted file size, keep write data to the file
		// This will make sure file will be exactly 10mb large
		// The file wil be filed with 1 full buffer at a time
		while ( tot < 10 * 1024*1024 - i) { // '&' is not needed in this example because buffer is already a pointer
			vul(buffer, i);
			n =write(fd, buffer, i);
			tot += i;
		}
		vul(buffer, 10 * 1024 * 1024 - tot);
		write(fd, buffer, 10*1024*1024-tot);
	
		if (close(fd) < 0) { // close file descriptor
			perror(argv[0]);
			exit(1);
		}
		double time = (clock() - start)/CLOCKS_PER_SEC;
		printf("BUF_SIZ=%d\tTime=%.2f\n", i, time);
		unlink(argv[1]);
	}
	exit(0);

}
