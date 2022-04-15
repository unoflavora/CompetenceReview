#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define CHUNK 512 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("input one image!\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    BYTE *buffer = malloc(CHUNK);
    char *output = malloc(8 * sizeof(char));
    FILE *img = NULL;;
    int counter = 0;
    while (fread(buffer, sizeof(BYTE), CHUNK, file) > 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (counter == 0) 
            {
                sprintf(output, "%03i.jpg", counter);
                img = fopen(output, "w");
                fwrite(buffer, sizeof(BYTE), CHUNK, img);
                counter++;
            }
            else
            {
                fclose(img);
                sprintf(output, "%03i.jpg", counter);
                img = fopen(output, "w");
                fwrite(buffer, sizeof(BYTE), CHUNK, img);
                counter++;
            }
        }
        else
        {
            if (counter != 0)
            {
                fwrite(buffer, sizeof(BYTE), CHUNK, img);
            }
        }
    }
    free(buffer);
    free(output);
    free(img);
    free(file);
    fclose(img);
    return 0;
}
