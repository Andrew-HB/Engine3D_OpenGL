#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Object.h"
#include "Engine.h"

#include <chrono>

#define width 640
#define height 480

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initalization error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        Object object3d("res/objects/cube.obj");

        Engine engine(height, width, object3d);

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(1);

        Shader shader("res/shaders/Basic.shader");

        Renderer renderer;

        float fElapsedTime;

        std::chrono::system_clock::time_point prevT;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            std::chrono::duration<float> elapsedTime = std::chrono::system_clock::now() - prevT;
            prevT = std::chrono::system_clock::now();
            fElapsedTime = elapsedTime.count();

            std::vector<triangle> positions = engine.Update(fElapsedTime);
            for (int i = 0; i < positions.size(); i++) {

                positions[i].p[0].x = (positions[i].p[0].x - width / 2) / width;
                positions[i].p[0].y = (positions[i].p[0].x - height / 2) / height;
                positions[i].p[1].x = (positions[i].p[1].x - width / 2) / width;
                positions[i].p[1].y = (positions[i].p[1].x - height / 2) / height;
                positions[i].p[2].x = (positions[i].p[2].x - width / 2) / width;
                positions[i].p[2].y = (positions[i].p[2].x - height / 2) / height;
            }

            Object glObject;
            glObject.ConvertObject(positions);

            VertexArray va;
            VertexBuffer vb(static_cast<void*>(glObject.positions.data()), sizeof(float) * glObject.positions.size());

            va.AddBuffer(vb, layout);

            IndexBuffer ib(static_cast<unsigned int*>(glObject.indices.data()), glObject.indices.size());

            std::cout << glObject.indices.size() << std::endl;

            shader.Bind();

            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    }
    glfwTerminate();
    return 0;
}