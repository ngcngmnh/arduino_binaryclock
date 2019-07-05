/*
An open-source binary clock for Arduino. 
Based on the code from by Rob Faludi (http://www.faludi.com) and Daniel Spillere Andrade (www.danielandrade.net)
Code under (cc) by (ngcngmnh)
http://creativecommons.org/license/cc-gpl
*/

//thiết đặt ban đầu

int hour=12, minute=12, second=12; //giờ bắt đầu 12h:12':12''
int sec_unit, min_unit, session, hour12, min_b=0, hour_b=0; //sec_unit & min_unit: giây/phút hàng đơn vị, session: sáng/chiều, hour12: giờ hệ 12h, min_b & hour_b: nút chỉnh phút/giờ

void setup() {
//Serial.begin(9600); //test
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  //pinMode(14, OUTPUT); //xóa '//' khi dùng phần code ở cuối
  //pinMode(15, OUTPUT); //xóa '//' khi dùng phần code ở cuối
  pinMode(16, OUTPUT); //pin 14 đến 19 là A2 đến A5 (analog in), ở đây dùng pin A2>A5 để hiển thị giờ
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  //thiết đặt các pin OUTPUT: 7 cho giây, 7 cho phút, 4 cho giờ
}

//clock và hiển thị dạng binary clock

void loop() {

  //clock, mã nguồn từ Rob Faludi
  
    static unsigned long lastTick = 0;
    if (millis() - lastTick >= 1000) {
      lastTick = millis();
      second++;
    }

    //move forward one minute every 60 seconds
      if (second >= 60) {
        minute++;
        second = 0; //reset seconds to zero
      }

    //move forward one hour every 60 minutes
      if (minute >= 60) {
        hour++;
        minute = 0; //reset minutes to zero
      }
      
    //đi ngủ thôi :D
      if (hour >= 24) {
        hour = 0;
        minute = 0; //reset minutes to zero
      }

  //binary clock

    //seconds units
      sec_unit = second % 10; //lấy giây hàng đơn vị
      if (sec_unit == 1 || sec_unit == 3 || sec_unit == 5 || sec_unit == 7 || sec_unit == 9) {digitalWrite(3, HIGH);} else {digitalWrite(3, LOW);} //led giây đơn vị 2^0, dùng với pin 3
      if (sec_unit == 2 || sec_unit == 3 || sec_unit == 6 || sec_unit == 7) {digitalWrite(2, HIGH);} else {digitalWrite(2, LOW);} //led giây đơn vị 2^1
      if (sec_unit == 4 || sec_unit == 5 || sec_unit == 6 || sec_unit == 7) {digitalWrite(1, HIGH);} else {digitalWrite(1, LOW);} //led giây đơn vị 2^2
      if (sec_unit == 8 || sec_unit == 9) {digitalWrite(0, HIGH);} else {digitalWrite(0,LOW);} //led giây đơn vị 2^3

    //seconds
      if ((second >= 10 && second < 20) || (second >= 30 && second < 40) || (second >= 50 && second < 60)) {digitalWrite(4, HIGH);} else {digitalWrite(4, LOW);} // led giây h.chục 2^0, dùng với pin 4
      if (second >= 20 && second < 40) {digitalWrite(5, HIGH);} else {digitalWrite(5, LOW);} // led giây h.chục 2^1
      if (second >= 40 && second < 60) {digitalWrite(6, HIGH);} else {digitalWrite(6, LOW);} // led giây h.chục 2^2

    //minutes units
      min_unit = minute % 10; //lấy phút hàng đơn vị
      if (min_unit == 1 || min_unit == 3 || min_unit == 5 || min_unit == 7 || min_unit == 9) {digitalWrite(10, HIGH);} else {digitalWrite(10, LOW);} //led phút đơn vị 2^0, dùng với pin 10
      if (min_unit == 2 || min_unit == 3 || min_unit == 6 || min_unit == 7) {digitalWrite(9, HIGH);} else {digitalWrite(9, LOW);} //led phút đơn vị 2^1
      if (min_unit == 4 || min_unit == 5 || min_unit == 6 || min_unit == 7) {digitalWrite(8, HIGH);} else {digitalWrite(8, LOW);} //led phút đơn vị 2^2
      if (min_unit == 8 || min_unit == 9) {digitalWrite(7, HIGH);} else {digitalWrite(7, LOW);} //led phút đơn vị 2^3

    //minutes
      if ((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60)) {digitalWrite(11, HIGH);} else {digitalWrite(11, LOW);} //led phút h.chục 2^0, dùng với pin 11
      if (minute >= 20 && minute < 40) {digitalWrite(12, HIGH);} else {digitalWrite(12, LOW);} //led phút h.chục 2^1
      if (minute >= 40 && minute < 60) {digitalWrite(13, HIGH);} else {digitalWrite(13, LOW);} //led phút h.chục 2^2

    //hour_12h: chuyển về hệ 12h
      if (hour > 12) {hour12 = hour - 12;} else {hour12=hour;}

    //hours
      if (hour12 == 1 || hour12 == 3 || hour12 == 5 || hour12 == 7 || hour12 == 9 || hour12 == 11) {digitalWrite(16, HIGH);} else {digitalWrite(16, LOW);} //led giờ 2^0
      if (hour12 == 2 || hour12 == 3 || hour12 == 6 || hour12 == 7 || hour12 == 10 || hour12 == 11) {digitalWrite(17, HIGH);} else {digitalWrite(17, LOW);} //led giờ 2^1
      if (hour12 == 4 || hour12 == 5 || hour12 == 6 || hour12 == 7 || hour12 == 12) {digitalWrite(18, HIGH);} else {digitalWrite(18, LOW);} //led giờ 2^2
      if (hour12 == 8 || hour12 == 9 || hour12 == 10 || hour12 == 11 || hour12 == 12) {digitalWrite(19, HIGH);} else {digitalWrite(19, LOW);} //led giờ 2^3

    //buttons (https://www.arduino.cc/en/Tutorial/Button)

      //nút chỉnh phút, +1 khi nhấn (giữ)
      min_b = analogRead(1); //đọc tín hiệu cổng A1
      if (min_b < 315) { //cái này giải thích dài dòng :((
        minute++;
        second = 0;
        delay(500); //delay để phút/giờ không thay dổi quá nhanh
      }

      //nút chỉnh giờ, +1 khi nhấn (giữ)
      hour_b = analogRead(0); //đọc tín hiệu cổng A0
      if (hour_b < 315) {
        hour++;
        second = 0;
        delay(500);
      }

//Serial.println(sec_unit); //test
//delay(1000);

/*bonus đoạn code dùng led thể hiện am/pm, phải đặt ngay trước '//hours', không thể dùng chung với '//buttons'

if (hour < 12) {digitalwrite(14, HIGH); digitalwrite(15, LOW)}
else {
  digitalwrite(15, HIGH); digitalwrite(14, LOW); //led màu khác nhau cho 2 pin 14, 15 (A0, A1)
}

*/

//end
}
