#if !defined(queueh)
#define queueh

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

typedef struct queue_numbers // Очередь для чисел
{
    double *number_v; // для векторного калькулятора
    double number_s1; // для обычного калькулятора
    double number_s2;
    struct queue_numbers *next;
} queue_numbers;

typedef struct simple_calc // в зависимости от используемого калькулятора, будет зависеть операции и 1 доп вопрос
{
    char operations;
    char use_answer;
} s_calc;

typedef struct vector_calc // в зависимости от используемого калькулятора, будет зависеть операции и 1 доп вопрос
{
    char operations;
    int num;
    int size;
} v_calc;

typedef struct settings_queue_calc // сама структура калькулятора
{
    char calc_type;
    s_calc *current_s;
    v_calc *current_v;
    char close_calculator_subspecies;
    char close_file;
    struct settings_queue_calc *next;
} settings_queue_calc;

typedef struct queue_answer // чисто изза условия, хотя ответ можно было сразу в файл писать
{
    char *ans_res;
    struct queue_answer *next;
} queue_answer;

typedef struct queue_calculator // сама структура калькулятора
{
    int order; // !!!!!!!!!!!!!!!!!     вроде не нужно но для проверки норм и не мешает.
    queue_numbers *head_n, *tail_n;
    settings_queue_calc *head_settings, *tail_settings;
    queue_answer *head_res, *tail_res;
} queue_calculator;

queue_calculator queue_calc;

void fill_queue(queue_calculator *example, FILE *inputFile, char *answer, int *future);

void pushback_queue_in(queue_calculator *current, char *answer, int *future);

void pushback_queue_out(char *line, queue_calculator *results);

void pop_queue_in(queue_calculator *current);

char *pop_queue_out(queue_calculator *results);

void delete_queue();

void delete_queue_Results();

void write_queue_AnswerToFile(FILE *outputFile);

#endif
