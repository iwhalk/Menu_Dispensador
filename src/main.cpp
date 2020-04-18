#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);//direccion de la lcd

/* direcciones de utilizadas de la memoria EEPROM */

const int direccion_t[5] = {0, 1, 2, 3, 4};
const int direccion_p[5] = {5, 6, 7, 8, 9};
const int direccion_e    = 10;

/*Botones Utilizados para la configuracion*/

#define boton_1     8 //Posicion del boton 1
#define boton_2     9 //Posicion del boton 2
#define boton_3     10 //Posicion del boton 3
#define boton_4     11 //Posicion del boton 4

/*Parametros base */

const int tiempo_i = 10;
const int precio_i = 10;

#define numero_opciones   4 //opciones para controlar el menu principal
#define numero_opciones_1 5 //opciones apra controlae la seleccion de tiempo y precio

///////////////////////////////////////////////Creando Funcion para desplegar informacion en la pantalla LCD////////////////////////////////////////////////////////////////////
void basico_LCD(){
  
}

///////////////////////////////////////////////Creando Funcion para desplegar informacion en la pantalla LCD////////////////////////////////////////////////////////////////////
//Se la copie a eduardo
void desplegar_LCD(String line0, String line1, String line2)
{
  do{

    int width=16;
    int height=16;
    int scroll=width;
    int Starttext,Endtext=0;
  
//primer bloque de modo venta muestra en la pantalla el nombre de la purificadora y se espera a que se realice una accion
    lcd.setCursor(0,1);
    lcd.print(line1);
    lcd.setCursor(scroll,0);
    lcd.print(line0.substring(Starttext,Endtext));
    delay(400);
    lcd.clear();

    if(Starttext==0 && scroll>0){//Aqui se hace que las letras vayan apareciendo una por una, disminuyendo el scroll en uno y aumentando el endtext lo que hace que el substring muestre un carcter mas en la cadena
      scroll--;
      Endtext++;
    }
    else if(Starttext==Endtext){//este if se encarga de volver a mostrar el cursor en la posicion 16,0 cuando se haya acabado de mostrar la ultima letra de nuestra linea
       Starttext=Endtext=0;
        scroll=width;
    }
    else if (Endtext==line0.length() && scroll==0){//esta condicional hara que empiecen a desaparecer las letras iniciales de la linea 
      Starttext++;
    }
    else{
        Starttext++;
        Endtext++;
    }

  }while ( (digitalRead(boton_1) == HIGH) || (digitalRead(boton_2) == HIGH) || (digitalRead(boton_3) == HIGH) );
  
}


//////////////////////////////////////////////*Funcion paraa seleccionar diferentes puestos de memoria del 1 al 5*//////////////////////////////////////////////////////////////
int  Seleccionar(String modo){

  int i = 0;
  String presentacion = modo + "s"; //se le agraga la letra "s" al final de  la palabra qu envian en la cadena "modo" que le envian la funcion donde se utiliza

  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print(presentacion);
  lcd.setCursor(8,1);
  lcd.print(modo);
  lcd.setCursor(14,1);
  lcd.print(i + 1); //Se le agrega uno a la variable i para imprimir por que esta empiza desde 0

  do
  {

    if (digitalRead(boton_1) == LOW){
/*Cada vez que se presiona el digitalRead(boton_1) se agrega una unidad a la varible i y por lo tanto se selecciona la opcion siguiente*/

      i = i + 1;
    }
    else if ( (digitalRead(boton_1) == LOW) && (i == numero_opciones_1) )
    {
/*Cuando le agregas una unidad a la varible i y a llegado a la ultima opcion se regresa a la primera*/

      i = 0;
    }
    else if( (digitalRead(boton_2) == LOW) && (i != 0) ){
/*Cada vez que se presiona el digitalRead(boton_2) se resta una unidad a la varible i y por lo tanto se selecciona la opcion anterior*/

      i = i - 1;
    }
    else if ( (digitalRead(boton_2) == LOW) && (i == 0) )
    {
/*Cuando le restas una unidad a la varible y a llegado a la primera opcion, avanza a la ultima*/

      i = numero_opciones_1;
    }

/*Se despliega la opcion en pantalla dependiendo de la variable i*/
    if (i == 6){
      lcd.print(modo);
    }
    else{
/*imprime la palabra Precio junto con el valor que actual de i */
      lcd.clear();
      lcd.setCursor(7, 0);
      lcd.print(presentacion);
      lcd.setCursor(8,1);
      lcd.print(modo);
      lcd.setCursor(14,1);
      lcd.print(i + 1);
    }

  delay(500);
//Sale del ciclo cuando se presiona el boton_3
  } while (digitalRead(boton_3) == HIGH);

  return i;
}

///////////////////////////////////////////////////////*funcion que determina el timepo determinado por el usuario*/////////////////////////////////////////////////////////////

