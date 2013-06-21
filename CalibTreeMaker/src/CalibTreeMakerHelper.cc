#include "Calibration/CalibTreeMaker/interface/CalibTreeMakerHelper.h"

#include <boost/regex.hpp> 

unsigned int CalibTreeMakerHelper::findTrigger(const std::vector<std::string>& list, const std::string& name)
{
  boost::regex re(std::string("^(")+name+"|"+name+"_v\\d*)$");
  for (unsigned int i = 0,n = list.size() ; i < n ; ++i) {
    if(boost::regex_match(list[i],re)) return i;
  }
  return list.size();
}

CalibTreeMakerHelper::AllTriggerInfo::AllTriggerInfo(std::string name, std::string HLTname, bool fired, int prescale, bool writePrescale) : name_(name), HLTname_(HLTname), fired_(fired), prescale_(prescale), writePrescale_(writePrescale) {}
