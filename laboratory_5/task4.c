#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	FILE *f1;
	FILE *f2;
	char symbol;
	struct stat buff;

	if (argc != 3){
		printf("Invalid number of arguments\n");
		return 1;
	}

	if((f1 = fopen(argv[1], "r")) && (f2 = fopen(argv[2], "w"))){
		stat(argv[1], &buff);
		chmod(argv[2], buff.st_mode);

		symbol = fgetc(f1);
		while(1){
			if(symbol != EOF){
				putc(symbol, f2);
				symbol = fgetc(f1);	
			}
			else if(feof(f1) != 0){
				return 0;
			}
			else{
				printf("File read error\n");
				return 1;
			}
		}
		fclose(f1);
		fclose(f2);
	}
	else{
		printf("File read error\n");
		return 1;
	}


	return 0;
}