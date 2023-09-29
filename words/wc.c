#include <stdio.h>
#include <stdbool.h>
#include "word_count.h"

int main(int argc, char *argv[]) 
{
    FILE *input_file;
    WordCount *word_count_list;
    char word[256];

    // Check if a file name is provided as a command-line argument
    if (argc > 1) 
    {
        input_file = fopen(argv[1], "r");
        if (input_file == NULL) 
        {
            perror("Error opening file");
            return 1;
        }
    }

    // Initialize word count list
    init_words(&word_count_list);

    int char_count = 0;
    int word_count = 0;
    int line_count = 0;
    bool in_word = false;

    // Read characters from the input
    int c;
    while ((c = fgetc(input_file)) != EOF) 
    {
        char_count++;

        if (c == '\n') 
        {
            line_count++;
        }

        // Check for word boundaries (whitespace or punctuation)
        if (isspace(c) || ispunct(c)) 
        {
            if (in_word) 
            {
                word[word_count] = '\0';
                add_word(&word_count_list, word);
                word_count = 0;
                in_word = false;
            }
        } 
        else 
        {
            // Add the character to the current word
            if (word_count < sizeof(word) - 1) 
            {
                word[word_count++] = c;
                in_word = true;
            }
        }
    }

    // Print word count statistics
    printf("%d %d %d\n", line_count, word_count_list->count, char_count);

    // Clean up and close the file
    if (input_file != stdin) 
    {
        fclose(input_file);
    }

    return 0;
}