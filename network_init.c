#include "nn.h"

//complete the node_per_layer field of the netwrk structure
static int node_per_layer(network_s **ntwrk)
{
    int layers = (*ntwrk)->hidden_layer + 2;
    int i = 0;

    (*ntwrk)->nodes_per_layer = malloc(sizeof(int) * layers + 1);
    if (!(*ntwrk)->nodes_per_layer)
        return (-1);
    while (i < layers)
    {
        if (i == 0)
            (*ntwrk)->nodes_per_layer[i] = (*ntwrk)->input_nodes;
        else if (i + 1 == layers)
            (*ntwrk)->nodes_per_layer[i] = (*ntwrk)->output_nodes;
        else
            (*ntwrk)->nodes_per_layer[i]  = (*ntwrk)->hidden_layer_nodes;
        i++;
    }
    (*ntwrk)->nodes_per_layer[i] = 0;
    return (0); 
}

//build a chained list of nodes with their respective number of weights
static node_s  *lst_build(int nodes_nbr, int weights_nbr)
{
    node_s  *head = 0;
    node_s  *node;
    int i = 0;

    //printf("nodes_nbr: %d\n", nodes_nbr);
    while (i < nodes_nbr)
    {
        node = new_node(weights_nbr);
        if (!node)
            return (NULL);
        add_node(node, &head);
        i++;
    }

    return (head);
}

//initialize each layers (chained list) of the ntwrk structure
static int layers_init(network_s  **ntwrk)
{
    int i = 0;
    int layers = (*ntwrk)->hidden_layer + 2;
    int weights_nbr;

    while (i < layers)
    {
        weights_nbr = (*ntwrk)->nodes_per_layer[i - 1];
        //printf("i: %d, layers: %d\n", i,  layers);
        if (i == 0)
        {
            (*ntwrk)->layers[i] = lst_build((*ntwrk)->input_nodes, 0);
        }
        else if (i + 1 == layers)
        {
            (*ntwrk)->layers[i] = lst_build((*ntwrk)->output_nodes, weights_nbr);
        }
        else
        {
            (*ntwrk)->layers[i] = lst_build((*ntwrk)->hidden_layer_nodes, weights_nbr);
        }
        if (!(*ntwrk)->layers[i])
            return (-1);
        i++;
        
    }
    (*ntwrk)->layers[i] = 0;
    return (0);

}

//initialize non-file related fields of ntwrk structure
int network_init(char **argv, network_s **ntwrk)
{   
    *ntwrk = malloc(sizeof(network_s));
    if (!ntwrk)
        return (-1);
    (*ntwrk)->input_nodes = atoi(argv[1]);
    (*ntwrk)->hidden_layer = atoi(argv[2]);
    (*ntwrk)->hidden_layer_nodes = atoi(argv[3]);
    (*ntwrk)->output_nodes = atoi(argv[4]);
    (*ntwrk)->layers = malloc(sizeof(node_s *) * (atoi(argv[2]) + 3));
    if (!(*ntwrk)->layers || node_per_layer(ntwrk))
    {
        //free
        return (-1);
    }
    if (layers_init(ntwrk))
        return (-1);
    return (0);
}