
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

tipo_pantalla pantalla_flecha1 = {
	.matriz = {

		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,1,1,1,0,0,0},
		{0,1,0,1,0,1,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0,0},
	}
};
tipo_pantalla pantalla_flecha2 = {
	.matriz = {

		{0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,1,1,1,0,0,0},
		{0,1,0,1,0,1,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0,0},
	}
};

tipo_pantalla pantalla_flecha3 = {
	.matriz = {

		{0,0,0,1,0,0,0,0},
		{0,0,1,1,1,0,0,0},
		{0,1,0,1,0,1,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0},

	}
};

tipo_pantalla pantalla_lv1 = {
	.matriz = {

		{0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0},

	}
};

tipo_pantalla pantalla_lv2 = {
	.matriz = {

		{0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,1,0,0,1,0,0},
		{0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0},

	}
};

tipo_pantalla pantalla_lv3 = {
	.matriz = {

		{0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,0},
		{0,0,0,0,0,1,0,0},
		{0,0,0,0,1,1,0,0},
		{0,0,1,0,0,0,1,0},
		{0,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0},

	}
};

tipo_pantalla pantalla_pregunta = {
	.matriz = {

		{0,0,0,1,0,0,0,0},
		{0,0,1,1,1,0,0,0},
		{0,1,0,0,0,1,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0},

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

digitalWrite(led_display->filas[0], 1);
digitalWrite(led_display->filas[1], 1);
digitalWrite(led_display->filas[2], 1);
digitalWrite(led_display->filas[3], 1);
digitalWrite(led_display->filas[4], 1);
digitalWrite(led_display->filas[5], 1);
digitalWrite(led_display->filas[6], 1);

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


}

void ActualizaLedDisplay (TipoLedDisplay *led_display) {

	ApagaFilas(led_display);

	ExcitaColumnas(led_display->p_columna);

	digitalWrite(led_display->filas[0], !led_display->pantalla.matriz[0][led_display->p_columna]);
	digitalWrite(led_display->filas[1], !led_display->pantalla.matriz[1][led_display->p_columna]);
	digitalWrite(led_display->filas[2], !led_display->pantalla.matriz[2][led_display->p_columna]);
	digitalWrite(led_display->filas[3], !led_display->pantalla.matriz[3][led_display->p_columna]);
	digitalWrite(led_display->filas[4], !led_display->pantalla.matriz[4][led_display->p_columna]);
	digitalWrite(led_display->filas[5], !led_display->pantalla.matriz[5][led_display->p_columna]);
	digitalWrite(led_display->filas[6], !led_display->pantalla.matriz[6][led_display->p_columna]);

	tmr_startms((tmr_t*)(led_display->tmr_refresco_display),TIMEOUT_COLUMNA_DISPLAY);


}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumnaDisplay (fsm_t* this) {
	int result = 0;
	TipoLedDisplay *p_ledDisplay;
	p_ledDisplay = (TipoLedDisplay*)(this->user_data);

	piLock(MATRIX_KEY);
	result=(p_ledDisplay->flags & FLAG_TIMEOUT_COLUMNA_DISPLAY );
	piUnlock(MATRIX_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

void ActualizaExcitacionDisplay (fsm_t* this) {
	TipoLedDisplay *p_ledDisplay;
	p_ledDisplay = (TipoLedDisplay*)(this->user_data);

	piLock(MATRIX_KEY);
	p_ledDisplay->flags &=(~FLAG_TIMEOUT_COLUMNA_DISPLAY);
	piUnlock(MATRIX_KEY);

	p_ledDisplay->p_columna++;
	if(p_ledDisplay->p_columna>7){
		p_ledDisplay->p_columna=0;
	}

	ActualizaLedDisplay(p_ledDisplay);
}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void timer_refresco_display_isr (union sigval value) {

	piLock (MATRIX_KEY);
	led_display.flags |= FLAG_TIMEOUT_COLUMNA_DISPLAY;
	piUnlock (MATRIX_KEY);
}
