// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Create an array of unsigned 8 bit integers representing a byte, make it of const HEADER_SIZE as a header is always that size
    uint8_t header[HEADER_SIZE];
    //Call fread and fwrite, which will loop through on its own using the 2nd argument of size, looping only by 1, reading from input to header, and writing from header to output
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
    // Create a 16bit signed int representing 2 bytes
    int16_t buffer;
    // While the fread function is active (which it will start from where it left off in the file, and end when its at the end of a file), read into buffer, factor it, and write it to output
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
