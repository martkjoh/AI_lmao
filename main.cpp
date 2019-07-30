#include "header/Interface.h"

int main()
{
    srand (time(NULL));

    string name = "test";
    makeNN(name);
    trainNN(name);
    testNN(name);

    return 0;
}