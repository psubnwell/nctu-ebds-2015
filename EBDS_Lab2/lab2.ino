void setup() {
  int i=0;
  Serial.begin(9600);
  analogReference(INTERNAL);
  for(i=0;i<=13;i++)
  {
      pinMode(i,OUTPUT);
  }
}

void loop() {
  
  int greyscale;
  int ambient;
  greyscale=analogRead(0);
  ambient=analogRead(1);
  //Serial.println("greyscale = %d",greyscale);
  //Serial.println("ambient = %d",ambient);
  delay(1);
  
  initial();
  if(greyscale>ambient)
  {
    displayLetter('L');
  }
  else
  {
    displayLetter('R');
  }
  
}

void initial(){
  int i;
  int rowNum[]={0,9,11,8,12,5,7,2};
  int colNum[]={0,13,3,4,10,6};
  for(i=1;i<=7;i++)
  {
    digitalWrite(rowNum[i],HIGH);
  }
  for(i=1;i<=5;i++)
  {
    digitalWrite(colNum[i],LOW);
  }
}

void displayPoint(int row,int col)
{
  int rowNum[]={0,9,11,8,12,5,7,2};
  int colNum[]={0,13,3,4,10,6};
  int i;
  
  initial();
  //digitalWrite(rowNum[row],LOW);
  /*
  for(i=1;i<=5;i++)
  {
    if(i==col)
    {
      ;
    }
    else
    {
      digitalWrite(colNum[i],LOW);
    }
  }
  */
  digitalWrite(colNum[col],HIGH);
  digitalWrite(rowNum[row],LOW);
  delay(1);
}

void displayLetter(char letter)
{
  switch(letter)
  {
  case 'L':
    displayPoint(1,1);
    displayPoint(2,1);
    displayPoint(3,1);
    displayPoint(4,1);
    displayPoint(5,1);
    displayPoint(6,1);
    displayPoint(7,1);
    displayPoint(7,2);
    displayPoint(7,3);
    displayPoint(7,4);
    displayPoint(7,5);
    break;
  case 'R':
    displayPoint(1,1);
    displayPoint(2,1);
    displayPoint(3,1);
    displayPoint(4,1);
    displayPoint(5,1);
    displayPoint(6,1);
    displayPoint(7,1);
    displayPoint(1,2);
    displayPoint(1,3);
    displayPoint(1,4);
    displayPoint(2,5);
    displayPoint(3,5);
    displayPoint(4,4);
    displayPoint(4,3);
    displayPoint(4,2);
    displayPoint(5,3);
    displayPoint(6,4);
    displayPoint(7,5);
    break;
  }
}

void shiftLeft()
{
    
}