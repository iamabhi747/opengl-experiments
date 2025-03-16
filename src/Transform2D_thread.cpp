#include <custom.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

void Transform2D_thread(OB_Context *context, GLfloat *vertices, GLint size)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "=======================================" << std::endl;
    std::cout << "    Welcome to Transform Engine!!!" << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "         Operations Supported         " << std::endl << std::endl;
    std::cout << "1. Translation: translate x y" << std::endl;
    std::cout << "2. Rotation   : rotate angle" << std::endl;
    std::cout << "3. Scaling    : scale x y" << std::endl;
    std::cout << "4. Shearing   : shear x y" << std::endl;
    std::cout << "5. Reflection : reflectx x" << std::endl;
    std::cout << "              : reflecty y" << std::endl << std::endl;
    std::cout << "* Center of transformation" << std::endl;
    std::cout << "  in 2, 3, 4 you can use @ x y" << std::endl;
    std::cout << "  to set the center of transformation" << std::endl;
    std::cout << "  default is center of window (600, 450)" << std::endl;
    std::cout << "=======================================" << std::endl;
    float transformationMatrix[3][3];

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
        IdentityMatrix2D(transformationMatrix);
        float cx = 600, cy = 450;

        if (operation == "translate") {
            float x, y; iss >> x >> y;
            Translate2D(transformationMatrix, x, y);
        } else if (operation == "rotate") {
            float angle; iss >> angle;
            angle = angle * 3.14159 / 180;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy; }
            Rotate2D(transformationMatrix, angle, cx, cy);
        } else if (operation == "scale") {
            float x, y; iss >> x >> y;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy; }
            Scale2D(transformationMatrix, x, y, cx, cy);
        } else if (operation == "shear") {
            float x, y; iss >> x >> y;
            char c; iss >> c;
            if (c == '@') { iss >> cx >> cy; }
            Shear2D(transformationMatrix, x, y, cx, cy);
        } else if (operation == "reflectx") {
            float cy; iss >> cy;
            ReflectX2D(transformationMatrix, cy);
        } else if (operation == "reflecty") {
            float cx; iss >> cx;
            ReflectY2D(transformationMatrix, cx);
        } else {
            std::cout << "Invalid command" << std::endl;
            continue;
        }

        ApplyTransformation2D(transformationMatrix, vertices, size);
    }

    std::cout << "Exiting Transform Engine" << std::endl;
    glfwSetWindowShouldClose(context->window, GLFW_TRUE);
}