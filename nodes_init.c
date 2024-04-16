#include "nn.h"

static void    inputl_nodes(node_s **head)
{
    node_s  *current = *head;

    while (current)
    {
        current->layer = 0;
        current->value = 0;
        current->weights = 0;
        current->bias = 0;
        current->prev_layer = 0;
        current = current->next;
    }

}

static void    outputl_nodes(node_s **head, network_s *network)
{
    node_s  *current = *head;
    int     i = 0;
    int     hidden_layer = network->hidden_layer;

    while (current)
    {
        i = 0;
        current->layer = hidden_layer + 1;
        while (i < current->weights_nbr)
            current->weights[i++] = normal_distr();
        current->bias = 0;
        current->value = 0;
        current->prev_layer = network->layers[hidden_layer];
        current = current->next;
    }

}

static void    hiddenl_nodes(node_s **head, network_s *network, int layer)
{
    node_s  *current = *head;
    int     i = 0;

    while (current)
    {
        current->layer = layer;
        i = 0;
        while (i < current->weights_nbr)
            current->weights[i++] = normal_distr();
        current->bias = 0;
        current->value = 0;
        current->prev_layer = network->layers[layer - 1];
        current = current->next;
    }

}

//initialize input/hidden layer/output nodes
int nodes_init(network_s **network)
{
    int i = 0;

    srand(time(NULL));
    while ((*network)->layers[i])
    {
        if (i == 0)
            inputl_nodes(&((*network)->layers[i]));
        else if (!(*network)->layers[i + 1])
            outputl_nodes(&((*network)->layers[i]), *network);
        else
            hiddenl_nodes(&((*network)->layers[i]), *network, i);
        i++;

    }
    return (0);
}