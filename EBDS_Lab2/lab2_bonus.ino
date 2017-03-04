int rowNum[]={0,9,11,8,12,5,7,2};
int colNum[]={0,13,3,4,10,6};

int pattern_H[7][5]={
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,0,0,1}};
  
int pattern_e[7][5]={
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0},
  {0,1,0,0,0},
  {0,1,1,1,0}};
  
int pattern_l[7][5]={
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,1,1,0}};
  
int pattern_o[7][5]={
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0}};
  
int pattern_W[7][5]={
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {0,1,0,1,0}};
  
int pattern_r[7][5]={
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,1,0,1,0},
  {0,1,1,0,1},
  {0,1,0,0,0},
  {0,1,0,0,0}};
  
int pattern_d[7][5]={
  {0,0,0,1,0},
  {0,0,0,1,0},
  {0,0,0,1,0},
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0}};

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
  
  int i,j;
  
  int greyscale;
  int ambient;
  greyscale=analogRead(0);
  ambient=analogRead(1);
  delay(1);
  
  initial();
  
  if(greyscale>ambient)
  {
    shiftLeft(pattern_H);
    shiftLeft(pattern_e);
    shiftLeft(pattern_l);
    shiftLeft(pattern_l);
    shiftLeft(pattern_o);
    shiftLeft(pattern_W);
    shiftLeft(pattern_o);
    shiftLeft(pattern_r);
    shiftLeft(pattern_l);
    shiftLeft(pattern_d);
  }
  else
  {
    shiftRight(pattern_H);
    shiftRight(pattern_e);
    shiftRight(pattern_l);
    shiftRight(pattern_l);
    shiftRight(pattern_o);
    shiftRight(pattern_W);
    shiftRight(pattern_o);
    shiftRight(pattern_r);
    shiftRight(pattern_l);
    shiftRight(pattern_d);
  }
  
}

//初始化, 令led全滅.
void initial(){
  int i;
  
  for(i=1;i<=7;i++)
  {
    digitalWrite(rowNum[i],HIGH);
  }
  for(i=1;i<=5;i++)
  {
    digitalWrite(colNum[i],LOW);
  }
}

//顯示其中一個點.
void displayPoint(int row,int col)
{
  int i;
  
  initial();

  digitalWrite(colNum[col],HIGH);
  digitalWrite(rowNum[row],LOW);
  delay(1);
}

//按照開頭定義的點陣顯示patter.
void displayPattern(int pattern[7][5])
{
  int i,j,keep;
  for(keep=1;keep<=50;keep++)
  {
    for(i=1;i<=7;i++)
    {
      for(j=1;j<=5;j++)
      {
        if(pattern[i-1][j-1]==1)
        {
          displayPoint(i,j);
        }
      }
    }
  }
}

void shiftLeft(int pattern[7][5])
{
  int cycle,i,j;
  int patternCopy[7][5];
  
  for(i=1;i<=7;i++)
  {
    for(j=1;j<=5;j++)
    {
      patternCopy[i-1][j-1]=pattern[i-1][j-1];
    }
  }
  
  //顯示原pattern.
  displayPattern(pattern);
  delay(50);

  //讓pattern從右到左移動5格.
  for(cycle=1;cycle<=5;cycle++)
  {
    for(j=1;j<=5;j++)
    {
      for(i=1;i<=7;i++)
      {
        if(j<5)
        {
          patternCopy[i-1][j-1]=patternCopy[i-1][j];     //將新的pattern存入patternCopy.
        }
        else if(j==5)
        {
          patternCopy[i-1][j-1]=0;     //清空最後一列.
        }
      }
      
    }
    
    displayPattern(patternCopy);     //再顯示移動後的pattern.
    delay(50);
  }
}

void shiftRight(int pattern[7][5])
{
  int cycle,i,j;
  int patternCopy[7][5];
  
  for(i=1;i<=7;i++)
  {
    for(j=1;j<=5;j++)
    {
      patternCopy[i-1][j-1]=pattern[i-1][j-1];
    }
  }
  
  //顯示原pattern.
  displayPattern(pattern);
  delay(50);

  //讓pattern從左到右移動5格.
  for(cycle=1;cycle<=5;cycle++)
  {
    for(j=5;j<=1;j--)
    {
      for(i=1;i<=7;i++)
      {
        if(j>1)
        {
          patternCopy[i-1][j]=patternCopy[i-1][j-1];     //將新的pattern存入patternCopy.
        }
        else if(j==1)
        {
          patternCopy[i-1][j-1]=0;     //清空第一列.
        }
      }
      
    }
    
    displayPattern(patternCopy);     //再顯示移動後的pattern.
    delay(50);
  }
}