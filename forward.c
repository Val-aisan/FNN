
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

int compute_output(network_s **ntwrk)
{
    int i = 1;
    int k = 0;
    node_s  *current;
    //printf("value: %f\n", (*ntwrk)->layers[0]->value);
    //printf("cycle; %d\n", (*ntwrk)->data_cycles);
    while((*ntwrk)->layers[i])
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
void    update_inputl(network_s **network, double *inputs_set)
{
    node_s *input_node = (*network)->layers[0];
    int     i = 0;

    while (input_node)
    {
        input_node->value = inputs_set[i];
        i++;
        input_node = input_node->next;
    }
}

double  compute_ssr(network_s **network)
{
    int     cycle = 0;
   //  node_s  *inputl = (*network)->layers[0];
    double  predicted_output;
    double  ssr = 0;

    while(cycle < (*network)->data_cycles)
    {
        update_inputl(network, (*network)->inputs[cycle]);+
        
        compute_output(network);
        predicted_output = (*network)->layers[(*network)->hidden_layer + 1]->value;
        ssr += pow(predicted_output - (*network)->observed_outputs[cycle], 2);
        cycle++;

    }
    return(ssr);


}