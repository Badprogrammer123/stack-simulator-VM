#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define STACK_CAPACITY 100

#define RAM_CAPACITY 200

#define COMMAND_OPCODE 63

#define POSITION 0

void load_program(int *ram, int *ip); 

void decode_and_executes(int *ram, int *stack, int *ip,  int *top);

void push(int* stack, int* ip, int *top);

int main(){

	bool running = true; 
	int stack[STACK_CAPACITY], ram[RAM_CAPACITY], *ip = ram, current_pos = 99, *top = &current_pos; 
	char commands[20];
	while(1){
		scanf("%s", commands); 
		if(strcmp(commands, "LOAD") == 0){
			printf("=====LOADING PROGRAM=====\n");
			load_program(ram, ip);
		}
		else if(strcmp(commands, "EXECUTE") == 0){
			printf("======EXECUTING PROGRAM=====\n");
			decode_and_executes(ram, stack, ip, top);
		}
	} 
}


void load_program(int *ram, int *ip){
	FILE *file = fopen("main.txt", "r");
	char command[100];
	char value[50];
	int ramPOS = 0;
	while(fscanf(file, "%s", command) != EOF){
		fscanf(file, "%s", value);
		if(strcmp(command, "PUSH") == 0){
			ram[ramPOS++] = '?'; 
			ram[ramPOS++] = '0';
			for(int i = 0; value[i] != '\0'; i++){
				ram[ramPOS++] = value[i];
			}
			
		}
		ram[ramPOS++] = '*';
	}	
	for(int i = 0; i < 10; i++) printf("%c", ram[i]);
	fclose(file);

}


void decode_and_executes(int *ram, int *stack, int *ip, int *top){
	int move_ip = 0;
	int duration = -1;
	while(duration != move_ip){
		if(*(ip + move_ip) == (int)'?' ){
			move_ip++;
			if(*(ip + move_ip) == (int)'0'){
				while(*(ip + move_ip++) != (int)'*'){
					push(stack, ip + move_ip, top);
				}
			}
			
		}
		else{
			printf("****ERROR: PROGRAM FAILED TO BE EXECUTED****\n");
			break;
		}
		duration++;
	}
}

void push(int *stack, int *ip, int *top){
	stack[*top] = *ip;
	printf("<%c>", stack[*top]);
	(*top)--;
}
