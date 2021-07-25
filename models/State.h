#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>

class State {
 public:
  std::string tag;
  bool terminateState = false;

  std::string getTag() const {
    return this->tag;
  }

  int getIndex() {
    return std::stoi(this->tag);
  }

  void changeTag(std::string tag) {
    this->tag = tag;
  }

  bool operator==(const State &stateToCompare) {
    return this->tag == stateToCompare.getTag();
  }

  bool operator!=(const State &stateToCompare) {
    return this->tag != stateToCompare.getTag();
  }

  friend std::ostream &operator<<(std::ostream &stream, const State &state) {
    return stream << state.tag;
  }

  bool isTerminateState() {
    return terminateState;
  }

  State() = default;
  ~State() = default;
};

#endif
