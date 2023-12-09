#include "nn.h"

//usage: ./programm "input nodes" "hidden layer" "node per hidden layer" "output nodes" "training file"
int main(int argc, char **argv)
{
    network_s   *new_network;
    
    if (network_init(argv, new_network))
        return (0);
    /*if (layers_init(new_network))
        return (0);
    if (nodes_init(new_network))
        return(0);

    build_network(argv);*/
}