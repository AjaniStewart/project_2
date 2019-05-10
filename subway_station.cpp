 /******************************************************************************
  Title          : subway_station.cpp
  Author         : Ajani Stewart
  Created on     : May 2, 2018
  Description    : implementation file for the SubwayStation object
  Purpose        : Encapsulates data and methods of a subway station
  Usage          :
  Build with     : -std=c++11
  Modifications  :  added overloading streaming operator, add_children

******************************************************************************/

#include <algorithm>

#include "subway_station.h"
#include "subway_portal.h"

SubwayStation::SubwayStation() : m_parent_id(-1), m_portal_name("") { }

SubwayStation::SubwayStation( SubwayPortal p ) : m_parent_id(-1),
                m_portal_name( p.p_name ), portal(p) {
  station_names.insert( p.station_name );
  m_primary_name = p.station_name;
}

//the station is in the middle of a messy divorce
//hopefully it can get past this
//it just wants a happy family
//play with its mom and dad
//but its mom is a drug addict and its dad cant take it anymore
//the dad won custody
//but the mom shows up from time to time
//mostly to bum money from the station under the pretext that shes changed
//she never changed
void SubwayStation::set_parent( int new_parent ) {
  m_parent_id = new_parent;
}

void SubwayStation::add_child( int new_child ) {
  children.push_back( new_child );
}

void SubwayStation::add_children( std::list<int> new_children ) {
  std::for_each(new_children.begin(), new_children.end(), [&](int child) {
    children.push_back(child);
  });
}

int SubwayStation::add_station_name( std::string name ) {
  if ( station_names.size() == 0) { m_primary_name = name; }
  size_t cur_size = station_names.size();
  station_names.insert( name );
  return cur_size != station_names.size();
}

std::list<std::string> SubwayStation::names() const {
  std::list<std::string> name_list;
  for ( auto it = station_names.begin(); it != station_names.end(); ++it ) {
    name_list.push_back(*it);
  }

  return name_list;
}

std::string SubwayStation::primary_name() const {
  return m_primary_name; 
}

int SubwayStation::parent_id() const {
  return m_parent_id;
}

std::list<int> SubwayStation::portal_list() const {
  return children;
}

std::string SubwayStation::portal_name() const {
  return m_portal_name;
}

void SubwayStation::get_portal( SubwayPortal& p ) const {
  p = portal;
}

bool connected( SubwayStation s1, SubwayStation s2 ) {
  return same_routes( s1.portal, s2.portal ) &&
         distance_between( s1.portal, s2.portal ) <= DISTANCE_THRESHOLD;
}

std::ostream& operator<<( std::ostream& out, SubwayStation s) {
  std::for_each(s.station_names.begin(), s.station_names.end(), [&](const std::string& s) {
    out << s;
  });
  return out;
}