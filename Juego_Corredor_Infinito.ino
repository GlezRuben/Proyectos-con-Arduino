// Link a mi canal de Youtube: https://www.youtube.com/channel/UCNMHoARQqaHZdmZcxNF6XKw

#include <LiquidCrystal.h>

#define PIN_BOTON 2
 
#define CORRER_1 1
#define CORRER_2 2
#define SALTAR 3
#define SALTO_ARRIBA '.'      
#define SALTO_ABAJO 4
#define BLOQUE_VACIO ' '     
#define BLOQUE_SOLIDO 5
#define DERECHA_BLOQUE_SOLIDO 6
#define IZQUIERDA_BLOQUE_SOLIDO 7
#define JUGADOR_POSICION_HORIZONTAL 1    
#define ANCHO_BLOQUE 16
#define BLOQUE_C_VACIO 0
#define BLOQUE_INFERIOR 1
#define BLOQUE_SUPERIOR 2
#define JUGADOR_EN_ESPERA 0          
#define POSICION_JUGADOR_ABAJO_1 1  
#define POSICION_JUGADOR_ABAJO_2 2  
#define POSICION_SALTO_1 3       
#define POSICION_SALTO_2 4       
#define POSICION_SALTO_3 5       
#define POSICION_SALTO_4 6       
#define POSICION_SALTO_5 7       
#define POSICION_SALTO_6 8       
#define POSICION_SALTO_7 9       
#define POSICION_SALTO_8 10      
#define POSICION_JUGADOR_ARRIBA_1 11 
#define POSICION_JUGADOR_ARRIBA_2 12 
 
LiquidCrystal lcd(5, 7, 10, 11, 12, 13); 
 
char bloqueSuperior[ANCHO_BLOQUE + 1];
char bloqueInferior[ANCHO_BLOQUE + 1];
volatile boolean botonPulsado = false;

int BUZZER = 3;
 
void iniciarGraficos() {
    byte graficos[] = {
        B01100,
        B01100,
        B00000,
        B01110,
        B11100,
        B01100,
        B11010,
        B10011,
        
        B01100,
        B01100,
        B00000,
        B01100,
        B01100,
        B01100,
        B01100,
        B01110,
        
        B01100,
        B01100,
        B00000,
        B11110,
        B01101,
        B11111,
        B10000,
        B00000,
        
        B11110,
        B01101,
        B11111,
        B10000,
        B00000,
        B00000,
        B00000,
        B00000,
        
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,
        B00011,

        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
        B11000,
    };
 
    int i;
 
    for (i = 0; i < 7; ++i) {
        lcd.createChar(i + 1, &graficos[i * 8]);
    }
 
    for (i = 0; i < ANCHO_BLOQUE; ++i) {
        bloqueSuperior[i] = BLOQUE_VACIO;
        bloqueInferior[i] = BLOQUE_VACIO;
    }
}
 
void avanceBloque(char* bloque, byte nuevoBloque) {
    for (int i = 0; i < ANCHO_BLOQUE; ++i) {
        char actual = bloque[i];
        char next = (i == ANCHO_BLOQUE-1) ? nuevoBloque : bloque[i+1];
 
        switch (actual) {
            case BLOQUE_VACIO:
                bloque[i] = (next == BLOQUE_SOLIDO) ? DERECHA_BLOQUE_SOLIDO : BLOQUE_VACIO;
            break;
 
            case BLOQUE_SOLIDO:
                bloque[i] = (next == BLOQUE_VACIO) ? IZQUIERDA_BLOQUE_SOLIDO : BLOQUE_SOLIDO;
            break;
 
            case DERECHA_BLOQUE_SOLIDO:
                bloque[i] = BLOQUE_SOLIDO;
            break;
 
            case IZQUIERDA_BLOQUE_SOLIDO:
                bloque[i] = BLOQUE_VACIO;
            break;
        }
    }
}
 
