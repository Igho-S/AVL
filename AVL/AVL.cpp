#include <iostream>
#include <cstdlib>
using namespace std;
//Хаззан Oмотола

class Node{
    public:
    Node* left;
    Node* right;
    int key;
    int height;
    
    Node(int k = 0, Node* l = 0, Node* r = 0){
        key = k, 
        left = l, 
        right = r;
    }
    
    ~Node(){
        key = 0;
        left = 0;
        right = 0;
    }
};
int max(int a, int b);

int height(Node* N){
    if (N == 0)
    return 0;
    return N->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

Node* newNode(int key){
    Node* node = new Node();
    node->key = key;
    node->left = 0;
    node->right = 0;
    node->height = 1;
    return node;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

int getBalanceFactor(Node* N){
    if (N == 0) return 0;
    return height(N->left) - height(N->right);
}

Node* insertNode(Node* node, int key){
    if (node == 0) return (newNode(key));
    if (key < node->key) node->left = insertNode(node->left, key);
    else if (key > node->key) node->right = insertNode(node->right, key);
    else return node;

    node->height = max(height(node->left), height(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1){
        if (key < node->left->key){
            return rightRotate(node);
        } 
        else if (key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1){
        if (key > node->right->key){
            return leftRotate(node);
        } 
        else if (key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Node* nodeWithMimumValue(Node* node){
    Node* current = node;
    while (current->left != 0) current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key){
    if (root == 0) return root;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else{
        if ((root->left == 0) || (root->right == 0)){
            Node* temp = root->left ? root->left : root->right;
            if (temp == 0){
                temp = root;
                root = 0;
            } 
            else
            *root = *temp;
            delete temp;
        } 
        else{
            Node* temp = nodeWithMimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == 0) return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1){
        if (getBalanceFactor(root->left) >= 0){
            return rightRotate(root);
        } 
        else{
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1){
        if (getBalanceFactor(root->right) <= 0){
            return leftRotate(root);
        } 
        else{
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void printTree(Node* root, string indent, bool last){
    if (root != 0){
        cout << indent;
        if (last){
            cout << "R    ";
            indent += "    ";
        }
        else{
            cout << "L    ";
            indent += "    ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main(void){
    Node* root = 0;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 35);
    root = insertNode(root, 38);
    root = insertNode(root, 36);
    root = insertNode(root, 5);
    printTree(root, "", true);
    root = deleteNode(root, 5);
    cout << "After Deleting 5" << endl;
    printTree(root, "", true);
    root = insertNode(root, 4);
    printTree(root, "", true);
}

