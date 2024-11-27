#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;
    Node(int data) {
        value = data;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
public:
    Node* root;
    BinaryTree() {
        root = NULL;
    }

    void insert(Node*& root, int data) {
        if (!root) {
            root = new Node(data);
        } else if (data < root->value) {
            insert(root->left, data);
        } else {
            insert(root->right, data);
        }
    }

    void insert(int data) {
        insert(root, data);
    }

    void display(Node* root) {
        if (root == NULL) {
            return;
        }
        display(root->left);
        cout << root->value << " ";
        display(root->right);
    }

    void display() {
        display(root);
        cout << endl;
    }

    int Depth(Node* root) {
        if (!root) {
            return 0;
        }
        int leftDepth = Depth(root->left);
        int rightDepth = Depth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }

    int Depth() {
        return Depth(root);
    }

    void displayLeafNodes(Node* root) {
        if (root) {
            if (!root->left && !root->right) {
                cout << root->value << " ";
            }
            displayLeafNodes(root->left);
            displayLeafNodes(root->right);
        }
    }

    void displayLeafNodes() {
        displayLeafNodes(root);
        cout << endl;
    }

    Node* copyTree(Node* root) {
        if (!root) {
            return NULL;
        }
        Node* newNode = new Node(root->value);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }

    BinaryTree copy() {
        BinaryTree newTree;
        newTree.root = copyTree(root);
        return newTree;
    }

    void displayCopiedTree(BinaryTree& copiedTree) {
        copiedTree.display();
    }

    Node* deleteNode(Node* root, int data) {
        if (root == NULL) {
            return root;
        }

        if (data < root->value) {
            root->left = deleteNode(root->left, data);
        } else if (data > root->value) {
            root->right = deleteNode(root->right, data);
        } else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void deleteNode(int data) {
        root = deleteNode(root, data);
    }

    bool search(Node* root, int data) {
        if (root == NULL) {
            return false;
        }
        if (root->value == data) {
            return true;
        }
        if (data < root->value) {
            return search(root->left, data);
        }
        return search(root->right, data);
    }

    bool search(int data) {
        return search(root, data);
    }

    bool bfsSearch(int data) {
        if (root == NULL) {
            return false;
        }

        const int MAX_NODES = 100;
        Node* queue[MAX_NODES];
        int front = 0, rear = 0;

        queue[rear++] = root;

        while (front < rear) {
            Node* current = queue[front++];

            if (current->value == data) {
                return true;
            }

            if (current->left) {
                queue[rear++] = current->left;
            }
            if (current->right) {
                queue[rear++] = current->right;
            }
        }

        return false;
    }

};

int main() {
    BinaryTree tree;

    int option = 0;
    int insertNumber = 0;
    int searchNumber = 0;
    int deleteNumber = 0;
    do {
        cout << "What would you like to do:" << endl;
        cout << "1- Insert" << endl;
        cout << "2- Display" << endl;
        cout << "3- Find the depth" << endl;
        cout << "4- Display the leaf nodes" << endl;
        cout << "5- Copy and display the tree" << endl;
        cout << "6- Search for a value" << endl;
        cout << "7- Delete a value" << endl;
        cout << "8- BFS search for a value" << endl;
        cout << "9- Exit" << endl;
        cout << "Enter your chosen option: ";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Enter the number you want to insert: ";
            cin >> insertNumber;
            tree.insert(insertNumber);
            break;
        case 2:
            cout << "Below is your current tree:" << endl;
            tree.display();
            break;
        case 3:
            cout << "The depth of your current tree: " << tree.Depth() << endl;
            break;
        case 4:
            cout << "Below are the leaf nodes from your current tree:" << endl;
            tree.displayLeafNodes();
            break;
        case 5: {
            BinaryTree copiedTree = tree.copy();
            cout << "Below is the copied tree:" << endl;
            tree.displayCopiedTree(copiedTree);
            break;
        }
        case 6:
            cout << "Enter the number you want to search: ";
            cin >> searchNumber;
            if (tree.search(searchNumber)) {
                cout << "Found" << endl;
            } else {
                cout << "Not Found" << endl;
            }
            break;
        case 7:
            cout << "Enter the number you want to delete: ";
            cin >> deleteNumber;
            tree.deleteNode(deleteNumber);
            cout << "Value deleted from the tree." << endl;
            break;
        case 8:
            cout << "Enter the number you want to search using BFS: ";
            cin >> searchNumber;
            if (tree.bfsSearch(searchNumber)) {
                cout << "Found" << endl;
            } else {
                cout << "Not Found" << endl;
            }
            break;
        case 9:
            cout << "Bye" << endl;
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
        cout << endl;
    } while (option != 9);

    return 0;
}
