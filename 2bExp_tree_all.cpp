#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

class Node {
public:
    char value;
    Node* left;
    Node* right;
    Node(char data) {
        value = data;
        left = NULL;
        right = NULL;
    }
};

bool isOperator(char character) {
    return (character == '+' || character == '-' || character == '*' || character == '/');
}

bool isOperand(char character) {
    return (character >= '0' && character <= '9');
}

Node* ExpTree(char* array, int size) {
    Node* stack[50];
    int top = -1;

    for (int i = 0; i < size; i++) {
        if (isOperand(array[i])) {
            Node* operandNode = new Node(array[i]);
            stack[++top] = operandNode;
        } else if (isOperator(array[i])) {
            Node* operatorNode = new Node(array[i]);
            Node* rightOperand = stack[top--];
            Node* leftOperand = stack[top--];

            operatorNode->left = leftOperand;
            operatorNode->right = rightOperand;

            stack[++top] = operatorNode;
        }
    }
    return stack[top];
}

void inorderTraversal(Node* root) {
    stack<Node*> nodeStack;
    Node* current = root;

    while (current != NULL || !nodeStack.empty()) {
        while (current != NULL) {
            nodeStack.push(current);
            current = current->left;
        }

        current = nodeStack.top();
        nodeStack.pop();

        cout << current->value << " ";

        current = current->right;
    }
}

void preorderTraversal(Node* root) {
    if (root == NULL) return;

    stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node* current = nodeStack.top();
        nodeStack.pop();

        cout << current->value << " ";

        if (current->right != NULL) nodeStack.push(current->right);
        if (current->left != NULL) nodeStack.push(current->left);
    }
}

void postorderTraversal(Node* root) {
    if (root == NULL) return;

    stack<Node*> nodeStack1, nodeStack2;
    nodeStack1.push(root);

    while (!nodeStack1.empty()) {
        Node* current = nodeStack1.top();
        nodeStack1.pop();
        nodeStack2.push(current);

        if (current->left != NULL) nodeStack1.push(current->left);
        if (current->right != NULL) nodeStack1.push(current->right);
    }

    while (!nodeStack2.empty()) {
        Node* current = nodeStack2.top();
        nodeStack2.pop();
        cout << current->value << " ";
    }
}

int main() {
    int size = 0;
    char expression[50];
    bool isValid = true;

    cout << "Enter the number of elements in your expression: ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        cout << "Enter the element no. " << i + 1 << ": ";
        cin >> expression[i];
        if (!isOperand(expression[i]) && !isOperator(expression[i])) {
            isValid = false;
        }
    }

    if (isValid) {
        Node* root = ExpTree(expression, size);

        cout << "In-order Traversal: ";
        inorderTraversal(root);
        cout << endl;

        cout << "Pre-order Traversal: ";
        preorderTraversal(root);
        cout << endl;

        cout << "Post-order Traversal: ";
        postorderTraversal(root);
        cout << endl;
    } else {
        cout << "Invalid expression!" << endl;
    }

    return 0;
}
