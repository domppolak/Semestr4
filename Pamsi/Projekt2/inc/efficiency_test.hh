#ifndef _EFFICIENCY_TEST_HH
#define _EFFICIENCY_TEST_HH

#include "adjacency_matrix.hh"
#include "adjacency_list.hh"
#include "libraries.hh"
#include "bf_algorithm.hh"

class EfficiencyTest
{
    int nodes[5] = {10, 50, 100, 500, 250};
    int density[4] = {25, 50, 75, 100};

public:
    EfficiencyTest() {}
    void generate_graph_to_file(int node, int edge)
    {
    int lp = edge-node+1;
    int num_node = node;
    int tmp = 0, count = 0;

    std::ofstream file;
    file.open("graph.txt", std::ios::app);
    file << node << " " << edge << " " << std::rand()%node << std::endl;

    for(int i(0); i < node-1 && i < edge-1; i++){
        file << i << " " << i+1 << " " << std::rand()%100+1 << std::endl;
    }

    while(count < lp){
        tmp = 0;

        while(count < lp && tmp < num_node - 2){
            file << num_node - 1 << " " << tmp << " " << std::rand()%10+1 << std::endl;
            count++;
            tmp++;
            
        }
        num_node--;
    }

    file.close();
    }

    void load_graph(AdjacencyList &list, AdjacencyMatrix &matrix)
    {
        std::ifstream file;
        file.open("graph.txt");
        file >> matrix;
        file.seekg(0);
        file >> list;
        file.close();
    }

    void save_results(double time, std::string name, int node, int den)
    {
        std::string source, tmp[4] = {"25", "50", "75", "100"};
        
        switch (node)
        {
            case 10:
                source = ".\\results\\10_"+tmp[den]+"_"+name+".txt";
                break;
            case 50:
                source = ".\\results\\50_"+tmp[den]+"_"+name+".txt";
                break;
            case 100:
                source = ".\\results\\100_"+tmp[den]+"_"+name+".txt";
                break;
            case 500:
                source = ".\\results\\500_"+tmp[den]+"_"+name+".txt";
                break;
            case 250:
                source = ".\\results\\250_"+tmp[den]+"_"+name+".txt";
                break;
            default:
                break;
        }

        std::ofstream file;
        file.open(source, std::ios::app);
        if(file.fail())
        {
        std::cerr << "Nie udalo sie zapisac" << std::endl;
        return;
        }
        file << time << std::endl;
        file.close();

    }

    double measurement_list(AdjacencyList &list)
    {
        BFalgorithm bf;
        std::ifstream file;
        file.open("graph.txt");
        auto start = std::chrono::steady_clock::now();
        for(int i(0); i < 100; i++){
            file >> list;
            bf.bf_algorithm(list);
            bf.delete_tab();
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        file.close();
        bf.~BFalgorithm();
        return  elapsed_seconds.count();    
    }

    double measurement_matrix(AdjacencyMatrix &matrix)
    {
        BFalgorithm bf;
        std::ifstream file;
        file.open("graph.txt");
        auto start = std::chrono::steady_clock::now();
        for(int i(0); i < 100; i++){
            file >> matrix;
            bf.bf_algorithm(matrix);
            bf.delete_tab();
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        file.close();
        bf.~BFalgorithm();
        return  elapsed_seconds.count();
    }

    void measurement(int node, int edge, int den)
    {   
        double time;
        AdjacencyList list;
        AdjacencyMatrix matrix;
        std::ofstream file;
        file.open("graph.txt");
        file.close();
        for(int i(0); i < 100; i++){
            generate_graph_to_file(node, edge);
        } 
            time = measurement_matrix(matrix);
            save_results(time, "matrix", node, den);
            time = measurement_list(list);
            save_results(time, "list", node, den);
            list.~AdjacencyList();
            matrix.~AdjacencyMatrix();
        
    }
    void test()
    {
        int max_edge, edge;
        for(int i(4); i < 5;i++){
            max_edge = nodes[i] *(nodes[i]-1)/2;
            for(int j(0); j<4;j++){
                edge = density[j]*max_edge/100;
                measurement(nodes[i], edge, j); //liczba od 1 do 4 jakie wypelnienie
            }
        }
    }


};

#endif