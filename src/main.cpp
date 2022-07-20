#include <Arduino.h>
#include <Keypad.h>
#include <TFT_eSPI.h> // TFT Treiber
#include <SPI.h>

// Programmteile einfuegen
#include <keypad4x3.h>
#include <fragen.h>
#include <btclogo.h>
#include <gclogo.h>
#include <spiel_var.h>

/////////////////////////////////////////////////////////////////////////// TFT Setup
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h



/////////////////////////////////////////////////////////////////////////// Intervall der Steuerung
unsigned long previousMillis_fragen = 0;
unsigned long interval_fragen = 2000; 

/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
//void callback                (char*, byte*, unsigned int);
void loop                      ();
void setup                     ();
void spiel_beginn              ();
void spiel_frage               (int nummer_der_frage);
void spiel_auswertung          ();


/////////////////////////////////////////////////////////////////////////// void SETUP
void setup() {

Serial.begin(115200);
Serial.println("Setup starten ..."); 
  
  // TFT init
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextSize(1);
  // text 1
  tft.setCursor(5, 10, 2);
  tft.println("System startet .....!");
  delay(2000);
  tft.setCursor(5, 30, 2);
  tft.println("Lade Fragen ........! ");
   delay(2000);
  tft.setCursor(5, 50, 2);
  tft.println("Teste Checksumme ...!");
   delay(2000);   
  tft.setCursor(8, 80, 2);
  tft.setTextSize(2);
  tft.setTextColor(TFT_ORANGE,TFT_BLACK);
  tft.println("Viel Spass");
   delay(2000);  


  tft.fillScreen(TFT_ORANGE);
  
  tft.drawBitmap(20, 10, bitcoinLogo, 128, 64, TFT_BLACK);
  tft.setCursor(30, 80, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
   tft.setTextSize(1);
  tft.println("Bitcoin Geocache");  
  tft.setCursor(60, 100, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
   tft.setTextSize(1);
  tft.println(gcnummer);   
   delay(4000); 
   tft.fillScreen(TFT_ORANGE);
}

///////////////////////////////////////////////////////////////////////////  void Auswertung
void spiel_auswertung() {
    char key = keypad.getKey();

  tft.setCursor(5, 2, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
  tft.setTextSize(1);
  tft.println("Ergebnis");

  tft.setCursor(5, 20, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
  tft.setTextSize(1);
  tft.print("Du hast "); tft.print(punkte); tft.print(" von "); tft.print(maxpunkte); 


  tft.setCursor(5, 35, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
  tft.setTextSize(1); 
  tft.println("Punkten erreicht."); 

  if (punkte == 10) {

    // Alle Punkte bekommen
    tft.setCursor(25, 55, 2);
    tft.setTextColor(TFT_RED,TFT_ORANGE);
    tft.setTextSize(2); 
    tft.println("FINALE!!!");

    tft.drawBitmap(5 , 90, gclogo, 36, 36, TFT_BLACK);

    tft.setCursor(50, 92, 2);
    tft.setTextColor(TFT_BLACK,TFT_ORANGE);
    tft.setTextSize(1); 
    tft.println(koordinaten_N);

    tft.setCursor(50, 108, 2);
    tft.setTextColor(TFT_BLACK,TFT_ORANGE);
    tft.setTextSize(1); 
    tft.println(koordinaten_E);  

      if (key == '*') {
    
      tft.fillScreen(TFT_ORANGE);
      start   = 1;
      punkte  = 0;
      frage   = 1;

    }   

  } else {

       // Alle Punkte bekommen
    tft.setCursor(25, 55, 2);
    tft.setTextColor(TFT_RED,TFT_ORANGE);
    tft.setTextSize(2); 
    tft.println("Verloren!");

    tft.setCursor(30, 90, 2);
    tft.setTextColor(TFT_BLACK,TFT_ORANGE);
    tft.setTextSize(1); 
    tft.println("Restart mit *!"); 


  if (key == '*') {
    
    tft.fillScreen(TFT_ORANGE);
    start   = 1;
    punkte  = 0;
    frage   = 1;

  }


  }




}   


///////////////////////////////////////////////////////////////////////////  void Spiel beginnen
void spiel_beginn() {
  char key = keypad.getKey();

   // Ablaufsteuerung zur wiedergabe der Einführung

  tft.setCursor(20, 40, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
  tft.setTextSize(1);
  tft.println("BITTE # DRUECKEN");
  tft.setCursor(38, 60, 2);
  tft.println("ZUM STARTEN");



    Serial.println("Spiel beginnt Starten # drücken");

  if (key == '#') {
    tft.fillScreen(TFT_ORANGE);
    start   = 1;
  }

}


///////////////////////////////////////////////////////////////////////////  void spiel fragen
void spiel_frage(int nummer_der_frage) {
  char key = keypad.getKey();

/*
  // Frage ausgeben
  Serial.print("Frage : ");
  Serial.println(frage_array[nummer_der_frage][0]);
  Serial.println("Antwort ");
  Serial.println(frage_array[nummer_der_frage][1]);
  Serial.println(frage_array[nummer_der_frage][2]);
  Serial.println(frage_array[nummer_der_frage][3]);
*/

  // TFT ausgabe
  tft.setCursor(3, 5, 2);
  tft.setTextColor(TFT_BLACK,TFT_ORANGE);
  tft.setTextSize(1);
  tft.print("Frage #");tft.println(nummer_der_frage);
  
  
  tft.setCursor(3, 30, 2);
  tft.println(frage_array[nummer_der_frage][0]);
  tft.setCursor(3, 50, 2);
  tft.println(frage_array[nummer_der_frage][1]);  
    tft.setCursor(3, 80, 2);
  tft.print("1) ");tft.println(frage_array[nummer_der_frage][2]);
    tft.setCursor(3, 95, 2);
  tft.print("2) ");tft.println(frage_array[nummer_der_frage][3]);
    tft.setCursor(3, 110, 2);
  tft.print("3) ");tft.println(frage_array[nummer_der_frage][4]);



	if( key == '1' || key == '2' || key == '3' ) //while the button is pressed
	{

  // Nach Eingabe Bildschirm löschen
  tft.fillScreen(TFT_ORANGE);

		// Antwort prüfen und Punkte bei richtiger Antwort addieren
    if(key == frage_antwort[nummer_der_frage]) {
      //Serial.println("*****************************GLEICH : ");
      // Punkte erhöhen und nächste Frage schreiben
      
          ++punkte;
          ++frage;
          return;

    } else {

          ++frage;
          return;
    }
    
	} else
  {   }


}



/////////////////////////////////////////////////////////////////////////// void loop
void loop() {


// ********************************************** Willkommen
if (punkte == 0 && frage == 1 && start == 0){
  // Spiel beginnt - Begruessung laden
  spiel_beginn();
} else {}


// ********************************************** Start Frage 1
if (start == 1 && frage <= 10){
  
  spiel_frage(frage);

} else {}


// ********************************************** Auswertung
if (frage == max_fragen_i){
  
  // Fragemodus beenden
  start = 2;

  // TFT loeschen
  
  
  // Auswertung aufrufen
  spiel_auswertung();
  

}  else {}

 delay(100);


//while(1) yield(); // We must yield() to stop a watchdog timeout.
}