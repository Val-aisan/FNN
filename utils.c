#include "nn.h"

//normale distribution for weights initialization
double  normal_distr(void)
{
    double      u1;
    double      u2;
    double      z;

    u1 = ((double)rand()/(double)(RAND_MAX));
    //printf("rand: %f\n", u1); 
    u2 = ((double)rand()/(double)(RAND_MAX));
    //printf("rand: %f\n", u2); 
    z = sqrt((-2) * log(u1)) * cos(2 * PI * u2);
    //printf("rand: %f\n", z); 
    return (z);

}

//activation function
double  softplus(double x)
{
    return (log(1 + exp(x)));
}

//add node to structure
void    add_node(node_s *new_node, node_s **head)
{
    node_s  *current = *head;
    if (!(current))
    {
        *head = new_node;
        return ;
    }
    while (current->next)
        current = current->next;
    current->next = new_node;
}

//create new_node for structure
node_s  *new_node(int weights_nb)
{
    node_s  *new_node;

    new_node = malloc(sizeof(node_s));
    if (!new_node)
        return (NULL);
    new_node->weights = malloc(sizeof(double) * weights_nb );
    new_node->weights_nbr = weights_nb;
    if (!new_node->weights)
    {
        free(new_node);
        return (NULL);
    } 
    new_node->next = 0;
    return(new_node);

}

//small check on cmd line arguments provided by user
int is_error(int argc, char **argv)
{
    int i = 1;

    if (argc != 6)
    {
        printf("\nToo few or too many arguments provided\n");
        printf("usage : \"input nodes\" \"hidden layers\" \"node per hidden layer\" \"output nodes\" \"training file\" \n");
        return (-1);
    }
    while (i < 5)
    {
        if ((i == 1 || i == 4) && atoi(argv[i]) < 1)
        {
            printf("\nBad value  provided as argument \n");
            return (-1);
        }
        if (atoi(argv[i]) < 0)
        {
            printf("\nBad value  provided as argument \n");
            return (-1);
        }
        i++;
    }
    if (!fopen(argv[i], "r"))
    {
        printf("Error: access to training file\n");
        return (-1);
    }
    return (0);
}
