# ifndef NN_H
#define NN_H
#define PI   3.14159f


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h> 

//structure d'un node d'une couche d'un réseau
typedef struct  n_data{
    int     layer;
    int     weights_nbr;
    double  *weights;
    double  bias;
    double  value;
    struct n_data  *prev_layer;
    struct n_data  *next;
}               node_s;

//structure d'un réseau chaque couche est une  liste chainée de structures node_s
typedef struct nn_data{
    int     input_nodes;
    int     output_nodes;
    int     hidden_layer;
    int     hidden_layer_nodes;
    int     data_cycles;
    int     current_cycle;
    int     *nodes_per_layer;
    double  **inputs;
    double  **observed_outputs;
    node_s  **layers;
}           network_s;

//structure d'une matrix dimension/valeurs
typedef struct k_data{
    int     row;
    int     col;
    double  **val;
}           matrix_s;

typedef struct kk_data{
    matrix_s    **layers;
    matrix_s    **psy;
    matrix_s    *old_psy;
}               gradient_s;

//structure d'une couche du réseau, les paramètres sont des vecteurs ou matrices 
typedef struct m_data{
    int     m;
    int     n;
    double  *x;
    double  *b;
    double  *z;
    double  *a;
    double  **w;
}           layer_s;

//
typedef struct mm_data{
    layer_s    **layer;
    double      ssr;
    double      psy;
}               network_mat_s;



//utils
double  normal_distr(void);
double  softplus(double x);
void    add_node(node_s *new_node, node_s **head);
node_s  *new_node(int nodes_hiddenl);
int     is_error(int argc, char **argv);

//network_init
int     network_init(char **argv, network_s **new_network);

//nodes_init
int     nodes_init(network_s **network);

//network_file_init
int file_data_init(network_s **network, char **argv);

//compute_output
int     compute_output(network_s **ntwrk, double *inputs_set);

//ft_malloc
void    free_netwrk(network_s **network);

//matrix
network_mat_s   *matrix_init(network_s *network);

//print_structures
void    print_network_s(network_s *new_network);
void    print_layers(network_mat_s *matrices);
void    print_gradient(gradient_s *gradient);
void    print_input_output(network_s *new_network);

//grd_init
int pop_gradient(network_mat_s *matrices, gradient_s **gradient);

//malloc safely
void    *ft_malloc(size_t size, gradient_s **gradient);

//matrix_op
void    adjust_psy(network_s *ntwrk, gradient_s **gradient, network_mat_s *matrices);
void    update_weight(gradient_s *gradient, network_mat_s **matrices);

#endif