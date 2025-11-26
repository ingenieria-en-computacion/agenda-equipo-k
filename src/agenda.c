#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Esta función se encarga de iniciar el número de contactos a cero
 */
void iniciar_agenda(Agenda *agenda){ // Ivan
    agenda->num_contactos=0; /*Se le asigna 0 a la agenda para poder manipularla con un valor de inicio,
    en caso de que haya más contactos tienen que ser cargados con la función de cargar contactos */

}




/**
 * Esta función sirve para agregar un contacto nuevo en la agenda
 */
void agregar_contacto(Agenda *agenda, Contacto c){ // Diane
    if (agenda->num_contactos < MAX_CONTACTOS){ // Se comparo el numero de contactos para que sea menor que el maximo numero de contactos
        agenda->contactos[agenda->num_contactos] = c; // Se le asigna los valores guardados previamente en c al ultimo contacto
        agenda->num_contactos++; // Se le agrega 1 al numero de contactos guardados
    }else{
        printf("ERROR! La agenda esta llena, no se pueden agregar más contactos"); //En caso de que la agenda este llena
    }

}


/**
 * Esta función sirve para buscar un contacto por nombre en la agenda y retorna la posición del contacto si exisite
 * En caso contrario retorna -1
 */
int buscar_contacto(Agenda *agenda, char *nombre){ //Ivan
    for (int i = 0; i < agenda->num_contactos; i++){ // Se compara que el numero de contactos sea mayor a 0
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0){ // Se comparan el número de caracteres del nombre a buscar con los de la agenda, pasando uno por uno
            return i;//En caso de entcontrarlo, se devuelve el # de contacto como int 
        }
    }
    return -1; //Si no se encontro se devuelve -1 como int
}


