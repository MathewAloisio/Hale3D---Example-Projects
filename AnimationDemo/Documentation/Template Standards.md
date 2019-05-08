# Project Template Stanards - Hale3D #
------------------------------------------------------------------------------
## Template lookup and registration. ##
* The *Hale3DEditorAPI* library will by default search for templates in the ```Templates``` folder of ***the directory that contains your engine data***. (Example: ```C:\Users\%username%\My Documents\Hale3D\Templates\```)
* When using a custom editor, or utilizes the API's Lua plugin system, You may call the recursive function ```Hale3D::Editor::RegisterTemplate(string pPath)``` to register all templates within the provided directory and subdirectories. Note that this function can also be passed a direct path to a ```.template``` file to register only a single template.
* The *Hale3DEditorAPI* library will look for the ```.template``` file which contains the following information:

|      Property      |      Description      |
| ------------------ | --------------------- |
| name               | The name of the template that will appear in menus, or               be used in console commands.                 |
* Below is an example of the ```.template``` file and folder hierachy of the ***Generic*** project template:
##### Template file: ######
```
// .template file
name="Generic"
```

###### Folder hierachy: ######
```
Generic
	.template
```
* As we can see from the above example, technically the only file required to make a valid template is the ```.template``` file. All files and folders within the same directory of this ```.template``` file will be created and added to the folder containing the newly created project, the ```.template``` file will not be copied into the new project.


## Template tag-and-replace system. ##
### ***(I)*** Hale3DEditor uses a simple tag system to find replace-able occurrences in file names, folder names and their contents. The convention is as follows: ###

>***(1.a) Engine tag style:***
>* Two preceding _'s, the letters h3d, an _, the tag-name,  followed by two trailing _'s. 
>* Two trailing underscores are used instead of one so tag-names may contain the _ character.
>
>* ```__h3d_tagname__```
>
>***(1.b) Folder name example:***
>
>Lets say we have a project named X, the template X was build off of contains the folder:
>
>```MyProject/__h3d_projname___Resources/```
>
>In the project, X, this folder would be renamed as:
>
>```MyProject/X_Resources/``` 

 
### ***(II)*** The Hale3DEditor will automatically rename files/folders & occurrences in their contents based on the following table: ###
>***(2.a) Name conversion table:***
> |     Tag name     |                   Resolves to                  |
> | ---------------- | ---------------------------------------------- |
> | projname         | Name of newly created project.                 |
> | projname_upper   | Uppercase name of newly created project.       |
> | enginename       | The name of the engine, see ```ENGINE_NAME```. |
> | enginedatadir    | The directory that contains your engine data.  |
> | engineinstalldir | The directory that contains the game engine.   |
