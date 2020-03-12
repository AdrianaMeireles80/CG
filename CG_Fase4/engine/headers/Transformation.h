#ifndef TRANFORMATION_TRANSFORMATION_H
#define TRANFORMATION_TRANSFORMATION_H
#include <string>
#include "Point.h"
#include <vector>


using namespace std;

class Transformation
{
    private:
        vector<Point*> controlPoints;
        string type;
	    bool deriv;
        float angle;
	    float time;
        vector<Point*> pointsCurve;
        float x;
        float y;
        float z;
        float vetor[4]={1,0,0};

    public:
        Transformation();
        Transformation(string typeT, float a, float xx, float yy, float zz);
        Transformation(float ti, vector<Point*> cP, bool de, string t);
		Transformation(float r, float g, float b);
        string getType();
        float getAngle();
		void setX(float x);
		void setY(float y);
		void setZ(float z);
        float getX();
        float getY();
        float getZ();
        float getTime();
        float* getVetor();
        void normalize(float *a);
        void cross(float *a, float *b, float *res);
        void rotMatrix(float *r, float *x, float *y, float *z);
        void multMatrixVector(float *m, float *v, float *res);
        bool getDeriv();
        vector<Point*> getPointsCurve();
        void getCatmullRomPoint(float t, int *indexes, float *p, float *deriv);
        void getGlobalCatmullRomPoint(float gt, float *p, float *deriv);
	   void setCatmullPoints();
};

#endif
