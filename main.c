#include "nn.h"

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

//usage: ./programm "input nodes" "hidden layer" "node per hidden layer" "output nodes" "training file"
int main(int argc, char **argv)
{
    network_s   *new_network;
    int         cycle = 0;
    
    if (is_error(argc, argv))
        return (0);
    if (network_init(argv, &new_network))
        return (0);
    if (layers_init(&new_network))
        return (0);
    if (data_file_format(argv[5], &new_network))
        return (0);
    if (data_init(argv[5], &new_network))
        return (0);
    if (nodes_init(&new_network))
        return (0);
    if (layer_sum(&new_network))
        return (0);
    print_network_s(new_network);
    cycle++;
    //if (nodes_init(&new_network))
     //   return(0);

}   