boolean dibujarJugador(byte posicion, char* bloqueSuperior, char* bloqueInferior, unsigned int puntaje) {
    boolean chocar = false;
    char arribaSeguro = bloqueSuperior[JUGADOR_POSICION_HORIZONTAL];
    char abajoSeguro = bloqueInferior[JUGADOR_POSICION_HORIZONTAL];
    byte arriba, abajo;
 
    switch (posicion) {
        case JUGADOR_EN_ESPERA:
            arriba = abajo = BLOQUE_VACIO;
        break;
 
        case POSICION_JUGADOR_ABAJO_1:
            arriba = BLOQUE_VACIO;
            abajo = CORRER_1;
        break;
 
        case POSICION_JUGADOR_ABAJO_2:
            arriba = BLOQUE_VACIO;
            abajo = CORRER_2;
        break;
 
        case POSICION_SALTO_1:
 
        case POSICION_SALTO_8:
            arriba = BLOQUE_VACIO;
            abajo = SALTAR;
        break;
 
        case POSICION_SALTO_2:
 
        case POSICION_SALTO_7:
            arriba = SALTO_ARRIBA;
            abajo = SALTO_ABAJO;
        break;
 
        case POSICION_SALTO_3:
 
        case POSICION_SALTO_4:
 
        case POSICION_SALTO_5:
 
        case POSICION_SALTO_6:
            arriba = SALTAR;
            abajo = BLOQUE_VACIO;
        break;
 
        case POSICION_JUGADOR_ARRIBA_1:
            arriba = CORRER_1;
            abajo = BLOQUE_VACIO;
        break;
 
        case POSICION_JUGADOR_ARRIBA_2:
            arriba = CORRER_2;
            abajo = BLOQUE_VACIO;
        break;
    }
 
    if (arriba != ' ') {
        bloqueSuperior[JUGADOR_POSICION_HORIZONTAL] = arriba;
        chocar = (arribaSeguro == BLOQUE_VACIO) ? false : true;
        
    }
 
    if (abajo != ' ') {
        bloqueInferior[JUGADOR_POSICION_HORIZONTAL] = abajo;
        chocar |= (abajoSeguro == BLOQUE_VACIO) ? false : true;
        
    }
 
    byte digitos = (puntaje > 9999) ? 5 : (puntaje > 999) ? 4 : (puntaje > 99) ? 3 : (puntaje > 9) ? 2 : 1;
 
    bloqueSuperior[ANCHO_BLOQUE] = '\0';
    bloqueInferior[ANCHO_BLOQUE] = '\0';
    char temp = bloqueSuperior[16-digitos];
    bloqueSuperior[16-digitos] = '\0';
    lcd.setCursor(0,0);
    lcd.print(bloqueSuperior);
    bloqueSuperior[16-digitos] = temp;
    lcd.setCursor(0,1);
    lcd.print(bloqueInferior);
 
    lcd.setCursor(16 - digitos,0);
    lcd.print(puntaje);
 
    bloqueSuperior[JUGADOR_POSICION_HORIZONTAL] = arribaSeguro;
    bloqueInferior[JUGADOR_POSICION_HORIZONTAL] = abajoSeguro;
    return chocar;
    
}
 
void buttonPush() {   
    botonPulsado = true;
}
 
void setup() {
    pinMode(PIN_BOTON, INPUT_PULLUP); 
 
    attachInterrupt(0, buttonPush, FALLING);
 
    iniciarGraficos();
 
    lcd.begin(16, 2);
  
    pinMode(BUZZER, OUTPUT);
}
 
void loop(){
    static byte posicionJugador = POSICION_JUGADOR_ABAJO_1;
    static byte nuevaTipoBloque = BLOQUE_C_VACIO;
    static byte nuevaDuracionBloque = 1;
    static boolean playing = false;
    static boolean blink = false;
    static unsigned int distancia = 0;
 
    if (!playing) {
        dibujarJugador((blink) ? JUGADOR_EN_ESPERA : posicionJugador, bloqueSuperior, bloqueInferior, distancia >> 3);
 
        if (blink) {
        lcd.setCursor(0,0);
        lcd.print("Pulse Iniciar");
        }
 
        delay(250);
        blink = !blink;
 
        if (botonPulsado) {
            iniciarGraficos();
            posicionJugador = POSICION_JUGADOR_ABAJO_1;
            playing = true;
            botonPulsado = false;
            distancia = 0;
        }
 
        return;
    }
 
    avanceBloque(bloqueInferior, nuevaTipoBloque == BLOQUE_INFERIOR ? BLOQUE_SOLIDO : BLOQUE_VACIO);
    avanceBloque(bloqueSuperior, nuevaTipoBloque == BLOQUE_SUPERIOR ? BLOQUE_SOLIDO : BLOQUE_VACIO);
 
    if (--nuevaDuracionBloque == 0) {
        if (nuevaTipoBloque == BLOQUE_C_VACIO) {
            nuevaTipoBloque = (random(3) == 0) ? BLOQUE_SUPERIOR : BLOQUE_INFERIOR;
            nuevaDuracionBloque = 2 + random(10);
        } else {
            nuevaTipoBloque = BLOQUE_C_VACIO;
            nuevaDuracionBloque = 10 + random(10);
        }
    }
 
    if (botonPulsado) {
        tone(BUZZER, 800, 12);
        if (posicionJugador <= POSICION_JUGADOR_ABAJO_2)
            posicionJugador = POSICION_SALTO_1;
 
        botonPulsado = false;
    }
 
    if (dibujarJugador(posicionJugador, bloqueSuperior, bloqueInferior, distancia >> 3)) {
        playing = false; 
        tone(BUZZER, 270, 500);
    } else {
        if (posicionJugador == POSICION_JUGADOR_ABAJO_2 || posicionJugador == POSICION_SALTO_8) {
            posicionJugador = POSICION_JUGADOR_ABAJO_1;
        } else if ((posicionJugador >= POSICION_SALTO_3 && posicionJugador <= POSICION_SALTO_5) && bloqueInferior[JUGADOR_POSICION_HORIZONTAL] != BLOQUE_VACIO) {
            posicionJugador = POSICION_JUGADOR_ARRIBA_1;
        } else if (posicionJugador >= POSICION_JUGADOR_ARRIBA_1 && bloqueInferior[JUGADOR_POSICION_HORIZONTAL] == BLOQUE_VACIO) {
            posicionJugador = POSICION_SALTO_5;
        } else if (posicionJugador == POSICION_JUGADOR_ARRIBA_2) {
            posicionJugador = POSICION_JUGADOR_ARRIBA_1;
        } else {
            ++posicionJugador;
        }
 
        ++distancia;
    }
 
    delay(100);
}
