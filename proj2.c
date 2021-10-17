/* fileio.c */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#define Min(a,b) (a<b?a:b)
/* 
TODO:
	stats
*/

int main(int argc, char *argv[])
{
	int fdIn, cnt, i, buffSize,ocurCount,n,pid;
	char* rem;
	struct stat sb;

	//errors
	if (argc < 3) {
		fprintf(stderr, "Please Provide a File and a Character\n");
		exit(1);
	}
	else if ((fdIn = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "error opening file\n");
		exit(1);
	}
   	
	ocurCount = 0;
	char target = argv[2][0];

	if (argc > 3) {
		if((strcmp(argv[3], "mmap") == 0) || (argv[3][0] == 'p')){
			//error
			if(fstat(fdIn, &sb) < 0){
				perror("Could not stat file to obtain its size");
				exit(1);
			}

			if(argv[3][0] == 'p'){
				argv[3]++;
				n = Min(16,atoi(argv[3]));
			} else
				n = 1;
				

			char *pchFile;
			//map file
			if ((pchFile = (char *) mmap (NULL, sb.st_size, PROT_READ, MAP_SHARED, fdIn, 0)) 
						== (char *) -1)	{
							perror("Could not mmap file");
							exit (1);
						}
			printf("File Size: %ld bytes\n",sb.st_size);

			for (i = 0; i < n; ++i) {
			    pid = fork();
			    if (pid > 0) {   // I am the parent, create more children
				continue;
			    } else if (pid == 0) { // I am a child, get to work
					
						//work
						for(int k = ((sb.st_size/n) * i); k < ((sb.st_size/n) * (i+1)); k++){
							if(pchFile[k] == target)
								ocurCount++;
						}
						//result
						
						printf("Occurances of the character '%c': %d\n",target,ocurCount);

						// Now clean up
						if(munmap(pchFile, sb.st_size) < 0){
							perror("Could not unmap memory");
							exit(1);
						}
				break;
			    } else {
				printf("fork error\n");
				exit(1);
			    }
			}
			
			for(int i = 0; i < n; i++){
				wait(0);
			}
		
			close(fdIn);
			exit(1);
		}
		//chunk size
		buffSize = strtol(argv[3],&rem,10); 
    } else {
	buffSize = 1024;
    }
		
	int sizeCount = 0;
	char buf[buffSize];
	do{
		cnt = read(fdIn, buf, buffSize);
		buf[cnt] = '\0';
		sizeCount += cnt;
		for(int i = 0; i < cnt; i++){
				if(buf[i] == target)
					ocurCount++;
		}
	} while (cnt > 0);

	printf("File Size: %d bytes\n",sizeCount);
	printf("Occurances of the character '%c': %d\n",target,ocurCount);

    if (fdIn > 0)
        close(fdIn);

	
}
