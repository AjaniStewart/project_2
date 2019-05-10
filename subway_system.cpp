/******************************************************************************
  Title          : subway_system.cpp
  Author         : Ajani Stewart
  Created on     : May 5, 2019
  Description    : implementation file for the SubwaySystem object
  Purpose        : Encapsulates data and methods of a subway system
  Usage          :
  Build with     : -std=c++11
  Modifications  :

******************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>

#include "subway_system.h"
#include "subway_portal.h"
#include "subway_station.h"
#include "_hash_item.h"
#include "gps.h"

typedef __ItemType item_t;

SubwaySystem::SubwaySystem() : number_of_portals(0) {
  for (int i = 0; i < MAX_ROUTES; ++i)
    route_masks[i].routes = (1 << i);
}

int SubwaySystem::add_portal( SubwayPortal portal ) {
  item_t p;
  p.set(portal.p_name, number_of_portals);
  int result = portal_hash.insert(p);
  if (0 == result) {
    return 0;
  } else {
    stations.push_back( SubwayStation( portal ) );

    //add station routes to route mask
    for ( int i = 0; i < MAX_ROUTES; ++i )
      if ( portal.p_routes & (1 << i) )
        route_masks[i].add_station_to_route( number_of_portals );

    ++number_of_portals;
    return 1;
  }
}

void SubwaySystem::list_all_stations( std::ostream& out ) const {
  station_hash.listall( out );
}

void SubwaySystem::list_all_portals( std::ostream& out, std::string station_name ) const {
  int position = portal_hash.find( station_name );
  SubwayStation s = stations[position];

  std::for_each(s.names().begin(), s.names().end(), [&]( const std::string& name ) {
    out << name;
  });
}

void SubwaySystem::list_stations_of_route( std::ostream& out, route_id route ) const {
  auto station_list = route_masks[ routestring2int( route ) - 1 ].station_list();
  
  std::for_each(station_list.begin(), station_list.end(), [&]( int index ) {
    out << stations[index];
  });
}

int SubwaySystem::form_stations() {
  // i need to combine stations that are connected into one set
  // i need to add the children of the roots of the set to the parents
  // then hash the roots in station_hash
  //naive method


  for ( size_t i = 0; i < stations.size() - 1; ++i ) {
    int root = find_station(i);

    for ( size_t j = i + 1; j < stations.size(); ++j ) {
      int root2 = find_station(j);
      if (connected(stations[root], stations[root2])) {
        union_stations(root, root2);
      }
    }
  }

  //add the children
  for ( size_t i = 0; i < stations.size(); ++i ) {
    if (stations[i].parent_id() > 0) {
      int root = find_station(i);
      stations[root].add_child(i);
    }
  }

  //add station names
  for (size_t i = 0; i < stations.size(); ++i) {
    if ( stations[i].parent_id() < 0 ) {
      const auto& p_list = stations[i].portal_list();

      std::for_each( p_list.begin(), p_list.end(), [&](int j) {
        if ( stations[j].primary_name() != "" )
          stations[i].add_station_name( stations[j].primary_name() );
      });
    }
  }

  //hashing disjoint stations
  int num_disjoint_sets = 0;
  for(size_t i = 0; i < stations.size(); ++i) {
    if ( stations[i].parent_id() < 0 ) {
      ++num_disjoint_sets;
      item_t s;
      auto name_list = stations[i].names();
      std::for_each(name_list.begin(), name_list.end(), [&](const std::string& name) {
        s.set(name, i);
        station_hash.insert(s);
      });
    }
  }
  return num_disjoint_sets;
}

bool SubwaySystem::get_portal( std::string name_to_find, SubwayPortal& portal ) const {
  int position = portal_hash.find( name_to_find );
  
  if ( -1 == position ) {
    return false;
  } else {
    stations[ position ].get_portal( portal );
    return true;
  }
}

SubwayPortal SubwaySystem::find_nearest_portal( double latitude, double longitude ) const {
  GPS point { latitude, longitude };
  double min_distance = 1000000;
  SubwayPortal nearest_p;
  for (size_t i = 0; i < stations.size(); ++i) {
    SubwayPortal cur_portal;
    stations[i].get_portal(cur_portal);
    double distance = distance_between(cur_portal.p_location(), point);
    if (distance < min_distance) {
      min_distance = distance;
      nearest_p = cur_portal;
    }
  }
  return nearest_p;
}

std::string SubwaySystem::nearest_portal( double latitude, double longitude ) const {
  return find_nearest_portal( latitude, longitude ).p_name;
}

std::string SubwaySystem::nearest_routes( double latitude, double longitude ) const {
  SubwayPortal p = find_nearest_portal( latitude, longitude );
  return str_from_routeset( p.routes() );
}

//credit to Mark Allen Weiss for union/find algorithms
int SubwaySystem::find_station( int index ) {
  if ( stations[index].parent_id() < 0 )
    return index;
  else {
    int temp = find_station( stations[index].parent_id() );
    stations[index].set_parent( temp );
    return temp;
  }
}

void SubwaySystem::union_stations( int s1, int s2 ) {
  if ( s1 != s2 ) {
    // s2 is deeper
    if ( stations[s2].parent_id() < stations[s1].parent_id() ) {
      stations[s2].set_parent( stations[s1].parent_id() + stations[s2].parent_id() );
      stations[s1].set_parent( s2 );
      //add station_names

      // auto names = stations[s1].names();
      // std::for_each( names.begin(), names.end(), [&](const std::string& ) {
      //   stations
      // });
    } else {
      stations[s1].set_parent( stations[s2].parent_id() + stations[s1].parent_id() );
      stations[s2].set_parent( s1 );
    }
  }
}
