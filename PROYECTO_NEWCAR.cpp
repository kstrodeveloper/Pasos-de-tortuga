#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

using namespace std;

// Estructura para almacenar informaci�n de productos comprados
struct PRODUCTO{
    char NOMBRE[30];
    float VALOR;
    int DIAS;
    int MES;
    int ANO;
};

// Estructura para almacenar informaci�n b�sica de clientes
struct CLIENTE{
    int CODIGO;
    char NOMBRE[30];
    int DIAS;
    int MES;
    int ANO;
};

/**
 * Funcion para convertir la primera letra de cada palabra a may�scula
 * y el resto a minuscula (formato titulo)
 * @param NOMBRE: cadena de caracteres a capitalizar
 */
void CAPITALIZAR(char NOMBRE[]){
    int INICIO=1; // Flag para indicar si estamos al inicio de una palabra
    for(int i=0;NOMBRE[i]!='\0';i++){
        if(NOMBRE[i]==' '){
            INICIO=1; // Despues de un espacio, la siguiente letra debe ser mayuscula
        } else {
            if(INICIO&&isalpha(NOMBRE[i])) {
                NOMBRE[i]=toupper(NOMBRE[i]); // Primera letra de palabra en mayuscula
                INICIO=0; // Ya no estamos al inicio de la palabra
            } else {
                NOMBRE[i]=tolower(NOMBRE[i]); // Resto de letras en minuscula
            }
        }
    }
}

/**
 * Funcion que genera automaticamente el siguiente codigo disponible
 * Lee el archivo CLIENTES.txt y encuentra el codigo mas alto usado
 * @return: siguiente codigo disponible (maximo + 1)
 */
int GENERARCODIGO(){
    ifstream ARCHIVO("CLIENTES.txt");
    if(!ARCHIVO){
        return 1; // Si no existe el archivo, empezar con codigo 1
    }							
    char LINEA[100];
    int MAXIMO=0;
    
    // Lee linea por linea el archivo de clientes
    while(ARCHIVO.getline(LINEA,100)){
        // Parsea cada linea usando "|" como separador
        /**strtok() es una funcion de C que divide una cadena en tokens (partes) usando un delimitador especifico.*/
        char*NOMBRELEIDO=strtok(LINEA,"|");
        char*codigost=strtok(NULL,"|");     // Extrae el codigo
        char*DIAS=strtok(NULL,"|");
        char*MES=strtok(NULL,"|");
        char*ANO=strtok(NULL,"|");
        
        int CODIGOLEIDO=atoi(codigost); // Convierte string a entero
        if(CODIGOLEIDO>MAXIMO){
            MAXIMO=CODIGOLEIDO; // Actualiza el maximo encontrado
        }
    }
    ARCHIVO.close();
    return MAXIMO+1; // Retorna el siguiente codigo disponible
} 

/**
 * Funcion principal para agregar un nuevo cliente al sistema
 * Crea registro en CLIENTES.txt y archivo individual para compras
 * @param CLIENTES: nombre del archivo de clientes
 * @param CLT: array de estructura CLIENTE
 * @param N: referencia al contador de clientes
 */
