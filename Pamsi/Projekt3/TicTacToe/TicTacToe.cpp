#include "TicTacToe.hh"

void TicTacToe::init_game()
{
    window.create(sf::VideoMode(size_square*size_field, size_square*size_field), "TicTacToe"); 
    window.clear(sf::Color(255,255,255)); 
    tab_board = new char *[size_field];

    for(int i(0); i < size_field; i++)
        { tab_board[i] = new char[size_field]; }
    
    for(int i(0); i < size_field; i++){
        for(int j(0); j < size_field; j++){
            tab_board[i][j] = '-';
        }
    }


}

void TicTacToe::delete_board()
{
    for(int i(0); i < size_field; i++){
        delete [] tab_board[i];
    }
    delete [] tab_board;
    tab_board = nullptr;
}   

void TicTacToe::draw_board()
{
    for(int i(0); i < size_field; i++)
    {
        sf::Vertex line1[2] 
        {
            sf::Vertex(sf::Vector2f(0, size_square*i), sf::Color(0,0,0)),
            sf::Vertex(sf::Vector2f(size_square*size_field, size_square*i), sf::Color(0,0,0))
        };
        sf::Vertex line2[2] 
        {
            sf::Vertex(sf::Vector2f(size_square*i, 0), sf::Color(0,0,0)),
            sf::Vertex(sf::Vector2f(size_square*i, size_field*size_square), sf::Color(0,0,0)) 
        };
        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
    }

}

void TicTacToe::display_board()
{
    draw_board();
    window.display();
}

void TicTacToe::choice_menu()
{
    int arg1, arg2, arg3;
    std::cout << "Podaj rozmiar pola kwadratowego" << std::endl;
    std::cin >> arg1;
    std::cout << "Podaj rozmiar gry" << std::endl;
    std::cin >> arg2;
    std::cout << "Podaj liczbe znakow potrzebnych do wygrania" << std::endl;
    std::cin >> arg3;
    size_square = arg1;
    size_field = arg2;
    num_of_sign = arg3;

}

void TicTacToe::game_loop()
{
    init_game();
    display_board();
    while(window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                { window.close(); }
        }

        int move_index = 0;
        while(is_move_left())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    { window.close(); }
                if(event.type == sf::Event::MouseButtonPressed && user_move)
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        user_click(sf::Mouse::getPosition(window)); 
                        move_index++;
                        whose_turn();
                    }
                }
            }

            if(check_win() || !is_move_left())
                { break; }
            if(!user_move)
            {
                find_best_move(move_index++);
                whose_turn();
            }
            if(check_win())
                { break; }
        }

        if(check_win())
        { 
            game_over(); 
            play_again();
        }else
        {
            std::cout << "It's a draw" << std::endl;
            play_again();
        }

    }
}

void TicTacToe::game_over()
{   
    if(check_win())
    {
        if(!user_move)
            std::cout << "You won" << std::endl;
        else
            std::cout << "You lost" << std::endl;
    }

}

void TicTacToe::rand_who_start()
{
    user_move = rand() % 2;
    if(!user_move)
    {
        random_move();
        whose_turn();
    }
}

void TicTacToe::play_again()
{
    std::cout << "Zagrac ponownie: y/n" << std::endl;
    char choice;
    std::cin >> choice;
    if(choice == 'y')
        {      
            delete_board();
            choice_menu();
            init_game();
            display_board();
            rand_who_start();
        }
    else
        { window.close(); }
    

}


void TicTacToe::user_click(sf::Vector2i localPosition)
{
    int x(0),y(0);

    for(int i(0); i < size_field; i++)
    {
        if(localPosition.x > size_square*i && localPosition.x < size_square*i+size_square)
        {
            y = i;
        }

        if(localPosition.y > size_square*i && localPosition.y < size_square*i+size_square)
        {
            x = i;
        }
    }

    if(tab_board[x][y] == '-')
    {
        tab_board[x][y] = 'X';
        draw_XO(img_X, x, y);
    }

    return;
}

void TicTacToe::draw_XO(sf::Texture &img, int x, int y)
{
    sf::Sprite sprite;
    float scl = size_square/200.00;
    sprite.setTexture(img);
    sprite.setPosition(size_square*y, size_square*x);
    sprite.setScale(scl, scl);
    display_board();
    window.draw(sprite);
    window.display();
}    

void TicTacToe::whose_turn()
{
    if(user_move)
        { user_move = false; }
    else
        { user_move = true;}
}

bool TicTacToe::check_win()
{   
    if(check_rows())
        { return true; }
    else if(check_columns())
        { return true; }
    else if(check_first_diagonal())
        { return true; }
    else if(check_second_diagonal())
        { return true; }

    return false;
}

