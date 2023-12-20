# DGameMaker

The engine with the will of D.

Check our full project page for more info about DGameEngine [GitHub Link](https://github.com/CITM-UPC/DGameMaker) 

### Members

- Francisco Ferrerós Puigmartí --> [kikofp02](https://github.com/kikofp02)
- Jan Neto Llorens --> [JanNetoLlorens](https://github.com/JanNetoLlorens)

## Windows

- Docking of any of the following windows available
- Windows can be hiden

### Hierarchy

- Any file droped is put under a gameObject parent which makes easier to keep an organised the hierarchy
- Where you see the gameObjects loaded in your scene
- Click on them to display their components and information in the inspector
- The Arrow allows to see the children of the parent
- Right click on any gameObject pops up a delete window which enables deletion for a gameObject and its childs

### Inspector

- The inspector shows the information relative to the gameObject selected

- Components:
  - Transform: Display the position, rotation and scale
  - Mesh: Display the information relative to the mesh (numVertex, numIndex, filepath, etc)
  - Texture: Display the information relative to the texture (filepath, isActive, etc
  - Camera: move around the scene through it
    
- Edition:
  - Tranform: Change the position, rotation and scale of the gameObject selected
  - Mesh: switch active state
  - Texture: in progress
  - Camera: in proguess
  - GameObject: switch active state

### Project

- On the left displays a tree of the files found inside the Assets library, it is possible to navigate through them
- On the right displays the files inside the selected library
 
### Console

- See the logs of the project

### Settings

- Menu to acces to the settings of the game engine

#### Video Settings

- Change resolution of the screen
- Change window type (fullscreen, resizable, fullscreen desktop, normal)
- On/Off borderless
- Change the brightness
- Change target FPS
- On/Off VSync
- Check current update time in ms

#### Controls

- Camera:
  - W --> forward
  - A --> left
  - S --> backward
  - D --> right
    
  - Space --> up
  - CTRL --> down
  - Alt + Rightclick --> panning
  - Rightclick --> rotate the gamera 
  - F center to the selected gameObject

#### Renderer

- Nothing yet

#### System Details

- Check library versions (SDL, DevIl, ImGui, GLEW, Graphical controllers Version/Vendor)
- Your PC specifications (CPU cores, GPU, RAM, VRAM budget/used/available)

#### Help

- Menu with info about the engine (description, members, resources, license)
- Download last version of the engine
- Report bugs
- GitHub repository link
- Contact us, link to our organization










