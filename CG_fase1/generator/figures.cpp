#define _USE_MATH_DEFINES
#include "figures.h"
#include <math.h>

using namespace std;

float quadrants[8][3] = {
		{ 1,  1,  1},
		{ 1,  1, -1},
		{-1,  1, -1},
		{-1,  1,  1},
		{ 1, -1,  1},
		{ 1, -1, -1},
		{-1, -1, -1},
		{-1, -1,  1},
};

Point drawPoints(float radius, float angle, float height) {
	Point p;
	p.x = radius * sin(angle);
	p.y = height;
	p.z = radius * cos(angle);

	return p;
}

// draw cone
vector<Point> cone(float radius, float height, int slices, int layers){
	vector<Point> points;
	Point p0, p1, p2, p3;
	float teta, alpha, scaleHeigth, heigthNow, 
		scaleRadius, radiusNow, radiusNext, tetaNext;

	alpha = (2 * M_PI) / slices;
	scaleHeigth = height / layers;
	scaleRadius = radius / layers;

	//draw base
	for (int i = 0; i < slices; i++) {
		teta = i * alpha;
		tetaNext = (i + 1) * alpha; 

		p0.x = 0;
		p0.y = 0;
		p0.z = 0;
		p1 = drawPoints(radius, tetaNext, 0);
		p2 = drawPoints(radius, teta, 0);	

		points.push_back(p0);
		points.push_back(p1);
		points.push_back(p2);
	}
	
	for (int i = 0; i < layers; i++) {

		heigthNow = i * scaleHeigth;
		radiusNow = radius - i * scaleRadius;
		radiusNext = radius - (1 + i) * scaleRadius;

		for (int j = 0; j < slices; j++) {
				teta = j * alpha;
				tetaNext = (j + 1) * alpha;

				p0 = drawPoints(radiusNow, teta, heigthNow);
				p1 = drawPoints(radiusNow, tetaNext, heigthNow);
				p2 = drawPoints(radiusNext, tetaNext, heigthNow + scaleHeigth);
				p3 = drawPoints(radiusNext, teta, heigthNow + scaleHeigth);

				//draw first triangle 
				points.push_back(p0);
				points.push_back(p1);
				points.push_back(p2);

				//draw second triangle
				points.push_back(p0);
				points.push_back(p2);
				points.push_back(p3);
		}
	}
	return points;
}

void divide(float length, float width, float height, int divisions, vector<Point> pointsTriangle,vector<Point> *points) {
	Point p1 = pointsTriangle[0], p2 = pointsTriangle[1], p3 = pointsTriangle[2],
			newP1, newP2, newP3;



	float l, h, newl, newh,neww;
	newl = length / divisions;
	neww = width / divisions;
	newh = height / divisions;

	if (p1.y == p2.y && p2.y == p3.y) {
		if (p1.x >= p2.x)
			l = -newl;
		else
			l = newl;

		if (p1.z >= p3.z)
			h = -neww;
		else
			h = neww;

		p2.y = p3.y = p1.y;
		p2.x = p3.x = p1.x + l;
		p2.z = p1.z;
		p3.z = p2.z + h;

		for (int i = 0; i < divisions; i++)	{
			newP1 = p1, newP2 = p2, newP3 = p3;

			for (int j = 0; j < divisions; j++) {
				(*points).push_back(newP1);
				(*points).push_back(newP2);
				(*points).push_back(newP3);

				newP1.z += h;
				newP2.z += h;
				newP3.z += h;
			}
			p1.x += l;
			p2.x += l;
			p3.x += l;
		}
	}
	else if (p1.x == p2.x && p2.x == p3.x) {
		if (p1.z <= p2.z)
			l = neww;
		else
			l = -neww;

		if (p1.y >= p3.y)
			h = -newh;
		else
			h = newh;

		p2.x = p3.x = p1.x;
		p2.z = p3.z = p1.z + l;
		p2.y = p1.y;
		p3.y = p1.y + h;

		for (int i = 0; i < divisions; i++)	{
			newP1 = p1, newP2 = p2, newP3 = p3;

			for (int j = 0; j < divisions; j++) {
				(*points).push_back(newP1);
				(*points).push_back(newP2);
				(*points).push_back(newP3);

				newP1.y += h;
				newP2.y += h;
				newP3.y += h;
			}
			p1.z += l;
			p2.z += l;
			p3.z += l;
		}
	}
	else if (p1.z == p2.z && p2.z == p3.z) {
		if (p1.x < p2.x)
			l = newl;
		else
			l = -newl;

		if (p1.y < p3.y)
			h = newh;
		else
			h = -newh;

		p2.z = p3.z = p1.z;
		p2.x = p3.x = p1.x + l;
		p2.y = p1.y;
		p3.y = p2.y + h;

		for (int i = 0; i < divisions; i++) {
			newP1 = p1, newP2 = p2, newP3 = p3;

			for (int j = 0; j < divisions; j++){
				(*points).push_back(newP1);
				(*points).push_back(newP2);
				(*points).push_back(newP3);

				newP1.y += h;
				newP2.y += h;
				newP3.y += h;
			}
			p1.x += l;
			p2.x += l;
			p3.x += l;
		}
	}
}

