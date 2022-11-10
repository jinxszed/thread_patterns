/*Write a program that takes three arguments: the number of “things” (between 1 and 256), a word: either “thread” or “process, and a “pattern number” (1-3 only).

Create as many subprocesses or threads (“things”) as the number. Obviously, create either processes or threads as the command-line argument dictates.

Implement the forking/threading pattern as below. Arrows represent which process or thread creates the next process/thread.

Each process or thread should output (say) “Process 3 beginning”, then sleep for a random number of seconds (say, 1-8). If it created processes/threads, it should output a message "Process 3 creating Process 4", then wait for them to complete, then output “Process 3 exiting”. 

 

Error checking: Check the inputs. If there is an error, emit the error and output how to invoke the program.

Help: implement a simple and SHORT -h (AND –help) to explain valid parameters.

Debug: implement a “-d” parameter that outputs any debug log messages you have created.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep() -> man sleep for deets
#include <pthread.h>
#include <string.h>

int command_line_input(int argc, char *argv[]);

void non_blocking_pattern(int action, int num_things); // things = how many threads or sub-processes to create
void blocking_pattern(int action, int things); 				 // action = thread or process
void heap_pattern(int action, int things);

void *print_confirmation(void *threadid);


int main(int argc, char *argv[]) {
	//pthread = thread_id
	//pthread_create(args -> investigate
	//pthread_join(args -> investigate
	
	int num_things = atoi(argv[1]),
			pattern = atoi(argv[3]);

	switch(command_line_input(argc, argv)) {
		case 0: 
			return 0;
		case 2:
				printf("thread, non-blocking\n");
			break;
		case 3:
				printf("process, non-blocking\n");
			break;
		case 4:
				printf("thread, blocking\n");
				blocking_pattern(pattern, num_things);
			break;
		case 5:
				printf("process, blocking\n");
			break;
		case 6:
				printf("thread, heap\n");
			break;
		case 7:
				printf("process, heap\n");
			break;
	}
			
	return 0;
}

int command_line_input(int argc, char *argv[]) {
	int action;
		
		// evaluate second argument (action)
		if(!strcmp(argv[2], "thread")) {
			printf("thread\n");
			action = 1; 
		}
		else if(!strcmp(argv[2], "process")) {
			printf("process\n");
			action = 2;
		}
		
		// evaluate third argument (pattern)
		// action == 2 -> thread, non-blocking
		// action == 5 -> process, non-blocking
		// action == 3 -> thread, blocking
		// action == 6 -> process, blocking
		// action == 4 -> thread, heap
		// action == 7 -> process, heap
		
		// thread
		if (atoi(argv[3]) == 1) {
			printf("non-blocking\n");
			action += 1; // thread, non-blocking
		}
		else if (atoi(argv[3]) == 2) {
			printf("blocking\n");
			action += 3; //thread, blocking
		}
		else if (atoi(argv[3]) == 3) {
			printf("heap\n");
			action += 5; //thread, heap, returns 4
		}
		
		// process 
		else if (atoi(argv[3]) == 1) {
			printf("non-blocking\n");
			action += 4;
		}
		else if (atoi(argv[3]) == 2) {
			printf("blocking\n");
			action += 5;
		}
		else if (atoi(argv[3]) == 3) {
			printf("heap\n");
			action += 6;
		}
		
				// program-ending cases
		if(!strcmp(argv[argc-1], "-h"))
			printf("This program takes in 3 command line arguments. \nFirst is a number between 1 and 256 (inclusive).\nSecond is a word, either \"thread\" or \"process\".\nThird is a number indicating the thread pattern to use. 1 is for non-blocking, 2 is for blocking, 3 is for heap.\n");
			
		else if(atoi(argv[1]) < 1 || atoi(argv[1]) > 256) {
				printf("Number should be between 1 and 256, inclusive. Exiting program.\n");
				action = 0;
			}
		else if(atoi(argv[3]) < 1 || atoi(argv[3]) > 3) {
				printf("Number should be between 1 and 3, inclusive. Exiting program.\n");
				action = 0;
			}
		else if (action == 0)
			printf("Improper command line input. Use flag \"-h\" as the last argument for help. Exiting program.\n");
		
	return action;
}


void non_blocking_pattern(int action, int things){

	// < 5 == thread, >= 5 == process
	if (action < 5) {
		// thread things
		
		}
	
	// process things
	else {
		
		}	
};

void blocking_pattern(int action, int num_things){

	pthread_t threads[num_things];
	
		// even = thread, odd = process
	if (action < 5) {
		// thread things
		for(int i = 0; i < num_things; i++) {
			void *arg = (void *) &i;
			printf("main() : creating thread %d\n", i+1);
			pthread_create(&threads[i], NULL, print_confirmation, arg);
	    sleep(1);
		}
	}
	// process things
	else {
		for(int i = 0; i < num_things; i++) {
			

		}
	}
};

void heap_pattern(int action, int things){

};


void *print_confirmation(void *threadid) {
   //long tid = (long)threadid;
   //printf("Thread created! Thread ID, %ld\n", (long)threadid/*tid*/);
   printf("Thread created with blocking pattern. Waiting...\n");
   pthread_exit(NULL);
};

//project 4
//even: divide by 2, replace with a diff number
//odd: multiply by 3, add 1















