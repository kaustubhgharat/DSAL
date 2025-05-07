#include<iostream>
#include<vector>
using namespace std;

#define SIZE 10 

class Node{
    int data;
    Node* next;
public:
    Node(int val) {
        data = val;
        next = NULL;
    }
    friend class Htable;
};

class Htable{
    vector<Node*> vec;//###################################

public:
    Htable() {
        for(int i=0; i<SIZE; i++) {
            vec.push_back(NULL);
        }
    }

    int HashCode(int data){
        return data % SIZE;
    }

    void Insert(int val) { 
        int hashKey = HashCode(val);
        Node* temp = new Node(val);//###################################

        if(!vec[hashKey]){
            vec[hashKey] = temp;
        } else {
            Node* head = vec[hashKey];//###################################
            while(head->next != NULL){
                head = head->next;
            }
            head->next = temp;
        }
    }

    void display() {
        for(int i=0; i<SIZE; i++) {
            if(!vec[i]){
                cout<<"Idx: "<< i << ": Empty "<<endl;
            }
            else{
                Node* head = vec[i];
                cout<<"Idx: "<< i;
                while(head != NULL){
                    cout<<" -> " << head->data;
                    head = head->next;
                }
                cout << endl;
            }
        }
    }

    void Find(int val){
        int hashKey = HashCode(val);
        if(!vec[hashKey]){
            cout<<"NOT FOUND"<<endl;
        }else{
           Node* head = vec[hashKey];
            while(head != NULL){
                if(head->data == val){
                    cout<<"Data "<< head->data <<" found at Idx: "<<hashKey<<endl;
                    return;
                }
                head = head->next;
            }
            cout<<"NOT FOUND"<<endl;
        }
    }

    void Delete(int val){
        int hashKey = HashCode(val);

        if(!vec[hashKey]){
            cout<<"NOT FOUND to Delete"<<endl;
        }else{
           Node* head = vec[hashKey];

           if(head->data == val){
               vec[hashKey] = head->next;//###################################
               delete head;
               cout << "Deleted "<< val << endl;
               return;
           }

           while(head->next != NULL && head->next->data != val){
               head = head->next;
           }

           if(head->next == NULL){//###################################
               cout<<"NOT FOUND to Delete"<<endl;
           } else {
               Node* del = head->next;//###################################
               head->next = head->next->next;
               del->next = NULL;
               delete del;
               cout << "Deleted "<< val << endl;
           }
        }
    }
};

int main() {
    Htable ht;
    int choice, val;

    while(true) {
        cout << "\nHash Table Menu\n";
        cout << "1. Insert\n";
        cout << "2. Display\n";
        cout << "3. Find\n";
        cout << "4. Delete\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                ht.Insert(val);
                cout << "Inserted " << val << " into hash table.\n";
                break;

            case 2:
                cout << "Displaying Hash Table:\n";
                ht.display();
                break;

            case 3:
                cout << "Enter value to find: ";
                cin >> val;
                ht.Find(val);
                break;

            case 4:
                cout << "Enter value to delete: ";
                cin >> val;
                ht.Delete(val);
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
