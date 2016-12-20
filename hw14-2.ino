// 引用ESP8266 Library
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// 引用 Servo Library
#include <Servo.h> 

// 建立一個 Servo 物件 
Servo myservo; 
 
#define SSID "Toosla"                                   
#define PASS "110419036"     

ESP8266WebServer server(80);

char led_status[200];
char Motor[50];
String webSite;

#define MotorPT 5

// 儲存旋轉角度的變數
int val;

void turnoff(){
  digitalWrite(MotorPT, LOW);
}

void buildWeb(){
  webSite += "<html>";
  webSite+="<head>\n";
  webSite+="<meta charset='UTF-8'/>\n";
  webSite+="<title>Form Control MOTOR</title>\n";
  webSite+="<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>";
  webSite+="<script>";
  webSite+="$(document).ready(function(){";
  webSite+="$(\"[type = range]\").change(function(){";
   webSite+="var motorval = $(\"#motor\").val();";
  webSite+="$(\"#motor-text\").text(motorval);";
  webSite+="});";
  webSite+="});";
  webSite+="</script>";
  webSite+="</head>\n";
  webSite += "<body>";
  webSite += "<h1>MOTOR Control form</h1>";
  webSite += "<form action=\"/form1\">";
  webSite += "<p>Motor : <span id = \"motor-text\">0</span></p>";
  webSite += "<input type=\"range\" id=\"motor\" name=\"motor-led\" min=\"0\" max=\"255\" value=\"0\"><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</body></html>";
}

void handleRoot(){
  server.send(200,"text/html",webSite);
}

void ColorPicker(){
  int motor_color = server.arg("motor-led").toInt();
  
  analogWrite(MotorPT,motor_color);
  
  server.send(200,"text/html",webSite);

}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  
  Serial.begin(115200);
  // put your setup code here, to run once:
  turnoff();
  buildWeb();
  WiFi.begin(SSID, PASS); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  server.on("/",handleRoot);
  server.on("/form1",ColorPicker);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println(WiFi.localIP());  
  myservo.attach(5);
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
  val = analogRead(MotorPT);            // 讀取可變電阻(數值介於 0 到 1023)
  val = map(val, 0, 1023, 0, 179);     // 把 0 - 1023 的數值按比例縮放為 0 - 180 的數值
  myservo.write(val);                  // 設定 Servo 旋轉角度
  delay(15);                           // 等待 Servo 旋轉指定的位置
}


