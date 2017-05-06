/*
 * convex-hull.cpp
 *
 *  Created on: 29 de abr de 2017
 *  Author: Maikon Igor
 */


#include "convex-hull.h"
#include<stdio.h>
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P, vector<Point> * differences)
{
	int n = P.size();
	int k = 0;

	/* Se o vetor tiver apenas um elemento, retorne este elemento */
	if (n == 1) return P;
	vector<Point> solution(2*n);

	// Ordena os pontos lexicographically
	sort(P.begin(), P.end());

	// Construir a borda inferior
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(solution[k-2], solution[k-1], P[i]) <= 0){
          k--;
		}
		solution[k++] = P[i];
	}

	// Constroi a borda superior
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(solution[k-2], solution[k-1], P[i]) <= 0) {
                k--;
		}
		solution[k++] = P[i];
	}

	solution.resize(k-1);

	//calculate the difference between solution and original points
	vector<Point> sortedPoints(P);
	vector<Point> sortedSolution(solution);

	sort(sortedPoints.begin(), sortedPoints.end());
	sort(sortedSolution.begin(), sortedSolution.end());

	set_symmetric_difference(sortedPoints.begin(), sortedPoints.end(),
                            sortedSolution.begin(), sortedSolution.end(),
                          back_inserter(*differences)
                          );


	return solution;
}
