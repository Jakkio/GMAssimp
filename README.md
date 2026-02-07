# 🎮 GMAssimp

[![GameMaker](https://img.shields.io/badge/GameMaker-LTS-blue.svg)](https://www.gamemaker.io/)
[![Assimp](https://img.shields.io/badge/Assimp-5.3.1-green.svg)](https://www.assimp.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

**GMAssimp** is a professional-grade port of the **Open Asset Import Library (Assimp)** for GameMaker. It provides a robust bridge between high-performance C++ asset processing and the ease of use of GML, allowing developers to import, manipulate, and visualize over 40 3D model formats with AAA precision.

---

## 🚀 Key Features

- **Multi-Format Support:** Import `.fbx`, `.obj`, `.gltf`, `.glb`, `.blend`, `.dae`, `.stl`, and many more.
- **Scene Hierarchy:** Full access to node structures, transformations, and parent-child relationships.
- **Advanced Mesh Data:** Direct access to vertices, normals, tangents, bitangents, colors, and multiple UV channels.
- **Animation System:** Support for skeletal animations (bones) and morph targets (anim-meshes).
- **Embedded Textures:** Automatically handles embedded textures by converting them from Base64 to native GameMaker sprites.
- **Powerful Post-Processing:** Over 30 optimization flags (triangulation, normal generation, mesh optimization, UV flipping, etc.).

---

## 📦 Supported Formats

Powered by Assimp, GMAssimp supports a vast array of formats, including:

- **Common:** FBX, OBJ, GLTF/GLB, Collada (DAE), Blender (.blend)
- **CAD/Industry:** STEP, IFC, IGES
- **Gaming:** MD3, MDL, MS3D, X
- **3D Printing:** STL, PLY, AMF
- ... and many others!

---

## 🛠️ Direct DLL Usage

If you want to use the extension (dll) directly, the functions are basically the same as assimp and you can use the original documentation. All of them have the "ASSIMP_" prefix, and have a different naming convention, for historical reasons of this lib. The only differences are that it works by using the "Bind" functions to make a specific struct the selected one, and then it will be used as context for the other functions. Also every function that returns vectors/matrices/arrays is decomposed for specific values, one at a time.

---

## 📖 Quick Start

Importing a model is as simple as writing a few lines of code:

```gml
// 1. Initialize the importer
var importer = new aiImporter();

// 2. Load the file with desired flags
var scene = importer.ReadFile(working_directory + "model.glb", 
    aiProcess.TRIANGULATE | 
    aiProcess.FLIP_UVS | 
    aiProcess.GEN_SMOOTH_NORMALS |
    aiProcess.OPTIMIZE_MESHES
);

// 3. Check if loading was successful
if (scene != undefined) {
    // Access model data
    var num_meshes = scene.mNumMeshes;
    show_debug_message("Model loaded with " + string(num_meshes) + " meshes!");
    
    // Example: Access the first mesh
    var mesh = scene.mMeshes[0];
    show_debug_message("Mesh name: " + mesh.mName);
} else {
    show_debug_message("Loading error: " + importer.mErrorString);
}
```

---

## ⚙️ Post-Processing Flags

GMAssimp provides granular control over the import process via post-processing flags:

- `aiProcess.TRIANGULATE`: Converts all polygons to triangles (essential for GM).
- `aiProcess.GEN_SMOOTH_NORMALS`: Generates smooth normals if missing.
- `aiProcess.FLIP_UVS`: Flips UV coordinates on the Y-axis (often required for GM textures).
- `aiProcess.JOIN_IDENTICAL_VERTICES`: Optimizes the mesh by joining duplicate vertices.
- `aiProcess.LIMIT_BONE_WEIGHTS`: Limits weights per bone for shader compatibility.

---

## 🏛️ Module Architecture & Technical Notes

GMAssimp is designed to be a direct GML mirror of the Assimp C++ API:

- **`aiScene`**: The root structure. It manages the lifecycle of imported data and handles the automatic conversion of embedded textures into GameMaker sprites.
- **`aiMesh`**: Contains geometry, vertex data, and bone weights.
- **`aiMaterial`**: Exposes material properties and texture mapping info.
- **`aiAnimation`**: Stores skeletal animation channels and keyframes.
- **`aiNode`**: Represents the transformation hierarchy of the scene.

**Note:** This port focuses on maintaining the original Assimp structure while optimizing for GML's memory management and constructor system.

---

## 🌍 Platform Compatibility

In theory, the code is not OS/target dependent, so it should be compatible with every target supported by Assimp. However, currently, only Windows binaries are provided.

---

## 🤝 Contributing

Contributions are welcome! If you find a bug or have an idea for a new feature, please open an Issue or submit a Pull Request.

**Specific Needs:**
Since the library is theoretically platform-agnostic, **contributions to compile and provide binaries for other targets** (macOS, Linux, Android, iOS, etc.) are highly appreciated and will help expand the reach of GMAssimp.

---

## 📄 License

This project is distributed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## ✨ Credits

- Developed by **Giacomo Marton** ([@GiacomoMarton](https://github.com/GiacomoMarton)).
- Based on the amazing [Assimp](https://github.com/assimp/assimp) library.

---

<p align="center">
  Built with ❤️ for the GameMaker community.
</p>
