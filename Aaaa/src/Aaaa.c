/*   ,==================================================================================================,     |   \
    /| Name        : Aaaa.c                                                                             |\    |\/\
=====| Author      : Dmitrii Kasper                                                                     |======={H|
    \| Version     : (NOT FOUND)                                                                        |/    | \X
     | Copyright   : free_version                                                                       |     |   \
     | Description : calculator                                                                         |     |\
     | Git	      : https://github.com/Shin0kari/Calculator/                                            |     | \
     |                                                                                                  |     |  \
     |--------------------------------------------------------------------------------------------------|     |   \
     |                                                                                                  |     |\
     | Теперь вы ей обладаете, самое сложное уже выполнено, осталось зайти в Eclipse, зайти в           |     | \
     | workspace(свой или новый, не важно).                                                             |     |  \
     | Как откроется IDE сверху выбираем Window->Percpective->Open Percpective->Other...->Git.          |     |   \
     | Откроется специальное окно, нужно нажать clone git repository(в ряду с желтыми значками).        |     |\
     | Появится окно, в нем нужно вбить сслыку, либо до откытия clone git repository сохранить          |     | \
     | в буфер обмена ссылку и Eclipse все сделает сам(Authentication заполнять не нужно,               |     |  \
     | как и все остально кроме location, и в Connection выбрать протокол https).                       |     |   \
     | Жмем Next, снова жмем Next, выбираем путь, где будет хранится репозиторий из гит на вашем        |     |\
     | компьютере(Путь должен содержать только английские буквы, и не должен содержать пробелы),        |     | \
     | а также желательно нажать на галочку в import all esisting Eclipse project after clone finishes. |     |  \
     | Жмем finish и видим, что появилась папка в git repositories                                      |     |\  \
     | заходим в эту папку, дальше Working tree.                                                        |     | \
     | Видим папку Aaaa, жмем 1 раз на нее, потом правой кнопкой. И жмем Import Project.                |     |  \
    /| Появляется окно, в нем ничего выбирать не нужно, просто если Eclipse выбрал не ту папку,         |\    | /\\
=====| то стоит ее редактировать.                                                                       |======={H|
    \| Жмем finish и уже проект появляется в C/C++. Теперь вы можете смотреть код(Aaaa/src/Aaaa.c).     |/    | \/
     '=================================================================================================='   */ 

#include <stdio.h>
#include <stdlib.h>

#include "libs/list.h"
#include "libs/queue.h"
#include "libs/stack.h"

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

int prioritization(char operation) // расстановка приоритетов
{
    switch (operation)
    {
    case '(':
        return 4;
    case ')':
        return 4;
    case '^':
        return 3;
    case '*':
        return 2;
    case '/':
        return 2;
    case '+':
        return 1;
    case '-':
        return 1;
    default:
        return 0;
    }
}

short int checkNum(char num) // проверка элемента, является ли оно числом
{
    int truth = 0;
    char Char_numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //все возможные числа
    for (int i = 0; i < 10; i++)
    {
        if (num == Char_numbers[i])
        {
            truth = 1;
            return truth;
        }
    }
    return truth;
}

short int checkOperation(char symbol) // проверка элемента, является ли оно операцией
{
    int truth = 0;
    char Char_operations[] = {'^', '*', '/', '+', '-', '!'}; //все возможные операции
    if (symbol == ' ')
    {
        truth = 1;
        return truth;
    }
    for (int i = 0; i < 6; i++)
    {
        if (symbol == Char_operations[i])
        {
            truth = 1;
            return truth;
        }
    }
    return truth;
}

double calculation(double firstNum, double secondNum, char operation) // калькулятор для выражений
{
    switch (operation)
    {
    case '!':
        if (firstNum == 0)
        {
            return 1.0;
        }
        double resForIntegral = 1.0;
        for (int j = 1; j <= (int)firstNum; j++)
        {
            resForIntegral *= j;
        }
        return resForIntegral;
    case '^':
        if (secondNum == 0)
        {
            return 1;
        }
        if (secondNum < 0)
        {
            secondNum = -secondNum;
            firstNum = 1.0 / firstNum;
        }
        double result = 1.0;
        for (int i = 0; i < (int)secondNum; i++)
        {
            result *= firstNum;
        }
        return result;
    case '*':
        return firstNum * secondNum;
    case '/':
        return firstNum / secondNum;
    case '+':
        return firstNum + secondNum;
    case '-':
        return firstNum - secondNum;
    }
}

