// Тестовый Вариант, где испоьзуется не вся проверка, а только выборочная
#include <stdio.h>
#include <stdlib.h>

typedef struct numbers // Очередь для чисел
{
    double *number_v; // для векторного калькулятора
    double number_s1; // для обычного калькулятора
    double number_s2;
    struct numbers *next;
} numbers;

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

typedef struct settings_calc // сама структура калькулятора
{
    char calc_type;
    s_calc *current_s;
    v_calc *current_v;
    char close_calculator_subspecies;
    char close_file;
    struct settings_calc *next;
} settings_calc;

typedef struct answer // чисто изза условия, хотя ответ можно было сразу в файл писать
{
    char *ans_res;
    struct answer *next;
} answer;

typedef struct calculator // сама структура калькулятора
{
    int order; // !!!!!!!!!!!!!!!!!     вроде не нужно но для проверки норм и не мешает.
    numbers *head_n, *current_n;
    settings_calc *head_settings, *current_settings;
    answer *head_res, *current_res;
} calculator;

calculator calc; // для удобства в обращении

char *pop_list_out(calculator *results) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    answer *term = results->head_res;
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

void push_list_out(char *line, calculator *results)
{
    if (results->head_res == NULL)
    {
        results->head_res = malloc(sizeof(answer));
        results->current_res = results->head_res;
    }
    else
    {
        results->current_res = results->head_res;
        while (results->current_res->next != NULL)
        {
            results->current_res = results->current_res->next;
        }
        results->current_res->next = malloc(sizeof(answer));
        results->current_res = results->current_res->next;
    }
    results->current_res->next = NULL;
    results->current_res->ans_res = line;
}

void deleteResults()
{
    calc.current_res = calc.head_res;
    while (calc.current_res != NULL)
    {
        calc.current_res = calc.head_res;
        pop_list_out(&calc);
    }
}

void writeAnswerToFile(FILE *outputFile)
{
    calc.current_res = calc.head_res;
    while (calc.current_res != NULL)
    {
        fprintf(outputFile, "%s\n", pop_list_out(&calc));
    }
}

// для удобства просмотра пробелы поставил просто так

void pop_list_in(calculator *current)
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
    settings_calc *term_s = current->head_settings;
    numbers *term_n = current->head_n;
    while (term_s->next != current->current_settings)
    {
        term_s = term_s->next;
        term_n = term_n->next;
    }
    term_s->next = current->current_settings->next;
    term_n->next = current->current_n->next;
    free(current->current_settings);
    free(current->current_n->number_v);
    free(current->current_n);
    current->current_settings = term_s;
    current->current_n = term_n;
}

void deleteList()
{
    calc.current_settings = calc.head_settings;
    calc.current_n = calc.head_n;
    while (calc.current_settings != NULL)
    {
        calc.current_settings = calc.head_settings;
        calc.current_n = calc.head_n;
        pop_list_in(&calc);
    }
}

