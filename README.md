# 🧮 BinConverter

**BinConverter** is a simple **GUI application** that converts binary files (such as `.png`, `.jpg`, `.wav`, `.mp3`, etc.) into a **Lua table** or **C-style byte array**. This tool is useful for embedding binary assets directly into source code.

---

## ✨ Features

- Converts binary files into:
  - **Lua tables**
  - **C-style arrays**
- Drag-and-drop or file dialog support
- Clean UI with **Dear ImGui**
- Cross-platform GUI (Windows/Linux*)
- Written in **Modern C++20**

---

## 🧰 Dependencies

- [Dear ImGui](https://github.com/ocornut/imgui)
- [NativeFileDialog-Extended (nfd)](https://github.com/btzy/nativefiledialog-extended)
- [SDL2](https://github.com/libsdl-org/SDL)

> 📦 Package management with **vcpkg** recommended

---

## 🛠️ Build Instructions

### ✅ Windows

```bash
git clone https://github.com/dwjclark11/BinConverter.git
cd BinConverter
./vcpkg install sdl2
cmake -S . -B build
cmake --build build --config Release
```
You can also open the build/BinConverter.sln file in Visual Studio.

## ⚠️ Linux
| ❗ Linux build is currently failing
To attempt a build on Linux, install the **GTK** dependency for **NativeFileDialog**:
```bash
sudo apt install libgtk-3-dev
```
Then run:
```bash
git clone https://github.com/dwjclark11/BinConverter.git
cd BinConverter
cmake -S . -B build
cmake --build build --config Release
```
--- 

## 🖼️ UI Preview
![image](https://github.com/dwjclark11/BinConverter/assets/63356975/97ae1698-c3b5-4167-b9d9-0386d5198a45)

---

## 📋 Desired Functionality / TODOs
* **Validate table name input:**
  * Table names can no longer include spaces — they are replaced with underscores (_).
  * Numbers are also filtered out as needed.
* **File type filtering:**
  * When uploading or dropping files, currently all file types are accepted. This should be restricted to supported formats only.
* **Overwrite warning for output files:**
  * If the output file already exists, a confirmation popup should appear asking the user whether to:
    * Overwrite the existing file
    * Append to the bottom of the file

## 📺 YouTube Series
Part of the **JADE-ite Games and Programming** educational content:
* [YouTube Channel – JADE-ite Games](https://www.youtube.com/@JADE-iteGames)

## 📄 License
This project is licensed under the MIT License. See [LICENSE](https://github.com/dwjclark11/BinConverter/blob/master/LICENSE) for details.
