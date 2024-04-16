#include "nn.h"


static void field_alloc(network_mat_s *matrices, gradient_s **gradient, int index)
{
    matrix_s    **psy;
    matrix_s    **layers;
    int         i = 0;       

    layers = (*gradient)->layers;
    psy = (*gradient)->psy;
    layers[index] = ft_malloc(sizeof(matrix_s), gradient);
    psy[index] = ft_malloc(sizeof(matrix_s), gradient);
    layers[index]->row = matrices->layer[index]->n;
    layers[index]->col = (matrices->layer[index]->m) + 1;
    psy[index]->row =  matrices->layer[index]->n;
    if (matrices->layer[index + 1])
        psy[index]->col = matrices->layer[index + 1]->n;
    else
        psy[index]->col = 1;
    layers[index]->val = ft_malloc(sizeof(double *) * matrices->layer[index]->n, gradient);
    psy[index]->val = ft_malloc(sizeof(double *) * matrices->layer[index]->n, gradient);
    while (i < matrices->layer[index]->n)
        layers[index]->val[i++] = ft_malloc(sizeof(double) * (matrices->layer[index]->m + 1), gradient);
    i = 0;
    while (i < matrices->layer[index]->n)
    {
        if (matrices->layer[index + 1])
            psy[index]->val[i++] = ft_malloc(sizeof(double) *  matrices->layer[index + 1]->n, gradient);
        else
            psy[index]->val[i++] = ft_malloc(sizeof(double), gradient);
    }

}
//while (i < matrices->layer[index + 1]->n)
//      psy[index]->val[i++] = ft_malloc(sizeof(double) * m, gradient);
//printf("TONY\n");


static int grad_alloc(network_mat_s *matrices, gradient_s **gradient)
{
    int i = 0;

    (*gradient) = ft_malloc(sizeof(gradient_s), gradient);
    while (matrices->layer[i])
        i++;
    (*gradient)->layers = ft_malloc((sizeof(matrix_s *) * (i + 1)), gradient);
    (*gradient)->psy = ft_malloc((sizeof(matrix_s *) * (i + 1)), gradient);
    (*gradient)->old_psy = ft_malloc(sizeof(matrix_s), gradient);
    i = 0;
    while (matrices->layer[i])
    {
        field_alloc(matrices, gradient, i);
        i++;
    }
    (*gradient)->layers[i] = 0;
    (*gradient)->psy[i] = 0;
    (*gradient)->old_psy  = (*gradient)->psy[0];
    return (0);

}

//todo
static void init_psy(matrix_s **psy, int j, int len)
{
    int p = 0;

    while (p < len)
    {
        (*psy)->val[j][p] = 0;
        p++;
    }
}

static int grad_init(network_mat_s *matrices, gradient_s **gradient)
{
    int i = 0;
    int j = 0;
    int k = 0;
    matrix_s    **psy;
    matrix_s    **layers;  

    layers = (*gradient)->layers;
    psy = (*gradient)->psy;
    while (matrices->layer[i])
    {
        j = 0;
        while (j < matrices->layer[i]->n)
        {
            k = 0;
            while (k < matrices->layer[i]->m)
            {
                layers[i]->val[j][k] = matrices->layer[i]->x[k];
                k++;
            }
            layers[i]->val[j][k] = matrices->layer[i]->b[j];
            if (matrices->layer[i + 1])
                init_psy(&psy[i], j, matrices->layer[i + 1]->n);
            else
                init_psy(&psy[i], j, 1);
            j++;
        }
        i++;
    }
    return (0);

}

int pop_gradient(network_mat_s *matrices, gradient_s **gradient)
{
    if (grad_alloc(matrices, gradient))
        return (-1);
    if (grad_init(matrices, gradient))
        return (-1);
    return (0);
}