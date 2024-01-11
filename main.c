#include "nn.h"

//usage: ./programm "input nodes" "hidden layer" "node per hidden layer" "output nodes" "training file"
int main(int argc, char **argv)
{
    network_s       *new_network;
    //network_mat_s   *network_matrices;
    int             cycle = 0;
    
    if (is_error(argc, argv))
        return (0);
    if (network_init(argv, &new_network))
        return (0);
    if (file_data_init(&new_network, argv))
        return (0);
    if (nodes_init(&new_network))
        return (0);
    compute_output(&new_network, new_network->inputs[cycle]);
    if (matrix_init(new_network))
        return (0);
    print_network_s(new_network);
    //print_layers(network_matrices);
    free_netwrk(&new_network);
    return (0);

}   