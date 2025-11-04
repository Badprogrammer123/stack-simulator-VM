#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define STACK_CAPACITY 100

#define RAM_CAPACITY 200

int load_program_and_decode(int *ram, int *ip); 

int execute(int *ram, int *stack, int *ip,  int *top);

void push(int* stack, int* ip, int *top);

void pop(int* stack, int* top);

int main(){

	bool running = true; 
	int stack[STACK_CAPACITY], ram[RAM_CAPACITY], *ip = ram, current_pos = 99, *top = &current_pos; 
	char commands[20];
	while(running){
		scanf("%s", commands); 
		if(strcmp(commands, "LOAD") == 0){
			if(load_program_and_decode(ram, ip)){
				printf("======PROGRAM LOADED SUCCESSFULLY=====\n");
			}
			else{
				printf("======PROGRAM FAILED TO LOAD=====\n");
			}
		}
		if(strcmp(commands, "EXECUTE") == 0){
			if(execute(ram, stack, ip, top)){
				printf("=====PROGRAM EXECUTED SUCCESSFULLY=====\n");
			}
			else{
				printf("=====PROGRAM FAILED TO EXECUTE=====\n");
			}
		}

		if(strcmp(commands, "PEEK") == 0){
			printf("STACK: \n");
			for(int i = 0; *top + i < 100; i++){
				printf("<%c>", stack [(*top) + i]);
			}
		}
	} 
}


int load_program_and_decode(int *ram, int *ip){
	FILE *file = fopen("main.txt", "r");
	char command[200];
	char value[50];
	int ramPOS = 0;
	while(fscanf(file, "%s", command) != EOF){
		if(strcmp(command, "PUSH") == 0){
			ram[ramPOS++] = '?'; 
			ram[ramPOS++] = '0';
			fscanf(file, "%s", value);
			for(int i = 0; value[i] != '\0'; i++){
				ram[ramPOS++] = value[i];
			}
		}

		if(strcmp(command, "POP") == 0){
                        ram[ramPOS++] = '?';
                        ram[ramPOS++] = '1';
                }
		

		if(strcmp(command, ">") == 0){
			ram[ramPOS++] = '>';
		}
		ram[ramPOS++] = '*';
	}	
	for(int i =0; i < 22; i ++) printf("%c", *(ram + i));
	return 1;

}


int execute(int *ram, int *stack, int *ip, int *top){
	int move_ip = 0;
	while(*(ip + move_ip) != (int)'>'){
		if(*(ip + move_ip) == (int)'?' ){
			move_ip++;
			if(*(ip + move_ip) == (int)'0'){
				while(*(ip + move_ip++) != (int)'*'){
					push(stack, ip + move_ip, top);
				}
			}
			if(*(ip + move_ip) == (int)'1'){
				while(stack[(*top)++] != (int)'*' && (*top) < 100);
				while(*(ip + move_ip++) != (int)'*'){
					pop(stack, top);
					//printf("%c", *(ip + move_ip));
				}
				//printf("%c", *(ip + move_ip));
			}
		}
	}
	*ip = move_ip; 
	return 1; 
}

void push(int *stack, int *ip, int *top){
	stack[(*top)--] = *ip;
}

void pop(int* stack, int* top){
	stack[*top] = '\0';
}
