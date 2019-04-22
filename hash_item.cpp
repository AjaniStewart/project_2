/******************************************************************************
  Title          : hash_item.cpp
  Author         : Ajani Stewart
  Created on     : March 31, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     :
  Modifications  :
******************************************************************************/

#include <string>
#include <iostream>

#include "_hash_item.h"

__ItemType::__ItemType() {
  name = "";
  position = -1;
}

void __ItemType::set(std::string s, int pos) {
  name = s;
  position = pos;
}

void __ItemType::get(std::string& s, int& pos) {
  s = name;
  pos = position;
}

bool __ItemType::operator==(__ItemType rhs) const {
  return rhs.name != "" && name == rhs.name;
}

//Credit to Stewart weiss
unsigned int encode (const int RADIX, const std::string& s) {
  unsigned int hashval = 0;
  for (int i = 0; i < s.length(); ++i)
    hashval = s[i] + RADIX * hashval; //p(x) = s_i + x(q(x))
  return hashval;
}

unsigned int __ItemType::code() {
  if (name != "")
    return encode(26, name);
  else
    return 0;
}

std::ostream& operator<<(std::ostream& os, __ItemType item) {
  os << "name: " << item.name << " position: " << item.position << "\n";
  return os;
}
