/*Write a program that takes three arguments: the number of “things” (between 1 and 256), a word: either “thread” or “process, and a “pattern number” (1-3 only).

Create as many subprocesses or threads (“things”) as the number. Obviously, create either processes or threads as the command-line argument dictates.

Implement the forking/threading pattern as below. Arrows represent which process or thread creates the next process/thread.

Each process or thread should output (say) “Process 3 beginning”, then sleep for a random number of seconds (say, 1-8). If it created processes/threads, it should output a message "Process 3 creating Process 4", then wait for them to complete, then output “Process 3 exiting”. 

 


Error checking: Check the inputs. If there is an error, emit the error and output how to invoke the program.

//DONE
Help: implement a simple and SHORT -h (AND –help) to explain valid parameters.

//DONE
Debug: implement a “-d” parameter that outputs any debug log messages you have created.

*/

/*
sleazy developer notes
running with -debug flag and a message logs to debug_log file, ex: ./main debug "my debug logs are not sleazy crap"; this is not disclosed in the instruction prompt
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 	 //sleep() -> man sleep for deets
#include <sys/types.h> // fork()
#include <pthread.h>
#include <string.h>

int error_checking(int argc, char *argv[]);
int command_line_input(int argc, char *argv[]); // evaluates which action and pattern to use
void input_debug_log(char* argv[]); // <- APPENDS a file with debug log messages
void output_debug_log(); // <- outputs file contents and exits without doing anything else

void non_blocking_pattern(int action, int num_things); // things = how many threads or sub-processes to create
void blocking_pattern(int action, int things); 				 // action = thread or process
void heap_pattern(int action, int things);

void *print_confirmation(void *threadid); // thread creation confirmation	


int main(int argc, char *argv[]) {

	// check for improper input before going further
	if(error_checking(argc, argv))
		return 0;
	
	/*
	int num_things = atoi(argv[1]),
			pattern = command_line_input(argc, argv);
	
	switch(pattern) {
		case 0: 
			return 0;
		case 2:
				printf("thread, non-blocking\n");
			break;
		case 3:
				printf("thread, blocking\n");
				blocking_pattern(3, num_things);
			break;
		case 4:
				printf("thread, heap\n");
			break;
		case 6:
				printf("process, non-blocking\n");
			break;
		case 7:
				printf("process, blocking\n");
				blocking_pattern(7, num_things);
			break;
		case 8:
				printf("process, heap\n");
			break;
	}
			*/
			
			printf("no error\n");
	return 0;
}

int error_checking(int argc, char *argv[]) {
	int result = 1; // if no error, change to 0

	// program-ending cases
	if(argc <= 1 || argc > 4 || strstr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()+=-`~_,./[]\\<>?{}|;:\'\"", argv[1]))
		printf("Improper command line input. Use flag \"-h\" or \"-help\" as the only argument for instructions. Exiting program.\n");
		
	else if(strcmp(argv[argc-1], "-h") == 0 || strcmp(argv[argc-1], "-help") == 0) // only checks first character? every character is an argument in argv[]
		printf("This program takes in 3 command line arguments. \nFirst is a number between 1 and 256 (inclusive).\nSecond is a word, either \"thread\" or \"process\".\nThird is a number indicating the pattern to use. 1 is for non-blocking, 2 is for blocking, 3 is for heap.\n");
		
	else if(strcmp(argv[argc-1], "-d") == 0)
		output_debug_log();
		
	else if(strcmp(argv[1], "-debug") == 0) {
		printf("Debug notes logged.\n");
		input_debug_log(&argv[2]);
	}
	else if(atoi(argv[1]) < 1 || atoi(argv[1]) > 256) // mistakenly compares ASCII values if any satisfactory input exists beforehand
		printf("First number should be between 1 and 256, inclusive. Use flag -h for more information. Exiting program.\n");
	
	else if(atoi(argv[3]) < 1 || atoi(argv[3]) > 3)  // same as above
		printf("Second number should be between 1 and 3, inclusive. Use flag -h for more information. Exiting program.\n");	
		
	else if(strcmp(argv[2], "thread") != 0 || strcmp(argv[2], "process") != 0)
		printf("Please enter either \"thread\" or \"process\" for second argument. Use flag -h for more information.\n");
		
	else 
		result = 0;

	return result;
}

void input_debug_log(char* argv[]){
  char db_log[30] = "debug_log";
  FILE *filename;
  
  filename = fopen(db_log,"a");
  fputs(*argv, filename);
  fputs("\n--------END DEBUG LOG--------\n\n", filename);

  fclose(filename);	
};

void output_debug_log(){
  char db_log[30] = "debug_log",
  		 character;
  FILE *filename;
  
  filename = fopen(db_log,"r");
	printf("Debug Logs:\n\n");
  while ((character = getc(filename)) != EOF) 
  	printf("%c", character);
  
  fclose(filename);	
};




int command_line_input(int argc, char *argv[]) {

	// action == 2/3/4 => thread 
	// action == 6/7/8 => process
	int action;
		
		// evaluate second argument (action)
		if(strcmp(argv[2], "thread") == 0) {
			printf("thread\n");
			action = 1; 
		}
		else if(strcmp(argv[2], "process") == 0) {
			printf("process\n");
			action = 5;
		}
		else
			return 0;
	
		
		// evaluate pattern	
		if (atoi(argv[3]) == 1) {
			printf("non-blocking\n");
			action += 1; // 2 or 6
		}
		else if (atoi(argv[3]) == 2) {
			printf("blocking\n");
			action += 2; // 3 or 7
		}
		else if (atoi(argv[3]) == 3) {
			printf("heap\n");
			action += 3; // 4 or 8
		}
		
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
	
	// thread things
	if (action < 5) {
		pthread_t threads[num_things];

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
			fork();
			printf("Forked sub-process.\n");
			exit(1);
		}
	}
};

void heap_pattern(int action, int things){

};


void *print_confirmation(void *threadid) {
   //long tid = (long)threadid;
   //printf("Thread created! Thread ID, %ld\n", tid);
   printf("Thread created with blocking pattern. Waiting...\n");
   pthread_exit(NULL);
};

//project 4
//even: divide by 2, replace with a diff number
//odd: multiply by 3, add 1















