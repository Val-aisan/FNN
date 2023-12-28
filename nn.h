# ifndef NN_H
#define NN_H
#define PI   3.14159f


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h> 


typedef struct  n_data{
    int     layer;
    double  *weights;
    double  bias;
    double  value;
    struct n_data  *prev_layer;
    struct n_data  *next;
}               node_s;

typedef struct nn_data{
    int     input_nodes;
    int     output_nodes;
    int     hidden_layer;
    int     hidden_layer_nodes;
    int     data_cycles;
    int     *nodes_per_layer;
    double  **inputs;
    double  *observed_outputs;
    node_s  **layers;
}           network_s;

typedef struct m_data{
    int     m;
    int     n;
    double  *x;
    double  *b;
    double  *z;
    double  *a;
    double  **w;
}           matrix_s;

typedef struct mm_data{
    matrix_s    *layer;
    double      ssr;
    double      psy;
}               network_mat_s;



double  normal_distr(void);
int     network_init(char **argv, network_s **new_network);
void    print_network_s(network_s *new_network);
int     layers_init(network_s **network);
void    add_node(node_s *new_node, node_s **head);
node_s  *new_node(int nodes_hiddenl);
double  softplus(double x);
node_s  *lst_build(int nodes_nbr, int hiddenl_nodes);
int     nodes_init(network_s **network);
int     data_init(char *file, network_s **new_network);
int     data_file_format(char *file, network_s **new_network);
int     compute_output(network_s **ntwrk);
void    update_inputl(network_s **network, double *inputs_set);





#endif 