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
	*differences = vector<Point>(P.size() - solution.size());
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

void convex_hull_1(vector<Point> P, list< vector<Point> > * listSolution ){

	if(P.size() <= 3)
		return;

	int n = P.size();
	int k = 0;

	/* Se o vetor tiver apenas um elemento, retorne este elemento */
	//if (n == 1) return P;
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

	listSolution->push_back(solution);

	P = calculate_difference(P, solution);

//	printf("Tamanho da solucao: %d\n", solution.size());
//	printf("Tamanho da diferrence: %d\n", P.size());
//
//	print_solution(P);
	convex_hull_1(P, listSolution);
}

vector<Point> calculate_difference(const vector<Point> points, const vector<Point> solution){
	vector<Point> differences;

	bool found = false;
	for(int i = 0; i < points.size(); i++){
		for(int k = 0; k < solution.size(); k++){
			if((points[i].x == solution[k].x) and (points[i].y == solution[k].y)){
				found = true;
			}
		}
		if(!found){
			differences.push_back(points[i]);
		}
		found = false;
	}

	return differences;
}

vector<Point> concat_solutions(list< vector<Point> > * listSolution){
	vector<Point> contatenated;
	bool invert = false;
	 for(list< vector<Point> >::iterator list_iter = listSolution->begin(); list_iter != listSolution->end(); list_iter++){
		 vector<Point> solution = *list_iter;
		 if(invert){
			 for(int i = solution.size() -1; i>=0; i--){
				 contatenated.push_back(solution[i]);
			 }
			 invert = false;
		 }else{
			 for(int i = 0; i<solution.size(); i++){
				 contatenated.push_back(solution[i]);
			 }
			 invert = true;
		 }

	 }
	 return contatenated;

}

void print_solution(const vector<Point> points){
	for(int i = 0; i < points.size(); i++){
		printf("[%f, %f]\n", points[i].x, points[i].y);
	}
}
