int incomingByte = 0;
void setup() {
  // mở serial với baudrate 9600
  
  Serial.begin(9600);
}
void loop() {
  // đọc giá trị analog trên chân A0
 Serial.print("<data><Length> 0.0 </Length> <Width> 4.0 </Width> <Height> 4.0 </Height> <Weight> 0.2 </Weight> <Barcode> H35M8045AVV2 </Barcode> </data> \n");
 delay(5000);
 Serial.print("<data><Length> 65</Length> <Width> 65 </Width> <Height> 0.00 </Height> <Weight> 0.2 </Weight> <Barcode> H35M8045AVV2 </Barcode> <WV>0.5</WV></data> \n");
 delay(5000);
 Serial.print("<data><Length> 0.0 </Length> <Width>0.0 </Width> <Height> 65.0 </Height> <Weight> 0.0 </Weight> <Barcode> H35M8045AVV2 </Barcode> </data> \n");
 delay(5000);
  while(Serial.available()>0)
  {
    incomingByte =Serial.read();
    Serial.println(char(incomingByte));
  }

}
