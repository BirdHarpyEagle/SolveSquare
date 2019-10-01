#include <stdio.h>
#include <math.h>


/**
	\brief Возвращается функциями SolveSquare() и SolveLinear(), если количество корней в уравнении бесконечно.
	 Равен 3, но по сути главное, чтобы не равнялся 0, 1 или 2.
*/
#define INFINITE 3

/**
	\brief Максимальное количество попыток, которое дается пользователю для ввода коэффициента.
*/
#define MAXTRIES 3

/**
	\brief Если установлен этот флаг, то считываемые функцией GetDouble() цифры идут в целую часть возвращаемого числа.
*/
#define BEFOREDOT 0

/**
	\brief Если установлен этот флаг, то считываемые функцией GetDouble() цифры идут в дробную часть возвращаемого числа.
*/
#define AFTERDOT 1

/**
    \brief Максимальное количество символов, которое может считать функция GetDouble().
*/
#define MAXCHARACTERS 60

/**
    \brief Используется функцией GetDouble(). С его помощью она оповещает о том, что введённое значение успешно обработано.
*/
#define SIGNAL_WORK_PROPERLY 0


/**
    \brief Используется функцией GetDouble(). С его помощью она оповещает о том,
    что введённое значение содержит более одной точки.
*/
#define ERROR_MORE_THAN_ONE_DOT 1

/**
    \brief Используется функцией GetDouble(). С его помощью она оповещает о том,
    что введённое значение содержит символ, не являющийся пробелом, цифрой, точкой, знаком или командой 'r'(restart).
*/
#define ERROR_WRONG_CHARACTER 2

/**
    \brief Используется функцией GetDouble(). С его помощью она оповещает о том,
    что введённое значение превышает максимально допустимую длину, задаваемую с помощью MAXCHARACTERS.
*/
#define ERROR_TOO_MUCH_CHARACTERS 3

/**
    \brief Используется функцией GetDouble(). С его помощью она оповещает о том,
    что пользователь ввел 'r'(restart), и ввод значений нужно перенести на первый коэффициент
*/
#define SIGNAL_RESTART 10


int SolveSquare(double a, double b, double c, double* x1, double* x2);
int SolveLinear(double a, double b, double* x);

int InputDouble(double* inputVariable, int maxTries, char inviteString[], char answerString[]);
int GetDouble(double* inputVariable);
void SkipCharacters();



/**
    \brief Основные задачи - форматный вывод, запуск функции InputDouble() нужное количество раз и обработка значений, возвращаемых функцией SolveSquare() (т.е. количество корней).

    Код функции:
    \code
    int main(void)
    {
        printf("Program name:\n\tSolveSquare\n");
        printf("Version:\n\t1.1.1\n");
        printf("Service:\n\tSquare equations solving\n");
        printf("Usage:\n\tWrite down the equation`s (double) coefficients.\n");
        printf("\tAs the result, program will return 2 strings:\n");
        printf("\t1st - number of roots, 2nd - roots (with '\\t' between).\n");
        printf("\tYou can restart the program`s input with 'r'.\n");
    
        double a, b, c;
        int inputDoubleResult = 0;
    
        while(1)
        {
            if((inputDoubleResult = InputDouble(&a, MAXTRIES, "Input a:\n", "a = ")) == ERROR_TOO_MUCH_CHARACTERS)
                return inputDoubleResult;
            if(inputDoubleResult == SIGNAL_RESTART)
                continue;
    
            if((inputDoubleResult = InputDouble(&b, MAXTRIES, "Input b:\n", "b = ")) == ERROR_TOO_MUCH_CHARACTERS)
                return inputDoubleResult;
            if(inputDoubleResult == SIGNAL_RESTART)
                continue;
    
            if((inputDoubleResult = InputDouble(&c, MAXTRIES, "Input c:\n", "c = ")) == ERROR_TOO_MUCH_CHARACTERS)
                return inputDoubleResult;
            if(inputDoubleResult == SIGNAL_RESTART)
                continue;
    
            if(inputDoubleResult != SIGNAL_RESTART && inputDoubleResult != ERROR_TOO_MUCH_CHARACTERS)
                break;
        }
    
    
        double x1 = NAN, x2 = NAN;
        int nRoots = SolveSquare(a, b, c, &x1, &x2);
    
        printf("Result:\n\tNumber of roots: ");
        switch(nRoots)
        {
            case 2:
            case 1:
            case 0:
                printf("%d\n", nRoots);
            if(x1 == x1)
                printf("\tRoots: %lg", x1);
            if(x2 == x2)
                printf("\t%lg\n", x2);
            else
                printf("\n");
            break;
    
            case INFINITE:
                printf("INFINITE\n");
                break;
      }
    }
    \endcode
    */
