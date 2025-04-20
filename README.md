# wxGL Demo App

This is a desktop application built using **wxWidgets** and **OpenGL**. The app demonstrates 2D rendering with interactive UI elements like sliders, checkboxes, and OpenGL-rendered buttons. It is designed for cross-platform usage and can be built on any local machine with standard development tools.

## Features

- Rendered triangle, rectangle, and circle shapes using OpenGL
- Rotatable shapes using a wxSlider
- Toggle rectangle visibility with a wxCheckBox
- Clickable OpenGL-based button that toggles the side panel
- Responsive layout using wxWidgets sizers

---

## Build Instructions

### ✅ Prerequisites

- C++ Compiler (GCC, Clang, or MSVC)
- CMake (recommended version 3.10+)
- wxWidgets (see installation below)
- OpenGL development libraries (`libGL`, `libGLU`, or platform equivalents)

### 🛠️ Installing wxWidgets

Follow the official instructions based on your platform:  
👉 [https://www.wxwidgets.org/downloads/](https://www.wxwidgets.org/downloads/)

---

## 💻 Building the Application

1. Clone the repository:

```bash
git clone https://github.com/yapa-ymtl/wxgl-demo-app.git
cd wxgl-demo-app
```

2. Create a `build` directory and run CMake:

```bash
mkdir build
cd build
cmake ..
```

3. Build the application:

```bash
make
```

4. Run the executable:

```bash
./demoApp      # On Linux/macOS
demoApp.exe    # On Windows
```

---
> ⚠️ **Note**: If the button icon (`.png`)  is not visible, please create a directory named `assets/` in the build area and place the `button.png` file inside it.

## 📁 Project Structure

```
wxgl-demo-app/
├── assets/              # PNG assets (button images)
├── include/             # Header files
│   ├── canvas.h
│   ├── mainfram.h
│   └── sidepanel.h
├── src/                 # Source files
│   ├── canvas.cpp
│   ├── mainfram.cpp
│   └── sidepanel.cpp
├── CMakeLists.txt       # Build configuration
└── README.md
```

---

## 📝 Notes

- Tested on macOS.

---
