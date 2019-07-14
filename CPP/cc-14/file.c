#include <stdlib.h>
#include <stdio.h>




void TestToCFunc(const char*);

void TestCFunc(const char* name)
{
    char str[200];
    memset(str, 0, 200);
    printf("Hello from C, %s\nEnter you name: ", name);
    fflush(stdout);
    scanf("%50s", str);
    printf("\nEntered name: %s", str);
    TestToCFunc(str);
}