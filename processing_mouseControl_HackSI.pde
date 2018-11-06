import processing.serial.*;

int _LastSent_MouseX;
int _LastSent_MouseY;
int _Current_MouseX;
int _Current_MouseY;
int _WindowWidth;
int _WindowHeight;
int midWidth;
int midHeight;
Serial _SerialPort;

void setup() {
  _WindowWidth = 1600;
  midWidth = _WindowWidth/2;
  _WindowHeight = 800;
  midHeight = _WindowHeight/2;
  size( 1600, 800 );
  strokeWeight( 8 );
  //The serial port will have to be changed
  _SerialPort = new Serial(this, "/dev/cu.usbmodem14601", 9600);
  _SerialPort.bufferUntil('\n');
}

void draw() {
  background( 100 );
  stroke(255);
  ellipse( _Current_MouseX, _Current_MouseY, 8, 8 );
}

void mouseMoved() {
  _Current_MouseX = mouseX;
  _Current_MouseY = mouseY;
  SendToArduino();
}

void SendToArduino() {
  int new_MouseX=round(map(_Current_MouseX, 0, _WindowWidth, 0., 127.));
  int new_MouseY=round(map(_Current_MouseY, 0, _WindowHeight, 255., 127.));
   if (new_MouseX!=_LastSent_MouseX || new_MouseY!=_LastSent_MouseY) {
    _LastSent_MouseX = new_MouseX;
    _LastSent_MouseY = new_MouseY;
    print("X: "+new_MouseX+"\n");
    print("Y: "+new_MouseY+"\n");
    _SerialPort.write((byte)new_MouseX);
    _SerialPort.write((byte)new_MouseY);
  }
}

void serialEvent(Serial myPort)
{
  String myString = myPort.readStringUntil('\n');
  println(myString);
}
