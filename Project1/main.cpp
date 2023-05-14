#include "classFreeFall.h"
int main()
{
    FreeFall* f = new FreeFall;
    f->run();
    delete f;
    return 0;
}