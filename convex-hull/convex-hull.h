/*
 * convex-hull.h
 *
 *  Created on: 29 de abr de 2017
 *  Author: Maikon Igor
 *
 * Implementation of Andrew's monotone chain 2D convex hull algorithm.
 * Asymptotic complexity: O(n log n).
 * Practical performance: 0.5-1.0 seconds for n=1000000 on a 1GHz machine.
 *
 * REFERENCES:
 *
 * Algorithm Implementation/Geometry/Convex hull/Monotone chain
 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
 *
 * Algoritmo Monotone Chain - Fecho Convexo
 * https://www.youtube.com/watch?v=LTCt81qAEnE&t=462s
 */

#ifndef CONVEX_HULL_H_
#define CONVEX_HULL_H_

#include <algorithm>
#include <vector>
#include <list>

using namespace std;

typedef double coord_t; // coordinate type
typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};


/*
 * 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
 * Returns a positive value, if OAB makes a counter-clockwise turn,
 * negative for clockwise turn, and zero if the points are collinear.
 */
coord2_t cross(const Point &O, const Point &A, const Point &B);

/*
 * Retorna a lista de pontos do fecho convexo no sentido anti-horário
 */
vector<Point> convex_hull(vector<Point> P, vector<Point> * differences);

void convex_hull_1(vector<Point> P, list< vector<Point> > * listSolution );

vector<Point> calculate_difference(const vector<Point> points, const vector<Point> solution);

void print_solution(const vector<Point> points);

vector<Point> concat_solutions(list< vector<Point> > * listSolution);

#endif /* CONVEX_HULL_H_ */
