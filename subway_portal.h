 /******************************************************************************
  Title          : subway_portal.h
  Author         : Ajani Stewart
  Created on     : April 28, 2018
  Description    : Interface file for the SubwayPortal object
  Purpose        : Encapsulates data and methods of a subway portal
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#ifndef SUBWAY_PORTAL_H_
#define SUBWAY_PORTAL_H_

#include <string>

#include "_subway_portal.h"
#include "subway_route.h"
#include "gps.h"

class SubwayPortal : public _SubwayPortal {
public:
  //delclarations of virtual functions in interface file
  SubwayPortal();
  // data_row is a single row in the csv file
  SubwayPortal( std::string data_row );

  double distance_from( double latitude, double longitude );

  std::string name() const;
  bool can_access( route_set route ) const;
  GPS p_location() const;
  GPS s_location() const;
  route_set routes() const;

  /** returns the distance between the two portals  */
  friend double distance_between( SubwayPortal portal1,
                                  SubwayPortal portal2);



  /** returns true if the two portals have the exact same set of routes  */
  friend bool same_routes( SubwayPortal portal1,
                            SubwayPortal portal2);

  /** returns true if the two portals belong to the same station */
  friend bool same_station( SubwayPortal portal1,
                            SubwayPortal portal2);

  friend ostream & operator<< ( ostream & out, SubwayPortal e);

  friend class SubwayStation;

private:
  std::string p_name;
  //based on data dictionary
  std::string division;
  std::string line;
  std::string station_name;

  double station_latitude;
  double station_longitude;

  route_set p_routes;

  std::string entrance_type;
  bool entry;
  bool exit_only;
  bool vending;
  std::string staffing;
  std::string staff_hours;
  bool ada;
  std::string ada_notes;
  bool free_crossover;
  std::string north_south_street;
  std::string east_west_street;
  std::string corner;
  int id;
  double entrance_latitude;
  double entrance_longitude;
  GPS station_location;
  GPS entrance_location;
};

#endif