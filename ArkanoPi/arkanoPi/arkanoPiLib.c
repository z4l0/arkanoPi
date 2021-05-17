#include "arkanoPiLib.h"

int level=1;
int pausa =0;
int flecha=0;
//variable para aumentar la velociad de desplazamiento de la pelota (ha dejado de ser una cte.)


//Pantallas básicas de transciones
tipo_pantalla pantalla_inicial = {
	.matriz = {
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0},
	}
};

tipo_pantalla pantalla_final = {
	.matriz = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,1,0,0,1,0,0},
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


		{0,0,1,1,1,0,0,0},
		{0,1,0,0,0,1,0,0},
		{0,1,0,0,0,1,0,0},
		{0,0,0,1,1,0,0,0},
		{0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0},

	}
};

//Matrices correspondientes a cada nivel
int ladrillos_basico[NUM_FILAS_DISPLAY][NUM_COLUMNAS_DISPLAY] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

int ladrillos_level2[NUM_FILAS_DISPLAY][NUM_COLUMNAS_DISPLAY] = {
		{2,0,2,0,2,0,2,0},
		{0,2,0,2,0,2,0,2},
		{2,0,2,0,2,0,2,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
};

int ladrillos_level3[NUM_FILAS_DISPLAY][NUM_COLUMNAS_DISPLAY] = {
		{3,3,3,3,3,3,3,3},
		{0,3,0,3,3,0,3,0},
		{0,0,3,3,3,3,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
};

//------------------------------------------------------
// FUNCIONES DE VISUALIZACION (ACTUALIZACION DEL OBJETO PANTALLA QUE LUEGO USARA EL DISPLAY)
//------------------------------------------------------

void PintaMensajeInicialPantalla (tipo_pantalla *p_pantalla, tipo_pantalla *p_pantalla_inicial) {
	int i, j = 0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = p_pantalla_inicial->matriz[i][j];
		}
	}

	return;
}

void PintaMensajeFinalPantalla (tipo_pantalla *p_pantalla) {
	int i, j = 0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = pantalla_final.matriz[i][j];
		}
	}

	return;
}

void PintaPregunta (tipo_pantalla *p_pantalla) {
	int i, j = 0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = pantalla_pregunta.matriz[i][j];
		}
	}

	return;
}

void PintaFlechaPantalla (tipo_pantalla *p_pantalla) {

	tipo_pantalla *p_pantalla_flecha;

	switch (flecha)
	{
			case 1:
				p_pantalla_flecha = &pantalla_flecha1;

				break;
			case 2:
				p_pantalla_flecha = &pantalla_flecha2;


				break;
			case 3:
				p_pantalla_flecha = &pantalla_flecha3;


				break;
			case 4:
				p_pantalla_flecha = &pantalla_flecha1;


				break;
			case 5:
				p_pantalla_flecha = &pantalla_flecha2;


				break;
			case 6:
				p_pantalla_flecha = &pantalla_flecha3;


				break;

			case 7:
				flecha = 0; //reinicio para la próxima

				piLock(SYSTEM_FLAGS_KEY);
				flags |= FLAG_CAMBIO_NIVEL;
				piUnlock(SYSTEM_FLAGS_KEY);

				break;



			default:
				break;

	}

	for(int i=0;i<NUM_FILAS_DISPLAY;i++){
		for(int j=0;j<NUM_COLUMNAS_DISPLAY;j++){

			p_pantalla->matriz[i][j] = p_pantalla_flecha->matriz[i][j];
		}
	}


	return;
}

void PintaNivelPantalla (tipo_pantalla *p_pantalla) {
	int i, j = 0;
	tipo_pantalla *p_pantalla_nivel;

	switch (level)
	{
		case 1:
		p_pantalla_nivel = &pantalla_lv1;
		break;

		case 2:
		p_pantalla_nivel = &pantalla_lv2;
		break;

		case 3:
		p_pantalla_nivel = &pantalla_lv3;
		break;

		default:
			break;

	}

	for(i=0;i<NUM_FILAS_DISPLAY;i++)
	{
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++)
		{
			p_pantalla->matriz[i][j] = p_pantalla_nivel->matriz[i][j];
		}
	}

	return;
}
/*
void PintaPantallaPorTerminal (tipo_pantalla *p_pantalla) {
#ifdef SIN_PSEUDOWIRINGPI
	int i=0, j=0;

	printf("\n[PANTALLA]\n");
	fflush(stdout);
	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			printf("%d", p_pantalla->matriz[i][j]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}
	fflush(stdout);
#endif
}
*/

