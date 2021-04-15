#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2,1,0,4,5,6,7,3, POSITIVE);

String 1st_comment = "Producer :  IME 201301246   ";
String 2nd_comment = "            Jung Jong Woo   ";
char soundInputPin = 0;

const int RedLed = 3;
const int GreenLed = 5;
const int BlueLed = 6;

#define COLUMN_OF_STARTING_COMMENTS     0  //starting comment의 COLUMN 위치
#define LENGTH_OF_STARTING_COMMENTS    28  //starting comment의 문자열 길이

#define HEIGHT_OF_SERIAL_MORNITOR       2  //Serial mornitor의 높이
#define WIDTH_OF_SERIAL_MORNITOR       16  //Serial mornitor의 너비
#define MAX_MOVING                     13  //최대 이동가능 픽셀

#define DB_COLUMN                      14  //'DB'라는 문자가 들어갈 열 번호
#define FIRST_ROW                       0  //첫 번째 행 번호
#define FIRST_COLUMN                    0  //첫 번째 열 번호
#define SECOND_ROW                      1  //두 번째 행 번호

#define MIN_BRIGHT                      0  //최소 밝기
#define MAX_BRIGHT                     255 //최대 밝기

#define GREEN_MIN_BRIGHT                0  //GREEN의 최소 밝기
#define GREEN_MAX_BRIGHT               255 //GREEN의 최대 밝기

#define BLUE_MIN_BRIGHT                 0  //BLUE의 최소 밝기
#define BLUE_MAX_BRIGHT                255 //BLUE의 최대 밝기

#define RED_MIN_BRIGHT                  0  //RED의 최소 밝기
#define RED_MAX_BRIGHT                 255 //RED의 최대 밝기

#define SOUNDINPUT_COLUMN               9  //soundinput값이 들어갈 열 번호
#define SOUNDINPUT_ROW                  0  //soundinput값이 들어갈 행 번호
#define SOUNDLEVEL_COLUMN              11  //soundlevel값이 들어갈 열 번호
#define SOUNDLEVEL_ROW                  1  //soundlevel값이 들어갈 행 번호
#define STANDARD_NOISE_LEVEL            4  //기준 소음 레벨



void setup() {
  // put your setup code here, to run once:
  //-----------Starting comments on LCD Mornitor----------
  lcd.begin(WIDTH_OF_SERIAL_MORNITOR, HEIGHT_OF_SERIAL_MORNITOR);
  lcd.backlight();
  lcd.print("Mood Light with");
  lcd.setCursor(FIRST_COLUMN, SECOND_ROW);
  lcd.print("Noise Meter");
  delay(3000);
  lcd.clear();

  for(int j = COLUMN_OF_STARTING_COMMENTS; j <= LENGTH_OF_STARTING_COMMENTS; j++) {
    if(j == MAX_MOVING){
      delay(3000);
      break;
    };
    lcd.setCursor(FIRST_COLUMN, FIRST_ROW);
    for(int i = j; i< j + WIDTH_OF_SERIAL_MORNITOR; i++){
      lcd.print(1st_comment.charAt(i));
    };
    lcd.setCursor(FIRST_COLUMN, SECOND_ROW);
    for(int i = j; i< j + WIDTH_OF_SERIAL_MORNITOR; i++){
      lcd.print(2nd_comment.charAt(i));
    };
    delay(300);
  }

  lcd.clear();
  lcd.setCursor(FIRST_COLUMN, FIRST_ROW);
  lcd.print("Noise : ");
  lcd.setCursor(DB_COLUMN, FIRST_ROW);
  lcd.print("DB");
  lcd.setCursor(FIRST_COLUMN, SECOND_ROW);
  lcd.print("Noise Lv: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = MIN_BRIGHT; i <= MAX_BRIGHT; i++){
    int soundInput1 = analogRead(soundInputPin);
    int soundLevel1 = map(soundInput1, 50, 900, 0, 8);
    soundRead(soundInput1, soundLevel1);
    ledOutput(RED_MIN_BRIGHT, GREEN_MAX_BRIGHT, i);
    delay(10);
  };
  for(int i = MIN_BRIGHT; i <= MAX_BRIGHT; i++){
    int soundInput2 = analogRead(soundInputPin);
    int soundLevel2 = map(soundInput2, 50, 900, 0, 8);
    soundRead(soundInput2, soundLevel2);
    ledOutput(RED_MIN_BRIGHT, GREEN_MAX_BRIGHT - i, BLUE_MAX_BRIGHT);
    delay(10);
  };
  for(int i = MIN_BRIGHT; i <= MAX_BRIGHT; i++){
    int soundInput3 = analogRead(soundInputPin);
    int soundLevel3 = map(soundInput3, 50, 900, 0, 8);
    soundRead(soundInput3, soundLevel3);
    ledOutput(RED_MIN_BRIGHT, i, BLUE_MAX_BRIGHT);
    delay(10);
  };
  for(int i = MIN_BRIGHT; i <= MAX_BRIGHT; i++){
    int soundInput4 = analogRead(soundInputPin);
    int soundLevel4 = map(soundInput4, 50, 900, 0, 8);
    soundRead(soundInput4, soundLevel4);
    ledOutput(RED_MIN_BRIGHT, GREEN_MAX_BRIGHT, BLUE_MAX_BRIGHT - i);
    delay(10);
  };
}

void ledOutput(int Red, int Green, int Blue){
  analogWrite(RedLed, Red);
  analogWrite(GreenLed, Green);
  analogWrite(BlueLed, Blue);
}

void soundRead(int soundInput, int soundLevel){
  lcd.setCursor(SOUNTINPUT_COLUMN, SOUNDINPUT_ROW);
  lcd.print("    ");
  lcd.setCursor(SOUNDINPUT_COLUMN,SOUNDINPUT_ROW);
  lcd.print(soundInput);
  lcd.setCursor(FIRST_COLUMN, SECOND_ROW);
  lcd.print("Noise Lv: ");
  lcd.setCursor(SOUNDLEVEL_COLUMN, SOUNDLEVEL_ROW);
  lcd.print(soundLevel);
  if( soundLevel > STANDARD_NOISE_LEVEL ){
    ledOutput( RED_MAX_BRIGHT, GREEN_MIN_BRIGHT, BLUE_MIN_BRIGHT );
    lcd.setCursor( FIRST_COLUMN, SECOND_ROW );
    lcd.print("It's Too Loud!!!");
    delay(10000);
    lcd.setCursor( FIRST_COLUMN, SECOND_ROW);
    lcd.print("                ");
  };
}

