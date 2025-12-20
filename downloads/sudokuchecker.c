//Necessary Packages
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//Main method
int main(int argc, char *argv[]){
        //get arguments
        int length = strlen(argv[1]);
        printf("Your integers are %s %s\n", argv[1], argv[2]);

        //initiate pipe and check for error
        int portToChild[2];
        int portToParent[2];
        if(pipe(portToChild) < 0 || pipe(portToParent) < 0){
                printf("Pipe Error");
                goto EndOfProgram;
        }

        //get process ID, fork, and check for fork error
        pid_t pid = getpid();
        pid_t cpid = fork();
        if(pid < 0){
                printf("Fork Error");
                goto EndOfProgram;
        }
	if(cpid > 0){
        	printf("Parent (PID %d): created child (PID %d)\n",pid,cpid);
	}
	
	//Add check for different steps of the calculation
	char step[] = "XYZ";
	int i = 0;

        //run if parent
        if(cpid > 0){
		//initiate variables for sections of the calculation
                char a1Char[3], a2Char[3], b1Char[3], b2Char[3];
                strncpy(a1Char, argv[1], 2);
                strncpy(a2Char, argv[1]+2, 2);
                strncpy(b1Char, argv[2], 2);
                strncpy(b2Char, argv[2]+2, 2);
                a1Char[2] = a2Char[2] = b1Char[2] = b2Char[2] = '\0';
                int X, Y, Z;
		//Begin the first part of the calculation
		if(step[i] == 'X'){
			printf("\n###\n#\tCalculating X\n###\n");
			printf("Parent PID(%d): Sending %s to child\n", pid, a1Char);
			//send information to the child to be calculated
			write(portToChild[1], a1Char, 2);
			printf("Parent PID(%d): Sending %s to child\n", pid, b1Char);
                	write(portToChild[1], b1Char, 2);
			int A;
			//read information from the child
			read(portToParent[0], &A, sizeof(A));
			printf("Parent PID(%d): Received %d from child\n", pid, A);
			X = A*10000;
			i++;
		}
		//Begin the second step of the calculation
		if(step[i] == 'Y'){
                        printf("\n###\n#\tCalculating Y\n###\n");
			printf("Parent PID(%d): Sending %s to child\n", pid, a2Char);
                        //send information to the child once again
			write(portToChild[1], a2Char, 2);
                        printf("Parent PID(%d): Sending %s to child\n", pid, b1Char);
                        write(portToChild[1], b1Char, 2);
                        int B;
			//read calculations from the child
                        read(portToParent[0], &B, sizeof(B));
                        printf("Parent PID(%d): Received %d from child\n", pid, B);
                        printf("Parent PID(%d): Sending %s to child\n", pid, a1Char);
                        //send some more information to the child to be calculated
			write(portToChild[1], a1Char, 2);
                        printf("Parent PID(%d): Sending %s to child\n", pid, b2Char);
                        write(portToChild[1], b2Char, 2);
                        int C;
			//read the childs calculations
                        read(portToParent[0], &C, sizeof(C));
                        printf("Parent PID(%d): Received %d from child\n", pid, C);
			Y = (B+C)*100;
			i++;
		}
		//begin the final third step of calculations
		if(step[i] =='Z'){
		printf("\n###\n#\tCalculating Y\n###\n");
                        printf("Parent PID(%d): Sending %s to child\n", pid, a2Char);
                        //send the last of the information to the child
			write(portToChild[1], a2Char, 2);
                        printf("Parent PID(%d): Sending %s to child\n", pid, b2Char);
                        write(portToChild[1], b2Char, 2);
                        int D;
			//read the last of the childs calculations
                        read(portToParent[0], &D, sizeof(D));
                        printf("Parent PID(%d): Received %d from child\n", pid, D);
                        Z = D;
		}
		//perform the final calculations and print out the answer
		int finalAns = X+Y+Z;
		printf("%s*%s == %d + %d + %d == %d\n", argv[1], argv[2], X, Y, Z, finalAns);

        }
        
        //run if child process
        if(cpid == 0){
		//loop 3 times for the 3 similar calculations to be performed
		for(int i = 0; i < 4; i++){
			pid_t ccpid = getpid();
			char firstStr[3];
			char secondStr[3];
			//read information from the parent
			read(portToChild[0], firstStr, 2);
			printf("Child PID(%d): Received %s from parent\n", ccpid, firstStr);
			read(portToChild[0], secondStr, 2);
			printf("Child PID(%d): Received %s from parent\n", ccpid, secondStr);
			//process the information and calculate
			int firstInt = atoi(firstStr);
			int secondInt = atoi(secondStr);
			int returnInt = firstInt * secondInt;
			//send calculations back to the parent
			write(portToParent[1], &returnInt, sizeof(returnInt));
			printf("Child PID(%d): Sending %d to parent\n", ccpid, returnInt);
		}
		//go to the end once all calculations are complete
		goto EndOfProgram;
        }


        //wait for the child
        if(cpid > 0){
                wait(NULL);
        }
        //end the program
        EndOfProgram:
        return 0;

}