void ReseteaPantalla (tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = 0;
		}
	}
}


//------------------------------------------------------
// FUNCIONES DE INICIALIZACION / RESET
//------------------------------------------------------

void InicializaLadrillos(tipo_pantalla *p_ladrillos) {
	int i=0, j=0;

		switch(level){
		case 1:
		for(i=0;i<NUM_FILAS_DISPLAY;i++) {
			for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
				p_ladrillos->matriz[i][j] = ladrillos_basico[i][j];}}
		break;
		case 2:
			for(i=0;i<NUM_FILAS_DISPLAY;i++) {
					for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
						p_ladrillos->matriz[i][j] = ladrillos_level2[i][j];}}
			break;
		case 3:
				for(i=0;i<NUM_FILAS_DISPLAY;i++) {
						for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
							p_ladrillos->matriz[i][j] = ladrillos_level3[i][j];}}
				break;
	}
}

void InicializaPelota(tipo_pelota *p_pelota) {
	//Aleatorizamos la posicion inicial de la pelota
	p_pelota->x = rand() % NUM_COLUMNAS_DISPLAY;
	p_pelota->y = 2 + rand() % (NUM_FILAS_DISPLAY-2); // 2 evita que aparezca encima de ladrillos y para que no empiece demasiado pegada al suelo de la pantalla

	// Pelota inicialmente en el centro de la pantalla
	//p_pelota->x = NUM_COLUMNAS_DISPLAY/2 - 1;
	//p_pelota->y = NUM_FILAS_DISPLAY/2 -1 ;

	InicializaPosiblesTrayectorias(p_pelota);

	// Trayectoria inicial
	//p_pelota->trayectoria.xv = 0;
	//p_pelota->trayectoria.yv = 1;
	CambiarDireccionPelota(p_pelota, rand() % p_pelota->num_posibles_trayectorias);
}

void InicializaPala(tipo_pala *p_pala) {
	// Pala inicialmente en el centro de la pantalla
	p_pala->x = NUM_COLUMNAS_DISPLAY/2 - p_pala->ancho/2;
	p_pala->y = NUM_FILAS_DISPLAY - 1;
	p_pala->ancho = NUM_COLUMNAS_PALA;
	p_pala->alto = NUM_FILAS_PALA;
}

void InicializaPosiblesTrayectorias(tipo_pelota *p_pelota) {
	p_pelota->num_posibles_trayectorias = 0;
	p_pelota->posibles_trayectorias[ARRIBA_IZQUIERDA].xv = -1;
	p_pelota->posibles_trayectorias[ARRIBA_IZQUIERDA].yv = -1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ARRIBA].xv = 0;
	p_pelota->posibles_trayectorias[ARRIBA].yv = -1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ARRIBA_DERECHA].xv = 1;
	p_pelota->posibles_trayectorias[ARRIBA_DERECHA].yv = -1;
	p_pelota->num_posibles_trayectorias++;

	p_pelota->posibles_trayectorias[ABAJO_DERECHA].xv = 1;
	p_pelota->posibles_trayectorias[ABAJO_DERECHA].yv = 1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ABAJO].xv = 0;
	p_pelota->posibles_trayectorias[ABAJO].yv = 1;
	p_pelota->num_posibles_trayectorias++;
	p_pelota->posibles_trayectorias[ABAJO_IZQUIERDA].xv = -1;
	p_pelota->posibles_trayectorias[ABAJO_IZQUIERDA].yv = 1;
	p_pelota->num_posibles_trayectorias++;

	//p_pelota->posibles_trayectorias[IZQUIERDA].xv = -1;
	//p_pelota->posibles_trayectorias[IZQUIERDA].yv = 0;
	//p_pelota->num_posibles_trayectorias++;
	//p_pelota->posibles_trayectorias[DERECHA].xv = 1;
	//p_pelota->posibles_trayectorias[DERECHA].yv = 0;
	//p_pelota->num_posibles_trayectorias++;
}

void PintaLadrillos(tipo_pantalla *p_ladrillos, tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			p_pantalla->matriz[i][j] = p_ladrillos->matriz[i][j];
		}
    }
}

