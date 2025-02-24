# cgopengl
A repo for my computer graphic with Open GL. 

You may also use this template. If you are new to OpenGL, you can follow these steps. 

## Complete Guide: Setting Up OpenGL with GLEW, GLFW, and FreeGLUT in Visual Studio 2022.
This guide will walk you through installing and configuring OpenGL, GLEW, GLFW, and FreeGLUT in Visual Studio 2022 (MSVC) for OpenGL development.

### 📌 Step 1: Install Visual Studio 2022 & Windows SDK

1️⃣ Install Visual Studio 2022
1. Download and install Visual Studio 2022 Community from: https://visualstudio.microsoft.com/downloads/
2. During installation, select the following components:
   * Desktop development with C++
   * Windows 10 or 11 SDK
   * C++ CMake tools for Windows (optional but recommended)

2️⃣ Verify Windows SDK Installation
   * Go to: C:\Program Files (x86)\Windows Kits\10\Lib
   * If you see folders like 10.0.19041.0, then the Windows SDK is installed.
   * If opengl32.lib is missing, reinstall the Windows SDK from the Visual Studio Installer.

### 📌 Step 2: Download and Install OpenGL Libraries
We will install GLEW, GLFW, and FreeGLUT manually.

1️⃣ Install GLEW
🔹 Download GLEW 2.2.0 (Windows 64-bit Precompiled binaries): https://glew.sourceforge.net/index.html
1. Extract it to: `C:\Libraries\GLEW\`
2. Ensure the extracted folders contain: 
```
C:\Libraries\GLEW\include\GL\ (Contains glew.h)
C:\Libraries\GLEW\lib\Release\x64\ (Contains glew32.lib)
C:\Libraries\GLEW\bin\Release\x64\ (Contains glew32.dll)
```
2️⃣ Install GLFW
🔹 Download GLFW 3.3.8 (Windows Precompiled Binaries): https://www.glfw.org/download.html
1. Extract it to: `C:\Libraries\GLFW\`
2. Ensure the extracted folders contain:  
```
C:\Libraries\GLFW\include\GLFW\ (Contains glfw3.h)
C:\Libraries\GLFW\lib-vc2022\ (Contains glfw3.lib)
```
3️⃣ Install FreeGLUT
🔹 Download FreeGLUT 3.2.1 (MSVC Precompiled): https://www.transmissionzero.co.uk/software/freeglut-devel/
1. Extract it to: `C:\Libraries\FreeGLUT\`
2. Ensure the extracted folders contain:
```
C:\Libraries\FreeGLUT\include\ (Contains freeglut.h)
C:\Libraries\FreeGLUT\lib\x64\ (Contains freeglut.lib)
C:\Libraries\FreeGLUT\bin\x64\ (Contains freeglut.dll)
```

### 📌 Step 3: Configure Visual Studio 2022
1️⃣ Open Visual Studio and Create a New Project
1. Open Visual Studio 2022
2. Create a new project → C++ Console Application
3. Right-click the project → Properties
4. Set "Configuration" to "All Configurations" (top-left dropdown)

2️⃣ Add Include Directories
1. Go to: C/C++ → General → Additional Include Directories
2. Click Edit → Add:
```
C:\Libraries\GLEW\include
C:\Libraries\GLFW\include
C:\Libraries\FreeGLUT\include
```
3️⃣ Add Library Directories
1. Go to: Linker → General → Additional Library Directories
2. Click Edit → Add:
```
C:\Libraries\GLEW\lib\Release\x64
C:\Libraries\GLFW\lib-vc2022
C:\Libraries\FreeGLUT\lib\x64
```

4️⃣ Link Necessary Libraries
1. Go to: Linker → Input → Additional Dependencies
2. Click Edit → Add:
```
glew32.lib
glfw3.lib
freeglut.lib
opengl32.lib
```

### 📌 Step 4: Copy DLL Files to Project Directory
After building your project, your .exe will require GLEW, GLFW, and FreeGLUT DLLs.

Find and copy these DLLs:
```
C:\Libraries\GLEW\bin\Release\x64\glew32.dll
C:\Libraries\FreeGLUT\bin\x64\freeglut.dll
```
Paste them in your project’s output folder (next to your .exe file):
```
C:\YourProject\Debug\
C:\YourProject\Release\
```

### 📌 Step 5: Test OpenGL Setup
Now, test if OpenGL is working by compiling this simple OpenGL program using GLEW, GLFW, and FreeGLUT: 
```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    // Initialize FreeGLUT
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL with FreeGLUT, GLEW, and GLFW");

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
```

### 📌 Step 6: Build and Run the Project
1. Build the project: Press Ctrl + Shift + B
2. Run the program: Press F5
3. If a window appears, OpenGL is set up correctly! 🎉
---
Alternatively, you may also check other setup tutorial: https://www.wikihow.com/Set-Up-an-OpenGL-FreeGLUT-GLEW-Template-Project-in-Visual-Studio 
