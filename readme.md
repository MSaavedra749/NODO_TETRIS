# NODO_TETRIS
Implementación del juego Tetris en C utilizando SDL3.



> El juego ya está listo para ejecutar.

## Configuración del juego
Desde el menú principal se puede acceder a un menú gráfico de configuración.

Parámetros configurables:
- `Dificultad`: fácil, normal y difícil.
- `Resolución`: 320x200 o 640x480.
- `Paleta de colores`: tres estilos visuales.
- `Ancho deluxe`: modifica el tamaño del tablero en modo deluxe.

Botones del menú:
- `Salir`: descarta los cambios.
- `Guardar cambios`: aplica la configuración seleccionada.

### Muestras de paletas de colores
| Clásica | GameBoy | Neon |
|--------|---------|------|
| ![Clásica](./img/clasica.png) | ![GameBoy](./img/gameboy.png) | ![Neon](./img/neon.png) |

`Imágenes tomadas en resolución 320x200 y escala x2`

## Opciones de lanzamiento
El juego acepta argumentos de línea de comandos al ejecutarlo desde CMD.

Para usarlo, abre la terminal en la carpeta donde está el ejecutable y añade los argumentos después del nombre del archivo.
```bash
cd \ruta\al\directorio\del\ejecutable
 tetris.exe -v
```

Argumentos disponibles:
- `-v`: inicia el juego en resolución VGA (640x480).
- `-c`: inicia el juego en resolución CGA (320x200).

> Ejemplo: `tetris.exe -v` inicia el juego en 640x480.


## Progreso

### Archivos a actualizar
- [x] cheats.c
- [x] cheats.h
- [x] dibujo.c
- [x] dibujo.h
- [x] graficos.c
- [x] graficos.h
- [x] Input.c
- [x] input.h
- [x] main.c
- [x] mEstados.c
- [x] mEstados.h
- [x] opciones.c
- [x] opciones.h
- [ ] Pausa.c
- [ ] Pausa.h
- [ ] Perder.c
- [ ] Perder.h
- [x] piezas.c
- [x] piezas.h
- [x] pMenu.c
- [x] pMenu.h
- [x] pNombre.c
- [x] pNombre.h
- [x] puntos.c
- [x] puntos.h
- [x] splash.c
- [x] splash.h
- [x] tablero.c
- [x] tablero.h
- [x] tda_vector.c
- [x] tda_vector.h
- [x] tetris.c
- [x] tetris.h
