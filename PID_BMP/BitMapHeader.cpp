/* 
 * File:   BitMapHeader.cpp
 * Author: marcelo-note
 *
 * Created on 8 de Abril de 2014, 14:45
 */

#include "BitMapHeader.h"

BitMapHeader::BitMapHeader() {
}

BitMapHeader::BitMapHeader(const BitMapHeader& orig) {
    this->BiBitCount = orig.GetBiBitCount();
    this->BiClrImport = orig.GetBiClrImport();
    this->BiCompress = orig.GetBiCompress();
    this->BiCrlUsed = orig.GetBiCrlUsed();
    this->BiHeigth = orig.GetBiHeigth();
    this->BiPlanes = orig.GetBiPlanes();
    this->BiSize =  orig.GetBiSize();
    this->BiSizeImage  = orig.GetBiSizeImage();
    this->BiWidth = orig.GetBiWidth();
    this->BiXPPMeter = orig.GetBiXPPMeter();
    this->BiYPPMeter = orig.GetBiYPPMeter();
}

BitMapHeader::~BitMapHeader() {
}

unsigned short BitMapHeader::GetBiBitCount() const {
    return BiBitCount;
}

void BitMapHeader::SetBiBitCount(unsigned short BiBitCount) {
    this->BiBitCount = BiBitCount;
}

unsigned int BitMapHeader::GetBiClrImport() const {
    return BiClrImport;
}

void BitMapHeader::SetBiClrImport(unsigned int BiClrImport) {
    this->BiClrImport = BiClrImport;
}

unsigned int BitMapHeader::GetBiCompress() const {
    return BiCompress;
}

void BitMapHeader::SetBiCompress(unsigned int BiCompress) {
    this->BiCompress = BiCompress;
}

unsigned int BitMapHeader::GetBiCrlUsed() const {
    return BiCrlUsed;
}

void BitMapHeader::SetBiCrlUsed(unsigned int BiCrlUsed) {
    this->BiCrlUsed = BiCrlUsed;
}

unsigned int BitMapHeader::GetBiHeigth() const {
    return BiHeigth;
}

void BitMapHeader::SetBiHeigth(unsigned int BiHeigth) {
    this->BiHeigth = BiHeigth;
}

unsigned short BitMapHeader::GetBiPlanes() const {
    return BiPlanes;
}

void BitMapHeader::SetBiPlanes(unsigned short BiPlanes) {
    this->BiPlanes = BiPlanes;
}

unsigned int BitMapHeader::GetBiSize() const {
    return BiSize;
}

void BitMapHeader::SetBiSize(unsigned int BiSize) {
    this->BiSize = BiSize;
}

unsigned int BitMapHeader::GetBiWidth() const {
    return BiWidth;
}


void BitMapHeader::SetBiWidth(unsigned int BiWidth) {
    this->BiWidth = BiWidth;
}

unsigned int BitMapHeader::GetBiXPPMeter() const {
    return BiXPPMeter;
}

void BitMapHeader::SetBiXPPMeter(unsigned int BiXPPMeter) {
    this->BiXPPMeter = BiXPPMeter;
}

unsigned int BitMapHeader::GetBiYPPMeter() const {
    return BiYPPMeter;
}

void BitMapHeader::SetBiYPPMeter(unsigned int BiYPPMeter) {
    this->BiYPPMeter = BiYPPMeter;
}

unsigned int BitMapHeader::GetBiSizeImage() const{
    return this->BiSizeImage;
}

void BitMapHeader::SetBiSizeImage(unsigned int BiSizeImage) {
    this->BiSizeImage = BiSizeImage;
}
void BitMapHeader::read(std::ifstream *input){
    input->read((char*)&this->BiSize,sizeof(this->BiSize));
    input->read((char*)&this->BiWidth,sizeof(this->BiWidth));
    input->read((char*)&this->BiHeigth,sizeof(this->BiHeigth));
    input->read((char*)&this->BiPlanes,sizeof(this->BiPlanes));
    input->read((char*)&this->BiBitCount,sizeof(this->BiBitCount));
    input->read((char*)&this->BiCompress,sizeof(this->BiCompress));
    input->read((char*)&this->BiSizeImage,sizeof(this->BiSizeImage));
    input->read((char*)&this->BiXPPMeter,sizeof(this->BiXPPMeter));
    input->read((char*)&this->BiYPPMeter,sizeof(this->BiYPPMeter));
    input->read((char*)&this->BiCrlUsed,sizeof(this->BiCrlUsed));
    input->read((char*)&this->BiClrImport,sizeof(this->BiClrImport));
    
}

void BitMapHeader::print(){
    std::cout << "BiSize     :" << this->GetBiSize() << std::endl;
    
    unsigned int a =  this->GetBiHeigth();
    std::cout << "BiWidth    :" << this->GetBiWidth() << std::endl;
    std::cout << "BiHeigth   :" << a << std::endl;
    std::cout << "BiPlanes   :" << this->GetBiPlanes() << std::endl;
    std::cout << "BiBitCount :" << this->GetBiBitCount() << std::endl;
    std::cout << "BiCompress :" << this->GetBiCompress() << std::endl;
    std::cout << "BiZiseImage:" << this->GetBiSizeImage() << std::endl;
    std::cout << "BiXPPMeter :" << this->GetBiXPPMeter() << std::endl;
    std::cout << "BiYPPMeter :" << this->GetBiYPPMeter() << std::endl;
    std::cout << "BiCrlUsed  :" << this->GetBiCrlUsed() << std::endl;
    std::cout << "BiCrlImport:" << this->GetBiClrImport() << std::endl;
}

BitMapHeader &BitMapHeader::operator =(const BitMapHeader &ori){
    this->SetBiBitCount(ori.GetBiBitCount());
    this->SetBiClrImport(ori.GetBiClrImport());
    this->SetBiCompress(ori.GetBiCompress());
    this->SetBiCrlUsed(ori.GetBiCrlUsed());
    this->SetBiHeigth(ori.GetBiHeigth());
    this->SetBiPlanes(ori.GetBiPlanes());
    this->SetBiSize(ori.GetBiSize());
    this->SetBiSizeImage (ori.GetBiSizeImage());
    this->SetBiWidth(ori.GetBiWidth());
    this->SetBiXPPMeter(ori.GetBiXPPMeter());
    this->SetBiYPPMeter(ori.GetBiYPPMeter());
    return (*this);
}

void BitMapHeader::SaveBitMapHeader(std::ofstream &arquivoSaida){
    //grava o cabeçalho da imagem
    arquivoSaida.write((char*) & this->BiSize, sizeof (this->BiSize));
    arquivoSaida.write((char*) & this->BiWidth, sizeof (this->BiWidth));
    arquivoSaida.write((char*) & this->BiHeigth, sizeof (this->BiHeigth));
    arquivoSaida.write((char*) & this->BiPlanes, sizeof (this->BiPlanes));
    arquivoSaida.write((char*) & this->BiBitCount, sizeof (this->BiBitCount));
    arquivoSaida.write((char*) & this->BiCompress, sizeof (this->BiCompress));
    arquivoSaida.write((char*) & this->BiSizeImage, sizeof (this->BiSizeImage));
    arquivoSaida.write((char*) & this->BiXPPMeter, sizeof (this->BiXPPMeter));
    arquivoSaida.write((char*) & this->BiYPPMeter, sizeof (this->BiYPPMeter));
    arquivoSaida.write((char*) & this->BiCrlUsed, sizeof (this->BiCrlUsed));
    arquivoSaida.write((char*) & this->BiClrImport, sizeof (this->BiClrImport));
}
