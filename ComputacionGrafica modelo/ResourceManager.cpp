#include "ResourceManager.h"

using namespace std;


ResourceManager::ResourceManager() {
    // Inicializa la biblioteca FreeImage
    initializeFreeImage();
}

// Destructor de la clase ResourceManager
ResourceManager::~ResourceManager() {
    
    FreeImage_DeInitialise();
}

// Función para inicializar la biblioteca FreeImage
void ResourceManager::initializeFreeImage() {
    FreeImage_Initialise();
}

// Función para cargar una textura desde un archivo
GLuint ResourceManager::loadTexture(const string& filePath) {
    // Verifica si la textura ya ha sido cargada
    if (textures.find(filePath) != textures.end()) {
        // Si ya está cargada, devuelve el ID de la textura
        return textures[filePath];
    }

    GLuint texid; // ID de la textura
    // Carga la imagen usando FreeImage
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filePath.c_str(), 0), filePath.c_str());
    // Convierte la imagen a un formato de 32 bits
    FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
    // Obtiene las dimensiones de la imagen
    int nWidth = FreeImage_GetWidth(pImage);
    int nHeight = FreeImage_GetHeight(pImage);

    // Genera un nuevo ID de textura y la enlaza
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    // Configura los parámetros de la textura
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // Carga los datos de la imagen en la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

    // Libera la imagen cargada
    FreeImage_Unload(pImage);
    // Habilita las texturas 2D en OpenGL
    glEnable(GL_TEXTURE_2D);

    // Almacena el ID de la textura en el mapa y lo devuelve
    textures[filePath] = texid;
    return texid;
}

// Función para cargar múltiples texturas desde una lista de archivos
void ResourceManager::loadTextures(const vector<string> &filePaths) {
    // Itera sobre cada ruta de archivo y carga la textura
    for (const auto& filePath : filePaths) {
        loadTexture(filePath);
    }
}

// Función para obtener el ID de una textura previamente cargada
GLuint ResourceManager::getTexture(const string &filePath) const {
    // Busca la textura en el mapa
    auto it = textures.find(filePath);
    // Si la encuentra, devuelve el ID de la textura
    if (it != textures.end()) {
        return it->second;
    }
    // Si no la encuentra, devuelve 0
    return 0;
}