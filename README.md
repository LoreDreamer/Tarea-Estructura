# SISTEMA DE GESTIÓN HOSPITALARIA

### DESCRIPCIÓN

Este sistema permite administrar la base de datos de un hospital. Hay varias acciones las cual el usuario puede realizar como registrar a un paciente, asignar su prioridad, mostrar a todos los pacientes, etc. Esta herramienta tiene como propósito mejorar la administración de pacientes en los hospitales y clínicas del país, para que el paciente tenga una atención más eficiente.

### COMO USAR

La base del código se encuentra actualmente en GitHub, pero para poder usarlo de manera correcta los invito a usar el link en los detalles o el "About" del GitHub.

Tras entrar al Replit, para usar usted debe hacer uso de la función "Fork and Run" a la derecha de la pantalla.

Usted tendrá acceso al código sin ningún problema.

Para poder ejecutar el programa, debe poner en el Shell el siguiente comando:

````
./main
````

Trate de no tocar nada del código en main.c, ya que este puede hacer que el programa deje de funcionar como es debido.

## FUNCIONALIDADES

### FUNCIONA CORRECTAMENTE:

- Registración de paciente con su nombre, edad y síntoma, siendo inicial asignado a prioridad baja.
- Asignación de prioridad para los pacientes, si es que es necesario cambiarlos de prioridad para ser atendidos antes.
- Mostrar la lista de los pacientes a ser atendidos, dividos en sus diferentes prioridades en orden de registración.
- Atender al paciente.

En la carpeta `tdas` se encuentran implementados distintos TDAs que puedes utilizar (lista, pila, cola, cola con prioridad y mapas). 

Las implementaciones no son las más eficientes (todas usan como estructura de datos una **lista enlazada**), por lo que puedes reemplazarlas por las que has realizado en los labs.

## Otros códigos (en carpeta examples)
Para ejecutar los distintos ejemplos que hay en la carpeta `examples`, primero debes compilarlos. Si estamos en la carpeta raíz:
````
gcc tdas/*.c examples/example2_menu.c -Wno-unused-result -o example
````
Y luego ejecutarlos:
````
./example
````

Se incluyen los siguientes ejemplos:
* `example1_list`: Uso del TDA Lista, inserción y eliminación de elementos.
* `example2_menu`: Ejemplo de menú con submenús.
* `example3_readcsv`: Ejemplo de lectura desde un archivo csv y almacenamiento en datos estructurados.
* `example4_map`: Ejemplo de uso del TDA mapa.