#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H
// line no. 20,35
#include "Node.h" // Including user-defined header file
#include <string>
#include <queue> // queue is a type of container that operate in FIFO type of arrangement
#include <map>//stores paired data like key-value pair
#include <vector>// vector is a dynamic contiguous array capable of resizing itself automatically.
#include "FileIO.h"

#include <iostream>
using namespace std;


/*
 This structure is a component of the priority queue collection, defining
 * how the collection will compare its elements. The comparison is made according
 * to the node frequencies, sorting them from the lowest to the highest frequency 
*/
//Don't know
struct node_cmp // structure with name node_cmp
{
	
    bool operator()(Node* a, Node* b ) const
    {
        return a->getFrequency() >= b->getFrequency();
    }
};


// Typedef Collection.
/* Definition of a new type of priority queue called FrequencyQueue, which is composed by a vector
 * of Nodes and a comparison function 
*/
// Don't know 
typedef priority_queue<Node*,vector<Node*>,node_cmp> FrequencyQueue;


//!  HuffmanCompressor.
/*!
  Class responsible for all the processes of enconding and compressing a file,
  as well as decoding and decompressing a file.
*/
class HuffmanCompressor{

private:
    Node *root;
    FrequencyQueue createFrequencyTable(char *content,int size);
    void serialize(Node *node, deque<int> *frequencies, deque<char> *symbols );
    Node* deserialize(deque<int> *frequencies, deque<char> *symbols);
    Node* createBinaryTree(FrequencyQueue queue);
    map<char,string> createEncodedMap();

public:
    bool encodeFile(string inputFile,string outputFilePath);
    bool decodeFile(string inputFile,string outputFilePath);

};



#endif //HUFFMAN_HUFFMAN_H
