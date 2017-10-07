
#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>

using namespace std;

typedef struct Menu_Item_S {
    char*       text;
} Menu_Item_T;

Menu_Item_S* menuItems;

int setup()
{
    menuItems = (Menu_Item_S*) malloc(sizeof(Menu_Item_S));

    menuItems->text = "Oyo";

    return 0;
}

int loop()
{
    printf("'%s'\n", menuItems->text);
    sleep(5);

    return 0;
}

int main(int argc, char *argv[])
{
    setup();

    for (;;) {
        loop();
    }

    return 0;
}

