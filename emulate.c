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
    HALT
} Instruction;

typedef int16_t unit;

unit program[10] = {
    PUSH, 10,
    PUSH, 5,
    ADD,
    JUMP, 0,
    HALT
};

unit memory[512] = {0};
unit stack[64] = {0};
unit ip = 0; // Instruction pointer
unit sp = 0; // Stack pointer

void loadProgramIntoMemory();
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

int main(int argc, char **argv){
    printf("Loading program into memory...\n");
    loadProgramIntoMemory();

    printf("Entering main loop...\n");
    while(true){
        dump(stack, 5, sp);

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


void push(){
    printf("pushing %d\n", memory[ip+1]);
    stack[sp] = memory[ip+1];
    sp++;
    ip++;
}

unit pop(){
    unit val = stack[sp-1];
    stack[sp-1] = 0;
    sp--;

    printf("pop %d\n", val);

    return val;
}

void add(){
    int num0 = pop();
    int num1 = pop();

    stack[sp] = num0 + num1;

    printf("%d + %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void sub(){
    int num1 = pop();
    int num0 = pop();

    stack[sp] = num0 - num1;

    printf("%d - %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void mul(){
    int num0 = pop();
    int num1 = pop();

    stack[sp] = num0 * num1;

    printf("%d * %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void div(){
    int num1 = pop();
    int num0 = pop();

    stack[sp] = num0 / num1;

    printf("%d / %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void set(){
    unit pos = memory[ip+1];
    unit val = memory[ip+2];

    memory[pos] = val;

    ip += 2;

    printf("set memory position %d = %d\n", pos, val);
}

void jump(){
    unit pos = memory[ip+1];

    ip = pos;

    printf("jump to memory location %d\n", pos);
}
