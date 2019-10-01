
#include "config.h"
#include <vector>
#include <iostream>




TxtConfig::TxtConfig(std::string filename) {
_filename=filename;
_filestream.open(_filename);
std::cout<<"_filename is"<<_filename<<"\n";
}

std::size_t TxtConfig::Read(){
std::string param;
std::getline(_filestream, param);
std::stringstream sstream(param);
size_t result;
sstream >> result;
return result;
}

void TxtConfig::Update(std::string field){

}

TxtConfig::~TxtConfig(){

}