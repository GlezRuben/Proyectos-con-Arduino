// Suscribete a mi canal: Aprende con Ruben's

#define NOTE_DO4   262
#define NOTE_DO4S  277
#define NOTE_RE4   294
#define NOTE_RE4S  311
#define NOTE_MI4   330
#define NOTE_FA4   349
#define NOTE_FA4S  370
#define NOTE_SOL4  392
#define NOTE_SOL4S 415
#define NOTE_LA4   440
#define NOTE_LA4S  466
#define NOTE_SI4   494

#define NOTE_DO5   523
#define NOTE_DO5S  554
#define NOTE_RE5   587
#define NOTE_RE5S  622
#define NOTE_MI5   659
#define NOTE_FA5   698
#define NOTE_FA5S  740
#define NOTE_SOL5  784
#define NOTE_SOL5S 831
#define NOTE_LA5   880
#define NOTE_LA5S  932
#define NOTE_SI5   988

#define NOTE_DO6   1047
#define NOTE_DO6S  1109
#define NOTE_RE6   1175
#define NOTE_RE6S  1245
#define NOTE_MI6   1319
#define NOTE_FA6   1397
#define NOTE_FA6S  1480
#define NOTE_SOL6  1568
#define NOTE_SOL6S 1661
#define NOTE_LA6   1760
#define NOTE_LA6S  1865
#define NOTE_SI6   1976

int melody[] = {
   NOTE_DO5, 8,
   NOTE_DO5, 8,
   NOTE_FA5, 32,
   NOTE_LA5, 8,
   NOTE_SOL5, 8,
   NOTE_FA5, 8,
   NOTE_SOL5, 32,

   NOTE_RE5, 8,
   NOTE_MI5, 8,
   NOTE_FA5, 32,
   NOTE_FA5, 8,
   NOTE_SOL5,8,
   NOTE_FA5, 8,
   NOTE_MI5, 32,
   
   NOTE_DO5, 8,
   NOTE_DO5, 8,
   NOTE_FA5, 32,
   NOTE_LA5, 8,
   NOTE_SOL5,8,
   NOTE_FA5, 8,
   NOTE_SOL5, 32,
  
   NOTE_RE5, 8,
   NOTE_MI5, 8,
   NOTE_FA5, 32,
   NOTE_FA5, 8,
   NOTE_MI5,16,
   NOTE_RE5,8,
   NOTE_DO5, 8,
   NOTE_RE5, 32,
  
   NOTE_DO5, 8,
   NOTE_DO5, 8,
   NOTE_FA5, 32,
   NOTE_LA5, 8,
   NOTE_SOL5, 8,
   NOTE_FA5, 8,
   NOTE_SOL5, 32,

   NOTE_RE5, 8,
   NOTE_MI5, 8,
   NOTE_FA5, 16,
   NOTE_FA5, 8,
   NOTE_SOL5,8,
   NOTE_FA5, 8,
   NOTE_MI5, 32,
   };

int num_notas = sizeof(melody) / (2 * sizeof(melody[0]));

int BUZZER = 8;

void setup() {
   pinMode(BUZZER, OUTPUT);
}


void loop() {

   for(int nota = 0; nota < num_notas*2; nota += 2) {
      int nota_tono = melody[nota];
      int nota_duracion = melody[nota+1];
      tone(BUZZER, nota_tono, nota_duracion*50);
      delay(nota_duracion * 50 + 30);
   }
   delay(20);
}
