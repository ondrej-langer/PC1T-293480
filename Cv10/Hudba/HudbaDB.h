#pragma once

#define INTERPRET_SIZE 50
#define ALBUM_SIZE 50

struct t_hudba
{
    char interpret[INTERPRET_SIZE];
    char album[ALBUM_SIZE];
    int  rok;
    struct t_hudba* dalsi;
};

void add(char* interpret, char* album, int rok,  struct t_hudba** uk_prvni);
void del(int rok, struct t_hudba** uk_prvni);
