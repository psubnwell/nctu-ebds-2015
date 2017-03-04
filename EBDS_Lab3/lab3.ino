#include <Servo.h>
Servo myservo;
//Pin角宣告
int button = 2;
int vib = 3;
int touch = 4;
int mag = 5;

int pos = 0;			//馬達位置
int Direction = 0;		//馬達旋轉方向(順時針/逆時針)
int state = 0;			//紀錄磁鐵是否有在震動
int ButtonState = 0;		//按鈕總共可切換兩個state，一為bonus，一為基本功能
int ButtonState_Last = 0;	//紀錄loop上次讀到按鈕的state
int res;
int resPin = 0;

//各種state
const int 	MagMode = 0;
const int 	VibMode = 1;
const int 	ResMode = 1;
const int 	Non_ResMode = 0;
int 		RotateMode = 0;	//分辨磁鐵or Vibration mode

void setup()
{
	myservo.attach(9);
	pinMode(touch,INPUT);  
	pinMode(mag,INPUT);
	pinMode(vib,INPUT);
	pinMode(button,INPUT);
	attachInterrupt(1,blink,FALLING);
	Serial.begin(9600);
	analogReference(INTERNAL);
}

void loop()
{
	//若上次state為HIGH，這次state為LOW，表示按鈕按下去一次過
	if (ButtonState_Last==1 && digitalRead(button)==0)
		ButtonState = 1 - ButtonState;			//切換bonus或是基本功能
	
	ButtonState_Last = digitalRead(button);		//記錄此次button值給下次loop用
	
	if (ButtonState == Non_ResMode)
	{
		if(digitalRead(touch)==HIGH)
		{
			if (digitalRead(mag)==HIGH)
			{    
				//如果從震動切回磁鐵sensor，將改變旋轉方向
				//如果上次轉動也是磁鐵sensor所觸發，則不改變旋轉方向
				Change_Mode(MagMode);
				//轉動馬達
				run();
			}
			  
			else if (state!=0)
			{
				state = 0;
				Change_Mode(VibMode);
				run();
			}
			  
			else
				;
		  
		}
		else if (digitalRead(touch)==LOW)
		  ;
	}
	
	else if (ButtonState == ResMode)
	{
		res = analogRead(resPin)/5.7;
		myservo.write(res);
	}
	
}

void run()
{
    myservo.write(pos);
    
	if (pos==0)
		Direction = 0;
    else if (pos==180)
        Direction = 1;
    else
        Direction = Direction;
        
    if (Direction==0)
        pos += 1;
    else if (Direction==1)
        pos -= 1;
    
	delay(15);
}

void Change_Mode(int vib_or_mag)
{
	if (RotateMode == vib_or_mag)
		RotateMode = RotateMode;
    else if ( RotateMode == (1-vib_or_mag) )
    {
		RotateMode = vib_or_mag;
		Direction = 1 - Direction;
    }	
}

void blink()
{
	state++;
}
