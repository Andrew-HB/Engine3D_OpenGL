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

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        unsigned int indices[]{
            0, 1, 2,
            2, 3, 0
        };

        Object object3d("res/objects/cube.obj");

        Engine engine(480, 640, object3d);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(1);

        Shader shader("res/shaders/Basic.shader");
        //shader.Bind();
        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        //shader.Unbind();

        Renderer renderer;

        float fElapsedTime;

        std::chrono::system_clock::time_point prevT;

        //float r = 0.0f;
        //float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            std::chrono::duration<float> elapsedTime = std::chrono::system_clock::now() - prevT;
            prevT = std::chrono::system_clock::now();
            fElapsedTime = elapsedTime.count();

            std::vector<triangle> positions = engine.Update(fElapsedTime);
            Object glObject;
            glObject.ConvertObject(positions);

            VertexArray va;
            VertexBuffer vb(&glObject.positions[0], sizeof(glObject.positions));

            va.AddBuffer(vb, layout);

            IndexBuffer ib(&glObject.indices[0], glObject.indices.size());

            shader.Bind();
            //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);

            //if (r > 1.0f)
            //    increment = -0.05f;
            //else if (r < 0.0f)
            //    increment = 0.05f;
            //
            //r += increment;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    }
    glfwTerminate();
    return 0;
}