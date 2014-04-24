#include "Header.h"

Header::Header() {
    this->BfType = NULL;
}

Header::~Header() {
    if (this->BfType != NULL) {
        delete this->BfType;
    }
}

unsigned int Header::GetBfOffSetBits() const {
    return BfOffSetBits;
}

void Header::SetBfOffSetBits(unsigned int BfOffSetBits) {
    this->BfOffSetBits = BfOffSetBits;
}

unsigned short Header::GetBfReser1() const {
    return BfReser1;
}

void Header::SetBfReser1(unsigned short BfReser1) {
    this->BfReser1 = BfReser1;
}

unsigned short Header::GetBfReser2() const {
    return BfReser2;
}

void Header::SetBfReser2(unsigned short BfReser2) {
    this->BfReser2 = BfReser2;
}

unsigned int Header::GetBfSize() const {
    return BfSize;
}

void Header::SetBfSize(unsigned int BfSize) {
    this->BfSize = BfSize;
}

unsigned char* Header::GetBfType() {
    return BfType;
}

void Header::SetBfType(unsigned char* BfType) {
    this->BfType = BfType;
}

void Header::read(std::ifstream *input) {

    this->BfType = new unsigned char[3];
    this->BfType[2] = '\0';
    input->read((char *) this->BfType, sizeof (char)*2); // Le bfType

    input->read((char*) & this->BfSize, sizeof (BfSize)); //Le BfSize

    input->read((char*) & this->BfReser1, sizeof (BfReser1)); //Le BfReser1

    input->read((char*) & this->BfReser1, sizeof (BfReser2)); //Le BfRezer2

    input->read((char*) & this->BfOffSetBits, sizeof (BfOffSetBits)); // Le BfOffSetBits

}

void Header::print() {
    std::cout << "BfType       : " << this->GetBfType() << std::endl;
    std::cout << "BfSize       : " << this->GetBfSize() << std::endl;
    std::cout << "BfRezer1     : " << this->GetBfReser1() << std::endl;
    std::cout << "BfRezer2     : " << this->GetBfReser1() << std::endl;
    std::cout << "BfOffSetBits: " << this->GetBfOffSetBits() << std::endl;
}