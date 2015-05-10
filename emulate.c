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
    MUL,
    DIV,
    JUMP,
    HALT,
    PRINT
} Instruction;

typedef uint8_t unit;

unit memory[512] = {0};
unit stack[64] = {0};
unit ip = 0; // Instruction pointer
unit sp = 0; // Stack pointer

void loadProgramIntoMemory(char filename[]);
unit getInstruction();
void evalInstruction(unit instr);
void dump(unit array[], int length, int pointer);
void push();
unit pop();
void add();
void sub();
void mul();
void div();
void set();
void jump();
void print();

#include "instructions.c"

int main(int argc, char **argv){
    printf("Loading program into memory...\n");
    loadProgramIntoMemory(argv[1]);

    printf("Entering main loop...\n");

    for(int loopIteration = 0;;loopIteration++){
        printf("\n\nMain loop %d: ip=%d sp=%d\n", loopIteration, ip, sp);
        printf("\nStack ");dump(stack, 5, sp);
        printf("Memory ");dump(memory, 10, sp);

        unit instr = getInstruction();

        if(instr == HALT)
            break;
        else
            evalInstruction(instr);

        ip++;
    }

    printf("Halting...");

    printf("\nMemory ");dump(memory, 20, ip);
    printf("\nStack ");dump(stack, 10, sp);

    return 0;
}

void loadProgramIntoMemory(char filename[]){
	FILE *f;

    f = fopen(filename, "rb");
    fread(memory, sizeof(memory), 1, f);
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

        case SUB:
            sub();
            break;

        case MUL:
            mul();
            break;

        case DIV:
            div();
            break;

        case SET:
            set();
            break;

        case JUMP:
            jump();
            break;

        case PRINT:
            print();
            break;

        default:
            printf("Unknown value %d - ignoring", instr);
    }
}

void dump(unit array[], int length, int pointer){
    printf("Dump (length=%d):\n", length);

    for(int i = 0; i < length; i++){
        if(pointer == i)
            printf("--> ");
        else
            printf("    ");
        printf("%d: %d\n", i, array[i]);
    }

    printf("\n\n");
}
