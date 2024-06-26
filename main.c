#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <time.h> 
#include <stdbool.h>

typedef struct { // Estructura para almacenar los datos de la persona
  char nombre[50];
  char edad[4];
  char sintoma[50];
  char prioridad[6];
  size_t horaIngreso;
  size_t minutoIngreso;
} typePaciente;

typedef struct { // Nodo de la lista
  List *alta;
  List *media;
  List *baja;
} typeListaPacientes;

void limpiarPantalla() { system("clear"); } // Limpia la pantalla

void presioneTeclaParaContinuar() { // Función para pausar el programa
  puts("Presione una tecla para continuar...");
  getchar(); 
  getchar(); 
}

void mostrarMenuPrincipal() { // Función para mostrar el menú principal
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================\n");
  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir\n");
}

bool detectorPalabra(char *cadena) { // Función para detectar si una cadena es un número

  for (size_t i = 0; i < strlen(cadena); i++) {

    if (isalpha(cadena[i])) // Si se encuentra una letra en la cadena
      return true;
  }
  return false; // Si no se encuentra ninguna letra en la cadena
}

bool detectorNumero(char *cadena) { // Función para detectar si una cadena es un número

  for (size_t i = 0; i < strlen(cadena); i++) {

    if (isdigit(cadena[i])) // Si se encuentra un dígito en la cadena
      return true;
  }
  return false; // Si no se encuentra ningún dígito en la cadena
}

void registrarPaciente(List *listaEntrada, time_t *horaActual) { // Función para registrar un paciente
  
    printf("\nREGISTRACIÓN DE PACIENTE\n\n");
    time(horaActual); // Obtiene la hora actual

    typePaciente *pacienteTemp = (typePaciente *) malloc(sizeof(typePaciente)); // Crea un nuevo paciente
    struct tm *timeA = localtime(horaActual); // Obtiene la hora actual
    int horaTemp = timeA->tm_hour - 4; // Resta 4 horas para obtener la hora local
  
    if (horaTemp < 0)
        horaTemp += 24; // Si la hora local es menor que 0, se le suma 24 horas

    pacienteTemp->horaIngreso = horaTemp; // Asigna la hora local al campo horaIngreso del paciente
    pacienteTemp->minutoIngreso = timeA->tm_min; // Asigna los minutos actuales al campo minutoIngreso del paciente

    printf("Ingrese nombre del paciente: ");
    scanf(" %49[^\n]", pacienteTemp->nombre);  // Lee el nombre del paciente

    if (detectorNumero(pacienteTemp->nombre)) { // Si el nombre contiene números
        printf("\nEl nombre no puede contener números.\n");
        return;
    }

    printf("\nIngrese edad del paciente: ");
    scanf(" %3[^\n]", pacienteTemp->edad); // Lee la edad del paciente

    if (detectorPalabra(pacienteTemp->edad)) { 
        printf("\nLa edad no puede contener letras.\n"); // Si la edad contiene letras
        return;
    }

    printf("\nIngrese sintoma del paciente: ");
    scanf(" %49[^\n]", pacienteTemp->sintoma); // Lee el sintoma del paciente

    strcpy(pacienteTemp->prioridad, "BAJA"); // Asigna la prioridad "BAJA" al paciente
    list_pushBack(listaEntrada, pacienteTemp); // Agrega el paciente a la lista de entrada
    printf("\nPaciente registrado con éxito.\n"); // Mensaje de éxito
}

void swapPatients(typePaciente *a, typePaciente *b) { // Función para intercambiar dos pacientes

  typePaciente temp = *a; // Crea una variable temporal para almacenar el paciente a
  *a = *b; // Asigna el paciente b al paciente a
  *b = temp; // Asigna el paciente temporal al paciente b
  
}

