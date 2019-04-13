/******************************************************************************
  Title          : gps.cpp
  Author         : Ajani Stewart
  Created on     : April 6, 2019
  Description    : The implementation of the gps class
  Purpose        :
  Usage          :
  Build with     :
  Modifications  : -lm
  

******************************************************************************/

#include <iostream>
#include <cmath>

#include "gps.h"

//radius of the earth in km
const double R = 6372.8;

//conversion of degrees to rads
const double TO_RAD = M_PI / 180.0;

GPS::GPS(double lon = 0, double lat = 0) throw (BadPoint) {
  if (lon > 180 || lon < -180 || lat > 90 || lat < -90)
    throw BadPoint();

  longitude = lon;
  latitude = lat;
}

GPS::GPS(const GPS& location) throw (BadPoint) {
  if (location.longitude > 180 || location.longitude < -180 ||
      location.latitude > 90 || location.latitude < -90)
    throw BadPoint();

  longitude = location.longitude;
  latitude  = location.latitude;
}

void GPS::operator=(const GPS& location) {
  longitude = location.longitude;
  latitude = location.latitude;
}

//Calculate distance on a sphere using Haversine Formula
double distance_between(GPS point1, GPS point2) {
  double lat1 = point1.latitude * TO_RAD;
  double lat2 = point2.latitude * TO_RAD;
  double lon1 = point1.longitude * TO_RAD;
  double lon2 = point2.longitude * TO_RAD;

  double dLat = (lat2 - lat1) / 2;
  double dLon = (lon2 - lon1) / 2;

  double a = sin(dLat);
  double b = sin(dLon);

  return 2 * R * asin(sqrt(a*a + cos(lat1) * cos(lat2) * b*b));
}

std::ostream& operator<<(std::ostream& out, GPS point) {
  out << "(" << point.latitiude << " " << point.longitude << ")";
}