void PintaPala(tipo_pala *p_pala, tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	for(i=0;i<NUM_FILAS_PALA;i++) {
		for(j=0;j<NUM_COLUMNAS_PALA;j++) {
			if (( (p_pala->y+i >= 0) && (p_pala->y+i < NUM_FILAS_DISPLAY) ) &&
				( (p_pala->x+j >= 0) && (p_pala->x+j < NUM_COLUMNAS_DISPLAY) ))
				p_pantalla->matriz[p_pala->y+i][p_pala->x+j] = 1;
		}
	}
}

void PintaPelota(tipo_pelota *p_pelota, tipo_pantalla *p_pantalla) {
	//mientras se encuentre dentro de los limites de la pantalla
	if( (p_pelota->x >= 0) && (p_pelota->x < NUM_COLUMNAS_DISPLAY) ) {
		if( (p_pelota->y >= 0) && (p_pelota->y < NUM_FILAS_DISPLAY) ) {
			p_pantalla->matriz[p_pelota->y][p_pelota->x] = 1;
		}
		else {
			printf("\n\nPROBLEMAS!!!! posicion y=%d de la pelota INVALIDA!!!\n\n", p_pelota->y);
			fflush(stdout);
		}
	}
	else {
		printf("\n\nPROBLEMAS!!!! posicion x=%d de la pelota INVALIDA!!!\n\n", p_pelota->x);
		fflush(stdout);
	}
}

void ActualizaPantalla(tipo_arkanoPi* p_arkanoPi) {

    // Borro toda la pantalla
	ReseteaPantalla((tipo_pantalla*)(p_arkanoPi->p_pantalla));

    // Pinta los ladrillos
	PintaLadrillos(
		(tipo_pantalla*)(&(p_arkanoPi->ladrillos)),
		(tipo_pantalla*)(p_arkanoPi->p_pantalla));

    // Pinta la pala
	PintaPala(
		(tipo_pala*)(&(p_arkanoPi->pala)),
		(tipo_pantalla*)(p_arkanoPi->p_pantalla));

	// Pinta la pelota
	PintaPelota(
		(tipo_pelota*)(&(p_arkanoPi->pelota)),
		(tipo_pantalla*)(p_arkanoPi->p_pantalla));
}

void InicializaArkanoPi(tipo_arkanoPi *p_arkanoPi) {
	ResetArkanoPi(p_arkanoPi);
	ActualizaPantalla(p_arkanoPi);
}

void ResetArkanoPi(tipo_arkanoPi *p_arkanoPi) {
	ReseteaPantalla((tipo_pantalla*)(p_arkanoPi->p_pantalla));
	InicializaLadrillos((tipo_pantalla*)(&(p_arkanoPi->ladrillos)));
	InicializaPelota((tipo_pelota*)(&(p_arkanoPi->pelota)));
	InicializaPala((tipo_pala*)(&(p_arkanoPi->pala)));
}

void CambiarDireccionPelota(tipo_pelota *p_pelota, enum t_direccion direccion) {
	if((direccion < 0)||(direccion > p_pelota->num_posibles_trayectorias)) {
		printf("[ERROR!!!!][direccion NO VALIDA!!!!][%d]", direccion);
		return;
	}
	else {
		p_pelota->trayectoria.xv = p_pelota->posibles_trayectorias[direccion].xv;
		p_pelota->trayectoria.yv = p_pelota->posibles_trayectorias[direccion].yv;
	}
}

void ActualizaPosicionPala(tipo_pala *p_pala, enum t_direccion direccion) {
	switch (direccion) {
		case DERECHA:
			// Dejamos que la pala rebase parcialmente el límite del area de juego
			if( p_pala->x + 1 + p_pala->ancho <= NUM_COLUMNAS_DISPLAY + 2 )
				p_pala->x = p_pala->x + 1;
			break;
		case IZQUIERDA:
			// Dejamos que la pala rebase parcialmente el límite del area de juego
			if( p_pala->x - 1 >= -2)
					p_pala->x = p_pala->x - 1;
			break;
		default:
			printf("[ERROR!!!!][direccion NO VALIDA!!!!][%d]", direccion);
			break;
	}
}

void ActualizaPosicionPelota (tipo_pelota *p_pelota) {
	p_pelota->x += p_pelota->trayectoria.xv;
	p_pelota->y += p_pelota->trayectoria.yv;
}

