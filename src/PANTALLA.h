#ifndef PANTALLA_H
#define PANTALLA_H

#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


class PANTALLA {
private:
  LiquidCrystal_I2C *LCD;
public:
  PANTALLA(int _Direccion, int _Columnas, int _Filas);
  void PRUEBAS(int _Dato);
  void CLEAR();
  void BIENVENIDA(String _Nombre_Purificadora);
  void DEPOSITE(float _Cantidad, unsigned long _Tiempo);
  void ESPERA(String _Estado);
  void CREDITO();
  void CALIBRACION(int _Numero_Prueba, int _Muestras_Litro_Calibracion);
  void EJECUTA_CALIBRACION(int _Numero_Prueba);
  int MENU(int _Numero_Menu);
  int SUBMENU(int _Numero_Menu, int _Numero_Sub_Menu);
  int ELECCION(int _Numero_Menu, int _Numero_Sub_Menu,float _Eleccion);



};

PANTALLA::PANTALLA(int _Direccion, int _Columnas, int _Filas) {
  LCD = new LiquidCrystal_I2C(_Direccion, _Columnas, _Filas);
  LCD->init();
  LCD->backlight();
}

void PANTALLA::CLEAR() {
  LCD->clear();
}

void PANTALLA::PRUEBAS(int _Dato) {
  LCD->print(_Dato);
}

void PANTALLA::BIENVENIDA(String _Nombre_Purificadora) {
  LCD->setCursor(0, 2);
  LCD->print(_Nombre_Purificadora);
}

void PANTALLA::DEPOSITE(float _Cantidad, unsigned long _Tiempo) {
  LCD->setCursor(0, 1); LCD->print(" DEPOSITE POR FAVOR ");
  LCD->setCursor(0, 2); LCD->print("       $"); LCD->print(_Cantidad);
  LCD->setCursor(1, 3); LCD->print("TIENES "); LCD->print(_Tiempo); LCD->print(" SEGUNDOS");
}

void PANTALLA::ESPERA(String _Estado) {
  LCD->setCursor(0, 0); LCD->print(" NO ABRIR LA PUERTA ");
  LCD->setCursor(0, 1); LCD->print("  ESPERE POR FAVOR  ");
  LCD->setCursor(5, 2); LCD->print(_Estado);
}

void PANTALLA::CREDITO() {
  LCD->setCursor(0, 1); LCD->print("CREDITO INSUFICIENTE");
  LCD->setCursor(0, 2); LCD->print("DEPOSITA MAS MONEDAS");
}

void PANTALLA::CALIBRACION(int _Numero_Prueba, int _Muestras_Litro_Calibracion){
  LCD->setCursor(3,0);LCD->print("CALIBRACION #");LCD->print(_Numero_Prueba);
  LCD->setCursor(8,1);LCD->print(_Muestras_Litro_Calibracion);
  LCD->setCursor(0,2);LCD->print("MUESTRAS REGISTRADAS");
}

void PANTALLA::EJECUTA_CALIBRACION(int _Numero_Prueba){
  LCD->setCursor(3,0);LCD->print("CALIBRACION #");LCD->print(_Numero_Prueba);
  LCD->setCursor(2,1);LCD->print("PRESIONE 'ENTER'");
  LCD->setCursor(0,2);LCD->print(" LLENADOS 10 LITROS ");
}

