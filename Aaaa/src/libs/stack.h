#if !defined(stackh)
#define stackh

typedef struct stack_numbers
{
    double num;
    struct stack_numbers *next;
} stack_numbers;

typedef struct stack_operations
{
    char operation;
    struct stack_operations *next;
} stack_operations;

typedef struct stack_calculator
{
    stack_numbers *head_n;
    stack_operations *head_o;
} stack_calculator;

stack_calculator stack_calc;

double pop_n(stack_calculator *stack);

char pop_o(stack_calculator *stack);

void delete_n(stack_calculator *stack);

void delete_o(stack_calculator *stack);

void pushback_stack_n(double data, stack_calculator *stack);

void pushback_stack_o(char data, stack_calculator *stack);

#endif
