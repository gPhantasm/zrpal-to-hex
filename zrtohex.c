#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(char argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: no .zrpal provided \nUsage: %s <zrpal file>\n", argv[0]);
        return 1;
    }

    FILE *zrpal, *output;
    char line[256]; // line buffer
    int value;
    zrpal = fopen(argv[1], "r");

    // check if zrpal is null
    if (zrpal == NULL)
    {
        printf("Error: zrpal is null\n");
        return 1;
    }

    char output_name[256];

    // dynamically name output based on zrpal input file
    snprintf(output_name, sizeof(output_name), "%s_hex.txt", argv[1]);

    output = fopen(output_name, "w");

    while (fgets(line, sizeof(line), zrpal))
    {
        // check if there's a decimal value after colarray
        if (sscanf(line, "colarray[%*d] = %d", &value) == 1)
        {
            // write the hex code to the output
            fprintf(output, "%X\n", value);
        }
    }

    fclose(zrpal);
    fclose(output);

    printf("Wrote hex codes to %s\n", output_name);
}
