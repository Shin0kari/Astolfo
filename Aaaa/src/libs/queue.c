#include"queue.h"

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

void fill_queue(queue_calculator *example, FILE *inputFile, char *answer, int *future)
{
    char type_l;

    if (queue_calc.head_settings == NULL)
    {
        example->head_settings = malloc(sizeof(settings_queue_calc)); //нужно всё инициализировать
        example->head_n = malloc(sizeof(queue_numbers));
        answer[0] = 'n';
        future[0] = 0;
    }
    if (future[0] == 0)
    {
        fscanf(inputFile, " %c ", &example->head_settings->calc_type);
        type_l = example->head_settings->calc_type;
        future[0] = 1;
    }

    switch (type_l)
    {
    case 'v':
        example->head_settings->current_s = NULL;
        example->head_settings->current_v = malloc(sizeof(v_calc));
        fscanf(inputFile, "%d", &example->head_settings->current_v->size);
        fscanf(inputFile, "%d", &example->head_settings->current_v->num);

        example->head_n->number_v = malloc((example->head_settings->current_v->num * example->head_settings->current_v->size) * sizeof(double));
        for (int i = 1; i < example->head_settings->current_v->num + 1; i++)
        {
            //printf("Введите координаты %i вектора: ", i);
            for (int j = 0; j < example->head_settings->current_v->size; j++)
            {
                fscanf(inputFile, "%lf", &example->head_n->number_v[example->head_settings->current_v->size * (i - 1) + j]);
            }
        }

        fscanf(inputFile, " %c ", &example->head_settings->current_v->operations); //какая операция с векторами
        fscanf(inputFile, " %c ", &example->head_settings->close_calculator_subspecies);
        if (example->head_settings->close_calculator_subspecies == 'e')
        {
            fscanf(inputFile, " %c ", &example->head_settings->close_file);
        }
        break;
    case 's':
        example->head_settings->current_s = malloc(sizeof(s_calc));
        example->head_settings->current_v = NULL;
        example->head_n->number_v = NULL;

        if (answer[0] != 'y') // check_work_with_Answer_l: 1 == y, 0 == n;
        {
            fscanf(inputFile, "%lf", &example->head_n->number_s1);
        }
        fscanf(inputFile, " %c ", &example->head_settings->current_s->operations);
        if (!((example->head_settings->current_s->operations == '!') || (example->head_settings->current_s->operations == 'a')))
        {
            fscanf(inputFile, "%lf", &example->head_n->number_s2);
        }
        fscanf(inputFile, " %c ", &example->head_settings->current_s->use_answer);
        if (example->head_settings->current_s->use_answer == 'y')
        {
            answer[0] = 'y';
        }
        else
        {
            answer[0] = 'n';
        }
        //check_work_with_Answer_l = current->head_settings->current_s->use_answer; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (example->head_settings->current_s->use_answer == 'n')
        {
            fscanf(inputFile, " %c ", &example->head_settings->close_calculator_subspecies);
            if (example->head_settings->close_calculator_subspecies == 'e')
            {
                fscanf(inputFile, " %c ", &example->head_settings->close_file);
                future[0] = 0; // новый калькулятор
            }
        }
        break;
    }
}

