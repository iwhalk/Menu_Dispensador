#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/* direcciones de utilizadas de la memoria EEPROM */

#define direccion_2 5 //Direccion para definir el precio
#define direccion_3 6 //Direccion para definir el timepo de enjuague
#define direccion_4 7 //Direccion para definir la fecha??

/*Botones Utilizados para la configuracion*/

#define boton_1     8 //Posicion del boton 1
#define boton_2     9 //Posicion del boton 2
#define boton_3     10 //Posicion del boton 3
#define boton_4     11 //Posicion del boton 4

/*Parametros base */

const int tiempo_i = 10;
const int precio_i = 10;
const int enjuague_i = 10;
const int fecha_i = 10;

const int direccion_p[5] = {0, 1, 2, 3, 4};
const int direccion_t[5] = {5, 6, 7, 8, 9};

#define numero_opciones 4
#define numero_opciones_1 6

/*Instrucciones para desplegar en pantalla(regresa la opcion deseada)*/

int  Seleccionar(){

  int i = 0;

  do
  {

    if (boton_1){

      i = i + 1;
    }
    else if ( (boton_1) && (i == numero_opciones_1) )
    {
      i = 0;
    }
    else if( (boton_2) && (i != 0) ){
      i = i - 1;
    }
    else if ( (boton_2) && (i == 0) )
    {
      i = numero_opciones_1;
    }

    if (i == 6){
      lcd.print("Salir");
    }
    else{
      lcd.clear();
      lcd.setCursor(2, 8);
      lcd.print("Precio ");
      lcd.setCursor(2,15);
      lcd.print(i);
    }

  } while (boton_3 == 0);

  return i;
}

/*funcion que determina el timepo determinado por el usuario*/

void Tiempos (){
  int i;


  i = Seleccionar();

while(i == 6){

/*Variables auxiliares para desplegar y cambiar el timepo*/
  int tiempo_a = 0; 
  int tiempo_b = 0;

/*Se le asigna lo que hay en la direccion_p seleccionada en la variale tiempo_b*/
  tiempo_b = EEPROM.read(direccion_t[i]);

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
/*Al tiempo base de le suma una unidad */
  lcd.clear();
    if(boton_1){

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
/*Al tiempo base de le resta una unidad */
    else if (boton_2){

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
  } while (boton_3 == 0);                                         
  EEPROM.write(direccion_t[i], tiempo_a);
}

}

/*funcion que determina el precio determinado por el usuario*/

void Precios(){

  int precio_a = 0;

  Serial.println("Oprima arriba y abajo para ajustar el precio");
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  do
  {
/*Al precio base de le suma una unidad */
    if(boton_1){
      if (precio_a == 0){                                       //Cuando comenzamos a cambiar el precio, al variable auxiliar inica en 0, utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_a + (precio_i + 1);
      }
      else{                                                     //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para agregarle una unidad al presionar el boton
        precio_a = precio_a + 1;
      }
    }
/*Al precio base de le resta una unidad */
    else if (boton_2){
      if (precio_a == 0){                                       //Cuando comenzamos a cambiar el precio, al variable auxiliar inica en 0, utilizamos esta condicion para quitarle una unidad al presionar el boton
  
        precio_a = precio_a + (precio_i - 1);
      }
      else{
        precio_a = precio_a - 1;                                //Despues la variable auxiliar ya tiene valores almacenado y utilizamos esta condicion para quitarle una unidad al presionar el boton
      }
    }
  } while (boton_3 == true);
  
  EEPROM.write(direccion_2, precio_a);

}

/*funcion que determina el tiempo de enjuague determinado por el usuario*/

void Enjuague(){

  int enjuague_a = 0;
/*Se ejecuta el siguiente bucle hasta que se presiones el boton 3*/
  Serial.println("Oprima arriba y abajo para ajustar el timepo de enjuague");
  do
  {
/*Al tiempo de enjuague base de le suma una unidad */
    if(boton_1){
      if (enjuague_a == 0){
        enjuague_a = enjuague_a + (enjuague_i + 1);
      }
      else{
        enjuague_a = enjuague_a + 1;
      }
    }
/*Al tiempo de enjuague base de le resta una unidad */
    else if (boton_2){
      if (enjuague_a == 0){
        enjuague_a = enjuague_a + (enjuague_i - 1);
      }
      else{
        enjuague_a = enjuague_a - 1;
      }
    }
  } while (boton_3 != true);
  
  EEPROM.write(direccion_3, enjuague_a);

}

/*Establece los parametros iniciales*/

void Calibrar(){

  pinMode(boton_1, INPUT);
  pinMode(boton_2, INPUT);
  pinMode(boton_3, INPUT);
  pinMode(boton_4, INPUT);

  lcd.begin(16,4);
  lcd.print("Hola");
}

/*Funcion para desplegar el menu*/

void menu(){

  int i = 0;
  bool salir = false;

  lcd.clear();
  lcd.setCursor(1, 3);
  lcd.print("Oprima arriba y abajo para seleccionar");

  do
  {
    if (boton_1){

      i = i + 1;
    }
    else if ( (boton_1) && (i == numero_opciones) )
    {
      i = 0;
    }
    else if( (boton_2) && (i != 0) ){

      i = i - 1;
    }
    else if ( (boton_2) && (i == 0) )
    {
      i = numero_opciones;
    }
    
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

  } while ( (boton_3 == 0) || (salir == true));

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

}

void setup() {

  Calibrar();

}

void loop() {

}