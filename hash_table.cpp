#include <vector>
#include <iostream>

#include "hash_table.h"
#include "_hash_item.h"

HashTable::HashTable() : current_size(0) {
  hash_table.resize(INITIAL_SIZE);
  for (int i = 0; i < hash_table.size(); ++i) {
    __ItemType temp;
    data_t t = { EMPTY, temp };
    hash_table[i] = t;
  }
}

HashTable::HashTable(int init_size) : current_size(0) {
  hash_table.resize(get_next_prime(init_size));
  for (int i = 0; i < hash_table.size(); ++i) {
    __ItemType temp;
    data_t t { EMPTY, temp };
    hash_table[i] = t;
  }
}

int HashTable::find_position(__ItemType& item) const {
  int collision_num = 0;
  int current_pos = item.code() % hash_table.size();

  while (hash_table[current_pos].state != EMPTY && !(hash_table[current_pos].item == item)) {
    current_pos += 2 * ++collision_num - 1;

    if (current_pos >= hash_table.size())
      current_pos -= hash_table.size();
  }
  //either the item was found or it encountered a cell with an EMPTY state
  return current_pos;
}

int HashTable::insert(__ItemType item) {
  int current_pos = find_position(item);
  if (hash_table[current_pos].state == ACTIVE)
    return 0;

  data_t t = {ACTIVE, item}; 
  hash_table[current_pos] = t;
  ++current_size;

  if (current_size > hash_table.size() / 2)
    rehash();

  return 1;
  
}

int HashTable::find(__ItemType& item) const {
  int current_pos = find_position(item);

  return hash_table[current_pos].state == ACTIVE ? 1 : 0;
}

int HashTable::remove(__ItemType item) {
  int current_pos = find_position(item);

  if (hash_table[current_pos].state == ACTIVE) {
    hash_table[current_pos].state = DELETED;
    --current_size;
    return 1;
  } else
    return 0;
}

int HashTable::size() const {
  return current_size;
}

int HashTable::listall (std::ostream& os) const {
  int num = 0;
  for (int i = 0; i < hash_table.size(); ++i) {
    if (hash_table[i].state == ACTIVE) {
      os << "item: "<< hash_table[i].item << " key: " << i << "\n";
      num++;
    }
  }
  return num;
}

//very ineffeicent primality testing
bool is_prime(int n) {
  for (int i = 2; i < n * n; ++i)
    if (n % i == 0)
      return false;
  return true;
}

int HashTable::get_next_prime(int n) {
  int start = n + 1;
  while (true) {
    if (is_prime(start))
      return start;
    start++;
  }
}

void HashTable::rehash() {
  int new_size = get_next_prime(2 * hash_table.size());
  std::vector<data_t> new_hash_table;
  new_hash_table.resize(new_size);

  for (auto& element : hash_table) {
    if (element.state == ACTIVE) {
      int current_pos = find_position(element.item);
      data_t t = {ACTIVE, element.item}; 
      new_hash_table[current_pos] = t;
    }
  }
  hash_table = new_hash_table;
}
  


    
