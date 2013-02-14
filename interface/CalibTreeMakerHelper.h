#ifndef CALIBTREEMAKERHELPER_H

#include <vector>
#include <string>

namespace CalibTreeMakerHelper {
  unsigned int findTrigger(const std::vector<std::string>& list, const std::string& name);

  class AllTriggerInfo{
  public:
    AllTriggerInfo(std::string name, std::string HLTname, bool fired, int prescale, bool writePrescale=false);
      
  private:
      std::string name_;
      std::string HLTname_;
  public:
      bool fired_;
      int prescale_;
      
      std::string name()        const {return name_;}                 //!< Return name used for branch
      std::string HLTname()     const {return HLTname_;}              //!< Return HLT name of trigger 
      bool writePrescale()      const {return writePrescale_;}        //!< Return whether prescale should be saved in n-tuple
  private:
      bool writePrescale_;
      
  };
}

#endif