void AGREGAR(const char*CLIENTES,struct CLIENTE CLT[],int &N){
    ofstream ARCHIVO;
    ARCHIVO.open("CLIENTES.txt",ios::app); // Abre en modo append (agregar al final)
    
    if(!ARCHIVO){
        printf("\nARCHIVO NO ENCONTRADO...\n");
    }
    else {
        // Captura datos del nuevo cliente
        printf("\nNOMBRE: ");cin.getline(CLT[N].NOMBRE,40);cin.ignore();
        CAPITALIZAR(CLT[N].NOMBRE); // Formatea el nombre
        CLT[N].CODIGO=GENERARCODIGO(); // Asigna codigo automatico
        
        // Captura fecha de registro
        printf("\n---FECHA DE REGISTRO--- ");
        printf("\nDIA: ");scanf("%d",&CLT[N].DIAS);cin.ignore();
        printf("\nMES: ");scanf("%d",&CLT[N].MES);cin.ignore();
        printf("\nANO: ");scanf("%d",&CLT[N].ANO);cin.ignore();
        
        // Guarda en formato: NOMBRE|CODIGO|DIA/MES/ANO
        ARCHIVO<<CLT[N].NOMBRE;
        ARCHIVO<<"|";
        ARCHIVO<<CLT[N].CODIGO;
        ARCHIVO<<"|";
        ARCHIVO<<CLT[N].DIAS;
        ARCHIVO<<"/";
        ARCHIVO<<CLT[N].MES;
        ARCHIVO<<"/";
        ARCHIVO<<CLT[N].ANO;
        ARCHIVO<<endl;
        
        // Crea archivo individual para las compras del cliente
        char NOMBREARCHIVO[40];
        /*sprintf() es una funcion que formatea y crea cadenas de texto, similar a printf()
		 pero en lugar de imprimir en pantalla, guarda el resultado en una variable string.*/
		 
        sprintf(NOMBREARCHIVO,"CLIENTE_%03d.txt", CLT[N].CODIGO); // Formato: CLIENTE_001.txt
        ofstream ARCHIVOCOMPRA;
        ARCHIVOCOMPRA.open(NOMBREARCHIVO,ios::app);
        
        if(!ARCHIVOCOMPRA){
            printf("\nARCHIVO NO ENCONTRADO...\n");
        }
        else {
            ARCHIVOCOMPRA.close(); // Solo crea el archivo, no escribe nada a�n
        }
    }
    printf("\nREGISTRO EXITOSO...\n");
    N++; // Incrementa contador de clientes
}

/**
 * Funcion para registrar una compra en el archivo especifico de un cliente
 * @param NOMBREARCHIVO: nombre del archivo del cliente (ej: CLIENTE_001.txt)
 */
void REGISTRAR(char NOMBREARCHIVO[]){
    PRODUCTO NUEVO;
    ofstream ARCHIVOCOMPRA;
    ARCHIVOCOMPRA.open(NOMBREARCHIVO, ios::app); // Abre en modo append
    
    if(!ARCHIVOCOMPRA){
        printf("\nNO SE PUDO ABRIR EL ARCHIVO DE CLIENTES...\n");
    }
    else {
        // Captura informacin del producto
        cin.ignore();
        printf("\nNOMBRE DEL PRODUCTO: ");cin.getline(NUEVO.NOMBRE,40);cin.ignore();
        CAPITALIZAR(NUEVO.NOMBRE);
        printf("\nVALOR DEL PRODUCTO: ");scanf("%f",&NUEVO.VALOR);cin.ignore();
        
        // Captura fecha de compra
        printf("\n---FECHA DE COMPRA DEL PRODUCTO---");
        printf("\nDIA: ");scanf("%d",&NUEVO.DIAS);cin.ignore();
        printf("\nMES: ");scanf("%d",&NUEVO.MES);cin.ignore();
        printf("\nANO: ");scanf("%d",&NUEVO.ANO);cin.ignore();
        
        // Guarda en formato: PRODUCTO|$VALOR|DIA/MES/ANO
        ARCHIVOCOMPRA<<NUEVO.NOMBRE;
        ARCHIVOCOMPRA<<"|$";
        ARCHIVOCOMPRA<<NUEVO.VALOR;
        ARCHIVOCOMPRA<<"|";
        ARCHIVOCOMPRA<<NUEVO.DIAS<<"/"<<NUEVO.MES<<"/"<<NUEVO.ANO;
        ARCHIVOCOMPRA<<endl;
        ARCHIVOCOMPRA.close();	
    }	
    printf("\nPRODUCTO REGISTRADO EXITOSAMENTE\n");
}

/**
 * Funcion para mostrar informacion completa de un cliente y su historial de compras
 * @param CODIGO: codigo unico del cliente a mostrar
 */