int CompruebaReboteLadrillo (tipo_arkanoPi *p_arkanoPi) {
	int p_posible_ladrillo_x = 0;
	int p_posible_ladrillo_y = 0;

	p_posible_ladrillo_x = p_arkanoPi->pelota.x + p_arkanoPi->pelota.trayectoria.xv;

	if ( ( p_posible_ladrillo_x < 0) || ( p_posible_ladrillo_x >= NUM_COLUMNAS_DISPLAY ) ) {
		printf("\n\nERROR GRAVE!!! p_posible_ladrillo_x = %d!!!\n\n", p_posible_ladrillo_x);
		fflush(stdout);
		exit(-1);
	}

	p_posible_ladrillo_y = p_arkanoPi->pelota.y + p_arkanoPi->pelota.trayectoria.yv;

	if ( ( p_posible_ladrillo_y < 0) || ( p_posible_ladrillo_y >= NUM_FILAS_DISPLAY ) ) {
		printf("\n\nERROR GRAVE!!! p_posible_ladrillo_y = %d!!!\n\n", p_posible_ladrillo_y);
		fflush(stdout);
	}

	if(p_arkanoPi->ladrillos.matriz[p_posible_ladrillo_y][p_posible_ladrillo_x] > 0 ) {
		// La pelota ha entrado en el area de ladrillos
		// y descontamos el numero de golpes que resta para destruir el ladrillo
		p_arkanoPi->ladrillos.matriz[p_posible_ladrillo_y][p_posible_ladrillo_x] = p_arkanoPi->ladrillos.matriz[p_posible_ladrillo_y][p_posible_ladrillo_x] - 1;

		return 1;
	}
	return 0;
}

int CompruebaReboteParedesVerticales (tipo_arkanoPi arkanoPi) {
	// Comprobamos si la nueva posicion de la pelota excede los limites de la pantalla
	if((arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv >= NUM_COLUMNAS_DISPLAY) ||
		(arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv < 0) ) {
		// La pelota rebota contra la pared derecha o izquierda
		return 1;
	}
	return 0;
}

int CompruebaReboteTecho (tipo_arkanoPi arkanoPi) {
	// Comprobamos si la nueva posicion de la pelota excede los limites de la pantalla
	if(arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv < 0) {
		// La pelota rebota contra la pared derecha o izquierda
		return 1;
	}
	return 0;
}

int CompruebaRebotePala (tipo_arkanoPi arkanoPi) {
	if(arkanoPi.pelota.trayectoria.yv > 0) { // Esta condicion solo tiene sentido si la pelota va hacia abajo en la pantalla
		if ((arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv >= arkanoPi.pala.x ) &&
			(arkanoPi.pelota.x + arkanoPi.pelota.trayectoria.xv < arkanoPi.pala.x + NUM_COLUMNAS_PALA)) {
				if ((arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv >= arkanoPi.pala.y) &&
					(arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv < arkanoPi.pala.y + NUM_FILAS_PALA)) {
					return 1;
				}
		}
	}
	return 0;
}

int CompruebaFallo (tipo_arkanoPi arkanoPi) {
	// Comprobamos si no hemos conseguido devolver la pelota
	if(arkanoPi.pelota.y + arkanoPi.pelota.trayectoria.yv >= NUM_FILAS_DISPLAY) {
		// Hemos fallado
		return 1;
	}
	return 0;
}

int CalculaLadrillosRestantes(tipo_pantalla *p_ladrillos) {
	int i=0, j=0;
	int numLadrillosRestantes;

	numLadrillosRestantes = 0;

	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			if(p_ladrillos->matriz[i][j] != 0) {
				numLadrillosRestantes++;
			}
		}
	}

	return numLadrillosRestantes;
}

//------------------------------------------------------
// FUNCIONES DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaBotonPulsado (fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_BOTON);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;

}

int CompruebaPausa (fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_PAUSA);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;

}

int CompruebaMovimientoIzquierda(fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_MOV_IZQUIERDA);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;
}

int CompruebaMovimientoDerecha(fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_MOV_DERECHA);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;
}

int CompruebaTimeoutActualizacionJuego (fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_TIMER_JUEGO);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;
}

int CompruebaFinalJuego(fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_FIN_JUEGO);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;

}

int CompruebaFinalNivel(fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_FIN_NIVEL);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;

}

