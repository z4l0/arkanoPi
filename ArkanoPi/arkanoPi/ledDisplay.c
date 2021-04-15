
#include "ledDisplay.h"

tipo_pantalla pantalla_inicial = {
	.matriz = {
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,1,0},
	{0,0,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0},
	}
};

tipo_pantalla pantalla_final = {
	.matriz = {
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,0,0},
	{0,1,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0},
	}
};

// Maquina de estados: lista de transiciones
// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t fsm_trans_excitacion_display[] = {
	{ DISPLAY_ESPERA_COLUMNA, CompruebaTimeoutColumnaDisplay, DISPLAY_ESPERA_COLUMNA, ActualizaExcitacionDisplay },
	{-1, NULL, -1, NULL },
};

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaLedDisplay (TipoLedDisplay *led_display) {

		wiringPiSetupGpio();

		led_display->p_columna=0;

		for (int i=0; i<7; i++){
		pinMode(led_display->filas[i],OUTPUT);
		}
		for(int j=0; j<3; j++){
		pinMode(led_display->pines_control_columnas[j],OUTPUT);
		}

}

//------------------------------------------------------
// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA
//------------------------------------------------------

void ApagaFilas (TipoLedDisplay *led_display){

	digitalWrite(led_display->filas[0], !led_display->pantalla.matriz[led_display->p_columna][0]);
	digitalWrite(led_display->filas[1], !led_display->pantalla.matriz[led_display->p_columna][1]);
	digitalWrite(led_display->filas[2], !led_display->pantalla.matriz[led_display->p_columna][2]);
	digitalWrite(led_display->filas[3], !led_display->pantalla.matriz[led_display->p_columna][3]);
	digitalWrite(led_display->filas[4], !led_display->pantalla.matriz[led_display->p_columna][4]);
	digitalWrite(led_display->filas[5], !led_display->pantalla.matriz[led_display->p_columna][5]);
	digitalWrite(led_display->filas[6], !led_display->pantalla.matriz[led_display->p_columna][6]);

}

void ExcitaColumnas(int columna) {

	switch(columna) {
			case 0:
				digitalWrite(led_display.pines_control_columnas[0], 0);
				digitalWrite(led_display.pines_control_columnas[1], 0);
				digitalWrite(led_display.pines_control_columnas[2], 0);


				break;

			case 1:
				digitalWrite(led_display.pines_control_columnas[0], 1);
				digitalWrite(led_display.pines_control_columnas[1], 0);
				digitalWrite(led_display.pines_control_columnas[2], 0);

				break;


			case 2:
				digitalWrite(led_display.pines_control_columnas[0], 0);
				digitalWrite(led_display.pines_control_columnas[1], 1);
				digitalWrite(led_display.pines_control_columnas[2], 0);

				break;

			case 3:
				digitalWrite(led_display.pines_control_columnas[0], 1);
				digitalWrite(led_display.pines_control_columnas[1], 1);
				digitalWrite(led_display.pines_control_columnas[2], 0);

				break;

			case 4:
				digitalWrite(led_display.pines_control_columnas[0], 0);
				digitalWrite(led_display.pines_control_columnas[1], 0);
				digitalWrite(led_display.pines_control_columnas[2], 1);

				break;

			case 5:
				digitalWrite(led_display.pines_control_columnas[0], 1);
				digitalWrite(led_display.pines_control_columnas[1], 0);
				digitalWrite(led_display.pines_control_columnas[2], 1);

				break;

			case 6:
				digitalWrite(led_display.pines_control_columnas[0], 0);
				digitalWrite(led_display.pines_control_columnas[1], 1);
				digitalWrite(led_display.pines_control_columnas[2], 1);

				break;

			case 7:
				digitalWrite(led_display.pines_control_columnas[0], 1);
				digitalWrite(led_display.pines_control_columnas[1], 1);
				digitalWrite(led_display.pines_control_columnas[2], 1);

				break;

			default:

				break;

		}

		tmr_startms((tmr_t*)(led_display.tmr_refresco_display),TIMEOUT_COLUMNA_DISPLAY);

}

void ActualizaLedDisplay (TipoLedDisplay *led_display) {



}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumnaDisplay (fsm_t* this) {
	int result = 0;
	//TipoLedDisplay *p_ledDisplay;
	//p_ledDisplay = (TipoLedDisplay*)(this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	result=(flags & FLAG_TIMEOUT_COLUMNA_DISPLAY );
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

void ActualizaExcitacionDisplay (fsm_t* this) {
	TipoLedDisplay *p_ledDisplay;
	p_ledDisplay = (TipoLedDisplay*)(this->user_data);

	p_ledDisplay->p_columna++;
	if(p_ledDisplay->p_columna>9){
		p_ledDisplay->p_columna=0;
	}

	ExcitaColumnas(p_ledDisplay->p_columna);
}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void timer_refresco_display_isr (union sigval value) {
	piLock (SYSTEM_FLAGS_KEY);
	flags |= FLAG_TIMEOUT_COLUMNA_DISPLAY;
	piUnlock (SYSTEM_FLAGS_KEY);
}

