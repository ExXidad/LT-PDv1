//
// Created by Ivan Kalesnikau on 18.08.2022.
//

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

#define MAXSENTENCELENGTH 1024
#define MAXWORDLENGTH 64
#define MAXNUMBEROFWORDS 64

class Parser
{
private:
//    char buf[MAXSENTENCELENGTH] = {};
//    char *str[MAXNUMBEROFWORDS] = {};
    char *buf;
    char **str;
    char div;

public:
    int tmp;

public:
    Parser(char *data, char newDiv = ',')
    {
        buf = data;
        div = newDiv;
    }

    ~Parser()
    {
        clear();
    }

    void clear()
    {
        if (str) free(str);
    }

    int amount()
    {
        int i = 0, count = 0;
        while (buf[i++])
            if (buf[i] == div) count++;// подсчёт разделителей
        return ++count;
    }

    int split()
    {
        int am = amount();            // количество данных
        clear();                      // освобождаем буфер
        str = (char **) malloc(am * sizeof(char *)); // создаём буфер
        str[0] = buf;                 // строка 0
        int i = 0, j = 0;             // счётчики
        while (buf[i])
        {              // пока не NULL
            if (buf[i] == div)
            {        // если разделитель
                buf[i] = '\0';            // меняем на NULL
                str[++j] = buf + i + 1;   // запоминаем начало строки
            }
            i++;
        }
        tmp = am;
        return am;
    }

    int16_t getInt(int num)
    {
        return atol(str[num]);
    }

    float getFloat(int num)
    {
        return atof(str[num]);
    }

    char *operator[](uint16_t idx)
    {
        return str[idx];
    }
};

#endif
