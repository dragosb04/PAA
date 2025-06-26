#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char name[20];
    char email[30];
    struct student *next;
} student_t;

typedef struct Node {
    int id;
    char titlu_curs[100];
    char nume_profesor[100];
    student_t *studenti;
    struct Node* right;
    struct Node* left;
} Node_t;

typedef Node_t* NodePtr_t;
typedef student_t* StudentPtr_t;

NodePtr_t create_node (int id, char* titlu, char* profesor) {
    NodePtr_t node = (NodePtr_t) malloc(sizeof(Node_t));
    node->id = id;
    strcpy(node->titlu_curs, titlu);
    strcpy(node->nume_profesor, profesor);
    node->right = NULL;
    node->left = NULL;
    node->studenti = NULL;
    return node;
}

void adauga_curs(NodePtr_t* head, int id, char* titlu, char* profesor) {
    if (*head == NULL) {
        *head = create_node(id, titlu, profesor);
        return;
    }

    NodePtr_t curr = *head;
    NodePtr_t parent = NULL;

    while (curr != NULL) {
        parent = curr;
        if (id < curr->id) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (id < parent->id) {
        parent->left = create_node(id, titlu, profesor);
    } else {
        parent->right = create_node(id, titlu, profesor);
    }
}

void print_by_id(NodePtr_t head) {
    if (head == NULL) {
        return;
    }

    print_by_id(head->left);
    printf("%d ", head->id);
    print_by_id(head->right);
}

int main(int argc, char* argv[]) {
    NodePtr_t root = NULL;  // Arborele începe empty

    // Exemplu de adăugare cursuri
    adauga_curs(&root, 5, "Programare", "Prof. Ionescu");
    adauga_curs(&root, 3, "Baze de date", "Prof. Popescu");
    adauga_curs(&root, 7, "Structuri de date", "Prof. Georgescu");
    adauga_curs(&root, 8, "Structuri de date", "Prof. Georgescu");
    adauga_curs(&root, 1, "Structuri de date", "Prof. Georgescu");
    adauga_curs(&root, 2, "Structuri de date", "Prof. Georgescu");
    adauga_curs(&root, 9, "Structuri de date", "Prof. Georgescu");

    print_by_id(root);

    return 0;
}
