#include "TicTacToe.hh"

int main()
{   
    std::srand(time(NULL));
    int arg1, arg2, arg3;
    std::cout << "Podaj rozmiar pola kwadratowego" << std::endl;
    std::cin >> arg1;
    std::cout << "Podaj rozmiar gry" << std::endl;
    std::cin >> arg2;
    std::cout << "Podaj liczbe znakow pod rzad potrzebnych do wygrania" << std::endl;
    std::cin >> arg3;

    TicTacToe game(arg1,arg2,arg3);
    game.game_loop();
    return 0;
}