void Tiempos (){

  String mensaje_modo = "Tiempo";
  int i = 0;

/*La funcion Seleccionar devuelve una valor que determina en que direccion de memoria */
  i = Seleccionar(mensaje_modo);

/*Cunado la variable que  regresa la funcion  es 6, es decir, la opcion salor, pasa al final de la ejecucion del programa*/
while(i != 5){

/*Variables auxiliares para desplegar y cambiar el timepo*/
  int tiempo_a = 0;
  int tiempo_b = 0;

/*Se le asigna lo que hay en la direccion_p seleccionada en la variale tiempo_b*/
  tiempo_b = EEPROM.read(direccion_p[i]);

  String mensaje_opciones = "Oprima arriba y abajo para seleccionar";
  String mensaje_titulo = "SELECCION";
  String mensaje3;

  desplegar_LCD(mensaje_opciones, mensaje_titulo, mensaje3);
  

/*si tiempo_b es igual 255 significa que no hay nada escrito en esa direccion y por lo tanto imprime el tiempo base, de lo contrario imprime el timepo_b*/
  if (tiempo_b == 255)
  {
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print(tiempo_i);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print(tiempo_b);
  }
  
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al precio se le suma una unidad */
  lcd.clear();
    if(digitalRead(boton_1) == LOW){

      if (tiempo_a == 0){                                          //Cuando comenzamos a cambiar el tiempo la variable auxiliar inica en 0, entonce utilizamos esta condicion para agregarle una unidad al presionar el boton
        tiempo_a = tiempo_i + 1;
        
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(tiempo_a);
      }
      else{                                                        //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        tiempo_a = tiempo_a + 1;

        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(tiempo_a);
      }

    }
/*Al preco se le resta una unidad */
    else if (digitalRead(boton_2) == LOW){

      if (tiempo_a == 0){                                         //Cuando comenzamos a cambiar el tiempo, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
        tiempo_a = tiempo_i - 1;

        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(tiempo_a);
      }
      else{
        tiempo_a = tiempo_a - 1;                                  //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
        
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(tiempo_a);      
      }

    }

  } while (digitalRead(boton_3) == HIGH);                                         
  EEPROM.write(direccion_p[i], tiempo_a);
}

}

/////////////////////////////////////////////////////*funcion que determina el precio determinado por el usuario*/////////////////////////////////////////////////////////////

void Precios (){

  String mensaje_modo = "Precio";
  int i;

/*La funcion Seleccionar devuelve una valor que determina en que direccion de memoria a usar*/
  i = Seleccionar(mensaje_modo);

/*Cunado la variable que  regresa la funcion  es 6, es decir, la opcion salor, pasa al final de la ejecucion del programa*/
while(i != 5){

/*Variables auxiliares para desplegar y cambiar el timepo*/
  int precio_a = 0;
  int precio_b = 0;

/*Se le asigna lo que hay en la direccion_p seleccionada en la variale precio_b*/
  precio_b = EEPROM.read(direccion_t[i]);

  lcd.setCursor(0, 0);
  lcd.print("Oprima arriba y abajo para ajustar el tiempo");
  lcd.setCursor(2, 8);

/*si precio_b es igual 255 significa que no hay nada escrito en esa direccion y por lo tanto imprime el tiempo base, de lo contrario imprime el timepo_b*/
  if (precio_b == 255)
  {
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print(precio_i);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print(precio_b);
  }
  
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al precio base de le suma una unidad */
  lcd.clear();
    if(digitalRead(boton_1) == LOW){

      if (precio_a == 0){                                          //Cuando comenzamos a cambiar el tiempo la variable auxiliar inica en 0, entonce utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_i + 1;
        
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(precio_a);
      }
      else{                                                        //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_a + 1;
        
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(precio_a);
      }

    }
/*Al tiempo base de le resta una unidad */
    else if (digitalRead(boton_2) == LOW){

      if (precio_a == 0){                                         //Cuando comenzamos a cambiar el tiempo, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
        precio_a = precio_i - 1;
        
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(precio_a);
      }
      else{
        precio_a = precio_a - 1;                                  //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
        
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(mensaje_modo);
        lcd.setCursor(0,1);
        lcd.print(precio_a);      
      }

    }
  } while (digitalRead(boton_3) == HIGH);                                         
  EEPROM.write(direccion_t[i], precio_a);                 //Escribe en la memorio el precio que quedo seleccionado
}



}

