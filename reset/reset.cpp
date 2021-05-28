#include <Arduino.h>
int RELAYpin = 7;

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	pinMode(RELAYpin, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(RELAYpin, HIGH);
	digitalWrite(LED_BUILTIN, HIGH);

	Serial.println("");
	Serial.println("> Input the string:");
	Serial.println("  =================");
	Serial.println("  on:    Power off");
	Serial.println("  off:   Power on");
	Serial.println("  reset: Reset");
	Serial.println("");
	Serial.print("> ");
}

String s = "";

void strcmd(String cmd)
{
	if (cmd == "off") {
		Serial.println("Power off ...");
		digitalWrite(RELAYpin, LOW);
	} else if (cmd == "on") {
		Serial.println("Power on ...");
		digitalWrite(RELAYpin, HIGH);
	} else if (cmd == "reset") {
		Serial.println("Wait 3s, and reset ...");
		digitalWrite(RELAYpin, LOW);
		delay(3000);
		digitalWrite(RELAYpin, HIGH);
	} else {
		Serial.println("No support ...");
	}
	
}

void loop() {
	if (Serial.available() > 0) {
		char c = Serial.read();
		if (c != '\r') {
			s += c;
			Serial.print(c);
			if (c == '\b') {
				Serial.print(" ");
				Serial.print(c);
				s.remove(s.length()-2);
			}
		} else {
			Serial.println("");
			if (s != "") {
				strcmd(s);
			}
			s = "";
			Serial.println("");
			Serial.print("> ");
		}
	}
}
