#include"stack.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

double pop_n(stack_calculator *stack)
{
    double lastNum = 0.0;
    if (stack->head_n == NULL)
    {
        return lastNum;
    }
    if (stack->head_n->next == NULL)
    {
        lastNum = stack->head_n->num;
        free(stack->head_n);
        stack->head_n = NULL;
        return lastNum;
    }
    stack_numbers *current = stack->head_n;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    lastNum = current->next->num;
    free(current->next);
    current->next = NULL;
    return lastNum;
}

char pop_o(stack_calculator *stack)
{
    char lastOperation = ' ';
    if (stack->head_o == NULL)
    {
        return lastOperation;
    }
    else if (stack->head_o->next == NULL)
    {
        lastOperation = stack->head_o->operation;
        free(stack->head_o);
        stack->head_o = NULL;
        return lastOperation;
    }
    stack_operations *current = stack->head_o;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    lastOperation = current->next->operation;
    free(current->next);
    current->next = NULL;
    return lastOperation;
}

void delete_n(stack_calculator *stack)
{
    while (stack->head_n != NULL)
    {
        pop_n(stack);
    }
}

void delete_o(stack_calculator *stack)
{
    while (stack->head_o != NULL)
    {
        pop_o(stack);
    }
}

void pushback_stack_n(double data, stack_calculator *stack)
{
    if (stack->head_n == NULL)
    {
        stack->head_n = malloc(sizeof(stack_numbers));
        stack->head_n->next = NULL;
        stack->head_n->num = data;
        return;
    }
    stack_numbers *current = stack->head_n;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(stack_numbers));
    current->next->num = data;
    current->next->next = NULL;
}

void pushback_stack_o(char data, stack_calculator *stack)
{
    if (stack->head_o == NULL)
    {
        stack->head_o = malloc(sizeof(stack_operations));
        stack->head_o->operation = data;
        stack->head_o->next = NULL;
        return;
    }
    stack_operations *current = stack->head_o;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(stack_operations));
    current->next->operation = data;
    current->next->next = NULL;
}
