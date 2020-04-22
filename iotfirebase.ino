#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <jsmn.h>
#include <WiFi.h>

#define FIREBASE_HOST "https://iotfirebase-dbd63.firebaseio.com/"
#define FIREBASE_AUTH "MVYujfwGcL6KiD3gbesZp6zPcu83EuwWAhwbu775"
#define WIFI_SSID "Partikel Cabul"
#define WIFI_PASSWORD "jancukasu"

int led1 = 12;
int led2 = 13;

int ledTest = 23;

FirebaseData firebaseData;
String path = "/node1";

int button_Pin = 15;
int buttonState; 
int ldr = 35;
int ldrState;


void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void setup() {
  Serial.begin(115200);
  pinMode(button_Pin, INPUT_PULLUP);
  pinMode(ldr, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ledTest, OUTPUT);
  initWifi();
}

void loop() {
  
  buttonState = digitalRead(button_Pin);
  if(buttonState == 0)buttonState = 1;
  else buttonState = 0; //jika ditekan = 1, dilepas = 0
  
  ldrState = analogRead(ldr);

  if(buttonState == 1) {
    Firebase.setInt(firebaseData, path + "/joystick", 1);
    Firebase.setInt(firebaseData, path + "/led1", 1);
  }
  else {
    Firebase.setInt(firebaseData, path + "/joystick", 0);
    Firebase.setInt(firebaseData, path + "/led1", 0);
  }
  
  if(ldrState > 3999) {
    Firebase.setInt(firebaseData, path + "/ldr", ldrState);
    Firebase.setInt(firebaseData, path + "/led2", 1);
  }
  else {
    Firebase.setInt(firebaseData, path + "/ldr", ldrState);
    Firebase.setInt(firebaseData, path + "/led2", 0);
  }

  if(Firebase.getInt(firebaseData, path + "/led1")){
    if(firebaseData.intData() == 0)
      digitalWrite(led1,LOW);
    else
      digitalWrite(led1,HIGH);   
  }
 if(Firebase.getInt(firebaseData, path + "/led2")){
    if(firebaseData.intData() == 0)
      digitalWrite(led2,LOW);
    else
      digitalWrite(led2,HIGH);   
  }
  
  if(Firebase.getInt(firebaseData, path + "/ledTest")){
    if(firebaseData.intData() == 0)
      digitalWrite(ledTest,LOW);
    else
      digitalWrite(ledTest,HIGH);   
  }
  
  Serial.print("Button: ");Serial.print(buttonState);
  Serial.print(" | LDR: ");Serial.println(ldrState);
}
