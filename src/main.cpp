#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

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
const bool enjuague_i = true;

#define numero_opciones   4 //opciones para controlar el menu principal
#define numero_opciones_1 5 //opciones apra controlae la seleccion de tiempo y precio

//////////////////////////////////////////////*Funcion paraa seleccionar diferentes puestos de memoria del 1 al 5*//////////////////////////////////////////////////////////////
int  Seleccionar(){

  int i = 0;

  do
  {

    if (digitalRead(boton_1)){
/*Cada vez que se presiona el digitalRead(boton_1) se agrega una unidad a la varible i y por lo tanto se selecciona la opcion siguiente*/

      i = i + 1;
    }
    else if ( (digitalRead(boton_1)) && (i == numero_opciones_1) )
    {
/*Cuando le agregas una unidad a la varible i y a llegado a la ultima opcion se regresa a la primera*/

      i = 0;
    }
    else if( (digitalRead(boton_2)) && (i != 0) ){
/*Cada vez que se presiona el digitalRead(boton_2) se resta una unidad a la varible i y por lo tanto se selecciona la opcion anterior*/

      i = i - 1;
    }
    else if ( (digitalRead(boton_2)) && (i == 0) )
    {
/*Cuando le restas una unidad a la varible y a llegado a la primera opcion, avanza a la ultima*/

      i = numero_opciones_1;
    }

/*Se despliega la opcion en pantalla dependiendo de la variable i*/
    if (i == 6){
      lcd.print("Salir");
    }
    else{
/*imprime la palabra Precio junto con el valor que actual de i */
      lcd.clear();
      lcd.setCursor(2, 8);
      lcd.print("Tiempo ");
      lcd.setCursor(2,15);
      lcd.print(i + 1);
    }

  } while (digitalRead(boton_3) == 1);

  return i;
}

///////////////////////////////////////////////////////*funcion que determina el timepo determinado por el usuario*/////////////////////////////////////////////////////////////

void Tiempos (){
  int i = 0;

/*La funcion Seleccionar devuelve una valor que determina en que direccion de memoria */
  i = Seleccionar();

/*Cunado la variable que  regresa la funcion  es 6, es decir, la opcion salor, pasa al final de la ejecucion del programa*/
while(i == 5){

/*Variables auxiliares para desplegar y cambiar el timepo*/
  int tiempo_a = 0;
  int tiempo_b = 0;

/*Se le asigna lo que hay en la direccion_p seleccionada en la variale tiempo_b*/
  tiempo_b = EEPROM.read(direccion_p[i]);

  lcd.setCursor(0, 0);
  lcd.print("Oprima arriba y abajo para ajustar el tiempo");
  lcd.setCursor(2, 8);

/*si tiempo_b es igual 255 significa que no hay nada escrito en esa direccion y por lo tanto imprime el tiempo base, de lo contrario imprime el timepo_b*/
  if (tiempo_b == 255)
  {
    lcd.print(tiempo_i);
  }
  else
  {
    lcd.print(tiempo_b);
  }
  
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al precio se le suma una unidad */
  lcd.clear();
    if(digitalRead(boton_1)){

      if (tiempo_a == 0){                                          //Cuando comenzamos a cambiar el tiempo la variable auxiliar inica en 0, entonce utilizamos esta condicion para agregarle una unidad al presionar el boton
        tiempo_a = tiempo_i + 1;
        lcd.clear();
        lcd.print(tiempo_a);
      }
      else{                                                        //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        tiempo_a = tiempo_a + 1;
        lcd.clear();
        lcd.print(tiempo_a);
      }

    }
/*Al preco se le resta una unidad */
    else if (digitalRead(boton_2)){

      if (tiempo_a == 0){                                         //Cuando comenzamos a cambiar el tiempo, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
        tiempo_a = tiempo_i - 1;
        lcd.clear();
        lcd.print(tiempo_a);
      }
      else{
        tiempo_a = tiempo_a - 1;                                  //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
        lcd.clear();
        lcd.print(tiempo_a);      
      }

    }
  } while (digitalRead(boton_3) == 0);                                         
  EEPROM.write(direccion_p[i], tiempo_a);
}

}