bool TicTacToe::check_rows()
{   
    for(int row(0); row < size_field; row++)
    {
       int counter = 0;
       char previous = '-';

       for(int i(0); i < size_field; i++)
       {
           if(tab_board[row][i] != '-')
           {
               if(tab_board[row][i] == previous)
                    { counter++; }
                else 
                    { counter = 1; }
           }

           if(counter >= num_of_sign)
            { return true; }

            previous = tab_board[row][i];
       }
    }

    return false;
}

bool TicTacToe::check_columns()
{   
    for(int column(0); column < size_field; column++)
    {
       int counter = 0;
       char previous = '-';

       for(int i(0); i < size_field; i++)
       {
           if(tab_board[i][column] != '-')
           {
               if(tab_board[i][column] == previous)
                    { counter++; }
                else 
                    { counter = 1; }
           }

           if(counter >= num_of_sign)
            { return true; }

            previous = tab_board[i][column];
       }
    }

    return false;
}

bool TicTacToe::check_first_diagonal()
{
    for (int k = size_field % num_of_sign; k >= 0; k--)
    {
        int counterD = 0,  counterU = 0;
        char prevDiagDown = '-', prevDiagUp = '-';
        for (int i = k; i < size_field; i++)
        {
            if (tab_board[i][i - k] != '-')
            {
                if (tab_board[i][i - k] == prevDiagDown)
                    { counterD++; }
                else
                    { counterD = 1; }
            }

            if (counterD >= num_of_sign)
                { return true; }

            if (tab_board[i - k][i] != '-')
            {
                if (tab_board[i - k][i] == prevDiagUp)
                    { counterU++; }
                else
                    { counterU = 1; }
            }

            if (counterU >= num_of_sign)
                { return true; }

            prevDiagDown = tab_board[i][i - k];
            prevDiagUp = tab_board[i - k][i];
        }
    }

    return false;
}

bool TicTacToe::check_second_diagonal()
{
    for (int k = 0; k < size_field * 2; k++)
    {
        char previous = '-';
        int counter = 0;
        for (int j = 0; j <= k; j++)
        {
            int i = k - j;
            if (i < size_field && j < size_field)
            {
                if (tab_board[i][j] != '-')
                {
                    if (tab_board[i][j] == previous)
                        { counter++; }
                    else if (previous == '-')
                        { counter = 1; }
                    else
                        { counter = 0; }
                }

                if (counter >= num_of_sign)
                    return true;

                previous = tab_board[i][j];
            }
        }
    }
    return false;
}

bool TicTacToe::is_move_left()
{
    for(int i(0); i < size_field; i++){
        for(int j(0); j < size_field; j++)
        {
            if(tab_board[i][j] == '-')
                { return true; }
        }
    }

    return false;
}

int TicTacToe::min_max(int depth, bool is_computer)
{
    int score = 0;
    int best_score = 0;

    if(check_win())
    {
        if(is_computer == true)
            { return -1; }
        if(is_computer == false)
            { return +1; }
    } 
    else
    {
        if(depth < size_field*size_field && depth > size_field*size_field-10)
        {
            if(is_computer == true)
            {
                best_score = -999;
                for(int i(0); i < size_field; i++){
                    for(int j(0); j < size_field; j++)
                    {
                        if(tab_board[i][j] == '-')
                        {
                            tab_board[i][j] = 'O';
                            score = min_max(depth+1, false);
                            tab_board[i][j] = '-';
                            if(score > best_score)
                                { best_score = score; }

                        }
                    }
                }
                return best_score;
            }
            else
            {
                best_score = 999;
                for(int i(0); i < size_field; i++){
                    for(int j(0); j < size_field; j++)
                    {
                        if(tab_board[i][j] == '-')
                        {
                            tab_board[i][j] = 'X';
                            score = min_max(depth+1, true);
                            tab_board[i][j] = '-';
                            if(score < best_score)
                                { best_score = score; }

                        }
                    }
                }
                return best_score;
            }
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

void TicTacToe::find_best_move(int move_index)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;

    if (size_field *size_field - move_index < 10)
    {
        for (int i = 0; i < size_field; i++){
            for (int j = 0; j < size_field; j++)
            {
                if (tab_board[i][j] == '-')
                {
                    tab_board[i][j] = 'O';
                    score = min_max(move_index + 1 , false);
                    tab_board[i][j] = '-';
                    if (score > bestScore)
                    {
                        bestScore = score;
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if(tab_board[x][y])
        {
            tab_board[x][y] = 'O';
            draw_XO(img_O, x, y);
        }
    }
    else
        find_best_move(size_field * size_field - 3);
}

void TicTacToe::random_move()
{
    int x = rand() % size_field;
    int y = rand() % size_field;

    if(tab_board[x][y] == '-')
    {
        tab_board[x][y] = 'O';
        draw_XO(img_O, x, y);
    }
}