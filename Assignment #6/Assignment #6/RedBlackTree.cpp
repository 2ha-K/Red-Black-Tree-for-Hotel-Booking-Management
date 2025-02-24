//************************************************************************
// ASU CSE310 Assignment #6 Fall 2024
// Author: PO-YI, LIN
// ASU ID: 1228434521
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
//----

#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
    //----
    root = nullptr; //initial root become nullptr
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
    //----
    int nodeSize = deleteNode(root);//delete all nodes
    cout << "The number of deleted nodes is: " << nodeSize << endl;
}

//Read the assignment description carefully and finish all functions definition here
//highly recommend that you follow the order defined in RedBlackTree.h
//----
// Get Root
Node* RedBlackTree::getRoot()
{
    return root;//get root
}
//----
//recursive function to delete nodes
int RedBlackTree::deleteNode(Node* node)
{
    if (node == nullptr) return 0;
    int leftCount = deleteNode(node->leftChild);
    int rightCount = deleteNode(node->rightChild);
    delete node;
    return 1 + leftCount + rightCount;
}
//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
//Note: duplicated node should not be added inside
void RedBlackTree::insertNode(Node* node)
{
    //----
    //----
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr)
    {
        parent = current;
        if (node->confirmNum < current->confirmNum)
            current = current->leftChild;
        else if (node->confirmNum > current->confirmNum)
            current = current->rightChild;
        else //duplicated node. Not added
        {
            cout << "Duplicated node. NOT added" << endl;
            return;
        }
    }
    //connect parent with newNode
    node->parent = parent;
    if (parent == nullptr)
    {
        root = node;
    }
    else if (node->confirmNum < parent->confirmNum)
    {
        parent->leftChild = node;
    }
    else
    {
        parent->rightChild = node;
    }
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    fixUp(node);//fix up RBT to correct format
    
}

// Fix up the red-black tree after insertion
void RedBlackTree::fixUp(Node* node)
{
    while (node != root && node->parent->color == "RED")
    {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        // Case when the parent is the left child of the grandparent
        if (parent == grandparent->leftChild)
        {
            Node* uncle = grandparent->rightChild;

            if (uncle != nullptr && uncle->color == "RED") // Case 1: Uncle is red
            {
                parent->color = "BLACK";
                uncle->color = "BLACK";
                grandparent->color = "RED";
                node = grandparent;
            }
            else
            {
                if (node == parent->rightChild) // Case 2: Node is right child
                {
                    node = parent;
                    leftRotate(node);//leftrotate
                }
                // Case 3: Node is left child
                node->parent->color = "BLACK";
                node->parent->parent->color = "RED";
                rightRotate(node->parent->parent);//rightrotate
            }
        }
        else // Case when the parent is the right child of the grandparent
        {
            Node* uncle = grandparent->leftChild;

            if (uncle != nullptr && uncle->color == "RED") // Case 1: Uncle is red
            {
                parent->color = "BLACK";
                uncle->color = "BLACK";
                grandparent->color = "RED";
                node = grandparent;
            }
            else
            {
                if (node == parent->leftChild) // Case 2: Node is left child
                {
                    node = parent;
                    rightRotate(node);
                }
                // Case 3: Node is right child
                node->parent->color = "BLACK";
                node->parent->parent->color = "RED";
                leftRotate(node->parent->parent);
            }
        }
    }
    root->color = "BLACK"; // Ensuring the root is always black
}
//preOrderTraversal
void RedBlackTree::preOrderTraversal(Node* node) {
    if (node == nullptr) {
        return;
    }
    print(node);
    preOrderTraversal(node->leftChild);
    preOrderTraversal(node->rightChild);
}
//inorderTraversal
void RedBlackTree::inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->leftChild);
        print(node);
        inorderTraversal(node->rightChild);
    }
}
//postOrderTraversal
void RedBlackTree::postOrderTraversal(Node* node) {
    if (node != nullptr) {
        postOrderTraversal(node->leftChild);
        postOrderTraversal(node->rightChild);
        print(node);
    }
}

// Minimum 
Node* RedBlackTree::findMinimumNode(Node* node) {
    while (node->leftChild) node = node->leftChild;
    return node;
}
//Maximum
Node* RedBlackTree::findMaximumNode(Node* node) {
    while (node->rightChild) node = node->rightChild;
    return node;
}

