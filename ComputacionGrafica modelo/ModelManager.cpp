#include "ModelManager.h"

using namespace std;

// Constructor de la clase ModelManager
ModelManager::ModelManager() {}

// Destructor de la clase ModelManager
ModelManager::~ModelManager() {
    // Itera sobre el mapa de modelos y elimina cada modelo usando glmDelete
    for (auto& pair : models) {
        glmDelete(pair.second);
    }
}

// Método para cargar un modelo desde un archivo
GLMmodel* ModelManager::loadModel(const string& filePath) {
    // Verifica si el modelo ya está cargado
    if (models.find(filePath) == models.end()) {
        // Si no está cargado, lo carga usando glmReadOBJ
        GLMmodel* model = glmReadOBJ(const_cast<char*>(filePath.c_str()));
        if (model) {
            // Normaliza el modelo
            glmUnitize(model);
            // Calcula las normales de las facetas
            glmFacetNormals(model);
            // Calcula las normales de los vértices con un ángulo de 90 grados
            glmVertexNormals(model, 90.0);
            // Almacena el modelo en el mapa
            models[filePath] = model;
        }
    }
    // Retorna el modelo cargado
    return models[filePath];
}

// Método para obtener un modelo ya cargado
GLMmodel* ModelManager::getModel(const string& filePath) const {
    // Busca el modelo en el mapa
    auto it = models.find(filePath);
    if (it != models.end()) {
        // Si lo encuentra, lo retorna
        return it->second;
    }
    // Si no lo encuentra, retorna nullptr
    return nullptr;
}

// Método para asociar una textura a un modelo
void ModelManager::associateTexture(const string& modelPath, const string& texturePath) {
    // Almacena la asociación en el mapa de texturas
    modelTextures[modelPath] = texturePath;
}

// Método para obtener la textura asociada a un modelo
string ModelManager::getTexture(const string& modelPath) const {
    // Busca la textura en el mapa de texturas
    auto it = modelTextures.find(modelPath);
    if (it != modelTextures.end()) {
        // Si la encuentra, la retorna
        return it->second;
    }
    // Si no la encuentra, retorna una cadena vacía
    return "";
}