
#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <curses.h>

using namespace std;

struct Menu_S;

typedef struct Menu_Item_S {
  char*           text;
  Menu_S*         menu;
  void            (*callback)(int o);
} Menu_Item_T;

typedef struct {
  char*               prompt;
  int                 nbItems;
  Menu_Item_S**       items;
} Menu_T;

const int MENU_COUNT = 1;
const int MENU_ITEMS_COUNT = 5;
const int MENU_ITEMS_TEXT_MAX = 16;

Menu_T* appMenu = (Menu_T*) malloc(MENU_COUNT * sizeof(Menu_T));

void doMenuAction(int selectedMenuItem)
{
    printf("%d\n", selectedMenuItem);
}

int setup()
{
    Menu_Item_T** items = (Menu_Item_T**) malloc(MENU_ITEMS_COUNT * sizeof(Menu_Item_T*));
    for (int i = 0; i < MENU_ITEMS_COUNT; ++i) {
        items[i] = (Menu_Item_S*) malloc(sizeof(Menu_Item_T));

        items[i]->text = (char*) malloc(MENU_ITEMS_TEXT_MAX * sizeof(char));
        sprintf(items[i]->text, "ITEM %d", i);
        items[i]->callback = &doMenuAction;
    }

    for (int h = 0; h < MENU_COUNT; ++h) {
        appMenu = (Menu_T*) malloc(sizeof(Menu_T));

        appMenu->prompt = "Choose:";
        appMenu->nbItems = MENU_ITEMS_COUNT;
        appMenu->items = items;
    }

    return 0;
}

int loop()
{
    char buffer[100];

    initscr();
    //(void)echo();

    addstr("What is your name> ");

    refresh();
    getnstr(buffer, sizeof(buffer) - 1);

    clear();

    // printw("Greetings and salutations %s!\n", buffer);
    printw("%s\n", appMenu->prompt);
    for (int i = 0; i < appMenu->nbItems; ++i) {
        printw("%s\n", appMenu->items[i]->text);
    }
    refresh();

    //mvaddch(LINES - 1, COLS - 1, '.');
    printw("\n\n\nPress ENTER to quit.");
    refresh();

    //getnstr(buffer, sizeof(buffer) - 1);
    while (10 != getch());
    endwin();

    return 0;
}

int main(int argc, char *argv[])
{
    setup();

    for (;;) {
        int exitValue = loop();
        if (exitValue == 0) {
            break;
        }
    }

    return 0;
}

