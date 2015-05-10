void push();
unit pop();
void add();
void sub();
void mul();
void div();
void set();
void jump();
void print();
void jumpIfEqual();
void jumpIfNotEqual();


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
    unit num0 = pop();
    unit num1 = pop();

    stack[sp] = num0 + num1;

    printf("%d + %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void sub(){
    unit num1 = pop();
    unit num0 = pop();

    stack[sp] = num0 - num1;

    printf("%d - %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void mul(){
    unit num0 = pop();
    unit num1 = pop();

    stack[sp] = num0 * num1;

    printf("%d * %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void div(){
    unit num1 = pop();
    unit num0 = pop();

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

    printf("OUTPUT: %d\n", val);
}

void jumpIfEqual(){
    unit num0 = pop();
    unit num1 = pop();

    printf("jump if equal %d == %d\n", num0, num1);

    if(num0 == num1)
        jump();
}

void jumpIfNotEqual(){
    unit num0 = pop();
    unit num1 = pop();

    printf("jump if not equal %d != %d\n", num0, num1);

    if(num0 != num1)
        jump();
}
