#include "Huffman.h"



void return_size(unsigned long size);
void return_compSize(unsigned long compSize);
void return_effiSize(double effiSize);
FrequencyQueue HuffmanCompressor::createFrequencyTable(char *character,int size) {

    //This map organize and increments frequencies of the characters, putting them in nodes, in order to
    //create the tree
    std::map<char,Node*> mapped;

    //Veryfing all the characters and counting how many times they appear in the file
    for(int i = 0; i < size; i++){
        if(mapped.count(character[i]) == 0) // if key is not present at the map, returns 0
            mapped.insert(std::pair<char, Node *>(character[i], new Node(character[i])));

        //if key already exits, increments its frequency by one
        mapped.at(character[i])->incrementFrequency();
    }

    //std::cout << "Size of the frequency table: " << mapped.size() <<  std::endl;


    //Inserting the nodes in the Frequency Queue, which sort them automatically
    FrequencyQueue queue;


    for(auto const& pair:mapped){
        queue.push(pair.second);

    }


    return queue;
}

Node* HuffmanCompressor::createBinaryTree(FrequencyQueue queue) {
    Node *first, *second;
    Node *parent;

    while(true){

        //Getting the two first nodes with lower frequencies and organizing them into a parent Node
        if(queue.empty())
            first = nullptr;
        else
            first = queue.top();

        if(!queue.empty()) queue.pop();

        if(queue.empty())
            second = nullptr;
        else
            second = queue.top();
        if(!queue.empty()) queue.pop();

        parent = new Node(first,second);
        parent->incrementFrequency(parent->getFrequency());


        //if the queue is empty, it means that the grouping has reached the end, leaving the two left
        //nodes to be put into the root node;
        if(queue.empty())
            return parent;

        queue.push(parent);
    }


}



std::map<char,std::string> HuffmanCompressor::createEncodedMap() {
    std::map<char,std::string> table;
    if(root!= nullptr)
        root->FillEncondedTable(&table,"");
    return table;
}


void HuffmanCompressor::serialize(Node *node, std::deque<int> *frequencies, std::deque<char> *symbols) {
    if(node != nullptr){
        if(node->isLeaf()){
            symbols->push_back(node->getSymbol());
            frequencies->push_back(node->getFrequency());
            return;
        }
        if(node->getLeft() != nullptr)
            serialize(node->getLeft(),frequencies,symbols);
        if(node->getRight()!= nullptr)
            serialize(node->getRight(),frequencies,symbols);
    }

}

Node *HuffmanCompressor::deserialize(std::deque<int> *frequencies, std::deque<char> *symbols) {
    FrequencyQueue queue;
    Node *aux;
    char c;
    int frequency;
    std::map<char,Node*> map;
    while(!frequencies->empty()){
        c = symbols->front();
        symbols->pop_front();
        frequency = frequencies->front();
        frequencies->pop_front();
        aux = new Node(c);
        aux->incrementFrequency(frequency);
        map.insert(std::pair<char,Node*>(c,aux));
    }

    for(auto const& pair:map)
        queue.push(pair.second);

    return createBinaryTree(queue);
}

