#include "nn.h"

void    print_input_output(network_s *new_network)
{
    int j = 0;
    int k = 0;

    while (k < new_network->data_cycles)
    {
        printf("Cycle %d: ", k);
        printf("Inputs: ");
        j = 0;
        while(new_network->inputs[k][j])
            printf("%f, ", new_network->inputs[k][j++]);
        printf("        ");
        printf("Outputs: ");
        j = 0;
        while(new_network->observed_outputs[k][j])
            printf("%f, ", new_network->observed_outputs[k][j++]);
        k++;
        printf("\n");
    }

}

//print network explicitly
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
            j = 0;
            while (j < ptr->weights_nbr)
            {
                printf("weight%d: %f, ", j, ptr->weights[j]);
                j++;
            }
            printf("value: %f\n", ptr->value);

            ptr = ptr->next;
        }
        printf("\n");
        i++;
    }

}

static void print_val(double *array, int size)
{
    int i = 0;

    printf("[");
    while (i < size)
    {
        printf("%f, ", array[i]);
        i++;
    }
    printf("]\n");
}

//print network like matrices layers-1
void    print_layers(network_mat_s *matrices)
{
    layer_s **layer = matrices->layer;
    int     i = 0;
    int     j = 0;
    int     k = 0;

    while (layer[i])
    {
        j = 0;
        printf("Layer: %d\n\n", i);
        printf("x: ");
        print_val(layer[i]->x, layer[i]->m);
        printf("z: ");
        print_val(layer[i]->z, layer[i]->n);
        printf("a: ");
        print_val(layer[i]->a, layer[i]->n);
        printf("b: ");
        print_val(layer[i]->b, layer[i]->n);
        printf("w: ");
        printf("[");
        j = 0;
        while(j < layer[i]->n)
        {
            k = 0;
            while (k < layer[i]->m)
            {
                printf("%f, ", layer[i]->w[j][k]);
                k++;
            }
            printf("\n");
            j++;
        }
        printf("]\n\n");
        i++;
    }
}

void    print_gradient(gradient_s *gradient)
{
    int i = 0;
    int k = 0;
    int j = 0;

    while (gradient->layers[i])
    {
        printf(" X_%d: [ ", i);
        j = 0;
        while (j < gradient->layers[i]->row)
        {
            k = 0;
            while (k < gradient->layers[i]->col)
            {
                printf("%f, ", gradient->layers[i]->val[j][k]);
                k++;
            }
            printf("\n");
            j++;
        }
        printf("]\n\n");
        i++;
    }
    i = 0;
    while (gradient->psy[i])
    {
        printf(" PSY_%d: [ ", i);
        j = 0;
        while (j < gradient->psy[i]->row)
        {
            k = 0;
            while (k < gradient->psy[i]->col)
            {
                printf("%f, ", gradient->psy[i]->val[j][k]);
                k++;
            }
            printf("\n");
            j++;
        }
        printf("]\n\n");
        i++;
    }
}