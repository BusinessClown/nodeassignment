// Header.h
#pragma once
#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

int num_items = 0;

//Prints the full list
void printList(Node* head) {
    // Iterate through the list and print each node's data
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << ", ";
        curr = curr->next;
    }
    cout << endl;
}

// the starting creation of the list
std::pair <Node*,Node*>  makeNodeList() {
    string nameA, nameB, trash;

    cout << "How many items do you want to enter? " << endl;
    cin >> num_items;
    getline(cin, trash);  // Clear newline after input
    cout << "Enter a item: ";
    getline(cin, nameA);

    Node* head = new Node(nameA);
    Node* tail = head;

    for (int i = 1; i < num_items; i++) {
        cout << "Enter a item: ";
        getline(cin, nameB);
        tail->next = new Node(nameB,nullptr);
        tail = tail->next;
    }
    printList(head);
    return make_pair(head, tail);
}


//Adds item in head position
Node* push_front(Node* item, Node*& head, Node*& tail) {
    item->next = head;
    head = item;
    if (tail == nullptr) {
        tail = head;
    }
    num_items++;
    return head;
}
// Adds item at in tail position
std::pair <Node*, Node*> push_back(Node* new_tail, Node*& tail, Node*& head) {
    
    Node* last = head;
    
    while(last->next != nullptr) {
        last = last->next;
    }
    last->next = new Node(new_tail->data,nullptr);
    tail = last->next;
    num_items++;
    return make_pair(head, tail);
}

//Removes head of list
Node* pop_front(Node*& head, Node*& tail) {
    if (head == nullptr) {
        throw std::invalid_argument("Attempt to call pop_front() on an empty list");
    }
    Node* removed_node = head;
    head = head->next;
    delete removed_node;
    num_items--;
    return head;
}

// Removes tail of list
std::pair <Node*, Node*> pop_back(Node*& head, Node*& tail) {
    if (tail == nullptr) {
        throw std::invalid_argument("Attempt to call pop_back() on an empty list");
    }
    Node* removed_node = tail;
    Node* curr = head;
    for (int i = 1; i < num_items-1; i++) {
        curr = curr->next;
    }
    curr->next = nullptr;
    
    tail = curr;
    delete removed_node;
    num_items--;
    return make_pair(head, tail);
}

// Lets the user remove item at any position in the list
Node* erase(Node*& head, Node*& tail,int pos) {
    
    if (head == nullptr) {
        throw std::invalid_argument("Attempt to call erase on an empty list");
    }
        // Removes head is chosen postion is at head or less than 1
    if (pos <= 1) {
        head = pop_front(head, tail);
        return head;

    }else if (pos >= num_items) {
        //Removes tail if chosen position is at the tail or bigger than the list length 
        auto result = pop_back(head, tail);
        head = result.first;
        tail = result.second;
        return head;
    }
    else {
        // Traverse to find the correct position
        Node* current = head;
        Node* follow = head;

        for (int i = 1; i < pos; i++) {

            current = current->next;
        }
        
        while (follow->next != current) {
            follow = follow->next;
        }
         // Remove node in the middle
        
        Node* removed_node = current;

        follow->next = current->next;
        num_items--;
        delete removed_node;
    }

    
    return head;
}
//returns the value at the head of the list
string& front(Node* head) {
    if (head == nullptr) {
        throw std::invalid_argument("List is empty");
    }
    return head->data;
}
//returns the value at the tail of the list
string& back(Node* tail) {
    if (tail == nullptr) {
        throw std::invalid_argument("List is empty");
    }
    return tail->data;
}
//Returns if the list is empty or not
bool empty(Node* head) {
    if (head == nullptr) {
        return true;
    }
    else {
        return false;
    }

    
}
// Lets the user see if a item is in the list and states were if found or length and the fact it wasn't found
size_t find(Node* head,Node* item) {
    int pos = 1;
    Node* curr = head;
    while (curr->next != nullptr && item->data != curr->data) {
        pos++;
        curr = curr->next;
    }
    if (item->data == curr->data) {
        cout << item->data << " was found in position " << pos << endl;
    }
    else{
        cout << "The length of the list is " << pos << " and " << item->data << " wasn't found." << endl;
    }

    return pos;
}
// allows the user to add a item into any part of the list
std::pair <Node*, Node*> insert(int pos, Node* item, Node* head, Node* tail) {
    // Insert at the front if pos is at or less than the head
    if (pos <= 1) {
        head = push_front(item, head, tail);
    }
    // Insert at the back if pos is more than the list is long or at the tail
    else if (pos >= num_items) {
        auto result = push_back(item, tail, head);
        head = result.first;
        tail = result.second;
    }
    else{
        // Traverse to find the correct position in the list and adds the item there
        Node* current = head;
    
        for (int i=1; i < pos-1; i++) {

        current = current->next;
        }
        item->next = current->next;
        current->next = item;
    }
    return make_pair(head, tail);
}

