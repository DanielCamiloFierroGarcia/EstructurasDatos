#include<bits/stdc++.h>

using namespace std;

// Nodo del árbol AVL
struct nodo{

    int dato;
    nodo *izquierdo;
    nodo *derecho;
    int altura;
};

//Obtener el numero mayor
int max(int a, int b);

//Obtener la altura del arbol
int altura(nodo *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

//Numero mayor
int max(int a, int b)
{
    return (a > b)? a : b;
}

//Crear nodo
nodo* newNode(int key)
{
    //nodo * nodo = new nodo();

    nodo *nnodo=new nodo;

    nnodo->dato = key;
    nnodo->izquierdo = NULL;
    nnodo->derecho = NULL;
    nnodo->altura = 1;
    return(nnodo);
}

//Rotar a la derecha el subarbol
nodo *rightRotate(nodo *y)
{
    nodo *x = y->izquierdo;
    nodo *T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(altura(y->izquierdo),
                    altura(y->derecho)) + 1;
    x->altura = max(altura(x->izquierdo),
                    altura(x->derecho)) + 1;
    return x;
}

//Rotar a la izquierda el subarbol
nodo *leftRotate(nodo *x)
{
    nodo *y = x->derecho;
    nodo *T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(altura(x->izquierdo),
                    altura(x->derecho)) + 1;
    y->altura = max(altura(y->izquierdo),
                    altura(y->derecho)) + 1;

    return y;
}

// Factor de equilibrio
int getBalance(nodo *N)
{
    if (N == NULL)
        return 0;
    return altura(N->izquierdo) -
           altura(N->derecho);
}

//Insertar nodo
nodo* insert(nodo* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if (key < node->dato)
        node->izquierdo = insert(node->izquierdo, key);
    else if (key > node->dato)
        node->derecho = insert(node->derecho, key);
    else
        return node;

    node->altura = 1 + max(altura(node->izquierdo),
                           altura(node->derecho));

    int balance = getBalance(node);

    if (balance > 1 && key < node->izquierdo->dato)
        return rightRotate(node);

    if (balance < -1 && key > node->derecho->dato)
        return leftRotate(node);

    if (balance > 1 && key > node->izquierdo->dato)
    {
        node->izquierdo = leftRotate(node->izquierdo);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->derecho->dato)
    {
        node->derecho = rightRotate(node->derecho);
        return leftRotate(node);
    }

    return node;
}

//Recibe un arbol no lleno y retorna el nodo con el valor minimo encontrado en ese arbol
nodo * minValueNode(nodo* node)
{
    nodo* current = node;

    while (current->izquierdo != NULL)
        current = current->izquierdo;

    return current;
}

//Función recursiva para eliminar el nodo de un arbol, recibiendo el arbol y el valor a eliminar
nodo* deleteNode(nodo* root, int key)
{

    if (root == NULL)
        return root;

    if ( key < root->dato )
        root->izquierdo = deleteNode(root->izquierdo, key);

    else if( key > root->dato )
        root->derecho = deleteNode(root->derecho, key);

    else
    {
        if( (root->izquierdo == NULL) ||
                (root->derecho == NULL) )
        {
            nodo *temp = root->izquierdo ?
                         root->izquierdo :
                         root->derecho;

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
            nodo* temp = minValueNode(root->derecho);

            root->dato = temp->dato;

            root->derecho = deleteNode(root->derecho, temp->dato);
        }
    }

    if (root == NULL)
        return root;

    // Actualiza la altura del nodo
    root->altura = 1 + max(altura(root->izquierdo),
                           altura(root->derecho));

    int balance = getBalance(root);

    if (balance > 1 &&
            getBalance(root->izquierdo) >= 0)
        return rightRotate(root);

    if (balance > 1 &&
            getBalance(root->izquierdo) < 0)
    {
        root->izquierdo = leftRotate(root->izquierdo);
        return rightRotate(root);
    }

    if (balance < -1 &&
            getBalance(root->derecho) <= 0)
        return leftRotate(root);

    if (balance < -1 &&
            getBalance(root->derecho) > 0)
    {
        root->derecho = rightRotate(root->derecho);
        return leftRotate(root);
    }

    return root;
}


// Función principal
int main()
{
    nodo *root = NULL;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);




    root = deleteNode(root, 10);




    return 0;
}
