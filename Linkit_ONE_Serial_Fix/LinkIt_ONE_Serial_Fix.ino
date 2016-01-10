String initializeBuffer;    // This will store what you enter to start the serial port
String message = "Hello World";

void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);    // Initialize the serial port at 9600 bauds

 while(Serial.available()== 0 ){}   // This will wait until anything is input by the user
 initializeBuffer = Serial.readString();

 Serial.println(message);

}

void loop() {
  // put your main code here, to run repeatedly:
}