void organizarLista(List *listTemp) { // Función para organizar la lista de pacientes

  typePaciente *aux = list_first(listTemp); // Obtener el primer paciente de la lista

  if (aux == NULL) // Si la lista está vacía, no hay nada que organizar

    return;
  else { // Si la lista no está vacía, ordenarla

    typePaciente *aux2 = list_next(listTemp); // Obtener el segundo paciente de la lista

    for (aux = list_first(listTemp); aux != NULL; aux = list_next(listTemp)) { // Recorrer la lista
      for (aux2 = list_next(listTemp); aux2 != NULL; aux2 = list_next(listTemp)) { // Recorrer la lista desde el segundo paciente

        if ((aux->horaIngreso > aux2->horaIngreso) || (aux->horaIngreso == aux2->horaIngreso && aux->minutoIngreso > aux2->minutoIngreso)) // Comparar las horas y minutos de ingreso de los pacientes

          swapPatients(aux, aux2); // Intercambiar los pacientes si es necesario.
      }
    }
  }
}

void reorganizarListas(typeListaPacientes *listaPacientes) { // Función para reorganizar las listas de pacientes

  organizarLista(listaPacientes->alta); // Reorganizar la lista de alta prioridad
  organizarLista(listaPacientes->media); // Reorganizar la lista de media prioridad
  organizarLista(listaPacientes->baja); // Reorganizar la lista de baja prioridad

}


void asignarPrioridad(typeListaPacientes *listaPacientes) { // Función para asignar prioridad a los pacientes

  printf("\nREASIGNACIÓN DE PRIORIDAD\n\n");

  char nombreTemporal[50]; // Variable temporal para almacenar el nombre del paciente
  char antiguaPrioridad[6]; // Variable temporal para almacenar la antigua prioridad del paciente
  size_t option; // Variable para almacenar la opción seleccionada por el usuario

  printf("Ingrese nombre del paciente: ");
  scanf(" %49[^\n]s", nombreTemporal);  // Leer el nombre del paciente
  
  printf("\nIngrese antigua prioridad del paciente (ALTA, MEDIA, BAJA): ");
  scanf(" %5[^\n]s", antiguaPrioridad); // Leer la antigua prioridad del paciente

  List *listaBuscada = NULL; // Puntero a la lista buscada

  if (strcmp(antiguaPrioridad, "ALTA") == 0) { // Comparar la antigua prioridad con "ALTA"

    listaBuscada = listaPacientes->alta; // Asignar la lista "alta" a la variable listaBuscada
  } else if (strcmp(antiguaPrioridad, "MEDIA") == 0) { // Comparar la antigua prioridad con "MEDIA"

    listaBuscada = listaPacientes->media; // Asignar la lista "media" a la variable listaBuscada

  } else if (strcmp(antiguaPrioridad, "BAJA") == 0) { // Comparar la antigua prioridad con "BAJA"

    listaBuscada = listaPacientes->baja; // Asignar la lista "baja" a la variable listaBuscada

  } else { // Si la antigua prioridad no coincide con ninguna de las tres opciones

    printf("Error: Prioridad inválida\n");
    return;

  }

  typePaciente *aux = list_first(listaBuscada); // Puntero auxiliar para recorrer la lista buscada

  if (aux == NULL) { // Si la lista buscada está vacía

    printf("\n\nLa lista original del paciente se encuentra vacía.\n");
    return;
  } while (aux != NULL) { // Recorrer la lista buscada

    if (strcmp(aux->nombre, nombreTemporal) == 0) { // Comparar el nombre del paciente con el nombre ingresado

      printf("\nIngrese nueva prioridad (1/2/3): ");
      scanf(" %zu", &option); // Leer la nueva prioridad del paciente

      switch(option) { // Evaluar la nueva prioridad del paciente

        case 1:
          strcpy(aux->prioridad, "ALTA"); // Asignar la nueva prioridad como "ALTA"
          list_pushBack(listaPacientes->alta, aux); // Agregar el paciente a la lista "alta"
          break;

        case 2:
          strcpy(aux->prioridad, "MEDIA"); // Asignar la nueva prioridad como "MEDIA"
          list_pushBack(listaPacientes->media, aux); // Agregar el paciente a la lista "media"
          break;

        case 3:
          strcpy(aux->prioridad, "BAJA"); // Asignar la nueva prioridad como "BAJA"
          list_pushBack(listaPacientes->baja, aux); // Agregar el paciente a la lista "baja"
          break;
        
        default:
          printf("\n\nOpción inválida.\n"); // Mostrar mensaje de error si la opción ingresada no es válida
          return;

      }

      list_popCurrent(listaBuscada); // Eliminar el paciente de la lista original
      printf("\nPrioridad reasignada con éxito\n"); // Mostrar mensaje de éxito
      return; // Salir de la función
    }

    aux = list_next(listaBuscada); // Avanzar al siguiente paciente

    if (aux == NULL) { // Si no se encuentra el paciente en la lista

      printf("\n\nEl paciente no se encuentra en la lista.\n"); 
      return;
    }
  }
}

