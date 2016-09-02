

void writeDac(byte address, int val){
  byte val1 = val >> 8;
  byte val2 = val & 0xff;
  
  Wire.beginTransmission(address);
  Wire.write(val1);
  Wire.write(val2);
  Wire.endTransmission();

}
