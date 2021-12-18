#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int i = 0;
    int count = 0;
    bool state = true;

    for (i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] == ' ' || argv[1][i] == '\t' || argv[1][i] == '\n')
        {
            state = true;
        }

        else if (state == true)
        {
            state = false;
            count += 1;
        }
    }

    if (argc > 1)
    {
        printf("String Contains %d Words!", count);
    }

    else
    {
        printf("String Is Empty!");
    }
}