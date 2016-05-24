 /**
 * @file      pantalla.c
 * @brief     Fichero de las funciones utilizadas por la tareaPantalla.
 * @par		  Descripci�n de la funci�n:
 * 			  Conjunto de funciones que utiliza la tareaPantalla para
 * 			  comunicarse con el HAL para realizar al impresion en pantalla.
 * @author    Javier Barrag�n
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include <stdio.h>
#include "display.h"
#include "watch.h"
#include "dataDisplay.h"
#include "dataSensors.h"

#include "pantalla.h"
/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

void APP_PANTALLA_screenClock(void);

void APP_PANTALLA_screenSensor(unsigned int Id);

void APP_PANTALLA_screenBanner(unsigned int Id);

void APP_PANTALLA_printTipo(CONFIG_SENSORS Id);

void APP_PANTALLA_printValor(float valor);

void APP_PANTALLA_printUnidad(CONFIG_SENSORS Id);

void APP_PANTALLA_printMensaje(char str[]);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/
char str[];
/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

//variables globales, precedidas de static (privada)

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void APP_PANTALLA_init()
{
    //inicializacion display
    HAL_DISPLAY_init();
    HAL_DISPLAY_refresh();
}

void APP_PANTALLA_mostrar()
{
	unsigned int Id;
	Id=APP_DATA_DISPLAY_getIdPantalla();
	if(Id==0) APP_PANTALLA_screenClock();
	else if(Id<10) APP_PANTALLA_screenSensor(Id);
	else if(Id>10) APP_PANTALLA_screenBanner(Id);
	else APP_PANTALLA_printMensaje("Error");
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
************************************************
*****************************************************/
/**
 * @fn         APP_PANTALLA_screenClock
 * @brief      Display del tiempo.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n que empieza con el llamado para
 * 			   imprimir el reloj en pantalla.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/05/2016
 */
void APP_PANTALLA_screenClock()
{
	LIBS_WATCH_displayTime();
}

/**
 * @fn         APP_PANTALLA_screenSensor
 * @brief      Display del sensor.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n que empieza con el llamado para
 * 			   imprimir el tipo, valor y unidad de un sensor en pantalla.
 * @param[in]  unsigned int ID, identificador del sensor.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/05/2016
 */
void APP_PANTALLA_screenSensor(unsigned int Id)
{
	DATAMANAGEMENT_SENSOR_DATA SENSOR;
	SENSOR=APP_DATA_SENSORS_getSensorData(Id);
	APP_PANTALLA_printTipo(SENSOR.nId);
	APP_PANTALLA_printValor(SENSOR.value);
	APP_PANTALLA_printUnidad(SENSOR.nId);
}

/**
 * @fn         APP_PANTALLA_screenBanner
 * @brief      Display de mensajes fijos.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n encargada de reproducir en el
 * 			   display los mensajes fijos sin valores.
 * @param[in]  unsigned int Id, Identificador del mensaje.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/05/2016
 */
void APP_PANTALLA_screenBanner(unsigned int Id)
{
	if(Id==40)	APP_PANTALLA_printMensaje("Recogiendo Datos...");
	else if(Id==41) APP_PANTALLA_printMensaje("Enviando Datos...");
	else if(Id==42) APP_PANTALLA_printMensaje("Boton de panico ON");
	else if(Id==43) APP_PANTALLA_printMensaje("Datos Recogidos");
	else APP_PANTALLA_printMensaje("Error");
}

/**
 * @fn         APP_PANTALLA_printTipo
 * @brief      Funci�n para imprimir el Tipo de sensor.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n encargada de reproducir en el
 * 			   display el tipo de sensor seleccionado y que
 * 			   se reproducir� sus datos en pantalla.
 * @param[in]  CONFIG_SENSORS Id, Identificador de la estructura del sensor.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       24/05/2016
 */
void APP_PANTALLA_printTipo(CONFIG_SENSORS Id)
{
	if(Id==PULSOMETRO) sprintf(str,"PULSOMETRO");
	else if(Id==BASCULA) sprintf(str,"BASCULA");
	else if(Id==GPS) sprintf(str,"GPS");
	HAL_DISPLAY_printString(str,'T');
}

/**
 * @fn         APP_PANTALLA_printValor
 * @brief      Funci�n para imprimir el Valor del sensor.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n encargada de reproducir en el
 * 			   display el valor de sensor seleccionado y que
 * 			   se reproducir� sus datos en pantalla.
 * @param[in]  float valor, valor del sensor.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       24/05/2016
 */
void APP_PANTALLA_printValor(float valor)
{
	sprintf(str,"%f\0",valor);
	HAL_DISPLAY_printString(str,'V');
}

/**
 * @fn         APP_PANTALLA_printUnidad
 * @brief      Funci�n para imprimir la Unidad del sensor.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n encargada de reproducir en el
 * 			   display la unidad del sensor seleccionado y que
 * 			   se reproducir� sus datos en pantalla.
 * @param[in]  CONFIG_SENSORS Id, Identificador del sensor.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       24/05/2016
 */
void APP_PANTALLA_printUnidad(CONFIG_SENSORS Id)
{
	if(Id==PULSOMETRO) sprintf(str,"BPM");
	else if(Id==BASCULA) sprintf(str,"KG");
	HAL_DISPLAY_printString(str,'U');
}

/**
 * @fn         APP_PANTALLA_printMensaje
 * @brief      Funci�n para imprimir mensajes en pantalla.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n encargada de reproducir en el
 * 			   display mensajes y que se reproducir� en pantalla.
 * @param[in]  char str[], cadena de caracteres del mensaje.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       24/05/2016
 */
void APP_PANTALLA_printMensaje(char str[])
{
	HAL_DISPLAY_printString(str,'V');
}