int PANTALLA::MENU(int _Numero_Menu) {
  delay(50);
  LCD->clear();  
  switch (_Numero_Menu) {
  case 0:
    LCD->setCursor(5, 1); LCD->write(126); LCD->print("TIEMPOS"); LCD->write(127);
    if (_Numero_Menu > 4 || _Numero_Menu < 0 )
      _Numero_Menu = 0;
    break;
  case 1:
    LCD->setCursor(5, 1); LCD->write(126); LCD->print("PRECIOS"); LCD->write(127);
    if (_Numero_Menu > 4 || _Numero_Menu < 0 )
      _Numero_Menu = 0;
    break;
  case 2:
    LCD->setCursor(5, 1); LCD->write(126); LCD->print("ENJUAGE"); LCD->write(127);
    if (_Numero_Menu > 4 || _Numero_Menu < 0 )
      _Numero_Menu = 0;
    break;

  case 3:
    LCD->setCursor(3, 1); LCD->write(126); LCD->print("CAUDALIMETRO"); LCD->write(127);
    if (_Numero_Menu > 4 || _Numero_Menu < 0 )
      _Numero_Menu = 0;
    break;

  case 4:
    LCD->setCursor(5, 1); LCD->write(126); LCD->print(" SALIR "); LCD->write(127);
    if (_Numero_Menu > 4 || _Numero_Menu < 0 )
      _Numero_Menu = 0;
    break;
        
  default:
    if (_Numero_Menu > 4 || _Numero_Menu < 0 )
      _Numero_Menu = 0;
  }
  return _Numero_Menu;
}

int PANTALLA::SUBMENU(int _Numero_Menu, int _Numero_Sub_Menu) {
  delay(50);
  LCD->clear();
  switch (_Numero_Menu) {
  case 0:
    LCD->setCursor(5, 1); LCD->write(126); LCD->print("TIEMPO "); LCD->print(_Numero_Sub_Menu + 1); LCD->write(127);
    if (_Numero_Sub_Menu < 0 || _Numero_Sub_Menu > 7)
      _Numero_Sub_Menu = 0;
    break;
  case 1:
    LCD->setCursor(5, 1); LCD->write(126); LCD->print("PRECIO "); LCD->print(_Numero_Sub_Menu + 1); LCD->write(127);
    if (_Numero_Sub_Menu < 0 || _Numero_Sub_Menu > 7)
      _Numero_Sub_Menu = 0;
    break;
  case 2:
    LCD->setCursor(4, 1); LCD->write(126); LCD->print("ENJUAGE "); LCD->print(_Numero_Sub_Menu + 1); LCD->write(127);
    if (_Numero_Sub_Menu < 0 || _Numero_Sub_Menu > 1)
      _Numero_Sub_Menu = 0;
    break;

  case 3:
    LCD->setCursor(2, 1); LCD->write(126); LCD->print("CAUDALIMETRO "); LCD->print(_Numero_Sub_Menu + 1); LCD->write(127);
    if (_Numero_Sub_Menu < 0 || _Numero_Sub_Menu > 1)
      _Numero_Sub_Menu = 0;
    break;
  }
  
  return _Numero_Sub_Menu;
}

int PANTALLA::ELECCION(int _Numero_Menu, int _Numero_Sub_Menu, float _Eleccion){

  switch (_Numero_Menu) {
      delay(50);
      LCD->clear();
      case 0:
        LCD->setCursor(0, 1);LCD->print("   EL TIEMPO "); LCD->print(_Numero_Sub_Menu + 1); LCD->print(" ES: ");
        LCD->setCursor(3, 2);LCD->print(_Eleccion); LCD->print("  SEGUNDOS");
        if (_Eleccion < 0)
          _Eleccion = 0;
        break;
      case 1:
        LCD->setCursor(0, 1);LCD->print("   EL PRECIO "); LCD->print(_Numero_Sub_Menu + 1); LCD->print(" ES: ");
        LCD->setCursor(5, 2);LCD->print("$");LCD->print(_Eleccion*0.5); LCD->print(" PESOS");
        if (_Eleccion < 0)
          _Eleccion = 0;
        break;

      case 2:
        LCD->setCursor(0,1);LCD->print(" EL ENJUAGE "); LCD->print(_Numero_Sub_Menu + 1); LCD->print(" ESTA: ");
        if(_Eleccion == 0){
          LCD->setCursor(0,2);LCD->print("     DESACTIVADO    ");
        }
        else if(_Eleccion==1){
          LCD->setCursor(0,2);LCD->print("      ACTIVADO      ");
        }
        else if(_Eleccion< 0 || _Eleccion>1 ){
           _Eleccion = 0;
        }
  }
  return _Eleccion;
}

#endif
