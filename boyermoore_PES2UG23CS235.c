#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Function to create the Bad Character Shift Table
int* bcst_create(const char* pattern, int pattern_len) 
{
    	int* bcst = (int*)malloc(26 * sizeof(int)); // since the input contains only small alphabet 
    	if (bcst == NULL) 
	{
        	perror("Memory allocation failed"); //doesnt allocate
        	exit(EXIT_FAILURE);
    	}
    	for (int i = 0; i < 26; i++) 
	{
        	bcst[i] = -1; // making all -1 
    	}
    	for (int i = 0; i < pattern_len; i++) {
        	if (pattern[i] >= 'a' && pattern[i] <= 'z')  
		{
            		bcst[pattern[i] - 'a'] = i; // latest position of each small letter 
        	}
    	}
    	return bcst;
}

// Function to create the Good Suffix Shift Table
int* gsst_create(const char* pattern, int pattern_len) 
{
    	int* gsst = (int*)malloc((pattern_len + 1) * sizeof(int)); 
    	if (gsst == NULL) 
	{
        	perror("Memory allocation failed"); //failure to allocate 
        	exit(EXIT_FAILURE);
    	}
    	int* suffix = (int*)malloc((pattern_len + 1) * sizeof(int));
    	if (suffix == NULL) 
	{
        	perror("Memory allocation failed");
        	exit(EXIT_FAILURE);
    	}

    	// Initialising the array
    	for (int i = 0; i <= pattern_len; i++) 
	{
        	gsst[i] = 0; 
    	}

    	// good suffix array  	
int i = pattern_len, j = pattern_len + 1;
    	suffix[i] = j;
    	while (i > 0) 
	{
        	while (j <= pattern_len && pattern[i - 1] != pattern[j - 1]) 
		{
            		if (gsst[j] == 0) 
			{
                		gsst[j] = j - i; 
            		}
            		j = suffix[j];
        	}
        	i--;
        	j--;
        	suffix[i] = j;
    	}
    	j = suffix[0];
    	for (i = 0; i <= pattern_len; i++) 
	{
        	if (gsst[i] == 0) 
		{
            		gsst[i] = j; //filling array
        	}
        	if (i == j) 
		{
            		j = suffix[j]; 
        	}
    	}
    	free(suffix);
    	return gsst;
}

// Boyer-Moore search function
int boyer_moore(const char* text, const char* pattern, int* bcst, int* gsst, FILE* output_file) 
{
    	int text_len = strlen(text);
    	int pattern_len = strlen(pattern);
    	int comparisons = 0; 
    	int pos = 0;

    	fprintf(output_file, "Occurrences:"); 
    	while (pos <= text_len - pattern_len) 
	{
        	int j = pattern_len - 1;
        	while (j >= 0 && pattern[j] == text[pos + j]) //as long as it equals each character 
		{
            		comparisons++; //counting 
            		j--;
        	}
        	comparisons++; //  when it is mismatched or it fully matched 

        	if (j < 0)  // Fully matched pattern 
		{
            		fprintf(output_file, "%d,", pos);
            		pos += gsst[0]; // good suffix shifting 
        	} 
		else 
		{
            		int bc_shift = pattern_len; // normal shift if not part of small alphabet 
            		char mismatch_char = text[pos + j];
            		if (mismatch_char >= 'a' && mismatch_char <= 'z') 
			{
                		bc_shift = j - bcst[mismatch_char - 'a'];
                		if (bc_shift < 1) 
				{
					bc_shift = 1; // shift should be a minimum of one
				}
            		}
            		int gs_shift = gsst[j + 1];
            		pos += (gs_shift > bc_shift) ? gs_shift : bc_shift; // the maximum of either shift will be used 
        	}
    	}
    	fprintf(output_file, "\n");
    	return comparisons;
}

void testcase(FILE* values_file, FILE* input_file, FILE* output_file) 
{
    	char text[2000];
    	char pattern[500];
    	fscanf(input_file, "%s", text);
    	fscanf(input_file, "%s", pattern);

    	int pattern_len = strlen(pattern);
    	int* bcst = bcst_create(pattern, pattern_len);
    	fprintf(output_file, "BCST:\n");
    	for (int i = 0; i < 26; i++) 
	{
        	fprintf(output_file, "%c:%d, ", (char)(i + 'a'), bcst[i]);
    	}
    	fprintf(output_file, "\n");

    	int* gsst = gsst_create(pattern, pattern_len);
    	fprintf(output_file, "GSST:\n");
    	for (int i = 1; i <= pattern_len; i++) 
	{
        	fprintf(output_file, "%d:%d, ", i, gsst[i]);
    	}
    	fprintf(output_file, "\n");

    	LARGE_INTEGER frequency, start, end;
    	QueryPerformanceFrequency(&frequency);
    	QueryPerformanceCounter(&start);

    	int comparisons = boyer_moore(text, pattern, bcst, gsst, output_file);
    	fprintf(output_file, "Comparisons:%d\n\n", comparisons);

    	QueryPerformanceCounter(&end);
    	long long elapsed_ns = (end.QuadPart - start.QuadPart) * 1000000000LL / frequency.QuadPart;

    	fprintf(values_file, "%d,%ld,%d,%lld\n", pattern_len, strlen(text), comparisons, elapsed_ns);

    	free(bcst);
    	free(gsst);
}

int main() 
{
    	FILE* input_file = fopen("input.txt", "r");
    	FILE* output_file = fopen("boyermoore_output_PES2UG23CS235.txt", "w");
    	FILE* values_file = fopen("boyermoore_values_PES2UG23CS235.txt", "w");

    	if (!input_file || !output_file || !values_file) 
	{
        	printf("Error opening file!\n");
        	return 1;
    	}
    	int testcases;
    	fscanf(input_file, "%d", &testcases);
    	int count = 0;
    	fprintf(values_file, "patternlen,textlen,cmp,timetaken\n");
    	while (count < testcases) 
	{
        	testcase(values_file, input_file, output_file);
        	count += 1;
    	}
    	fclose(input_file);
    	fclose(output_file);
    	fclose(values_file);
    	return 0;
}
