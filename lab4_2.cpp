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
struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
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
		if (root == NULL)
			return r;

		if (data > root->data)
			root->left = r;
		else if (data < root->data)
			root->right = r;
		else
		{
			free(r);
		}
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else if (data < r->data)
		CreateTree(r, r->right, data);

	return root;
}


void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf("  ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}


int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1;
	int element, k = 0;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	print_tree(root, 0);

	scanf_s("%d", &D);
	return 0;
}