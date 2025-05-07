#include <iostream>
using namespace std;

#define SIZE 10  

class HashTable {

private:
    int cnt = 0;//###################################
    int hashArray[SIZE];  

    int hashCode(int data) {
        return data % SIZE;
    }

public:

    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            hashArray[i] = -1;  
        } 
    } 

    void insert(int data) { // Without replacement

        int hashIndex = hashCode(data);
        int comp = 0;

        
        while (hashArray[hashIndex] != -1) {
            comp++;
            hashIndex = (hashIndex + 1) % SIZE;
        }

        hashArray[hashIndex] = data;
        cnt++;
        cout<<"Data inserted with "<< comp <<" comparisons "<<endl;
    }

    void insertWithReplacement(int data) { // With replacement

        int hashIndex = hashCode(data);
        int newHash = hashCode(hashArray[hashIndex]);
        int temp, comp = 0;


        if(hashArray[hashIndex] != -1) comp = -1;//###################################

        if(newHash == hashIndex){
            temp = data;
        }
        else{
            temp = hashArray[hashIndex];
            hashArray[hashIndex] = data;
        }

        while (hashArray[hashIndex] != -1) {
            comp++;
            hashIndex = (hashIndex + 1) % SIZE;
        }

        hashArray[hashIndex] = temp;//###################################
        cnt++;

        cout<<"Data inserted with "<< comp <<" comparisons "<<endl;

    }

    void bulkInsert(int numItems, bool withReplacement) {
        if(numItems > SIZE){
            cout<<"Hash Table size is 10"<<endl;
            return;
        }

        int data;
        for (int i = 0; i < numItems; i++) {
            if(cnt == SIZE){
                cout<<"Hash Table is Full"<<endl;
                return;
            }

            cout << "Enter data for item " << (i + 1) << ": ";
            cin >> data;
            if (withReplacement) {
                insertWithReplacement(data);  
            } else {
                insert(data);  
            }
        }
    }

    pair<bool, int> search(int data) {
        int hashIndex = hashCode(data);
        int mark = hashIndex;
        int t2 = 0;

        while (hashArray[hashIndex] != -1) {//###################################
            if(mark == hashIndex) t2++;

            if(t2 == 2){ 
                return {false, -1};
            }

            if (hashArray[hashIndex] == data) {
                return {true, hashIndex}; 
            }
            hashIndex = (hashIndex + 1) % SIZE;
        }

        return {false, -1}; 
    }

    bool deleteItem(int data) {
        int hashIndex = hashCode(data);
        int mark = hashIndex;
        int t3 = 0;

        while (hashArray[hashIndex] != -1) {

            if(mark == hashIndex) t3++;

            if(t3 == 2){
                return false;
            }

            if (hashArray[hashIndex] == data) {
                hashArray[hashIndex] = -1;  
                cnt--;
                return true;  
            }
            hashIndex = (hashIndex + 1) % SIZE;
        }

        return false;  
    }

    
    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (hashArray[i] == -1) {
                cout << "Idx " << i << ": Empty/Deleted" << endl;
            } else {
                cout << "Idx " << i << ": " << hashArray[i] << endl;
            }
        }
    }
};

int main() {
    HashTable hashTable;
    int choice, data, numItems; 
    
    pair<bool, int> srch = {false, -1};

    do {
        cout << "\n--- Hash Table Menu ---" << endl;
        cout << "1. Insert (Without replacement)" << endl;
        cout << "2. Insert (With replacement)" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Display" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter the number of items to insert: ";
                cin >> numItems;
                hashTable.bulkInsert(numItems, false); // Without replacement
                break;

            case 2:
                cout << "Enter the number of items to insert: ";
                cin >> numItems;
                hashTable.bulkInsert(numItems, true); // With replacement
                break;

            case 3: 
                cout << "Enter data to search: ";
                cin >> data;
                srch = hashTable.search(data);
                if (srch.first) {//###################################
                    cout << "Data found: " << data <<" at idx = "<< srch.second << endl;
                } else {
                    cout << "Data not found." << endl;
                }
                break;

            case 4:
                cout << "Enter data to delete: ";
                cin >> data;
                if (hashTable.deleteItem(data)) {//###################################
                    cout << "Data deleted: " << data << endl;
                } else {
                    cout << "Data not found to delete." << endl;
                }
                break;

            case 5:
                hashTable.display();
                break;

            case 6:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}
