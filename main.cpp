#include <iostream>
#include <fstream>
#include <sstream>
#include "Customer.h"
#include "GroceryItem.h"
#include "CustomerBST.h"
#include "GroceryHashTable.h"
#include "DeliveryGraph.h"

using namespace std;

void loadCustomers(CustomerBST& bst, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening " << filename << endl;
        return;
    }
    
    vector<Customer> customers;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string cnic, name, mobile, address;
        
        getline(ss, cnic, ',');
        getline(ss, name, ',');
        getline(ss, mobile, ',');
        getline(ss, address, ',');
        
        customers.push_back(Customer(cnic, name, mobile, address));
    }
    
    bst.buildBalancedFromVector(customers);
    file.close();
    cout << "Loaded " << customers.size() << " customers successfully!" << endl;
}

void loadGroceryItems(GroceryHashTable& hashTable, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening " << filename << endl;
        return;
    }
    
    string line;
    int count = 0;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string barcode, title, priceStr, quantityStr;
        
        getline(ss, barcode, ',');
        getline(ss, title, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        
        double price = stod(priceStr);
        int quantity = stoi(quantityStr);
        
        hashTable.insert(GroceryItem(barcode, title, price, quantity));
        count++;
    }
    
    file.close();
    cout << "Loaded " << count << " grocery items successfully!" << endl;
}

void loadGraph(DeliveryGraph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening " << filename << endl;
        return;
    }
    
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string nodeStr, name;
        
        getline(ss, nodeStr, ',');
        getline(ss, name, ',');
        
        int node = stoi(nodeStr);
        graph.setNodeName(node, name);
    }
    
    file.close();
    
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 6);
    graph.addEdge(2, 3, 4);
    graph.addEdge(2, 5, 3);
    graph.addEdge(3, 6, 7);
    graph.addEdge(4, 6, 2);
    graph.addEdge(4, 7, 5);
    graph.addEdge(5, 8, 4);
    graph.addEdge(6, 9, 3);
    graph.addEdge(7, 9, 4);
    graph.addEdge(8, 9, 2);
    
    cout << "Graph loaded successfully!" << endl;
}

