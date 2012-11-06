#ifndef CALIBTREEMAKERHELPER_H

#include <vector>
#include <string>

namespace CalibTreeMakerHelper {
  unsigned int findTrigger(const std::vector<std::string>& list, const std::string& name);

  class AllTriggerInfo{
  public:
    AllTriggerInfo(std::string name, std::string HLTname, bool fired, int prescale, bool writePrescale=false) : name_(name), HLTname_(HLTname), fired_(fired), prescale_(prescale), writePrescale_(writePrescale) {};

    std::string name_;
    std::string HLTname_;
    bool fired_;
    int prescale_;
    bool writePrescale_;

  };
}

#endif