double calc__result_of_evaluating_expression() // подсчёт результата вычисления выражения
{
    char computation_operation = pop_o(&stack_calc);
    double secondNumToCalc = pop_n(&stack_calc);
    double firstNumToCalc = pop_n(&stack_calc);
    pushback_stack_n(calculation(firstNumToCalc, secondNumToCalc, computation_operation), &stack_calc);
    return calculation(firstNumToCalc, secondNumToCalc, computation_operation);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char file_check, input[80], output[80], BackToTheFutures, theSameFile, calculator_types;
    int codeOffended = 0, stepRepeat = 0;

    do
    {
        list_calc.head_settings = NULL;
        list_calc.head_n = NULL;
        list_calc.head_res = NULL;

        queue_calc.head_settings = NULL;
        queue_calc.head_n = NULL;
        queue_calc.head_res = NULL;

        stack_calc.head_o = NULL;
        stack_calc.head_n = NULL;

        printf("Выберите, какой использовать калькулятор(l - list, q - queue, s - stack): ");
        scanf(" %c", &calculator_types);
        printf("\n");

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

        if (calculator_types == 's')
        {
            char taken_symbol; // Читаем по одному элементу char
            do
            {

                char *expression; // записываем элементы в строку
                expression = malloc(125 * sizeof(char));
                int i = 0;
                do
                {
                    fscanf(inputFile, " %c ", &taken_symbol);
                    expression[i] = (taken_symbol != 'y' && taken_symbol != 'n') ? taken_symbol : ' '; // конец выражения выглядит так: ' '
                    if (++i >= 125)
                    {
                        break;
                    }
                } while (taken_symbol != 'y' && taken_symbol != 'n');

                i = 0;
                short int brackets = 0;        // Кол-во скобок
                short int checkNumSymbol = -1; // проверка, является ли char числом
                while (expression[i] != ' ')
                {
                    short int below_zero; // для отрицательных чисел
                    if (checkNumSymbol == 0 && expression[i] == '-' && (i + 1) < 125 && checkNum(expression[i + 1]))
                    {
                        below_zero = 1;
                        checkNumSymbol = 1;
                    }
                    else
                    {
                        below_zero = 0;
                        checkNumSymbol = checkNum(expression[i]);
                    }
                    switch (checkNumSymbol)
                    {
                    case 1:;
                        char *symbol; // Записываем сюда потенциальное число
                        symbol = malloc(15 * sizeof(char));
                        for (int j = 0; j < 15; j++)
                        {
                            if ((checkOperation(expression[i]) && !below_zero) || expression[i] == ' ' || expression[i] == '(' || expression[i] == ')')
                            {
                                break;
                            }
                            symbol[j] = expression[i];
                            below_zero = 0;
                            i++;
                        }
                        double line_to_num; // перевод строки в число
                        line_to_num = strtod(symbol, NULL);
                        pushback_stack_n(line_to_num, &stack_calc);
                        free(symbol);
                        break;
                    case 0:
                        if (expression[i] == '!')
                        {
                            pushback_stack_n(calculation(pop_n(&stack_calc), 0.0, '!'), &stack_calc);
                            i++;
                            break;
                        }
                        if (expression[i] == '(')
                        {
                            brackets += 1;
                            pushback_stack_o('(', &stack_calc);
                            i++;
                            break;
                        }
                        char line_to_operation = pop_o(&stack_calc);
                        if (expression[i] == ')')
                        {
                            if (line_to_operation == ' ')
                            {
                                pushback_stack_o(line_to_operation, &stack_calc);
                                brackets -= 1;
                                i++;
                                break;
                            }
                            if (line_to_operation == '(')
                            {
                                brackets -= 1;
                                i++;
                                break;
                            }
                            pushback_stack_o(line_to_operation, &stack_calc);
                            calc__result_of_evaluating_expression();
                            break;
                        }
                        else if ((prioritization(line_to_operation) >= prioritization(expression[i]))) // выбор части с большим приоритетом
                        {
                            if (line_to_operation != '(')
                            {
                                pushback_stack_o(line_to_operation, &stack_calc);
                                calc__result_of_evaluating_expression();
                                checkNumSymbol = 1;
                                break;
                            }
                        }
                        if (line_to_operation != ' ')
                        {
                            pushback_stack_o(line_to_operation, &stack_calc);
                        }
                        pushback_stack_o(expression[i], &stack_calc);
                        i++;
                        break;
                    }
                }

                while (stack_calc.head_o != NULL)
                {
                    calc__result_of_evaluating_expression();
                }

                switch (brackets)
                {
                case 0:
                    if (stack_calc.head_n->next == NULL)
                    {
                        i = 0;
                        while (expression[i] != ' ')
                        {
                            if (checkNum(expression[i]))
                            {
                                do
                                {
                                    if (checkOperation(expression[i]) || expression[i] == ' ' || expression[i] == '(' || expression[i] == ')')
                                    {
                                        break;
                                    }
                                    fprintf(outputFile, "%c", expression[i]);
                                    i++;
                                } while (1);
                                fprintf(outputFile, " ");
                            }
                            else
                            {
                                fprintf(outputFile, "%c ", expression[i]);
                                i++;
                            }
                        }
                        free(expression);
                        fprintf(outputFile, "= %lf\n", pop_n(&stack_calc)); // Записываем результат
                    }
                    else
                    {
                        fprintf(outputFile, "Incorrect write expression\n");
                    }
                    break;
                }
                delete_n(&stack_calc);
                delete_o(&stack_calc);
            } while (taken_symbol != 'n');
            fclose(outputFile);
            fclose(inputFile);
        }
        else if ((calculator_types == 'l') || (calculator_types == 'q'))
        {
            int *check_future, *check_future_1;
            char end;
            char *line_expression, *check_answer, *check_answer_1;

            check_future = malloc(1 * sizeof(int));
            check_future_1 = malloc(1 * sizeof(int));
            check_answer = malloc(1 * sizeof(char));
            check_answer_1 = malloc(1 * sizeof(char));

            if (calculator_types == 'l')
            {
                while (!feof(inputFile))
                {                                 // Заполнение всего листа settings
                    list_calculator example_list; // для создания 1 стр
                    fill_list(&example_list, inputFile, check_answer, check_future);
                    push_back(&example_list, check_answer_1, check_future_1);
                }
            }
            else
            {
                while (!feof(inputFile))
                {                                  // Заполнение всего листа settings
                    queue_calculator example_list; // для создания 1 стр
                    fill_queue(&example_list, inputFile, check_answer, check_future);
                    pushback_queue_in(&example_list, check_answer_1, check_future_1);
                }
            }

            free(check_future);
            free(check_future_1);
            free(check_answer);
            free(check_answer_1);

            fclose(inputFile);

            if (calculator_types == 'l')
            {
                list_calc.current_settings = list_calc.head_settings;
                list_calc.current_n = list_calc.head_n;
                list_calc.current_res = list_calc.head_res;

                do
                {
                    char start;
                    start = list_calc.current_settings->calc_type;

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

                            res = list_calc.current_n->number_s1; //тк калькулятор win может продолжить работу

                            do //с ответом, я решил сделать также.
                            {  //поэтому у меня два while - 1 отвечает"не хотите ли
                                /*if (tic == 1)              			    	//вы закончить работу?"
                        fprintf(outputFile,"%lf",res);*/
                                //2 - отвечает "хотите продолжить работу с ответом?"

                                str = list_calc.current_settings->current_s->operations;
                                if ((str != 'a') && (str != '!'))
                                    b = list_calc.current_n->number_s2;

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

                                workWithRes = list_calc.current_settings->current_s->use_answer;
                                if (workWithRes == 'y')
                                {
                                    push_list_out(line_expression, &list_calc);
                                }
                                if (workWithRes == 'y')
                                {
                                    list_calc.current_settings = list_calc.current_settings->next;
                                    list_calc.current_n = list_calc.current_n->next;
                                }
                            } while (workWithRes == 'y');

                            //printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");

                            res_s = list_calc.current_settings->close_calculator_subspecies;
                            if (res_s != 'e')
                            {
                                list_calc.current_settings = list_calc.current_settings->next;
                                list_calc.current_n = list_calc.current_n->next;
                            }
                            if (res_s != 'e')
                            {
                                push_list_out(line_expression, &list_calc);
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
                            size = list_calc.current_settings->current_v->size;
                            num = list_calc.current_settings->current_v->num;
                            sizeVector = 0;

                            massiv = malloc((size * num) * sizeof(double));
                            res = malloc(size * sizeof(double));
                            for (int i = 1; i < num + 1; i++)
                            {
                                //printf("Введите координаты %i вектора: ", i);
                                for (int j = 0; j < size; j++)
                                {
                                    massiv[size * (i - 1) + j] = list_calc.current_n->number_v[list_calc.current_settings->current_v->size * (i - 1) + j];
                                    sizeVector += counter((int)massiv[size * (i - 1) + j]);
                                }
                                //printf("\n");
                            }
                            //printf("Введите операцию: ");
                            str = list_calc.current_settings->current_v->operations;

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
                                res_v = list_calc.current_settings->close_calculator_subspecies;
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
                                res_v = list_calc.current_settings->close_calculator_subspecies;
                            }
                            else
                            {
                                //sprintf(line_expression, "Нужно вводить размер вектора(>0) и количество векторов(>1)!!!\n");
                            }
                            if (res_v != 'e')
                            {
                                list_calc.current_settings = list_calc.current_settings->next;
                                list_calc.current_n = list_calc.current_n->next;
                            }

                            if (res_v != 'e')
                            {
                                push_list_out(line_expression, &list_calc);
                            }

                        } while (res_v != 'e');
                    }
                    else
                    {
                        //sprintf(line_expression, "Программа это запомнит.\n");
                        //sprintf(line_expression, "Теперь программа отказывается вам помогать.");
                    }
                    //printf("Хотите завершить пользование калькулятором? e - выход из приложения, другие символы - продолжение\n");
                    end = list_calc.current_settings->close_file;
                    if (end != 'e')
                    {
                        list_calc.current_settings = list_calc.current_settings->next;
                        list_calc.current_n = list_calc.current_n->next;
                    }

                    push_list_out(line_expression, &list_calc);

                } while (end != 'e');

                deleteList();
                writeAnswerToFile(outputFile);
                fclose(outputFile);
                deleteResults();
            }
            else
            {
                do
                {
                    char start;
                    start = queue_calc.head_settings->calc_type;

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

                            res = queue_calc.head_n->number_s1; //тк калькулятор win может продолжить работу

                            do //с ответом, я решил сделать также.
                            {  //поэтому у меня два while - 1 отвечает"не хотите ли
                                /*if (tic == 1)              			    	//вы закончить работу?"
                        fprintf(outputFile,"%lf",res);*/
                                //2 - отвечает "хотите продолжить работу с ответом?"

                                str = queue_calc.head_settings->current_s->operations;
                                if ((str != 'a') && (str != '!'))
                                    b = queue_calc.head_n->number_s2;

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

                                workWithRes = queue_calc.head_settings->current_s->use_answer;
                                if (workWithRes == 'y')
                                {
                                    pushback_queue_out(line_expression, &queue_calc);
                                    pop_queue_in(&queue_calc);
                                }
                            } while (workWithRes == 'y');

                            //printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");

                            res_s = queue_calc.head_settings->close_calculator_subspecies;
                            if (res_s != 'e')
                            {
                                pushback_queue_out(line_expression, &queue_calc);
                                pop_queue_in(&queue_calc);
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
                            size = queue_calc.head_settings->current_v->size;
                            num = queue_calc.head_settings->current_v->num;
                            sizeVector = 0;

                            massiv = malloc((size * num) * sizeof(double));
                            res = malloc(size * sizeof(double));
                            for (int i = 1; i < num + 1; i++)
                            {
                                //printf("Введите координаты %i вектора: ", i);
                                for (int j = 0; j < size; j++)
                                {
                                    massiv[size * (i - 1) + j] = queue_calc.head_n->number_v[queue_calc.head_settings->current_v->size * (i - 1) + j];
                                    sizeVector += counter((int)massiv[size * (i - 1) + j]);
                                }
                                //printf("\n");
                            }
                            //printf("Введите операцию: ");
                            str = queue_calc.head_settings->current_v->operations;

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
                                res_v = queue_calc.head_settings->close_calculator_subspecies;
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
                                res_v = queue_calc.head_settings->close_calculator_subspecies;
                            }
                            else
                            {
                                //sprintf(line_expression, "Нужно вводить размер вектора(>0) и количество векторов(>1)!!!\n");
                            }

                            if (res_v != 'e')
                            {
                                pushback_queue_out(line_expression, &queue_calc);
                                pop_queue_in(&queue_calc);
                            }

                        } while (res_v != 'e');
                    }
                    else
                    {
                        //sprintf(line_expression, "Программа это запомнит.\n");
                        //sprintf(line_expression, "Теперь программа отказывается вам помогать.");
                    }
                    //printf("Хотите завершить пользование калькулятором? e - выход из приложения, другие символы - продолжение\n");
                    end = queue_calc.head_settings->close_file;
                    if (end != 'e')
                    {
                        pop_queue_in(&queue_calc);
                    }
                    pushback_queue_out(line_expression, &queue_calc);

                } while (end != 'e');

                delete_queue();
                write_queue_AnswerToFile(outputFile);
                fclose(outputFile);
                delete_queue_Results();
            }
        }

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