void displayMenu() {
    cout << "\n========== Online Grocery Store ==========" << endl;
    cout << "1.  Add Customer" << endl;
    cout << "2.  Search Customer" << endl;
    cout << "3.  Update Customer" << endl;
    cout << "4.  Delete Customer" << endl;
    cout << "5.  Display All Customers" << endl;
    cout << "6.  Add Grocery Item" << endl;
    cout << "7.  Search Grocery Item (by Barcode)" << endl;
    cout << "8.  Search Grocery Item (by Title)" << endl;
    cout << "9.  Update Grocery Item" << endl;
    cout << "10. Delete Grocery Item" << endl;
    cout << "11. Display All Grocery Items" << endl;
    cout << "12. Process Delivery Order" << endl;
    cout << "0.  Exit" << endl;
    cout << "===========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    CustomerBST customerBST;
    GroceryHashTable groceryTable;
    DeliveryGraph deliveryGraph(10);
    
    loadCustomers(customerBST, "customers.txt");
    loadGroceryItems(groceryTable, "items.txt");
    loadGraph(deliveryGraph, "graph.txt");
    
    int choice;
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        if (choice == 0) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        
        switch (choice) {
            case 1: {
                string cnic, name, mobile, address;
                cout << "Enter CNIC: ";
                getline(cin, cnic);
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Mobile: ";
                getline(cin, mobile);
                cout << "Enter Address: ";
                getline(cin, address);
                
                customerBST.insert(Customer(cnic, name, mobile, address));
                cout << "Customer added successfully!" << endl;
                break;
            }
            
            case 2: {
                string cnic;
                cout << "Enter CNIC to search: ";
                getline(cin, cnic);
                
                Customer* customer = customerBST.search(cnic);
                if (customer != nullptr) {
                    cout << "\nCustomer Found:" << endl;
                    customer->display();
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;
            }
            
            case 3: {
                string cnic, name, mobile, address;
                cout << "Enter CNIC of customer to update: ";
                getline(cin, cnic);
                
                Customer* existing = customerBST.search(cnic);
                if (existing == nullptr) {
                    cout << "Customer not found!" << endl;
                    break;
                }
                
                cout << "Enter new Name: ";
                getline(cin, name);
                cout << "Enter new Mobile: ";
                getline(cin, mobile);
                cout << "Enter new Address: ";
                getline(cin, address);
                
                customerBST.update(cnic, Customer(cnic, name, mobile, address));
                cout << "Customer updated successfully!" << endl;
                break;
            }
            
            case 4: {
                string cnic;
                cout << "Enter CNIC of customer to delete: ";
                getline(cin, cnic);
                
                customerBST.remove(cnic);
                cout << "Customer deleted successfully!" << endl;
                break;
            }
            
            case 5: {
                cout << "\nAll Customers:" << endl;
                cout << "===================" << endl;
                customerBST.displayAll();
                break;
            }
            
            case 6: {
                string barcode, title;
                double price;
                int quantity;
                
                cout << "Enter Barcode: ";
                getline(cin, barcode);
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Unit Price: ";
                cin >> price;
                cout << "Enter Quantity: ";
                cin >> quantity;
                cin.ignore();
                
                groceryTable.insert(GroceryItem(barcode, title, price, quantity));
                cout << "Grocery item added successfully!" << endl;
                break;
            }
            
            case 7: {
                string barcode;
                cout << "Enter Barcode to search: ";
                getline(cin, barcode);
                
                GroceryItem* item = groceryTable.searchByBarcode(barcode);
                if (item != nullptr) {
                    cout << "\nItem Found:" << endl;
                    item->display();
                } else {
                    cout << "Item not found!" << endl;
                }
                break;
            }
            
            case 8: {
                string title;
                cout << "Enter Title to search: ";
                getline(cin, title);
                
                vector<GroceryItem*> items = groceryTable.searchByTitle(title);
                if (!items.empty()) {
                    cout << "\nItems Found: " << items.size() << endl;
                    for (auto item : items) {
                        item->display();
                        cout << "-------------------" << endl;
                    }
                } else {
                    cout << "No items found!" << endl;
                }
                break;
            }
            
            case 9: {
                string barcode, title;
                double price;
                int quantity;
                
                cout << "Enter Barcode of item to update: ";
                getline(cin, barcode);
                
                GroceryItem* existing = groceryTable.searchByBarcode(barcode);
                if (existing == nullptr) {
                    cout << "Item not found!" << endl;
                    break;
                }
                
                cout << "Enter new Title: ";
                getline(cin, title);
                cout << "Enter new Unit Price: ";
                cin >> price;
                cout << "Enter new Quantity: ";
                cin >> quantity;
                cin.ignore();
                
                groceryTable.update(barcode, GroceryItem(barcode, title, price, quantity));
                cout << "Item updated successfully!" << endl;
                break;
            }
            
            case 10: {
                string barcode;
                cout << "Enter Barcode of item to delete: ";
                getline(cin, barcode);
                
                groceryTable.remove(barcode);
                cout << "Item deleted successfully!" << endl;
                break;
            }
            
            case 11: {
                cout << "\nAll Grocery Items:" << endl;
                cout << "===================" << endl;
                groceryTable.displayAll();
                break;
            }
            
            case 12: {
                string cnic, barcode;
                int quantity;
                
                cout << "Enter Customer CNIC: ";
                getline(cin, cnic);
                
                Customer* customer = customerBST.search(cnic);
                if (customer == nullptr) {
                    cout << "Customer not found!" << endl;
                    break;
                }
                
                cout << "Enter Item Barcode: ";
                getline(cin, barcode);
                
                GroceryItem* item = groceryTable.searchByBarcode(barcode);
                if (item == nullptr) {
                    cout << "Item not found!" << endl;
                    break;
                }
                
                cout << "Enter Quantity to order: ";
                cin >> quantity;
                cin.ignore();
                
                if (item->quantityAvailable < quantity) {
                    cout << "Insufficient quantity available!" << endl;
                    break;
                }
                
                cout << "\nOrder Details:" << endl;
                cout << "Customer: " << customer->name << endl;
                cout << "Item: " << item->title << endl;
                cout << "Quantity: " << quantity << endl;
                cout << "Total Price: $" << (item->unitPrice * quantity) << endl;
                cout << "Delivery Address: " << customer->address << endl;
                cout << endl;
                
                int customerNode;
                cout << "Enter customer's location node (0-9): ";
                cin >> customerNode;
                cin.ignore();
                
                deliveryGraph.displayPath(0, customerNode);
                
                groceryTable.updateQuantity(barcode, quantity);
                cout << "\nOrder processed successfully!" << endl;
                cout << "Inventory updated. Remaining quantity: " << item->quantityAvailable << endl;
                break;
            }
            
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}