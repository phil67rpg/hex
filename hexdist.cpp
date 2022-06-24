#include <iostream>
#include <math.h>

using namespace std;

class Point
{
public:
	float x = 0.0f;
	float y = 0.0f;
};

int ComputeDistanceHexGrid(const Point & A, const Point & B);

int main()
{
	Point pointA;
	Point pointB;
	
	pointA.x = 0;
	pointA.y = 0;
	pointB.x = 1;
	pointB.y = -1;

	cout << ComputeDistanceHexGrid(pointA,pointB);
	
	return 0;
}

int ComputeDistanceHexGrid(const Point & A, const Point & B)
{
	Point distance;
	distance.x = A.x - B.x;
	distance.y = A.y - B.y;
	Point diagonalMovement;
	int lesserCoord = abs(distance.x) < abs(distance.y) ? abs(distance.x) : abs(distance.y);
	diagonalMovement.x = (distance.x < 0) ? -lesserCoord : lesserCoord;
	diagonalMovement.y = (distance.y < 0) ? -lesserCoord : lesserCoord;
	Point straightMovement;
	straightMovement.x = distance.x - diagonalMovement.x;
	straightMovement.y = distance.y - diagonalMovement.y;
	size_t straightDistance = abs(straightMovement.x) + abs(straightMovement.y);
	size_t diagonalDistance = abs(diagonalMovement.x);
	if ((diagonalMovement.x < 0 && diagonalMovement.y>0) || (diagonalMovement.x > 0 && diagonalMovement.y < 0))
	{
		diagonalDistance *= 2;
	}
	return straightDistance + diagonalDistance;
}