void fill_list(calculator *current, FILE *inputFile)
{
    int check_future_l;
    char check_work_with_Answer_l, type_l;

    if (calc.head_settings == NULL)
    {
        current->current_settings = malloc(sizeof(current->current_settings)); //нужно всё инициализировать
        current->current_n = malloc(sizeof(current->current_n));
        check_work_with_Answer_l = ' ';
        check_future_l = 0;
    }

    if (check_future_l == 0)
    {
        fscanf(inputFile, " %c ", &current->current_settings->calc_type);
        type_l = current->current_settings->calc_type;
        check_future_l = 1;
    }
    switch (type_l)
    {
    case 'v':
        current->current_settings->current_v = malloc(sizeof(current->current_settings->current_v));
        fscanf(inputFile, "%d", &current->current_settings->current_v->num);
        fscanf(inputFile, "%d", &current->current_settings->current_v->size);
        current->current_n->number_v = malloc((current->current_settings->current_v->num * current->current_settings->current_v->size) * sizeof(double));
        for (int i = 1; i < current->current_settings->current_v->num + 1; i++)
        {
            //printf("Введите координаты %i вектора: ", i);
            for (int j = 0; j < current->current_settings->current_v->size; j++)
            {
                fscanf(inputFile, "%lf", &current->current_n->number_v[current->current_settings->current_v->size * (i - 1) + j]);
            }
        }
        fscanf(inputFile, " %c ", &current->current_settings->current_v->operations); //какая операция с векторами
        fscanf(inputFile, " %c ", &current->current_settings->close_calculator_subspecies);
        if (current->current_settings->close_calculator_subspecies == 'e')
        {
            fscanf(inputFile, " %c ", &current->current_settings->close_file);
        }
        break;
    case 's':
        current->current_settings->current_s = malloc(sizeof(current->current_settings->current_s));
        current->current_settings->current_v = NULL;
        if (check_work_with_Answer_l != 'y')
        {
            fscanf(inputFile, "%lf", &current->current_n->number_s1);
        }
        fscanf(inputFile, " %c ", &current->current_settings->current_s->operations);
        if (!((current->current_settings->current_s->operations == '!') || (current->current_settings->current_s->operations == 'a')))
        {
            fscanf(inputFile, "%lf", &current->current_n->number_s2);
        }
        fscanf(inputFile, " %c ", &current->current_settings->current_s->use_answer);
        check_work_with_Answer_l = current->current_settings->current_s->use_answer;
        if (current->current_settings->current_s->use_answer == 'n')
        {
            fscanf(inputFile, " %c ", &current->current_settings->close_calculator_subspecies);
            if (current->current_settings->close_calculator_subspecies == 'e')
            {
                fscanf(inputFile, " %c ", &current->current_settings->close_file);
                check_future_l = 0; // новый калькулятор
            }
        }
        break;
    }
}

void push_back(calculator *current)
{
    int check_future;
    char check_work_with_Answer, type; // нужна для такого ввода s + 2 n n   <-- т.е. мы работаем с ответом из прошлого
    if (calc.head_settings == NULL)    // начинаем проверку с NULL, потом current
    {
        calc.head_settings = malloc(sizeof(calc.head_settings)); //нужно всё инициализировать
        calc.head_n = malloc(sizeof(calc.head_n));
        calc.current_n = calc.head_n;
        calc.current_settings = calc.head_settings;
        check_work_with_Answer = ' ';
        check_future = 0;
    }
    else
    {
        calc.current_n = calc.head_n;
        calc.current_settings = calc.head_settings;
        while (calc.current_settings->next != NULL)
        {
            calc.current_settings = calc.current_settings->next;
            calc.current_n = calc.current_n->next;
        }
        calc.current_settings->next = malloc(sizeof(settings_calc));
        calc.current_n->next = malloc(sizeof(numbers));
        calc.current_settings = calc.current_settings->next;
        calc.current_n = calc.current_n->next;
    }
    calc.current_settings->next = NULL;
    calc.current_n->next = NULL;
    if (check_future == 0) //  начинаем заполнять список по элементам
    {
        calc.current_settings->calc_type = current->current_settings->calc_type;
        type = calc.current_settings->calc_type;
        check_future = 1; // использовать старый калькулятор
    }
    switch (type)
    {
    case 'v':
        calc.current_settings->current_v = malloc(sizeof(calc.current_settings->current_v));
        calc.current_settings->current_s = NULL;
        calc.current_settings->current_v->num = current->current_settings->current_v->num;
        calc.current_settings->current_v->size = current->current_settings->current_v->size;
        calc.current_n->number_v = malloc((calc.current_settings->current_v->num * calc.current_settings->current_v->size) * sizeof(double));
        for (int i = 1; i < calc.current_settings->current_v->num + 1; i++)
        {
            //printf("Введите координаты %i вектора: ", i);
            for (int j = 0; j < calc.current_settings->current_v->size; j++)
            {
                calc.current_n->number_v[calc.current_settings->current_v->size * (i - 1) + j] = current->current_n->number_v[calc.current_settings->current_v->size * (i - 1) + j];
            }
        }
        calc.current_settings->current_v->operations = current->current_settings->current_v->operations; //какая операция с векторами
        calc.current_settings->close_calculator_subspecies = current->current_settings->close_calculator_subspecies;
        if (calc.current_settings->close_calculator_subspecies == 'e')
        {
            calc.current_settings->close_file = current->current_settings->close_file;
        }
        break;
    case 's':
        calc.current_settings->current_s = malloc(sizeof(calc.current_settings->current_s));
        calc.current_settings->current_v = NULL;
        if (check_work_with_Answer != 'y')
        {
            calc.current_n->number_s1 = current->current_n->number_s1;
        }
        calc.current_settings->current_s->operations = current->current_settings->current_s->operations;
        if (!((calc.current_settings->current_s->operations == '!') || (calc.current_settings->current_s->operations == 'a')))
        {
            calc.current_n->number_s2 = current->current_n->number_s2;
        }
        calc.current_settings->current_s->use_answer = current->current_settings->current_s->use_answer;
        check_work_with_Answer = calc.current_settings->current_s->use_answer;
        if (calc.current_settings->current_s->use_answer == 'n')
        {
            calc.current_settings->close_calculator_subspecies = current->current_settings->close_calculator_subspecies;
            if (calc.current_settings->close_calculator_subspecies == 'e')
            {
                calc.current_settings->close_file = current->current_settings->close_file;
                check_future = 0; // новый калькулятор
            }
        }
        break;
    }
}

