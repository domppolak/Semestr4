#ifndef _ADJACENCY_MATRIX_HH
#define _ADJACENCY_MATRIX_HH

#include "libraries.hh"

class AdjacencyMatrix
{   
    int **tab;
    int size;
    int node;
    int edge;
    int start_node;
public:
    AdjacencyMatrix() : tab(NULL){}
    ~AdjacencyMatrix() { delete_matrix(); }
    int get_size()  const { return this->size; }

    void create_matrix()
    {
        tab = new int *[this->size];
        for(int i(0); i < this->size; i++)
            { tab[i] = new int[this->size]; }

        for(int i(0); i < size; i++){
            for(int j(0); j < size; j++)
                { tab[i][j] = 0; }
        }
    }

    void delete_matrix()
    {
        for(int i(0); i < size; i++)
            { delete []tab; }
        delete []tab;
        tab = NULL;
    }

    int get_start_node() const { return start_node; }

    void set_all(int n, int e, int s_n)
    {   
        this->size = n;
        create_matrix(); //allocate memory for our matrix
        this->node = n;
        this->edge = e;
        this->start_node = s_n;
    }

    int get_value(int index1, int index2) const
    {
        if(index1>size && index2>size && index1<0 && index2<0){ 
            std::cerr << "Zly index" << std::endl;
            exit(1);
        }

        return tab[index1][index2];      
    }

    void set_value(int index1, int index2, int value)
    {
        if(index1>size && index2>size && index1<0 && index2<0){ 
            std::cerr << "Zly index" << std::endl;
            exit(1);
        }

        tab[index1][index2] = value;  
    }

};


std::istream &operator >> (std::istream &strm, AdjacencyMatrix &Arg1)
{
    int node, edge, s_node;
    int x,y,w;

    strm >> node >> edge >> s_node;
    Arg1.set_all(node, edge, s_node);

    for(int i(0); i < edge; i++){
        strm >> x >> y >> w;
        Arg1.set_value(x,y,w);

    }
    return strm;
}

std::ostream &operator << (std::ostream &strm, const AdjacencyMatrix &Arg1)
{
    for(int i(0); i < Arg1.get_size(); i++){
        for(int j(0); j < Arg1.get_size(); j++){
           strm << Arg1.get_value(i,j) <<  " ";
        }
        strm << std::endl;
    }

    return strm;
}

#endif