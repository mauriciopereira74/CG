#include "../../include/world.h"

World::World(){}

World::World(Window newWindow, Camera newCamera, Group newGroup){
    window = newWindow;
    camera = newCamera;
    group = newGroup;
}

World::World(char *path){
    XMLDocument xmlDoc;
	XMLError result = xmlDoc.LoadFile(path);
	XMLNode *root = xmlDoc.FirstChild();
    
	if(root){
        XMLElement *windowElement = root->FirstChildElement("window");
        if(windowElement){
            window = Window(windowElement);
        }

        XMLElement *cameraElement = root->FirstChildElement("camera");
        if(cameraElement){
            camera = Camera(cameraElement);
        }
    
        XMLElement *groupElement = root->FirstChildElement("group");
        if(groupElement){
            XMLElement *modelsElement = groupElement->FirstChildElement("models");
            if(modelsElement){
                vector<string> modelsPaths;
                for (XMLElement *modelElement = modelsElement->FirstChildElement("model"); modelElement; modelElement = modelElement->NextSiblingElement("model")){               
                    const char *path = (char *)modelElement->Attribute("file");
                    modelsPaths.push_back(string(path));
                }
                group = Group(modelsPaths);
            }
        }
	}
}

void World::loadGroup(){
    for(int i = 0; i<group.modelsPaths.size(); i++){
        group.vbos.push_back(VBO((char *)group.modelsPaths[i].c_str()));
    }
}

// -----------WINDOW-----------
Window::Window(){}

Window::Window(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
}

Window::Window(XMLElement *windowElement){
    width = atoi(windowElement->Attribute("width"));
    height = atoi(windowElement->Attribute("height"));
}


// -----------CAMERA-----------
Camera::Camera(){}

Camera::Camera(Point newPosition, Point newLookAt, Point newUp, Projection newProjection){
    position = newPosition;
    lookAt = newLookAt;
    up = newUp;
    projection = newProjection;
}

Camera::Camera(XMLElement *cameraElement){
    XMLElement *positionElement = cameraElement->FirstChildElement("position");
    float positionX = atof(positionElement->Attribute("x"));
    float positionY = atof(positionElement->Attribute("y"));
    float positionZ = atof(positionElement->Attribute("z"));
    

    XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
    float lookAtX = atof(lookAtElement->Attribute("x"));
    float lookAtY = atof(lookAtElement->Attribute("y"));
    float lookAtZ = atof(lookAtElement->Attribute("z"));

    XMLElement *upElement = cameraElement->FirstChildElement("up");
    float upX = atof(upElement->Attribute("x"));
    float upY = atof(upElement->Attribute("y"));
    float upZ = atof(upElement->Attribute("z"));

    XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
    float projectionFov = atof(projectionElement->Attribute("fov"));
    float projectionNear = atof(projectionElement->Attribute("near"));
    float projectionFar = atof(projectionElement->Attribute("far"));

    position = Point(positionX, positionY, positionZ);
    lookAt = Point(lookAtX, lookAtY, lookAtZ);
    up = Point(upX, upY, upZ);
    projection = Projection(projectionFov, projectionNear, projectionFar);
}


// -----------GROUP-----------
Group::Group(){}

Group::Group(vector<VBO> newVBOS){
    vbos = newVBOS;
}

Group::Group(vector<string> newModelsPaths){
    modelsPaths = newModelsPaths;
}


// -----------PROJECTION-----------
Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}