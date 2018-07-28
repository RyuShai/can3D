int incomingByte = 0;
void setup() {
  // mở serial với baudrate 9600
  
  Serial.begin(9600);
}
void loop() {
  // đọc giá trị analog trên chân A0
 Serial.print("<data><Length> 26.0 <Length> <Width> 18.0 <Width> <Height> 0./0 <Height> <Weight> 0.2 <W/eight> <Barcode> H35M8045AVV2 <Barcode> </data> \n");
 delay(5000);
  while(Serial.available()>0)
  {
    incomingByte =Serial.read();
    Serial.println(char(incomingByte));
  }

}
