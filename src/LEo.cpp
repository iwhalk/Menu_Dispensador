#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//direccion de la lcd
#define direccion_nombre 0
#define direccion_precio1 200
#define direccion_precio2
#define direccion_precio3
#define direccion_precio4
#define monedero 12
byte tiempo [5]={2,1,3,4,5};
byte boton [5]={5,6,7,8,9};
int tiempo_paro;
const int valvula =11;
String line3 = "CATIVA";
String line2;
String line1;
int credito=0;
int precio_boton1;
int precio_boton2;
int precio_boton3;
int precio_boton4 ;
int width=16;
int height=16;
int scroll=width;
int Starttext,Endtext=0;
String texto_boton1 = "Deposite    pesos";

void setup() {
  // put your setup code here, to run once:
lcd.begin();
lcd.backlight();
Serial.begin(9600); 
pinMode(boton[0],INPUT);
pinMode(boton[1],INPUT);
pinMode(boton[2],INPUT);
pinMode(boton[3],INPUT);
pinMode(boton[4],INPUT);
pinMode(monedero,INPUT);
pinMode(valvula,OUTPUT);
  EEPROM.put(direccion_nombre , line3);
  EEPROM.put(direccion_precio1 , 20);
  EEPROM.get(direccion_nombre , line2);
  EEPROM.get(direccion_precio1, precio_boton1);
}

void modo_venta()
{
 //primer bloque de modo venta muestra en la pantalla el nombre de la purificadora y se espera a que se realice una accion
  line1 = "PURIFICADORA DE AGUA " + line2;
  lcd.setCursor(0,1);
  lcd.print("Deposite monedas");
  lcd.setCursor(scroll,0);
  lcd.print(line1.substring(Starttext,Endtext));
    delay(400);
    lcd.clear();
  if(Starttext==0 && scroll>0){//Aqui se hace que las letras vayan apareciendo una por una, disminuyendo el scroll en uno y aumentando el endtext lo que hace que el substring muestre un carcter mas en la cadena
    scroll--;
    Endtext++;}
  else if(Starttext==Endtext){//este if se encarga de volver a mostrar el cursor en la posicion 16,0 cuando se haya acabado de mostrar la ultima letra de nuestra linea
     Starttext=Endtext=0;
      scroll=width;}
  else if (Endtext==line1.length() && scroll==0){//esta condicional hara que empiecen a desaparecer las letras iniciales de la linea 
    Starttext++;}
   else{
      Starttext++;
      Endtext++;}

 //segundo bloque, aqui si se presiona el boton aparece una cuenta regresiva y el tiempo a pagar
  if(digitalRead(boton[0])==1){
    int temporizador=480;
     do{
       temporizador--;
       lcd.clear ();
       lcd.print(texto_boton1 );
       lcd.setCursor(9,0);
       lcd.print(precio_boton1);
       lcd.setCursor(0,1);
        lcd.print("tienes    seg"); 
        lcd.setCursor(7,1);
        lcd.print(temporizador/8);
        delay(120);
   //si el programa detecta un pulso del monedero lo guarda en la variable credito y te manda a una pantalla en la que se muestra el credito que llevas
       if (digitalRead(monedero)==1){
          ++credito;
           do{ 
            if (digitalRead(monedero)==1){
              ++credito;}
              lcd.clear();
              lcd.setCursor(4,0);
              lcd.print("Credito");
              lcd.setCursor(7,1);
              lcd.print(credito);
              delay(100);
           //cuando tu credito sea igual al precio del boton presionado mandara a la funcion llenado
              if(credito>=precio_boton1){
                credito=0;
                 return llenado_1();}
          }while(true); 
        }
      }while(digitalRead(boton[0])==0 && temporizador>0);
     }
  else if(digitalRead(boton[1])==1){
    venta2();
  }
  else if(digitalRead(boton[2])==1){
    venta3();
  }
  //si en lugar de presionar boton se deposita un credito, se ejecutara esta parte del codigo
  else if (digitalRead(monedero)==1){
      ++credito;
    //esta parte se  encarga de leer los creditos depositados
     do {
       if (digitalRead(monedero)==1){
         ++credito;}
         lcd.clear();
         lcd.setCursor(4,0);
         lcd.print("Credito");
         lcd.setCursor(7,1);
         lcd.print(credito);
         delay(100);
     //el programa dejara de contar creditos hasta que se seleccione un boton
     }while(digitalRead(boton[0])==0 && digitalRead(boton[1])==0 && digitalRead(boton[2])==0);
     //aqui se llama a la funcion que detecta el numero de boton que fue presionado
     button_pressed ();
     credito=0;
 
  }
}
void venta2 (){
   int temporizador=480;
     do{
       temporizador--;
       lcd.clear ();
       lcd.print(texto_boton1);
       lcd.setCursor(9,0);
       lcd.print(precio_boton2);
       lcd.setCursor(0,1);
        lcd.print("tienes    seg"); 
        lcd.setCursor(7,1);
        lcd.print(temporizador/8);
        delay(120);
   //si el programa detecta un pulso del monedero lo guarda en la variable credito y te manda a una pantalla en la que se muestra el credito que llevas
       if (digitalRead(monedero)==1){
          ++credito;
           do{ 
            if (digitalRead(monedero)==1){
              ++credito;}
              lcd.clear();
              lcd.setCursor(4,0);
              lcd.print("Credito");
              lcd.setCursor(7,1);
              lcd.print(credito);
              delay(100);
           //cuando tu credito sea igual al precio del boton presionado mandara a la funcion llenado
              if(credito>=precio_boton2){
                credito=0;
                 return llenado_2();}
          }while(true); 
        }
      }while(digitalRead(boton[1])==0 && temporizador>0);
}
void venta3 (){
   int temporizador=480;
     do{
       temporizador--;
       lcd.clear ();
       lcd.print(texto_boton1);
       lcd.setCursor(9,0);
       lcd.print(precio_boton3);
       lcd.setCursor(0,1);
        lcd.print("tienes    seg"); 
        lcd.setCursor(7,1);
        lcd.print(temporizador/8);
        delay(120);
   //si el programa detecta un pulso del monedero lo guarda en la variable credito y te manda a una pantalla en la que se muestra el credito que llevas
       if (digitalRead(monedero)==1){
          ++credito;
           do{ 
            if (digitalRead(monedero)==1){
              ++credito;}
              lcd.clear();
              lcd.setCursor(4,0);
              lcd.print("Credito");
              lcd.setCursor(7,1);
              lcd.print(credito);
              delay(100);
           //cuando tu credito sea igual al precio del boton presionado mandara a la funcion llenado
              if(credito>=precio_boton3){
                credito=0;
                 return llenado_3();}
          }while(true); 
        }
     }while(digitalRead(boton[0])==0 && temporizador>0); 
}


