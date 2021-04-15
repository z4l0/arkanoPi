#include "teclado_TL04.h"




char tecladoTL04[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

// Maquina de estados: lista de transiciones
// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t fsm_trans_excitacion_columnas[] = {
	{ TECLADO_ESPERA_COLUMNA, CompruebaTimeoutColumna, TECLADO_ESPERA_COLUMNA, TecladoExcitaColumna },
	{-1, NULL, -1, NULL },
};

fsm_trans_t fsm_trans_deteccion_pulsaciones[] = {
	{ TECLADO_ESPERA_TECLA, CompruebaTeclaPulsada, TECLADO_ESPERA_TECLA, ProcesaTeclaPulsada},
	{-1, NULL, -1, NULL },
};

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTeclado(TipoTeclado *p_teclado) {

	wiringPiSetupGpio();

	p_teclado->tmr_duracion_columna=0;
	p_teclado->teclaPulsada.col=0;
	p_teclado->teclaPulsada.row=0;
	p_teclado->columna_actual=0;

	int i=0;
	for (i=0; i<4; i++){
	pinMode(p_teclado->columnas[i], OUTPUT);
	pinMode(p_teclado->filas[i], INPUT);
	pullUpDnControl (p_teclado->filas[i], PUD_DOWN );
	// todas las filas inicialmente a pull down

	wiringPiISR(p_teclado->filas[i], INT_EDGE_RISING,p_teclado->rutinas_ISR[i]);

	//declaración de un array de rutinas de interrupción que se ejecutan
	// dependiendo del pin en el que se produce un cambio de nivel
	// detectan flanco de subida


}

}

//------------------------------------------------------
// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA
//------------------------------------------------------

