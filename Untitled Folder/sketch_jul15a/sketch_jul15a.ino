void setup() {
  // mở serial với baudrate 9600
  Serial.begin(9600);
}
void loop() {
  // đọc giá trị analog trên chân A0
  Serial.print("0.0,0.0,0.0,0.0,barcode#\n");
  delay(30000);
  Serial.print("1.0,2.0,3.0,4.0,barcode#\n");
  delay(30000);
  Serial.print("4.5,5.0,7.5,3.0,barcode#\n");
  delay(30000);
  Serial.print("7.0,10.0,7.0,0.0,barcode#\n");
  delay(30000);
}
