/* STD305D ZN1040 replacement

    (c) A.G.Doswell 22 November 2020

    full desciption on the webiste http:/www.andydoz.blogspot.com

*/

int pulseInt = INT0; // interrupt pin from tacho signal conditioning
volatile int pulseCount; // tacho pulse counter
long int oldMillis;
int RPM;
int seg_a = 3; //segment pin assignments
int seg_b = 4;
int seg_c = 5;
int seg_d = 6;
int seg_e = 7;
int seg_f = 8;
int seg_g = 9;
int NLSD = A1; // display digit pin assignments
int NMSD = A2;
int MSD = A3;
int number;

void setup() {
  pinMode (2, INPUT); // define pins
  pinMode (NMSD, OUTPUT);
  pinMode (NLSD, OUTPUT);
  pinMode (MSD, OUTPUT);
  for (int i = 3; i <= 9; i++) {
    pinMode (i, OUTPUT);
    digitalWrite(i, LOW);
  }
  attachInterrupt(pulseInt, pulseCounter, FALLING); // start interrupt running
  splashscreen ();// run splashscreen
  oldMillis = millis(); //  initial timer state
}

void loop() {
  if (millis() >= (oldMillis + 500)) { // count pulses for 500mS
    RPM = (pulseCount * 0.642); // convert pulses to rpm. Alter this figure to calibrate.
    pulseCount = 0; // reset
    oldMillis = millis();
  }
  number = (RPM % 10); //display RPM 
  digitalWrite (NLSD, HIGH);
  display7seg() ;
  digitalWrite (NLSD, LOW);
  number = (RPM / 10) % 10;
  digitalWrite (NMSD, HIGH);
  display7seg ();
  digitalWrite (NMSD, LOW);
  number = (RPM / 100) % 10;
  digitalWrite (MSD, HIGH);
  display7seg ();
  digitalWrite (MSD, LOW);
}

void pulseCounter()
{
  pulseCount++;
  return;
}

void display7seg () {
  switch (number) { // defines 7 segment pattern
    case 0:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, LOW);
      digitalWrite (seg_e, LOW);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, HIGH);
      break;
    case 1:
      digitalWrite (seg_a, HIGH);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, HIGH);
      digitalWrite (seg_e, HIGH);
      digitalWrite (seg_f, HIGH);
      digitalWrite (seg_g, HIGH);
      break;
    case 2:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, HIGH);
      digitalWrite (seg_d, LOW);
      digitalWrite (seg_e, LOW);
      digitalWrite (seg_f, HIGH);
      digitalWrite (seg_g, LOW);
      break;
    case 3:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, LOW);
      digitalWrite (seg_e, HIGH);
      digitalWrite (seg_f, HIGH);
      digitalWrite (seg_g, LOW);
      break;
    case 4:
      digitalWrite (seg_a, HIGH);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, HIGH);
      digitalWrite (seg_e, HIGH);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, LOW);
      break;
    case 5:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, HIGH);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, LOW);
      digitalWrite (seg_e, HIGH);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, LOW);
      break;
    case 6:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, HIGH);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, LOW);
      digitalWrite (seg_e, LOW);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, LOW);
      break;
    case 7:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, HIGH);
      digitalWrite (seg_e, HIGH);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, HIGH);
      break;
    case 8:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, LOW);
      digitalWrite (seg_e, LOW);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, LOW);
      break;
    case 9:
      digitalWrite (seg_a, LOW);
      digitalWrite (seg_b, LOW);
      digitalWrite (seg_c, LOW);
      digitalWrite (seg_d, HIGH);
      digitalWrite (seg_e, HIGH);
      digitalWrite (seg_f, LOW);
      digitalWrite (seg_g, LOW);
      break;
  }
  delay (2);
}

void splashscreen () {
  oldMillis = millis();
  while ((oldMillis + 2000) >= millis()) {
    digitalWrite (MSD, HIGH); //"S"
    number = 5;
    display7seg();
    digitalWrite (MSD, LOW); // "t"
    digitalWrite (NMSD, HIGH);
    digitalWrite (seg_a, HIGH);
    digitalWrite (seg_b, HIGH);
    digitalWrite (seg_c, HIGH);
    digitalWrite (seg_d, LOW);
    digitalWrite (seg_e, LOW);
    digitalWrite (seg_f, LOW);
    digitalWrite (seg_g, LOW);
    delay (2);
    digitalWrite (NMSD, LOW);
    digitalWrite (NLSD, HIGH);
    digitalWrite (seg_a, HIGH); //"d"
    digitalWrite (seg_b, LOW);
    digitalWrite (seg_c, LOW);
    digitalWrite (seg_d, LOW);
    digitalWrite (seg_e, LOW);
    digitalWrite (seg_f, HIGH);
    digitalWrite (seg_g, LOW);
    delay (2);
    digitalWrite (NLSD, LOW);
  }
  oldMillis = millis();
  while ((oldMillis + 2000) >= millis()) {
    digitalWrite (MSD, HIGH);
    number = 3;
    display7seg ();
    digitalWrite (MSD, LOW);
    digitalWrite (NMSD, HIGH);
    number = 0;
    display7seg();
    digitalWrite (NMSD, LOW);
    digitalWrite (NLSD, HIGH);
    number = 5 ;
    display7seg();
    delay (2);
    digitalWrite (NLSD, LOW);
  }
  oldMillis = millis();
  while ((oldMillis + 2000) >= millis()) {
    digitalWrite (MSD, HIGH);
    digitalWrite (seg_a, HIGH); // "D"
    digitalWrite (seg_b, LOW);
    digitalWrite (seg_c, LOW);
    digitalWrite (seg_d, LOW);
    digitalWrite (seg_e, LOW);
    digitalWrite (seg_f, HIGH);
    digitalWrite (seg_g, LOW);
    delay (2);
    digitalWrite (MSD, LOW); // "O"
    digitalWrite (NMSD, HIGH);
    number = 0;
    display7seg() ;
    delay (2);
    digitalWrite (NMSD, LOW); //"Z"
    digitalWrite (NLSD, HIGH);
    number = 2;
    display7seg() ;
    digitalWrite (NLSD, LOW);
  }
  oldMillis = millis();
  while ((oldMillis + 2000) >= millis()) {
    digitalWrite (MSD, HIGH);
    digitalWrite (seg_a, HIGH); //"V"
    digitalWrite (seg_b, LOW);
    digitalWrite (seg_c, LOW);
    digitalWrite (seg_d, LOW);
    digitalWrite (seg_e, LOW);
    digitalWrite (seg_f, LOW);
    digitalWrite (seg_g, HIGH);
    delay (2);
    digitalWrite (MSD, LOW);
    digitalWrite (NMSD, HIGH);
    number = 1;
    display7seg() ;
    digitalWrite (NMSD, LOW);
    digitalWrite (NLSD, HIGH);
    number = 0;
    display7seg() ;
    digitalWrite (NLSD, LOW);
  }
}
