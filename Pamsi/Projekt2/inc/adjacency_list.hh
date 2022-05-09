#ifndef _ADJACENCY_LIST_HH
#define _ADJACENCY_LIST_HH

#include "libraries.hh"

struct listelem
{
    int node;
    int weight;
    listelem* next;
};

class AdjacencyList
{
    int node;
    int edge;
    int start_node;
    listelem **tab_list;

public:
    AdjacencyList() { tab_list = NULL; }
    ~AdjacencyList() { delete_list(); }

    void delete_list()
    {
        delete []tab_list;
        tab_list = NULL;
    }

    void set_elem(int node, int edge, int start_node)
    {
        this->node = node;
        this->edge = edge;
        this->start_node = start_node;
        create_list();
    }
    
    void create_list()
    {
        tab_list = new listelem *[node];
        for(int i(0); i < node; i++){
            tab_list[i] = NULL;
        }
    }

    listelem *get_tab_elem(int index) const
    {
        if(index>edge && index<0){ 
            std::cerr << "Zly index" << std::endl;
            exit(1);
        }
        return tab_list[index];
    }
    
    void set_tab_elem(listelem *list, int index)
    {
        if(index>edge && index<0){ 
            std::cerr << "Zly index" << std::endl;
            exit(1);
        }
        tab_list[index] = list;
    }

    int get_node() const
    {
        return this->node;
    }

    int get_start_node() const 
    {
        return this->start_node;
    }
};


std::istream &operator >> (std::istream &strm, AdjacencyList &Arg1)
{
    listelem *list;
    int node, edge, start_node;
    int x,y,w;
    strm >> node >> edge >> start_node;
    Arg1.set_elem(node, edge, start_node);

    for(int i(0); i < edge; i++){
        strm >> x >> y >> w;
        list = new listelem;
        list->node = y;
        list->weight = w;
        list->next = Arg1.get_tab_elem(x);
        Arg1.set_tab_elem(list, x);
    }
    list = NULL;
    return strm;
    
}

std::ostream &operator << (std::ostream &strm, const AdjacencyList &Arg1)
{
    listelem *list;
    for(int i(0); i < Arg1.get_node(); i++)
    {   
        list = Arg1.get_tab_elem(i);
        while(list)
        {
            strm << list->node << " ";
            list = list->next;
        }

        strm << std::endl;
    }

    delete []list;
    list = NULL;
    return strm;
}


#endif