#if !defined(listh)
#define listh

#ifndef STDIO_H
#include<stdio.h>
#endif

#ifndef STDLIB_H
#include<stdlib.h>
#endif

typedef struct list_numbers // Очередь для чисел
{
    double *number_v; // для векторного калькулятора
    double number_s1; // для обычного калькулятора
    double number_s2;
    struct list_numbers *next;
} list_numbers;

typedef struct list_simple_calc // в зависимости от используемого калькулятора, будет зависеть операции и 1 доп вопрос
{
    char operations;
    char use_answer;
} l_s_calc;

typedef struct list_vector_calc // в зависимости от используемого калькулятора, будет зависеть операции и 1 доп вопрос
{
    char operations;
    int num;
    int size;
} l_v_calc;

typedef struct settings_list_calc // сама структура калькулятора
{
    char calc_type;
    l_s_calc *current_s;
    l_v_calc *current_v;
    char close_calculator_subspecies;
    char close_file;
    struct settings_list_calc *next;
} settings_list_calc;

typedef struct list_answer // чисто изза условия, хотя ответ можно было сразу в файл писать
{
    char *ans_res;
    struct list_answer *next;
} list_answer;

typedef struct list_calculator // сама структура калькулятора
{
    int order; // !!!!!!!!!!!!!!!!!     вроде не нужно но для проверки норм и не мешает.
    list_numbers *head_n, *current_n;
    settings_list_calc *head_settings, *current_settings;
    list_answer *head_res, *current_res;
} list_calculator;

list_calculator list_calc;

char *pop_list_out(list_calculator *results);

void push_list_out(char *line, list_calculator *results);

void deleteResults();

void writeAnswerToFile(FILE *outputFile);

void pop_list_in(list_calculator *current);

void deleteList();

void fill_list(list_calculator *example, FILE *inputFile, char *answer, int *future);

void push_back(list_calculator *current, char *answer, int *future);

#endif
