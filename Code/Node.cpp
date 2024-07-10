#include "Node.h"
#include <iostream>
#include <iomanip>
#include "Huffman.h"




Node::Node(char character) {
    this->left = nullptr;
    this->right = nullptr;
    this->character = character;
    this->frequency = 0;
}



Node::Node(Node *left, Node *right) {
    this->left = left;
    this->right = right;
    this->character = '+';
    this->frequency = 0;

}

Node::~Node() {
    delete this->left;
    delete this->right;
}

bool Node::isLeaf() {
    return (this->right == nullptr && this->left == nullptr);
}

int Node::getFrequency(){
    if(this->isLeaf())
        return this->frequency;

    return this->left->getFrequency() + this->right->getFrequency();

}

char Node::getSymbol() {
    return this->character;
}

Node* Node::getLeft() {
    return this->left;
}

Node* Node::getRight() {
    return this->right;
}

void Node::setSymbol(char c) {
    this->character = c;
}

void Node::incrementFrequency() {
    this->frequency++;
}

void Node::incrementFrequency(int value) {
    this->frequency += value;
}

void Node::FillEncondedTable(std::map<char,std::string> *table,std::string bitsValue) {
    if(this->isLeaf()){
        table->insert(std::pair<char,std::string>(getSymbol(),bitsValue));

        return;
    }

    if(left != nullptr);
        left->FillEncondedTable(table,bitsValue + "0");

    if(right!= nullptr)
        right->FillEncondedTable(table,bitsValue + "1");

}

void Node::showTree() {

    std::cout << "Character: " << this->character << " Frequency: " << this->frequency << std::endl;
    if(left != nullptr) {

        std::cout << "Left" << std::endl;
        left->showTree();
    }
    if(right != nullptr) {
        std::cout << "Right" << std::endl;
        right->showTree();
    }

}


