/******************************************************************************
  Title          : hash_table.h
  Author         : Ajani Stewart
  Created on     : April 12, 2019
  Description    : Defines a hash table class
  Purpose        : 
  Usage          :
  Build with     : 
  Modifications  : overloads find


******************************************************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>

#include "_hash_table.h"
#include "_hash_item.h"


class HashTable : public __HashTable {

public:
  
  //default constructor for hash table
  //defaults the size of the hash table to the constant INITIAL_SIZE
  HashTable();

  //parameterized constructor for hash_table
  //initializes the size of the hash table to init_size
  //actual size will be the smallest prime number greater than or equal to init_size
  HashTable(int init_size);

   /** find() searches in table for given item
     *  @precondition: item's key value is initialized
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  ItemType [in,out] item : item to search for
     *  @return int 0 if item is not in table, and 1 if it is
     */

  int find (__ItemType& item) const;

   /** insert() inserts the given item into the table
     *  @precondition: item is initialized
     *  @postcondition: if item is not in table already, it is inserted
     *  @param  ItemType [in] item : item to insert
     *  @return int 0 if item is not inserted in table, and 1 if it is
     */
  
  /** find() searches in table for given string
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  string [in] s : string to search for
     *  @return int -1 if item is not in table, and position of the associated value of s if it is
     */
  int find ( std::string s ) const;

  int insert (__ItemType item);

   /** remove() removes the specified  item from the table, if it is there
     *  @precondition: item's key is initialized
     *  @postcondition: if item was in table already, it is removed
     *  @param  ItemType [in] item : item to remove
     *  @return int 0 if item is not removed from the table, and 1 if it is
     */

  int remove (__ItemType item);

  /** size() returns the number of items in the table
     *  @precondition: none
     *  @postcondition: none
     *  @return int the number of items in the table
     */

  int size() const;

  /** listall() lists all items currently in the table
     *  @note   This function writes each item in the tabel onto the given stream.
     *          Items should be written one per line, in whatever format the
     *          underlying _ItemType output operator formats them.
     *  @param  ostream [in,out] the stream onto which items are written
     *  @return int the number of items written to the stream
     */

  int listall (std::ostream& os) const;

private:

  enum States { ACTIVE, EMPTY, DELETED };

  struct data_t {
    States state;
    __ItemType item;
  };

  //This implementation will use quadratic probing
  
  std::vector<data_t> hash_table;

  //the number of items in the table
  size_t current_size;

  //gets the smallest prime number that is greater than n
  int get_next_prime(int n);

  //doubles the size of the hash table
  //and rehashes the table
  void rehash();

  
  //find where the item WOULD be in the hash table
  int find_position(__ItemType& item) const;

  //used for lazy deletion
  
};

#endif //HASH_TABLE_H
  
  