void pushback_queue_in(queue_calculator *current, char *answer, int *future)
{
    char type; // нужна для такого ввода s + 2 n n   <-- т.е. 1 значение берётся из прошлого
    if (queue_calc.head_settings == NULL)
    {
        queue_calc.head_settings = malloc(sizeof(settings_queue_calc)); //нужно всё инициализировать
        queue_calc.head_n = malloc(sizeof(queue_numbers));
        queue_calc.tail_n = queue_calc.head_n;
        queue_calc.tail_settings = queue_calc.head_settings;
        answer[0] = ' '; // у меня
        future[0] = 0;
    }
    else
    {
        queue_calc.tail_settings->next = malloc(sizeof(settings_queue_calc));
        queue_calc.tail_n->next = malloc(sizeof(queue_numbers));
        queue_calc.tail_settings = queue_calc.tail_settings->next;
        queue_calc.tail_n = queue_calc.tail_n->next;
    }
    queue_calc.tail_settings->next = NULL;
    queue_calc.tail_n->next = NULL;
    if (future[0] == 0) //  начинаем заполнять список по элементам
    {
        queue_calc.tail_settings->calc_type = current->head_settings->calc_type;
        type = queue_calc.tail_settings->calc_type;
        future[0] = 1; // использовать старый калькулятор
    }
    switch (type)
    {
    case 'v': //!!!!!!!!!!!!!!!!!!! вопрос, можно прировнять просто 2 массива и не обяз записывать просто числа?!!!!!!!!!!!!

        queue_calc.tail_settings->current_v = malloc(sizeof(v_calc));
        queue_calc.tail_settings->current_s = NULL;
        queue_calc.tail_settings->current_v->size = current->head_settings->current_v->size;
        queue_calc.tail_settings->current_v->num = current->head_settings->current_v->num;
        queue_calc.tail_n->number_v = malloc((queue_calc.tail_settings->current_v->num * queue_calc.tail_settings->current_v->size) * sizeof(double));
        for (int i = 1; i < queue_calc.tail_settings->current_v->num + 1; i++)
        {
            //printf("Введите координаты %i вектора: ", i);
            for (int j = 0; j < queue_calc.tail_settings->current_v->size; j++)
            {
                queue_calc.tail_n->number_v[queue_calc.tail_settings->current_v->size * (i - 1) + j] = current->head_n->number_v[queue_calc.tail_settings->current_v->size * (i - 1) + j];
            }
        }
        queue_calc.tail_settings->current_v->operations = current->head_settings->current_v->operations; //какая операция с векторами
        queue_calc.tail_settings->close_calculator_subspecies = current->head_settings->close_calculator_subspecies;
        if (queue_calc.tail_settings->close_calculator_subspecies == 'e')
        {
            queue_calc.tail_settings->close_file = current->head_settings->close_file;
        }
        break;
    case 's':

        queue_calc.tail_settings->current_s = malloc(sizeof(s_calc));
        queue_calc.tail_settings->current_v = NULL;
        queue_calc.tail_n->number_v = NULL;
        if (answer[0] != 'y')
        {
            queue_calc.tail_n->number_s1 = current->head_n->number_s1;
        }
        queue_calc.tail_settings->current_s->operations = current->head_settings->current_s->operations;
        if (!((queue_calc.tail_settings->current_s->operations == '!') || (queue_calc.tail_settings->current_s->operations == 'a')))
        {
            queue_calc.tail_n->number_s2 = current->head_n->number_s2;
        }
        queue_calc.tail_settings->current_s->use_answer = current->head_settings->current_s->use_answer;
        if (queue_calc.tail_settings->current_s->use_answer == 'y')
        {
            answer[0] = 'y';
        }
        else
        {
            answer[0] = 'n';
        }
        if (queue_calc.tail_settings->current_s->use_answer == 'n')
        {
            queue_calc.tail_settings->close_calculator_subspecies = current->head_settings->close_calculator_subspecies;
            if (queue_calc.tail_settings->close_calculator_subspecies == 'e')
            {
                queue_calc.tail_settings->close_file = current->head_settings->close_file;
                future[0] = 0; // новый калькулятор
            }
        }
        break;
    }
}

void pushback_queue_out(char *line, queue_calculator *results)
{
    if (results->head_res == NULL)
    {
        results->head_res = malloc(sizeof(queue_answer));
        results->tail_res = results->head_res;
    }
    else
    {
        results->tail_res->next = malloc(sizeof(queue_answer));
        results->tail_res = results->tail_res->next;
    }
    results->tail_res->next = NULL;
    results->tail_res->ans_res = line;
}

void pop_queue_in(queue_calculator *current)
{
    if (current->head_settings == NULL)
    {
        return;
    }
    if (current->head_settings->next == NULL)
    {
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
        current->tail_n = NULL;
        current->tail_settings = NULL;
        return;
    }
    settings_queue_calc *term_s = current->head_settings;
    queue_numbers *term_n = current->head_n;
    current->head_settings = term_s->next;
    current->head_n = term_n->next;
    free(term_s);
    free(term_n); // возможно придётся добавить получше отчищение
}

char *pop_queue_out(queue_calculator *results)
{
    char *line;
    if (results->head_res == NULL)
    {
        return NULL;
    }
    if (results->head_res->next == NULL)
    {
        line = results->head_res->ans_res;
        free(results->head_res);
        results->head_res = NULL;
        results->tail_res = NULL;
        return line;
    }
    queue_answer *term = results->head_res;
    results->head_res = term->next;
    line = term->ans_res;
    free(term);
    return line;
}

void delete_queue()
{                                            // Удалить листы очереди
    while (queue_calc.head_settings != NULL) // не уверен, что должно быть в условии !!!!!!!!!!!!!!!!!!!!!!!!
    {
        pop_queue_in(&queue_calc);
    }
}

void delete_queue_Results()
{ // Удалить лист output_data_for_queues
    while (queue_calc.head_res != NULL)
    {
        pop_queue_out(&queue_calc);
    }
}

void write_queue_AnswerToFile(FILE *outputFile)
{ // Вписать из листа в файл
    while (queue_calc.head_res != NULL)
    {
        fprintf(outputFile, "%s\n", pop_queue_out(&queue_calc));
    }
}