//esta funcion activa la electrovalvula durante el tiempo configurado por el usuario
void  llenado_1(){
  lcd.clear();
  int timer=millis()/1000;
  do{
    tiempo_paro=millis()/1000;
    digitalWrite(valvula,HIGH);
    lcd.setCursor(3,0);
    lcd.print("Llenando");
    lcd.setCursor(2,1);
    lcd.print("Espere...");
  
  }while(tiempo_paro-timer<=tiempo[0]);
  }

  
void llenado_2(){
  lcd.clear();
  int timer=millis()/1000;
  do{
    tiempo_paro=millis()/1000;
    digitalWrite(valvula,HIGH);
    lcd.setCursor(3,0);
    lcd.print("Llenando");
    lcd.setCursor(2,1);
    lcd.print("Espere...");
  
  }while(tiempo_paro-timer<=tiempo[1]);}



void llenado_3() {

  lcd.clear();
  int timer=millis()/1000;

  do{
    tiempo_paro=millis()/1000;
    digitalWrite(valvula,HIGH);
    lcd.setCursor(3,0);
    lcd.print("Llenando");
    lcd.setCursor(2,1);
    lcd.print("Espere...");
  
  }while(tiempo_paro-timer<=tiempo[2]);
  }



void llenado_4()
{
  lcd.clear();
  int timer=millis()/1000;
  do{
    tiempo_paro=millis()/1000;
    digitalWrite(valvula,HIGH);
    lcd.setCursor(3,0);
    lcd.print("Llenando");
    lcd.setCursor(2,1);
    lcd.print("Espere...");
  
  }while(tiempo_paro-timer<=tiempo[3]);
}



void enjuague (){}


void button_pressed (){
  for(int i;i<=2;i++)
  
  if(digitalRead(boton[i])==1){
       switch(boton[i]){
      case 5:
        if(credito>=precio_boton1){
          llenado_1();
           if(credito>precio_boton1){
              lcd.clear();
              lcd.setCursor(3,0);
              lcd.print("Tome su");
              lcd.setCursor(4,1);
              lcd.print("cambio");
              delay(300);}    
        }
        else{
          completar_credito1();
        }
        break;
      case 6:
          if(credito>=precio_boton2){
            llenado_2(); 
             if(credito>precio_boton2){
              lcd.clear();
              lcd.setCursor(3,0);
              lcd.print("Tome su");
              lcd.setCursor(4,1);
              lcd.print("cambio");
              delay(3000);}    
        }
        else{
          completar_credito2();
        }
        break; 
       case 7:
        if(credito>=precio_boton3){
            llenado_3(); 
             if(credito>precio_boton3){
              lcd.clear();
              lcd.setCursor(3,0);
              lcd.print("Tome su");
              lcd.setCursor(4,1);
              lcd.print("cambio");
              delay(3000);}    
        }
        else{
          completar_credito3();
        }
        break;  
       }
    }
    
}

void completar_credito1(){
  lcd.clear();
  lcd.print("Credito insuficiente");
  delay(1000);
    do {
       if (digitalRead(monedero)==1){
         ++credito;}
       lcd.clear();
       lcd.print(texto_boton1);
       lcd.setCursor(9,0);
       lcd.print(precio_boton1);
       lcd.setCursor(7,1);
       lcd.print(credito);
       delay(120);
       
  }while(credito<precio_boton1);
  llenado_1 ();
}
void completar_credito2(){
  lcd.clear();
  lcd.print("Credito insuficiente");
  delay(1000);
    do {
       if (digitalRead(monedero)==1){
         ++credito;}
       lcd.clear();
       lcd.print(texto_boton1);
       lcd.setCursor(9,0);
       lcd.print(precio_boton2);
       lcd.setCursor(7,1);
       lcd.print(credito);
       delay(120);
       
  }while(credito<precio_boton2);
  llenado_2 ();
 
}

void completar_credito3(){
  lcd.clear();
  lcd.print("Credito insuficiente");
  delay(1000);
    do {
       if (digitalRead(monedero)==1){
         ++credito;}
       lcd.clear();
       lcd.print(texto_boton1);
       lcd.setCursor(9,0);
       lcd.print(precio_boton3);
       lcd.setCursor(7,1);
       lcd.print(credito);
       delay(120);
       
  }while(credito<precio_boton3);
  llenado_3 ();
}
void loop() {// put your main code here, to run repeatedly:
  
  modo_venta ();
 
}