#include "headers/parser.h"
#include "headers/Point.h"


int readPointsFile(string filename, vector<Point*> *points) {
	string l, t, token;
	ifstream file(filename);
	int j, i = 0;
	vector<float> tokens;

	if (!file.is_open()) {
		cout << "Unable to open file: " << filename << "." << endl;
		return -1;
	}
	else
	{
		while (!file.eof())
		{
			getline(file, l);
			stringstream ss(l.c_str());

			if (l.c_str() != NULL)
			{
				j = 0;

				while(j < 3 && getline(ss,token,',')) {
					tokens.push_back(stof(token));
					j++;
				}

				Point *p = new Point(tokens[i++], tokens[i++], tokens[i++]);
				points->push_back(p);
			}
		}
		points->pop_back();
		file.close();
	}
	return 0;
}

Group* loadXMLfile(string filename, vector<Point*> *points) {
    Group* group = nullptr;
    XMLDocument xmlDoc;
    XMLNode *pRoot;
    XMLElement *pElement;
    string fileDir = "../../files/" + filename;
    XMLError eResult = xmlDoc.LoadFile(fileDir.c_str());
    
    if (eResult == XML_SUCCESS)
    {
        pRoot = xmlDoc.FirstChild();
        if (pRoot != nullptr)
        {
            group = new Group();
            pElement = pRoot->FirstChildElement("group");
            parseGroup(group,pElement,points,0);
        }
    }
    else
    {
        cout << "Unable to open file: " << filename << "." << endl;
    }
    return group;
}

void parseRotate (Group* group, XMLElement* element) {
    float angle = 0, x = 0, y = 0, z = 0;
    string type = "rotation";
    Transformation *t;

    if(element->Attribute("angle"))
        angle = stof(element->Attribute("angle"));

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    t = new Transformation(type,angle,x,y,z);
    group->addTransformation(t);
}

void parseTranslate (Group *group, XMLElement *element, vector<Point*> *orbits, int d)
{
    float x=0, y=0, z=0;
    string type = "translation";
    Transformation *t;

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    t = new Transformation(type,0,x,y,z);
    group->addTransformation(t);

    if (d == 0 || d == 1)
    {
        Point *p = new Point(x,y,z);
        orbits->push_back(p);
    }
}

void parseScale (Group *group, XMLElement *element){
    float x=1, y=1, z=1;
    string type = "scale";
    Transformation *t;

    if(element->Attribute("X"))
        x = stof(element->Attribute("X"));

    if(element->Attribute("Y"))
        y = stof(element->Attribute("Y"));

    if(element->Attribute("Z"))
        z = stof(element->Attribute("Z"));

    t = new Transformation(type,0,x,y,z);
    group->addTransformation(t);
}

void parseColour (Group *group, XMLElement *element){
    float x=1, y=1, z=1;
    string type = "colour";
    Transformation *t;

    if(element->Attribute("R"))
        x = stof(element->Attribute("R"));

    if(element->Attribute("G"))
        y = stof(element->Attribute("G"));

    if(element->Attribute("B"))
        z = stof(element->Attribute("B"));


    t = new Transformation(type,0,x,y,z);
    group->addTransformation(t);
}

void parseModels (Group *group, XMLElement *element) {
    string file;
    vector<Shape*> shapes;

    element = element->FirstChildElement("model");

    if (element == nullptr) {
        cout << "XML error: Models are not available!" << endl;
        return;
    }

    while (element != nullptr) {

        file = element->Attribute("file");
        string fileDir = "../../files/" + file;
        if(!file.empty()) {
            vector<Point*> points;
            readPointsFile(fileDir, &points);

            if (points.size()) {
                Shape *shape = new Shape(points);
                shapes.push_back(shape);
            }
        }
        element = element->NextSiblingElement("model");
    }

    if (shapes.size())
        group->setShapes(shapes);
}

void parseGroup (Group *group, XMLElement *gElement, vector<Point*> *orbits, int d)
{
    XMLElement *element = gElement->FirstChildElement();

    while (element)
    {
        if (strcmp(element->Name(),"translate") == 0)
            parseTranslate(group,element,orbits,d);

        else if (strcmp(element->Name(),"scale") == 0)
            parseScale(group,element);

        else if (strcmp(element->Name(),"rotate") == 0)
            parseRotate(group,element);

        else if (strcmp(element->Name(),"models") == 0)
            parseModels(group, element);

	else if (strcmp(element->Name(),"colour") == 0)
            parseColour(group, element);

        else if (strcmp(element->Name(),"group") == 0)
        {
            Group *child = new Group();
            group->addGroup(child);
            parseGroup(child,element,orbits,d+1);
        }

        element = element->NextSiblingElement();
    }
}
