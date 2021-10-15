
#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <cstdlib>
#include <random>
#include <chrono>
#include <ctime>
//vertex shader kaynak kodu
const char* vssource = "#version 330 core\n"
"layout (location = 0) in vec3 inPosition;\n"
"uniform vec3 uMove;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(inPosition+uMove,1.0);\n"
"}\0";
const char* fssource = "#version 330 core\n"
"out vec4 fragColor;\n"
"uniform vec4 uColor;\n"
"void main()\n"
"{\n"
"   fragColor = uColor;\n"
"}\n\0";
//renk
glm::vec4 kareColor   = glm::vec4(1.0f,0.0f,1.0f,1.0);
glm::vec4 ucgenColor  = glm::vec4(1.0f, 1.0f, 0.0f, 1.0);
glm::vec4 cemberColor = glm::vec4(1.0f, 0.5f, 0.5f, 1.0);
//randomkonum
glm::vec3 positionK, positionU, positionC;
//randomsekil
int randSekil1, randSekil2;
float kx, ky, ux, uy, cx, cy;
//nokta kordinat
float kareNokta,ucgenNokta;
float randomKordinatKare()
{
    srand(time(0));
    kareNokta = (std::rand() % 11 + 7);
    kareNokta = kareNokta / 100;
    return kareNokta;

}
float randomKordinatUcgen()
{
    srand(time(0));
    ucgenNokta = (std::rand() % 11 + 7);
    ucgenNokta = ucgenNokta / 100;
    return ucgenNokta;

}
//noktalara ait koordinat bilgileri.
float kare[] = {
    -randomKordinatKare(),  randomKordinatKare(), 0.0f,
    -randomKordinatKare(), -randomKordinatKare(), 0.0f,
     randomKordinatKare(), -randomKordinatKare(), 0.0f,

    -randomKordinatKare(),  randomKordinatKare(), 0.0f,
     randomKordinatKare(), -randomKordinatKare(), 0.0f,
     randomKordinatKare(),  randomKordinatKare(), 0.0f
};
float ucgen[] = {
    -randomKordinatUcgen(), -randomKordinatUcgen(), 0.0f,
     randomKordinatUcgen(), -randomKordinatUcgen(), 0.0f,
     randomKordinatUcgen() - randomKordinatUcgen(), randomKordinatUcgen(), 0.0f,
};
std::vector<glm::vec3>cember;
void cemberOlustur(float radius, int vertexCound)
{
    std::vector<glm::vec3>tempVertices;
    float angle = 360.0f / vertexCound;
    int triangleCount = vertexCound - 2;
    for (int i=0;i<vertexCound;i++)
    { 
        float newAngle = angle * i;
        float x = radius * cos(glm::radians(newAngle));
        float y = radius * sin(glm::radians(newAngle));
        float z = 0.0f;
        tempVertices.push_back(glm::vec3(x,y,z));
    }
    for (int i = 0; i < triangleCount; i++)
    {
        cember.push_back(tempVertices[0]);
        cember.push_back(tempVertices[i+1]);
        cember.push_back(tempVertices[i+2]);
    }

}
void randomKonum()
{
    float randX, randY, erandX, erandY;
    for (int i = 0; i < 3; i++)
    {
        srand(time(0));
        randX = (std::rand() % 19 + 1) - 10;
        randX = randX / 10;
        while (true)
        {
            srand(time(0));
            randY = ((std::rand() % 19 + 1) - 10);
            randY = randY / 10;
            if (randX != randY)
            {
                if (i == 0)
                {
                    // kare baþlangýc pozisyonu
                    positionK = glm::vec3(randX, randY, 0.0f);
                }
                if (i == 1)
                {
                    // ucgen baþlangýc pozisyonu
                    positionU = glm::vec3(randX, randY, 0.0f);
                }
                if (i == 2)
                {
                    // cember baþlangýc pozisyonu
                    positionC = glm::vec3(randX, randY, 0.0f);
                }
                break;
            }
        }
    }
}
void randomSekil()
{
    srand(time(0));
    randSekil1 = (std::rand() % 3 + 1);
    while (true)
    {
        randSekil2 = (std::rand() % 3 + 1);
        if (randSekil2 != randSekil1)
            break;
    }
}
float yCap;
void randomCemberCap()
{
    srand(time(0));  
    yCap = (std::rand() % 11 + 7);
    yCap = yCap / 100;
    cemberOlustur(yCap, 36);
}
void kareXY()
{
    int kareH = (std::rand() % 4);
    if (kareH == 0)
    {
        kx = -0.0003;
        ky = 0.0;
    }
    else if (kareH == 1)
    {
        kx = 0.0003;
        ky = 0.0;
    }
    else if (kareH == 2)
    {
        kx = 0.0;
        ky = 0.0003;
    }
    else if (kareH == 3)
    {
        kx = 0.0;
        ky = -0.0003;
    }
}
void ucgenXY()
{
    // srand(time(0));
    int ucgenH = (std::rand() % 4);
    if (ucgenH == 0)
    {
        ux = -0.0003;
        uy = 0.0;
    }
    else if (ucgenH == 1)
    {
        ux = 0.0003;
        uy = 0.0;
    }
    else if (ucgenH == 2)
    {
        ux = 0.0;
        uy = 0.0003;
    }
    else if (ucgenH == 3)
    {
        ux = 0.0;
        uy = -0.0003;
    }

}
void cemberXY()
{
    //  srand(time(0));
    int cemberH = (std::rand() % 4);
    if (cemberH == 0)
    {
        cx = -0.0003;
        cy = 0.0;
    }
    else if (cemberH == 1)
    {
        cx = 0.0003;
        cy = 0.0;
    }
    else if (cemberH == 2)
    {
        cx = 0.0;
        cy = 0.0003;
    }
    else if (cemberH == 3)
    {
        cx = 0.0;
        cy = -0.0003;
    }

}
std::clock_t start;
double duration;
void timerKontrol()
{
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    if (duration > 4.5)
    {
        start = std::clock();
    }
    if (duration > 3.250 && duration < 3.300)
    {
        kareXY();
    }
    else if (duration > 3.200 && duration < 3.250)
    {
        ucgenXY();
    }

    else if (duration > 3.150 && duration < 3.200)
    {
        cemberXY();
    }
}
void carpismaKontrolKenar()
{
    //kare
    if (positionK.x >= 1.0 - kareNokta)
    {
        kx = -0.0003;
        ky = 0.0;
    }
    else if (positionK.y >= 1.0 - kareNokta)
    {
        kx = 0.0;
        ky = -0.0003;
    }
    else if ( positionK.x <= -1.0+ kareNokta)
    {
        kx = 0.0003;
        ky = 0.0;
    }
    else if (positionK.y <= -1.0 + kareNokta)
    {
        kx = 0.0;
        ky = 0.0003;
    }
    //ucgen
    if (positionU.x >= 1.0 - ucgenNokta)
    {
        ux = -0.0003;
        uy = 0.0;
    }
    else if (positionU.y >= 1.0 - ucgenNokta)
    {
        ux = 0.0;
        uy = -0.0003;
    }
    else if (positionU.x <= -1.0 + ucgenNokta)
    {
        ux = 0.0003;
        uy = 0.0;
    }
    else if (positionU.y <= -1.0 + ucgenNokta)
    {
        ux = 0.0;
        uy = 0.0003;
    }
    //Cember
    if (positionC.x >= 1.0 - yCap)
    {
        cx = -0.0003;
        cy = 0.0;
    }
    else if (positionC.y >= 1.0 - yCap)
    {
        cx = 0.0;
        cy = -0.0003;
    }
    else if (positionC.x <= -1.0 + yCap)
    {
        cx = 0.0003;
        cy = 0.0;
    }
    else if (positionC.y <= -1.0 + yCap)
    {
        cx = 0.0;
        cy = 0.0003;
    }

}
float cuX, cuY, ckX, ckY, ukX, ukY;
bool carpismaKontrolSekil()
{
    if ((randSekil1 == 2 || randSekil1 == 3) && (randSekil2 == 2 || randSekil2 == 3))
    {
         cuX = abs(positionC.x - positionU.x);
         cuY = abs(positionC.y - positionU.y);
        if (cuX - ucgenNokta - yCap <= -0.03 && cuY - ucgenNokta - yCap <= -0.03)
        {
            std::cout << "------>>> DAIRE-UCGEN CARPISMASI TEPIT EDILDI <<<------";
            return true;
        }

    }

    else  if ((randSekil1 == 1 || randSekil1 == 3) && (randSekil2 == 1 || randSekil2 == 3))
    {
         ckX = abs(positionC.x - positionK.x);
         ckY = abs(positionC.y - positionK.y);
        if (ckX - kareNokta - yCap <= -0.02 && ckY - kareNokta - yCap <= -0.02)
        {
            std::cout << "------>>> DAIRE-KARE CARPISMASI TEPIT EDILDI  <<<------";
            return true;
        }

    }


    else if ((randSekil1 == 1 || randSekil1 == 2) && (randSekil2 == 1 || randSekil2 == 2))
    {
         ukX = abs(positionU.x - positionK.x);
         ukY = abs(positionU.y - positionK.y);
        if (ukX - kareNokta - ucgenNokta <= -0.03 && ukY - kareNokta - ucgenNokta <= -0.03)
        {
            std::cout << "------>>> KARE-UCGEN CARPISMASI TEPIT EDILDI <<<------";
            return true;
        }

    }
    return false;
}
//OpenGL nesnelerinin id deðerlerini tutacak olan deðiþkenler
unsigned int fragmentShader;
unsigned int vertexShader;
unsigned int shaderProgram;
unsigned int VBO;
unsigned int VAO;
std::map<std::string, unsigned int> m_Uniformvars;
//id atama
void addUniform(const std::string& varName)
{
    m_Uniformvars[varName] = glGetUniformLocation(shaderProgram, varName.c_str());
}
//yeniKordinat
void setVec3(const std::string& varName, const glm::vec3 &value)
{
    glUniform3f(m_Uniformvars[varName], value.x,value.y,value.z);
}
//yeniRenk
void setVec4(const std::string& varName, const glm::vec4& value)
{
    glUniform4f(m_Uniformvars[varName], value.r, value.g, value.b, value.a);
}

