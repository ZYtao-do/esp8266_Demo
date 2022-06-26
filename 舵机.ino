#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>
#include <Servo.h>

char auth[] = "e682c3a6a379";  // 添加设备是获得的secret key
char ssid[] = "HUAWEI Mate 30";
char pswd[] = "123456788";

Servo myservo;      // 初始化舵机对象

int ser_num;

// 新建组件对象
BlinkerButton Button1("led");
BlinkerNumber Number1("number-abc");
BlinkerButton Button2("open-door");
BlinkerSlider Slider1("real-time");

int counter = 0;

// 按下按键即会执行该函数
// 这个是led开关的回调函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// 这是控制舵机运动的回调函数
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    
    myservo.write(0);
    // delay control the spin time
    delay(3000);
    myservo.write(126);

    //myservo.write(0);
}

void Slider1_callback(int32_t value)
{
    ser_num = value;
    myservo.write(ser_num);
    Blinker.delay(100);
    BLINKER_LOG("get slider value: ", value);
}


// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

void setup() {
    // 初始化串口
    Serial.begin(9600);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

    // 初始化LED的IO
    // 将LED_BUILTIN口定义为输出模式
    pinMode(LED_BUILTIN, OUTPUT);
    // 默认启动时将led为熄灭状态
    digitalWrite(LED_BUILTIN, HIGH);
    
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Slider1.attach(Slider1_callback);

    // 初始化舵机并将其复位
    myservo.attach(2);  // connect the servo to pin
    //myservo.write(90);// Initial the spin angle to 0
}

void loop() {
    Blinker.run();
}                                                                                                                                                                                                                                   