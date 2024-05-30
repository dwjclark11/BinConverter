# BinConverter
Simple GUI application that will take in a binary files such as a PNG, JPG, WAV, MP3, etc, and convert the 
binary file into a lua table or a C-Style array. 

It uses [Dear ImGui](https://github.com/ocornut/imgui) for the user interface, [NativeFileDialog-Extended](https://github.com/btzy/nativefiledialog-extended) for 
opening the necessary file dialogs. It also uses [SDL2](https://github.com/libsdl-org/SDL) for windowing and processing events. 

## Build
* Install dependencies ```./vcpkg install sdl2```
* Clone the repository ```https://github.com/dwjclark11/BinConverter.git```
* Get into the ```BinConverter``` directory and run ```cmake -S . -B build```
* Get into the ```build``` directory and run ```cmake --build . --config Debug``` or ```--config Release```
 * If you are using ```MSVC``` you can build from the ```.sln``` that was created in the ```build``` dir. 

![image](https://github.com/dwjclark11/BinConverter/assets/63356975/97ae1698-c3b5-4167-b9d9-0386d5198a45)

### Desired Functionality
* ~~When user is inputting the name of the table, currently there can be numbers and spaces. This needs to be checked and either a warning displayed or automatically changed to something else. Like turn spaces into ```_```.~~ Added
* Add filters for specific file types. For when we are uploading (or Dropping) files, we want to ensure that it is a supported type. Currently it accepts all files --> NOT DESIRED.
* If the out file already exists, we need to add a pop up that asks the user if they want to overwrite the file or append to the bottom.