/**
 * Esta función  sirve para buscar un contacto por su número de telefono en la agenda
 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){ //Maestra, porque char telefono y no int y ya T_T
    
    for(int i = 0; i < agenda->num_contactos; i++){
        if(strcmp(agenda->contactos[i].numero, telefono) == 0){
            return i;
        }
    }
    return -1;

}


/*
  Esta función sirve para ordenar los contactos por nombres de forma ascendente
*/
void ordenar_contactos(Agenda *agenda){
    int i, j;
    Contacto temp;
    for(i = 0; i < agenda->num_contactos; i++){
        for(j = 0; j < agenda->num_contactos-i-1; j++){
            if(strcmp(agenda->contactos[j].nombre, agenda->contactos[j+1].nombre)>0){
                temp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j+1];
                agenda->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma descendente
 */

void ordenar_contactos_inv(Agenda *agenda) { //Diane
    int i, j;
    Contacto temp;

    for (i = 0; i < agenda->num_contactos; i++) {
        for (j = 0; j < agenda->num_contactos - i - 1; j++) {
            if (strcmp(agenda->contactos[j].nombre, agenda->contactos[j + 1].nombre) < 0){ //Se cambio el mayor que, a menor que para que cambiara el orden a descendente
                temp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j + 1];
                agenda->contactos[j + 1] = temp;
            }
        }
    }
}



/**
 * Función auxiliar para imprimir un contacto
 */
void mostrar_contacto(Contacto c){ //Diane
    printf("Nombre: %s\n", c.nombre);
    printf("Apellido: %s\n", c.apellido);
    printf("Mes de nacimiento: %s\n", c.mes);
    printf("Dia de nacimiento: %d\n", c.nacimiento);
    printf("Tipo de contacto: %s\n", c.tipo_contacto);
    printf("Numero telefonico: %s\n", c.numero);
    printf("Tipo de numero: %s\n", c.tipo_numero);
    printf("----------------------------------\n"); // parte de decoración -Ivan
    // Se se imprime todo de acuerdo a la dirección en RAM de cada dato necesario
}


/**
 * Función auxiliar para leer un contacto
 */
void leer_contacto(Contacto *c){ //Diane
    printf("Nombre: ");
    scanf("%s", c->nombre); 
    
    printf("Apellido: ");
    scanf("%s", c->apellido);
    
    printf("Mes de nacimiento (ej. ENERO): ");
    scanf("%s", c->mes);

    printf("Dia de nacimiento: ");
    scanf("%d", &c->nacimiento); 

    printf("Tipo de contacto (ej. FAMILIA): ");
    scanf("%s", c->tipo_contacto);

    printf("Numero de telefono: ");
    scanf("%s", c->numero); 

    printf("Tipo de numero (CASA, MOVIL, OFICINA u OTRO): ");
    scanf("%s", c->tipo_numero);
// Se le asigna a una dirección de variable cada elemento dependiendo de que es lo que se pregunta
}

/**
 * Función que imprime todos los contactos de la agenda en pantalla
 */
void imprimir_agenda(Agenda agenda){ //Ivan
    if (agenda.num_contactos == 0){ //Se comprueba que el numero de contactos sea 0
        printf("La agenda esta vacia");//Si es el caso se afirma que la agenda esta vacia
        return;
    }

    printf("Agenda completa:\n");
    printf("=============================\n");// Partes para que se vean más bonitas

    for (int i = 0; i < agenda.num_contactos; i++){// Se comprueba que i sea menos que el numero de contactos para hacer el ciclo hasta que se llegue al número de contactos
        printf("Contacto #%d:\n", i + 1); // Aclarar en que posición esta el contacto
        mostrar_contacto(agenda.contactos[i]); //Se ocupa la función mostar_contacto para que con la dirección del contacto se imprima
    }

}

/**
 * Función que sirve para cargar contactos escritos en un archivo a la agenda
 */
void cargar_contactos(char *filename, Agenda *agenda){ // Ivan, Diane, Yamil
    FILE *archivo;

    archivo = fopen(filename, "r"); // Función para abrir un archivo y leerlo -Yamil
    
    if (archivo == NULL) { //Se comprueba que el archivo exista o este vacio -Yamil
        printf("Archivo '%s' no encontrado", filename);
        iniciar_agenda(agenda); //Se pone la agenda como 0 en su número de contactos -Ivan
        return;
    }

    iniciar_agenda(agenda); //En caso de que haya algo en la agenda se reinicia para que no haya problemas -Diane

    while (agenda->num_contactos < MAX_CONTACTOS && 
           fscanf(archivo, "%s %s %s %d %s %s %s", 
                  agenda->contactos[agenda->num_contactos].nombre,
                  agenda->contactos[agenda->num_contactos].apellido, 
                  agenda->contactos[agenda->num_contactos].mes,
                  &agenda->contactos[agenda->num_contactos].nacimiento, 
                  agenda->contactos[agenda->num_contactos].tipo_contacto,
                  &agenda->contactos[agenda->num_contactos].numero,
                  agenda->contactos[agenda->num_contactos].tipo_numero 
                 ) == 7) { /*Se lee cada linea y por el orden en el que se guardan los contactos se le van asignando a cada numero de contaco
                    un valor, ya que son siete los datos de un contacto se compara para asegurarse de que los 7 datos se leyeron para pasar al siguiente contacto -Ivan*/
        agenda->num_contactos++; //Se actualiza el numero de contacto para guardar el siguiente -Ivan
    }
    
    fclose(archivo); //Siempre cerrar el archivo -Ivan
    printf("Se completo la carga en  %s. Total de contactos cargados: %d\n", filename, agenda->num_contactos); //Texto de confirmación -Yamil

}


/**
 * Función que sirve para guardar todos los contactos de la agenda en un archivo
 */
void guardar_contactos(char *filename, Agenda *agenda){ //Diane
    FILE *archivo;
    archivo = fopen(filename, "w"); //Abrir un archivo para escribir
    if (archivo == NULL){ // En caso de que el archivo no exista abra error
        printf("Error al abrir el archivo '%s' para guardar.\n", filename);
        return;
    }

    for(int i = 0; i < agenda->num_contactos; i++){ //Se hace un ciclo que se repita hasta llegar al ultimo numero de contacto
        fprintf(archivo, "%s %s %s %d %s %s %s\n",
        agenda->contactos[i].nombre,
        agenda->contactos[i].apellido,
        agenda->contactos[i].mes,
        agenda->contactos[i].nacimiento,
        agenda->contactos[i].tipo_contacto,
        agenda->contactos[i].numero,
        agenda->contactos[i].tipo_numero);
    }// Se imprime en el archivo el numero de datos desde 0 hasta el número de contactos actual

    fclose(archivo); //Siempre se tiene que cerrar el archivo
    printf("Agenda guardada correctamente en '%s'. Total de contactos: %d\n", filename, agenda->num_contactos);//texto de confirmación -Yamil

}