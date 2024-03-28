/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// define colors
#define BLACK 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define TEAL 5
#define BLUE 6
#define INDIGO 7
#define VIOLET 8
#define BURGUNDY 9



// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define VECT_INCR 100 //the number of vector increments for direction vector

// Stores frequency read by the photodiodes
float redFrequency = 0;
float greenFrequency = 0;
float blueFrequency = 0;


// Max and min RGB readings for each colour
// Max distance is ~13cm from surface of coloured paper
float redFrequencyMin[3] = {90, 304, 59};
float redFrequencyMax[3] = {718, 866, 249};
float orangeFrequencyMin[3] = {39, 118, 26};
float orangeFrequencyMax[3] = {270, 456, 133};
float yellowFrequencyMin[3] = {34, 60, 18};
float yellowFrequencyMax[3] = {266, 397, 122};
float greenFrequencyMin[3] = {248, 150, 57};
float greenFrequencyMax[3] = {880, 791, 253};
float tealFrequencyMin[3] = {197, 99, 36};
float tealFrequencyMax[3] = {480, 469, 156};
float blueFrequencyMin[3] = {263, 96, 30};
float blueFrequencyMax[3] = {831, 698, 218};
float indigoFrequencyMin[3] = {214, 190, 54};
float indigoFrequencyMax[3] = {483, 526, 172};
float violetFrequencyMin[3] = {141, 117, 30};
float violetFrequencyMax[3] = {451, 486, 151};
float burgundyFrequencyMin[3] = {80, 176, 42};
float burgundyFrequencyMax[3] = {364, 506, 152};

float* colorFreqMin[10] = {0, redFrequencyMin, orangeFrequencyMin, yellowFrequencyMin, greenFrequencyMin, tealFrequencyMin, blueFrequencyMin, indigoFrequencyMin, violetFrequencyMin, burgundyFrequencyMin};
float* colorFreqMax[10] = {0, redFrequencyMax, orangeFrequencyMax, yellowFrequencyMax, greenFrequencyMax, tealFrequencyMax, blueFrequencyMax, indigoFrequencyMax, violetFrequencyMax, burgundyFrequencyMax};


float colorDirVect[10][3];
// float redDirVect[3];
// float orangeDirVect[3];
// float yellowDirVect[3];
// float greenDirVect[3];
// float tealDirVect[3];
// float blueDirVect[3];
// float indigoDirVect[3];
// float violetDirVect[3];
// float burgundyDirVect[3];

float colorTestArray[3];

// Stores the red. green and blue colors
// float redColor = 0;
// float greenColor = 0;
// float blueColor = 0;

// store the distances of test color from sample colors in this array
float colorDist[10] = {0};

//return distance between test point and stored color point
float color_dist(float colourFrequencyMin[3], float colourDirVect[3], float testArray[3]) {
  float colourMainVect[3];
  float calc_dist = 0;
  float min_dist = 0;
  for (int i = 0; i < VECT_INCR; i += 1) {
    // add the direction vector to the main vector
    for (int j = 0; j < 3; j += 1) { 
      colourMainVect[j] = colourFrequencyMin[j] + i * colourDirVect[j];
    }
    
    float sum = 0;
    float dist_squared[3] = {0, 0, 0};
    for (int i = 0; i < 3; i += 1) {
      dist_squared[i] = colourMainVect[i] - testArray[i];
      dist_squared[i] *= dist_squared[i]; // square the distance value
      sum += dist_squared[i];
    }
    
    calc_dist = sqrt((double) sum);
    if (min_dist < 1 || calc_dist < min_dist) {
      min_dist = calc_dist;
    }
  }
  Serial.print("returning color dist: ");
  Serial.println(min_dist);
  return min_dist;
}