// Search function
Node* RedBlackTree::treeSearch(string hotelName, string arrivalDate, int confirmNum)
{
    Node* current = root;
    while (current != nullptr)
    {
        if (current->hotelName == hotelName &&
            current->arrivalDate == arrivalDate &&
            current->confirmNum == confirmNum)
        {
            cout << left << setw(18) << hotelName << "on "
                << setw(12) << arrivalDate << "confirmation No.: "
                << setw(8) << confirmNum << " is found." << endl;
            return current;
        }
        if (confirmNum < current->confirmNum)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    cout << left << setw(5) << hotelName
        << setw(10) << confirmNum << " on "
        << setw(12) << arrivalDate << "confirmation No.: "
        << setw(8) << confirmNum <<" is NOT found." << endl;
    return nullptr;
}

// Left rotate function
void RedBlackTree::leftRotate(Node* node)
{
    Node* rightChild = node->rightChild;
    node->rightChild = rightChild->leftChild;

    if (rightChild->leftChild != nullptr)
        rightChild->leftChild->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->leftChild)
        node->parent->leftChild = rightChild;
    else
        node->parent->rightChild = rightChild;

    rightChild->leftChild = node;
    node->parent = rightChild;
}

// Right rotate function
void RedBlackTree::rightRotate(Node* node)
{
    Node* leftChild = node->leftChild;
    node->leftChild = leftChild->rightChild;

    if (leftChild->rightChild != nullptr)
        leftChild->rightChild->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->leftChild)
        node->parent->leftChild = leftChild;
    else
        node->parent->rightChild = leftChild;

    leftChild->rightChild = node;
    node->parent = leftChild;
}
// Predecessor
Node* RedBlackTree::findPredecessorNode(Node* node) {
    if (node->leftChild != nullptr) return findMaximumNode(node->leftChild);//findMaximumNode
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->leftChild) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Successor
Node* RedBlackTree::findSuccessorNode(Node* node) {
    if (node->rightChild != nullptr) return findMinimumNode(node->rightChild);//findMinimumNode
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->rightChild) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}
//function calling findMinimumNode(root)
void RedBlackTree::treeMinimum() {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    Node* minNode = findMinimumNode(root);
    cout << "The MINIMUM is:" << endl;
    print(minNode);
}
//function calling findMaximumNode(root)
void RedBlackTree::treeMaximum() {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    Node* maxNode = findMaximumNode(root);
    cout << "The MAXIMUM is:" << endl;
    print(maxNode);
}
//function calling preOrderTraversal(root);
void RedBlackTree::treePreorder() {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    preOrderTraversal(root);
}
//function calling inorderTraversal(root);
void RedBlackTree::treeInorder() {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    inorderTraversal(root);
}
//function calling postOrderTraversal(root);
void RedBlackTree::treePostorder() {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    postOrderTraversal(root);
}
//tree predecessor function
void RedBlackTree::treePredecessor(string hotelName, string arrivalDate, int confirmNum) {
    Node* node = treeSearch(hotelName, arrivalDate, confirmNum);
    if (node == nullptr) {
        cout << "Its Predecessor does NOT exist" << endl;
        return;
    }

    Node* predecessor = findPredecessorNode(node);
    if (predecessor != nullptr) {
        cout << "Its Predecessor is:" << endl;
        print(predecessor);
    }
    else {
        cout << "Its Predecessor does NOT exist" << endl;
    }
}
//tree successor function
void RedBlackTree::treeSucessor(string hotelName, string arrivalDate, int confirmNum) {
    Node* node = treeSearch(hotelName, arrivalDate, confirmNum);
    if (node == nullptr) {
        cout << "Its Predecessor does NOT exist" << endl;
        return;
    }

    Node* successor = findSuccessorNode(node);
    if (successor != nullptr) {
        cout << "Its Successor is:" << endl;
        print(successor);
    }
    else {
        cout << "Its Successor does NOT exist" << endl;
    }
}

// Insert a node with color fixing
void RedBlackTree::treeInsert(string hotelName, string arrivalDate, int confirmNum)
{
    Node* newNode = new Node();
    newNode->hotelName = hotelName;
    newNode->arrivalDate = arrivalDate;
    newNode->confirmNum = confirmNum;
    newNode->color = "RED"; //new node color will be red
    insertNode(newNode);
}

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node* node)
{
    cout << left;
    cout << setw(18) << node->hotelName
        << setw(12) << node->arrivalDate
        << setw(8) << node->confirmNum;
    cout << right << setw(7) << node->color << endl;
}


