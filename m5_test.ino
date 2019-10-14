
#include <M5Stack.h>
#include "Ambient.h" // Ambientのヘッダーをインクルード

WiFiClient client;
Ambient ambient; // Ambientオブジェクトを定義

const char* ssid = "HG8045-856B-bg";
const char* password = "dr3xefhb";

unsigned int channelId = 14764; // AmbientのチャネルID
const char* writeKey = "240e08888ee53abb"; // ライトキー


#define IR_pin 36 //センサーのピン番号



void setup(){
    M5.begin();
    M5.Lcd.printf("IR test\r\n"); // LCD display
    pinMode(IR_pin, INPUT);

    
    WiFi.begin(ssid, password);  //  Wi-Fi APに接続
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(100);
    }
    Serial.print("WiFi connected\r\nIP address: ");
    Serial.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化
    
    
    
}

void loop() {

    int IR_data= 0;
    
    // IRセンサからのanalog出力を読み込む
    IR_data = analogRead(IR_pin);
    
    M5.Lcd.printf("IR_data=%d\r\n",IR_data);

    ambient.set(1, IR_data);
    ambient.send();
    

    delay(1000);
}
