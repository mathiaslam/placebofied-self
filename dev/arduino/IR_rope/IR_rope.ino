#define IRsensorPin 9
#define IRledPin 10
#define D13ledPin 13 

int counter = 0;
int placebo = -5;
int placeboCount = 0;

void IR38Write() {
  for(int i = 0; i <= 384; i++) {
    digitalWrite(IRledPin, HIGH);
    delayMicroseconds(13);
    digitalWrite(IRledPin, LOW);
    delayMicroseconds(13);
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(IRledPin, OUTPUT);
  digitalWrite(IRledPin, LOW);
  pinMode(D13ledPin, OUTPUT);
  digitalWrite(D13ledPin, LOW);
}
 
void loop(){
  IR38Write();
  if (digitalRead(IRsensorPin)==LOW){
    digitalWrite(D13ledPin, HIGH);
  } else {
    digitalWrite(D13ledPin, LOW);
    if (placeboCount >= 10) {
      counter += placebo;
      placeboCount = 0;
      Serial.write(counter);
      } else {
        counter++;
        placeboCount++;
        }
    Serial.println(counter);
  }


  delay(300);
}
