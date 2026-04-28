#ifndef GROCERYHASHTABLE_H
#define GROCERYHASHTABLE_H

#include "GroceryItem.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class GroceryHashTable {
private:
    static const int TABLE_SIZE = 100;
    vector<list<GroceryItem>> table;

    int hashFunction(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }

public:
    GroceryHashTable() : table(TABLE_SIZE) {}

    void insert(GroceryItem item) {
        int index = hashFunction(item.barcode);
        
        for (auto& existing : table[index]) {
            if (existing.barcode == item.barcode) {
                existing = item;
                return;
            }
        }
        
        table[index].push_back(item);
    }

    GroceryItem* searchByBarcode(string barcode) {
        int index = hashFunction(barcode);
        
        for (auto& item : table[index]) {
            if (item.barcode == barcode) {
                return &item;
            }
        }
        
        return nullptr;
    }

    vector<GroceryItem*> searchByTitle(string title) {
        vector<GroceryItem*> results;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (auto& item : table[i]) {
                if (item.title.find(title) != string::npos) {
                    results.push_back(&item);
                }
            }
        }
        
        return results;
    }

    vector<GroceryItem*> searchByBarcodeAndTitle(string barcode, string title) {
        vector<GroceryItem*> results;
        
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (auto& item : table[i]) {
                if (item.barcode == barcode && item.title.find(title) != string::npos) {
                    results.push_back(&item);
                }
            }
        }
        
        return results;
    }

    void remove(string barcode) {
        int index = hashFunction(barcode);
        
        table[index].remove_if([barcode](const GroceryItem& item) {
            return item.barcode == barcode;
        });
    }

    void update(string barcode, GroceryItem newItem) {
        GroceryItem* item = searchByBarcode(barcode);
        if (item != nullptr) {
            item->title = newItem.title;
            item->unitPrice = newItem.unitPrice;
            item->quantityAvailable = newItem.quantityAvailable;
        }
    }

    void displayAll() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (auto& item : table[i]) {
                item.display();
                cout << "-------------------" << endl;
            }
        }
    }

    void updateQuantity(string barcode, int quantityOrdered) {
        GroceryItem* item = searchByBarcode(barcode);
        if (item != nullptr) {
            item->quantityAvailable -= quantityOrdered;
            if (item->quantityAvailable < 0) {
                item->quantityAvailable = 0;
            }
        }
    }
};

#endif