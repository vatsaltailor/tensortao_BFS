#include <iostream>
#include "graph.h"

int main(int args, char **argv)
{
    std::cout << "Input: ./exe beg csr weight\n";
    if(args != 4)
    {
        std::cout << "Wrong input\n";
        return -1;
    }
    
    const char *beg_file = argv[1];
    const char *csr_file = argv[2];
    const char *weight_file = argv[3];
    
    graph<long, long, int, long, long, char> *ginst = new graph<long, long, int, long, long, char>(beg_file, csr_file, weight_file);
    
    ginst->BFS(0);

    delete ginst;

    return 0;   
}
