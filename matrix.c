#include "nn.h"

//allocate a layer's fields with needed network parameters
static int matrix_alloc(network_s *network, network_mat_s **matrices)
{
    int i = 1;
    int k = 0;
    int j = 0;
    layer_s **layer = (*matrices)->layer;
    
    while (network->layers[i])
    {
        layer[k] = malloc(sizeof(layer_s));
        j = 0;
        layer[k]->n = network->nodes_per_layer[i];
        layer[k]->m = network->nodes_per_layer[i - 1];
        //as soon  as the programm hit this line it exits 
        layer[k]->a = malloc(sizeof(double) * (network->nodes_per_layer[i]));
        layer[k]->b = malloc(sizeof(double) * (network->nodes_per_layer[i]));
        layer[k]->x = malloc(sizeof(double) * network->nodes_per_layer[i - 1]);
        layer[k]->z = malloc(sizeof(double) * network->nodes_per_layer[i]);
        layer[k]->w = malloc(sizeof(double *) * (network->nodes_per_layer[i]));
        while(j < network->nodes_per_layer[i])
            layer[k]->w[j++] =  malloc(sizeof(double) * (network->nodes_per_layer[i - 1]));
        i++;
        k++;

    }
    layer[k] = 0;
    return (0);
}

//allocate network's layers of matrices structure
static int matrices_alloc(network_s *network, network_mat_s  **matrices)
{
    if (!(*matrices))
        return (-1);
    (*matrices)->layer = malloc(sizeof(layer_s *) * (network->hidden_layer + 2));
    if (!((*matrices)->layer))
    {
        free(matrices);
        return (-1);
    }
    if (matrix_alloc(network, matrices))
    {
        return (-1);
    }
    return (0);
}

//fill field of layer with parameters
static void    fill_matrices(node_s *node, layer_s **layer, int node_nbr, int node_prev_layer)
{
    int     i = 0;
    double  z = 0;

    (*layer)->a[node_nbr] = node->value;
    (*layer)->b[node_nbr] = node->bias;
    while (i < node_prev_layer)
    {
        z += (*layer)->x[i] * node->weights[i];
        (*layer)->w[node_nbr][i] = node->weights[i];
        i++;
    }
    (*layer)->z[node_nbr] = z; 
    
}

//fill matrices structure
static int matrices_init(network_s *network, network_mat_s **matrices)
{
    int i = 1;
    int k = 0;
    int j = 0;
    node_s  *node;
    node_s  *node_2;
    int node_prev_layer;

    while (network->layers[i])
    {
        node = network->layers[i];
        j = 0;
        node_prev_layer = network->nodes_per_layer[i - 1];
        node_2 = network->layers[i - 1];
        while (j < node_prev_layer)
        {
            (*matrices)->layer[k]->x[j++] = node_2->value;
            node_2 = node_2->next;
        }
        j = 0;
        while (node)
        {
            fill_matrices(node, &((*matrices)->layer[k]), j, node_prev_layer);
            node = node->next;
            j++;
        }
        k++;
        i++;
    }
    return (0);
}

//initialization of networks's layers
network_mat_s   *matrix_init(network_s *network)
{
    network_mat_s   *matrices;
    
    matrices = malloc(sizeof(network_mat_s));
    if(matrices_alloc(network, &matrices))
    {
        return (0);
    }
    if (matrices_init(network, &matrices))
    {
        return (0);
    }
    //print_layers(matrices);
    return (matrices);           

}