#include "../../include/engine/group.h"

Group::Group(){}

//Construção de um grupo para um único asteróide
Group::Group(pair<vector<float>, vector<int> > vectors, float radiusIn, float radiusOut, float verticalAngle, Point *newColor){
    if(newColor != NULL){
        color->x = newColor->x;
        color->y = newColor->y;
        color->z = newColor->z;
    }
    else color = NULL;
  
    
    models.push_back(Model(vectors.first, vectors.second));

    float angle = (float) rand() / RAND_MAX;
    angle = angle * 360.0; // 0 e 360

    float vAngle = (float) rand() / RAND_MAX;
    vAngle = (vAngle * verticalAngle) - verticalAngle/2.0;

    float deltaX = (float) rand() / RAND_MAX;
    deltaX = (deltaX * radiusIn) - radiusIn/2.0;

    transforms.push_back(new Rotate(0, 1, 0, angle));
    transforms.push_back(new Rotate(0, 0, 1, vAngle));
    transforms.push_back(new Translate(radiusOut + deltaX, 0, 0));
    transforms.push_back(new Scale((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX));
}


Group::Group(XMLElement *groupElement){
    color = NULL;

    for(XMLElement *elem = groupElement->FirstChildElement(); elem; elem = elem->NextSiblingElement()){
        string name(elem->Name());

        if(name == "transform"){
            for(XMLElement *transformElem = elem->FirstChildElement(); transformElem; transformElem = transformElem->NextSiblingElement()){
                string transform(transformElem->Name());

                if(transform == "translate"){
                    transforms.push_back(new Translate(transformElem));
                }
                else if(transform == "rotate"){
                    transforms.push_back(new Rotate(transformElem));
                }
                else if(transform == "scale"){
                    transforms.push_back(new Scale(transformElem));
                }
            }
        }
        else if(name == "models"){
            for(XMLElement *modelElem = elem->FirstChildElement(); modelElem; modelElem = modelElem->NextSiblingElement()){
                string name(modelElem->Name());

                if(name == "model"){
                    models.push_back(Model(modelElem));
                }
                else if(name == "belt"){
                    char *path = strdup((char *)modelElem->Attribute("file"));
                    int n = atoi((char *)modelElem->Attribute("n"));
                    float radiusIn = atof((char *)modelElem->Attribute("radiusIn"));
                    float radiusOut = atof((char *)modelElem->Attribute("radiusOut"));
                    float verticalAngle = atof((char *)modelElem->Attribute("verticalAngle"));
                    int seed = atoi((char *)modelElem->Attribute("seed"));
                    pair<vector<float>, vector<int> > vectors = Model::readFile(path);
                    Point *color = NULL;

                    XMLElement *child = modelElem->FirstChildElement();
                    if(child != NULL){
                        string name(child->Name());
                        if(name == "color"){
                            float r = atof((char *)child->Attribute("R"));
                            float g = atof((char *)child->Attribute("G"));
                            float b = atof((char *)child->Attribute("B"));
                            color = new Point(r, g, b);
                        }
                    }

                    srand(seed);
                    float anglePart = 2 * M_PI / (float)n;
                    for(int i = 0; i<n; i++){
                        groups.push_back(Group(vectors, radiusIn, radiusOut, verticalAngle, color));
                    }
                }
                
            }
        }
        else if(name == "group"){
            groups.push_back(Group(elem));
        }
        else if(name == "color"){
            color = new Point(atof((char*)elem->Attribute("R")), atof((char*)elem->Attribute("G")), atof((char*)elem->Attribute("B")));
        }
    }
}


void Group::loadModels(){
    for(int i = 0; i < models.size(); i++){
        models[i].load();
    }

    for(int i = 0; i < groups.size(); i++){
        groups[i].loadModels();
    }
}


void Group::drawModels(){
    glPushMatrix();

    if (color != NULL) {
        glColor3f(color->x / 255.0, color->y / 255.0, color->z / 255.0);
    }

    for(int i = 0; i < transforms.size(); i++){
        transforms[i]->transform();
    }
    
    for(int i = 0; i < models.size(); i++){
        models[i].draw();
    }    

    for(int i = 0; i < groups.size(); i++){
        groups[i].drawModels();
    }

    glPopMatrix();
}
