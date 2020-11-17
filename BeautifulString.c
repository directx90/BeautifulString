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
            while (begin <= length - 6)
            {
                if (aabbcc(inputLine, begin, length, beautifulString))
                    save(outputLine, beautifulString, lineNum, &finded);
                begin += strlen(beautifulString);
            }

            begin = 0;
            while (begin <= length - 3)
            {
                if (abc(inputLine, begin, length, beautifulString))
                    save(outputLine, beautifulString, lineNum, &finded);
                begin += strlen(beautifulString);
            }

            begin = 0;
            while (begin <= length - 3)
            {
                if (bbb(inputLine, begin, length, beautifulString))
                    save(outputLine, beautifulString, lineNum, &finded);
                begin += strlen(beautifulString);
            }

            begin = 0;
            while (begin <= length - 6)
            {
                if (acacac(inputLine, begin, length, beautifulString))
                    save(outputLine, beautifulString, lineNum, &finded);
                begin += strlen(beautifulString);
            }
        }
        if (finded)
        {
            strcat(outputLine, "\n");
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
        if (index > 0 && c - beautifulString[index - 1] != 1)
            break;
        beautifulString[index++] = c;
    }
    beautifulString[index] = '\0';
    return index >= 3;
}

int aabbcc(char *input, int begin, int length, char *beautifulString)
{
    int index = 0;
    int preCount = 0;
    int curCount = 0;
    char finded = 0;
    for (int i = begin; i < length; i++)
    {
        char c = input[i];
        if (index == 0)
        {
            beautifulString[index++] = c;
            curCount++;
        }
        else if (index == 1)
        {
            int delta = c - beautifulString[index - 1];
            if (delta != 0)
                break;
            beautifulString[index++] = c;
            curCount++;
        }
        else
        {
            int delta = c - beautifulString[index - 1];
            if (delta == 0)
            {
                beautifulString[index++] = c;
                curCount++;
                if (0 < preCount && preCount < curCount)
                {
                    index--;
                    break;
                }
            }
            else if (delta == 1)
            {
                beautifulString[index++] = c;
                if (curCount < preCount)
                {
                    if (preCount + curCount == index - 1)
                    {
                        for (int j = curCount; j < index; j++)
                            beautifulString[j] = beautifulString[j + 1];
                        index -= preCount - curCount;
                    }
                    else
                    {
                        index -= curCount + 1;
                        if (index < preCount * 3)
                            index -= preCount;
                        break;
                    }
                }
                preCount = curCount;
                curCount = 1;
            }
            else
            {
                if (preCount && curCount != preCount)
                    index -= curCount;
                break;
            }
        }
    }
    beautifulString[index] = '\0';
    return preCount && index >= preCount * 3;
}

int bbb(char *input, int begin, int length, char *beautifulString)
{
    int index = 0;
    for (int i = begin; i < length; i++)
    {
        char c = input[i];
        if (index > 0 && c - beautifulString[index - 1] != 0)
            break;
        beautifulString[index++] = c;
    }
    beautifulString[index] = '\0';
    return index >= 3;
}

int acacac(char *input, int begin, int length, char *beautifulString)
{
    int index = 0;
    for (int i = begin; i < length; i++)
    {
        char c = input[i];
        if (index == 1)
        {
            if (c - beautifulString[0] == 0)
                break;
        }
        else if (index > 1)
        {
            if (c != beautifulString[index % 2])
            {
                if (index < 6 || !(index % 2))
                    index--;
                break;
            }
        }
        beautifulString[index++] = c;
    }
    beautifulString[index] = '\0';
    return index >= 6;
}

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