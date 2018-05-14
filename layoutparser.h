#ifndef __LAYOUTPARSER_H__
#define __LAYOUTPARSER_H__
#include <vector>
#include <fstream>
#include "charactersMapping.h"

class LayoutParser {
  std::ifstream &inputFile;
  const int numFile = 5;
  const int rowNum = 25;
  const int totalRowNum = rowNum * numFile;
  public:
    LayoutParser(std::ifstream &file);
    ~LayoutParser() = default;
    std::vector<std::vector<CM>> parseFile();
};

#endif