/////////////////////////////////////////////////////*funcion que determina el precio determinado por el usuario*/////////////////////////////////////////////////////////////

void Precios (){
  int i;

/*La funcion Seleccionar devuelve una valor que determina en que direccion de memoria a usar*/
  i = Seleccionar();

/*Cunado la variable que  regresa la funcion  es 6, es decir, la opcion salor, pasa al final de la ejecucion del programa*/
while(i == 5){

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
    lcd.print(precio_i);
  }
  else
  {
    lcd.print(precio_b);
  }
  
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al precio base de le suma una unidad */
  lcd.clear();
    if(digitalRead(boton_1)){

      if (precio_a == 0){                                          //Cuando comenzamos a cambiar el tiempo la variable auxiliar inica en 0, entonce utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_i + 1;
        lcd.clear();
        lcd.print(precio_a);
      }
      else{                                                        //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_a + 1;
        lcd.clear();
        lcd.print(precio_a);
      }

    }
/*Al tiempo base de le resta una unidad */
    else if (digitalRead(boton_2)){

      if (precio_a == 0){                                         //Cuando comenzamos a cambiar el tiempo, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
        precio_a = precio_i - 1;
        lcd.clear();
        lcd.print(precio_a);
      }
      else{
        precio_a = precio_a - 1;                                  //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
        lcd.clear();
        lcd.print(precio_a);      
      }

    }
  } while (digitalRead(boton_3) == 0);                                         
  EEPROM.write(direccion_t[i], precio_a);
}

}



//////////////////////////////////////////*funcion que determina el tiempo de enjuague determinado por el usuario*////////////////////////////////////////////////////////////////////////////////
void Enjuague(){

  int i;
  bool enjuague;


  lcd.clear();
  lcd.setCursor(1, 3);
  lcd.print("Oprima arriba y abajo para seleccionar");

  if( (EEPROM.read(direccion_e)) == 255){
    lcd.print("Enjuague Activado");
  }

  else{
    if(EEPROM.read(direccion_e) == true){
      lcd.print("Enjuague Desactivado");
    }
    else{
      lcd.print("Enjuague Desactivado");
    }
      
  }

  Seleccionar();


  
}

/////////////////////////////////////////////////////*Establece los parametros iniciales*/////////////////////////////////////////////////////////////////////////////////////////////

void Calibrar(){

  pinMode(boton_1, INPUT);
  pinMode(boton_2, INPUT);
  pinMode(boton_3, INPUT);
  pinMode(boton_4, INPUT);

  lcd.begin(16,4);
  lcd.print("Hola");
}

/////////////////////////////////////////////////////////////*Funcion para desplegar el menu*////////////////////////////////////////////////////////////////

void menu(){

  int i = 0;
  bool salir = false;
  do{
  
/*Imprimir en pantalla lcd*/
  lcd.clear();
  lcd.setCursor(1, 3);
  lcd.print("Oprima arriba y abajo para seleccionar");

/*inicia ciclo para seleccionar la opcion deseeada dependiando del boton presionado, termina cunado se presiona el digitalRead(boton_3)*/
  do
  {
    if (digitalRead(boton_1)){
/*al presionar el boton 1 de le agrega una unidad a la varible i*/
      i = i + 1;
    }
    else if ( (digitalRead(boton_1)) && (i == numero_opciones) )
    {
/*Cuando se le quiere añadir una unidad a la variable i pero ya se ha llegado a la ultima opcion se regresa a la primera*/
      i = 0;
    }
    else if( (digitalRead(boton_2)) && (i != 0) ){
/*Cuando se presiona el digitalRead(boton_2) se le resta una unidad a la variable i*/
      i = i - 1;
    }
    else if ( (digitalRead(boton_2)) && (i == 0) )
    {
/*Cunado se le quiere restar una unidad a la varible i pero ya ha llegado a la primera se pasa a la ultima*/
      i = numero_opciones;
    }

/*Dependiendo del valor de la variable "i" imprime la opcion a seleccionar*/    
    lcd.clear();
    lcd.setCursor(2, 8);
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
  } while ( (digitalRead(boton_3) == 1) || (salir == true));

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
     lcd.print("Saliendo");
     break;
   default:
     lcd.print("Error, Inente de Nuevo");
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