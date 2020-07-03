#include <TimeLib.h>
#include <Wire.h>
#include <SSD1306.h>
#include "DHT.h"
#define DHTPIN 2  // D9-Data
#define DHTTYPE DHT11

typedef void (*Frame)();
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int hr = 1;   //출력할 때의 시
int minutE = 0; //출력할 때의 분
int sec = 0;    // 출력할 때의 초
int alarmHr = 1;
int alarmMin = 0;
int STWmin = 0;
int STWsec = 0;
int Mode=0;
int count=0;    // blink와 delay를 위해서 사용
char *Week[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
int dayOfWeek=0;

#define frameLength 12;
SSD1306 display(0x3c, D14, D15);//SDA,SCL
DHT dht(DHTPIN, DHTTYPE);

// utility function for digital clock display: prints leading 0
String twoDigits(int digits){
  if(digits < 10) {
    String i = '0'+String(digits);
    return i;
  }
  else {
    return String(digits);
  }
}

void drawButton() {
  // Mode button
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0,0, "MODE" );
  // Adjust button
  display.fillRect(0, 54, 10, 64);
  // Triangle-shaped button
  for (int i = 1; i <= 9; i++) {
      int k=i/2;
      for (int j=0; j<=k; j++){
        display.setPixel(123+j,i);
        display.setPixel(123-j,i);
      }
    }
  // Upper-Triangle-shaped button
  for (int i = 1; i <= 9; i++) {
      int k=i/2;
      for (int j=0; j<=k; j++){
        display.setPixel(123+j,64-i);
        display.setPixel(123-j,64-i);
      }
    }
}

void basicFrame(){
}

void changeWeek(){
  display.drawHorizontalLine(1, 44, 20);   // 밑줄 추가
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode++;
     }
     else if(ch2=='2'){
      Mode=0;
     }
     else if(ch2 == '3'){ // 시간 증가
        dayOfWeek++;
     }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        dayOfWeek--;
     }
  }
}

void changeHrFrame(){
  display.drawHorizontalLine(26, 44, 20);   // 밑줄 추가
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode++;
     }
     else if(ch2=='2'){
      Mode=0;
     }
     else if(ch2 == '3'){ // 시간 증가
        hr++;
     }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        hr--;
     }
  }
}

void changeMinFrame(){
  display.drawHorizontalLine(56, 44, 20);   // 밑줄 추가
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode++;
     }
     else if(ch2=='2'){
        Mode=0;
      }
       else if(ch2 == '3'){ // 시간 증가
        minutE++;
      }
     else if(ch2=='4'){  // 시간 감소
        minutE--;
      }
  }
}
void changeSecFrame(){
  display.drawHorizontalLine(86, 44, 20);   // 밑줄 추가
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode++;
     }
     else if(ch2=='2'){
        Mode=0;
      }
     if(ch2 == '3'){ // 시간 증가
        sec++;
   }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        sec--;
     }
  }
}

void changeAlarmHr(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "ALM" );
  display.drawString(66, 50, String(alarmHr) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(alarmMin));
  display.drawHorizontalLine(68, 62, 10);
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode++;
     } 
     else if(ch2 == '3'){ // 시간 증가
        alarmHr++;
   }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        alarmHr--;
     }
  }
}

void changeAlarmMin(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "ALM" );
  display.drawString(66, 50, String(alarmHr) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(alarmMin));
  display.drawHorizontalLine(82, 62, 10);   // 밑줄 추가
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode = Mode+2;
     } 
     else if(ch2=='2'){
      Mode++;
      }
     else if(ch2 == '3'){ // 시간 증가
        alarmMin++;
   }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        alarmMin--;
     }
    }
}

void alarm(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "ALM" );
  display.drawString(66, 50, String(alarmHr) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(alarmMin));
  display.setColor(WHITE);    // 알람을 설정했을 시
  display.drawCircle(100,56,4);
  display.display();
  if ((hr == alarmHr) && (minutE == alarmMin)){ // 알람시간 도착했을 때
      display.fillCircle(100,56,4);
      display.display();
    }
    
  if(Serial.available()){
    char ch2 = Serial.read();
    Serial.println(ch2);
    if(ch2=='1'){
      Mode++;
     }
     else if(ch2=='2'){
      Mode = 0;
     }
  }
}

void STWstart(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "STW" );
  display.drawString(66, 50, String(STWmin) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(STWsec));

  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){    // 다음 모드로 넘어감
      Mode = Mode + 2;
     } 
     else if(ch2=='2'){ // 스톱워치 시작
      Mode++;
      }
    }
}

