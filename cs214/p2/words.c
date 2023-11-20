#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>

typedef struct WordCount {
    char* word;
    int count;
} WordCount;

WordCount* word_counts; 
int word_counts_size; // number of unique words

#define BUFF_SIZE 1024

void readfile(char *filename) {
    // count the number of words and store them in word_counts
    char buf[BUFF_SIZE];
    int fd = open(filename, O_RDONLY);
    //printf("opened %s\n", filename);
    if (fd == -1) {
        perror(filename);
        return;
    }


//luke worked on this
    ssize_t bytes_read;
    char word_buffer[BUFF_SIZE];
    int word_length = 0;
    WordCount* new_word_counts;

    // read the file content in chunks
    // this loop also replaces read(fd, buf, BUFF_SIZE); because we do not know the set file size and it could potentially be larger than BUFF_SIZE
    while ((bytes_read = read(fd, buf, BUFF_SIZE)) > 0) {

        for (int i = 0; i < bytes_read; ++i) {

            if (isalpha(buf[i]) ||  
            (buf[i] == '\'' && word_length >= 0 && i + 1 < bytes_read && (isalpha(buf[i + 1]) || buf[i + 1] == '\'')) ||
            (buf[i] == '-' && word_length > 0 && i + 1 < bytes_read && isalpha(buf[i + 1]))) {
                word_buffer[word_length++] = buf[i];
            } else if (word_length > 0) {
                word_buffer[word_length] = '\0'; // Null-terminate the word

                //check if the word is already in the list
                int check = 0;
                for (int j = 0; j < word_counts_size; ++j) {

                    if (strcmp(word_counts[j].word, word_buffer) == 0) {
                        //word found, increment the count
                        word_counts[j].count++;
                        check = 1;
                        break;
                    }
                }

                if (!check) {
                    //new word, need to reallocate the word_counts array
                    new_word_counts = realloc(word_counts, (word_counts_size + 1) * sizeof(WordCount));

                    if (!new_word_counts) {
                        perror(filename);
                        free(word_counts);
                        close(fd);
                        return;
                    }
                    //add
                    word_counts = new_word_counts;
                    word_counts[word_counts_size].word = strdup(word_buffer);
                    word_counts[word_counts_size].count = 1;
                    word_counts_size++;
                }

                word_length = 0; //reset for next word
            }
        }
    }

    //check for the last word in the buffer if it doesn't end with a delimiter
    if (word_length > 0) {
        word_buffer[word_length] = '\0';
        //check if the word is already in the list
                int check = 0;
                for (int j = 0; j < word_counts_size; ++j) {

                    if (strcmp(word_counts[j].word, word_buffer) == 0) {
                        //word found, increment the count
                        word_counts[j].count++;
                        check = 1;
                        break;
                    }
                }

                if (!check) {
                    //new word, need to reallocate the word_counts array
                    new_word_counts = realloc(word_counts, (word_counts_size + 1) * sizeof(WordCount));

                    if (!new_word_counts) {
                        perror(filename);
                        free(word_counts);
                        close(fd);
                        return;
                    }
                    //add
                    word_counts = new_word_counts;
                    word_counts[word_counts_size].word = strdup(word_buffer);
                    word_counts[word_counts_size].count = 1;
                    word_counts_size++;
                }
    }

    if (bytes_read == -1) {
        perror(filename);
    }

    close(fd);
}

void readdirectory(char *dirname) {
    // if there's a folder inside a folder
    // directory() again
    
    DIR *dir_info;
    struct dirent *dir_entry;
    struct stat buf;
    char path[1024];

    dir_info = opendir(dirname);

    //printf("opendir\n");

    if (dir_info != NULL) {
        while ((dir_entry = readdir(dir_info)) != NULL){
            if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0) {
                continue;
            } else {
                strcpy(path, dirname);
                strcat(path, "/");
                strcat(path, dir_entry->d_name);

                if (stat(path, &buf) == -1) {
                    perror(path);
                    continue;
                }

                if (S_ISDIR(buf.st_mode)) {
                    //printf("[dir] %s\n", dir_entry->d_name);
                    readdirectory(path);
                } else if ( S_ISREG(buf.st_mode)) {
                    //printf("[file] %s\n", dir_entry->d_name);
                    readfile(path);
                }
            }
        }
        closedir(dir_info);
    } else {
        perror(dirname);
    }

}


int compare(const void* a, const void* b) {
    // compare algorithm for qsort
    WordCount *wordA = (WordCount *)a;
    WordCount *wordB = (WordCount *)b;

    if (wordA->count != wordB->count) {
        return wordB->count - wordA->count;
    } else {
        return strcmp(wordA->word, wordB->word);
    }
}

void words(int argc, char* argv[]) {
    word_counts = (WordCount*)malloc(0);

    // checking if input is file or directory
    struct stat file_stat;
    if (stat(argv[1], &file_stat) == 0) {
        if (S_ISREG(file_stat.st_mode)) {
            // file
            readfile(argv[1]);
        } else if (S_ISDIR(file_stat.st_mode)) {
            // directory
            readdirectory(argv[1]);
        } else {
            // invalid
            perror(argv[1]);
            return;
        }
    } else {
        perror(argv[1]);
        // invalid
        return;
    }

    // sorting from greatest frequency to smallest frequency
    qsort(word_counts, word_counts_size, sizeof(WordCount), compare);

    // printing one by one
    for (int i = 0; i < word_counts_size; i++) {
        printf("%s %d\n", word_counts[i].word, word_counts[i].count);
    }

    free(word_counts);    
}


int main(int argc, char* argv[]) {

    // only one argument
    if (argc != 2) {
        printf("wrong number of arguments\n");
        return 1;
    }

    words(argc, argv);

    return 0;
}