#include "nn.h"

double  softplus(double x)
{
    return (log(1 + exp(x)));
}

void    print_network_s(network_s *new_network)
{
    int i = 0;
    int j = 0;
    printf("\n");
    printf("ntwrk input: %d\n",new_network->input_nodes);
    printf("ntwrk output: %d\n",new_network->output_nodes);
    printf("ntwrk hidden_layers: %d\n",new_network->hidden_layer);
    printf("ntwrk nodes hidden layer: %d\n",new_network->hidden_layer_nodes);
    printf("\n");
    printf("\n");
    while (new_network->layers[i])
    {
        printf("ntwrk_layer%d\n",i);
        node_s *ptr = new_network->layers[i];
        while (ptr)
        {
            printf("node, ");
            printf("layer: %d, ", ptr->layer);
            printf("bias: %f, ", ptr->bias);
            printf("value: %f", ptr->value);
            j = 0;
            while (j < new_network->hidden_layer_nodes)
            {
                printf("weight%d: %f, ", j, ptr->weights[j]);
                j++;
            }
            if  (i == 3)
                printf("hey\n");
            printf("value: %f\n", ptr->value);

            ptr = ptr->next;
        }
        printf("\n");
        i++;
    }
    i = 0;
    while (new_network->inputs[i] != 0)
    {
        j = 0;
        while (j < new_network->input_nodes)
        {
            printf("input%d: %f\n", i, new_network->inputs[i][j]);
            j++;
        }
        i++;
    }
    i = 0;
    while (i < new_network->data_cycles)
    {
         printf("output%d: %f\n", i, new_network->observed_outputs[i]);
         i++;
    }

}

void    add_node(node_s *new_node, node_s **head)
{
    node_s  *current = *head;
    if (!(current))
    {
        *head = new_node;
        return ;
    }
    while (current->next)
        current = current->next;
    current->next = new_node;
}

node_s  *new_node(int nodes_hiddenl)
{
    node_s  *new_node;

    new_node = malloc(sizeof(node_s));
    if (!new_node)
        return (NULL);
    new_node->weights = malloc(sizeof(double) * nodes_hiddenl);
    if (!new_node->weights)
    {
        free(new_node);
        return (NULL);
    } 
    new_node->next = 0;
    return(new_node);

}