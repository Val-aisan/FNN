#ifndef NN_H
#define NN_H
#define PI   3.14159f


#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h> 

struct nn_data;
struct n_data;

typedef struct  n_data {
    int     layer;
    double  weight;
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
    double  **inputs;
    double  **observed_outputs;
    node_s  **layers;
}           network_s;


double  normal_distr(void);
int     network_init(char **argv, network_s *new_network);
int     layers_init(network_s *network);
void    add_node(node_s *new_node, node_s **head);
node_s  *new_node(void);
double  softplus(double x);
void    build_network(char **argv);
int     lst_build(int nodes_nbr, node_s *layer_head);
int     nodes_init(network_s *network);



#endif 