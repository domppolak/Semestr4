#ifndef _TICTACTOE_HH
#define _TICTACTOE_HH

#include "libraries.hh"

#define WIN 1000
#define DRAW 0
#define LOSS -1000

#define START_DEPTH 0

class TicTacToe
{   
    //rozmiar pola kwadratowego
    int size_square;
    //rozmiar naszej gry
    int size_field;
    //ilosc znakow potrzebna do wygranej
    int num_of_sign;

    sf::RenderWindow window;
    char **tab_board;
    char XO = 'X';
    sf::Texture img_X, img_O;

    //flags
    bool user_move = true;
    bool game_active = false;

public:
    TicTacToe(int Arg1, int Arg2, int Arg3):
        size_square(Arg1),
        size_field(Arg2),
        num_of_sign(Arg3)
    {
        img_X.loadFromFile("X.png");
        img_O.loadFromFile("O.png"); 
    }
    ~TicTacToe() { delete_board(); }
    void delete_board();
    void init_game();
    void draw_board();
    void display_board();
    void game_loop();
    void user_click(sf::Vector2i localPosition);
    void game_over();
    void whose_turn();
    void draw_XO(sf::Texture &img,  int x, int y);
    void play_again();
    void choice_menu();
    void rand_who_start();
    //funckje sprawdzajace wygrana
    bool check_win();
    bool check_rows();
    bool check_columns();
    bool check_first_diagonal();
    bool check_second_diagonal();

    //MinMax algorytm
    bool is_move_left();
    int min_max(int depth, bool is_computer);
    void find_best_move(int move_index);
    void random_move();


};
#endif



