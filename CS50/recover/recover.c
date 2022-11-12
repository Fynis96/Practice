#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Ensure argc is only = 2, name of program and the argument (file)
    if (argc != 2)
    {
        printf("Usage: :/recover filename.jpeg\n");
        return 1;
    }
    //Open up file given in argv[1]
    FILE *input = fopen(argv[1], "r");
    //If file can't open, return 1.
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    FILE *filePointer = NULL;
    char fileName[8];
    int i = 0;

    //For each iteration of this while loop, which is every time a blocksized piece of info goes into buffer, the block within runs
    while (fread(&buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        //Search for sequence of data indicating a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If not the first JPEG, close last file before beginning new iteration
            if (!(i == 0))
            {
                fclose(filePointer);
            }
            //Create filename, open new file with new filename, increase counter
            sprintf(fileName, "%03i.jpg", i);
            filePointer = fopen(fileName, "w");
            i++;
        }
        //if the first jpeg has been found, begin writing
        if (!(i == 0))
        {
            fwrite(&buffer, BLOCK_SIZE, 1, filePointer);
        }
    }


    //Close out files no longer being used.
    fclose(input);
    fclose(filePointer);
    return 0;
}