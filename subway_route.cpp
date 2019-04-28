/******************************************************************************
  Title          : subway_routes.cpp
  Author         : Ajani Stewart
  Created on     : April 27, 2019
  Description    : implementqtion file for the SubwayRoute object
  Purpose        : Encapsulates data and methods of a set of subway routes
  Usage          :
  Build with     : -std=c++11
  Modifications  :

******************************************************************************/

#include <stdexcept>

#include "subway_route.h"



/*******************************************************************************
 *                    Functions related to subway routes                        *
 ******************************************************************************/

void to_upper( std::string& s) {
  for (char& element : s) {
    element = toupper(element);
  }
}  

bool is_route_id( std::string s ) {
  to_upper(s);

  if (s == "FS" || s == "GS")
    return true;

  return ( (s.c_str()[0] >= 'A' && s.c_str()[0] <= 'Z') ||
           (s.c_str()[0] >= '1' && s.c_str()[0] <= '7') );
}

std::string str_from_routeset( route_set s ) {
  std::string routes("");

  for (int i = 1; i < 36; ++i) {
    if ((s & 1) == 1) {
      routes += int2route_id(i) + " ";
    }
    s = s >> 1;
  }

  return routes;
}

//maps number trains to themselves e.g. 1 train = 1
//FS = 8
//GS = 9
//letter trains start with a = 10
//invalid strings get -1
int routestring2int( std::string s ) {
  to_upper(s);

  if (is_route_id(s)) {
    if (s == "FS") { return 8; }
    else if (s == "GS") { return 9; }
    else {
      try {
        return std::stoi(s);
      } 
      catch (const std::invalid_argument& e) {
        return static_cast<int>(*(s.c_str())) - 55;
      }
    }
  } else {
    return -1;
  } 
}

//inverse of above

std::string int2route_id ( int k ) {
  if (k >= 1 && k <= 7) { return std::to_string(k); }
  else if (k == 8) { return "FS"; }
  else if (k == 9) { return "GS"; }
  else { return std::string(1, static_cast<char>(k + 55)); }
}

SubwayRoute::SubwayRoute() { }

std::list<int> SubwayRoute::station_list() const {
  return stations;
}

void SubwayRoute::add_station_to_route( int station_id ) {
  stations.push_back(station_id);
}

route_set SubwayRoute::get_routeset() const {
  return routes;
}