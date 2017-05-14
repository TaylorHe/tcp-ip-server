/*
  Pipesex.c
  Demo on using pipes and forks
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

int main(int argc, char* argv[]){
	
    if(argc == 1){
        perror("usage error"), exit(1);
    }
    
	pid_t pid;
	/* Read line and write line, mutually exclusive */
	int p[2];
	int p2[2];
	int maxBufferSize = 150;
	if(pipe(p) < 0){
		perror("failed creating pipe"), exit(1);
	}
	if(pipe(p2) < 0){
		perror("failed creating pipe2"), exit(1);
	}

	if((pid = fork()) < 0){
		perror("Error creating fork"), exit(1);
	} else if(pid == 0){
		//my_str("Hello from child\n");
		// Child's job is to read
		
		char buffer[maxBufferSize];
		int num_bytes;
		close(p[1]);
		if((num_bytes = read(p[0], buffer, maxBufferSize)) < 0){
			perror("Error reading from pipe"), exit(1);
		}
		my_str("Child: ");
        my_str(buffer);
        my_str("\n");
		//close(p[0]);
		//close(p2[0]);

		if(write(p2[1], buffer, strlen(buffer) + 1) < 0){
			perror("failed creating pipe"), exit(1);
		}
		//close(p2[1]);
		
					
		if((pid = fork()) < 0){
			perror("Error you suck"), exit(1);
		} else if (pid == 0){
			int num_bytes2;
			char buffer2[maxBufferSize];
			close(p2[1]);
			if((num_bytes2 = read(p2[0], buffer2, maxBufferSize)) < 0){
				perror("Error reading from pipe"), exit(1);
			}
			my_str("grandchild: ");
            my_str(buffer);
            my_str("\n");
			close(p2[0]);
			exit(6);

		} else {
			int grandstatus;

			wait(&grandstatus);
		}


		exit(5);
	} else {
		/* adult */
		int status;
        //char** tovec = argv + 1;
        char* str = my_vect2str(argv+1);
		my_str("parent: ");
        my_str(str);
        my_str("\n");
		//closes the read line and opens the write line to write
		//strlen + 1 because need a NULL terminator
		close(p[0]);
		if(write(p[1], str, strlen(str) + 1) < 0){
			perror("failed creating pipe"), exit(1);
		}

		wait(&status);
		//my_str("hello from parent\nChild exited with status : %i\n", WEXITSTATUS(status));

	}
	return 0;




}