void ActualizaExcitacionTecladoGPIO (int columna) {

	switch(columna){
		case 0:
			digitalWrite(teclado.columnas[3], 0);
			digitalWrite(teclado.columnas[0], 1);
			digitalWrite(teclado.columnas[1], 0);
			digitalWrite(teclado.columnas[2], 0);

			break;

		case 1:
			digitalWrite(teclado.columnas[0], 0);
			digitalWrite(teclado.columnas[1], 1);
			digitalWrite(teclado.columnas[2], 0);
			digitalWrite(teclado.columnas[3], 0);
			break;


		case 2:
			digitalWrite(teclado.columnas[0], 0);
			digitalWrite(teclado.columnas[1], 0);
			digitalWrite(teclado.columnas[2], 1);
			digitalWrite(teclado.columnas[3], 0);
			break;

		case 3:
			digitalWrite(teclado.columnas[0], 0);
			digitalWrite(teclado.columnas[1], 0);
			digitalWrite(teclado.columnas[2], 0);
			digitalWrite(teclado.columnas[3], 1);
			break;

		default:
			digitalWrite(teclado.columnas[0], 0);
			digitalWrite(teclado.columnas[1], 0);
			digitalWrite(teclado.columnas[2], 0);
			digitalWrite(teclado.columnas[3], 0);
		break;

	}

	tmr_startms((tmr_t*)(teclado.tmr_duracion_columna),TIMEOUT_COLUMNA_TECLADO);
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumna (fsm_t* this) {
	int result = 0;
	//TipoTeclado *p_teclado;
	//p_teclado = (TipoTeclado*)(this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	result=(flags & FLAG_TIMEOUT_COLUMNA_TECLADO );
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;


}

int CompruebaTeclaPulsada (fsm_t* this) {
	int result = 0;
	//TipoTeclado *p_teclado;
	//p_teclado = (TipoTeclado*)(this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	result=(flags & FLAG_TECLA_PULSADA);
	piUnlock(SYSTEM_FLAGS_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LAS MAQUINAS DE ESTADOS
//------------------------------------------------------

void TecladoExcitaColumna (fsm_t* this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*)(this->user_data);

	p_teclado->columna_actual++;
	p_teclado->columna_actual=p_teclado->columna_actual%4;



	ActualizaExcitacionTecladoGPIO(p_teclado->columna_actual);
	// Llamada a ActualizaExcitacionTecladoGPIO con columna a activar como argumento
}

void ProcesaTeclaPulsada (fsm_t* this) {
	TipoTeclado *p_teclado;
	p_teclado = (TipoTeclado*)(this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	flags &= (~FLAG_TECLA_PULSADA);
	piUnlock(SYSTEM_FLAGS_KEY);

	switch(p_teclado->teclaPulsada.col){
	case COLUMNA_1:
		if(p_teclado->teclaPulsada.row==FILA_1){
			//printf("\nKeypress 1!!!\n");
			//fflush(stdout);
			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
			}
		else if(p_teclado->teclaPulsada.row==FILA_2){
			//printf("\nKeypress 4!!!\n");
			//fflush(stdout);

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
		}
		else if(p_teclado->teclaPulsada.row==FILA_3){
			//printf("\nKeypress 7!!!\n");
			//fflush(stdout);
			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
		}
		else if(p_teclado->teclaPulsada.row==FILA_4){
			//printf("\nKeypress A!!!\n");
			fflush(stdout);
			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
				}
	break;
	case COLUMNA_2:
		if(p_teclado->teclaPulsada.row==FILA_1){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
				}
		else if(p_teclado->teclaPulsada.row==FILA_2){
			piLock (SYSTEM_FLAGS_KEY);
			flags |= FLAG_MOV_IZQUIERDA;
			piUnlock (SYSTEM_FLAGS_KEY);







						p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
				}
		else if(p_teclado->teclaPulsada.row==FILA_3){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
				}
		else if(p_teclado->teclaPulsada.row==FILA_4){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
				}
		break;

	case COLUMNA_3:
		if(p_teclado->teclaPulsada.row==FILA_1){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
						}
		else if(p_teclado->teclaPulsada.row==FILA_2){
			piLock (SYSTEM_FLAGS_KEY);
			flags |= FLAG_MOV_DERECHA;
			piUnlock (SYSTEM_FLAGS_KEY);
			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
						}
		else if(p_teclado->teclaPulsada.row==FILA_3){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
						}
		else if(p_teclado->teclaPulsada.row==FILA_4){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
						}
		break;
	case COLUMNA_4:
		if(p_teclado->teclaPulsada.row==FILA_1){
			piLock (SYSTEM_FLAGS_KEY);
			flags |= FLAG_BOTON ;
			piUnlock (SYSTEM_FLAGS_KEY);
			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
								}
		else if(p_teclado->teclaPulsada.row==FILA_2){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
								}
		else if(p_teclado->teclaPulsada.row==FILA_3){

			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
								}
		else if(p_teclado->teclaPulsada.row==FILA_4){
			exit(0);
			p_teclado->teclaPulsada.row= -1;
			p_teclado->teclaPulsada.col = -1;
								}
		break;

	default:
		break;

	}

}


//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void teclado_fila_1_isr (void) {

	if(millis()< teclado.debounceTime[0]){
		teclado.debounceTime[0]= millis () + DEBOUNCE_TIME;
		return;
	}
	piLock(SYSTEM_FLAGS_KEY);
	teclado.teclaPulsada.row=FILA_1;
	teclado.teclaPulsada.col=teclado.columna_actual;

	flags |= FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);

	teclado.debounceTime[0]=millis()+ DEBOUNCE_TIME;
}

void teclado_fila_2_isr (void) {

	if(millis()< teclado.debounceTime[1]){
			teclado.debounceTime[1]=millis () + DEBOUNCE_TIME;
			return;
	}
	piLock(SYSTEM_FLAGS_KEY);
	teclado.teclaPulsada.row=FILA_2;
	teclado.teclaPulsada.col=teclado.columna_actual;

	flags |= FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);

	teclado.debounceTime[1]=millis()+ DEBOUNCE_TIME;
}

void teclado_fila_3_isr (void) {

	if(millis()< teclado.debounceTime[2]){
				teclado.debounceTime[2]=millis () + DEBOUNCE_TIME;
				return;
	}
	piLock(SYSTEM_FLAGS_KEY);
	teclado.teclaPulsada.row=FILA_3;
	teclado.teclaPulsada.col=teclado.columna_actual;

	flags |= FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);

	teclado.debounceTime[2]=millis()+ DEBOUNCE_TIME;
}

void teclado_fila_4_isr (void) {

	if(millis()< teclado.debounceTime[3]){
					teclado.debounceTime[3]=millis () + DEBOUNCE_TIME;
					return;
	}
	piLock(SYSTEM_FLAGS_KEY);
	teclado.teclaPulsada.row=FILA_4;
	teclado.teclaPulsada.col=teclado.columna_actual;

	flags |= FLAG_TECLA_PULSADA;
	piUnlock(SYSTEM_FLAGS_KEY);

	teclado.debounceTime[3]=millis()+ DEBOUNCE_TIME;
}

void timer_duracion_columna_isr (union sigval value) {

	piLock (SYSTEM_FLAGS_KEY);
	flags |= FLAG_TIMEOUT_COLUMNA_TECLADO ;
	piUnlock (SYSTEM_FLAGS_KEY);

}