int main(void)
{
    printf("Program name:\n\tSolveSquare\n");
    printf("Version:\n\t1.1.1\n");
    printf("Service:\n\tSquare equations solving\n");
    printf("Usage:\n\tWrite down the equation`s (double) coefficients.\n");
    printf("\tAs the result, program will return 2 strings:\n");
    printf("\t1st - number of roots, 2nd - roots (with '\\t' between).\n");
    printf("\tYou can restart the program`s input with 'r'.\n");

    double a, b, c;
    int inputDoubleResult = 0;

    while(1)
    {
        if((inputDoubleResult = InputDouble(&a, MAXTRIES, "Input a:\n", "a = ")) == ERROR_TOO_MUCH_CHARACTERS)
            return inputDoubleResult;
        if(inputDoubleResult == SIGNAL_RESTART)
            continue;

        if((inputDoubleResult = InputDouble(&b, MAXTRIES, "Input b:\n", "b = ")) == ERROR_TOO_MUCH_CHARACTERS)
            return inputDoubleResult;
        if(inputDoubleResult == SIGNAL_RESTART)
            continue;

        if((inputDoubleResult = InputDouble(&c, MAXTRIES, "Input c:\n", "c = ")) == ERROR_TOO_MUCH_CHARACTERS)
            return inputDoubleResult;
        if(inputDoubleResult == SIGNAL_RESTART)
            continue;

        if(inputDoubleResult != SIGNAL_RESTART && inputDoubleResult != ERROR_TOO_MUCH_CHARACTERS)
            break;
    }


    double x1 = NAN, x2 = NAN;
    int nRoots = SolveSquare(a, b, c, &x1, &x2);

    printf("Result:\n\tNumber of roots: ");
    switch(nRoots)
    {
        case 2:
        case 1:
        case 0:
            printf("%d\n", nRoots);
        if(x1 == x1)
            printf("\tRoots: %lg", x1);
        if(x2 == x2)
            printf("\t%lg\n", x2);
        else
            printf("\n");
        break;

        case INFINITE:
            printf("INFINITE\n");
            break;
  }
}

/**
    \brief Вычисляет корни квадратного уравнения
    \param a,b,c Коэффициенты уравнения
    \param *x1,*x2 Области памяти, в которые нужно положить корни
    \return Количество корней
    
    Код функции:
    \code
    int SolveSquare(double a, double b, double c, double* x1, double* x2)
    {
        int rootsLinear = 0;
    
        if(a == 0)
            return SolveLinear(b, c, x1);
    
        if(c == 0)
        {
            rootsLinear = SolveLinear(a, b, x1);
            if(*x1 == 0)
                return rootsLinear;
            else
            {
                *x2 = 0;
                return rootsLinear + 1;
            }
        }
    
        double discr = b * b - 4.0 * a * c;
    
        if(discr < 0)
            return 0;
    
        if(discr == 0)
        {
            *x1 = (- b) / (2.0 * a);
            return 1;
        }
    
        if(discr > 0)
        {
            *x1 = (- b - sqrt(discr)) / (2.0 * a);
            *x2 = (- b + sqrt(discr)) / (2.0 * a);
            return 2;
        }
    }
    \endcode
*/
int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    int rootsLinear = 0;

    if(a == 0)
        return SolveLinear(b, c, x1);

    if(c == 0)
    {
        rootsLinear = SolveLinear(a, b, x1);
        if(*x1 == 0)
            return rootsLinear;
        else
        {
            *x2 = 0;
            return rootsLinear + 1;
        }
    }

    double discr = b * b - 4.0 * a * c;

    if(discr < 0)
        return 0;

    if(discr == 0)
    {
        *x1 = (- b) / (2.0 * a);
        return 1;
    }

    if(discr > 0)
    {
        *x1 = (- b - sqrt(discr)) / (2.0 * a);
        *x2 = (- b + sqrt(discr)) / (2.0 * a);
        return 2;
    }
}

