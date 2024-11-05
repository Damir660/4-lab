#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root;
int nodeCount = 0; 


void invertTree(struct Node* r) {
    if (r == NULL) {
        return;
    }

    
    struct Node* temp = r->left;
    r->left = r->right;
    r->right = temp;

    
    invertTree(r->left);
    invertTree(r->right);
}

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
    if (nodeCount >= 20) { 
        printf("Дерево достигло максимального размера (20 элементов).\n");
        return root;
    }

    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        nodeCount++; 
        if (root == NULL)
            return r;

        if (data > root->data)
            root->left = r;
        else
            root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}


void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }

    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

int Find_data(struct Node* root, struct Node* r, int element, int k) {
    if (r != NULL) {
        if (element == r->data) {
            k++;
            Find_data(r, r->right, element, k);
        }
        else if (element > r->data) {
            Find_data(r, r->left, element, k);
        }
        else {
            Find_data(r, r->right, element, k);
        }
    }
    else {
        return k;
    }
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;
    int element, k = 0;

    root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, root, D);
        }
    }

    printf("Дерево до инверсии:\n");
    print_tree(root, 0);

    
    invertTree(root);
    printf("\nДерево после инверсии:\n");
    print_tree(root, 0);

    printf("Введите элемент, который хотите найти: \n");
    scanf("%d", &element);
    k = Find_data(root, root, element, k);
    printf("Нашли %d - %d раз\n", element, k);

    return 0;
}