// This is the menu that lets the user activate functions and use softwear
string menu() {
    // Has the user make the list
    auto result = makeNodeList();
    Node* head = result.first;
    Node* tail = result.second;
    string end,item,trash;
    bool test;
    int pos;
    // the loop that is the menu 
    while (end != "finished") {
        string menu_option;
        //user prompts
        cout << "Enter the option you want to perform: " << endl;
        cout << "push_front" << endl
            << "push_back" << endl
            << "pop_front" << endl
            << "pop_back" << endl
            << "front" << endl
            << "back" << endl
            << "empty" << endl
            << "insert" << endl
            << "remove" << endl
            << "find" << endl
            << "view_list" << endl
            << "end" << endl;
            cin >> menu_option;

        if (menu_option == "push_front") {
            // Push front logic
            getline(cin, trash);
            cout << "Enter the item you want to add" << endl;

            getline(cin, item);
            head = push_front(new Node(item), head, tail);

        }
        else if (menu_option == "push_back") {
            // Push back logic
            getline(cin, trash);
            cout << "Enter the value you want to add" << endl;
            getline(cin, item);
            auto result = push_back(new Node (item),tail,head);
            head = result.first;
            tail = result.second;
        }
        else if (menu_option == "pop_front") {
            // Pop front logic
            head = pop_front(head, tail);
        }
        else if (menu_option == "pop_back") {
            // Pop back logic
            auto result = pop_back(head, tail);
            head = result.first;
            tail = result.second;
        }
        else if (menu_option == "front") {
            // Print front logic
            cout << front(head) << " Is the first value in the list." << endl;
        }
        else if (menu_option == "back") {
            // Print back logic
            cout << back(tail) << " Is the last value in the list." << endl;
        }
        else if (menu_option == "empty") {
            // Check empty logic
            test = empty(head);
            if (test == true) {
                cout << "The list is empty." << endl;
            }
            else if (test == false) {
                cout << "The list is not empty." << endl;
            }
        }
        else if (menu_option == "insert") {
            // Insert logic
            cout << "Enter the numaric position you want to put the new value in at." << endl;
            cin >> pos;
            getline(cin, trash);
            cout << "Enter the value you want to add" << endl;
            getline(cin, item);
            auto result = insert(pos,new Node(item),head,tail);
            head = result.first;
            tail = result.second;
        }
        else if (menu_option == "remove") {
            // Remove logic
            cout << "Enter the postion you want to remove" << endl;
            cin >> pos;

            head = erase(head, tail,pos);

        }
        else if (menu_option == "find") {
            // Find logic
            getline(cin, trash);
            cout << "Enter the value you want to find" << endl;
            getline(cin, item);
            find(head,new Node(item));
        }
        else if (menu_option == "view_list") {
            // view list logic
            printList(head);
        }
        else if (menu_option == "end") {
            // Ends program logic
            printList(head);
            end = "finished";
        }
        else {
            // If the user enters something other than one of the 13 prompts
            cout << "Make sure you enter a valid option." << endl;
        }
    }
    return "done";
}