/**
    \brief Решает линейные уравнения
    Также является частью функции SolveSquare()
    \param a,b Коэффициенты уравнения
    \param *x Область памяти, в которую нужно положить корень
    \return Количество корней
    
    Код функции:
    \code
    int SolveLinear(double a, double b, double* x)
    {
        if(a == 0)
        {
            if(b == 0)
                return INFINITE;
    
            else
                return 0;
        }
    
        else
        {
            *x = (- b) / a;
            return 1;
        }
    }
    \endcode
*/
int SolveLinear(double a, double b, double* x)
{
    if(a == 0)
    {
        if(b == 0)
            return INFINITE;

        else
            return 0;
    }

    else
    {
        *x = (- b) / a;
        return 1;
    }
}


/**
    \brief Форматное расширение функции GetDouble().
    В случае необычного поведения программы, выводит пользователю причину такого поведения.
    \param inputVariable Область памяти, в которую помещается вводимое значение
    \param maxTries Максимальное количество попыток, даваемое пользователю для ввода
    \param inviteString Строка-приглашение к вводу
    \param answerString Строка-ответ, оповещающая, как обработан ввод
    \return Ошибки и сигналы, оповещающие о результате работы функции. Идентичны GetDouble()

    Код функции:
    \code
    int InputDouble(double* inputVariable, int maxTries, char inviteString[], char answerString[])
    {
        int getDoubleResult;
    
        int countTries = 1;
        while(countTries <= maxTries)
        {
            printf("%s", inviteString);
            switch(getDoubleResult = GetDouble(inputVariable))
            {
                case ERROR_MORE_THAN_ONE_DOT:
                    printf("Error(InputDouble): used more than one dot\n");
                    countTries++;
                    break;
    
                case ERROR_WRONG_CHARACTER:
                    printf("Error(InputDouble): used wrong character\n");
                    countTries++;
                    break;
    
                case ERROR_TOO_MUCH_CHARACTERS:
                    printf("Error(InputDouble): used too much characters\n");
                    countTries++;
                    break;
    
                case SIGNAL_RESTART:
                    printf("Signal(InputDouble): signal 'r' detected, restarting the input...\n");
                    break;
    
                case SIGNAL_WORK_PROPERLY:
                    printf("%s", answerString);
                    printf("%lg\n", *inputVariable);
                    break;
            }
            if(getDoubleResult == SIGNAL_WORK_PROPERLY || getDoubleResult == SIGNAL_RESTART)
                break;
        }
        if(countTries > maxTries)
        {
            printf("Error(InputDouble): used all possible tries, terminating the program\n");
            return ERROR_TOO_MUCH_CHARACTERS;
        }
    
        return getDoubleResult;
    }
    \endcode
    */
int InputDouble(double* inputVariable, int maxTries, char inviteString[], char answerString[])
{
    int getDoubleResult;

    int countTries = 1;
    while(countTries <= maxTries)
    {
        printf("%s", inviteString);
        switch(getDoubleResult = GetDouble(inputVariable))
        {
            case ERROR_MORE_THAN_ONE_DOT:
                printf("Error(InputDouble): used more than one dot\n");
                countTries++;
                break;

            case ERROR_WRONG_CHARACTER:
                printf("Error(InputDouble): used wrong character\n");
                countTries++;
                break;

            case ERROR_TOO_MUCH_CHARACTERS:
                printf("Error(InputDouble): used too much characters\n");
                countTries++;
                break;

            case SIGNAL_RESTART:
                printf("Signal(InputDouble): signal 'r' detected, restarting the input...\n");
                break;

            case SIGNAL_WORK_PROPERLY:
                printf("%s", answerString);
                printf("%lg\n", *inputVariable);
                break;
        }
        if(getDoubleResult == SIGNAL_WORK_PROPERLY || getDoubleResult == SIGNAL_RESTART)
            break;
    }
    if(countTries > maxTries)
    {
        printf("Error(InputDouble): used all possible tries, terminating the program\n");
        return ERROR_TOO_MUCH_CHARACTERS;
    }

    return getDoubleResult;
}


