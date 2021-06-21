// испоьзовать input.txt

/*
Во первых, вы должны обладать ссылкой (https://github.com/Shin0kari/Calculator/).
Теперь вы ей обладаете, самое сложное уже выполнено, осталось зайти в Eclipse, зайти в workspace(свой или новый, не важно).
Как откроется IDE сверху выбираем Window->Percpective->Open Percpective->Other...->Git.
Откроется специальное окно, нужно нажать clone git repository(в ряду с желтыми значками).
Появится окно, в нем нужно вбить сслыку, либо до откытия clone git repository сохранить в буфер обмена ссылку и Eclipse все сделает сам(Authentication заполнять не нужно, как и все остально кроме location, и в Connection выбрать протокол https).
Жмем Next, снова жмем Next, выбираем путь, где будет хранится репозиторий из гит на вашем компьютере(Путь должен содержать только английские буквы, и не должен содержать пробелы), а также желательно нажать на галочку в import all esisting Eclipse project after clone finishes.
Жмем finish и видим, что появилась папка в git repositories заходим в эту папку, дальше Working tree.
Видим папку Aaaa, жмем 1 раз на нее, потом правой кнопкой. И жмем Import Project.
Появляется окно, в нем ничего выбирать не нужно, просто если Eclipse выбрал не ту папку, то стоит ее редактировать.
Жмем finish и уже проект появляется в C/C++. Теперь вы можете смотреть код(Aaaa/src/Aaaa.c)
*/

#include <stdlib.h>
#include <stdio.h> //решил пофлексить Каспер Дмитрий 1 курс 4 группа(ИВТ)

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

char *pop_list_out(calculator *results) // вроде исправлял, но пока оставлю !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    calc.current_settings = calc.head_settings;
    calc.current_n = calc.head_n;
    while (calc.current_settings != NULL)
    {
        calc.current_settings = calc.head_settings;
        calc.current_n = calc.head_n;
        pop_list_in(&calc);
    }
}

