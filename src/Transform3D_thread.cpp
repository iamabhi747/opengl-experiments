#include <custom.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

void Transform3D_thread(OB_Context *context, GLfloat *vertices, GLint size)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "=======================================" << std::endl;
    std::cout << "    Welcome to Transform Engine!!!" << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "         Operations Supported         " << std::endl << std::endl;
    std::cout << "1. Translation: translate x y z" << std::endl;
    std::cout << "2. Rotation   : rotatex angle" << std::endl;
    std::cout << "              : rotatey angle" << std::endl;
    std::cout << "              : rotatez angle" << std::endl;
    std::cout << "3. Scaling    : scale x y z" << std::endl;
    std::cout << "4. Reflection : reflectxy z" << std::endl;
    std::cout << "              : reflectyz x" << std::endl;
    std::cout << "              : reflectxz y" << std::endl << std::endl;
    std::cout << "* Center of transformation" << std::endl;
    std::cout << "  in 2, 3 you can use @ x y z" << std::endl;
    std::cout << "  to set the center of transformation" << std::endl;
    std::cout << "  default is center of window (600, 450, 0)" << std::endl;
    std::cout << "=======================================" << std::endl;
    float transformationMatrix[4][4];

    std::string command;
    while (!glfwWindowShouldClose(context->window)) {
        std::cout << "Your Command : ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        std::istringstream iss(command);
        std::string operation;
        iss >> operation;
        IdentityMatrix3D(transformationMatrix);
        float cx = 600, cy = 450, cz = 0;

        if (operation == "translate") {
            float x, y, z; iss >> x >> y >> z;
            Translate3D(transformationMatrix, x, y, z);
        } else if (operation == "rotatex") {
            float angle; iss >> angle;
            angle = angle * 3.14159 / 180;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy >> cz; }
            RotateX3D(transformationMatrix, angle, cx, cy, cz);
        } else if (operation == "rotatey") {
            float angle; iss >> angle;
            angle = angle * 3.14159 / 180;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy >> cz; }
            RotateY3D(transformationMatrix, angle, cx, cy, cz);
        } else if (operation == "rotatez") {
            float angle; iss >> angle;
            angle = angle * 3.14159 / 180;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy >> cz; }
            RotateZ3D(transformationMatrix, angle, cx, cy, cz);
        } else if (operation == "scale") {
            float x, y, z; iss >> x >> y >> z;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy >> cz; }
            Scale3D(transformationMatrix, x, y, z, cx, cy, cz);
        } else if (operation == "reflectxy") {
            float z; iss >> z;
            ReflectXY3D(transformationMatrix, z);
        } else if (operation == "reflectyz") {
            float x; iss >> x;
            ReflectYZ3D(transformationMatrix, x);
        } else if (operation == "reflectxz") {
            float y; iss >> y;
            ReflectXZ3D(transformationMatrix, y);
        } else {
            std::cout << "Invalid command" << std::endl;
            continue;
        }

        ApplyTransformation3D(transformationMatrix, vertices, size);
    }

    std::cout << "Exiting Transform Engine" << std::endl;
    glfwSetWindowShouldClose(context->window, GLFW_TRUE);
}