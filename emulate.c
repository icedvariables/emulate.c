#include <stdio.h>
#include <stdint.h>

// C doesn't have booleans...
#define true 1
#define false 0

typedef enum{
    PUSH = 1,
    POP,
    SET,
    ADD,
    SUB,
    HALT
} Instruction;

typedef int16_t unit;

unit program[10] = {
    PUSH, 5,
    PUSH, 10,
    ADD,
    HALT
};

unit memory[512] = {0};
unit stack[64] = {0};
unit ip = 0;
unit sp = 0;

void loadProgramIntoMemory();
unit getInstruction();
void evalInstruction(unit instr);
void dump(unit array[], int length);
void push();
void pop();
void add();

int main(int argc, char **argv){
    printf("Loading program into memory...\n");
    loadProgramIntoMemory();

    dump(memory, 10);

    printf("Entering main loop...\n");
    while(true){
        dump(stack, 5);

        unit instr = getInstruction();

        if(instr == HALT)
            break;
        else
            evalInstruction(instr);

        ip++;
    }

    printf("Halting...");

    return 0;
}

void loadProgramIntoMemory(){
	for(int i = 0; i < 10; i++){
        memory[i] = program[i];
    }
}

unit getInstruction(){
    return memory[ip];
}

void evalInstruction(unit instr){
    switch(instr){
        case PUSH:
            push();
            break;

        case POP:
            pop();
            break;

        case ADD:
            add();
            break;
    }
}

void dump(unit array[], int length){
    printf("Dump (length=%d):\n", length);

    for(int i = 0; i < length; i++){
        printf("%d: %d\n", i, array[i]);
    }

    printf("\n\n");
}


void push(){
    printf("Pushing %d\n", memory[ip+1]);
    stack[sp] = memory[ip+1];
    sp++;
    ip++;
}

void pop(){
    printf("Pop %d\n", stack[sp-1]);
    stack[sp-1] = 0;
    sp--;
}

void add(){
    int num0 = stack[sp-1];
    int num1 = stack[sp-2];

    stack[sp-1] = 0;
    stack[sp-2] = 0;
    sp -= 2;

    stack[sp] = num0 + num1;

    printf("%d + %d = %d\n", num0, num1, stack[sp]);

    sp++;
}
