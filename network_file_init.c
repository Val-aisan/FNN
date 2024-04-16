#include "nn.h"

//initialize file-related field of network structure 
static int data_init(char *file, network_s **new_network)
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
                (*new_network)->inputs[row - 1][i] = (double)atof(token);
                token = strtok(NULL, ",");
                i++;
            }
            (*new_network)->inputs[row - 1][i] = 0;
            i = 0;
            while (i < (*new_network)->output_nodes)
            {
                (*new_network)->observed_outputs[row - 1][i] = (double)atof(token);
                token = strtok(NULL, ",");
                i++;
            }
            (*new_network)->observed_outputs[row - 1][i] = 0;
        }
        row++;
    }
    fclose(fp);
    return (0);
}

//allocate the dynamic field of network structure for file_related data
static int ntwrk_inputs_alloc(int rows, network_s **new_network)
{
    int i = 0;
    int inputs = (*new_network)->input_nodes;
    int outputs = (*new_network)->output_nodes;

    (*new_network)->data_cycles = rows - 1;
    (*new_network)->observed_outputs = malloc(sizeof(double *) * (rows));
    if (!((*new_network)->observed_outputs))
    {
        perror("Bad alloc for observed outputs");
        return (-1);
    }
    while (i < (rows - 1))
    {
        (*new_network)->observed_outputs[i] = malloc(sizeof(double) * (outputs + 1));
        if (!((*new_network)->observed_outputs[i]))
        {
            perror("Bad alloc for inputs");
            return (-1);
        }
        i++;
    }
    (*new_network)->observed_outputs[i] = 0;
    (*new_network)->inputs = malloc(sizeof(double*) * (rows));
    if (!((*new_network)->inputs))
    {
        perror("Bad alloc for inputs");
        return (-1);
    }
    i = 0;
    while (i < (rows - 1))
    {
        (*new_network)->inputs[i] = malloc(sizeof(double) * (inputs + 1));
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

//check format of the file and give info for memory allocation 
static int data_file_format(char *file, network_s **new_network)
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
    if ((columns - (*new_network)->output_nodes) != (*new_network)->input_nodes)
    {
        printf("Error: Inputs nodes do not match training file data\n");
        return (-1);
    }
    fclose(fp);
    if (ntwrk_inputs_alloc(rows, new_network) == -1)
        return (-1);
    return (0);  
}

int file_data_init(network_s **network, char **argv)
{
    if (data_file_format(argv[5], network))
        return (-1);
    if (data_init(argv[5], network))
        return (-1);
    return (0);
}