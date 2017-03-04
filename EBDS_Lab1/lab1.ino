float tempC;
int temp;
int reading;
int tempPin = 0;

int number[10][7]={
  {12,8,4,6,7,11},
  {8,4},
  {12,8,6,7,3},
  {12,8,4,6,3},
  {8,4,11,3},
  {12,4,6,11,3},
  {12,4,6,7,11,3},
  {12,8,4},
  {12,8,4,6,7,11,3},
  {12,8,4,6,11,3}
};

void setup() {
  int i=0;
  
  Serial.begin(9600);
  analogReference(INTERNAL);
  for(i=2;i<=13;i++)
  {
      pinMode(i,OUTPUT);
  }
}

void loop() {
  int i=0;
  int shi;
  int ge;
  
  reading = analogRead(tempPin);
  tempC = reading/9.31;
  temp=ceil(tempC);
  Serial.println(temp);
  
  shi=temp/10;
  ge=temp%10;
  
  displayNumber(1,shi);
  delay(1);
  initial();
  displayNumber(0,ge);
  delay(1);
  initial();
}

void initial() {
  int i=0;
  
  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(2,HIGH);  // Pin 3,2,1,0 (controller) low.
  
  digitalWrite(5,LOW);  // Pin h (dot) low.
  
  for(i=0;i<=7;i++){
    digitalWrite(number[8][i],LOW);  // Pin a-g (nixietubes) low.
  }
}

void displayNumber(int wei, int num){
  int i;
  
  if(wei==0){
    digitalWrite(13,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(2,LOW);
  }
  else if(wei==1){
    digitalWrite(13,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(2,HIGH);
  }
  
  for(i=0;i<=6;i++){
      digitalWrite(number[num][i],HIGH);
  }
}