float getAvgReading(int iterations) {
  int colSum = 0;
  for (int i = 0; i < iterations; i += 1) {
    int colFreq = pulseIn(sensorOut, LOW); // actly returns period in microseconds
    colSum += colFreq;
  }
  return float(colSum) / iterations;
}

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // vector eqtn of red = redFrequencyMin - t
  for (int i = RED; i < 10; i += 1) {
    for (int j = 0; j < 3; j += 1) {
      colorDirVect[i][j] = (colorFreqMax[i][j] - colorFreqMin[i][j]) / VECT_INCR;
      // redDirVect[i] = (redFrequencyMax[i] - redFrequencyMin[i]) / VECT_INCR;
      // greenDirVect[i] = (greenFrequencyMax[i] - greenFrequencyMin[i]) / VECT_INCR;
      // blueDirVect[i] = (blueFrequencyMax[i] - blueFrequencyMin[i]) / VECT_INCR;
    }
  }

  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  // redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // redColor = map(redFrequency, 70, 120, 255,0);
  // redColor = map(redFrequency, 85, 750, 255,0);
  
  redFrequency = getAvgReading(5);
  colorTestArray[0] = redFrequency;
  
  // Printing the RED (R) value
  // Serial.print("R = ");
  // Serial.print(redColor);
  // delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = getAvgReading(5);
  colorTestArray[1] = greenFrequency;
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  // greenColor = map(greenFrequency, 150, 850, 255, 0);
  
  
  // Printing the GREEN (G) value  
  // Serial.print(" G = ");
  // Serial.print(greenColor);
  // delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = getAvgReading(5);
  colorTestArray[2] = blueFrequency;
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  // blueColor = map(blueFrequency, 33, 240, 255, 0);
  
  // Printing the BLUE (B) value 
  // Serial.print(" B = ");
  // Serial.println(blueColor);
  // delay(100);

  // Serial.print("Rf = ");
  // Serial.print(redFrequency);
  // Serial.print(" Gf = ");
  // Serial.print(greenFrequency);
  // Serial.print(" Bf = ");
  // Serial.println(blueFrequency);
  // delay(100);

  // K-nearest neighbours
  for (int i = RED; i < 10; i += 1) { // start looping from RED (i.e. 1)
    colorDist[i] = color_dist(colorFreqMin[i], colorDirVect[i], colorTestArray);  
    // Serial.print("Closest color: ");
    // Serial.println(colorDist[i]);
  };

  float minDist = colorDist[RED];
  int closestColor = RED;
  for (int color = RED; color < 10; color += 1) {
    if (colorDist[color] < minDist) {
      minDist = colorDist[color];
      closestColor = color;
    }
  }

  // convert int color to output the actual name of the color
  if (closestColor == RED) {
    Serial.println("RED");
  }
  else if (closestColor == ORANGE) {
    Serial.println("ORANGE");
  }
  else if (closestColor == YELLOW) {
    Serial.println("YELLOW");
  }
  else if (closestColor == GREEN) {
    Serial.println("GREEN");
  }
  else if (closestColor == TEAL) {
    Serial.println("TEAL");
  }
  else if (closestColor == BLUE) {
    Serial.println("BLUE");
  }
  else if (closestColor == INDIGO) {
    Serial.println("INDIGO");
  }
  else if (closestColor == VIOLET) { 
    Serial.println("VIOLET");
  }
  else if (closestColor == BURGUNDY) {
    Serial.println("BURGUNDY");
  }

  // float redColorDist = color_dist(redFrequencyMin, redDirVect, colorTestArray);
  // float greenColorDist = color_dist(greenFrequencyMin, greenDirVect, colorTestArray);
  // float blueColorDist = color_dist(blueFrequencyMin, blueDirVect, colorTestArray);

  // Checks the current detected color and prints
  // // a message in the serial monitor
  // if(redColorDist < greenColorDist && redColorDist < blueColorDist){
  //     Serial.println(" - RED detected!");
  // }
  // else if(greenColorDist < redColorDist && greenColorDist < blueColorDist){
  //   Serial.println(" - GREEN detected!");
  // }
  // else if(blueColorDist < redColorDist && blueColorDist < greenColorDist){
  //   Serial.println(" - BLUE detected!");
  // }

  delay(3000);
}