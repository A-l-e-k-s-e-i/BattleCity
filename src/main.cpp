#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int g_WindowSizeX = 640;
int g_WindowSizeY = 480;
        
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) /*Функция изменения окна*/
{
    g_WindowSizeX = width;
    g_WindowSizeY = height;
    glViewport(0, 0, g_WindowSizeX, g_WindowSizeY); /*Передаём параметры где мы хотим рисовать*/
}
/*******************************/
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)  /*Функция обработки клавиш*/
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  /*Проверяем если нажата ESC и было нажатие*/
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);      /*Указываем glfw что мы хотим закрыть окно. Устанавливаем флаг TRUE */
    }
}
/*******************************/


int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Создаём окно. Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSizeX, g_WindowSizeY, "BattleCity", nullptr, nullptr);
    if (!pWindow)  /*выводим ошибку если окно не создалось*/
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback); /*Функция активируется при изменении окна*/
    glfwSetKeyCallback(pWindow, glfwKeyCallback); /*Функция активируется при нажатии клавиш клавиатуры*/


       /* Делаем контекст OpenGL для текущего окна Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL()) /*Инициализируем glad выводим ошибку если неуспешно*/
	{
		std::cout << "Can't load GLAD!" <<std::endl;
		return -1;
	}



        std::cout << "Renderer: " << glGetString(GL_RENDERER) <<std::endl;
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		
		glClearColor(1, 1, 0, 1);


    /* Главный цикл отрисовки */
    while (!glfwWindowShouldClose(pWindow)) /*Проверяем состояние окна если закрыто то выходим из цикла*/
    {
        /* Очищаем буфер цвета. Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Меняем местами буфер отрисовки. Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Обрабатываем события (мыш, клавиатура и тд.) Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate(); /* Освобождаем ресурсы после выхода из окна*/
    return 0;
}