void MOSTRARCLIENTE(int CODIGO){
    // Primero busca y muestra informacion basica del cliente
    ifstream ARCHIVO("CLIENTES.txt");
    if(!ARCHIVO){
        printf("\nERROR AL LEER ARCHIVO DE CLIENTES...");
    }
    else{
        bool ENCONTRADO=false;
        char LINEA[100];
        
        // Busca el cliente por codigo
        /**strtok() es una funcion de C que divide una cadena en tokens (partes) usando un delimitador especifico.*/
        while(ARCHIVO.getline(LINEA,100)){
            char*NOMBRE=strtok(LINEA,"|");
            char*codigost=strtok(NULL,"|");
            char*DIAS=strtok(NULL,"|");
            char*MES=strtok(NULL,"|");
            char*ANO=strtok(NULL,"|");
            int CODIGOLEIDO =atoi(codigost);
            
            if(CODIGOLEIDO == CODIGO){
                // Muestra informacion basica del cliente
                printf("\nCLIENTE ENCONTRADO...");
                printf("\nNOMBRE: %s ",NOMBRE);
                printf("\nCODIGO: %s ",codigost);
                printf("\nFECHA DE REGISTRO: %s/%s/%s\n",DIAS,MES,ANO);
                system("pause");
                ENCONTRADO=true;
                system("cls");	
            }
        }
        ARCHIVO.close();
        
        if(!ENCONTRADO){
            printf("\nCODIGO NO ENCONTRADO...");
        }
    }
    
    // Luego muestra el historial de compras del cliente
    char NOMBREARCHIVO[40];
    sprintf(NOMBREARCHIVO,"CLIENTE_%03d.txt",CODIGO);
    ifstream ARCHIVOCOMPRA;
    ARCHIVOCOMPRA.open(NOMBREARCHIVO);
    
    if(!ARCHIVOCOMPRA){
        printf("\nERROR AL LEER EL ARCHIVO DE CLIENTES...");
    }
    else {
        printf("\nHISTORIAL DE COMPRAS...");
        char LINEA[100];
        
        // Lee y muestra cada compra
        /**strtok() es una funcion de C que divide una cadena en tokens (partes) usando un delimitador especifico.*/
        
        while(ARCHIVOCOMPRA.getline(LINEA,100)){
            char*NOMBRELEIDO=strtok(LINEA,"|");
            char*VALOR=strtok(NULL,"|");
            char*FECHA=strtok(NULL,"|");
            char*DIAS=strtok(FECHA,"/");
            char*MES=strtok(NULL,"/");
            char*ANO=strtok(NULL,"/");
            
            printf("\nPRODUCTO: %s",NOMBRELEIDO);
            printf("\nVALOR DEL PRODUCTO: $%s",VALOR);
            printf("\nFECHA DE COMPRA DEL PRODUCTO: %s/%s/%s",DIAS,MES,ANO);	
        }
        ARCHIVOCOMPRA.close();
    }
}

/**
 * Funcion para buscar un cliente por nombre
 * Usa strcasecmp para comparacion sin considerar mayusculas/minusculas
 * @param NOMBRE: nombre del cliente a buscar
 */
void BUSCARCLIENTE(const char *NOMBRE){
    ifstream ARCHIVO("CLIENTES.txt");
    if(!ARCHIVO){
        printf("\nERROR AL LEER ARCHIVOS DE CLIENTES");
    }   
    else {
        bool ENCONTRADO=false;
        char LINEA[100];
        
        while(ARCHIVO.getline(LINEA,100)){
            char*NOMBRELEIDO=strtok(LINEA,"|");
            char*codigost=strtok(NULL,"|");
            char*DIAS=strtok(NULL,"|");
            char*MES=strtok(NULL,"|");
            char*ANO=strtok(NULL,"|");
            
            // Comparacion insensible a mayusculas/minusculas
            if(strcasecmp(NOMBRELEIDO,NOMBRE)==0){
                printf("\nCLIENTE ENCONTRADO...");
                printf("\nNOMBRE: %s ",NOMBRELEIDO);
                printf("\nCODIGO: %s ",codigost);
                printf("\nFECHA DE REGISTRO: %s/%s/%s\n",DIAS,MES,ANO);
                ENCONTRADO=true;
                system("pause");
                system("cls");
                
                // Muestra informaci�n completa del cliente encontrado
                MOSTRARCLIENTE(atoi(codigost));
                break;
            }
        }
        ARCHIVO.close();
        
        if(!ENCONTRADO){
            printf("\nCLIENTE NO ENCONTRADO...");
            system("pause");
            system("cls");
        }
    } 
}    

