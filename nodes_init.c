#include "nn.h"

double  normal_distr(void)
{
    double      u1;
    double      u2;
    double      z;

    u1 = ((double)rand()/(double)(RAND_MAX));
    //printf("rand: %f\n", u1); 
    u2 = ((double)rand()/(double)(RAND_MAX));
    //printf("rand: %f\n", u2); 
    z = sqrt((-2) * log(u1)) * cos(2 * PI * u2);
    //printf("rand: %f\n", z); 
    return (z);

}

void    inputl_nodes(node_s **head, double *input, network_s *network)
{
    node_s  *current = *head;
    int i = 0;
    int j = 0;

    while (current)
    {
        current->layer = 0;
        j = 0;
        while (j < network->hidden_layer_nodes)
            current->weights[j++] = normal_distr();
        current->bias = 0;
        current->prev_layer = 0;
        current->value = input[i++];
        current = current->next;
    }

}

void    outputl_nodes(node_s **head, network_s *network)
{
    node_s  *current = *head;
    int hidden_layer = network->hidden_layer;

    while (current)
    {
        current->layer = hidden_layer + 1;
        current->weights = 0;
        current->bias = 0;
        current->value = 0;
        current->prev_layer = network->layers[hidden_layer];
        current = current->next;
    }

}

void    hiddenl_nodes(node_s **head, network_s *network, int layer)
{
    node_s  *current = *head;
    int     i = 0;

    while (current)
    {
        current->layer = layer;
        i = 0;
        while (i < network->hidden_layer_nodes)
            current->weights[i++] = normal_distr();
        current->bias = 0;
        current->value = 0;
        current->prev_layer = network->layers[layer - 1];
        current = current->next;
    }

}

//when iterating on linked list use double pointer othewise the pointer is moved 

int nodes_init(network_s **network, int cycle)
{
    int i = 0;

    while ((*network)->layers[i])
    {
        if (i == 0)
            inputl_nodes(&((*network)->layers[i]), (*network)->inputs[cycle], *network);
        else if (!(*network)->layers[i + 1])
            outputl_nodes(&((*network)->layers[i]), *network);
        else
            hiddenl_nodes(&((*network)->layers[i]), *network, i);
        i++;

    }
    return (0);
}