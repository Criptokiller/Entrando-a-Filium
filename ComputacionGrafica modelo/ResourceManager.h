#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GL/glew.h>
#include <FreeImage.h>
#include <string>
#include <unordered_map>

using namespace std;

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    GLuint loadTexture(const string &filePath);
    void loadTextures(const vector<string> &filePaths);
    GLuint getTexture(const string &filePath) const;

private:
    void initializeFreeImage();
    unordered_map<string, GLuint> textures;
};

#endif // RESOURCE_MANAGER_H
