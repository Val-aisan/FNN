
#include "nn.h"

//find node value of layer i, multiplying all the nodes of prev layer times their weight
static double node_sum(node_s *node)
{
    double  sum = 0;
    int     i = 0;
    node_s  *prev;
    prev = node->prev_layer;
    while (prev)
    {
        printf("value: %f \n", prev->value);
        printf("weights: %f\n", node->weights[i]);
        //printf("value: %f",node->value);
        sum += prev->value * node->weights[i++];
        prev = prev->next;
    }
    printf("sum : %f\n", sum);
    return(sum);

}

//update the input values of the network given a set from training sets
static void    update_inputl(network_s **network, double *inputs_set)
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

//compute output value of network given an input set
int compute_output(network_s **ntwrk, double *inputs_set)
{
    int i = 1;
    int k = 0;
    node_s  *current;

    update_inputl(ntwrk, inputs_set);
    while((*ntwrk)->layers[i])
    {
        current = (*ntwrk)->layers[i];
        k = 0;
        while(current)
        {
            current->value = node_sum(current) + current->bias;
            printf("layer: %d value: %f bias %f\n", i, current->value, current->bias);
            current->value = softplus(current->value);
            printf("after a: %f\n", current->value);
            current = current->next;
            k++;
        }
        i++;
    }
    return (0);
}

/*double  compute_ssr(network_s **network)
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


}*/