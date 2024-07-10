#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <map> //stores paired data like key-value pair
#include <vector>// vector is a dynamic contiguous array capable of resizing itself automatically.
#include <deque>// double sided queue that allows fast insertion & deletion at both its starting & its end


#include <iostream>
#include <string>
using namespace std;

/*
  This Class responsible for representing a node of a tree. Its goal is tosupport creation of the Huffman Tree.
*/
class Node{

private:
	//Data members
    char character;
    int frequency;
    Node* left;
    Node* right;
    //Node stores at least 2 things - data & address

	
public:
	//Member functions
    Node(Node* left, Node* right);
    Node(char character);
    ~Node(); 
	/*
	destructor of a class named 'Node', 
	destructor is a special member function that is called automatically when an object of the class goes out of scope or is explicitly deleted. 
	responsible for cleanup operation for the object 
	cleanup tasks like realeasing dynamically allocated memory, closing files etc to ensure the proper destruction of the object
	*/
    bool isLeaf();
    int getFrequency();
    char getSymbol();
    Node* getLeft();
    Node* getRight();
    void setSymbol(char c);
    void incrementFrequency();
    void incrementFrequency(int value);
    void FillEncondedTable(map<char,string> *table,string bitsValue);
    void showTree();
};







#endif //HUFFMAN_NODE_H
