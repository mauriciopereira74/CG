#include "../../include/engine/world.h"

World::World(){}

World::World(Window newWindow, Camera newCamera, vector<Group> newGroups){
    window = newWindow;
    camera = newCamera;
    groups = newGroups;
}

World::World(char *path){
    XMLDocument xmlDoc;
	XMLError result = xmlDoc.LoadFile(path);
	XMLElement *root = xmlDoc.FirstChildElement("world");
    
    for(XMLElement *elem = root->FirstChildElement(); elem; elem=elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "window"){
            window = Window(elem);
        }
        else if(name == "camera"){
            camera = Camera(elem);
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
    }
}


void World::loadModels(){
    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


void World::drawModels(){
    for(int i = 0; i < groups.size(); i++){
        groups[i].drawModels();
    }
}
