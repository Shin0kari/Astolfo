#include"list.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

char *pop_list_out(list_calculator *results) // вроде исправлял, но пока оставлю !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    char *line;
    if (results->head_res == NULL || results->current_res == NULL)
    {
        return NULL;
    }
    else if (results->head_res == results->current_res)
    {
        line = results->current_res->ans_res;
        results->current_res = results->current_res->next;
        free(results->head_res);
        results->head_res = results->current_res;
        return line;
    }
    list_answer *term = results->head_res;
    while (term->next != results->current_res)
    {
        term = term->next;
    }
    line = results->current_res->ans_res;
    term->next = results->current_res->next;
    free(results->current_res);
    results->current_res = term;
    return line;
}

void push_list_out(char *line, list_calculator *results)
{
    if (results->head_res == NULL)
    {
        results->head_res = malloc(sizeof(list_answer));
        results->current_res = results->head_res;
    }
    else
    {
        results->current_res = results->head_res;
        while (results->current_res->next != NULL)
        {
            results->current_res = results->current_res->next;
        }
        results->current_res->next = malloc(sizeof(list_answer));
        results->current_res = results->current_res->next;
    }
    results->current_res->next = NULL;
    results->current_res->ans_res = line;
}

void deleteResults()
{
    list_calc.current_res = list_calc.head_res;
    while (list_calc.current_res != NULL)
    {
        list_calc.current_res = list_calc.head_res;
        pop_list_out(&list_calc);
    }
}

void writeAnswerToFile(FILE *outputFile)
{
    list_calc.current_res = list_calc.head_res;
    while (list_calc.current_res != NULL)
    {
        fprintf(outputFile, "%s\n", pop_list_out(&list_calc));
    }
}

// для удобства просмотра пробелы поставил просто так

void pop_list_in(list_calculator *current)
{
    if (current->head_settings == NULL || current->current_settings == NULL)
    {
        return;
    }
    else if (current->head_settings == current->current_settings)
    {
        current->current_settings = current->current_settings->next;
        current->current_n = current->current_n->next;
        if (current->head_n->number_v != NULL) // очищение массива для вект кальк если он есть
        {
            free(current->head_n->number_v);
            current->head_n->number_v = NULL;
        }
        if (current->head_settings->current_s != NULL) // очищение настроек обычного кальк
        {
            free(current->head_settings->current_s);
            current->head_settings->current_s = NULL;
        }
        if (current->head_settings->current_v != NULL) // очищение настроек вект кальк
        {
            free(current->head_settings->current_v);
            current->head_settings->current_v = NULL;
        }
        free(current->head_settings); // очищение настроек общее
        free(current->head_n);        // очищение чисел общее
        current->head_settings = NULL;
        current->head_n = NULL;
        current->head_settings = current->current_settings;
        current->head_n = current->current_n;
        return;
    }
    settings_list_calc *term_s = current->head_settings;
    list_numbers *term_n = current->head_n;
    while (term_s->next != current->current_settings)
    {
        term_s = term_s->next;
        term_n = term_n->next;
    }
    term_s->next = current->current_settings->next;
    term_n->next = current->current_n->next;
    if (current->current_n->number_v != NULL) // очищение массива для вект кальк если он есть
    {
        free(current->current_n->number_v);
        current->current_n->number_v = NULL;
    }
    if (current->current_settings->current_s != NULL) // очищение настроек обычного кальк
    {
        free(current->current_settings->current_s);
        current->current_settings->current_s = NULL;
    }
    if (current->current_settings->current_v != NULL) // очищение настроек вект кальк
    {
        free(current->current_settings->current_v);
        current->current_settings->current_v = NULL;
    }
    free(current->current_settings); // очищение настроек общее
    free(current->current_n);        // очищение чисел общее
    current->current_settings = NULL;
    current->current_n = NULL;
    current->current_settings = term_s;
    current->current_n = term_n;
}

void deleteList()
{
    list_calc.current_settings = list_calc.head_settings;
    list_calc.current_n = list_calc.head_n;
    while (list_calc.current_settings != NULL)
    {
        list_calc.current_settings = list_calc.head_settings;
        list_calc.current_n = list_calc.head_n;
        pop_list_in(&list_calc);
    }
}

