#include "layoutparser.h"
#include "codeConversion.h"
#include <string>
using namespace std;

LayoutParser::LayoutParser(ifstream &file): inputFile{file} {}

vector<vector<CM>> LayoutParser::parseFile(){
  string line;
  vector<vector<CM>> vvcm;
  for(int i=0; i < numFile; ++i){
    vector<CM> vcm;
    vvcm.emplace_back(vcm);
  }
  for(int i=0; i < totalRowNum; ++i){
    getline(inputFile, line);
    for(char& c : line) {
      CM tile = charToCmConversion[c];
      vvcm.at(i/rowNum).emplace_back(tile);
    }
  }
  return vvcm;
}
