/*
KEYMAP as found here: http://www.nouspikel.com/ti99/titechpages.htm
 
 # = wire from left to right looking at Serial from normal orientation
 
      #12  #13  #14  #15  #9  #8  #6
 #5    =    .    ,    M    N   /   
 #4  spac   L    K    J    H   ;
 #1  entr   O    I    U    Y   P
 #2         9    8    7    6   0
 #7  fctn   2    3    4    5   1  lock
 #3  shft   S    D    F    G   A
 #10 ctrl   W    E    R    T   Q
 #11        X    C    V    B   Z
 
 Edited for ATMEGA 32U4
 Greg Winn
 
 */


#include <Bounce.h>
#include <Wire.h>

/*
	SLAVE / KEYBOARD ADDRESS -> 2
*/
#define KEYBOARD_ADDRESS 2

const int bounceDelay = 90;

Bounce wire1  = Bounce(0, bounceDelay); // OUTPUT
Bounce wire3  = Bounce(3, bounceDelay); // OUTPUT
Bounce wire4  = Bounce(4, bounceDelay); // OUTPUT
Bounce wire5  = Bounce(5, bounceDelay); // OUTPUT
Bounce wire6  = Bounce(6, bounceDelay); // INPUT
Bounce wire7  = Bounce(7, bounceDelay); // OUTPUT
Bounce wire8  = Bounce(8, bounceDelay); // INPUT
Bounce wire9  = Bounce(9, bounceDelay); // INPUT
Bounce wire10 = Bounce(10, bounceDelay); // OUTPUT
Bounce wire11 = Bounce(11, bounceDelay); // OUTPUT
Bounce wire12 = Bounce(12, bounceDelay); // INPUT
Bounce wire13 = Bounce(13, bounceDelay); // INPUT
Bounce wire14 = Bounce(A0, bounceDelay); // INPUT
Bounce wire15 = Bounce(A1, bounceDelay); // INPUT

boolean fctn;
boolean shft;
boolean ctrl;
boolean lock;


void setup(){
	Serial.begin(9600);
	Wire.begin(KEYBOARD_ADDRESS);
	delay(5); // Give it time to get setup
	Wire.onRequest(requestEvent);
	
	pinMode(0, OUTPUT);  // 1
	pinMode(2, OUTPUT);  // 2
	pinMode(3, OUTPUT);  // 3
	pinMode(4, OUTPUT);  // 4
	pinMode(5, OUTPUT);  // 5
	pinMode(6, INPUT);  // 6
	pinMode(7, OUTPUT);  // 7
	pinMode(8, INPUT);  // 8
	pinMode(9, INPUT );  // 9
	pinMode(10, OUTPUT );  // 10
	pinMode(11, OUTPUT );  // 11
	pinMode(12, INPUT );  // 12
	pinMode(13, INPUT );  // 13
	pinMode(A0, INPUT );  // 14 
	pinMode(A1, INPUT );  // 15
}

