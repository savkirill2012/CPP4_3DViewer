#ifndef PASCER_H
#define PASCER_H

#include <fstream>
#include <sstream>
#include <string>

#include "obj_data.h"
namespace s21 {
class Read {
 public:
  virtual ~Read(){};
  virtual bool Search(std::string name_file, DataObj *data_model) = 0;
};

class ReadOne : public Read {
 public:
  bool Search(std::string name_file, DataObj *data_model) override;
  unsigned int getCountMemory(std::string &str);
};

class ReadTwo : public Read {
 public:
  bool Search(std::string name_file, DataObj *data_model) override;
  bool getDigit(std::string &str, DataObj *data_model);
  bool PushToFacets(std::string &str, unsigned int &first_element, int &step,
                    DataObj *data_model);
};

class Parser {
 public:
  Parser(Read *read) : read_(read){};
  ~Parser();
  void setStrategy(Read *read);
  bool ReadFile(std::string name_file, DataObj *data_model);
  // bool ReadDataFile(std::string &file_name);

 private:
  Read *read_;
};
}  // namespace s21
#endif  // PASCER_H
