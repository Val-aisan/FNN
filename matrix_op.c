#include "nn.h"

void    alloc_mat(matrix_s **new_matrix, int m, int n, gradient_s **gradient)
{
    int i = 0;
    *new_matrix = ft_malloc(sizeof(matrix_s), gradient);
    (*new_matrix)->col = m;
    (*new_matrix)->row = n;
    (*new_matrix)->val = ft_malloc(sizeof(double *) * n, gradient);
    while (i < n)
        (*new_matrix)->val[i++] = ft_malloc(sizeof(double) * m, gradient);
}



//if m2->col  != m1->row problem
matrix_s    *dot_product(matrix_s *m1, matrix_s *m2, gradient_s **gradient)
{
    int         m = 0;
    int         n = 0;
    int         sum = 0;
    int         i = 0;
    matrix_s    *new_matrix = 0;

    alloc_mat(&new_matrix, m1->col, m2->row, gradient);
    while (n < m2->row)
    {
        m = 0;
        while (m < m1->col)
        {
            sum = 0;
            i = 0;
            while (i < m1->row)
            {
                sum += m1->val[0][i] * m2->val[n][i];
                i++;
            }
            new_matrix->val[n][m] = sum;
            m++;
        }
        n++;
    }
    return (new_matrix);
}

matrix_s    *kron_prod(matrix_s *vector, matrix_s *matrix)
{
    int n = 0;
    int m = 0;

    while (n < vector->row)
    {
        m = 0;
        while (m < matrix->col)
        {
            matrix->val[n][m] *= vector->val[n][0];
            m++;
        }
        n++;
    }
    return (matrix);
}

void adjust_psy(network_s *ntwrk, gradient_s **gradient, network_mat_s *matrices)
{
    matrix_s    *psy;
    node_s      *out;
    int         i = 0;
    int         j = 0;
    int         k = 0;
    int         w = 0;
    int         x = 0;
    double      expected;
    double      output;

    psy = (*gradient)->psy[ntwrk->hidden_layer];
    out = ntwrk->layers[ntwrk->hidden_layer + 1];
    while (i < ntwrk->output_nodes)
    {
        printf("a\n");
        expected = ntwrk->observed_outputs[ntwrk->current_cycle][i];
        output = out->value;
        printf("expected: %f output: %f\n", expected, output);
        psy->val[i][0] = (-2 * (expected - output)) * (output * (1 - output));
        out = out->next;
        i++; 
    }
    i = ntwrk->hidden_layer - 1;
    while (i > -1)
    {
        j = 0;
        while (j < matrices->layer[i]->m)
        {
            k = 0;
            while (k < matrices->layer[i]->n)
            {
                x = matrices->layer[i]->x[j];
                w = matrices->layer[i]->w[j][k]; 
                (*gradient)->psy[i]->val[j][k] = w * (1 - x);
                k++;
            }
            j++;
            
        }
        //free psy
        (*gradient)->psy[i] = dot_product((*gradient)->psy[i + 1],(*gradient)->psy[i], gradient);
        i--;
    }
}

void update_weight(gradient_s *gradient, network_mat_s **matrices)
{
    int         i = 0;
    int         j = 0;
    int         k = 0;
    matrix_s    *update;

    while((*matrices)->layer[i])
    {
        update = kron_prod(gradient->psy[i], gradient->layers[i]);
        j = 0;
        while (j < (*matrices)->layer[i]->n)
        {
            k = 0;
            while (k < (*matrices)->layer[i]->m)
            {
                (*matrices)->layer[i]->w[j][k] += update->val[j][k];
                k++;
            }
            (*matrices)->layer[i]->b[j] += update->val[j][k];
            j++;
        }
        i++;
    }
}