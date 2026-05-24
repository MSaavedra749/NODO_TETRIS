# NODO_TETRIS
Implementación del juego Tetris en C utilizando las librerías GBT.

## Requisitos previos
- Compilador: Code::Blocks 25.03 mingw-nosetup
- Librería: [libgbt](https://gitlab.com/RodrigoMaranzana/libgbt-dist)

## Compilación del proyecto

### 1. Crear el proyecto en Code::Blocks
1. En Code::Blocks, seleccionar `File > New > Project`.
2. Elegir la opción `Console application` y el lenguaje `C`.
3. Asignar un nombre al proyecto y guardarlo en una carpeta vacía.

### 2. Agregar los archivos al proyecto
- Descargar este proyecto completo y extraerlo dentro de la carpeta del proyecto de Code::Blocks.
- Descargar la librería `libgbt` y extraer la carpeta `releases` dentro de la carpeta del proyecto de Code::Blocks.
- En Code::Blocks, ubicar el nombre del proyecto en el panel izquierdo y hacer clic derecho.
- Seleccionar `Add files` en el menú contextual.
- Añadir todos los archivos `.c` y `.h` del proyecto.
- En la ventana de adición, asegurarse de que las opciones `Debug` y `Release` estén marcadas.

### 3. Configurar el linker
- Hacer clic derecho en el nombre del proyecto y seleccionar `Build options`.
- En la pestaña `Linker`, agregar el texto: `-lGBT -lm`.
- En la pestaña `Search directories`, hacer clic en `Add` y buscar la carpeta `release\GBT_v2026.1c.01\include\`.
- Luego seleccionar la subpestaña `Linker` y hacer clic en `Add` para agregar la carpeta `release\GBT_v2026.1c.01\lib`.

### 4. Compilar
- Presionar el botón de tuerca en la barra de herramientas superior de Code::Blocks.
- Cuando aparezca en la consola el mensaje `Build finished`, el proyecto estará correctamente compilado.

## Instalación y ejecución
- Navegar a la carpeta del proyecto y buscar el archivo `gbt.dll` en `release\GBT_v2026.1c.01\bin\`.
- Copiar `gbt.dll` a la carpeta `bin\debug\` junto con el archivo `.exe` generado.

¡El juego ya está listo para ejecutar!