/**
    \brief Преобразует вводимые символы в число формата double

    Принимает на вход пробельные символы, знаки(+ и -), цифры, точку.
    Пропускает и обрабатывает пробелы и знаки, в какой бы части числа они не были.
    Знак числа совпадает с последним введенным знаком.
    Ввиду реализации (с помощью getchar()), способен обрабатывать весьма необычные строки. Например:
    "+-0    1 6- 45.1 + 16" -> +1645.116 ; При вводе символа 'r' возвращает SIGNAL_RESTART,
    т.е. запрос о перезапуске.
    \param inputVariable Область памяти, в которую помещается вводимое значение
    \return Ошибки и сигналы, оповещающие о результате работы функции.

    Код функции:
    \code
    int GetDouble(double* inputVariable)
    {
        char character = 0;
        int stateRelativeToDot = BEFOREDOT;
        int countCharacters = 0;
        int errorsSignalsDetector = SIGNAL_WORK_PROPERLY;
    
        double powerAfterDotCounting = 0.1;
    
        int sign = 1;
        double variableBeforeDot = 0.0;
        double variableAfterDot = 0.0;
    
        while(((character = getchar()) != '\n') && (countCharacters++ <= MAXCHARACTERS))
        {
            if(character == ' ' || character == '\t')
                continue;
    
            if(character == '-' || character == '+')
            {
                if(character == '-')
                    sign = -1;
                else
                    sign = 1;
                continue;
            }
    
            if((character >= '0') && (character <= '9') && (stateRelativeToDot == BEFOREDOT))
            {
                variableBeforeDot = 10 * variableBeforeDot + character - '0';
                continue;
            }
    
            if(character == '.')
            {
                if(stateRelativeToDot == BEFOREDOT)
                {
                    stateRelativeToDot = AFTERDOT;
                    continue;
                }
                if(stateRelativeToDot == AFTERDOT)
                {
                    errorsSignalsDetector = ERROR_MORE_THAN_ONE_DOT;
                    break;
                }
            }
    
            if((character >= '0') && (character <= '9') && (stateRelativeToDot == AFTERDOT))
            {
                variableAfterDot = variableAfterDot + powerAfterDotCounting * (character - '0');
                powerAfterDotCounting /= 10;
                continue;
            }
    
            if(character == 'r')
            {
                errorsSignalsDetector = SIGNAL_RESTART;
                break;
            }
    
            errorsSignalsDetector = ERROR_WRONG_CHARACTER;
            break;
        }
    
        if(countCharacters > MAXCHARACTERS)
            errorsSignalsDetector = ERROR_TOO_MUCH_CHARACTERS;
    
        if(errorsSignalsDetector == SIGNAL_WORK_PROPERLY)
            *inputVariable = sign * (variableBeforeDot + variableAfterDot);
        else
            SkipCharacters();
    
        return errorsSignalsDetector;
    }
    \endcode
*/
int GetDouble(double* inputVariable)
{
    char character = 0;
    int stateRelativeToDot = BEFOREDOT;
    int countCharacters = 0;
    int errorsSignalsDetector = SIGNAL_WORK_PROPERLY;

    double powerAfterDotCounting = 0.1;

    int sign = 1;
    double variableBeforeDot = 0.0;
    double variableAfterDot = 0.0;

    while(((character = getchar()) != '\n') && (countCharacters++ <= MAXCHARACTERS))
    {
        if(character == ' ' || character == '\t')
            continue;

        if(character == '-' || character == '+')
        {
            if(character == '-')
                sign = -1;
            else
                sign = 1;
            continue;
        }

        if((character >= '0') && (character <= '9') && (stateRelativeToDot == BEFOREDOT))
        {
            variableBeforeDot = 10 * variableBeforeDot + character - '0';
            continue;
        }

        if(character == '.')
        {
            if(stateRelativeToDot == BEFOREDOT)
            {
                stateRelativeToDot = AFTERDOT;
                continue;
            }
            if(stateRelativeToDot == AFTERDOT)
            {
                errorsSignalsDetector = ERROR_MORE_THAN_ONE_DOT;
                break;
            }
        }

        if((character >= '0') && (character <= '9') && (stateRelativeToDot == AFTERDOT))
        {
            variableAfterDot = variableAfterDot + powerAfterDotCounting * (character - '0');
            powerAfterDotCounting /= 10;
            continue;
        }

        if(character == 'r')
        {
            errorsSignalsDetector = SIGNAL_RESTART;
            break;
        }

        errorsSignalsDetector = ERROR_WRONG_CHARACTER;
        break;
    }

    if(countCharacters > MAXCHARACTERS)
        errorsSignalsDetector = ERROR_TOO_MUCH_CHARACTERS;

    if(errorsSignalsDetector == SIGNAL_WORK_PROPERLY)
        *inputVariable = sign * (variableBeforeDot + variableAfterDot);
    else
        SkipCharacters();

    return errorsSignalsDetector;
}


/**
    \brief Пропускает все символы до следующего перевода каретки. Используется в GetDouble().

    Код функции:
    \code
    void SkipCharacters()
    {
        int character = 0;
        while((character = getchar()) != EOF && character != '\n')
            ;
    }
    \endcode

*/
void SkipCharacters()
{
    int character = 0;
    while((character = getchar()) != EOF && character != '\n')
        ;
}
