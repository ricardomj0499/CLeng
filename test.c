#include <stdio.h>
#include <string.h>

int main()
{
   char fuck[150] = "hola";

    if(strcmp(fuck, "hola")==0)
    {
        printf("\nYou entered the same string two times %s\n",fuck);
    }

    else
    {
        printf("\nEntered strings are not same! %s\n", fuck);
    }

	return 0;
}

