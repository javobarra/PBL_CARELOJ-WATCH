/**
 * @file    main.c
 * @brief   Fichero principal
 * @par		Logica
 *			- Inicializa las tareas y el hardware
 *			- Tarea para gestionar el control de la m�quina de estados del reloj
 *			- Tarea para gestionar el env�o de datos del reloj al exterior
 * @par		Flujo
 * @image	html diagrama.genral.jpg
 * @author  F. Dom�nguez
 * @date    19/02/2016
 * @todo	Implementar control entre tareas
 * @todo    A�adir tarea de control de pantalla
 * @todo    Crear funci�n para la inicializaci�n
 */


#include "tareaLogica.h"
#include "tareaEnvio.h"
#include "tareaPantalla.h"
#include "timer_scugic.h"
#include "axi-gpio.h"
#include "pantalla.h"

int main()
{
	APP_PANTALLA_init();
	HAL_TIMER_SCUGIC_initTimer(1000);
	APP_DATA_SENSORS_setSensorData(1,65.5);
	APP_DATA_SENSORS_setSensorData(2,77.8);
	APP_DATA_SENSORS_setSensorData(3,90);
	while(1){
		APP_TAREALOGICA_ejecutaTarea();
		APP_TAREAENVIO_ejecutaTarea();
	    APP_TAREAPANTALLA_ejecutaTarea();
	}
    return 0;
}