/**
 * Funcion para eliminar un cliente del sistema
 * Crea archivo temporal, copia todos excepto el cliente a eliminar
 * @param CODIGO: c�digo del cliente a eliminar
 */
void ELIMINARCLIENTES(int CODIGO){
    ifstream ARCHIVO("CLIENTES.txt");
    ofstream ARCHIVOTEMP("TEMP.txt");
    
    if(!ARCHIVO||!ARCHIVOTEMP){
        printf("\nERROR AL ABRIR ARCHIVOS...");
    }
    
    // Confirmacion del usuario
    char OPCION;
    printf("\nESTA SEGURO DE ELIMINAR AL CLIENTE CON CODIGO %d SI/NO ?: ",CODIGO);
    scanf(" %c",&OPCION);
    
    if(toupper(OPCION)!='S'){
        printf("\nELIMINACION CANCELADA POR EL USUARIO...");
        ARCHIVO.close();
        ARCHIVOTEMP.close();
        return;
    }
    
    // Copia todos los clientes excepto el que se va a eliminar
    char LINEA[100];
    while(ARCHIVO.getline(LINEA,100)){
        char*NOMBRELEIDO=strtok(LINEA,"|");
        char*codigost=strtok(NULL,"|");
        char*DIAS=strtok(NULL,"|");
        char*MES=strtok(NULL,"|");
        char*ANO=strtok(NULL,"|");
        
        int CODIGOLEIDO=atoi(codigost);
        if(CODIGOLEIDO!=CODIGO){
            // Solo copia si NO es el cliente a eliminar
            ARCHIVOTEMP<<NOMBRELEIDO<<"|"<<codigost<<"|"<<DIAS<<"|"<<MES<<"|"<<ANO<<endl;
        }
    }
    
    ARCHIVO.close();
    ARCHIVOTEMP.close();
    
    // Reemplaza el archivo original con el temporal
    remove("CLIENTES.txt");
    rename("TEMP.txt","CLIENTES.txt");
    
    // Elimina tambien el archivo individual de compras del cliente
    char NOMBREARCHIVO[40];
    sprintf(NOMBREARCHIVO,"CLIENTE_%03d.txt",CODIGO);
    remove(NOMBREARCHIVO);
    
    printf("\nCLIENTE ELIMINADO CON EXITO...");	
}  

/**
 * Funcion que solicita y valida que un codigo de cliente exista
 * Repite la solicitud hasta que se ingrese un codigo valido
 * @return: codigo valido ingresado por el usuario
 */
int PEDIRCODIGO(){
    int CODIGO;
    bool EXISTE=false;
    
    do{
        printf("\nINGRESE CODIGO: ");scanf("%d",&CODIGO);
        ifstream ARCHIVO("CLIENTES.txt");
        
        if(!ARCHIVO){
            printf("\nERROR AL ABRIR EL ARCHIVO DE CLIENTES..");
        }	
        
        // Verifica si el codigo existe
        char LINEA[100];
        while(ARCHIVO.getline(LINEA,100)){
            char*NOMBRELEIDO=strtok(LINEA,"|");
            char*codigost=strtok(NULL,"|");
            char*DIAS=strtok(NULL,"|");
            char*MES=strtok(NULL,"|");
            char*ANO=strtok(NULL,"|");
            int CODIGOLEIDO=atoi(codigost);
            
            if(CODIGOLEIDO==CODIGO){
                EXISTE=true;
                break;
            }
        }
        ARCHIVO.close();
        
        if(!EXISTE){
            printf("\nCODIGO NO ENCONTRADO. INTENTE NUEVAMENTE...");
        }
        
    }while(!EXISTE); // Repite hasta encontrar codigo valido
    
    return CODIGO;
} 

