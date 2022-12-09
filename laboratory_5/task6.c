#include <stdio.h>
#include <dirent.h> 
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void print_in_file_str(FILE* f, char* str){
	int str_len = strlen(str);
	for(int i = 0; i < str_len; i++){
		putc(str[i], f);
	}
	putc(*" ", f);
}

void print_in_file_int(FILE* f, int number){
	char number_str[number];
	sprintf(number_str, "%d", number);
	print_in_file_str(f, number_str);
	putc(*" ", f);
}

void print_in_file_path(FILE* f, const char* path){
	int str_len = strlen(path);
	for(int i = 0; i < str_len; i++){
		putc(path[i], f);
	}
	putc(*" ", f);
}

int check_size(const char *path, int recursive, FILE* f)
{
    struct dirent *direntp;
    DIR *dir;
    size_t path_len;

    path_len = strlen(path);
    dir = opendir(path);
    if (!dir){
    	printf("Directory read error\n");
        return 1;	
    }

    int size = 0;
	int count = 0;
	char* max_file = "";
	int max_file_size = 0;
    while ((direntp = readdir(dir)) != NULL)
    {
        struct stat fstat;
        char full_name[PATH_MAX + 1];

        if ((path_len + strlen(direntp->d_name) + 1) > PATH_MAX)
            continue;

        strcpy(full_name, path);
        if (full_name[path_len - 1] != '/')
            strcat(full_name, "/");
        strcat(full_name, direntp->d_name);

        if ((strcmp(direntp->d_name, ".") == 0) ||
            (strcmp(direntp->d_name, "..") == 0))
            continue;

        if(direntp->d_type != DT_DIR){
				count++;
				stat(direntp->d_name, &fstat);
				size += fstat.st_size;
				if(fstat.st_size > max_file_size){
					max_file_size = fstat.st_size;
					max_file = direntp->d_name;
				}
			}

        if (stat(full_name, &fstat) < 0)
            continue;
        if (S_ISDIR(fstat.st_mode))
        {
            if (recursive)
                check_size(full_name, 1, f);
        }
    }
    printf("%s, %d, %d, %s\n", path, count, size, max_file);
	print_in_file_path(f, path);
	print_in_file_int(f, count);
	print_in_file_int(f, size);
	print_in_file_str(f, max_file);
	putc(*"\n", f);

    closedir(dir);
    return 0;
}

int main(int argc, const char* argv[])
{
	FILE *f;

    if (argc != 3){
		printf("Invalid number of arguments\n");
		return 1;
    }


    if(f = fopen(argv[2], "w")){
		check_size(argv[1], 1, f);
    }
    else{
		printf("File read error\n");
		return 1;
	}

    return 0;
}