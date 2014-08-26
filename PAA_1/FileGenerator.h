/* 
 * File:   FileGenerator.h
 * Author: familia
 *
 * Created on 10 de Agosto de 2014, 16:29
 */

#ifndef FILEGENERATOR_H
#define	FILEGENERATOR_H

class FileGenerator {
public:
    
    FileGenerator();
    FileGenerator(const FileGenerator& orig);
    virtual ~FileGenerator();
    int generate();
    
private:

};

#endif	/* FILEGENERATOR_H */

