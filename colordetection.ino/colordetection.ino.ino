#include <Arduino_APDS9960.h>

void setup() {
  //start the serial monitor
  Serial.begin(9600);
  while (!Serial);
  
  //check if the sensor is responsive
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }

  Serial.println("Red,Green,Blue");
  // put your setup code here, to run once:
}

void loop() {
  //declare variables to store the rgb values and to set the proximity range
  int r,g,b,c,prox;
  float sum;
  while(!APDS.colorAvailable()||!APDS.proximityAvailable()){}
  
  //use the sensor to read the color values
  APDS.readColor(r,g,b,c);
  sum=r+g+b;
  //start reading the proximity from the sensor
  prox=APDS.readProximity();

// set a suitable proximity range here the range is theoratically infinity
  if (prox>=0 && c>10 && sum>0){
    // calculate the ratio of each color that is by normalizing the values for better accuracy
    float redratio=r/sum;
    float greenratio=g/sum;
    float blueratio=b/sum;

//print the values in the serial monitor and copy them to a csv files
    Serial.print(redratio, 3);
    Serial.print(',');
    
    Serial.print(greenratio, 3);
    Serial.print(',');

    Serial.print(blueratio, 3);
    Serial.println();
  }
  // put your main code here, to run repeatedly:
}