void fill_list(list_calculator *example, FILE *inputFile, char *answer, int *future)
{

    char type_l;

    if (list_calc.head_settings == NULL)
    {
        example->current_settings = malloc(sizeof(settings_list_calc)); //нужно всё инициализировать
        example->current_n = malloc(sizeof(list_numbers));
        answer[0] = 'n';
        future[0] = 0;
    }

    if (future[0] == 0)
    {
        fscanf(inputFile, " %c ", &example->current_settings->calc_type);
        type_l = example->current_settings->calc_type;
        future[0] = 1;
    }
    switch (type_l)
    {
    case 'v':
        example->current_settings->current_s = NULL;
        example->current_settings->current_v = malloc(sizeof(l_v_calc));
        fscanf(inputFile, "%d", &example->current_settings->current_v->size);
        fscanf(inputFile, "%d", &example->current_settings->current_v->num);
        example->current_n->number_v = malloc((example->current_settings->current_v->num * example->current_settings->current_v->size) * sizeof(double));
        for (int i = 1; i < example->current_settings->current_v->num + 1; i++)
        {
            //printf("Введите координаты %i вектора: ", i);
            for (int j = 0; j < example->current_settings->current_v->size; j++)
            {
                fscanf(inputFile, "%lf", &example->current_n->number_v[example->current_settings->current_v->size * (i - 1) + j]);
            }
        }
        fscanf(inputFile, " %c ", &example->current_settings->current_v->operations); //какая операция с векторами
        fscanf(inputFile, " %c ", &example->current_settings->close_calculator_subspecies);
        if (example->current_settings->close_calculator_subspecies == 'e')
        {
            fscanf(inputFile, " %c ", &example->current_settings->close_file);
        }
        break;
    case 's':
        example->current_settings->current_s = malloc(sizeof(l_s_calc));
        example->current_settings->current_v = NULL;
        example->current_n->number_v = NULL;
        if (answer[0] != 'y') // check_work_with_Answer_l: 1 == y, 0 == n;
        {
            fscanf(inputFile, "%lf", &example->current_n->number_s1);
        }
        fscanf(inputFile, " %c ", &example->current_settings->current_s->operations);
        if (!((example->current_settings->current_s->operations == '!') || (example->current_settings->current_s->operations == 'a')))
        {
            fscanf(inputFile, "%lf", &example->current_n->number_s2);
        }
        fscanf(inputFile, " %c ", &example->current_settings->current_s->use_answer);
        if (example->current_settings->current_s->use_answer == 'y')
        {
            answer[0] = 'y';
        }
        else
        {
            answer[0] = 'n';
        }
        //check_work_with_Answer_l = current->current_settings->current_s->use_answer; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (example->current_settings->current_s->use_answer == 'n')
        {
            fscanf(inputFile, " %c ", &example->current_settings->close_calculator_subspecies);
            if (example->current_settings->close_calculator_subspecies == 'e')
            {
                fscanf(inputFile, " %c ", &example->current_settings->close_file);
                future[0] = 0; // новый калькулятор
            }
        }
        break;
    }
}

void push_back(list_calculator *current, char *answer, int *future)
{
    char type;                           // нужна для такого ввода s + 2 n n   <-- т.е. 1 значение берётся из прошлого
    if (list_calc.head_settings == NULL) // начинаем проверку с NULL, потом current
    {
        list_calc.head_settings = malloc(sizeof(settings_list_calc)); //нужно всё инициализировать
        list_calc.head_n = malloc(sizeof(list_numbers));
        list_calc.current_n = list_calc.head_n;
        list_calc.current_settings = list_calc.head_settings;
        answer[0] = ' '; // у меня
        future[0] = 0;
    }
    else
    {
        list_calc.current_n = list_calc.head_n;
        list_calc.current_settings = list_calc.head_settings;
        while (list_calc.current_settings->next != NULL)
        {
            list_calc.current_settings = list_calc.current_settings->next;
            list_calc.current_n = list_calc.current_n->next;
        }
        list_calc.current_settings->next = malloc(sizeof(settings_list_calc));
        list_calc.current_n->next = malloc(sizeof(list_numbers));
        list_calc.current_settings = list_calc.current_settings->next;
        list_calc.current_n = list_calc.current_n->next;
    }
    list_calc.current_settings->next = NULL;
    list_calc.current_n->next = NULL;
    if (future[0] == 0) //  начинаем заполнять список по элементам
    {
        list_calc.current_settings->calc_type = current->current_settings->calc_type;
        type = list_calc.current_settings->calc_type;
        future[0] = 1; // использовать старый калькулятор
    }
    switch (type)
    {
    case 'v':
        list_calc.current_settings->current_v = malloc(sizeof(l_v_calc));
        list_calc.current_settings->current_s = NULL;
        list_calc.current_settings->current_v->size = current->current_settings->current_v->size;
        list_calc.current_settings->current_v->num = current->current_settings->current_v->num;
        list_calc.current_n->number_v = malloc((list_calc.current_settings->current_v->num * list_calc.current_settings->current_v->size) * sizeof(double));
        for (int i = 1; i < list_calc.current_settings->current_v->num + 1; i++)
        {
            //printf("Введите координаты %i вектора: ", i);
            for (int j = 0; j < list_calc.current_settings->current_v->size; j++)
            {
                list_calc.current_n->number_v[list_calc.current_settings->current_v->size * (i - 1) + j] = current->current_n->number_v[list_calc.current_settings->current_v->size * (i - 1) + j];
            }
        }
        list_calc.current_settings->current_v->operations = current->current_settings->current_v->operations; //какая операция с векторами
        list_calc.current_settings->close_calculator_subspecies = current->current_settings->close_calculator_subspecies;
        if (list_calc.current_settings->close_calculator_subspecies == 'e')
        {
            list_calc.current_settings->close_file = current->current_settings->close_file;
        }
        break;
    case 's':
        list_calc.current_settings->current_s = malloc(sizeof(l_s_calc));
        list_calc.current_settings->current_v = NULL;
        list_calc.current_n->number_v = NULL;
        if (answer[0] != 'y')
        {
            list_calc.current_n->number_s1 = current->current_n->number_s1;
        }
        list_calc.current_settings->current_s->operations = current->current_settings->current_s->operations;
        if (!((list_calc.current_settings->current_s->operations == '!') || (list_calc.current_settings->current_s->operations == 'a')))
        {
            list_calc.current_n->number_s2 = current->current_n->number_s2;
        }
        list_calc.current_settings->current_s->use_answer = current->current_settings->current_s->use_answer;
        if (list_calc.current_settings->current_s->use_answer == 'y')
        {
            answer[0] = 'y';
        }
        else
        {
            answer[0] = 'n';
        }
        if (list_calc.current_settings->current_s->use_answer == 'n')
        {
            list_calc.current_settings->close_calculator_subspecies = current->current_settings->close_calculator_subspecies;
            if (list_calc.current_settings->close_calculator_subspecies == 'e')
            {
                list_calc.current_settings->close_file = current->current_settings->close_file;
                future[0] = 0; // новый калькулятор
            }
        }
        break;
    }
}
