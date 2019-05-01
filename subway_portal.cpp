 /******************************************************************************
  Title          : subway_portal.cpp
  Author         : Ajani Stewart
  Created on     : April 29, 2018
  Description    : Implementation file for the SubwayPortal object
  Purpose        : Encapsulates data and methods of a subway portal
  Usage          :
  Build with     : c++11
  Modifications  :

******************************************************************************/

#include <string>
#include <vector>
#include <cctype>

#include "subway_portal.h"
#include "subway_route.h"

typedef std::vector<std::string> string_array;

SubwayPortal::SubwayPortal() { }


//splits a string on a specified 
string_array split( std::string s, char delimiter = ',' ) {
  string_array string_vector;
  std::string current_string = "";
  for ( size_t i = 0; i < s.size(); ++i ) {
    if (s[i] != delimiter) {
      current_string += s[i];
    } else {
      string_vector.push_back(current_string);
      current_string = "";
    }
  }
  return string_vector; 
}

//removes excessive whitespace in string
//e.g. "hello          world!" -> "hello world!"

std::string munch_whitespace(std::string s) {
    std::string result = "";
    for (size_t i = 0; i < s.size(); ++i) {
        if (isspace(s[i])) {
            result += " ";
            ++i;
            while (isspace(s[i])) ++i;
            --i;
        } else
            result += s[i];
    }       
    return result;   
}

SubwayPortal::SubwayPortal( std::string data_row ) {
  string_array data_vector = split(data_row);

  division = data_vector[0];
  line = data_vector[1];
  station_name = data_vector[2];

  station_latitude = std::stod(data_vector[4]);
  station_latitude = std::stod(data_vector[5]);

  p_routes = 0;
  //sets the relevant bits
  //least significant bit is 1 - train
  //35th lesat significant bit (or 29th most significant bit) is z train
  for ( int i = 6; i < 17; ++i ) {
    if ( data_vector[i] != "" ) {
      int k = routestring2int(data_vector[i]);
      p_routes = p_routes | (1 << (k - 1));
    }
  }

  entrance_type = data_vector[17];
  entry = (data_vector[18] == "YES");
  exit_only = (data_vector[19] == "YES");
  vending = (data_vector[20] == "YES");

  staffing = data_vector[21];
  ada = (data_vector[22] == "TRUE");
  ada_notes = data_vector[23];
  free_crossover = (data_vector[24] == "TRUE");

  north_south_street = data_vector[25];
  east_west_street = data_vector[26];
  corner = data_vector[27];
  id = std::stoi(data_vector[28]);

  entrance_latitude = std::stod(data_vector[29]);
  entrance_longitude = std::stod(data_vector[30]);
  
  station_location = GPS( station_longitude, station_latitude );

  entrance_location = GPS( entrance_longitude, entrance_latitude );

  p_name = munch_whitespace(north_south_street + "," + east_west_street + "," + corner + "," + to_string(id));
}

double SubwayPortal::distance_from( double latitude, double longitude )  {
  return distance_between(entrance_location, GPS(longitude,latitude));
}

std::string SubwayPortal::name() const  {
  return p_name;
}

bool SubwayPortal::can_access( route_set route ) const {
  return (p_routes & route) != 0;
}

GPS SubwayPortal::p_location() const  {
  return entrance_location;
}

GPS SubwayPortal::s_location() const  {
  return station_location;
}

route_set SubwayPortal::routes() const {
  return p_routes;
}

double distance_between( SubwayPortal p1, SubwayPortal p2 ) {
  return p1.distance_from( p2.entrance_latitude, p2.entrance_longitude );
}

bool same_routes( SubwayPortal p1, SubwayPortal p2 ) {
  return p1.p_routes == p2.p_routes;
}

bool same_station( SubwayPortal p1, SubwayPortal p2 ) {
  return p1.station_name == p2.station_name;
}