int CompruebaCambioNivel(fsm_t* this) {

	int result = 0;
	piLock (SYSTEM_FLAGS_KEY);
	result = (flags & FLAG_CAMBIO_NIVEL);
	piUnlock (SYSTEM_FLAGS_KEY);
	return result;

}


//------------------------------------------------------
// FUNCIONES DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

// void InicializaJuego (void): funcion encargada de llevar a cabo
// la oportuna inicialización de toda variable o estructura de datos
// que resulte necesaria para el desarrollo del juego.

void InicializaJuego(fsm_t* this) {
	tipo_arkanoPi *p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);


	piLock (SYSTEM_FLAGS_KEY);
	flags = 0;
	piUnlock (SYSTEM_FLAGS_KEY);

	piLock (MATRIX_KEY);
	InicializaArkanoPi(p_arkanoPi);
	piUnlock (MATRIX_KEY);
/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);
*/

	int pid;
	switch(level){
	case 1:

		//Thread que actua en segundo plano para reproducir música mientras jugamos ArkanoPi
				system("killall omxplayer.bin");

				pid=fork(); //crea un clon identico (hijo) del proceso que se está ejecutando (padre) y guarda su identificador

				if(pid==0) //solo el proceso hijo devolvera el valor 0, y se dedicara a reproducir la musica

				{
					//reproducimos el archivo de audio mediante OMXplayer (nativo de la raspy) a través del HDMI
					execlp("/usr/bin/omxplayer", "omxplayer", "--loop", "--vol", "-2500", "/home/pi/Downloads/lvl1.mp3", NULL);

					_exit(0); //Sale del proceso hijo sin detener la ejecucion del juego (proceso padre)
				}
				break;
	case 2:



				system("killall omxplayer.bin");

				pid=fork();
				if(pid==0)
				{
				execlp("/usr/bin/omxplayer", "omxplayer", "--loop", "--vol", "-1500", "/home/pi/Downloads/lvl2.mp3", NULL);
				_exit(0);
				}
				break;

	case 3:


				system("killall omxplayer.bin");

				pid=fork();
				if(pid==0)
				{
				execlp("/usr/bin/omxplayer", "omxplayer", "--loop", "--vol", "-2500", "/home/pi/Downloads/lvl3.mp3", NULL);
				_exit(0);
				}
				break;

	default:
				break;

	}


	tmr_startms(p_arkanoPi->tmr_actualizacion_juego,TIMEOUT_ACTUALIZA_JUEGO);



	//piLock(STD_IO_BUFFER_KEY);
	//printf("Pulse 's' para comenzar y pulse 'q' para salir...");
	//piUnlock(STD_IO_BUFFER_KEY);


}

// void MuevePalaIzquierda (void): funcion encargada de ejecutar
// el movimiento hacia la izquierda contemplado para la pala.
// Debe garantizar la viabilidad del mismo mediante la comprobación
// de que la nueva posición correspondiente a la pala no suponga
// que ésta rebase o exceda los límites definidos para el área de juego
// (i.e. al menos uno de los leds que componen la raqueta debe permanecer
// visible durante todo el transcurso de la partida).

void MuevePalaIzquierda (fsm_t* this) {

	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);



	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_MOV_IZQUIERDA);
	piUnlock(SYSTEM_FLAGS_KEY);

	ActualizaPosicionPala(&(p_arkanoPi->pala),IZQUIERDA);


	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi);
	piUnlock(MATRIX_KEY);

/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);

*/


}
// void MuevePalaDerecha (void): función similar a la anterior
// encargada del movimiento hacia la derecha.

void MuevePalaDerecha (fsm_t* this) {

	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_MOV_DERECHA);
	piUnlock(SYSTEM_FLAGS_KEY);

	ActualizaPosicionPala(&(p_arkanoPi->pala),DERECHA);


	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi);
	piUnlock(MATRIX_KEY);

/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);
*/

}

// void ActualizarJuego (void): función encargada de actualizar la
// posición de la pelota conforme a la trayectoria definida para ésta.
// Para ello deberá identificar los posibles rebotes de la pelota para,
// en ese caso, modificar su correspondiente trayectoria (los rebotes
// detectados contra alguno de los ladrillos implicarán adicionalmente
// la eliminación del ladrillo). Del mismo modo, deberá también
// identificar las situaciones en las que se dé por finalizada la partida:
// bien porque el jugador no consiga devolver la pelota, y por tanto ésta
// rebase el límite inferior del área de juego, bien porque se agoten
// los ladrillos visibles en el área de juego.

