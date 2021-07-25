#ifndef TRANSITION_H
#define TRANSITION_H

#include "State.h"
#include <string>
#include <utility>

class Transition {
 private:

  State *begin;
  State *end;
  std::string caracter;

 public:
  Transition(State *&begin, State *&end, std::string caracter) : begin(begin), end(end), caracter(std::move(caracter)) {};

  State *get_begin() {
    return this->begin;
  }

  State *get_end() {
    return this->end;
  }

  std::string get_caracter() {
    return this->caracter;
  }

  void swap() {
    if (this->begin == this->end) {
      return;
    }

    State *alt;
    alt = this->begin;
    this->begin = this->end;
    this->end = alt;
  }
};

#endif
