#include "nn.h"

double  softplus(double x)
{
    return (log(1 + exp(x)));
}