void ActualizarJuego (fsm_t* this) {
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	int timeout = TIMEOUT_ACTUALIZA_JUEGO;

	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_TIMER_JUEGO);
	piUnlock(SYSTEM_FLAGS_KEY);

	/*el TIMEOUT_ACTUALIZA JUEGO se inicia a 1200 ms, y a medida que se van eliminando ladrillos se llega a un
				valor mínimo de 450 ms.*/
	if(CalculaLadrillosRestantes(p_arkanoPi->p_pantalla) < 12){
				timeout = TIMEOUT_ACTUALIZA_JUEGO - 200;
	}
		else if(CalculaLadrillosRestantes(p_arkanoPi->p_pantalla) < 7){
				timeout = TIMEOUT_ACTUALIZA_JUEGO - 250;
		}
				else if(CalculaLadrillosRestantes(p_arkanoPi->p_pantalla) < 4){
				timeout = TIMEOUT_ACTUALIZA_JUEGO - 350;
				}

	if(CompruebaRebotePala(*p_arkanoPi)){
		switch(p_arkanoPi->pelota.x + p_arkanoPi->pelota.trayectoria.xv - p_arkanoPi->pala.x){
				case 0:
					CambiarDireccionPelota((&p_arkanoPi->pelota),ARRIBA_IZQUIERDA);
					break;
				case 1:
					CambiarDireccionPelota((&p_arkanoPi->pelota),ARRIBA);
					break;
				case 2:
					CambiarDireccionPelota((&p_arkanoPi->pelota),ARRIBA_DERECHA);
					break;
		}
	}

	if(CompruebaReboteParedesVerticales(*p_arkanoPi)){
			p_arkanoPi->pelota.trayectoria.xv= -(p_arkanoPi->pelota.trayectoria.xv);
		}
		if(CompruebaReboteTecho(*p_arkanoPi)){
			p_arkanoPi->pelota.trayectoria.yv = -(p_arkanoPi->pelota.trayectoria.yv);
		}
		if(CompruebaFallo(*p_arkanoPi)){
			piLock(SYSTEM_FLAGS_KEY);
			flags |= FLAG_FIN_JUEGO;
			piUnlock(SYSTEM_FLAGS_KEY);
			return;
		}

	if (CompruebaReboteLadrillo(p_arkanoPi)) {


		p_arkanoPi->pelota.trayectoria.yv = -(p_arkanoPi->pelota.trayectoria.yv);

		if(CalculaLadrillosRestantes(p_arkanoPi->p_pantalla)<= 0) {
			if(level<3){

				piLock (SYSTEM_FLAGS_KEY);
				flags |= FLAG_FIN_NIVEL;
				piUnlock (SYSTEM_FLAGS_KEY);
				return;

				}
				else{

				piLock (SYSTEM_FLAGS_KEY);
				flags |= FLAG_FIN_JUEGO;
				piUnlock (SYSTEM_FLAGS_KEY);
				return;

									}
		}else if(CompruebaReboteTecho (*p_arkanoPi)){
			p_arkanoPi->pelota.trayectoria.xv = -(p_arkanoPi->pelota.trayectoria.xv);
			p_arkanoPi->pelota.trayectoria.yv = -(p_arkanoPi->pelota.trayectoria.yv);
	}
	}

	ActualizaPosicionPelota(&p_arkanoPi->pelota);

	piLock(MATRIX_KEY);
	ActualizaPantalla(p_arkanoPi);
	piUnlock(MATRIX_KEY);

/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);
*/

	tmr_startms(p_arkanoPi->tmr_actualizacion_juego,timeout);

}

// void FinalJuego (void): función encargada de mostrar en la ventana de
// terminal los mensajes necesarios para informar acerca del resultado del juego.

