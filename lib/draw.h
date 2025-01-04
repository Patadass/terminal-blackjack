#include <ncurses.h>
#include <fstream>
#include <cstdio>

#ifndef DRAW_H
#define DRAW_H

#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define WHITE 8

struct Ascii_card{
public:
    int a_height, a_width;
    int suit_height, suit_width;
    char rank_ascii[5][12];
    char suit_ascii[4][5];
    Ascii_card(char rank, char suit){
        for(int i = 0;i < 5;i++){
            for(int j = 0;j < 9;j++){
                rank_ascii[i][j] = ' ';
            }
        }
        a_height = a_width = 0;
        std::ifstream file;
        if((rank >= '0' && rank <= '9') || rank == 'X'){
            file.open("cards/numbers");
        }else{
            file.open("cards/letters");
        }
        std::string line;
        bool found = false;
        while(getline(file, line)){
            if(found && line[0] != '*'){
                int ph_widht = 0;
                for(size_t i = 0;i < line.length();i++){
                    rank_ascii[a_height][ph_widht] = line[i];
                    ph_widht++;
                }
                if(a_width < ph_widht){
                    a_width = ph_widht;
                }
                a_height++;
            }
            if(found && line[0] == '*'){
                break;
            }
            if(found){
                continue;
            }
            if(line[0] == '*'){
                std::string s_num = "12";
                for(size_t i = 1;i < line.length();i++){
                    s_num[i-1] = line[i];
                }
                int num = stoi(s_num);
                if(num == rank){
                    found = true;
                }
            }
        }
        file.close();

        suit_height = suit_width = 0;
        file.open("cards/suits");
        found = false;
        while(getline(file, line)){
            if(found && line[0] != '*'){
                int ph_widht = 0;
                for(size_t i = 0;i < line.length();i++){
                    suit_ascii[suit_height][ph_widht] = line[i];
                    ph_widht++;
                }
                if(suit_width < ph_widht){
                    suit_width = ph_widht;
                }
                suit_height++;
            }
            if(found && line[0] == '*'){
                break;
            }
            if(found){
                continue;
            }
            if(line[0] == '*'){
                std::string s_num = "12";
                for(size_t i = 1;i < line.length();i++){
                    s_num[i-1] = line[i];
                }
                int num = stoi(s_num);
                if(num == suit){
                    found = true;
                }
            }
        }
        file.close();
    }

    void print(){
        for(int i = 0;i < a_height;i++){
            for(int j = 0;j < a_width;j++){
                printw("%c", rank_ascii[i][j]);
            }
            printw("\n");
        }
        refresh();
    }
};

class Draw{
public:
    //static void show_console_cursor(bool show);

    Draw(){
        _color_pair = 0;
        init_pair(1, COLOR_BLACK, COLOR_BLACK);
        init_pair(2, COLOR_BLACK, COLOR_RED);
        init_pair(3, COLOR_BLACK, COLOR_GREEN);
        init_pair(4, COLOR_BLACK, COLOR_YELLOW);
        init_pair(5, COLOR_BLACK, COLOR_BLUE);
        init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(7, COLOR_BLACK, COLOR_CYAN);
        init_pair(8, COLOR_BLACK, COLOR_WHITE);
    }

    void clear_screen(){
        clear();
    }

    void setxy(short x, short y){
        move(y, x);
    }

    void setxy(int x,int y){
        move(y, x);
    }

    void reset_color(){
        if(_color_pair == 0){
            return;
        }
        attroff(COLOR_PAIR(_color_pair));
    }

    void set_color(int w){
        _color_pair = w;
        attron(COLOR_PAIR(w));
    }

    void draw_fill_rect(int x, int y, int width,int height){
        for(int i = x;i < width+x;i++){
            for(int j = y;j < height+y;j++){
                setxy(i, j);
                printw(" \n");
            }
        }
        refresh();
    }

    void draw_rect(int x,int y,int width,int height){
        for(int i = x;i < width+x;i++){
            for(int j = y;j < height+y;j++){
                if(i == x || i+1 == width+x || j == y || j+1 == height+y){
                    setxy(i, j);
                    printw(" \n");
                }
            }
        }
        refresh();
    }

    void draw_ascii_rect(int x, int y, int width, int height){
        setxy(x, y);
        for(int i = 0;i < height;i++){
            setxy(x,y+i);
            for(int j = 0;j < width;j++){
                if(i == 0 || i + 1 == height){
                    printw("-");
                    continue;
                } 
                if(j == 0 || j + 1 == width){
                    printw("|");
                    continue;
                }
                printw(" ");
             }
        }
        refresh();
    }

    void draw_card(Ascii_card card, int x,int y){
        int width = 20;
        int height = 15;
        draw_ascii_rect(x, y, width, height);
        for(int i = 0;i < card.a_height;i++){
            setxy(x + 10 - (card.a_width/2), y + 1 + i);
            for(int j = 0;j < card.a_width;j++){
                printw("%c", card.rank_ascii[i][j]);
            }
        }
        for(int i = 0;i < card.suit_height;i++){
            setxy(x + 10 - (card.suit_width/2),y + 3 + card.a_height + i);
            for(int j = 0;j < card.suit_width;j++){
                printw("%c", card.suit_ascii[i][j]);
            }
        }
        refresh();
    }
private:
    int _color_pair;
};

#endif //DRAW_H
