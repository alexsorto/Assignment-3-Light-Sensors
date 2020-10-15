#include <EEPROM.h>


int sensorPin0 = A0;   // select the input pin for ldr
long sensorValue0 = 0;  // variable to store the value coming from the sensor

int sensorPin1 = A1;   // select the input pin for ldr
long sensorValue1 = 0;  // variable to store the value coming from the sensor

int sensorPin2 = A2;   // select the input pin for ldr
long sensorValue2 = 0;  // variable to store the value coming from the sensor

int sensorPin3 = A3;   // select the input pin for ldr
long sensorValue3 = 0;  // variable to store the value coming from the sensor


long sensor1Readings[10];
long sensor2Readings[10];
long sensor3Readings[10];
long sensor0Readings[10];

bool arraysFilledTo100 = false;
int arrayFillingCounter = 1;


void setup() {
  Serial.begin(9600); //sets serial port for communication
}

long powerOf2(long value) {
	
  return value * value;
}

void pushValueToArray(long newValue,long array[10]) {
	
  
  for (int i = 9; i > -1; i--) {
    if (i == 0) {
      array[i] = newValue;
    } else {
      array[i] = array[i - 1];
    }
  }

}

float calculateArrayMean(long array[10]) {
  long arraySumma = 0L;
  float arrayMean = 0.0;
  
  for (int i = 10; i > 0; i--) {
   	  arraySumma = arraySumma + array[i-1];

  }
  
  arrayMean = arraySumma / 10;
  
  //Serial.println("ARRAY MEAN"); 
  //Serial.println(arrayMean); 
  return arrayMean;
}


float calculateArrayVariance(float arrayMean, long array[10]) {

  
  long arrayPowSumma = 0.0;
  float arrayVariance = 0.0;

  for (int i = 10; i > 0; i--) {
   	  arrayPowSumma = arrayPowSumma + calculateMeanDistance(arrayMean, array[i-1]);
  }
  
  Serial.println("ARRAY VARIANCE"); 
  Serial.println(arrayPowSumma / 4); 
}

float calculateMeanDistance(float mean,float value) {
  float distance = 0.0;
  
  if(value > mean) {
  	distance = value - mean;
  }
  
  if(value <= mean) {
  	distance = mean - value;
  }
  
  
  return distance;
}

void loop()
{
  
   // CALCULATING CURRENT MEAN AND VARIANCE
	
  //float currentSensorMean = 0.0;
  //float currentSensorVariance = 0.0;
  //int summa = 0;
  //long powSumma = 0L;  
  
  //summa = sensorValue0 + sensorValue1 + sensorValue2 + sensorValue3;
  
  //currentSensorMean = summa / 4;  

  //currentSensorVariance = powSumma / 4;
  //long sPow0 = powerOf2(calculateMeanDistance(currentSensorMean,sensorValue0));
  //long sPow1 = powerOf2(calculateMeanDistance(currentSensorMean,sensorValue1));
  //long sPow2 = powerOf2(calculateMeanDistance(currentSensorMean,sensorValue2));
  //long sPow3 = powerOf2(calculateMeanDistance(currentSensorMean,sensorValue3));


  //powSumma = sPow0 + sPow1 + sPow2 + sPow3;
  //currentSensorVariance = powSumma / 4;
 
  //Serial.println("ALL SENSOR MEAN"); //prints the values coming from the sensor on the screen
  //Serial.println(currentSensorMean); 
  
  //Serial.println("ALL SENSOR VARIANCE"); //prints the values coming from the sensor on the screen
  //Serial.println(currentSensorVariance); 

 // read the value from the sensor:
  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);


 //PUSHING NEW VALUES TO ARRAYS
	
  if(arraysFilledTo100 == true) {
	pushValueToArray(sensorValue0,sensor0Readings);
   //pushValueToArray(sensorValue1,sensor1Readings);
   //pushValueToArray(sensorValue2,sensor2Readings);
   //pushValueToArray(sensorValue3,sensor3Readings);    
    
    Serial.println("ARRAY VARIANCE"); 
    calculateArrayVariance(calculateArrayMean(sensor0Readings), sensor0Readings);
	


  } 
  else if(arrayFillingCounter == 10) {
    arraysFilledTo100 = true;
  } else {
    
  	sensor1Readings [arrayFillingCounter] = sensorValue1;
  	//sensor2Readings [arrayFillingCounter] = sensorValue2;
  	//sensor3Readings [arrayFillingCounter] = sensorValue3;
  	//sensor0Readings [arrayFillingCounter] = sensorValue0;

	Serial.println(arrayFillingCounter); 
	arrayFillingCounter++;
  }

  delay(100); 
  
}