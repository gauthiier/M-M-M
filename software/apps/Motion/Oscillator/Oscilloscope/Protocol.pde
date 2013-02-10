import processing.serial.*;

class Protocol {
  Serial port;  // The serial port
  Protocol() {;}
  
  int F, V, X, Xin;
  
  Protocol(Serial p) {
    port = p;
    port.bufferUntil('\n');
  }
  
  void processData() {
    String in = port.readStringUntil('\n');
    if(in != null){
      String[] t = splitTokens(in);
      F = int(t[0]);
      V = int(t[1]);
      X = int(t[2]);
      Xin = int(t[3]);
    }
  }
}