//////////////////////////////////////////*funcion que determina el tiempo de enjuague determinado por el usuario*////////////////////////////////////////////////////////////////////////////////
void Enjuague(){

  int i;
  bool enjuague;

  String mensaje_opciones = "Oprima arriba y abajo para seleccionar. Enter para confirmar";
  String mensaje_modo = "Enjuague";
  String mensaje3;
// Manda a llamar la funcion desplegar_LCD para desplehar las opciones en scroll y la palabra "Enjuague"
  desplegar_LCD(mensaje_opciones, mensaje_modo, mensaje3);

// Si es la primera vez que se escribe en la memoria entonce la informacion contenida en esa direccion es 255 y por lo tanto se activa el enjuague en el primer inicio
  if( (EEPROM.read(direccion_e)) == 255){
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print("Activado");
  }

//Caso contrario manda despliega la opcion previamente almacenada

  else{
//Para el valor booleano verdadero se activa el enjuague
    if(EEPROM.read(direccion_e) == true){

      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(mensaje_modo);
      lcd.setCursor(0,1);
      lcd.print("Activado");
      enjuague = true;
    }
//Para el valor booleano falso se desactiva el enjuaghue
    else{
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(mensaje_modo);
      lcd.setCursor(0,1);
      lcd.print("Desactivado");
      enjuague = false;
    }
      
  }

  do{
//Entra en el ciclo para activar y desactivar el enjuague
  
  if ( (digitalRead(boton_1) == LOW) || (digitalRead(boton_2) == LOW) ){
//Si se apreta cualquiera de los dos botones el estado de activacion del enjuague cambia al valor booleano contrario
    enjuague = !enjuague;

  }

//Nuevamente despliega en pantalla el estado de activacion del enjuague dependiendo del valor booleano que tenga la variable enjuague
  if (enjuague == true){
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print("Activado");   
  }
  else
  {
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(mensaje_modo);
    lcd.setCursor(0,1);
    lcd.print("Desactivado");   
  }
  
//Oprimir el boton_3 termina el ciclo 
  }while ( (digitalRead(boton_3) == HIGH));
  
  EEPROM.write(direccion_e, enjuague); //Escribe en memoria el valor final de la varible enjuague que contiene un valor booleano

}

/////////////////////////////////////////////////////*Establece los parametros iniciales*/////////////////////////////////////////////////////////////////////////////////////////////

void Calibrar(){

  lcd.backlight();
  pinMode(boton_1, INPUT_PULLUP);
  pinMode(boton_2, INPUT_PULLUP);
  pinMode(boton_3, INPUT_PULLUP);
  pinMode(boton_4, INPUT_PULLUP);

  lcd.init();
  lcd.print("Hola");
}

/////////////////////////////////////////////////////////////*Funcion para desplegar el menu*////////////////////////////////////o////////////////////////////

void menu(){

  int i = 0;
  bool salir = false;
  do{
  
/*Imprimir en pantalla lcd*/
  lcd.clear();
  
  String mensaje_opciones = "Oprima arriba y abajo para seleccionar";
  String mensaje_titulo = "CONFIGURACION";
  String mensaje3;

  desplegar_LCD(mensaje_opciones, mensaje_titulo, mensaje3);

/*inicia ciclo para seleccionar la opcion deseeada dependiando del boton presionado, termina cunado se presiona el digitalRead(boton_3)*/
  do
  {
    if (digitalRead(boton_1) == LOW){
/*al presionar el boton 1 de le agrega una unidad a la varible i*/
      i = i + 1;
    }
    else if ( (digitalRead(boton_1) == LOW) && (i == numero_opciones) )
    {
/*Cuando se le quiere añadir una unidad a la variable i pero ya se ha llegado a la ultima opcion se regresa a la primera*/
      i = 0;
    }
    else if( (digitalRead(boton_2) == LOW) && (i != 0) ){
/*Cuando se presiona el digitalRead(boton_2) se le resta una unidad a la variable i*/
      i = i - 1;
    }
    else if ( (digitalRead(boton_2) == LOW) && (i == 0) )
    {
/*Cunado se le quiere restar una unidad a la varible i pero ya ha llegado a la primera se pasa a la ultima*/
      i = numero_opciones;
    }

/*Dependiendo del valor de la variable "i" imprime la opcion a seleccionar*/    
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("MENU");
    lcd.setCursor(2, 1);
    switch (i)
    {
    case 0:
      lcd.print("Tiempo");
      break;
    case 1:
      lcd.print("Precio");
      break;
    case 2:
      lcd.print("Enjuague");
      break;
    case 3:
      lcd.print("Fecha");
      break;
    case 4:
      lcd.print("Salir");
      salir = true;
      break;

    default:
      lcd.print("Error, Inente de Nuevo");
      break;
    }
/*El ciclo solo termina cuando presionamos el digitalRead(boton_3) o la opcion salir*/
  } while ( (digitalRead(boton_3) == HIGH) || (salir == true));

/*Dependiendo del valor de la variabe i se ejecuta la funcion deseada*/

  switch (i)
  {
   case 0:
     Tiempos();
     break;
  case 1:
     Precios();
     break;
   case 2:
     Enjuague();
     break;
   case 3:
//     Fecha();
     break;
   case 4:
    lcd.clear();
    lcd.print("Saliendo");
    delay(500);
    break;
   default:
    lcd.clear();
    lcd.print("Error, Inente de Nuevo");
    delay(500);
    break;
    }
  
/*Solo cuando se selecciono la opcion salir termina el ciclo y, por lo tanto, la funcion del menu */
  } while (salir == true);

}

void setup() {

  Calibrar();

}

void loop() {
  menu();
}
