#include <Arduino_APDS9960.h>


void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }

  Serial.println("Red,Green,Blue");
  // put your setup code here, to run once:
}

void loop() {
  int r,g,b,c,prox;
  float sum;
  while(!APDS.colorAvailable()||!APDS.proximityAvailable()){}

  APDS.readColor(r,g,b,c);
  sum=r+g+b;
  prox=APDS.readProximity();

  if (prox>=0 && c>10 && sum>0){
    float redratio=r/sum;
    float greenratio=g/sum;
    float blueratio=b/sum;

    Serial.print(redratio, 3);
    Serial.print(',');
    
    Serial.print(greenratio, 3);
    Serial.print(',');

    Serial.print(blueratio, 3);
    Serial.println();
  }
  // put your main code here, to run repeatedly:
}
