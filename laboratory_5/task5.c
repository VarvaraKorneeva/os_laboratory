#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *d;
	struct dirent *ds;
	char *file_name;

	if (argc != 2){
		printf("Invalid number of arguments\n");
		return 1;
	}

	if(d = opendir(".")){
		printf("Current directory:\n");
		ds = readdir(d);
		while(ds != NULL){
			file_name = ds->d_name;
			printf("%s\n", file_name);
			ds = readdir(d);
		}
		closedir(d);
	}
	else{
		printf("Directory read error\n");
		return 1;
	}

	printf("-----------------------\n");

	if(d = opendir(argv[1])){
		printf("Directory - %s:\n", argv[1]);
		ds = readdir(d);
		while(ds != NULL){
			file_name = ds->d_name;
			printf("%s\n", file_name);
			ds = readdir(d);
		}
		closedir(d);
	}
	else{
		printf("Directory read error\n");
		return 1;
	}
	
	return 0;
}