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

    FILE *input,*output;
    input = fopen("input.txt","r");
    output = fopen("output.txt","w");
    char start, end;


    /*printf("Выберите, что использовать: (s) - simple calculator\n");     //<- из консольного калькулятора
    printf("Выберите, что использовать: (v) - vector calculator\n");*/


    do
    {
    fscanf(input," %c",&start);
    if (start == 's')
    {
        									 //Задумка была такая: сделать калькулятор
        									 //не нагруженным в использовании, похожим
        unsigned long int a;                 //на калькулятор в Windows
        //int tic;
        double res,b,c;
        char str,workwithres,res_s;
        do
        {
        //tic=0;


        /*printf("вы можете: взять факториал 1 числа(3 !), модуль 1 числа(3 a)\n");      //<- из консольного калькулятора
        printf("сложить 2 числа(1 + 2), поделить(1 / 2), умножить(1 * 1)\n");
        printf("возвести 1 число в степень равную номеру 2 числа(1 ^ 2)\n");*/


        	fscanf(input,"%lf",&res);             				//тк калькулятор win может продолжить работу
            do                             				        //с ответом, я решил сделать также.
            {                              				        //поэтому у меня два while - 1 отвечает"не хотите ли
                /*if (tic == 1)              			    	//вы закончить работу?"
                    fprintf(output,"%lf",res);*/     		    //2 - отвечает "хотите продолжить работу с ответом?"
                fscanf(input," %c",&str);
                if ((str != 'a') && (str != '!'))
                	fscanf(input,"%lf",&b);
                switch (str)
                {                               						  //есть возможность, если мы захотим
                    case '+':                   						  //продолжить работу с циклом.
                    {                          							  //высветится ответ, около которого мы можем написать
                        fprintf(output,"%lf + %lf = %lf\n",res,b,res+b);  //необходимую операцию и 2 число
                        res=res+b;
                        break;
                    }
                    case '-':
                    {

                    	fprintf(output,"%lf - %lf = %lf\n",res,b,res-b);  //необходимую операцию и 2 число
                    	res=res-b;
                        break;
                    }
                    case '*':
                    {
                    	fprintf(output,"%lf * %lf = %lf\n",res,b,res*b);  //необходимую операцию и 2 число
                    	res=res*b;
                        break;
                    }
                    case '/':
                    {
                    	fprintf(output,"%lf / %lf = %lf\n",res,b,res/b);  //необходимую операцию и 2 число
                    	res=res/b;
                        break;
                    }
                    case 'a':
                    {
                        if (res<0)
                        {
                        	fprintf(output,"abs(%lf) = %lf\n",res, -res);
                        	res=-res;
                        }
                        else
                        {
                        	fprintf(output,"abs(%lf) = %lf\n",res, res);
                        }
                        break;
                    }
                    case '!':
                    {
                        a=1;
                        if (res<0)
                        	fprintf(output,"ты хочешь найти факториал отрицательного числа? я нет\n");
                        else if (res>12)
                        	fprintf(output,"Я переиграл твоё переигрывание, я столько считать не буду '^'\n");
                        else
                            for (int i=1;i<=res;i++)
                            {
                                a=a*i;
                            }
                        fprintf(output,"%lf! = %lu\n",res,a);           // Help Vlada
                        res=a;
                        break;
                    }
                    case '^':
                    {
                        c=1;                      							//с возведением в степень была некая проблема
                        if (b<0)                  							//когда ты делишь 1 число кучу раз в цикле
                        {                         							//оно становится равным нулю.
                            for (int i=0;i>b;i--) 							//ну я как CoolHackerMan нашаманил в коде и
                            {                     							//исправил ошибку: теперь у меня умножается в
                                c=c*res;          							//цикле кучу раз знаменатель, а потом 1 число
                            }                     							//делится на этот знаменатель
                            fprintf(output,"%lf ^ %lf = %lf\n",res, b, 1/c);
                        }
                        else
                        {
                            for (int i=1;i<=b;i++)
                            {
                                c=c*res;
                            }
                            fprintf(output,"%lf ^ %lf = %lf\n",res, b, c);
                        }
                        if (b<0)
                        {
                        	res=1/c;
                        }
                        else
                        {
                        	res=c;
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

                fscanf(input," %c",&workwithres);
            } while (workwithres == 'y');

            //printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");

            fscanf(input," %c",&res_s);
        }
        while (res_s != 'e');
    }
    else if (start == 'v')
    {
        float *massiv,*res;
        int size, num;
        char str, res_v;              // <- о-операция
        do
        {
        	//printf("Введите размер вектора(>0) и количество векторов(>1): ");            //программа работает с 2 и более векторов
        	fscanf(input,"%d %d",&size, &num);
        	//scanf("%i",&num);

        	massiv = malloc((size*num)*sizeof(int));
        	res = malloc(size *sizeof(int));
        	for (int i=1;i<num+1;i++)
        	{
        		//printf("Введите координаты %i вектора: ", i);
        		for (int j=0;j<size;j++)
            	{
        			fscanf(input,"%f",&massiv[size*(i-1)+j]);
            	}
        		//printf("\n");
        	}
        	//printf("Введите операцию: ");
        	fscanf(input," %c",&str);
        	if ((size > 0) && (num > 2))
        	{
        	switch(str)
        	{
        	case '+':
        	{
        	    for (int j=0;j<size;j++)
        	        res[j]=0;
        	    for (int i=0;i<num;i++)
        	    {
        	    	fprintf(output,"(");
        	        for (int j=0;j<size;j++)
        	        {
        	        	res[j]=res[j] + massiv[size*i+j];
        	        	fprintf(output,"%f", massiv[size*i+j]);
        	        	if (j != size-1)
        	        		fprintf(output,", ");
        	        }
        	        fprintf(output,") ");
        	        if (i != num-1)
        	        	fprintf(output,"+ ");
        	        else
        	        	fprintf(output,"= ");
        	    }
        	    fprintf(output,"(");
        	    for (int j=0;j<size;j++)
        	    {
        	    	fprintf(output,"%f", res[j]);
        	        if (j != size-1)
        	        	fprintf(output,", ");
        	    }
        	    fprintf(output,")\n");
        	    break;
        	}
        	case '-':
        	{
        	    for (int j=0;j<size;j++)
        	        res[j]=0;
        	    for (int i=0;i<num;i++)
        	    {
        	    	fprintf(output,"(");
        	        for (int j=0;j<size;j++)
        	        {
        	        	if (i==0)
        	        		res[j]=massiv[j];
        	        	else
        	        		res[j]=res[j] - massiv[size*i+j];
        	        	fprintf(output,"%f", massiv[size*i+j]);
        	        	if (j != size-1)
        	        		fprintf(output,", ");
        	        }
        	        fprintf(output,") ");
        	        if (i != num-1)
        	        	fprintf(output,"- ");
        	        else
        	        	fprintf(output,"= ");
        	    }
        	    fprintf(output,"(");
        	    for (int j=0;j<size;j++)
        	    {
        	    	fprintf(output,"%f", res[j]);
        	        if (j != size-1)
        	        	fprintf(output,", ");
        	    }
        	    fprintf(output,")\n");
        	    break;
        	}
            default:
            {
            	fprintf(output,"я на 50 шагов впереди тебя и всех остальных. Мой код не победить.(возможно)\n");
            	break;
            }
        	}  //<- switch
        	free(massiv);
        	free(res);
			//printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");
        	fscanf(input," %c",&res_v);
        	}
        	else if ((size > 0) && (num == 2))
        	{
        		switch (str)
        		{
        			case '*':                   //приведение ответа к единице, так же перед подсчётом
        			{                           //для скалярного произведения
        				for (int j=0;j<size;j++)
        					res[j]=1;
        				for (int i=0;i<num;i++)
        				{
        					fprintf(output,"(");
        					for (int j=0;j<size;j++)
        					{
        						res[j]=res[j] * massiv[size*i+j];
        						fprintf(output,"%f", massiv[size*i+j]);
        						if (j != size-1)
        							fprintf(output,", ");
        					}
        					fprintf(output,") ");
        					if (i != num-1)
        						fprintf(output,"* ");
        					else
        						fprintf(output,"= ");
        				}
        				for (int j=1;j<size;j++)
        				    res[0]=res[0]+res[j];
        				fprintf(output,"%f\n", res[0]);
        				break;
        			}
        			case '+':
        			{
        				for (int j=0;j<size;j++)
        				    res[j]=0;
        				for (int i=0;i<num;i++)
        				{
        					fprintf(output,"(");
        					for (int j=0;j<size;j++)
        				    {
        				        res[j]=res[j] + massiv[size*i+j];
        				        fprintf(output,"%f", massiv[size*i+j]);
        				        if (j != size-1)
        				        	fprintf(output,", ");
        				    }
        					fprintf(output,") ");
        					if (i != num-1)
        						fprintf(output,"+ ");
        					else
        						fprintf(output,"= ");
        				}
        				fprintf(output,"(");
        				for (int j=0;j<size;j++)
        				{
        					fprintf(output,"%f", res[j]);
        				    if (j != size-1)
        				    	fprintf(output,", ");
        				}
        				fprintf(output,")\n");
        				break;
        			}
        			case '-':
        			{
        			    for (int j=0;j<size;j++)
        			        res[j]=0;
        			    for (int i=0;i<num;i++)
        			    {
        			    	fprintf(output,"(");
        			        for (int j=0;j<size;j++)
        			        {
        			        	if (i==0)
        			        	{
        			        		res[j]=massiv[j];
        			        	}
        			        	else
        			        		res[j]=res[j] - massiv[size*i+j];
        			        	fprintf(output,"%f", massiv[size*i+j]);
        			        	if (j != size-1)
        			        		fprintf(output,", ");
        			        	}
        			        	fprintf(output,") ");
        			        	if (i != num)
        			        		fprintf(output,"- ");
        			        	else
        			        		fprintf(output,"= ");
        			        }
        			    	fprintf(output,"(");
        			        for (int j=0;j<size;j++)
        			        {
        			        	fprintf(output,"%f", res[j]);
        			        if (j != size-1)
        			        	fprintf(output,", ");
        			    }
        			    fprintf(output,")\n");
        			    break;
        			}
        			default:
        			{
        				fprintf(output,"я на 50 шагов впереди тебя и всех остальных. Мой код не победить.(возможно)\n");
        			}
        		} //<- switch
        		free(massiv);
        		free(res);
        		//printf("Хотите завершить вычисления? e - выход из приложения, другие символы - продолжение\n");
        		fscanf(input," %c",&res_v);
        	}
        	else
        	{
        		fprintf(output,"Нужно вводить размер вектора(>0) и количество векторов(>1)!!!\n");
        	}
        }
        while (res_v != 'e');
    }
    else
    {
    	fprintf(output,"Программа это запомнит.\n");
    	fprintf(output,"Теперь программа отказывается вам помогать.");
    }
    //printf("Хотите завершить пользование калькулятором? e - выход из приложения, другие символы - продолжение\n");
    fscanf(input," %c",&end);
	}
    while (end != 'e');
    return 0;
}
