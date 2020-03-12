#include "headers/Patch.h"
#include "headers/Point.h"
#include "headers/figures.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

void writePointsFile(string filename, vector<Point> verts,vector<Point> normals,vector<float>text) {
        ofstream file;

        string fileDir = "../../files/" + filename;
        file.open(fileDir, ios_base::trunc);

        if (!file.is_open()) {
                cout << "Error while opening the file " << filename << endl;
        }
        else {
                file << verts.size() << "\n";
                for (const Point vert : verts) {
                        string x, y, z;

                        x = to_string(vert.x).append(",");
                        y = to_string(vert.y).append(",");
                        z = to_string(vert.z).append("\n");

                        file << x << y << z;
                }

                file << normals.size() << "\n";
                for(const Point normal : normals){
                        string x, y, z;
                        x = to_string(normal.x).append(",");
                        y = to_string(normal.y).append(",");
                        z = to_string(normal.z).append("\n");

                        file << x << y << z;
                }

                file << text.size() / 2 << "\n";
                for(float i = 0.0;i<text.size();i+=2){
                        string t1,t2;
                        t1 = to_string(text[i]).append(",");
                        t2 = to_string(text[i+1]).append("\n");

                        file << t1 << t2;
                }

                file.close();
                cout << filename << " file was created!" << endl;
        }
}


int main (int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Not enough arguments!\n");
        return -1;
    }

    vector<Point> normal;
    vector<float> texture;
    vector<Point> points;
    string file;

    if (strcmp("cone",argv[1]) == 0 && argc == 7)
    {
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int layers = atoi(argv[5]);
        file = argv[6];
        points = cone(radius,height,slices,layers,&normal,&texture);
    }
    else if (strcmp("box", argv[1]) == 0 && argc == 7)
    {
        float length = atof(argv[2]), width = atof(argv[3]), height = atof(argv[4]);
        int divisions = atoi(argv[5]);
        file = argv[6];
        points = box(length,width,height,divisions,&normal,&texture);
    }
    else if (strcmp("sphere",argv[1]) == 0 && argc == 6)
    {
            float radius = atof(argv[2]);
            int slices = atoi(argv[3]);
            int layers = atoi(argv[4]);
            file = argv[5];
            points = sphere(radius, slices, layers,&normal,&texture);
    }
    else if (strcmp("plane", argv[1]) == 0 && argc == 4)
    {
            float size = atof(argv[2]);
            file = argv[3];
            points = plane(size / 2 ,&normal,&texture);
    }
   else if (strcmp("cylinder",argv[1]) == 0 && argc == 7)
    {
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int layers = atoi(argv[5]);
        file = argv[6];
        points = cylinder(radius,height,slices,layers,&normal,&texture);
    }
     
    else if (strcmp("torus",argv[1]) == 0 && argc == 7){
    
            float radiusIn = atof(argv[2]);
	    float radiusOut = atof(argv[3]);
            int slices = atoi(argv[4]);
            int layers = atoi(argv[5]);
            file = argv[6];
            points = torus(radiusIn,radiusOut, slices, layers,&normal,&texture);
    }

    else if (strcmp("-patch",argv[1]) == 0 && argc==5){
          string filename = argv[2];
          int tess = atoi(argv[3]);
          file = argv[4];

          Patch *p = new Patch(tess,filename);
          p->geradorModeloBezier(&points,&normal,&texture);
      }


    else{
        printf("Invalid input!\n");
        return -1;
    }

    if(points.size())
        writePointsFile(file,points,normal,texture);
    
    return 0;
}

