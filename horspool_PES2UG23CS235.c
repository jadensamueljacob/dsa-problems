#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#include <windows.h>


// Fill in the TODO sections as required and DO NOT TOUCH any of the fprintf statements

void init_table(int* shift_table, int n) 
{
    for (int i = 0; i < 26; i++) // since the input only has small alphabet
    {
        shift_table[i] = n; //we make the initial table values to the pattern length 
    }
}

void preprocess(int* shift_table, char* pattern) //for bad character shift table
{
    int m = strlen(pattern);
    for (int i = 0; i < m - 1; i++)
    {
        if (pattern[i] >= 'a' && pattern[i] <= 'z') 
	{
            shift_table[pattern[i] - 'a'] = m - 1 - i; //we use the formula (length-1-index)
        }
    }
}

int string_match(int* shift_table, char* pattern, char* text, FILE* output_file) //checking for matches
{
    int matches = 0;
    int star_pos = 0;
    char star_char;
    int cmp = 0;
    int occurance = 0;
    
    int pattern_len = strlen(pattern);
    int text_len = strlen(text);

    fprintf(output_file,"Occurrences:");

    while (star_pos <= text_len - pattern_len) //end to start
    {
        matches = 0;
        int i = pattern_len - 1;
        int j = star_pos + i;

        while (i >= 0 && text[j] == pattern[i]) //if a character is matched
        {
            matches++;
            i--;
            j--;
            cmp++;
        }
	if (i >= 0) 
	{
    	cmp++; //for mismatch comparison
	}

        if (matches == pattern_len) //pattern found completely 
        {
            fprintf(output_file, "%d,", star_pos);
            occurance++;
        }
        char bad_char = text[star_pos + pattern_len - 1];
        star_pos += shift_table[bad_char - 'a'];      
    }

    if (occurance == 0) {
        fprintf(output_file, " None");
    }

    fprintf(output_file,"\n");
    fprintf(output_file,"Comparisons:%d\n\n", cmp);
    return cmp;
}

void print_table(int* shift_table, FILE* output_file)
{
    fprintf(output_file,"BCST:\n");
    for (int i = 0; i < 26; i++)
    {
        fprintf(output_file, "%c:%d", (char)(i + 'a'), shift_table[i]);
    }
    
}

void testcase(FILE* values_file, FILE* input_file, FILE* output_file)
{
    char text[2000];
    char pattern[100];
    fscanf(input_file, "%s", text);
    fscanf(input_file, "%s", pattern);

    int* shift_table = calloc(26, sizeof(int));
    init_table(shift_table, strlen(pattern));
    preprocess(shift_table, pattern);
    print_table(shift_table, output_file);

    // High-resolution timer
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    int cmp = string_match(shift_table, pattern, text, output_file);

    QueryPerformanceCounter(&end);

    long long elapsed_ns = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;

    fprintf(values_file, "%ld,%ld,%d,%lld\n", strlen(pattern), strlen(text), cmp, elapsed_ns);
    free(shift_table);
}

int main()
{	
	FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("horspool_output_PES2UG23CS235.txt", "w");
    FILE *values_file = fopen("horspool_values_PES2UG23CS235.txt", "w");

    if (!input_file || !output_file || !values_file) {
        printf("Error opening file!\n");
        return 1;
    }
    int testcases;
	fscanf(input_file,"%d",&testcases);
	int count = 0;
	fprintf(values_file, "patternlen,textlen,cmp,timetaken\n");
	while(count < testcases)
	{
		testcase(values_file, input_file, output_file);
		count += 1;
	}
	fclose(input_file);
	fclose(output_file);
	fclose(values_file);
	return 0;
}