int main(int argc, char** argv)
{
    start = std::clock();
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Pencere Olusturulamadi" << std::endl;

        glfwTerminate();

        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD Baþlatýlamadý" << std::endl;
        return -1;
    }

    //vertex shader oluþsturuluyor
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vssource, NULL);
    glCompileShader(vertexShader);

    //Fragment Shader Oluþturuluyor
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fssource, NULL);
    glCompileShader(fragmentShader);

    //Program nesnesi oluþturuluyor ve shader nesneleri yükleniyor    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //vertex array object oluþturuluyor
    glGenVertexArrays(1, &VAO);
    //vertex buffer object oluþuruluyor
    glGenBuffers(1, &VBO);

    //vertex array object aktif edildi.
    glBindVertexArray(VAO);
    //vertex buffer nesnesi aktif edildi.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //vertex buffer'a nokta bilgileri ytollanýyor
    //gönderilen vertex'e ait özellikler etiketleniyor
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //özellik  etiketi aktif ediliyor.
    glEnableVertexAttribArray(0);

    randomKordinatKare();

    randomSekil();

    randomCemberCap();

    randomKonum();

    randomKordinatUcgen();
  
    while (!glfwWindowShouldClose(window))
    {       
        if (carpismaKontrolSekil() == true)
        {
            break;
        }
        carpismaKontrolKenar();
        timerKontrol();
        //Id getir
        addUniform("uMove");
        addUniform("uColor");
        //oluþturulacak resim baþlangýç rengine boyanýyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //çizimde kullanýlacak olan program nesnesi aktif ediliyor
        glUseProgram(shaderProgram);
        //çizimde kullanýlacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //kare
        if (randSekil1 == 1 || randSekil2==1)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(kare), kare, GL_STATIC_DRAW);
            setVec3("uMove", positionK);
            setVec4("uColor", kareColor);
            positionK += glm::vec3(kx, ky, 0.0f);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        //ücgen
        if (randSekil1 == 2 || randSekil2 == 2)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(ucgen), ucgen, GL_STATIC_DRAW);
            setVec3("uMove", positionU);
            setVec4("uColor", ucgenColor);
            positionU += glm::vec3(ux, uy, 0.0f);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        //daire
        if (randSekil1 == 3 || randSekil2 == 3)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cember.size(), &cember[0], GL_STATIC_DRAW);
            setVec3("uMove", positionC);
            setVec4("uColor", cemberColor);
            positionC += glm::vec3(cx, cy, 0.0f);
            glDrawArrays(GL_TRIANGLES, 0, cember.size());
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
