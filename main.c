/**
 * Anthony Sare
 * sarea@uoguelph.ca
 * CIS*2520 Assignment 2 Question 2
 * Calculates Postfix result from command line input
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Operand stack struct
typedef struct stack{
    double value;
    struct stack *next;
}stack_t;

//Function prototypes
void push(stack_t **top, double val);
double pop(stack_t **top);
double operation(char op, double val1, double val2);
void printStack(stack_t *toPrint);
double postFix(char *expression);
int stringLength(char *toCheck);
int checkArg(char *toCheck);

int main(int argc, char *argv[]) {
    //Declaring variables
    char *expression;
    double result;


    //Checking that command line arg is valid and end if not
    if(checkArg(argv[1])==1){
        expression =argv[1];
    }else{
        printf("Invalid command line argument");
        return 0;
    }

    //Processing and output
    result = postFix(expression);
    printf("Postfix result =  %.2lf\n", result);

    return 0;
}

/**
 * Checks the length of the command line argument
 * @param toCheck String to check length of
 * @return length of string
 */
int stringLength(char *toCheck){
    int i;
    for ( i = 0; toCheck[i] != '\0' ; i++);
    return i;
}

/**
 * Checks that the command line argument is a valid postfix expression
 * @param toCheck expression to check
 * @return 1 if valid, -1 if not
 */
int checkArg(char *toCheck){
    for ( int i = 0; toCheck[i] != '\0' ; i++){
        if(isdigit(toCheck[i]) == 0 && toCheck[i] != '+' && toCheck[i] != '-' && toCheck[i] != '*'&& toCheck[i] != '/'){
            return -1;
        }
    }
    return 1;
}

/**
 * Calculates postfix expression
 * @param expression postfix expression to calculate
 * @return result of postfix expression with 2 decimals
 */
double postFix(char *expression){
    //Declare and initialize operand stack
    stack_t *operand;
    operand = NULL;
    //Get size of expression
    int size = stringLength(expression);
    //Iterate through characters and perform proper calculations
    for (int i = 0; i < size; ++i) {
        //If char is digit, add to stack
        if(isdigit(expression[i])!=0){
            push(&operand, expression[i]-'0');
        //If char is operator, push result of operation
        }else if(isdigit (expression[i]) == 0){
            push(&operand, operation(expression[i], pop(&operand), pop(&operand)));
        }
    }
    //Return remaining element in stack
    return pop(&operand);
}
/**
 * Test function to print stack
 * @param toPrint stack to print
 */
void printStack(stack_t *toPrint){
    stack_t *current;
    current = toPrint;
    while(current != NULL){
        printf("%.2lf : ", current->value);
        current = current->next;
    }
    printf("\n");
}

/**
 * Performs operation based on char given
 * @param op operator
 * @param val1 value one of expression
 * @param val2 value two of expression
 * @return result of expression
 */
double operation(char op, double val1, double val2){
    double result =0 ;
    //Check ASCII values of the char and perform operation accordingly
    switch (op){
        case 42: // Multiplication *
            result = val1 * val2;
            break;
        case 43: // Addition +
            result = val1 + val2;
            break;
        case 45: // Subtraction -
            result = val1-val2;
            break;
        case 47: // Division /
            result = val1/val2;
            break;
        default:
            printf("Invalid operation\n");
            break;
    }
    //Testing print statement
    //printf("%lf %c %lf = %.2lf\n",val1, op, val2, result );
    return result;
}

/**
 * Push value to stack
 * @param top Top of stack
 * @param val Value to push
 */
void push(stack_t **top, double val){
    //Creating new stack element
    stack_t *toAdd;
    toAdd = malloc(sizeof(stack_t));

    //Adding to top
    toAdd->value = val;
    toAdd->next = *top;
    *top = toAdd;
}

/**
 * Pop value from stack
 * @param top top of stack
 * @return value of popped element
 */
double pop(stack_t **top){
    //Declare value and temp stack
    double val;
    stack_t *temp;
    //Check if stack is empty
    if(*top == NULL){
        return 0;
    //Move next item to top and return old tops value
    }else{
        temp = *top;
        *top = temp->next;
        val = temp->value;
        free(temp);
        return val;
    }
}

