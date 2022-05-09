#include "efficiency_test.hh"

void menu();
void menu_wyboru(int choice, AdjacencyList &list, AdjacencyMatrix &matrix, BFalgorithm &bf);
void how_display(int choice, AdjacencyList &list, AdjacencyMatrix &matrix);

int main()
{ 
    std::srand(time(NULL));
    AdjacencyList list;
    AdjacencyMatrix matrix;
    BFalgorithm bf;
    int choice;
    while(true)
    {
        menu();
        std::cin >> choice;
        if(choice == 6){
            break;
        }

        menu_wyboru(choice, list, matrix, bf);
    }
    std::cout<< "Koniec" << std::endl;

}


void menu()
{
    std::cout << "-----MENU-----" << std::endl
    << "1. Test efektywnosci" << std::endl
    << "2. Wczytaj graf" << std::endl
    << "3. Wyswietl graf" << std::endl
    << "4. Zapisz sciezke" << std::endl
    << "5. Wygeneruj graf do pliku" << std::endl
    << "6. koniec" << std::endl;
}

void menu_wyboru(int choice, AdjacencyList &list, AdjacencyMatrix &matrix, BFalgorithm &bf)
{
    std::string source;
    std::ifstream file;
    int node, edge;
    EfficiencyTest test;
    switch (choice)
    {
        case 1:
            test.test();
            break;
        case 2:
            std::cout << "Nazwa pliku" << std::endl;
            std::cin >> source;
            file.open(source);
            if(file.fail()){
            std::cerr << "Nie ma takiego pliku" << std::endl;
            return;
            }
            file >> matrix;
            file.seekg(0);
            file >> list;
            file.close();
            break;
        case 3:
            std::cout << "Sposob wyswietlenia" << std::endl
            << "1. lista sasiedztwa" << std::endl
            << "2. macierz sasiedztwa" << std::endl;
            std::cin >> choice;
            how_display(choice, list, matrix);
            break;
        case 4:
            bf.bf_algorithm(matrix);
            bf.set_node(matrix.get_size());
            bf.save_path();
            break;
        case 5:
            std::cout << "Podaj liczbe wierzholkow i krawedzi: ";
            std::cin >> node >> edge;
            test.generate_graph_to_file(node, edge);
            break;
    
        default:
            std::cerr << "nie ma takiej opcji" << std::endl;
            break;
    }
}

void how_display(int choice, AdjacencyList &list, AdjacencyMatrix &matrix)
{
        switch (choice)
        {
            case 1:
                std::cout << "----Lista sasiedztwa ----" << std::endl;
                std::cout << list;
            break;
            case 2:
                std::cout << "----Macierz sasiedztwa ----" << std::endl;
                std::cout << matrix;
            break;
        
            default:
                std::cerr << "Zly wybor" << std::endl;
                return;
                break;
        }       
}