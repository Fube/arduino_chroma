const int X_pin = A0;
const int Y_pin = A1;

const int R = 11;
const int G = 10;
const int B = 9;

const int DELAY = 0;
const double V = 0.8;

int originX;
int originY;

void setup() {
  

  Serial.begin(9600);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  originX = analogRead(X_pin);
  originY = analogRead(Y_pin);
}

void setLights(double r, double g, double b){

  analogWrite(R, (int)r);
  analogWrite(G, (int)g);
  analogWrite(B, (int)b);
}

void resetLights(){
  setLights(LOW, LOW, LOW);
}

double * toRGB(double h, double s){

  double toRet[3];
  
  double C = s * V;
  double hPrime = h / 60;
  double X = C * (1 - abs(fmod(hPrime, 2) - 1));
  double M = V - C;

  if(h == 400){
    toRet[0] = 0;
    toRet[1] = 0;
    toRet[2] = 0;
  }
  else if(0 <= hPrime && hPrime <= 1){
    toRet[0] = C;
    toRet[1] = X;
    toRet[2] = 0;
  }
  else if(hPrime <= 2){
    toRet[0] = X;
    toRet[1] = C;
    toRet[2] = 0;
  }
  else if(hPrime <= 3){
    toRet[0] = 0;
    toRet[1] = C;
    toRet[2] = X;
  }
  else if(hPrime <= 4){
    toRet[0] = 0;
    toRet[1] = X;
    toRet[2] = C;
  }
  else if(hPrime <= 5){
    toRet[0] = X;
    toRet[1] = 0;
    toRet[2] = C;
  }
  else if(hPrime <= 6){
    toRet[0] = C;
    toRet[1] = 0;
    toRet[2] = X;
  }

  toRet[0] += (int)M;
  toRet[1] += (int)M;
  toRet[2] += (int)M;


  /**
   * DO NOT REMOVE THESE!
   * DO NOT TOUCH THIS FUNCTION IN ANY WAY SHAPE OR FORM!!
   * REMOVING THESE WILL BREAK THE CODE AND I HAVE NO IDEA WHY
   * THE LIGHTING ON THE LED WILL NOT WORK PROPERLY IF THESE PRINT STATEMENTS AREN'T HERE
   */
  Serial.print("R: ");
  Serial.println(toRet[0]);

  Serial.print("G: ");
  Serial.println(toRet[1]);

  Serial.print("B: ");
  Serial.println(toRet[2]);

  return toRet;
}

void loop() {

  /**
   * CHANGE THESE AT YOUR OWN RISK AND PERIL
   * I HAVE NO IDEA WHY THIS WORKS
   * I HAVE NO IDEA HOW THIS WORKS
   */

  int x = analogRead(X_pin) - originX;
  int y = analogRead(Y_pin) - originY;
  
  double hue;
  double saturation = sqrt(pow(x, 2) + pow(y, 2)) / 755;
  if(sqrt(pow(x, 2) + pow(y, 2)) <= 30){
    hue = 400;
  }else{
    hue = atan2((double)y, (double)x) * 180.0 / PI;
  }
  if(hue < 0){
    hue += 360;
  }

  double * RGB = toRGB(hue, saturation);
  setLights(RGB[0] * 255, RGB[1] * 255, RGB[2] * 255);
  
  delay(DELAY);
}
