#include "nn.h"

double node_sum(node_s *node, int h_layer)
{
    double  sum = 0;
    node_s  *prev;

    while(node)
    {
        prev = node->prev_layer;
        while (prev)
        {
            //printf("value: %f",node->value);
            sum += prev->value * prev->weights[h_layer];
            prev = prev->next;
        }
        node = node->next;
    }
    printf("sum : %f\n", sum);
    return(sum);

}


int layer_sum(network_s **ntwrk)
{
    int i = 1;
    node_s  *current;
    printf("value: %f\n", (*ntwrk)->layers[0]->value);
    while((*ntwrk)->layers[i + 1])
    {
        current = (*ntwrk)->layers[i];
        while(current)
        {
            //printf("value: %f\n", current->value);
            //node_sum(&current, i - 1) + current->bias
           // current->value = node_sum(&current, i - 1) + current->bias;
            //current->value = softplus(current->value);
            current = current->next;
        }
        i++;
    }
    return (0);
}

