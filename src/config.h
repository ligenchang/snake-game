#ifndef CONFIG_H
#define CONFIG_H
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
class Config {
public:
  virtual std::size_t Read(std::string field) = 0;
  virtual void Update(std::string field) = 0;
};

class TxtConfig : public Config{
public:

std::size_t Read() override;


void Update(std::string field)override;

TxtConfig(std::string filename);

~TxtConfig();

private:
std::ifstream _filestream;
std::string _filename;
};

#endif