int counter(unsigned long int i)
{ // Функция считает сколько нужно символов перед запятой для числа
    int counter = 0;
    if (i < 0)
    {
        counter++;
        i = -i;
    }
    do
    {
        counter++;
        i = i / 10;
    } while (i > 0);
    return counter;
}

int main(int argc, char const *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    calc.head_settings = NULL;
    calc.head_n = NULL;
    calc.head_res = NULL;
    char file_check, input[80], output[80];
    printf("Введите название файла из которого будет происходить\n");
    printf("чтение(максимальная длина названия 80 символов): ");
    scanf(" %s", input);
    printf("\n");
    FILE *inputFile, *outputFile;
    inputFile = fopen(input, "r");
    fscanf(inputFile, " %c", &file_check);

    printf("Введите название файла в который будет происходить\n");
    printf("запись(максимальная длина названия 80 символов): ");
    scanf(" %s", output);
    printf("\n");
    outputFile = fopen(output, "w");

    while (!feof(inputFile))
    {                                        // Заполнение всего листа settings
        calculator example_list;             //  хз
        fill_list(&example_list, inputFile); //inputFile.txt
        push_back(&example_list);
    }
    fclose(inputFile);

    // проверка на загрузку в res

    calc.current_settings = calc.head_settings;
    calc.current_n = calc.head_n;
    calc.current_res = calc.head_res; // хз нужна ли !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! <- это для меня потом для проверки

    char start;
    start = calc.current_settings->calc_type;

    if (start == 's')
    {
        unsigned long int a;
        double res, b, c;
        char str, workWithRes, res_s;
        char *line_expression;
        calc.current_n->number_v = NULL;
        res = calc.current_n->number_s1;
        str = calc.current_settings->current_s->operations;
        if ((str != 'a') && (str != '!'))
            b = calc.current_n->number_s2;
        switch (str)
        {                                                                                                                                 //есть возможность, если мы захотим
        case '+':                                                                                                                         //продолжить работу с циклом.
        {                                                                                                                                 //высветится ответ, около которого мы можем написать
            line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(res + b)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах //необходимую операцию и 2 число

            sprintf(line_expression, "%lf + %lf = %lf", res, b, res + b);
            res = res + b;
            break;
        }
        } // закрытие switch

        pop_list_in(&calc);
        deleteList();
        push_list_out(line_expression, &calc);
        writeAnswerToFile(outputFile);
        fclose(outputFile);
        pop_list_out(&calc);
        deleteResults();
        fclose(outputFile);
    }
    return 0;
}