void STWstop(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "STW" );
  display.drawString(66, 50, String(STWmin) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(STWsec));
  display.display();

  while(true){
  if(count%2==1){
    STWsec++;
    }
    count++;
    break;
  }
  if(STWsec>=60){
    STWsec=0;
    STWmin++;
  }
  
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){    // 다음 모드로 넘어감
      Mode++;
     } 
     else if(ch2=='2'){  // 스톱워치 중지
      Mode--;
      }
    }
}

void changeTimerMin(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "TIM" );
  display.drawString(66, 50, String(alarmHr) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(alarmMin));
  display.drawHorizontalLine(68, 62, 10);
  
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){    // 다음 모드로 넘어감
      Mode++;
     } 
      else if(ch2 == '3'){ // 시간 증가
        alarmHr++;
   }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        alarmHr--;
     }
    }
}

void changeTimerSec(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "TIM" );
  display.drawString(66, 50, String(alarmHr) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(alarmMin));
  display.drawHorizontalLine(82, 62, 10);   // 밑줄 추가
  
  display.display();
  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){    // 다음 모드로 넘어감
      Mode = (Mode + 2) % frameLength;
     } 
     else if(ch2 == '2'){
      Mode++;
     }
      else if(ch2 == '3'){ // 시간 증가
        alarmMin++;
   }  // end of if(Serial.available())
     else if(ch2=='4'){  // 시간 감소
        alarmMin--;
     }
    }
}

void timer(){
  display.setFont(ArialMT_Plain_10);
  display.drawString(38, 50, "TIM" );
  display.drawString(66, 50, String(alarmHr) );
  display.drawString(78, 50, ":");
  display.drawString(82, 50, twoDigits(alarmMin));
  display.setColor(WHITE);    // 타이머를 설정했을 시
  display.drawCircle(100,56,4);
  display.display();
  // alarmHr=분, alarmMin=초
  while(true){
    if(count%2==1){
      alarmMin--;
      }
      count++;
      break;
  }
  if(alarmMin < 0){
    if(alarmHr > 0){
      alarmMin=59;
      alarmHr--;
    }
    else{
      alarmHr=0;
      alarmMin=0;
    display.fillCircle(100,56,4);
    display.display();
    }
  }

  if(Serial.available()){
     char ch2 = Serial.read();
     Serial.println(ch2);
     if(ch2=='1'){
      Mode = (Mode + 1) % frameLength;
     }
     else if(ch2=='2'){
      Mode = 0;
     }
  }
}

void setup() {
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();

  dht.begin();
}

Frame frames[] = {basicFrame, changeWeek, changeHrFrame, changeMinFrame, changeSecFrame, 
              changeAlarmHr, changeAlarmMin, alarm, STWstart, STWstop, changeTimerMin, changeTimerSec, timer};

void loop() {
  display.clear();
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  display.setFont(ArialMT_Plain_10);
  display.drawString(36, 8, String(h));
  display.drawString(48, 8, "%");
  display.drawString(66, 8, String(t));
  display.drawString(92, 8, "°C");
  display.drawString(1, 32, String(Week[dayOfWeek%7]));
  
  currentMillis = millis();
  if(currentMillis - previousMillis >=1000){
    previousMillis = currentMillis;
    sec++;
  }

  if(sec>=60){
    sec=0;
    minutE++;
  }
  if(sec<0){
    sec=59;
  }
  if(minutE>=60){
    minutE=0;
    hr++;
  }
  if(minutE < 0){
    minutE=59;
  }
  if( hr >= 24 ) {
    hr = 0;
    dayOfWeek++;
  }
  if( hr < 0){
    hr = 23;
  }
  if(alarmMin>=60){
    alarmMin=0;
  }
  if(alarmMin<0){
    alarmMin=59;
  }
  if(alarmHr<0){
    alarmHr=0;
  }
  drawButton();
  display.setFont(ArialMT_Plain_24);
  display.drawString(22, 20, String(hr));
  display.drawString(47, 20,(":"));
  display.drawString(52, 20, twoDigits(minutE));
  display.drawString(77, 20,(":"));
  display.drawString(82, 20, twoDigits(sec));  
  display.display();
  frames[Mode]();   // mode 실행
  if(Serial.available()){
     char ch = Serial.read();
     Serial.println(ch);
     if(ch == '1'){ //mode 변경
        Mode = (Mode + 1) % frameLength;
   }  // end of if(Serial.available())
  }
  delay(500);
}//끝
