// ------------
// Light Sensor
// ------------


// Variables

int led1 = D7; //On board LED
int photoresistor = A0; //Photoresistor analog signal connected to A0
int analogValue; // stores photoresistor value
int temp;  // stores previous photoresistor value for comparison
int light_thresh = 2000;  // light threshold value
bool flag;  // Flag to force initial check (while loop) to run once.

//Setup

void setup() {

  pinMode(led1, OUTPUT);
  pinMode(photoresistor, INPUT);
  Particle.variable("photoresistor", analogValue);
  temp = analogRead(photoresistor);
  flag = TRUE;
}

//Main Loop
void loop() {
    
analogValue = analogRead(photoresistor);

// Initial check on start up and inital event publish.
    
while (flag) {
    if (analogValue > light_thresh) {
        temp = analogValue;
        Particle.publish("Enough_Light", "Your terrarium is in light");
        digitalWrite (led1, HIGH);
        flag = FALSE;
    }
    
    if (analogValue <= light_thresh) {
        temp = analogValue;
        Particle.publish("Not_Enough_Light", "Your terrarium is not in light");
        digitalWrite (led1, LOW);
        flag = FALSE;
    }
}

// After initial check it loops over the below every 5 seconds and publishes an event if a change of state occurs between enough light or not enough light.
//This is where comparison takes places on previous photoresistor value.
// If light is brighter than threshold  LED is on. Otherwise LED is off.
// Sun lit room = approx 4000. pitch black room = close to zero

if ((analogValue > light_thresh) && (temp <= light_thresh)) {
    temp = analogValue;
    Particle.publish("Enough_Light", "Your terrarium is in light");
    digitalWrite (led1, HIGH);
}

if ((analogValue <= light_thresh) && (temp > light_thresh)) {
    temp = analogValue;
    Particle.publish("Not_Enough_Light", "Your terrarium is not in light");
    digitalWrite (led1, LOW);
}

delay(5000); // wait 5 seconds.

}

