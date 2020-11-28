#include<bits/stdc++.h>

using namespace std;

// Nodo del árbol AVL
class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

//Obtener el numero mayor
int max(int a, int b);

//Obtener la altura del arbol
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

//Numero mayor
int max(int a, int b)
{
    return (a > b)? a : b;
}

//Crear nodo
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

//Rotar a la derecha el subarbol
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    return x;
}

//Rotar a la izquierda el subarbol
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

// Factor de equilibrio
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

//Insertar nodo
Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//Recibe un arbol no lleno y retorna el nodo con el valor minimo encontrado en ese arbol
Node * minValueNode(Node* node)
{
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

//Función recursiva para eliminar el nodo de un arbol, recibiendo el arbol y el valor a eliminar
Node* deleteNode(Node* root, int key)
{

    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    else
    {
        if( (root->left == NULL) ||
                (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Actualiza la altura del nodo
    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&
            getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 &&
            getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 &&
            getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 &&
            getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//Imprime en preorden
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Función principal
int main()
{
    Node *root = NULL;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);


    cout << "Arbol impreso luego de insertar\n";
    preOrder(root);

    root = deleteNode(root, 10);

    cout << "Arbol impreso luego de eliminar el 10\n";
    preOrder(root);

    return 0;
}

