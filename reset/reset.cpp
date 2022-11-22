/* Pin definition */
int RELAYpin = 7;

/* Public variable */
String s = "";
int wait_time = 3;
String power_status = "on";

void help() 
{
  Serial.println("");
  Serial.println("> Power control help:");
  Serial.println("  =======================================================");
  Serial.println("  on:                    Power on");
  Serial.println("  off:                   Power off");
  Serial.println("  reset:                 Reset (default time: 3s)");
  Serial.println("  config time <time>:    Config reset time (Unit: second)");
  Serial.println("  help:                  Help messages");
  Serial.println("  =======================================================");
  Serial.println("");
  Serial.println("  Author: Allen Hsu, aka Dajia coder.  Date: 2022.11.23");
  Serial.println("");
  Serial.print("> ");
}

void countdown(int time)
{
  int i = 0;
  while (1){
    delay(1000);
    i += 1;
    Serial.print(i);
    Serial.println(" second ...");
    if (i == time)
      break;
  }
}
void power_on()
{
  Serial.println("Power on ...");
  power_status = "on";
  digitalWrite(RELAYpin, HIGH);
}

void power_off()
{
  Serial.println("Power off ...");
  power_status = "off";
  digitalWrite(RELAYpin, LOW);
}

void strcmd(String cmd)
{
  if (cmd == "off") {
    if (cmd == power_status) {
      Serial.println("No action, power off already!");
    } else {
      power_off();
    }
  } else if (cmd == "on") {
    if (cmd == power_status) {
      Serial.println("No action, power on already!");
    } else {
      power_on();
    }
  } else if (cmd == "reset") {
    Serial.print("Waiting ");
    Serial.print(wait_time);
    Serial.println(" seconds, and then reset ...");
    power_off();
    //delay(wait_time * 1000);
    countdown(wait_time);
    power_on();
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
