#ifndef _BF_ALGORITHM_HH
#define _BF_ALGORITHM_HH
#include "libraries.hh"
#include "adjacency_matrix.hh"
#include "adjacency_list.hh"

class BFalgorithm
{
    int *tab_cost; //tablica kosztow dojscia
    int *tab_previous; //tablica zawiera numer wierzhcolka bedacy poprzednikiem
                    // wierzhcolka na najkrotszej sciezce
    int node_t;
public:
    BFalgorithm():
    tab_cost(NULL)
    ,tab_previous(NULL) {}
    ~BFalgorithm() { delete_tab(); }
    void set_node(int node) {this->node_t = node; }
    int get_node() const { return node_t; }

    void create_tab(int node)
    {
        tab_cost = new int[node];
        tab_previous = new int [node];

        for(int i(0); i < node; i++){
            tab_cost[i] = MAX_INT; //przypisujemy koszt nieskonczonosc co 
                                //w naszym programie oznacza max wartosc inta
            tab_previous[i] = -1; //wartosc dla tablicy poprzednikow
        }
    }

    void display_path(int node)
    {
        int *tab_display = new int[node];
        int n = 0, m;

        for(int i(0); i < node; i++){
            std::cout << i << ": "; //jaki wierzcholek
            for(m = i; m != -1 && n < node; m=tab_previous[m]){
                tab_display[n++] = m;            //umieszczamy od pierwzego
                                                //do ostatniego
            }
            while(n){
                std::cout << tab_display[--n] << " "; // od pierwszego 
                                                    //do ostatniego
            }

            std::cout << "$" << tab_cost[i] << std::endl;
        }

        delete []tab_display;
        tab_display = NULL;
    }

    void save_path()
    {   
        std::ofstream file;
        file.open("path.txt");

        int *tab_display = new int[node_t];
        int n = 0, m;

        for(int i(0); i < node_t; i++){
            file << i << ": "; //jaki wierzcholek
            for(m = i; m != -1 && n < node_t; m=tab_previous[m]){
                tab_display[n++] = m;                
            }
            while(n){
                file << tab_display[--n] << " ";
            }

            file << "$" << tab_cost[i] << std::endl;
        }

        delete []tab_display;
        tab_display = NULL;
        file.close();
    }

    void delete_tab()
    {
        delete []tab_cost;
        delete []tab_previous;
        tab_cost = NULL;
        tab_previous = NULL;
    }

    void bf_algorithm(AdjacencyMatrix &matrix)
    {   
        int start_node = matrix.get_start_node();
        int node = matrix.get_size();
        create_tab(node);
        tab_cost[start_node] = 0; //wierzhcolek startowy koszt dojscia 0

        for(int i(0); i < node; i++){
            for(int j(0); j < node; j++){
                for(int k(0); k < node; k++){
                    if(tab_cost[j] != MAX_INT && matrix.get_value(k,j) != 0 && tab_cost[k] > tab_cost[j] + matrix.get_value(k,j)){
                            tab_cost[k] = tab_cost[j] + matrix.get_value(k,j);
                            tab_previous[k] = j;
                        }
                }
            }
        }
    }

    void bf_algorithm(AdjacencyList &list)
    {
        int start_node = list.get_start_node();
        int node = list.get_node();
        listelem *list_pom;
        create_tab(node);
        tab_cost[start_node] = 0;
        
        for(int i(1); i < node; i++){ //petla relaksacji
            for(int j(0); j < node; j++){ //petla przechodzenia przez kolejne wierzhcolki
                for(list_pom = list.get_tab_elem(j); list_pom; list_pom = list_pom->next){
                    if(tab_cost[j] != MAX_INT && tab_cost[list_pom->node] > tab_cost[j] + list_pom->weight){
                        tab_cost[list_pom->node] = tab_cost[j] + list_pom->weight;
                        tab_previous[list_pom->node] = j; //poprzednikiem sasiada bedzie j
                    }
                }
            }
        }
    }
};

#endif