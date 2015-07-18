void push(){
    /*
     * Push a value onto the stack.
     */

    printf("pushing %d\n", memory[ip+1]);
    stack[sp] = memory[ip+1];
    sp++;
    ip++;
}

unit pop(){
    /*
     * Pop a value off the stack.
     */

    unit val = stack[sp-1];
    stack[sp-1] = 0;
    sp--;

    printf("pop %d\n", val);

    return val;
}

void add(){
    /*
     * Pop two values off the stack, add them together and push the result.
     */

    unit num0 = pop();
    unit num1 = pop();

    stack[sp] = num0 + num1;

    printf("%d + %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void sub(){
    /*
     * Pop two values off the stack, subtract the top value from the other and
     * push the result.
     */

    unit num1 = pop();
    unit num0 = pop();

    stack[sp] = num0 - num1;

    printf("%d - %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void mul(){
    /*
     * Pop two values off the stack, multiply them and push the result.
     */

    unit num0 = pop();
    unit num1 = pop();

    stack[sp] = num0 * num1;

    printf("%d * %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void div(){
    /*
     * Pop two values off the stack, divide the second to top value by the top
     * and push the result.
     */

    unit num1 = pop();
    unit num0 = pop();

    stack[sp] = num0 / num1;

    printf("%d / %d = %d\n", num0, num1, stack[sp]);

    sp++;
}

void set(){
    /*
     * Set memory[top of stack] to the value second to the top of stack.
     */

    unit pos = memory[ip+1];
    unit val = memory[ip+2];

    memory[pos] = val;

    ip += 2;

    printf("set memory position %d = %d\n", pos, val);
}

void jump(){
    /*
     * Jump to memory location at the top of the stack.
     */

    unit pos = memory[ip+1];

    ip = pos - 1; // have to minus 1 because the main loop increases the ip straight after

    printf("jump to memory location %d\n", pos);
}

void print(){
    /*
     * Output the value at the top of the stack
     */

    unit val = pop();

    printf("OUTPUT: %d\n", val);
}

void jumpIfEqual(){
    /*
     * Jump to the memory location at the third to the top of the stack if the first
     * and second value on the stack are equal.
     */

    unit num0 = pop();
    unit num1 = pop();

    printf("jump if equal %d == %d\n", num0, num1);

    if(num0 == num1)
        jump();
}

void jumpIfNotEqual(){
    /*
     * Jump to the memory location at the third to the top of the stack if the first
     * and second value on the stack are not equal.
     */

    unit num0 = pop();
    unit num1 = pop();

    printf("jump if not equal %d != %d\n", num0, num1);

    if(num0 != num1)
        jump();
}

void jumpIfGreaterThan(){
    /*
     * Jump to the memory location at the third to the top of the stack if the first
     * value is greater than the second.
     */
    unit num0 = pop();
    unit num1 = pop();

    printf("jump if greater than %d > %d\n", num0, num1);

    if(num0 > num1)
        jump();
}

void jumpIfLessThan(){
    /*
     * Jump to the memory location at the third to the top of the stack if the first
     * value is less than the second.
     */

    unit num0 = pop();
    unit num1 = pop();

    printf("jump if less than %d < %d\n", num0, num1);

    if(num0 < num1)
        jump();
}
