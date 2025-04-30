#include <iostream>
using namespace std;

// Define the structure for a node
struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Function to split the linked list into two halves
Node* getMiddle(Node* head) {
    if (!head) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// Function to merge two sorted linked lists
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    // Merge the two sorted lists
    if (left->data <= right->data) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

// Merge Sort function for linked list
Node* mergeSort(Node* head) {
    // Base case: if the list is empty or has one element
    if (!head || !head->next) return head;

    // Step 1: Split the list into two halves
    Node* mid = getMiddle(head);
    Node* left = head;
    Node* right = mid->next;
    mid->next = nullptr;

    // Step 2: Recursively sort each half
    left = mergeSort(left);
    right = mergeSort(right);

    // Step 3: Merge the sorted halves
    return merge(left, right);
}

// Function to print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Helper function to add a new node at the end of the list
void push(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int main() {
    Node* head = nullptr;

    // Create a linked list: 10 -> 30 -> 20 -> 5 -> 50
    push(head, 10);
    push(head, 30);
    push(head, 20);
    push(head, 5);
    push(head, 50);

    cout << "Original Linked List: ";
    printList(head);

    // Perform merge sort on the linked list
    head = mergeSort(head);

    cout << "Sorted Linked List: ";
    printList(head);

    return 0;
}

