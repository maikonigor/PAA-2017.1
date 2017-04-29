/*
 * main.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: maikon
 */

#include "convex-hull.h"
#include <stdio.h>

int main(){

	/*
	 * Creating test points.
	 * NOTE: they should to be generated ramdomicaly
	 */
	vector<Point> points(11);
	Point p;

	p.x = 1; p.y = 9;
	points[0] = p;

	p.x = 2; p.y = 6;
	points[1] = p;

	p.x = 8; p.y = 0;
	points[2] = p;

	p.x = 0; p.y = 0;
	points[3] = p;


	p.x = 0; p.y = 11;
	points[4] = p;

	p.x = 7; p.y = 9;
	points[5] = p;

	p.x = 6; p.y = 6;
	points[6] = p;

	p.x = 7; p.y = 1;
	points[7] = p;

	p.x = 3; p.y = 2;
	points[8] = p;

	p.x = 1; p.y = 1;
	points[9] = p;

	p.x = 8; p.y = 10;
	points[10] = p;



	vector<Point> solution = convex_hull(points);
	for (unsigned i = 0; i < solution.size(); i++) {
	            Point ps = solution[i];
	            printf("%f , %f\n",ps.x, ps.y);
	}
	return 0;
}




