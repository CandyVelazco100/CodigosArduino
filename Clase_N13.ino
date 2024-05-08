// Define el número máximo de caracteres en el mensaje
#define MAX_CHAR 12

// Declaración de variables globales
char mensaje[MAX_CHAR];        // Almacena el mensaje recibido
char caracter_leido;           // Lee cada carácter de la comunicación serial
byte indice = 0;              // Índice para el arreglo de mensaje
int i;

// Pines del RGB LED
int pinRojo = 9;               // Pin para el componente Rojo del RGB -> D9
int pinVerde = 10;             // Pin para el componente Verde del RGB -> D10
int pinAzul = 11;              // Pin para el componente Azul del RGB -> D11

// Variables temporales para los valores de color
String valorTemporalRojo = "";  // Valor temporal del componente Rojo
String valorTemporalVerde = ""; // Valor temporal del componente Verde
String valorTemporalAzul = "";  // Valor temporal del componente Azul

int bandera = 0;                  // Bandera para indicar que se recibió un mensaje completo
char colorActual = 'R';        // Color actual, comienza con rojo

void setup() {
  pinMode(pinRojo, OUTPUT);     // Configura el pin del componente Rojo como salida
  pinMode(pinAzul, OUTPUT);     // Configura el pin del componente Azul como salida
  pinMode(pinVerde, OUTPUT);    // Configura el pin del componente Verde como salida
  Serial.begin(9600);          // Inicializa la comunicación serial a 9600 bps
}

void loop() {
  // Mientras haya datos disponibles en la comunicación serial
  while (Serial.available() > 0) {
    bandera = 0; // Reinicia la bandera
    if (indice < (MAX_CHAR - 1)) { // Verifica que el índice sea menor que el máximo de caracteres
      caracter_leido = Serial.read();   // Lee un carácter de la comunicación serial
      mensaje[indice] = caracter_leido; // Almacena el carácter en el arreglo mensaje
      if (caracter_leido == 'R') {
        colorActual = 'R'; // Establece el color actual como Rojo
        valorTemporalRojo = ""; // Reinicia el valor temporal del componente Rojo
      } else if (caracter_leido == 'G') {
        colorActual = 'G'; // Establece el color actual como Verde
        valorTemporalVerde = ""; // Reinicia el valor temporal del componente Verde
      } else if (caracter_leido == 'B') {
        colorActual = 'B'; // Establece el color actual como Azul
        valorTemporalAzul = ""; // Reinicia el valor temporal del componente Azul
      }
      if (colorActual == 'R' && caracter_leido != 'R') {
        valorTemporalRojo += caracter_leido; // Acumula caracteres para el componente Rojo
      } else if (colorActual == 'G' && caracter_leido != 'G') {
        valorTemporalVerde += caracter_leido; // Acumula caracteres para el componente Verde
      } else if (colorActual == 'B' && caracter_leido != 'B') {
        valorTemporalAzul += caracter_leido; // Acumula caracteres para el componente Azul
      }
      indice++;                       // Incrementa la posición en el mensaje
      mensaje[indice] = '\0';         // Termina el string con nulo
    }
  }

  // Cuando no hay más datos disponibles
  if (bandera == 0) {
    // Actualiza los valores de los pines PWM de los LED
    analogWrite(pinRojo, valorTemporalRojo.toInt());
    analogWrite(pinVerde, valorTemporalVerde.toInt());
    analogWrite(pinAzul, valorTemporalAzul.toInt());
    Serial.println(mensaje);  // Imprime el mensaje recibido
    bandera = 1; // Establece la bandera a 1 para indicar que se procesó el mensaje
    for (i = 0; i < MAX_CHAR; i++) {
      mensaje[i] = '\0';       // Reinicia el arreglo mensaje
    }
    indice = 0;                 // Reinicia el índice
  }
}
