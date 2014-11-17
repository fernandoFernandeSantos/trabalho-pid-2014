#include "Header.h"

Header::Header() {
    this->BfType = NULL;
}

Header::Header(const Header & orig){
    this->BfOffSetBits = orig.BfOffSetBits;
    this->BfReser1 = orig.BfReser1;
    this->BfReser2 = orig.BfReser2;
    this->BfSize = orig.BfSize;
    this->BfType = new unsigned char[3];
    strcpy((char*)BfType,(char*)orig.BfType);
}

Header::~Header() {
    if (this->BfType != NULL) {
        delete[] this->BfType;
        this->BfType = NULL;
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
    std::cout << "BfOffSetBits : " << this->GetBfOffSetBits() << std::endl;
}

void Header::saveHeader(std::ofstream& arquivoSaida){
    //como em c só grava endereço tem que por para variavéis
    /*char BfType1 = out.GetBfType()[0];
    char BfType2 = out.GetBfType()[1];
    unsigned int BfSize = out.GetBfSize();
    u_short BfReser1 = out.GetBfReser1();
    u_short BfReser2 = out.GetBfReser2();
    unsigned int BfOffSetBits = out.GetBfOffSetBits();
*/
    //grava o header
    arquivoSaida.write((char*) & this->BfType[0], sizeof (this->BfType[0]));
    arquivoSaida.write((char*) & this->BfType[1], sizeof (this->BfType[1]));
    arquivoSaida.write((char*) & this->BfSize, sizeof (BfSize));
    arquivoSaida.write((char*) & this->BfReser1, sizeof (BfReser1));
    arquivoSaida.write((char*) & this->BfReser2, sizeof (BfReser2));
    arquivoSaida.write((char*) & this->BfOffSetBits, sizeof (BfOffSetBits));
}


Header &Header::operator =(const Header &orig){
    this->SetBfOffSetBits(orig.BfOffSetBits);
    this->SetBfReser1(orig.BfReser1);
    this->SetBfReser2(orig.BfReser2);
    this->SetBfSize(orig.BfSize);
    this->BfType  = new unsigned char[3];
    strcpy((char*)BfType,(char*)orig.BfType);
    return (*this);
}
