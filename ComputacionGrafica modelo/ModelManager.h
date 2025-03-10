#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <string>
#include <unordered_map>
#include "glm.h"

using namespace std;

class ModelManager {
public:
    ModelManager();
    ~ModelManager();

    GLMmodel* loadModel(const string& filePath);
    GLMmodel* getModel(const string& filePath) const;
    void associateTexture(const string& modelPath, const string& texturePath);
    string getTexture(const string& modelPath) const;

private:
    unordered_map<string, GLMmodel*> models;
    unordered_map<string, string> modelTextures;
};

#endif MODEL_MANAGER_H
