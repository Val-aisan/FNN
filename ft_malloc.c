#include "nn.h"

//free a network_s structure
void    free_netwrk(network_s **network)
{
    node_s  *node = (*network)->layers[0];
    node_s  *tmp_node;
    int     i = 0;

    if (node)
    {
        while ((*network)->layers[i])
        {
            node = (*network)->layers[i++];
            while (node)
            {
                tmp_node = node;
                free(node->weights);
                free(node->prev_layer);
                node = node->next;
                free(tmp_node);
            }
        }
        free((*network)->layers);
    }
    if ((*network)->nodes_per_layer)
        free((*network)->nodes_per_layer);
    if ((*network)->observed_outputs)
        free((*network)->observed_outputs);
    i = 0;
    if ((*network)->inputs[i])
    {
        while ((*network)->inputs[i])
            free((*network)->inputs[i++]);
        free((*network)->inputs);
    }
    free(*network);

}


//free an array of  matrix_s structure
void    free_mat_arr(matrix_s **array)
{
    int     i = 0;
    int     j = 0;
    double  **values;

    while (array[i])
    {
        if (!array[i]->val)
        {
            values = array[i]->val;
            while (values[j])
                free(values[j++]);
            free(values);
        }
        free(array[i]);
        i++;
    }

}
//free gradient structure
void    free_gradient(gradient_s **matrices)
{
    matrix_s    **layers;
    matrix_s    **psy;
    matrix_s    *old_psy;

    if(!(*matrices))
    {
        layers = (*matrices)->layers;
        psy = (*matrices)->psy;
        old_psy = (*matrices)->old_psy;
        if(!layers)
            free_mat_arr(layers);
        if (!psy)
            free_mat_arr(psy);
        if (!old_psy)
            free(old_psy);
        free(matrices);

    }
}

//todo 
/*void free_matrices(network_mat_s **matrices)
{
    matrix_s    **layer = (*matrices)->layer;
    int         i = 0;
    int         j = 0;

    while (layer[i])
    {
        j = 0;
        free(layer[i]->b);
        free(layer[i]->z);
        free(layer[i]->a);
        free(layer[i]->x);
        while(layer[i]->w[j])
            free(layer[i]->w[j++]);
        free(layer[i]->w);
        free(layer[i]);
        i++;

    }
    free((*matrices)->layer);
    free((*matrices));
}*/

void    *ft_malloc(size_t size, gradient_s **gradient)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        printf("MALLOC ERROR\n");
        free_gradient(gradient);
    }
    return (ptr);
}


