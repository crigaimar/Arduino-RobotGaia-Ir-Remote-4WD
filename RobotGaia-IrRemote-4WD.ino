/* Sketch realizzato da Cristian Milia per info cmonline58@yahoo.it
 * Lo sketch è stato realizzato per il seguente materiale installato: 
 * Arduino Uno rev.3 
 * 2A Motor Shield Twin L298P V1.1 DFROBOT
 * Sensore IR TSOP38238 
 * nr. 4 Motori Micro DC Geared Motor
 * Il collegamento dei motori e del sensore è molto semplice. I due motori latareli sinistri (guardando il Robot da dietro), 
 * sono stati collegati sulla scheda motori (2A Motor Shield Twin L298P V1.1 DFROBOT)M1+ e M1- mentre i motori di destra a M2+ e M1-, 
 * il sensore IR è stato collegato il piedino out del sensore al pin 3 della scheda motori. Il positivo del sensore al 5V della scheda motori, 
 * il negativo del sensore al GND della scheda motori.
 * N.B. Vi consiglio per evitare errori di caricare su Arduino, prima lo Sketch che trovate qui nella mia scheda Github denominato IRecvDemo al fine di decodificare,
 * i comandi del vostro telecomando che vanno inseriti subito dopo results.value ==.
 * Per qualsiasi problema e informazioni potete tranquillamente contattarmi alla mail che ho inserito all'inizio del commento
 */


#include <IRremote.h>  // chiamo la libreria IRremote.h

#define E1 10 // PWM Speed Control (Controllo Velocità) Motore di Sinistra
#define M1 12 // Direction Control (Controllo Direzione)Motore di Sinistra
#define E2 11  // PWM Speed Control (Controllo Velocità)Motore di Destra
#define M2 13 // Direction Control (Controllo Direzione)Motore di Destra


int RECV_PIN = 3; // E' il numero del Pin della scheda motori dove ho collegato il mio sensore IR 


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()

{

irrecv.enableIRIn();



pinMode(M1,OUTPUT);
pinMode(M2,OUTPUT);

}

void loop() {

if (irrecv.decode(&results)) {

irrecv.resume();

if (results.value == 0x9CB47){ // Tasto freccia AVANTI decodificata del mio telecomdando Samsung, muove il Robot in avanti

digitalWrite(E1,150); // Imposto la velocità dei due motori sx a 150 
digitalWrite(M1,LOW); // Setto a LOW Direction Control (Controllo Direzione)Motore di Sinistra
digitalWrite(E2,120); // Imposto la velocità dei due motori dx a 120 
digitalWrite(M2,HIGH); // Setto a HIGH Direction Control (Controllo Direzione)Motore di Destra affinchè le ruote girano nello stesso senso delle ruote sx



} else if(results.value == 0xDCB47){ // Tasto freccia SINISTRA decodificata del mio telecomdando Samsung, permette al Robot di girare a sinistra

digitalWrite(M1,HIGH);
digitalWrite(E1,130);
digitalWrite(M2,HIGH);
digitalWrite(E2,130);



} else if(results.value == 0x3CB47){ // Tasto freccia DESTRA decodificato del mio telecomdando Samsung, permette al Robot di girare a destra

digitalWrite(M2,LOW);
digitalWrite(E2,130);
digitalWrite(M1,LOW);
digitalWrite(E1,130);


} else if(results.value == 0x5CB47){ // Tasto freccia RETROMARCIA decodificato del mio telecomdando Samsung, permette al Robot di effettuare retromarcia

digitalWrite(E1,130);
digitalWrite(M1,HIGH);
digitalWrite(E2,130);
digitalWrite(M2,LOW);


} else if(results.value == 0xBCB47){ // Tasto centrale STOP decodificato del mio telecomdando Samsung, permette al Robot di fermare la marcia

digitalWrite(E1,LOW);
digitalWrite(E2,LOW);
digitalWrite(M1,LOW);
digitalWrite(M2,LOW);


irrecv.resume();

}

}

}