void mostrarPaciente(typePaciente aux) {

  printf("Nombre: %s\n", aux.nombre);
  printf("Edad: %s\n", aux.edad);
  printf("Sintoma: %s\n", aux.sintoma);

  if (aux.minutoIngreso >= 10) // Mostrar la hora y minuto de ingreso del paciente
    printf("Hora Ingreso: %zu:%zu\n\n", aux.horaIngreso, aux.minutoIngreso);
  else // Mostrar la hora y minuto de ingreso del paciente si los minutos son menores a 10
    printf("Hora Ingreso: %zu:0%zu\n\n", aux.horaIngreso, aux.minutoIngreso);
  
}

void mostrarPacientes(List *listaTemp) { // Función para mostrar los pacientes de una lista

  typePaciente *temporal = list_first(listaTemp); // Puntero temporal para recorrer la lista

  if (temporal == NULL) { // Si la lista está vacía

    printf("No hay pacientes en espera.\n");
    return;
  } while (temporal != NULL) { // Recorrer la lista

    mostrarPaciente(*temporal);
    temporal = list_next(listaTemp); // Avanzar al siguiente paciente
  }
}

void mostrarListaPacientes(typeListaPacientes listaPacientes) { // Función para mostrar las listas de pacientes

  printf("\nPacientes en espera: \n\n");
  reorganizarListas(&listaPacientes); // Reorganizar las listas

  printf("PRIORIDAD ALTA (1): \n\n");
  mostrarPacientes(listaPacientes.alta); // Mostrar la lista de alta prioridad

  printf("\nPRIORIDAD MEDIA (2): \n\n");
  mostrarPacientes(listaPacientes.media); // Mostrar la lista de media prioridad

  printf("\nPRIORIDAD BAJA (3): \n\n");
  mostrarPacientes(listaPacientes.baja); // Mostrar la lista de baja prioridad

}

bool detectorListaYAtencionPaciente(List *listTemp) { // Función para detectar si hay pacientes en espera y atenderlos

  typePaciente *aux = list_first(listTemp); // Puntero auxiliar para recorrer la lista

  if (listTemp == NULL || aux == NULL) { // Si la lista está vacía o el primer paciente está vacío

    return true;
  
  } while (aux != NULL) { // Recorrer la lista

      mostrarPaciente(*aux);      
      printf("El paciente ha sido atendido.\n"); // Mostrar mensaje de éxito

      aux = list_next(listTemp); // Avanzar al siguiente paciente
      list_popFront(listTemp); // Eliminar el paciente de la lista
      break;
    }
  return false;   
}

