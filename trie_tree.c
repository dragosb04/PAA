#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 26

typedef struct Trie {
    int isEndOfWord;
    struct Trie* next[MAX_CHILDREN];
} Trie_t;

Trie_t* create_node() {
    Trie_t* node = (Trie_t*)malloc(sizeof(Trie_t));
    node->isEndOfWord = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->next[i] = NULL;
    }
    return node;
}

void insert_in_tree(Trie_t* node, const char* word) {
    if (node == NULL) {
        node = create_node();
    }

    Trie_t* curr = node;
    for (int i = 0; i < strlen(word); i++) {
        if (curr->next[word[i] - 'a'] == NULL) {
            curr->next[word[i] - 'a'] = create_node();
        }
        curr = curr->next[word[i] - 'a'];
    }
    curr->isEndOfWord = 1;
}

void print_words(Trie_t* node, char* word, int index) {
    if (node->isEndOfWord) {
        word[index] = '\0';
        printf("%s\n", word);
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->next[i] != NULL) {
            word[index] = i + 'a';
            print_words(node->next[i], word, index + 1);
        }
    }

}

void mean_wordlength(Trie_t* node, int index, int* result) {
    if (node->isEndOfWord) {
        *result += index;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (node->next[i] != NULL) {
            mean_wordlength(node->next[i], index + 1, result);
        }
    }
}

int find_word(Trie_t* node, const char* word) {
    Trie_t* curr = node;
    for (int i = 0; i < strlen(word); i++) {
        if (curr->next[word[i] - 'a'] == NULL) {
            return 0;
        }
        curr = curr->next[word[i] - 'a'];
    }

    return curr->isEndOfWord;
}

int main (int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buffer[60];
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    Trie_t* root = create_node();
    int num_words = 0;

    while (fgets(buffer, 60, file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insert_in_tree(root, buffer);
        num_words++;
    }

    // char word[60];
    // print_words(root, word, 0);
    // printf("%d\n", find_word(root, "ana"));
    // printf("%d\n", find_word(root, "andrei"));
    // printf("%d\n", find_word(root, "barca"));
    // printf("%d\n", find_word(root, "doi"));
    // printf("%d\n", find_word(root, "corn"));
    // printf("%d\n", find_word(root, "dus"));

    int result = 0;
    mean_wordlength(root, 0, &result);

    printf("%f\n", (float) result / num_words);

    return 0;
}
