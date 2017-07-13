#ifdef WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif


#include "xmlParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>



using std::cout;
using std::endl;
using std::string;




void Run(const char *xmlpath){

    XMLNode xMainNode=XMLNode::openFileHelper(xmlpath, "PMML");

    XMLNode xNode=xMainNode.getChildNode("Header");
    cout << xNode.getChildNode("Application").getAttribute("name") << endl;

    cout << xMainNode.getChildNodeByPath("Command").getAttribute("name") << endl;


    xNode=xMainNode.getChildNode("Command");
    int n=xNode.nChildNode("Key");

    std::string ptrName;
    std::string ptrSource;
    std::string ptrDest;
    int i,myIterator=0;


    char * buffer;
    int len = 4096;

    for (i=0; i < n; i++){
        auto temp = xNode.getChildNode("Key",&myIterator);
        ptrName = std::string(temp.getAttribute("name") );
        ptrSource = std::string(temp.getAttribute("sourcefile")) ;
        ptrDest = std::string(temp.getAttribute("destfile")) ;

        if( ptrSource[ptrSource.size()-1] != '/' ) { ptrSource = ptrSource + "/"; }
        if( ptrDest[ptrDest.size()-1] != '/' ) { ptrDest = ptrDest + "/"; }   

        
         std::ifstream infile(ptrSource + ptrName, std::ios::in | std::ios::binary);
         

         if(infile){ 
             std::ofstream outfile(ptrDest + ptrName, std::ios::out | std::ios::binary);  
             if(outfile){
                 buffer = new char[len];
                 while (!infile.eof()){
                  infile.read(buffer, len);
                  if(infile.gcount()) outfile.write(buffer, infile.gcount());
                 }
                 outfile.close();
              }else{
                 cout << "Not find file: " << ptrSource + ptrName << endl;
              } 
         }else{   
            cout << "Not find file: " << ptrSource + ptrName << endl;                          
         }
        
         infile.close();
          

         delete[] buffer;
    }
}

int main(int argc, char **argv)
{
   

    Run("XMLCommand.xml");  

    return 0;
}

