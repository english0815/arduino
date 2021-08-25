/* Pin definition */
int RELAYpin = 7;

/* Public variable */
String s = "";
int wait_time = 3;

void help() 
{
  Serial.println("");
  Serial.println("> Help:");
  Serial.println("  =================");
  Serial.println("  on:    Power on");
  Serial.println("  off:   Power off");
  Serial.println("  reset: Reset (default time: 3s)");
  Serial.println("  config time <time>: config reset time (Unit: second)");
  Serial.println("");
  Serial.print("> ");
} 

void strcmd(String cmd)
{
  if (cmd == "off") {
    Serial.println("Power off ...");
    digitalWrite(RELAYpin, LOW);
  } else if (cmd == "on") {
    Serial.println("Power on ...");
    digitalWrite(RELAYpin, HIGH);
  } else if (cmd == "reset") {
    Serial.print("Waiting ");
    Serial.print(wait_time);
    Serial.println(" second, and then reset ...");
    digitalWrite(RELAYpin, LOW);
    delay(wait_time * 1000);
    digitalWrite(RELAYpin, HIGH);
  } else if (cmd == "help") {
    help();
  } else if (cmd.substring(0, 11) == "config time") { // config time s
    int tmp_time = cmd.substring(11).toInt();
    
    if (tmp_time == 0) {
      Serial.print("Invalid input: ");
      Serial.println(tmp_time);
      return;
    }
    
    wait_time = tmp_time;
    Serial.print("Config reset time to ");
    Serial.println(wait_time);
  } else {
    Serial.println("No support ...");
  }
  
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(RELAYpin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(RELAYpin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

  help();
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
