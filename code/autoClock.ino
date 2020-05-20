#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#include <Blinker.h>
#include <Servo.h>

Servo myservo_left;//定义左按键舵机
Servo myservo_right;//定义左按键舵机

char auth[] = "xxxxx";//设备key根据需要自行修改
char ssid[] = "xxxxx"; //WIFI名称
char pswd[] = "xxxxx"; //WIFI密码

// 新建组件对象
BlinkerButton Button1("btn-left");
BlinkerButton Button2("btn-right");


int counter = 0;


// 按下按键即会执行该函数,左按键
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    if (state=="on") 
    {
        myservo_left.write(160);//收到“on”的指令后舵机旋转
        Blinker.delay(2000);//延时
        myservo_left.write(90);//舵机归零垂直
         
        
    } else if(state=="press")
    {
       myservo_left.write(165);//长按开关按键后舵机旋转165°
       Blinker.delay(2000);//延时
       myservo_left.write(90);//舵机归零垂直
    }
        
}
//右按键
void button2_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
    if (state=="on") 
    {
        myservo_right.write(106);//收到“on”的指令后舵机旋转106°
        Blinker.delay(2000);//延时
        myservo_right.write(90);//舵机归零垂直
         
        
    } else if(state=="press")
    {
       myservo_right.write(75);//长按开关按键后舵机旋转
       Blinker.delay(2000);//延时
       myservo_right.write(90);//舵机归零垂直
    }
        
}
// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
 
}

void setup()
{
    // 初始化串口
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    // 初始化舵机
    myservo_left.attach(12);//舵机的IO口，nodemcu的D6口，左按键
    myservo_right.attach(13);//舵机的IO口，nodemcu的D6口,右按键
    myservo_left.write(90);//上电时左舵机归零垂直
    myservo_right.write(90);//上电时右舵机归零垂直
  BlinkerMIOT.attachPowerState(miotPowerState);//注册回调函数，反馈该控制状态
  
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);
    Button2.attach(button2_callback);

}

void loop() {
    Blinker.run();
}
