# 🧊 Model Loading UI

A lightweight desktop application for loading and rendering 3D models using a GTK4-based interface and an OpenGL backend. Built with CMake for cross-platform flexibility, this tool supports `.obj`, `.fbx`, and `.glb` formats and integrates real-time rendering with interactive camera controls.

---

## 🚀 Features

- 📁 **File Dialog Integration** — Browse and select 3D model files via GTK4's modern file picker
- 🧵 **Asynchronous UI** — Non-blocking file selection and rendering launch
- 🧠 **Model Parsing** — Uses Assimp to load meshes, materials, and textures
- 🎨 **Texture Support** — Handles both embedded and external textures via `stb_image`
- 🧭 **Camera Navigation** — WASD movement, mouse look, and scroll-based zoom
- 🖥️ **OpenGL Renderer** — Real-time rendering with lighting and shader support
- 🛠️ **CMake Build System** — Modular and portable across Linux, Windows, and macOS

---

## 🧰 Dependencies

- **GTK4** (UI framework)
- **GLFW** (OpenGL context/window creation)
- **GLAD** (OpenGL function loader)
- **Assimp** (model loading)
- **stb_image** (texture decoding)
- **glm** (math library)
- **CMake** (build system)

---

## 🛠️ Build Instructions

### Prerequisites

Ensure the following libraries are installed and discoverable by CMake:

- GTK4 development headers
- CMake ≥ 3.16
- A C++17-compatible compiler
- OpenGL drivers

### Build Steps

```bash
git clone https://github.com/thelastgoth128/Model_Loading-UI.git
cd Model_Loading-Ui
mkdir build && cd build
cmake ..
cmake --build . --config Release