void FinalJuego (fsm_t* this) {
	tipo_arkanoPi *p_arkanoPi;
		p_arkanoPi = (tipo_arkanoPi*)(this->user_data);


		piLock(SYSTEM_FLAGS_KEY);
		flags &=(~FLAG_TIMER_JUEGO);
		piUnlock(SYSTEM_FLAGS_KEY);

		piLock(MATRIX_KEY);
		PintaMensajeFinalPantalla(p_arkanoPi->p_pantalla);
		piUnlock(MATRIX_KEY);

/*
		piLock(STD_IO_BUFFER_KEY);
		PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
		piUnlock(STD_IO_BUFFER_KEY);
*/

		system("killall omxplayer.bin");


		tmr_startms(p_arkanoPi->tmr_actualizacion_juego,TIMEOUT_ACTUALIZA_JUEGO*4);

}

//void ReseteaJuego (void): función encargada de llevar a cabo la
// reinicialización de cuantas variables o estructuras resulten
// necesarias para dar comienzo a una nueva partida.

void ReseteaJuego (fsm_t* this) {
	tipo_arkanoPi *p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	piLock (SYSTEM_FLAGS_KEY);
	flags = 0;
	piUnlock (SYSTEM_FLAGS_KEY);

	piLock (MATRIX_KEY);
	InicializaArkanoPi(p_arkanoPi);
	piUnlock (MATRIX_KEY);
/*
	piLock (STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock (STD_IO_BUFFER_KEY);
*/

}

void PantallaEspera (fsm_t* this) {
	tipo_arkanoPi *p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);


	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_TIMER_JUEGO);
	piUnlock(SYSTEM_FLAGS_KEY);

	piLock(MATRIX_KEY);
	PintaPregunta(p_arkanoPi->p_pantalla);
	piUnlock(MATRIX_KEY);

/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);
*/

}


void CambioNivel (fsm_t* this) {

	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	if(flecha == 0){
		system("killall omxplayer.bin");
		int pid;
				pid=fork();
					if(pid==0)
						{
						execlp("/usr/bin/omxplayer", "omxplayer", "--loop", "--vol", "-1500", "/home/pi/Downloads/level_up.wav", NULL);
						_exit(0);
						}
	}



	//quitamos la flag para usarla en el siguente nivel
	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_FIN_NIVEL);
	piUnlock(SYSTEM_FLAGS_KEY);

	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_TIMER_JUEGO);
	piUnlock(SYSTEM_FLAGS_KEY);

	flecha++;

	piLock(MATRIX_KEY);
	PintaFlechaPantalla(p_arkanoPi->p_pantalla);
	piUnlock(MATRIX_KEY);

/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);
*/



	tmr_startms(p_arkanoPi->tmr_actualizacion_juego,TIMEOUT_ACTUALIZA_JUEGO/2);

}

void ActualizaNumeroNivel (fsm_t* this) {

	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);

	system("killall omxplayer.bin");

	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_TIMER_JUEGO);
	piUnlock(SYSTEM_FLAGS_KEY);

	// desactiva el flag
	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_CAMBIO_NIVEL);
	piUnlock(SYSTEM_FLAGS_KEY);

	level++;

	piLock(MATRIX_KEY);
	PintaNivelPantalla(p_arkanoPi->p_pantalla);
	piUnlock(MATRIX_KEY);

/*
	piLock(STD_IO_BUFFER_KEY);
	PintaPantallaPorTerminal(p_arkanoPi->p_pantalla);
	piUnlock(STD_IO_BUFFER_KEY);
*/

	tmr_startms(p_arkanoPi->tmr_actualizacion_juego,TIMEOUT_ACTUALIZA_JUEGO);

}

void ActivaPausa(fsm_t* this){
	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);
	pausa = 1;
	// pausar omxplayer
	system("dbuscontrol.sh pause");
	// desactiva el flag
	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_PAUSA);
	piUnlock(SYSTEM_FLAGS_KEY);

}

void DesactivaPausa(fsm_t* this){

	tipo_arkanoPi* p_arkanoPi;
	p_arkanoPi = (tipo_arkanoPi*)(this->user_data);
	pausa = 0;
	//resumir omxplayer
	system("dbuscontrol.sh pause");
	// desactiva el flag
	piLock(SYSTEM_FLAGS_KEY);
	flags &=(~FLAG_PAUSA);
	piUnlock(SYSTEM_FLAGS_KEY);

	ActualizarJuego(this);

}
//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void tmr_actualizacion_juego_isr(union sigval value) {
	piLock (SYSTEM_FLAGS_KEY);
	flags |= FLAG_TIMER_JUEGO ;
	piUnlock (SYSTEM_FLAGS_KEY);
}
