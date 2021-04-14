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
#include <stdio.h>   //решил пофлексить Каспер Дмитрий 1 курс 4 группа(ИВТ)
int main (int argc, char* argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);


    int a;
    printf("Выберите, что использовать: (1) - калькулятор обычный\n");
    printf("Выберите, что использовать: (2) - калькулятор векторный\n");
    scanf("%i",&a);
    if (a == 1)
    {
        //Задумка была такая: сделать калькулятор
        //не нагруженным в использовании, похожим
        unsigned long int a;                 //на калькулятор в Windows
        int tic;
        double res,b,c;
        char str,s,r;
        tic=0;
        printf("вы можете: взять факториал 1 числа(3 !), модуль 1 числа(3 a)\n");
        printf("сложить 2 числа(1 + 2), поделить(1 / 2), умножить(1 * 1)\n");
        printf("возвести 1 число в степень равную номеру 2 числа(1 ^ 2)\n");
        do
        {
            scanf("%lf",&res);             //тк калькулятор win может продолжить работу
            do                             //с ответом, я решил сделать также.
            {                              //поэтому у меня два while - 1 отвечает"не хотите ли
                if (tic == 1)              //вы закончить работу?"
                    printf("%lf",res);     //2 - отвечает "хотите продолжить работу с ответом?"
                scanf("%s",&str);
                if ((str != 'a') && (str != '!'))
                    scanf("%lf",&b);
                switch (str)
                {                               //есть возможность, если мы захотим
                    case '+':                   //продолжить работу с циклом.
                    {                           //высветится ответ, около которого мы можем написать
                        res=res+b;              //необходимую операцию и 2 число
                        printf("= %lf\n",res);
                        break;
                    }
                    case '-':
                    {
                        res=res-b;
                        printf("= %lf\n",res);
                        break;
                    }
                    case '*':
                    {
                        res=res*b;
                        printf("= %lf\n",res);
                        break;
                    }
                    case '/':
                    {
                        res=res/b;
                        printf("= %lf\n",res);
                        break;
                    }
                    case 'a':
                    {
                        if (res<0)
                            res=-res;
                        printf("= %lf\n",res);
                        break;
                    }
                    case '!':
                    {
                        a=1;
                        if (res<0)
                            printf("ты хочешь найти факториал отрицательного числа? я нет\n");
                        else if (res>12)
                            printf("Я переиграл твоё переигрывание, я столько считать не буду '^'\n");
                        else
                            for (int i=1;i<=res;i++)
                            {
                                a=a*i;
                            }
                        res=a;
                        printf("= %lf\n",res);
                        break;
                    }
                    case '^':
                    {
                        c=1;                      //с возведением в степень была некая проблема
                        if (b<0)                  //когда ты делишь 1 число кучу раз в цикле
                        {                         //оно становится равным нулю.
                            for (int i=0;i>b;i--) //ну я как CoolHackerMan нашаманил в коде и
                            {                     //исправил ошибку: теперь у меня умножается в
                                c=c*res;          //цикле кучу раз знаменатель, а потом 1 число
                            }                     //делится на этот знаменатель
                            res=1/c;
                        }                         //Импровизируй, Адаптируйся, Преодолевай
                        else if (b==0.0000000)
                        {
                            res=1;
                        }
                        else
                        {
                            for (int i=1;i<=b;i++)
                            {
                                c=c*res;
                            }
                            res=c;
                        }
                        printf("= %lf\n", res);
                        break;
                    }
                    default:
                    {
                        printf("я на 50 шагов впереди тебя и всех остальных. Мой код не победить.(возможно)\n");
                    }
                }
                tic=1;
                printf("Хотите продолжить вычисления с ответом? y - да, другие символы - выход\n");
                scanf(" %c",&s);
            } while (s == 'y');
            printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");
            scanf(" %c",&r);
        }
        while (r != 'e');
    }
    else if (a == 2)
    {
        float *massiv,*res;
        int size, num;
        char str;              // <- о-операция
        printf("Введите размер вектора и количество векторов: ");            //программа работает с 2 и более векторов
        scanf("%d %d",&size, &num);                                                  //может и с 1 но я не уверен, не проверял ))
        //scanf("%i",&num);
        massiv = malloc((size*num)*sizeof(int));
        res = malloc(size *sizeof(int));
        printf("Введите формулу по примеру:\n");
        printf("x1 y1 x2 y2 ... xn yn o, где n - количество векторов,\n");
        printf("o - операция (+ - *)\n");
        for (int i=0;i<size*num;i++)
        {
            scanf("%f",&massiv[i]);
        }
        scanf(" %c",&str);
        switch(str)
        {
            case '+':
            {
                printf("Результат сложения векторов: ");
                for (int j=0;j<size;j++)
                    res[j]=0;
                for (int i=0;i<num;i++)
                {
                    for (int j=0;j<size;j++)
                    {
                        res[j]=res[j] + massiv[size*i+j];
                    }
                }
                for (int j=0;j<size;j++)
                    printf("%f ", res[j]);
                break;
            }
            case '-':
            {
                printf("Результат разности векторов: ");
                for (int j=0;j<size;j++)       //суть в том, что вы можете использовать
                    res[j]=massiv[j];                  //больше 1 вектора в 1 операции
                for (int i=1;i<num;i++)
                {
                    for (int j=0;j<size;j++)
                    {
                        res[j]=res[j] - massiv[size*i+j];
                    }
                }
                for (int j=0;j<size;j++)
                    printf("%f ", res[j]);
                break;
            }
            case '*':
            {
                for (int j=0;j<size;j++)       //приведение ответа к единице, так же перед подсчётом
                    res[j]=1;                  //для скалярного произведения
                for (int i=0;i<num;i++)
                {
                    for (int j=0;j<size;j++)
                    {
                        res[j]=res[j] * massiv[size*i+j];
                    }
                }
                for (int j=1;j<size;j++)
                    res[0]=res[0]+res[j];
                printf("Результат скалярного произведения: %f ", res[0]);
                break;
            }
            default:
            {
                printf("я на 50 шагов впереди тебя и всех остальных. Мой код не победить.(возможно)\n");
            }
        }
        free(massiv);
        free(res);
    }
    else
    {
        printf("Программа это запомнит.\n");
        printf("Теперь программа отказывается вам помогать.");
    }
    return 0;
}
