#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>

const char* get_current_time(){
	struct timeval cur_time;
	gettimeofday(&cur_time, NULL);
	int milli = cur_time.tv_usec / 1000;

	char buffer[80];
	strftime(buffer, 80, "%H:%M:%S", localtime(&cur_time.tv_sec));

	static char current_time[84] = "";
	sprintf(current_time, "%s:%03d", buffer, milli);
	
	return current_time;
}

int find_milsec(const char* time){
	static char milsec[8] = {}; 
	sprintf(milsec, "%c%c%c%c%c", time[6], time[7], time[9], time[10], time[11]);
	int old = atoi(milsec);

	return old;
}

void create_child(int n_gen, int n_child, pid_t parent_pid, int current_gen, \
	pid_t (*data)[3], pid_t root){
	if (current_gen == n_gen){
		return;
	}
		for (int i = 0; i < n_child; i++){
			if (getpid() == parent_pid){
		    	pid_t pid = fork();
		    	if (pid == 0){
		    		int number = getpid() - root + 1;
		    		data[number][0] = getpid();
		    		data[number][1] = parent_pid;
		    		data[number][2] = number*200;
		    		const char* old_cur_time = get_current_time();
		    		data[number][3] = find_milsec(old_cur_time);

		    		current_gen++;
		    		parent_pid = getpid();
		    		create_child(n_gen, n_child, parent_pid, current_gen, data, root);
		    		return;
		    	}
			}
	}
	return;
}

int main(int argc, const char* argv[])
{
	pid_t parent_pid, root, root_parent;
	int current_gen = 0;

	if (argc != 3){
		printf("Invalid number of arguments\n");
		return 1;
    }

    int n_gen = atoi(argv[1]);
    int n_child = atoi(argv[2]);
    pid_t data[100][3] = {};

    root = getpid();
    root_parent = getppid();
    data[1][0] = getpid();
    data[1][1] = getppid();
    data[1][2] = 200;
    const char* old_cur_time = get_current_time();
    data[1][3] = find_milsec(old_cur_time);
    create_child(n_gen, n_child, root, current_gen, data, root);

    const char* time;
    int number;
    int result_time;

    while (1){
		number = getpid() - root + 1;
		time = get_current_time();
		result_time = find_milsec(time);
		if (result_time >= (data[number][3] + data[number][2])){
		    printf("number=%d, pid=%d, ppid=%d, time=%s\n", \
		    	number, data[number][0], data[number][1], time);
		    data[number][3] = result_time;
		}
    }

    return 0;
}