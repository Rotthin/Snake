#include "point.hpp"

bool Point::isOverlapping(Point b){
	return 	x == b.x && y == b.y;
}