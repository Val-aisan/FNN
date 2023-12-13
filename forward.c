
#include "nn.h"

double node_sum(node_s *node, int h_layer)
{
    double  sum = 0;
    node_s  *prev;
    prev = node->prev_layer;
    while (prev)
    {
        //printf("value: %f",node->value);
        sum += prev->value * prev->weights[h_layer];
        prev = prev->next;
    }
    //printf("sum : %f\n", sum);
    return(sum);

}


int layer_sum(network_s **ntwrk)
{
    int i = 1;
    int k = 0;
    node_s  *current;
    //printf("value: %f\n", (*ntwrk)->layers[0]->value);
    while((*ntwrk)->layers[i + 1])
    {
        current = (*ntwrk)->layers[i];
        k = 0;
        while(current)
        {
            current->value = node_sum(current, k++) + current->bias;
            current->value = softplus(current->value);
            current = current->next;
        }
        i++;
    }
    return (0);
}

