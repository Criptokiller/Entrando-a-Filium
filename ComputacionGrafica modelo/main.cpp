//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include <FreeImage.h> //*** Para Textura: Incluir librer�a
#include "ModelManager.h" //*** Para Textura: Incluir librer�a
#include "ResourceManager.h" //*** Para Textura: Incluir librer�a

using namespace std;

//-----------------------------------------------------------------------------

class myWindow : public cwc::glutWindow {
protected:
    cwc::glShaderManager SM;
    cwc::glShader* shader;
    cwc::glShader* shader1;
    GLuint ProgramObject;
    clock_t time0, time1;
    float timer010;
    bool bUp;
	GLMmodel* objmodels[5];
    ModelManager modelManager;
    ResourceManager resourceManager; // Definir instancia de ResourceManager

public:
    myWindow() {}

    void initialize_textures() {
        vector<string> texturePaths = {
            "./Mallas/bola.jpg",
            "./Mallas/otra_textura.jpg",
            "./Mallas/madera.jpg",
            "./Mallas/tree_texture.png",
            "./Mallas/car.jpg",
            "./Mallas/tumba_sangre.jpg",
            "./Mallas/gus.jpg"
            // Agrega m�s rutas de texturas aqu�
        };

        resourceManager.loadTextures(texturePaths);

        // Asociar texturas con modelos
        modelManager.associateTexture("./Mallas/bola.obj", "./Mallas/bola.jpg");
        modelManager.associateTexture("./Mallas/perro_madera.obj", "./Mallas/madera.jpg");
        modelManager.associateTexture("./Mallas/Tree.obj", "./Mallas/tree_texture.png");
        modelManager.associateTexture("./Mallas/car.obj", "./Mallas/car.jpg");
        modelManager.associateTexture("./Mallas/tumba_sangre.obj", "./Mallas/tumba_sangre.jpg");
        modelManager.associateTexture("./Mallas/gus.obj", "./Mallas/gus.jpg");

    }

    virtual void OnInit() {
        glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        shader = SM.loadfromFile("vertexshader.txt", "fragmentshader.txt");
        if (shader == 0)
            cout << "Error Loading, compiling or linking shader\n";
        else
            ProgramObject = shader->GetProgramObject();

        shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt");
        if (shader1 == 0)
            cout << "Error Loading, compiling or linking shader\n";
        else
            ProgramObject = shader1->GetProgramObject();

        time0 = clock();
        timer010 = 0.0f;
        bUp = true;

        objmodels[0] = modelManager.loadModel("./Mallas/car.obj");
        objmodels[1] = modelManager.loadModel("./Mallas/tumba_sangre.obj");
        objmodels[2] = modelManager.loadModel("./Mallas/perro_madera.obj");
        objmodels[3] = modelManager.loadModel("./Mallas/Tree.obj");
        objmodels[4] = modelManager.loadModel("./Mallas/gus.obj");


        initialize_textures();
        DemoLight();
    }

    void renderModel(GLMmodel* model, const std::string& modelPath, cwc::glShader* shader) {
        if (shader) shader->begin();
    
        glPushMatrix();
    
        if (modelPath == "./Mallas/car.obj") {
            glTranslatef(-1.5f, 0.0f, 0.0f);
            glScalef(2.0f, 2.0f, 2.0f);
        } else if (modelPath == "./Mallas/tumba_sangre.obj") {
            glTranslatef(1.5f, 0.0f, 0.0f);
            glScalef(2.0f, 2.0f, 2.0f);
        } else if (modelPath == "./Mallas/perro_madera.obj") {
            glTranslatef(0.0f, -1.5f, 0.0f);
            glScalef(2.0f, 2.0f, 2.0f);
        } else if (modelPath == "./Mallas/Tree.obj") {
            glTranslatef(0.0f, 1.5f, 0.0f);
        } else if (modelPath == "./Mallas/gus.obj") {
            glTranslatef(0.0f, -0.3f, 0.0f);
            glScalef(0.6f, 0.6f, 0.6f);
        }
    
        glBindTexture(GL_TEXTURE_2D, resourceManager.getTexture(modelManager.getTexture(modelPath)));
        glmDraw(model, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    
        glPopMatrix();
    
        if (shader) shader->end();
    }
    

    virtual void OnRender(void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
    
        renderModel(objmodels[0], "./Mallas/car.obj", shader);
        renderModel(objmodels[1], "./Mallas/tumba_sangre.obj", shader1);
        renderModel(objmodels[2], "./Mallas/perro_madera.obj", shader1);
        renderModel(objmodels[3], "./Mallas/Tree.obj", shader1);
        renderModel(objmodels[4], "./Mallas/gus.obj", shader);
    
        glutSwapBuffers();
        glPopMatrix();
    
        UpdateTimer();
        Repaint();
    }
    

    virtual void OnIdle() {}

    virtual void OnResize(int w, int h) {
        if (h == 0) h = 1;
        float ratio = 1.0f * (float)w / (float)h;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, w, h);

        gluPerspective(45, ratio, 1, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 4.0f,
            0.0, 0.0, -1.0,
            0.0f, 1.0f, 0.0f);
    }

    virtual void OnClose(void) {}
    virtual void OnMouseDown(int button, int x, int y) {}
    virtual void OnMouseUp(int button, int x, int y) {}
    virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) {}

    virtual void OnKeyDown(int nKey, char cAscii) {
        if (cAscii == 27) // 0x1b = ESC
        {
            this->Close(); // Close Window!
        }
    }

    virtual void OnKeyUp(int nKey, char cAscii) {
        if (cAscii == 's')      // s: Shader
            shader->enable();
        else if (cAscii == 'f') // f: Fixed Function
            shader->disable();
    }

    void UpdateTimer() {
        time1 = clock();
        float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
        delta = delta / 4;
        if (delta > 0.00005f) {
            time0 = clock();
            if (bUp) {
                timer010 += delta;
                if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
            }
            else {
                timer010 -= delta;
                if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
            }
        }
    }

    void DemoLight(void) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

        GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
        GLint spot_exponent = 30;
        GLint spot_cutoff = 180;

        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
        glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
        glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

        GLfloat Kc = 1.0;
        GLfloat Kl = 0.0;
        GLfloat Kq = 0.0;

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);

        GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
        GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
        GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
        GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

        GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
        GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
        GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
        GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
        GLfloat material_Se = 20.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
    }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication {
public:
    virtual void OnInit() { cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void) {
    myApplication* pApp = new myApplication;
    myWindow* myWin = new myWindow();

    pApp->run();
    delete pApp;
    return 0;
}

//-----------------------------------------------------------------------------
