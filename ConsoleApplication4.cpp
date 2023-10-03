#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
int count_occurrences(struct Node* root, int value);

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    int c = -1;
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data)root->left = r;
        else root->right = r;
        return r;
    }
    if (data == r->data) {
        printf("Значение %d уже есть в дереве\n", data);
        printf("1 - всё равно добавить, 2 - продолжить : ");
        scanf("%d", &c);
        if (c == 1)
            ;
        else
            return NULL;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}
int count_occurrences(struct Node* root, int value) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;
    if (root->data == value) {
        count++;
    }

    count += count_occurrences(root->left, value);
    count += count_occurrences(root->right, value);

    return count;
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

int main() {
    setlocale(LC_ALL, "RUS");
    int D, start = 1;

    struct Node* root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, root, D);
        }
    }

    print_tree(root, 0);

    printf("Введите значение для поиска: ");
    scanf("%d", &D);
    int occurrences = count_occurrences(root, D);
    printf("Число вхождений элемента %d в дерево: %d\n", D, occurrences);
    return 0;
}
