// Arduino Nano + Display SSD1306 + Brushlessmotor mit ESC

// Anschluss Arduino:
// A0 = analog Eingang Poti
// A1 = analog Eingang Spannungsteiler => Voltmeter
// A4 = Display SDA
// A5 = Display SCK
// D2 = Taster "LEER, noch nicht vorgesehen" => Reedkontakt schaltet ueber GND
// D3 = Taster "LEER, noch nicht vorgesehen" => Reedkontakt schaltet ueber GND
// D4 = Taster "Gas geben" => Reedkontakt schaltet ueber GND
// D5 = Taster "LEER, noch nicht vorgesehen" => Reedkontakt schaltet ueber GND
// D6 = Steuerleitung ESC Brushless Motor

// Daten ESC:
// Rechtecksignal
// Periodendauer: 20ms
// min Pulsdauer: 1ms => servo.write(0)
// max. Pulsdauer: 2ms => servo.write(180)

// Programmbeschreibung (Forderung)
// Einschalten von Arduino => Display zeigt aktuelle Spannung an (richtige Zellenspannung wird angezeigt => 40,4V)
// Das ESC wird initialisiert (funktioniert)
// ueber Poti kann die Geschwindigkeit eingestellt werden funktioniert, jedoch dreht der Motor direkt in der eingestellten Geschwindigkeit los)
// Motor dreht nur, wenn Taster D4 (Gas geben) betätigt wird (Funktioniert nicht)
// Wenn Taster D4 nicht betaetigt ist, dann muss die Pulsdauer von 1ms an D6 anliegen
// Wenn Taster D4 betätigt ist liegt am D6 die am Poti eingestellte Pulsdauer an


// Servo
#include <Servo.h>  //20ms Periode (50 Hz)

Servo servo;  // create servo object

unsigned long startzeit;
unsigned long messzeit = 100000; // Messintervall in Mikrosekunden
int val = 25;

// Display
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int analogInput = 1;
float vout = 0.0;
float vin = 0.0;
float R1 = 10000.0; // resistance of R1
float R2 = 1408.0; // resistance of R2
int value = 0;

// Trigger
const int buttonThrottle_Pin = 4;
bool buttonThrottle =  false;

void setup() {
  // Motor
  Serial.begin(115200);
  startzeit = micros(); // aktuelle Zeit wir in ms ausgelesen
  servo.attach(6); // ESC ausgang aus Pin D6
  servo.write(25); //Wird zum Initialisieren des ESC  benötigt
  //delay(2000);
  
  //TRIGGER
  pinMode(buttonThrottle_Pin, INPUT_PULLUP);

  //Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  if ((micros() - startzeit) >= messzeit) {
    servo.write(val);
    //Serial.println(val);
    startzeit = micros();
  }

  if(readButtonThrottle()) {
    // button gedrückt
    //val = map(analogRead(A0), 0, 1023, 30, 110);
    val = 180;
    servo.write(val);
    Serial.println(val);
    //delay(20);
  }
  else {
    // button nicht gedrückt
    servo.write(25);
    Serial.println(-1);
    //delay(200);
  }
  
  //val = map(analogRead(A0), 0, 1023, 30, 110);
  //servo.write(val);

   // Display => analog Eingang lesen
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0;
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;
} 
 Serial.println(vin);

  // set text color / Textfarbe setzen
  display.setTextColor(WHITE);
  // set text size / Textgroesse setzen
  display.setTextSize(1);
  // set text cursor position / Textstartposition einstellen
  display.setCursor(1,0);
  // show text / Text anzeigen
  display.println("D. Kroell");
  
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(45,10);
  display.println(vin);
  //delay(10); // war vorher 1000
  

  display.setTextSize(2);
  display.setCursor(1,10);
  display.print("U=");
  
  display.setTextSize(2);
  display.setCursor(110,10);
  display.print("V");
  
  display.display();
  //delay(20); // war vorher 2000
  //display.clearDisplay();
  
  // invert the display / Display invertieren
  //display.invertDisplay(true);
  //delay(2000); 
  //display.invertDisplay(false);
  //delay(1000); 

}


// true wenn button gedrückt sonst false
bool readButtonThrottle() {
  int temp = digitalRead(buttonThrottle_Pin);
  if(temp>0) return false; // Taster nicht betätigt
  else return true; // Taster betätigt
}
