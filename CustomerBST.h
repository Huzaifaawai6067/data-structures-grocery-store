#ifndef CUSTOMERBST_H
#define CUSTOMERBST_H

#include "Customer.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BSTNode {
    Customer data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Customer c) : data(c), left(nullptr), right(nullptr) {}
};

class CustomerBST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, Customer customer) {
        if (node == nullptr) {
            return new BSTNode(customer);
        }
        
        if (customer.cnic < node->data.cnic) {
            node->left = insertHelper(node->left, customer);
        } else if (customer.cnic > node->data.cnic) {
            node->right = insertHelper(node->right, customer);
        }
        
        return node;
    }

    BSTNode* searchHelper(BSTNode* node, string cnic) {
        if (node == nullptr || node->data.cnic == cnic) {
            return node;
        }
        
        if (cnic < node->data.cnic) {
            return searchHelper(node->left, cnic);
        }
        
        return searchHelper(node->right, cnic);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* deleteHelper(BSTNode* node, string cnic) {
        if (node == nullptr) return nullptr;
        
        if (cnic < node->data.cnic) {
            node->left = deleteHelper(node->left, cnic);
        } else if (cnic > node->data.cnic) {
            node->right = deleteHelper(node->right, cnic);
        } else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data.cnic);
        }
        
        return node;
    }

    void inorderHelper(BSTNode* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            node->data.display();
            cout << "-------------------" << endl;
            inorderHelper(node->right);
        }
    }

    BSTNode* buildBalancedBST(vector<Customer>& customers, int start, int end) {
        if (start > end) return nullptr;
        
        int mid = start + (end - start) / 2;
        BSTNode* node = new BSTNode(customers[mid]);
        
        node->left = buildBalancedBST(customers, start, mid - 1);
        node->right = buildBalancedBST(customers, mid + 1, end);
        
        return node;
    }

public:
    CustomerBST() : root(nullptr) {}

    void insert(Customer customer) {
        root = insertHelper(root, customer);
    }

    Customer* search(string cnic) {
        BSTNode* result = searchHelper(root, cnic);
        if (result != nullptr) {
            return &(result->data);
        }
        return nullptr;
    }

    void remove(string cnic) {
        root = deleteHelper(root, cnic);
    }

    void update(string cnic, Customer newData) {
        Customer* customer = search(cnic);
        if (customer != nullptr) {
            customer->name = newData.name;
            customer->mobile = newData.mobile;
            customer->address = newData.address;
        }
    }

    void displayAll() {
        inorderHelper(root);
    }

    void buildBalancedFromVector(vector<Customer>& customers) {
        sort(customers.begin(), customers.end(), 
             [](const Customer& a, const Customer& b) { return a.cnic < b.cnic; });
        root = buildBalancedBST(customers, 0, customers.size() - 1);
    }
};

#endif