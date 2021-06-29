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

typedef struct numbers
{
    double num;
    struct numbers *next;
} numbers;

typedef struct operations
{
    char operation;
    struct operations *next;
} operations;

typedef struct calculator
{
    numbers *head_n;
    operations *head_o;
} calculator;

calculator calc;

double pop_n(calculator *stack)
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
    numbers *current = stack->head_n;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    lastNum = current->next->num;
    free(current->next);
    current->next = NULL;
    return lastNum;
}

char pop_o(calculator *stack)
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
    operations *current = stack->head_o;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    lastOperation = current->next->operation;
    free(current->next);
    current->next = NULL;
    return lastOperation;
}

void delete_n(calculator *stack)
{
    while (stack->head_n != NULL)
    {
        pop_n(stack);
    }
}

void delete_o(calculator *stack)
{
    while (stack->head_o != NULL)
    {
        pop_o(stack);
    }
}

void pushback_stack_n(double data, calculator *stack)
{
    if (stack->head_n == NULL)
    {
        stack->head_n = malloc(sizeof(numbers));
        stack->head_n->next = NULL;
        stack->head_n->num = data;
        return;
    }
    numbers *current = stack->head_n;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(numbers));
    current->next->num = data;
    current->next->next = NULL;
}

void pushback_stack_o(char data, calculator *stack)
{
    if (stack->head_o == NULL)
    {
        stack->head_o = malloc(sizeof(operations));
        stack->head_o->operation = data;
        stack->head_o->next = NULL;
        return;
    }
    operations *current = stack->head_o;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = malloc(sizeof(operations));
    current->next->operation = data;
    current->next->next = NULL;
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
    char computation_operation = pop_o(&calc);
    double secondNumToCalc = pop_n(&calc);
    double firstNumToCalc = pop_n(&calc);
    pushback_stack_n(calculation(firstNumToCalc, secondNumToCalc, computation_operation), &calc);
    return calculation(firstNumToCalc, secondNumToCalc, computation_operation);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char file_check, input[80], output[80], BackToTheFutures, theSameFile;
    int codeOffended = 0, stepRepeat = 0;

    do
    {
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
                    pushback_stack_n(line_to_num, &calc);
                    free(symbol);
                    break;
                case 0:
                    if (expression[i] == '!')
                    {
                        pushback_stack_n(calculation(pop_n(&calc), 0.0, '!'), &calc);
                        i++;
                        break;
                    }
                    if (expression[i] == '(')
                    {
                        brackets += 1;
                        pushback_stack_o('(', &calc);
                        i++;
                        break;
                    }
                    char line_to_operation = pop_o(&calc);
                    if (expression[i] == ')')
                    {
                        if (line_to_operation == ' ')
                        {
                            pushback_stack_o(line_to_operation, &calc);
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
                        pushback_stack_o(line_to_operation, &calc);
                        calc__result_of_evaluating_expression();
                        break;
                    }
                    else if ((prioritization(line_to_operation) >= prioritization(expression[i]))) // выбор части с большим приоритетом
                    {
                        if (line_to_operation != '(')
                        {
                            pushback_stack_o(line_to_operation, &calc);
                            calc__result_of_evaluating_expression();
                            checkNumSymbol = 1;
                            break;
                        }
                    }
                    if (line_to_operation != ' ')
                    {
                        pushback_stack_o(line_to_operation, &calc);
                    }
                    pushback_stack_o(expression[i], &calc);
                    i++;
                    break;
                }
            }

            while (calc.head_o != NULL)
            {
                calc__result_of_evaluating_expression();
            }

            switch (brackets)
            {
            case 0:
                if (calc.head_n->next == NULL)
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
                    fprintf(outputFile, "= %lf\n", pop_n(&calc)); // Записываем результат
                }
                else
                {
                    fprintf(outputFile, "Incorrect write expression\n");
                }
                break;
            }
            delete_n(&calc);
            delete_o(&calc);
        } while (taken_symbol != 'n');
        fclose(outputFile);
        fclose(inputFile);

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
