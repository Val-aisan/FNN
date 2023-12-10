#include "nn.h"

//usage: ./programm "input nodes" "hidden layer" "node per hidden layer" "output nodes" "training file"
int main(int argc, char **argv)
{
    network_s   *new_network;
    int         cycle = 0;
    
    if (argc < 5)
        return (0);
    if (network_init(argv, &new_network))
        return (0);
    if (layers_init(&new_network))
        return (0);
    if (data_file_format(argv[5], &new_network))
        return (0);
    if (data_init(argv[5], &new_network))
        return (0);
    if (nodes_init(&new_network, cycle))
        return (0);
    print_network_s(new_network);
    cycle++;
    //if (nodes_init(&new_network))
     //   return(0);

}   