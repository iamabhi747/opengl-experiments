#include <custom.h>

void PrintOpenGLErrors(char const *const Function, char const *const File, int const Line)
{
    GLenum Error = glGetError();
    if (Error != GL_NO_ERROR)
    {
        const char *ErrorString;
        switch (Error)
        {
        case GL_INVALID_ENUM:
            ErrorString = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            ErrorString = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            ErrorString = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            ErrorString = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            ErrorString = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_CONTEXT_LOST:
            ErrorString = "CONTEXT_LOST";
            break;
        default:
            ErrorString = "UNKNOWN_ERROR";
            break;
        }
        std::cerr << "OpenGL Error in " << File << " at line " << Line << " calling function " << Function << ": " << ErrorString << std::endl;
    }
}

#ifdef OB_DEBUG
#define CheckedGLCall(x)                                         \
    do                                                           \
    {                                                            \
        PrintOpenGLErrors(">>BEFORE<< " #x, __FILE__, __LINE__); \
        (x);                                                     \
        PrintOpenGLErrors(#x, __FILE__, __LINE__);               \
    } while (0)
#define CheckedGLResult(x) (PrintOpenGLErrors(#x, __FILE__, __LINE__), (x))
#define CheckExistingErrors(x) PrintOpenGLErrors(">>BEFORE<< " #x, __FILE__, __LINE__);
#else
#define CheckedGLCall(x) (x)
#define CheckedGLResult(x) (x)
#define CheckExistingErrors(x)
#endif

void PrintShaderInfoLog(GLint const Shader)
{
    int InfoLogLength = 0;
    int CharsWritten = 0;

    glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0)
    {
        GLchar *InfoLog = new GLchar[InfoLogLength];
        glGetShaderInfoLog(Shader, InfoLogLength, &CharsWritten, InfoLog);
        std::cout << "Shader Info Log:" << std::endl
                  << InfoLog << std::endl;
        delete[] InfoLog;
    }
}

std::string LoadShaderFromFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open shader file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint CompileShader(const std::string &path, GLenum shaderType)
{
    std::string shaderSource = LoadShaderFromFile(path);
    const char *source = shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        PrintShaderInfoLog(shader);
        throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
    }

    return shader;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW (OpenGL version 2.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Create window
    GLFWwindow *window = glfwCreateWindow(640, 480, "Modern OpenGL", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        const char *description;
        glfwGetError(&description); // Get the error description
        std::cerr << "GLFW Error: " << description << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    // Print OpenGL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Init OpenglBase
    OB_Context *context = OB_InitContext();

#ifdef OB_ENABLE_SHADER

    // Create and populate vertex buffer
    GLuint VBO;
    CheckedGLCall(glGenBuffers(1, &VBO));
    CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, context->Vertices.size() * sizeof(GLfloat), context->Vertices.data(), GL_STATIC_DRAW));

    // Create and populate element buffer
    GLuint EBO;
    CheckedGLCall(glGenBuffers(1, &EBO));
    CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, context->Elements.size() * sizeof(GLfloat), context->Elements.data(), GL_STATIC_DRAW));

    // Create and compile vertex shader
    GLuint VertexShader = CompileShader(OB_VERTSHADER_PATH, GL_VERTEX_SHADER);

    // Create and compile fragment shader
    GLuint FragmentShader = CompileShader(OB_FRAGSHADER_PATH, GL_FRAGMENT_SHADER);

    // Create and link shader program
    GLuint ShaderProgram = CheckedGLResult(glCreateProgram());
    CheckedGLCall(glAttachShader(ShaderProgram, VertexShader));
    CheckedGLCall(glAttachShader(ShaderProgram, FragmentShader));
    CheckedGLCall(glLinkProgram(ShaderProgram));
    CheckedGLCall(glUseProgram(ShaderProgram));

    // Setup vertex attributes
    GLint PositionAttribute = CheckedGLResult(glGetAttribLocation(ShaderProgram, "position"));
    CheckedGLCall(glEnableVertexAttribArray(PositionAttribute));
    CheckedGLCall(glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0));

#endif

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

#ifdef OB_ENABLE_SHADER

        CheckedGLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));

#else

        glBegin(OB_DRAW_MODE);
        OB_Render(context);
        glEnd();

#endif

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
#ifdef OB_ENABLE_SHADER
    CheckedGLCall(glDeleteProgram(ShaderProgram));
    CheckedGLCall(glDeleteShader(FragmentShader));
    CheckedGLCall(glDeleteShader(VertexShader));
    CheckedGLCall(glDeleteBuffers(1, &EBO));
    CheckedGLCall(glDeleteBuffers(1, &VBO));
#endif

    glfwTerminate();
    return 0;
}