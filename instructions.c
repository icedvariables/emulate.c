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

    ip = pos - 1; // have to minus 1 because the main loop increases the ip straight after

    printf("jump to memory location %d\n", pos);
}

void print(){
    unit val = pop();

    printf("%d", val);
}
