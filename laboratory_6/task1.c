#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


void print_current_time(){
	struct timeval cur_time;
	gettimeofday(&cur_time, NULL);
	int milli = cur_time.tv_usec / 1000;

	char buffer[80];
	strftime(buffer, 80, "%H:%M:%S", localtime(&cur_time.tv_sec));

	char current_time[84] = "";
	sprintf(current_time, "%s:%03d", buffer, milli);
	printf("current time: %s \n", current_time);
}


int main()
{
	pid_t pid;
	pid_t pid2;

	pid = fork();
	if (pid == 0) {
		printf("First child process pid=%d\n", getpid());
		printf("First child process parent pid=%d\n", getppid());
		print_current_time();
		exit(0);
	}
	if (pid > 0){
		pid2 = fork();
			if (pid2 == 0) {
			printf("Second child process pid=%d\n", getpid());
			printf("Second child process parent pid=%d\n", getppid());
			print_current_time();
			exit(0);
		}
	}
	if (pid > 0 && pid2 > 0){
		printf("Parent process pid=%d\n", getpid());
		printf("Parent process parent pid=%d\n", getppid());
		print_current_time();
		system("ps -x");
	}
}