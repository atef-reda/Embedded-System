#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "MCAL_layer/mcal_std_types.h"

uint16 error=0;
// Stack structure definition
typedef struct {
    int top;
    unsigned capacity;
    int* array;
} Stack;

// Function to create a stack
Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Push an element to the stack
void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        error=555;
        return;
    }
    stack->array[++stack->top] = item;
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        error=555;
        return -1;
    }
    return stack->array[stack->top--];
}

// Get the top element of the stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        error=555;
        return -1;
    }
    return stack->array[stack->top];
}

// Function to check if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to get the precedence of an operator
int getPrecedence(char operator) {
    if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '+' || operator == '-')
        return 1;
    else
        return 0;
}

// Function to convert infix expression to postfix notation
void infixToPostfix12(const char* infix, char* postfix) {
    Stack* stack = createStack(strlen(infix));
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        if (isspace(infix[i])) {
            continue;
        }
        else if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (isOperator(infix[i])) {
            while (!isEmpty(stack) && isOperator(peek(stack)) && getPrecedence(peek(stack)) >= getPrecedence(infix[i])) {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            push(stack, infix[i]);
        }
        else if (infix[i] == '(') {
            push(stack, infix[i]);
        }
        else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
                postfix[j++] = ' ';
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                pop(stack);
            }
            else {
                printf("Invalid expression: Unbalanced parentheses\n");
                error=555;
                return;
            }
        }
        else {
            printf("Invalid character in expression: %c\n", infix[i]);
            error=555;
            return;
        }
    }

    while (!isEmpty(stack)) {
        if (peek(stack) == '(') {
            printf("Invalid expression: Unbalanced parentheses\n");
            error=555;
            return;
        }
        postfix[j++] = pop(stack);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
    free(stack->array);
    free(stack);
}

// Function to evaluate the postfix expression using stack
uint32 evaluatePostfix(const char* postfix) {
    Stack* stack = createStack(strlen(postfix));
    int i, operand1, operand2, result;

    for (i = 0; postfix[i] != '\0'; i++) {
        if (isspace(postfix[i])) {
            continue;
        }
        else if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push(stack, num);
            i--;
        }
        else if (isOperator(postfix[i])) {
            operand2 = pop(stack);
            operand1 = pop(stack);

            switch (postfix[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator: %c\n", postfix[i]);
                    error=555;
                    return -1;
            }

            push(stack, result);
        }
        else {
            printf("Invalid character in expression: %c\n", postfix[i]);
            error=555;
            return -1;
        }
    }

    result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}