void loop(){
	
	// check for SHIFT, CTRL, FCTN, and/or ALPHA LOCK
  checkModifiers();
	
	digitalWrite(0, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	// ----------------------- Y
	if(wire9.risingEdge()){
		if(lock == true){ 
			Serial.print('Y');
			lock = false;
		} 
		else if(shft == true){
			Serial.print('Y');
			shft = false;
		} else {
			Serial.print('y');
		}
	}
	
	// ----------------------- P
	if(wire8.risingEdge()){
		if(lock == true){ 
			Serial.print('P'); 
			lock = false;
		} 
		else if(shft == true){
			Serial.print('P'); 
			shft = false;
		}
		else if(fctn == true) {
			Serial.print('"');
			fctn = false;
		} else {
			Serial.print('p');			
		}
	}
	
	// ----------------------- I
	if(wire14.risingEdge()){
		if(lock == true){ 
			Serial.print('I'); 
			lock = false;
		} 
		else if(shft == true){
			Serial.print('I'); 
			shft = false;
		}
		else if(fctn == true) {
			Serial.print('?');
			fctn = false;
		} else {
			Serial.print('i'); 
		}
	}
	
	// ----------------------- O
	if(wire13.risingEdge()){
		if(lock == true){ 
			Serial.print('O'); 
			lock = false;
		} 
		else if(shft == true){
			Serial.print('O'); 
			shft = false;
		}
		else if(fctn == true) {
			Serial.print("'");
			fctn = false;
		} else {
			Serial.print('o'); 
		}
	}
	
	// ----------------------- Enter / Return
	if(wire12.risingEdge()){
		Serial.print('\n');
	}
	
	// ----------------------- U
	if(wire15.risingEdge()){
		if(lock == true){ 
			Serial.print('U'); 
			lock = false;
		} 
		else if(shft == true){
			Serial.print('U'); 
			shft = false;
		}
		else if(fctn == true) {
			Serial.print("_");
			fctn = false;
		} else {
			Serial.print('u'); 
		}
	}
	// ------------------------------ END ROW 0
	digitalWrite(0, LOW);
	
	
	// ------------------------------ Start ROW 2
	digitalWrite(2, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	
	// ----------------------- 6
	if(wire9.risingEdge()){
		if(shft == true){
			Serial.print('^'); 
			shft = false;
		} else {
			Serial.print('6');			
		}
	}
	
	// ----------------------- 0
	if(wire8.risingEdge()){
		if(shft == true){
			Serial.print(')'); 
			shft = false;
		} else {
			Serial.print('0');			
		}
	}
	
	// ----------------------- 7
	if(wire15.risingEdge()){
		if(shft == true){
			Serial.print('&'); 
			shft = false;
		} else {
			Serial.print('7');			
		}
	}
	
	// ----------------------- 8
	if(wire14.risingEdge()){
		if(shft == true){
			Serial.print('*'); 
			shft = false;
		} else {
			Serial.print('8');			
		}
	}
	
	// ----------------------- 9
	if(wire13.risingEdge()){
		if(shft == true){
			Serial.print('('); 
			shft = false;
		} else if(fctn == true){
			Serial.press(KEY_LEFT_ARROW);
			fctn = false;
			Serial.release(KEY_LEFT_ARROW);
		} else {
			Serial.print('9');
		}
	}
	
	// ------------------------------ END ROW 2
	digitalWrite(2, LOW);
	
	// ------------------------------ Start ROW 3
	digitalWrite(3, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	// ----------------------- A
	if(wire8.risingEdge()){
		if(lock == true){
			Serial.print('A'); 
			lock = false;
		} else if(fctn == true) {
			Serial.print("|");
			fctn = false;
		} else if(shft == true){
			Serial.print('A');
			shft = false;
		} else {
			Serial.print('a'); 
		}
	}

	// ----------------------- G
	if(wire9.risingEdge()){
		if(lock == true){
			Serial.print('G'); 
			lock = false;
		} else if(fctn == true) {
			Serial.print("}");
			fctn = false;
		} else if(shft == true){
			Serial.print('G');
			shft = false;
		} else {
			Serial.print('g'); 
		}
	}

	// ----------------------- F
	if(wire15.risingEdge()){
		if(lock == true){
			Serial.print('F'); 
			lock = false;
		} else if(fctn == true) {
			Serial.print("{");
			fctn = false;
		} else if(shft == true){
			Serial.print('F'); 
			shft = false;
		} else {
			Serial.print('f'); 
		}
	}

	// ----------------------- D
	if(wire14.risingEdge()){
		if(lock == true){
			Serial.print('D'); 
			lock = false;
		} else if(fctn == true) {
			Serial.press(KEY_RIGHT_ARROW);
			fctn = false;
			Serial.release(KEY_RIGHT_ARROW);
		} else if(shft == true) {
			Serial.print('D');
			shft = false;
		} else {
			Serial.print('d'); 
		}
	}

	// ----------------------- S
	if(wire13.risingEdge()){
		if(lock == true){
			Serial.print('S');
			lock = false; 
		} else if(fctn == true) {
			Serial.press(KEY_LEFT_ARROW);
			fctn = false;
			Serial.release(KEY_LEFT_ARROW);
		} else if(shft == true){
			Serial.print('S');
			shft = false;
		} else {
			Serial.print('s'); 
		}
	}

	// ------------------------------ END ROW 3
	digitalWrite(3, LOW);
	
	// ------------------------------ Start ROW 4
	digitalWrite(4, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	
	// ----------------------- ;
	if(wire8.risingEdge()){
		if(shft == true){
			Serial.print(':'); 
			shft = false;
		} else {
			Serial.print(';'); 
		}
	}

	// ----------------------- H
	if(wire9.risingEdge()){
		if(lock == true){
			Serial.print('H'); 
			lock = false;
		} else if(shft == true){
			Serial.print('H');
			shft = false;
		} else {
			Serial.print('h'); 
		}
	}

	// ----------------------- J
	if(wire15.risingEdge()){
		if(lock == true){
			Serial.print('J'); 
			lock = false;
		} else if(shft == true){
			Serial.print('J'); 
			shft = false;
		} else {
			Serial.print('j'); 
		}
	}

	// ----------------------- K
	if(wire14.risingEdge()){
		if(lock == true){
			Serial.print('K'); 
			lock = false;
		} else if(shft == true) {
			Serial.print('K');
			shft = false;
		} else {
			Serial.print('k'); 
		}
	}

	// ----------------------- L
	if(wire13.risingEdge()){
		if(lock == true){
			Serial.print('L');
			lock = false; 
		} else if(shft == true){
			Serial.print('L');
			shft = false;
		} else {
			Serial.print('l'); 
		}
	}

	// ----------------------- SPACE
	if(wire12.risingEdge()){
		Serial.print(' '); 
	}  
	
	// ------------------------------ END ROW 4
	digitalWrite(4, LOW);
	
	// ------------------------------ Start ROW 5
	digitalWrite(5, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	
	// ----------------------- /
	if(wire8.risingEdge()){
		if(shft == true){
			Serial.print('-'); 
			shft = false;
		} else {
			Serial.print('/'); 
		}
	}

	// ----------------------- N
	if(wire9.risingEdge()){
		if(lock == true){
			Serial.print('N'); 
			lock = false;
		} else if(shft == true){
			Serial.print('N'); 
		} else {
			Serial.print('n'); 
		}
	}

	// ----------------------- M
	if(wire15.risingEdge()){
		if(lock == true){
			Serial.print('M'); 
			lock = false;
		} else if(shft == true){
			Serial.print('M'); 
		} else {
			Serial.print('m'); 
		}
	}

	// ----------------------- ,
	if(wire14.risingEdge()){
		if(shft == true){
			Serial.print('<'); 
			shft = false;
		} else {
			Serial.print(','); 
		}
	}

	// ----------------------- .
	if(wire13.risingEdge()){
		if(shft == true){
			Serial.print('>'); 
			shft = false;
		} else {
			Serial.print('.'); 
		}
	}

	// ----------------------- =
	if(wire12.risingEdge()){
		if(shft == true){
			Serial.print('+'); 
			shft = false;
		} else {
			Serial.print('='); 
		}
	}  
	
	// ------------------------------ END ROW 5
	digitalWrite(5, LOW);
	
	// ------------------------------ Start ROW7
	digitalWrite(7, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	
	// ----------------------- 1
	if(wire8.risingEdge()){
		if(shft == true){
			Serial.print('!'); 
			shft = false;
		} else if(ctrl == true){
			Serial.press(KEY_BACKSPACE);
			ctrl = false;
			Serial.release(KEY_BACKSPACE);
		} else {
			Serial.print('1'); 
		}
	}

	// ----------------------- 5
	if(wire9.risingEdge()){
		if(shft == true){
			Serial.print('%'); 
		} else {
			Serial.print('5'); 
		}
	} 

	// ----------------------- 4
	if(wire15.risingEdge()){
		if(shft == true){
			Serial.print('$'); 
		} else {
			Serial.print('4'); 
		}
	} 

	// ----------------------- 3
	if(wire14.risingEdge()){
		if(shft == true){
			Serial.print('#'); 
		} else {
			Serial.print('3'); 
		}
	}  

	// ----------------------- 2
	if(wire13.risingEdge()){
		if(shft == true){
			Serial.print('@'); 
		} else {
			Serial.print('2'); 
		}
	}
	
	// ------------------------------ END ROW 7
	digitalWrite(7, LOW);
	
	// ------------------------------ Start ROW 10
	digitalWrite(10, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	
	// ----------------------- Q
	if(wire8.risingEdge()){
		if(lock == true){
			Serial.print('Q'); 
			lock = false;
		} else if(shft == true){
			Serial.print('Q');
			shft = false; 
		} else {
			Serial.print('q'); 
		}
	} 

	// ----------------------- T
	if(wire9.risingEdge()){
		if(lock == true){
			Serial.print('T'); 
			lock = false;
		} else if(shft == true){
			Serial.print('T');
			shft = false; 
		} else if(fctn == true){
			Serial.print(']');
			fctn = false;
		} else {
			Serial.print('t'); 
		}
	}  

	// ----------------------- R
	if(wire15.risingEdge()){
		if(lock == true){
			Serial.print('R'); 
			lock = false;
		} else if(shft == true){
			Serial.print('R');
			shft = false; 
		} else if(fctn == true){
			Serial.print('[');
			fctn = false;
		} else {
			Serial.print('r'); 
		}
	}  

	// ----------------------- E
	if(wire14.risingEdge()){
		if(lock == true){
			Serial.print('E'); 
			lock = false;
		} else if(shft == true){
			Serial.print('E');
			shft = false; 
		} else if(fctn == true){
			Serial.press(KEY_UP_ARROW);
			fctn = false;
			Serial.release(KEY_UP_ARROW);
		} else {
			Serial.print('e'); 
		}
	} 

	// ----------------------- W
	if(wire13.risingEdge()){
		if(lock == true){
			Serial.print('W'); 
			lock = false;
		} else if(shft == true){
			Serial.print('W');
			shft = false; 
		} else if(fctn == true){
			Serial.print('~');
			fctn = false;
		} else {
			Serial.print('w'); 
		}
	} 
	
	// ------------------------------ END ROW 10
	digitalWrite(10, LOW);
	
	// ------------------------------ Start ROW 11
	digitalWrite(11, HIGH);
	wire6.update();
	wire9.update();
	wire8.update();
	wire15.update();
	wire14.update();
	wire13.update();
	wire12.update();
	
	// ----------------------- Z
	if(wire8.risingEdge()){
		if(lock == true){
			Serial.print('Z'); 
			lock = false;
		} else if(shft == true){
			Serial.print('Z');
			shft = false; 
		} else if(fctn == true){
			Serial.print("\\");
			fctn = false;
		} else {
			Serial.print('z'); 
		}
	} 

	// ----------------------- B
	if(wire9.risingEdge()){
		if(lock == true){
			Serial.print('B'); 
			lock = false;
		} else if(shft == true){
			Serial.print('B');
			shft = false; 
		} else {
			Serial.print('b'); 
		}
	} 

	// ----------------------- V
	if(wire15.risingEdge()){
		if(lock == true){
			Serial.print('V'); 
			lock = false;
		} else if(shft == true){
			Serial.print('V');
			shft = false; 
		} else {
			Serial.print('v'); 
		}
	} 

	// ----------------------- C
	if(wire14.risingEdge()){
		if(lock == true){
			Serial.print('C'); 
			lock = false;
		} else if(shft == true){
			Serial.print('C');
			shft = false; 
		} else if(fctn == true){
			Serial.print('`');
			fctn = false; 
		} else {
			Serial.print('c'); 
		}
	} 

	// ----------------------- X
	if(wire13.risingEdge()){
		if(lock == true){
			Serial.print('X'); 
			lock = false;
		} else if(shft == true){
			Serial.print('X');
			shft = false; 
		} else if(fctn == true){
			Serial.press(KEY_DOWN_ARROW);
			fctn = false;
			Serial.release(KEY_DOWN_ARROW);
		} else {
			Serial.print('x'); 
		}
	} 
	
	// ------------------------------ END ROW 11
	digitalWrite(11, LOW);
}


//------------------------------------------------  MODIFIER KEYS
void checkModifiers(){ 
  
	// ------------------------ Wire 3 @ PIN 12: shft
	digitalWrite(3, HIGH);
	wire12.update();
	if(digitalRead(12) == 1){
		shft = true; 
	} else {
		shft = false; 
	}
	digitalWrite(3, LOW);

	// ------------------------ Wire 7 @ PIN 16: fctn & lock
	digitalWrite(7, HIGH); 
	wire12.update();
	wire6.update(); 
	if(digitalRead(12) == 1){
		fctn = true; 
	} else {
		fctn = false; 
	}
	if(digitalRead(6) == 1){
		lock = true; 
	} else {
		lock = false; 
	}
	digitalWrite(7, LOW);


	// ------------------------ Wire 10 @ PIN 44: ctrl
	digitalWrite(10, HIGH);
	wire12.update();
	if(digitalRead(12) == 1){
		ctrl = true; 
	} else {
		ctrl = false; 
	}
	digitalWrite(10, LOW);
}

void requestEvent(){
	
}