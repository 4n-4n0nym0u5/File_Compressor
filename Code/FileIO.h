#ifndef HUFFMAN_FILEIO_H
#define HUFFMAN_FILEIO_H
/*
 'ifndef' & 'define' are called as an include guard used to prevent the multiple inclusions of the header file
//'#ifndef': if not define & also checks uniwue or not
'#define': then define & continue
*/
#include <string> 
#include <deque> // double sided queue that allows fast insertion & deletion at both its starting & its end
#include <fstream> // file stram responsible for reading & writing to a file
#include <iostream> //Input-Output stram, like cin, cout
#include <cstring> // similar to normal string, but they contain an extra null character corresponds to the end of the string
using namespace std;


/*
  "FileIO" Class responsible for all the processes related to reading and writing into a file,
  supporting the compressing and decompressing processes.
*/
class FileIO{
	/*
	Access specifiers can be public or private
	Data members;// variables to be used
	Member functions(){}  //methods to access data members
	'bool' member function: to return true or false
	'void' member function: if we don't want anything to return
	*/
	
public:
    bool readFile(string path,char **bufferOut, size_t *sizeOfFile);
	/*
	 path variable of string type, bufferOut pointer-to-pointer of char type & a pointer to an object of type size_t type 
	 size_t type returned by the sizeof operator used to describe sizes & counts
	*/
    bool writeEncodedFile(string path,string fileExtension,deque<int> frequencies,deque<char> symbols,int padding);
    void writeEncodedByte(const char bits[],unsigned long bufferSize);
    /* 
	unsigned long data type: (4 bytes) for large positive integers
	const is a type specifier that can't be changed
    */
	bool readerHeader(string path,deque<int> *frequencies, deque<char> *symbols,int *padding);
    void readSymbols(deque<char>*symbols);
    bool writeDecodedFile(string path);
    void writeDecodedByte( const char bits);
    void closeFile();

private:
    size_t getFileSize(string path);
    fstream stream; //stream is the name of variable & it's datatype is fstream, fstream is used for reading & writing to a file

}; //class always ends with a semicolon

#endif //used to close the '#ifndef' block

/* 
std:: means Standard library also known as STL(Standard template library)
used to access classes, functions, & objects from standard library
using namespace std; can remove the 'std::' writing from the program
*/