bool HuffmanCompressor::encodeFile(std::string inputFile, std::string outputFilePath) {
    std::cout << "Compressing file..." <<std::endl;
    FileIO encodedFile;
    char *content;
    size_t size;
    std::map<char,std::string> encodedMap;
    std::string encondedText;
    std::deque<int> frequencies;
    std::deque<char> symbols;
    int padding = 0;
    unsigned long count;
    unsigned long numberOfChars;
    FrequencyQueue tableQueue;
	
	unsigned long totalSize;
	double efficiency;
	
    if(!encodedFile.readFile(inputFile,&content, &size)){
        std::cout << "File couldn't be opened, please check the path and try again" << std::endl;
        return false;
    }
	totalSize = size * 8;
    return_size(totalSize);
    std::cout << "File size: " << size * 8 << " bytes"<< std::endl;

    tableQueue = createFrequencyTable(content,size);

    //defining the root of the tree
    root = createBinaryTree(tableQueue);
    encodedMap = createEncodedMap();

    //Serializing the tree to write at the head of the compressed file
    serialize(root,&frequencies,&symbols);


    //calculating the padding of the encoded file

    count = tableQueue.size();
    numberOfChars = 0;
    for(int i = 0; i < count; i ++){
        numberOfChars += tableQueue.top()->getFrequency() * encodedMap.at(tableQueue.top()->getSymbol()).size();
        tableQueue.pop();
    }



    padding = numberOfChars % 8;
    std::cout << "Size of the compressed file: " << numberOfChars << " bytes" << std::endl;
    return_compSize(numberOfChars);
    
    efficiency = ((double) (totalSize-numberOfChars)/totalSize)*100;
	std::cout <<"Efficiency of this file compression process is: "<<efficiency<<"%"<<endl;
    return_effiSize(efficiency);
    unsigned long bufferSize = (numberOfChars/8);
    if(bufferSize > 1024)
        bufferSize/=1024;
    else if(bufferSize > 512)
        bufferSize /= 512;
    else
        bufferSize = 1;

    //Writing header and enconded content to file

    if(!encodedFile.writeEncodedFile(outputFilePath,".tfs",frequencies,symbols,padding)){
        std::cout << "Output file couldn't be created." << std::endl;
    }

    //Enconding new compressed file and writing to file

    unsigned long j = 1;
    for(unsigned long i =0; i<size;i++){
        if(i>j)
            break;
        encondedText.append(encodedMap.at(content[i]));
        if(encondedText.size() >= 8 * bufferSize){
            encodedFile.writeEncodedByte(encondedText.substr(0,8 * bufferSize).c_str(), bufferSize);
            encondedText.erase(0,8 * bufferSize); // clean up the buffer to next byte
            j = i;
        }
    }

    //Writes the remaining bytes that didn't fit the bufferSize
    if(++j < size){
        for(;j<size;j++){
            encondedText.append(encodedMap.at(content[j]));
           if(encondedText.size() >=8){
                encodedFile.writeEncodedByte(encondedText.substr(0,8).c_str(),1);
                encondedText.erase(0,8);
            }
        }
    }



    //if there's padding, then write last byte, filling the rest of it with 1's
    if(padding != 0) {

        for (int i = 0; i < 8 - padding; i++) {
            encondedText.append("1");
        }
        encodedFile.writeEncodedByte(encondedText.c_str(),1);
    }
    encodedFile.closeFile();

    //Deallocating memory used by chars and Huffman Tree
    delete content;
    delete root;

    std::cout << "File compressed successfully!" << std::endl<<std::endl<<std::endl;
    return true;
}

bool HuffmanCompressor::decodeFile(std::string inputFile, std::string outputFilePath) {
    std::cout << "Decompressing file..." << std::endl;
    Node *root,*current;
    FileIO decodedFile;
    int padding;
    std::deque<int> frequencies;
    std::deque<char> symbols;


    if(!decodedFile.readerHeader(inputFile,&frequencies,&symbols,&padding)){
        std::cout << "Input file couldn't be opened, please check the path and try again" << std::endl;
        return false;
    }
    root = deserialize(&frequencies,&symbols);
    symbols.clear();
    decodedFile.readSymbols(&symbols);
    int count;
    char c;
    current = root;

    decodedFile.writeDecodedFile(outputFilePath);

    count = 8;

    for(unsigned long i = 0; i < symbols.size(); i++){
        c = symbols.at(i);
        if(i == symbols.size() - 1) {
            count = padding;
			}

        for(int j = 0; j<count; j++){
            if(((c >> j) & 0x01) == 0){
                current = current->getLeft();
            }
            else {
                current = current->getRight();
            }
                if(current->isLeaf()){
                    decodedFile.writeDecodedByte(current->getSymbol());
                current = root;
            }

        }
    }
    decodedFile.closeFile();
    //Deallocating memory used by Huffman Tree
    delete root;

    std::cout << "File decompressed successfully!" << std::endl<<std::endl<<std::endl;
    return true;

}