//draw box
vector<Point> box(float length, float width, float height, int divisions) {
	vector<Point> points;
	int tam = 36;
	vector<Point> pointsTriangle(3);

	int faces[36] =
	{
		4,7,6,6,5,4,
		1,0,4,4,5,1,
		3,2,6,6,7,3,
		1,2,3,3,0,1,
		2,1,5,5,6,2,
		0,3,7,7,4,0,	
	};

	for (int i = 0, j = 0; i < tam; i++)
	{
		Point p;
		int f = faces[i];

		p.x = length / 2 * quadrants[f][0];
		p.y = height / 2 * quadrants[f][1];
		p.z = width / 2 * quadrants[f][2];

		if (divisions > 1)
		{
			if (j == 3)
			{
				divide(length, width, height, divisions, pointsTriangle,&points);
				j = 0;
			}
			pointsTriangle[j++] = p;

			if (i + 1 == tam)
				divide(length, width, height, divisions, pointsTriangle,&points);
		}
		else
			points.push_back(p);
	}
	return points;
}


Point pointsSphere (float radius, float beta, float alpha)
{
    Point result;
    
    result.x = radius * sin(alpha) * cos(beta);
    result.y = radius * sin(beta);
    result.z = radius * cos(beta) * cos(alpha);
    
    return result;
}

//draw sphere
vector<Point> sphere(float radius, int slices, int layers)
{
	Point p1, p2, p3, p4;
	vector<Point> points;
	float alpha, nextAlpha,
		beta, nextBeta;

	for (int i = 0; i < layers; i++)
	{
		beta = i * (M_PI / layers) - M_PI_2;
		nextBeta = (i + 1) * (M_PI / layers) - M_PI_2;

		for (int j = 0; j < slices; j++)
		{
			alpha = j * 2 * M_PI / slices;
			nextAlpha = (j + 1) * 2 * M_PI / slices;

			p1 = pointsSphere(radius, nextBeta, alpha);
			p2 = pointsSphere(radius, beta, alpha);
			p3 = pointsSphere(radius, nextBeta, nextAlpha);
			p4 = pointsSphere(radius, beta, nextAlpha);

			// First triangle
			points.push_back(p1);
			points.push_back(p2);
			points.push_back(p3);

			// Second triangle
			points.push_back(p3);
			points.push_back(p2);
			points.push_back(p4);
		}
	}
	return points;
}

//draw plane
vector<Point> plane(float size)
{
	Point pt;
	vector<Point> points;

	int face[6] = { 0, 1, 3, 3, 1, 2 };

	for (int i = 0, j; i < 6; i++)
	{
		j = face[i];
		pt.x = size * quadrants[j][0];
		pt.y = 0;
		pt.z = size * quadrants[j][2];

		points.push_back(pt);
	}
	return points;
}

//draw cylinder
vector<Point> cylinder(float radius, float height, int slices, int layers){
	vector<Point> points;
	Point p0, p1, p2, p3;
	float teta, alpha, scaleHeigth, heigthNow, tetaNext;

	alpha = (2 * M_PI) / slices;
	scaleHeigth = height / layers;

	//draw base
	for (int i = 0; i < slices; i++) {
		teta = i * alpha;
		tetaNext = (i + 1) * alpha;

		p0.x = 0;
		p0.y = 0;
		p0.z = 0;
		p1 = drawPoints(radius, tetaNext, 0);
		p2 = drawPoints(radius, teta, 0);

		points.push_back(p0);
		points.push_back(p1);
		points.push_back(p2);
	}

	for (int i = 0; i < layers; i++) {

		heigthNow = i * scaleHeigth;

		for (int j = 0; j < slices; j++) {
			teta = j * alpha;
			tetaNext = (j + 1) * alpha;

			p0 = drawPoints(radius, teta, heigthNow);
			p1 = drawPoints(radius, tetaNext, heigthNow);
			p2 = drawPoints(radius, tetaNext, heigthNow + scaleHeigth);
			p3 = drawPoints(radius, teta, heigthNow + scaleHeigth);

			//draw first triangle
			points.push_back(p0);
			points.push_back(p1);
			points.push_back(p2);

			//draw second triangle
			points.push_back(p0);
			points.push_back(p2);
			points.push_back(p3);
		}
	}
	
	//draw topo
    for (int i = 0; i < slices; i++) {
        teta = i * alpha;
        tetaNext = (i + 1) * alpha;

        p0.x = 0;
        p0.y = height;
        p0.z = 0;
        p1 = drawPoints(radius, tetaNext, height);
        p2 = drawPoints(radius, teta, height);

        points.push_back(p0);
        points.push_back(p2);
        points.push_back(p1);
    }
	return points;
}