void fill_list(calculator *example, FILE *inputFile, char *answer, int *future)
{

    char type_l;

    if (calc.head_settings == NULL)
    {
        example->current_settings = malloc(sizeof(settings_calc)); //нужно всё инициализировать
        example->current_n = malloc(sizeof(numbers));
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
        example->current_settings->current_v = malloc(sizeof(v_calc));
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
        example->current_settings->current_s = malloc(sizeof(s_calc));
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

void push_back(calculator *current, char *answer, int *future)
{
    char type;                      // нужна для такого ввода s + 2 n n   <-- т.е. 1 значение берётся из прошлого
    if (calc.head_settings == NULL) // начинаем проверку с NULL, потом current
    {
        calc.head_settings = malloc(sizeof(settings_calc)); //нужно всё инициализировать
        calc.head_n = malloc(sizeof(numbers));
        calc.current_n = calc.head_n;
        calc.current_settings = calc.head_settings;
        answer[0] = ' '; // у меня
        future[0] = 0;
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
    if (future[0] == 0) //  начинаем заполнять список по элементам
    {
        calc.current_settings->calc_type = current->current_settings->calc_type;
        type = calc.current_settings->calc_type;
        future[0] = 1; // использовать старый калькулятор
    }
    switch (type)
    {
    case 'v':
        calc.current_settings->current_v = malloc(sizeof(v_calc));
        calc.current_settings->current_s = NULL;
        calc.current_settings->current_v->size = current->current_settings->current_v->size;
        calc.current_settings->current_v->num = current->current_settings->current_v->num;
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
        calc.current_settings->current_s = malloc(sizeof(s_calc));
        calc.current_settings->current_v = NULL;
        calc.current_n->number_v = NULL;
        if (answer[0] != 'y')
        {
            calc.current_n->number_s1 = current->current_n->number_s1;
        }
        calc.current_settings->current_s->operations = current->current_settings->current_s->operations;
        if (!((calc.current_settings->current_s->operations == '!') || (calc.current_settings->current_s->operations == 'a')))
        {
            calc.current_n->number_s2 = current->current_n->number_s2;
        }
        calc.current_settings->current_s->use_answer = current->current_settings->current_s->use_answer;
        if (calc.current_settings->current_s->use_answer == 'y')
        {
            answer[0] = 'y';
        }
        else
        {
            answer[0] = 'n';
        }
        if (calc.current_settings->current_s->use_answer == 'n')
        {
            calc.current_settings->close_calculator_subspecies = current->current_settings->close_calculator_subspecies;
            if (calc.current_settings->close_calculator_subspecies == 'e')
            {
                calc.current_settings->close_file = current->current_settings->close_file;
                future[0] = 0; // новый калькулятор
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

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char file_check, input[80], output[80], BackToTheFutures, theSameFile;
    int codeOffended = 0, stepRepeat = 0;

    do
    {
        calc.head_settings = NULL;
        calc.head_n = NULL;
        calc.head_res = NULL;

        printf("Введите название файла из которого будет происходить\n");
        printf("чтение(максимальная длина названия 80 символов): ");
        scanf(" %s", input);
        printf("\n");
        FILE *inputFile, *outputFile;
        inputFile = fopen(input, "r");
        fscanf(inputFile, " %c", &file_check);
        while ((inputFile == NULL) || (feof(inputFile)) || (codeOffended == 2) || (file_check != 'o'))
        {

            if (feof(inputFile))
            {
                printf("ты как из пустого файла решил читать? А ну переделывай\n");
                printf("Введите название файла из которого будет происходить чтение: ");
                scanf(" %s", input);
                inputFile = fopen(input, "r");
                printf("\n");
                fscanf(inputFile, " %c", &file_check);
            }

            else if (codeOffended == 2)
            {
                printf("Код обиделся, теперь произойдёт аннигиляция. Удачного дня");
                return 0;
            }
            else
            {
                printf("Код это запомнит? Такого файла не существует\n");
                codeOffended++;
                printf("Введите название файла из которого будет происходить чтение: ");
                scanf(" %s", input);
                inputFile = fopen(input, "r");
                printf("\n");
                fscanf(inputFile, " %c", &file_check);
            }
        }
        codeOffended = 0;    // это для проверки на дурака:)
        if (stepRepeat == 1) // файл для записи на 2 кругу
        {
            printf("Хотите ли вы вывести ответ в тот же файл?(y-\"yes\";n-\"no\"): ");
            scanf(" %c", &theSameFile);
            printf("\n");
            while ((theSameFile != 'y') && (theSameFile != 'n')) // Проверка на корректно введенное y или n
            {
                printf("Да ну ладно, нормально ведь общались.\n");
                printf("Другие ответы не принимаются.\n");
                printf("Хотите ли вы вывести ответ в тот же файл?(y-\"yes\";n-\"no\"): ");
                scanf(" %c", &theSameFile);
            }
        }
        if ((stepRepeat == 0) || (theSameFile == 'n')) // файл для записи на 1 кругу
        {
            printf("Введите название файла в который будет происходить\n");
            printf("запись(максимальная длина названия 80 символов): ");
            scanf(" %s", output);
            outputFile = fopen(output, "w");
        }

        //место для части кода, где в список будут записываться числа

        /*printf("Выберите, что использовать: (s) - simple calculator\n");     //<- из консольного калькулятора
        printf("Выберите, что использовать: (v) - vector calculator\n");*/
        int *check_future, *check_future_1;
        char end;
        char *line_expression, *check_answer, *check_answer_1;

        check_future = malloc(1 * sizeof(int));
        check_future_1 = malloc(1 * sizeof(int));
        check_answer = malloc(1 * sizeof(char));
        check_answer_1 = malloc(1 * sizeof(char));

        while (!feof(inputFile))
        {                            // Заполнение всего листа settings
            calculator example_list; // для создания 1 стр
            fill_list(&example_list, inputFile, check_answer, check_future);
            push_back(&example_list, check_answer_1, check_future_1);
        }

        free(check_future);
        free(check_future_1);
        free(check_answer);
        free(check_answer_1);

        fclose(inputFile);

        calc.current_settings = calc.head_settings;
        calc.current_n = calc.head_n;
        calc.current_res = calc.head_res; // хз нужна ли эта строка !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        do
        {
            char start;
            start = calc.current_settings->calc_type;

            if (start == 's')
            {
                //Задумка была такая: сделать калькулятор
                //не нагруженным в использовании, похожим
                //на калькулятор в Windows
                unsigned long int a;
                //int tic;
                double res, b, c;
                char str, workWithRes, res_s;
                do
                {
                    //tic=0;

                    /*printf("вы можете: взять факториал 1 числа(3 !), модуль 1 числа(3 a)\n");      //<- из консольного калькулятора
                    printf("сложить 2 числа(1 + 2), поделить(1 / 2), умножить(1 * 1)\n");
                    printf("возвести 1 число в степень равную номеру 2 числа(1 ^ 2)\n");*/

                    res = calc.current_n->number_s1; //тк калькулятор win может продолжить работу

                    do //с ответом, я решил сделать также.
                    {  //поэтому у меня два while - 1 отвечает"не хотите ли
                        /*if (tic == 1)              			    	//вы закончить работу?"
                        fprintf(outputFile,"%lf",res);*/
                        //2 - отвечает "хотите продолжить работу с ответом?"

                        str = calc.current_settings->current_s->operations;
                        if ((str != 'a') && (str != '!'))
                            b = calc.current_n->number_s2;

                        switch (str)
                        {
                        case '+':
                        {
                            line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(res + b)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                            sprintf(line_expression, "%lf + %lf = %lf", res, b, res + b);
                            res = res + b;
                            break;
                        }
                        case '-':
                        {
                            line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(res + b)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                            sprintf(line_expression, "%lf - %lf = %lf", res, b, res - b);
                            res = res - b;
                            break;
                        }
                        case '*':
                        {
                            line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(res + b)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                            sprintf(line_expression, "%lf * %lf = %lf", res, b, res * b);
                            res = res * b;
                            break;
                        }
                        case '/':
                        {
                            line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(res + b)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                            sprintf(line_expression, "%lf / %lf = %lf", res, b, res / b);
                            res = res / b;
                            break;
                        }
                        case 'a':
                        {
                            if (res < 0)
                            {
                                line_expression = malloc((counter((int)res) + counter((int)(res)) + 2 * 7 + 5 + 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                                sprintf(line_expression, "abs(%lf) = %lf", res, -res);
                                res = -res;
                                break;
                            }
                            else
                            {
                                line_expression = malloc((counter((int)res) + counter((int)(res)) + 2 * 7 + 5 + 3 + 1) * sizeof(char));
                                sprintf(line_expression, "abs(%lf) = %lf", res, res);
                            }
                            break;
                        }
                        case '!':
                        {
                            a = 1;
                            if (res < 0)
                                sprintf(line_expression, "ты хочешь найти факториал отрицательного числа? я нет");
                            else if (res > 12)
                                sprintf(line_expression, "Я переиграл твоё переигрывание, я столько считать не буду '^'");
                            else
                                for (int i = 1; i <= res; i++)
                                {
                                    a = a * i;
                                }
                            line_expression = malloc((counter((int)res) + counter((int)(a)) + 2 * 7 + 4 + 1) * sizeof(char));
                            sprintf(line_expression, "%lf! = %lu", res, a);
                            res = a;
                            break;
                        }
                        case '^':
                        {
                            c = 1;                          //с возведением в степень была некая проблема
                            if (b < 0)                      //когда ты делишь 1 число кучу раз в цикле
                            {                               //оно становится равным нулю.
                                for (int i = 0; i > b; i--) //ну я как CoolHackerMan нашаманил в коде и
                                {                           //исправил ошибку: теперь у меня умножается в
                                    c = c * res;            //цикле кучу раз знаменатель, а потом 1 число
                                }                           //делится на этот знаменатель

                                line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(1 / c)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                                sprintf(line_expression, "%lf ^ %lf = %lf", res, b, 1 / c);
                            }
                            else
                            {
                                for (int i = 1; i <= b; i++)
                                {
                                    c = c * res;
                                }
                                line_expression = malloc((counter((int)res) + counter((int)b) + counter((int)(c)) + 3 * 7 + 2 * 3 + 1) * sizeof(char)); // Выделение памяти как и в след. вариантах
                                sprintf(line_expression, "%lf ^ %lf = %lf", res, b, c);
                            }
                            if (b < 0)
                            {
                                res = 1 / c;
                            }
                            else
                            {
                                res = c;
                            }
                            break;
                        }
                        default:
                        {
                            break;
                        }
                        }
                        //tic=1;

                        //printf("Хотите продолжить вычисления с ответом? y - да, другие символы - выход\n");

                        workWithRes = calc.current_settings->current_s->use_answer;
                        if (workWithRes == 'y')
                        {
                            push_list_out(line_expression, &calc);
                        }
                        if (workWithRes == 'y')
                        {
                            calc.current_settings = calc.current_settings->next;
                            calc.current_n = calc.current_n->next;
                        }
                    } while (workWithRes == 'y');

                    //printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");

                    res_s = calc.current_settings->close_calculator_subspecies;
                    if (res_s != 'e')
                    {
                        calc.current_settings = calc.current_settings->next;
                        calc.current_n = calc.current_n->next;
                    }
                    if (res_s != 'e')
                    {
                        push_list_out(line_expression, &calc);
                    }
                } while (res_s != 'e');
            }
            else if (start == 'v')
            {
                float *massiv, *res;
                int size, num;
                int sizeVector;  // для определения размера вектора
                char str, res_v; // <- о-операция

                do
                {
                    //printf("Введите размер вектора(>0) и количество векторов(>1): ");            //программа работает с 2 и более векторов
                    //fscanf(inputFile, "%d %d", &size, &num);
                    //scanf("%i",&num);
                    size = calc.current_settings->current_v->size;
                    num = calc.current_settings->current_v->num;
                    sizeVector = 0;

                    massiv = malloc((size * num) * sizeof(double));
                    res = malloc(size * sizeof(double));
                    for (int i = 1; i < num + 1; i++)
                    {
                        //printf("Введите координаты %i вектора: ", i);
                        for (int j = 0; j < size; j++)
                        {
                            massiv[size * (i - 1) + j] = calc.current_n->number_v[calc.current_settings->current_v->size * (i - 1) + j];
                            sizeVector += counter((int)massiv[size * (i - 1) + j]);
                        }
                        //printf("\n");
                    }
                    //printf("Введите операцию: ");
                    str = calc.current_settings->current_v->operations;

                    if ((size > 0) && (num > 2))
                    {
                        switch (str)
                        {
                        case '+':
                        {
                            for (int j = 0; j < size; j++) // обнуление ответа
                                res[j] = 0;

                            for (int i = 0; i < num; i++) // подсчёт ответа, делаем отдельно, чтобы узнать, сколько места потом заберёт ответ
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    res[j] = res[j] + massiv[size * i + j];
                                    if (i + 1 >= num)
                                        sizeVector += counter((int)res[j]);
                                }
                            }

                            line_expression = malloc((sizeVector + 1 + num * size * 7 + (num - 1) * 5 + 2 * (size - 1) * num + 4 + 1 + size * 7 + (size - 1) + 1 + 1) * sizeof(char));
                            // sizeV - количество места всех чисел до "," + первая ( + кол-во символов после "," для чисел до ответа + внутри векторов ,_ +
                            // + )_=_ + ( + кол-во символов после "," для чисел в ответе + внутри вектора ,_ в ответе + ) + _
                            sprintf(line_expression, "");
                            for (int i = 0; i < num; i++)
                            {
                                sprintf(line_expression, "%s(", line_expression);
                                for (int j = 0; j < size; j++)
                                {
                                    sprintf(line_expression, "%s%f", line_expression, massiv[size * i + j]);
                                    if (j != size - 1)
                                        sprintf(line_expression, "%s, ", line_expression);
                                }
                                sprintf(line_expression, "%s)", line_expression);
                                if (i != num - 1)
                                    sprintf(line_expression, "%s + ", line_expression);
                                else
                                    sprintf(line_expression, "%s = ", line_expression);
                            }

                            sprintf(line_expression, "%s(", line_expression);
                            for (int j = 0; j < size; j++)
                            {
                                sprintf(line_expression, "%s%f", line_expression, res[j]);
                                if (j != size - 1)
                                    sprintf(line_expression, "%s, ", line_expression);
                            }
                            sprintf(line_expression, "%s)", line_expression);
                            break;
                        }
                        case '-':
                        {
                            for (int j = 0; j < size; j++)
                                res[j] = 0;
                            for (int i = 0; i < num; i++)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (i == 0)
                                    {
                                        res[j] = massiv[j];
                                        if (i + 1 >= num)
                                            sizeVector += counter((int)res[j]);
                                    }
                                    else
                                    {
                                        res[j] = res[j] - massiv[size * i + j];
                                        if (i + 1 >= num)
                                            sizeVector += counter((int)res[j]);
                                    }
                                }
                            }

                            line_expression = malloc((sizeVector + 1 + num * size * 7 + (num - 1) * 5 + 2 * (size - 1) * num + 4 + 1 + size * 7 + (size - 1) + 1 + 1) * sizeof(char));
                            sprintf(line_expression, "");

                            for (int i = 0; i < num; i++)
                            {
                                sprintf(line_expression, "%s(", line_expression);
                                for (int j = 0; j < size; j++)
                                {
                                    sprintf(line_expression, "%s%f", line_expression, massiv[size * i + j]);
                                    if (j != size - 1)
                                        sprintf(line_expression, "%s, ", line_expression);
                                }
                                sprintf(line_expression, "%s)", line_expression);
                                if (i != num - 1)
                                    sprintf(line_expression, "%s - ", line_expression);
                                else
                                    sprintf(line_expression, "%s = ", line_expression);
                            }
                            sprintf(line_expression, "%s(", line_expression);
                            for (int j = 0; j < size; j++)
                            {
                                sprintf(line_expression, "%s%f", line_expression, res[j]);
                                if (j != size - 1)
                                    sprintf(line_expression, "%s, ", line_expression);
                            }
                            sprintf(line_expression, "%s)", line_expression);
                            break;
                        }
                        default:
                        {
                            sprintf(line_expression, "я на 50 шагов впереди тебя и всех остальных. Мой код не победить.(возможно)\n");
                            break;
                        }
                        } //<- switch
                        free(massiv);
                        free(res);
                        //printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");
                        res_v = calc.current_settings->close_calculator_subspecies;
                    }
                    else if ((size > 0) && (num == 2))
                    {
                        switch (str)
                        {
                        case '*': //приведение ответа к единице, так же перед подсчётом
                        {         //для скалярного произведения
                            for (int j = 0; j < size; j++)
                                res[j] = 1;
                            for (int i = 0; i < num; i++)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    res[j] = res[j] * massiv[size * i + j];
                                    if (i + 1 >= num)
                                        sizeVector += counter((int)res[j]);
                                }
                            }
                            for (int j = 1; j < size; j++)
                                res[0] = res[0] + res[j];
                            sizeVector += counter((int)res[0]);

                            line_expression = malloc((sizeVector + 1 + num * size * 7 + (num - 1) * 5 + 2 * (size - 1) * num + 4 + 1 * 7 + 1) * sizeof(char));
                            // так эе как и в прошлый раз, но после "+ 4" идёт: остаток от числа + _
                            sprintf(line_expression, "");
                            for (int i = 0; i < num; i++)
                            {
                                sprintf(line_expression, "%s(", line_expression);
                                for (int j = 0; j < size; j++)
                                {
                                    sprintf(line_expression, "%s%f", line_expression, massiv[size * i + j]);
                                    if (j != size - 1)
                                        sprintf(line_expression, "%s, ", line_expression);
                                }
                                sprintf(line_expression, "%s)", line_expression);
                                if (i != num - 1)
                                    sprintf(line_expression, "%s * ", line_expression);
                                else
                                    sprintf(line_expression, "%s = ", line_expression);
                            }
                            sprintf(line_expression, "%s%f", line_expression, res[0]);

                            break;
                        }
                        case '+':
                        {
                            for (int j = 0; j < size; j++)
                                res[j] = 0;
                            for (int i = 0; i < num; i++)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    res[j] = res[j] + massiv[size * i + j];
                                    if (i + 1 >= num)
                                        sizeVector += counter((int)res[j]);
                                }
                            }

                            line_expression = malloc((sizeVector + 1 + num * size * 7 + (num - 1) * 5 + 2 * (size - 1) * num + 4 + 1 + size * 7 + (size - 1) + 1 + 1) * sizeof(char));
                            sprintf(line_expression, "");
                            for (int i = 0; i < num; i++)
                            {
                                sprintf(line_expression, "%s(", line_expression);
                                for (int j = 0; j < size; j++)
                                {
                                    sprintf(line_expression, "%s%f", line_expression, massiv[size * i + j]);
                                    if (j != size - 1)
                                        sprintf(line_expression, "%s, ", line_expression);
                                }
                                sprintf(line_expression, "%s)", line_expression);
                                if (i != num - 1)
                                    sprintf(line_expression, "%s + ", line_expression);
                                else
                                    sprintf(line_expression, "%s = ", line_expression);
                            }
                            sprintf(line_expression, "%s(", line_expression);
                            for (int j = 0; j < size; j++)
                            {
                                sprintf(line_expression, "%s%f", line_expression, res[j]);
                                if (j != size - 1)
                                    sprintf(line_expression, "%s, ", line_expression);
                            }
                            sprintf(line_expression, "%s)", line_expression);
                            break;
                        }
                        case '-':
                        {
                            for (int j = 0; j < size; j++)
                                res[j] = 0;
                            for (int i = 0; i < num; i++)
                            {
                                for (int j = 0; j < size; j++)
                                {
                                    if (i == 0)
                                    {
                                        res[j] = massiv[j];
                                    }
                                    else
                                        res[j] = res[j] - massiv[size * i + j];
                                    if (i + 1 >= num)
                                        sizeVector += counter((int)res[j]);
                                }
                            }

                            line_expression = malloc((sizeVector + 1 + num * size * 7 + (num - 1) * 5 + 2 * (size - 1) * num + 4 + 1 + size * 7 + (size - 1) + 1 + 1) * sizeof(char));
                            sprintf(line_expression, "");

                            for (int i = 0; i < num; i++)
                            {
                                sprintf(line_expression, "%s(", line_expression);
                                for (int j = 0; j < size; j++)
                                {
                                    sprintf(line_expression, "%s%f", line_expression, massiv[size * i + j]);
                                    if (j != size - 1)
                                        sprintf(line_expression, "%s, ", line_expression);
                                }
                                sprintf(line_expression, "%s)", line_expression);
                                if (i != num - 1)
                                    sprintf(line_expression, "%s - ", line_expression);
                                else
                                    sprintf(line_expression, "%s = ", line_expression);
                            }

                            sprintf(line_expression, "%s(", line_expression);
                            for (int j = 0; j < size; j++)
                            {
                                sprintf(line_expression, "%s%f", line_expression, res[j]);
                                if (j != size - 1)
                                    sprintf(line_expression, "%s, ", line_expression);
                            }
                            sprintf(line_expression, "%s)", line_expression);
                            break;
                        }
                        default:
                        {
                            //sprintf(line_expression, "я на 50 шагов впереди тебя и всех остальных. Мой код не победить.(возможно)\n");
                            break;
                        }
                        } //<- switch
                        free(massiv);
                        free(res);
                        //printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");
                        res_v = calc.current_settings->close_calculator_subspecies;
                    }
                    else
                    {
                        //sprintf(line_expression, "Нужно вводить размер вектора(>0) и количество векторов(>1)!!!\n");
                    }
                    if (res_v != 'e')
                    {
                        calc.current_settings = calc.current_settings->next;
                        calc.current_n = calc.current_n->next;
                    }

                    if (res_v != 'e')
                    {
                        push_list_out(line_expression, &calc);
                    }

                } while (res_v != 'e');
            }
            else
            {
                //sprintf(line_expression, "Программа это запомнит.\n");
                //sprintf(line_expression, "Теперь программа отказывается вам помогать.");
            }
            //printf("Хотите завершить пользование калькулятором? e - выход из приложения, другие символы - продолжение\n");
            end = calc.current_settings->close_file;
            if (end != 'e')
            {
                calc.current_settings = calc.current_settings->next;
                calc.current_n = calc.current_n->next;
            }

            push_list_out(line_expression, &calc);

        } while (end != 'e');

        deleteList();
        writeAnswerToFile(outputFile);
        fclose(outputFile);
        deleteResults();

        printf("Хотите снова использовать калькулятор?(y-yes;n-no): "); // Вывод строки, с вопросом, продолжить ли вычисление с файлами
        scanf(" %c", &BackToTheFutures);                                // Читает символ, если y - продолжить, если n - закончить
        while ((BackToTheFutures != 'y') && (BackToTheFutures != 'n'))  // Проверка на корректно введенное y или n
        {
            printf("Пока ты не напишишь \"y\" или \"n\", ты не куда не уйдёшь.\n");
            scanf(" %c", &BackToTheFutures);
        }
        stepRepeat = 1;
    } while (BackToTheFutures == 'y');
    return 0;
}
