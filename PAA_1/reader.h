#ifndef READER_H
#define READER_H

#include <fstream>
#include <string>


class reader
{
public:
    reader();
    static void read(std::string nome, int size);
    static int* getVector();
    static int size;
    ~reader();
    static int *v;

};

#endif // READER_H
