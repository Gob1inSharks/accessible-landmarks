#include <Wire.h>

#define SLAVE_ID 9

#define COLOR_GROUPS_NUM 4
#define COLOR_GROUPS_ID (int[]){22,32,23,33}
#define COLORS (int[]){1,3,1,3}

#define RED_LOWER_BOUND 0
#define RED_UPPER_BOUND 255

#define BLUE_LOWER_BOUND 0
#define BLUE_UPPER_BOUND 255

#define GREEN_LOWER_BOUND 0
#define GREEN_UPPER_BOUND 255

#define COLOR_SENSOR_DELAY_TIME 100

#define PIECES_NUM 2

int color_groups_pins[COLOR_GROUPS_NUM][5];
int colors[COLOR_GROUPS_NUM][3];
bool pieceFlag[PIECES_NUM*2];

int piecesInPlace = 0;

void assignColorPins() {

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    
    int current_id = COLOR_GROUPS_ID[i];

    color_groups_pins[i][0] = current_id + 0;
    pinMode(current_id + 0, OUTPUT);

    color_groups_pins[i][1] = current_id + 2;
    pinMode(current_id + 2, OUTPUT);

    color_groups_pins[i][2] = current_id + 4;
    pinMode(current_id + 4, OUTPUT);

    color_groups_pins[i][3] = current_id + 6;
    pinMode(current_id + 6, OUTPUT);

    color_groups_pins[i][4] = current_id + 8;
    pinMode(current_id + 8, INPUT);

    setFrequencyScalingTo20Percent(current_id);
  }
}

void setFrequencyScalingTo20Percent(int id){

  digitalWrite(id + 0,HIGH);
  digitalWrite(id + 2,LOW);

}

void setup() {

  Wire.begin(SLAVE_ID);
  Wire.onRequest(requestEvent);

  Serial.begin(9600);
  
  assignColorPins();
}

int getRedFrequencies(int id){

  digitalWrite(id + 4, LOW);
  digitalWrite(id + 6, LOW);

  delay(COLOR_SENSOR_DELAY_TIME);

  int redFrequency = pulseIn(id + 8, LOW);

  return redFrequency;
}

int getRedFrequenciesWithMapping(int id){

  digitalWrite(id + 4, LOW);
  digitalWrite(id + 6, LOW);

  delay(COLOR_SENSOR_DELAY_TIME);

  int redFrequency = pulseIn(id + 8, LOW);

  int redColorValue = map(redFrequency, RED_LOWER_BOUND, RED_UPPER_BOUND, 255, 0);

  return redColorValue;
}

int getBlueFrequencies(int id){

  digitalWrite(id + 4, LOW);
  digitalWrite(id + 6, HIGH);

  delay(COLOR_SENSOR_DELAY_TIME);

  int blueFrequency = pulseIn(id + 8, LOW);

  return blueFrequency;
}

int getBlueFrequenciesWithMapping(int id){

  digitalWrite(id + 4, LOW);
  digitalWrite(id + 6, HIGH);

  delay(COLOR_SENSOR_DELAY_TIME);

  int blueFrequency = pulseIn(id + 8, LOW);

  int blueColorValue = map(blueFrequency, BLUE_LOWER_BOUND, BLUE_UPPER_BOUND, 255, 0);

  return blueColorValue;
}

int getGreenFrequencies(int id){

  digitalWrite(id + 4, LOW);
  digitalWrite(id + 6, HIGH);

  delay(COLOR_SENSOR_DELAY_TIME);

  int greenFrequency = pulseIn(id + 8, LOW);

  return greenFrequency;
}

int getGreenFrequenciesWithMapping(int id){

  digitalWrite(id + 4, LOW);
  digitalWrite(id + 6, HIGH);

  delay(COLOR_SENSOR_DELAY_TIME);

  int greenFrequency = pulseIn(id + 8, LOW);

  int greenColorValue = map(greenFrequency, GREEN_LOWER_BOUND, GREEN_UPPER_BOUND, 255, 0);

  return greenColorValue;
}

void getAllColorFrequencies(){

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    colors[i][0] = getRedFrequencies(COLOR_GROUPS_ID[i]);
  }

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    colors[i][1] = getGreenFrequencies(COLOR_GROUPS_ID[i]);
  }

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    colors[i][2] = getBlueFrequencies(COLOR_GROUPS_ID[i]);
  }

}

void getAllColorFrequenciesWithMapping(){

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    colors[i][0] = getRedFrequenciesWithMapping(COLOR_GROUPS_ID[i]);
  }

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    colors[i][1] = getGreenFrequenciesWithMapping(COLOR_GROUPS_ID[i]);
  }

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    colors[i][2] = getBlueFrequenciesWithMapping(COLOR_GROUPS_ID[i]);
  }

}

void showColorsInSerial(){
  Serial.println("----------------------------------------------");
  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    for(int j = 0; j < 3; j++){
      Serial.print(colors[i][j]);
      Serial.print(",");
    } Serial.println();
  }
  Serial.println("----------------------------------------------");

  delay(100);
}

int colorCorrect(int color_id){

  int THRESHOLD = 50;

  int r = colors[color_id][0], g = colors[color_id][1], b = colors[color_id][2];
  
  if((r > g - THRESHOLD) && (r > b - THRESHOLD)){
    return 1;
  }else if((g > r - THRESHOLD) && (g > b - THRESHOLD)){
    return 2;
  }else if((b > r - THRESHOLD) && (b > g - THRESHOLD)){
    return 3;
  }

  return 0;
}

void updateFlags(){

  for(int i = 0; i < COLOR_GROUPS_NUM; i++){
    int color = colorCorrect(i);
    
    if(color = COLORS[i]){
      pieceFlag[i] = true;
    }else{
      pieceFlag[i] = false;
    }
  }
}

void updatePiecesInPlace(){

  updateFlags();
  piecesInPlace = 0;

  for(int i = 0; i < COLOR_GROUPS_NUM; i+=2){
    if(pieceFlag[i] && pieceFlag[i]){
      piecesInPlace ++;
    }
  }
}

void requestEvent() {

  Wire.write("<");
  switch (piecesInPlace) {
    case 1:
      Wire.write("1");
      break;
    case 2:
      Wire.write("2");
      break;
    case 3:
      Wire.write("3");
      break;
    case 4:
      Wire.write("4");
      break;
    default:
      Wire.write("0");
      break;
    }
  Wire.write(">");

}

void test() {
  
}

void loop() {

  getAllColorFrequencies();
  //getAllColorFrequenciesWithMapping();
  showColorsInSerial();
  
}
