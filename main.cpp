#include <ncurses.h>

#include "lib/draw.h"
#include "lib/blackjack.h"

using namespace std;

int main(){
    initscr();
    start_color();

    Draw draw;
    Ascii_card card('X','s');

    draw.draw_card(card, 10,10);
    getch();
    endwin();
    return 0;
}