/**
 * Funcion principal que muestra el menu y maneja la navegacion
 * Controla el flujo principal del programa
 */
void MOSTRARMENU(){
    int OPCION;
    
    do{
        system("cls"); // Limpia pantalla
        
        // Muestra menu principal
        printf("|-------------------------------------------------------|\n");
        printf("|                   MENU DE OPCIONES                    |\n");
        printf("|---------------------------|---------------------------|\n");
        printf("|  1.AGREGAR CLIENTE.       |   5.ELIMINAR CLIENTE.    	|\n");
        printf("|  2.REGISTRAR COMPRA.      |   6.GENERAR CODIGO.      	|\n");
        printf("|  3.MOSTRAR CLIENTE.       |   7.PEDIR CODIGO         	|\n");
        printf("|  4.BUSCAR CLIENTE POR     |   8.SALIR DEL PROGRAMA   	|\n");
        printf("|     NOMBRE.               |                          	|\n");
        printf("|-------------------------------------------------------|\n");
        printf("|        SELECCIONE UNA OPCION ENTRE (1) Y (8)          |\n");
        printf("|-------------------------------------------------------|\n");
        printf(">>");
        
        scanf("%d",&OPCION);cin.ignore();
        
        // Validacion de opcion
        if(OPCION<1||OPCION>8){
            printf("\nERROR INTENTA OTRA OPCION...\n");
            system("pause");
        }	
        
        // Switch principal que maneja cada opcion del menu
        switch(OPCION){
            case 1:{ // Agregar nuevo cliente
                int N=0; // Contador local para nuevos clientes
                CLIENTE CLT[1]; // Array para un cliente
                AGREGAR("CLIENTES.txt",CLT,N);
                break;
            }
            case 2: { // Registrar compra para cliente existente
                int CODIGO=PEDIRCODIGO(); // Pide codigo valido
                char NOMBREARCHIVO[40];
                sprintf(NOMBREARCHIVO,"CLIENTE_%03d.txt",CODIGO);
                REGISTRAR(NOMBREARCHIVO);
                break;
            }
            case 3:{ // Mostrar informacion completa de cliente
                int CODIGO=PEDIRCODIGO();
                MOSTRARCLIENTE(CODIGO);
                break;
            }
            case 4:{ // Buscar cliente por nombre
                char NOMBREBUSCAR[40];
                printf("\nINGRESE NOMBRE DEL CLIENTE A BUSCAR: ");
                cin.getline(NOMBREBUSCAR,40);
                CAPITALIZAR(NOMBREBUSCAR); // Formatea busqueda
                BUSCARCLIENTE(NOMBREBUSCAR);
                break;
            }
            case 5:{ // Eliminar cliente
                int CODIGO=PEDIRCODIGO();
                ELIMINARCLIENTES(CODIGO);
                break;
            }
            case 6:{ // Mostrar proximo codigo disponible
                int NUEVOCODIGO=GENERARCODIGO();
                printf("\nEL SIGUIENTE CODIGO DISPONIBLE ES: %03d\n",NUEVOCODIGO);
                break;
            }
            case 7:{ // Validar que un codigo existe
                int CODIGO=PEDIRCODIGO();
                printf("\nCODIGO VALIDADO: %03d\n",CODIGO);
                break;
            }
            case 8:{ // Salir del programa
                printf("\nSALIENDO DEL PROGRAMA...\n");
                break;
            }
            default:{
                printf("OPCION NO VALIDA. INTENTE DE NUEVO...");
                break;
            }
        }
        system("pause"); // Pausa para ver resultados
        
    }while(OPCION!=8); // Repite hasta que el usuario elija salir
}

// Funcion principal - punto de entrada del programa
int main(void){
    int N=0; // Contador inicial de clientes
    MOSTRARMENU(); // Inicia el programa mostrando el menu
    return 0;
}
