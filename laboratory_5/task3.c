#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *f;
	char symbol;

	if (argc != 3){
		printf("Invalid number of arguments\n");
		return 1;
	}

	int n = atoi(argv[2]);

	if(f = fopen(argv[1], "r")){
		if (n == 0){
			symbol = fgetc(f);
			while(symbol != EOF){
				printf("%c", symbol);
				symbol = fgetc(f);
			}
		}
		else{
			while(1){
				for(int i = 0; i < n; i++){
					symbol = fgetc(f);
					if(symbol != EOF){ 
						while(symbol != '\n'){
							printf("%c", symbol);
							symbol = fgetc(f);
						}
						printf("\n");
					}
					else if(feof(f) != 0){
						return 0;
					}
					else{
						printf("File read error\n");
						return 1;
					}
				}
				getchar();
			}
		}
		fclose(f);
	}
	else{
		printf("File read error\n");
		return 1;
	}

	return 0;
}