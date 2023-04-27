#include "iostream"
#include "stdio.h"
#include "string"
int main(int argc, char const *argv[])
{
    char wkwk[12];
    // strcpy(wkwk, "#123")
    sprintf(wkwk, "+123");
    std::cout << atoi(wkwk) << std::endl;
    return 0;
}
