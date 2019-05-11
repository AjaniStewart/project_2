 /******************************************************************************
  Title          : subway_station.h
  Author         : Ajani Stewart
  Created on     : April 30, 2018
  Description    : Interface file for the SubwayStation object
  Purpose        : Encapsulates data and methods of a subway station
  Usage          :
  Build with     :
  Modifications  : overloaded streaming operator

******************************************************************************/

#ifndef SUBWAY_STATION_H_
#define SUBWAY_STATION_H_

#include <string>
#include <list>
#include <set>
#include <iostream>

#include "subway_portal.h"
#include "subway_route.h"

#define DISTANCE_THRESHOLD 0.32

class SubwayStation {
public:
  /** default constructor
   *  initializes all private members with suitable defaults
   */
  SubwayStation();

  /** parameterized constructor that creates a SubwayStation object
   *  from a portal
   *  it makes the portal the embedded portal
   */
  SubwayStation( SubwayPortal portal );

  /** set_parent() sets the parent id of the station
   *  @param int [in] the id of the parent
   */
  void set_parent( int new_parent );

  /** add_child() adds a new child to the station's list of children
   *  @param int [int] the index of the child
   */
  void add_child( int new_child );

  /** add_children adds a list of children to the station's list of children
   *  @param list<int> list of indicies of children
   */
  void add_children( std::list<int>children );

  /** A friend function that determines when two stations are connected
   *  @param SubwayStation [in] s1
   *  @param SubwayStation [in] s2
   *  @return bool true if is connected based on heuristic
   */
  friend bool connected( SubwayStation s1, SubwayStation s2 );

  /** add_station_name() adds a new name to station
   *  does not add a name if it already exists
   *  @param string [in] name to be added
   *  @return 1 if name is added, 0 if not
   */
  int add_station_name( std::string name );

  /** names() returns a list of the names of the station as a list of strings*/
  std::list<std::string> names() const;

  //primary_name() returns the first station name in the list of names
  std::string primary_name() const;

  //parent_id is the index in the array of the parent of this station
  int parent_id() const;

  //portal_list returns a list of the ids in the list of the portals in this station set
  std::list<int> portal_list() const;

  //returns the name of the embedded portal
  std::string portal_name() const;

  //returns the embedded portal
  void get_portal( SubwayPortal& portal ) const;

  friend std::ostream& operator<<( std::ostream& out, SubwayStation s);

private:
  int m_parent_id;
  std::set<std::string> station_names;
  std::list<int> children;
  std::string m_portal_name;
  SubwayPortal portal;
  std::string m_primary_name;
};

#endif //SUBWAY_STATION_H_