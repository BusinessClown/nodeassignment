// Node.h
#pragma once
#ifndef NODE_H_
#define NODE_H_
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(const string& data_item, Node* next_ptr = nullptr)
        : data(data_item), next(next_ptr) {}
};

#endif