void atenderPaciente(typeListaPacientes *listaPacientes) { // Función para atender a un paciente

  printf("\n ATENDIENDO AL PACIENTE\n\n");

  List *alta = listaPacientes->alta; // Puntero a la lista de alta prioridad
  List *media = listaPacientes->media; // Puntero a la lista de media prioridad
  List *baja = listaPacientes->baja; // Puntero a la lista de baja prioridad

  bool altaVacia = detectorListaYAtencionPaciente(alta); // Verificar si la lista está vacía, y si no imprime el paciente a atender.

  if (altaVacia) { 
    
    bool mediaVacia = detectorListaYAtencionPaciente(media); // Verificar si la lista está vacía, y si no imprime el paciente a atender.

    if (mediaVacia) {
      
      bool bajaVacia = detectorListaYAtencionPaciente(baja); // Verificar si la lista está vacía, y si no imprime el paciente a atender.
      
      if (bajaVacia) { 
        
        printf("\n\nNo hay pacientes en espera.\n");
        return;
      }
    }
  }
}

void mostrarPrioridad(typeListaPacientes listaPacientes) { // Función para mostrar las listas de pacientes por prioridad

  size_t option; // Variable para almacenar la opción seleccionada por el usuario

  reorganizarListas(&listaPacientes); // Reorganizar las listas
  printf("\nLISTA POR PRIORIDAD\n\n");
  printf("Elija prioridad a mostrar (1/2/3): "); // Pedir al usuario que elija una prioridad
  scanf(" %zu", &option); // Leer la opción seleccionada por el usuario

  switch(option) { // Evaluar la opción seleccionada por el usuario

    case 1: // Mostrar la lista de alta prioridad
      printf("\nPRIORIDAD ALTA (1): \n\n");
      mostrarPacientes(listaPacientes.alta);
      break;

    case 2: // Mostrar la lista de media prioridad
      printf("\nPRIORIDAD MEDIA (2): \n\n");
      mostrarPacientes(listaPacientes.media);
      break;

    case 3: // Mostrar la lista de baja prioridad
      printf("\nPRIORIDAD BAJA (3): \n\n");
      mostrarPacientes(listaPacientes.baja);
      break;

    default: // Mostrar mensaje de error si la opción ingresada no es válida
      printf("\n\nOpción inválida.\n");
      return; 
  }
}

int main() {

  time_t horaActual; // Variable para almacenar la hora actual
  char opcion; // Variable para almacenar la opción seleccionada por el usuario
  typeListaPacientes listaPacientes; // Variable para almacenar las listas de pacientes

  listaPacientes.alta = list_create(); // Crear lista de pacientes en alta prioridad
  listaPacientes.media = list_create(); // Crear lista de pacientes en media prioridad
  listaPacientes.baja = list_create(); // Crear lista de pacientes en baja prioridad

  do {

    mostrarMenuPrincipal(); // Mostrar el menú principal
    printf("Ingrese su opción: "); // Solicitar al usuario que ingrese una opción
    scanf(" %c", &opcion); // Leer la opción ingresada por el usuario

    switch (opcion) {

    case '1':
      registrarPaciente(listaPacientes.baja, &horaActual); // Registrar un paciente en baja prioridad
      break;

    case '2':
      asignarPrioridad(&listaPacientes); // Asignar prioridad a un paciente
      break;

    case '3':
      mostrarListaPacientes(listaPacientes); // Mostrar la lista de pacientes en espera
      break;

    case '4':
      atenderPaciente(&listaPacientes); // Atender al siguiente paciente en espera
      break;

    case '5':
      mostrarPrioridad(listaPacientes); // Mostrar la lista de pacientes por prioridad
      break;

    case '6':
      puts("Saliendo del sistema de gestión hospitalaria..."); // Salir del sistema
      break;

    default:
      puts("Opción no válida. Por favor, intente de nuevo."); // Mostrar un mensaje de error si la opción ingresada no es válida

    }
    presioneTeclaParaContinuar(); // Esperar a que el usuario presione una tecla para continuar
  } while (opcion != '6');

  list_clean(listaPacientes.alta); // Liberar la memoria de las listas de pacientes
  list_clean(listaPacientes.media); // Liberar la memoria de las listas de pacientes
  list_clean(listaPacientes.baja); // Liberar la memoria de las listas de pacientes

  return 0;
}