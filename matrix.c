#include "nn.h"

int matrix_alloc(network_s *network, matrix_s  **layer)
{
    int i = 1;
    int j = 0;

    while (network->layers[i])
    {
        j = 0;
        layer[i]->n = network->nodes_per_layer[i];
        layer[i]->m = network->nodes_per_layer[i - 1];
        layer[i]->a = malloc(sizeof(double) * network->nodes_per_layer[i]);
        layer[i]->b = malloc(sizeof(double) * network->nodes_per_layer[i]);
        layer[i]->x = malloc(sizeof(double) * network->nodes_per_layer[i]);
        layer[i]->z = malloc(sizeof(double) * network->nodes_per_layer[i]);
        layer[i]->w = malloc(sizeof(double *) * (network->nodes_per_layer[i] + 1));
        while(j < network->nodes_per_layer[i])
            layer[i]->w[j++] =  malloc(sizeof(double) * (network->nodes_per_layer[i - 1] + 1));
        layer[i]->w[j] = 0;
        i++;

    }
    layer[i] = 0;

}



int matrices_alloc(network_s *network, network_mat_s  **matrices)
{
    (*matrices) = malloc(sizeof(network_mat_s));
    if (!(*matrices))
        return (-1);
    (*matrices)->layer = malloc(sizeof(matrix_s *) * network->hidden_layer + 2);
    if (!(*matrices)->layer)
    {
        free(matrices);
        return (-1);
    }
    if (matrix_alloc(network, (*matrices)->layer))
        return (-1);
}



int matrix_init(network_s *network, network_mat_s **matrices)
{
    if(matrices_alloc(network, matrices))
        return (-1);

}