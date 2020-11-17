#include <stdio.h>
#include <string.h>

int main()
{
    char input[] = "input.txt";
    char output[] = "output.txt";
    FILE *inputFp;
    FILE *outputFp;
    if ((inputFp = fopen(input, "r")) == NULL)
    {
        printf("open input file error!");
        return -1;
    }
    if ((outputFp = fopen(output, "w")) == NULL)
    {
        fclose(inputFp);
        printf("open output file error!");
        return -1;
    }

    const int inputLength = 128;
    const int outputLength = 1024;
    char inputLine[inputLength];
    char beautifulString[inputLength];
    char outputLine[outputLength];
    memset(outputLine, 0, outputLength);
    int lineNum = 1;
    while (!feof(inputFp))
    {
        memset(inputLine, 0, inputLength);
        fgets(inputLine, inputLength, inputFp);
        int length = strlen(inputLine);
        char finded = 0;
        if (length > 0)
        {
            int begin = 0;
            while (begin + 3 <= length)
            {
                if (abc(inputLine, begin, length, beautifulString))
                    save(outputLine, beautifulString, lineNum, &finded);
                begin += strlen(beautifulString);
            }

            begin = 0;
            while (begin + 6 <= length)
            {
                if (aabbccdd(inputLine, begin, length, beautifulString))
                    save(outputLine, beautifulString, lineNum, &finded);
                begin += strlen(beautifulString);
            }

            begin = 0;
        }
        if (finded)
        {
            sprintf(outputLine, "%s", outputLine);
            printf("%s", outputLine);

            fputs(outputLine, outputFp);
            memset(outputLine, 0, outputLength);
        }
        lineNum++;
    }

    fclose(inputFp);
    fclose(outputFp);
    return 0;
}

int abc(char *input, int begin, int length, char *beautifulString)
{
    int index = 0;
    for (int i = begin; i < length; i++)
    {
        char c = input[i];
        if (index > 0)
        {
            if (c - beautifulString[index - 1] != 1)
                break;
        }
        beautifulString[index++] = c;
    }
    beautifulString[index] = '\0';
    return index >= 3 ? 1 : 0;
}

int aabbccdd(char *input, int begin, int length, char *beautifulString)
{
    int index, preCount curCount = 0;
    char finded = 1;
    for (int i = begin; i < length; i++)
    {
        char c = input[i];
        if (index == 0)
        {
            beautifulStrings[index++] = c;
             preCount++;
            curCount++;
        }
        else if (index == 1)
        {
            int delta = c - beautifulString[index - 1];
            if (delta != 0)
            {
                finded = 0
                break;
            }
             beautifulStrings[index++] =c;
             preCount++;
            curCount++;
        }
        else
        {
            if (index > 0)
            {
                int delta = c - beautifulString[index - 1];
                if (delta == 0)
                {
                }
                else if (delta == 1)
                {
                }
                else
                {
                    break;
                }
            }
        }
    }
    beautifulString[index] = '\0';
    return finded;
}
void bbbb() {}
void acacac() {}

void save(char *outputLine, char *beautifulString, int lineNum, char *finded)
{
    if (*finded)
    {
        strcat(outputLine, " ");
    }
    else
    {
        sprintf(outputLine, "Line%d:", lineNum);
        *finded = 1;
    }
    strcat(outputLine, beautifulString);
}