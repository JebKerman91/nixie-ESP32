#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "WiFi SSID";
const char* password = "WiFi PASSWORD";

WiFiUDP ntpUDP;  // https://github.com/arduino-libraries/NTPClient

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 7200*1000); // NTP Server, offset in s, update interval in ms

// ESP32 pin numbering
#define A1 1
#define B1 2
#define C1 3
#define D1 4
#define A2 11
#define B2 12
#define C2 13
#define D2 14
#define A3 21
#define B3 18
#define C3 17
#define D3 10
#define A4 9
#define B4 8
#define C4 7
#define D4 6

char A[4] = { A1, A2, A3, A4 };
char B[4] = { B1, B2, B3, B4 };
char C[4] = { C1, C2, C3, C4 };
char D[4] = { D1, D2, D3, D4 };

int hours;
int minutes;

int zero;
int one;
int two;
int three;

IPAddress ip;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(B4, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(D4, OUTPUT);

  // Set CPU freq (240, 160, 80, 40, 20, 10 MHz)
  setCpuFrequencyMhz(80);

  for (char i = 0; i < 4; i++) {
    digitalWrite(A[i], HIGH);
    digitalWrite(B[i], HIGH);
    digitalWrite(C[i], HIGH);
    digitalWrite(D[i], HIGH);
  }

  // WiFi
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    for (int i = 0; i <= 3; i++) {
      writenumber(i, 0);
    }
    delay(500);
    for (int i = 0; i <= 3; i++) {
      writenumber(i, 1);
    }
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  ip = WiFi.localIP();
  Serial.println(ip);

  for (int i = 0; i <= 3; i++) {
    writeByte(ip[i]);
    delay(4000);
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  hours = timeClient.getHours();  // Manual offset for missing timezone for now
  minutes = timeClient.getMinutes();

  Serial.print("Hours: ");
  Serial.println(hours);
  Serial.print("Minutes: ");
  Serial.println(minutes);

  zero = (hours / 10) % 10;
  one = hours % 10;
  two = (minutes / 10) % 10;
  three = minutes % 10;

  writenumber(0, zero);
  writenumber(1, one);
  writenumber(2, two);
  writenumber(3, three);

  Serial.println(ip[0]);

  delay(1000);
}

void writeByte(int a) {
  zero = 0;
  three = a % 10;
  two = a / 10 % 10;
  one = a / 100 % 10;

  Serial.println(zero);
  Serial.println(one);
  Serial.println(two);
  Serial.println(three);

  writenumber(0, zero);
  writenumber(1, one);
  writenumber(2, two);
  writenumber(3, three);
}

void writenumber(int a, int b) {
  switch (b) {
    case 0:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 9:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 8:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 7:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 6:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 5:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 4:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 3:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 2:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 1:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
  }
}

void off(int a) {
  digitalWrite(A[a], HIGH);
  digitalWrite(B[a], HIGH);
  digitalWrite(C[a], HIGH);
  digitalWrite(D[a], HIGH);
}
