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
- Atender al paciente, basado en el orden de prioridad y la hora de llegada.

### PROBLEMAS CONOCIDOS:

- Para buscar a un paciente mientras se asigna la prioridad, uno debe escribir de la misma forma que el nombre fue ingresado.
- El uso de cáracteres especiales puede hacer que la búsqueda de pacientes se haga más díficil, por lo que se recomienda registrar los nombres sin tildes ni otros cáracteres.
- Aquellos pacientes con nombres similares pueden causar problemas al tratar de asignar la prioridad, por lo que es necesario usar nombre y apellido para evitar este tipo de casos.
- Al asignar prioridad, puede ser posible que el sistema lo devuelva a la pantalla original sin razón alguna. Esto es debido a que se introduce una nueva lista inválida para que el paciente sea transferido, lo cual el sistema lo trata como error.

## EJEMPLO DE USO

Para empezar, debemos a registrar a nuestro paciente:

````
REGISTRACIÓN DE PACIENTE

Ingrese nombre del paciente: Eduardo Cordero

Ingrese edad del paciente: 19

Ingrese síntoma del paciente: Fiebre
````

Esto deja a nuestro paciente, Eduardo, ingresado al sistema como paciente de prioridad baja. Si llegase el caso de que al ser revisado, el doctor requiera que el paciente sea movido de prioridad, uno puede hacer uso de la asignación de prioridad:

````
REASIGNACIÓN DE PRIORIDAD

Ingrese nombre del paciente: Eduardo Cordero

Ingrese antigua prioridad del paciente: BAJA

Ingrese nueva prioridad (1/2/3): 2
````

Debido a que la fiebre de Eduardo no paraba, el doctor decidió subirlo a prioridad media. Ahora Eduardo no tendrá que esperar mucho tiempo, pero el hospital tiene varios pacientes antes que nuestro personaje. La lista se puede ver mediante la impresión de la lista de espera:

````
Pacientes en espera:

PRIORIDAD ALTA (1):

No hay pacientes en espera.

PRIORIDAD MEDIA (2):

Nombre: Julia Torres
Edad: 42
Sintoma: Dolor estomacal
Hora de Ingreso: 15:59 

Nombre: Pablo Ibarra
Edad: 7
Síntoma: Falta de energía
Hora de Ingreso: 16:10

Nombre: Eduardo Cordero
Edad: 19
Síntoma: Fiebre
Hora de Ingreso: 16:42 

PRIORIDAD BAJA:

Nombre: Javiera Cortés
Edad: 16
Síntoma: Tos
Hora de Ingreso: 15:47

````

Para poder avanzar con los pacientes, el doctor llama a Julia Torres para que sea atendida:

````
ATENDIENDO AL PACIENTE

Nombre: Julia Torres
Edad: 42
Síntoma: Dolor estomacal
Hora de Ingreso: 15:59

El paciente ha sido atendido.

````

Ya con Julia atendida, si queremos ver la lista de espera de prioridad media, podemos hacer uso de la interfaz para exclusivamente esta lista:

````
LISTA POR PRIORIDAD

Elija la prioridad a mostrar (1/2/3): 2

PRIORIDAD MEDIA (2):

Nombre: Pablo Ibarra
Edad: 7
Síntoma: Falta de energía
Hora de Ingreso: 16:10

Nombre: Eduardo Cordero
Edad: 19
Síntoma: Fiebre
Hora de Ingreso: 16:42 

````

Para salir del sistema, haga uso de la última opción y estará fuera de la aplicación:

````
Saliendo del sistema de gestión hospitalaria...
Presione una tecla para continuar...
````