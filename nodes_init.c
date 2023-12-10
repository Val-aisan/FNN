#include "nn.h"

double  normal_distr(void)
{
    double   u1;
    double   u2;
    double   z;

    srand(time(0));
    u1 = ((float)rand()/(float)(RAND_MAX)); 
    u2 = ((float)rand()/(float)(RAND_MAX));
    z = sqrt((-2) * log(u1)) * cos(2 * PI * u2);
    return (z);

}

void    inputl_nodes(node_s **head, double *input)
{
    node_s  *current = *head;
    int i = 0;

    while (current)
    {
        current->layer = 0;
        current->weight = normal_distr();
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
        current->weight = 0;
        current->bias = 0;
        current->value = 0;
        current->prev_layer = network->layers[hidden_layer];
        current = current->next;
    }

}

void    hiddenl_nodes(node_s **head, network_s *network, int layer)
{
    node_s  *current = *head;

    while (current)
    {
        current->layer = layer;
        current->weight = normal_distr();
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
            inputl_nodes(&((*network)->layers[i]), (*network)->inputs[cycle]);
        else if (!(*network)->layers[i + 1])
            outputl_nodes(&((*network)->layers[i]), *network);
        else
            hiddenl_nodes(&((*network)->layers[i]), *network, i);
        i++;

    }
    return (0);
}