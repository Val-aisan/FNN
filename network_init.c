#include "nn.h"

int network_init(char **argv, network_s *new_network)
{
    new_network = malloc(sizeof(network_s));
    if (!new_network)
        return (-1);
    new_network->input_nodes = atoi(argv[1]);
    new_network->hidden_layer = atoi(argv[2]);
    new_network->hidden_layer_nodes = atoi(argv[3]);
    new_network->output_nodes = atoi(argv[4]);
    new_network->layers = malloc(sizeof(node_s) * (atoi(argv[2]) + 3));
    if (!new_network->layers)
    {
        //free
        return (-1);
    }
    return (0);
}

/*int layers_init(network_s  *network)
{
    int i = 0;
    int layers = network->hidden_layer + 2;
    int error;

    while (i < layers)
    {
         network->layers[i]->next = 0;
        if (i == 0)
            error = lst_build(network->input_nodes, network->layers[i]);
        else if (i + 1 == layers)
            error = lst_build(network->output_nodes, network->layers[i]);
        else
            error = lst_build(network->hidden_layer_nodes, network->layers[i]);
        if (error)
            return (-1);
        i++;
        
    }
    network->layers[i] = 0;
    return (0);

}

int     lst_build(int nodes_nbr, node_s *layer_head)
{
    node_s  *node;
    node_s  **head = &layer_head;
    int i = 0;

    while (i < nodes_nbr)
    {
        node = new_node();
        if (!node)
            return (-1);
        add_node(node, head);
        i++;
    }

}

void    add_node(node_s *new_node, node_s **head)
{
    while ((*head)->next)
        *head = (*head)->next;
    (*head)->next = new_node;
}

node_s  *new_node(void)
{
    node_s  *new_node;

    new_node = malloc(sizeof(node_s));
    if (!new_node)
        return (NULL);
    new_node->next = 0;
    return(new_node);

}*/