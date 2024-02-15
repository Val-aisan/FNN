#include "nn.h"

//usage: ./programm "input nodes" "hidden layer" "node per hidden layer" "output nodes" "training file"
int main(int argc, char **argv)
{
    network_s       *new_network;
    network_mat_s   *matrices;
    gradient_s      *gradient;
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
    matrices = matrix_init(new_network);
    if (!matrices)
        return (0);
    //print_network_s(new_network);
    //print_input_output(new_network);
    //print_layers(matrices);
    if (pop_gradient(matrices, &gradient))
        return (0);
    //print_gradient(gradient);
    printf("hello\n");
    adjust_psy(new_network, &gradient, matrices);
    print_gradient(gradient);
    free_netwrk(&new_network);
    return (0);

}   