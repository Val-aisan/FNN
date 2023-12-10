#include "nn.h"

int network_init(char **argv, network_s **ntwrk)
{   
    *ntwrk = malloc(sizeof(network_s));
    if (!ntwrk)
        return (-1);
    (*ntwrk)->input_nodes = atoi(argv[1]);
    (*ntwrk)->hidden_layer = atoi(argv[2]);
    (*ntwrk)->hidden_layer_nodes = atoi(argv[3]);
    (*ntwrk)->output_nodes = atoi(argv[4]);
    (*ntwrk)->layers = malloc(sizeof(node_s *) * (atoi(argv[2]) + 3));
    if (!(*ntwrk)->layers)
    {
        //free
        return (-1);
    }
    return (0);
}

int layers_init(network_s  **ntwrk)
{
    int i = 0;
    int layers = (*ntwrk)->hidden_layer + 2;

    while (i < layers)
    {
        //printf("i: %d, layers: %d\n", i,  layers);
        if (i == 0)
        {
            (*ntwrk)->layers[i] = lst_build((*ntwrk)->input_nodes);
        }
        else if (i + 1 == layers)
        {
            (*ntwrk)->layers[i] = lst_build((*ntwrk)->output_nodes);
        }
        else
        {
            (*ntwrk)->layers[i] = lst_build((*ntwrk)->hidden_layer_nodes);
        }
        if (!(*ntwrk)->layers[i])
            return (-1);
        i++;
        
    }
    (*ntwrk)->layers[i] = 0;
    return (0);

}

int data_init(char *file, network_s **new_network)
{
    FILE*   fp = fopen(file, "r");
    char    line[200];
    int     row = 0;
    char    *token;
    int     i = 0; 

    if (!fp)
    {
        perror("Can't open the file");
        return (-1);
    }
    while (fgets(line, 200, fp) != NULL)
    {
        if (row != 0)
        {
            i = 0;
            token  = strtok(line, ",");
            while (i < (*new_network)->input_nodes)
            {
                (*new_network)->inputs[row - 1][i] = (double)atoi(token);
                token = strtok(NULL, ",");
                i++;
            }
            (*new_network)->observed_outputs[row - 1] = (double)atoi(token);
        }
        row++;
    }
    fclose(fp);
    return (0);
}

int ntwrk_inputs_alloc(int rows, int columns, network_s **new_network)
{
    printf("rows: %d\n", rows);
    printf("columns: %d\n", columns);
    int i = 0;
    (*new_network)->data_cycles = rows - 1;
    (*new_network)->observed_outputs = malloc(sizeof(double) * rows - 1);
    if (!((*new_network)->observed_outputs))
    {
        perror("Bad alloc for observed outputs");
        return (-1);
    }
    (*new_network)->inputs = malloc(sizeof(double*) * rows);
    if (!((*new_network)->inputs))
    {
        perror("Bad alloc for inputs");
        return (-1);
    }
    while (i < (rows - 1))
    {
        (*new_network)->inputs[i] = malloc(sizeof(double) * columns - 1);
        if (!((*new_network)->inputs[i]))
        {
            perror("Bad alloc for inputs");
            return (-1);
        }
        i++;
    }
    (*new_network)->inputs[i] = 0;
    return (0);
}

int data_file_format(char *file, network_s **new_network)
{
    FILE*   fp = fopen(file, "r");
    char    line[200];
    int     rows = 0;
    int     columns = 0;
    char    *token;

    if (!fp)
    {
        perror("Can't open the file");
        return (-1);
    }
    printf("file: %s\n", file);
    while (fgets(line, 200, fp) != NULL)
    {
        rows++;
        if (rows == 1)
        {
            token  = strtok(line, ",");
            while (token != NULL)
            {
                columns++;
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(fp);
    if (ntwrk_inputs_alloc(rows, columns, new_network) == -1)
        return (-1);
    return (0);  
}

node_s  *lst_build(int nodes_nbr)
{
    node_s  *head = 0;
    node_s  *node;
    int i = 0;

    //printf("nodes_nbr: %d\n", nodes_nbr);
    while (i < nodes_nbr)
    {
        node = new_node();
        if (!node)
            return (NULL);
        add_node(node, &head);
        i++;
    }

    return (head);
}
