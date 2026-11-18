#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <time.h>

// Preencha somente em uma copia privada. Sem credenciais, roda offline.
const char WRITE_KEY[] = "";
const char ROOT_CA[] = R"PEM(-----BEGIN CERTIFICATE-----
MIIDjjCCAnagAwIBAgIQAzrxQWQyZ/fubT8wVJM6MjANBgkqhkiG9w0BAQsFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH
MjAeFw0xMzA4MDExMjAwMDBaFw0zODAxMTUxMjAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IEcyMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuzfNNNx7a8myaJCtSnX/RrohCgiN9RlUyfuI
2/Ou8jqJkTx65qsGGmvPrC3oXgkkRLpimn7Wo6h+4FR1IAWsULecYxpsMNzaHxmx
1x7e/dfgy5SDN67sH0NO3Xss0r0upS/kqbitOtSZpLYl6ZtrAGCSYP9PIUkY92eQ
q2EGnI/yuum06ZIya7XzV+hdG82MHauVBJV8zUtluNJbd134/tJS7SsVQepj5Wz
tCO7TG1F8PapspUwtP1MVYwnSlcUfIKdzXOS0xZKBgyMUNGPHgm+F6HmIcr9g+UQ
vIOlCsRnKPZzFBQ9RnbDhxSJITRNrw9FDKZJobq7nMWxM4MphQIDAQABo0IwQDAP
BgNVHRMBAf8EBTADAQH/MA4GA1UdDwEB/wQEAwIBhjAdBgNVHQ4EFgQUTiJUIBiV
5uNu5g/6+rkS7QYXjzkwDQYJKoZIhvcNAQELBQADggEBAGBnKJRvDkhj6zHd6mcY
1Yl9PMWLSn/pvtsrF9+wX3N3KjITOYFnQoQj8kVnNeyIv/iPsGEMNKSuIEyExtv4
NeF22d+mQrvHRAiGfzZ0JFrabA0UWTW98kndth/Jsw1HKj2ZL7tcu7XUIOGZX1NG
Fdtom/DzMNU+MeKNhJ7jitralj41E6Vf8PlwUHBHQRFXGU7Aj64GxJUTFy8bJZ91
8rGOmaFvE7FBcf6IKshPECBV1/MUReXgRPTqh5Uykw7+U0b6LJ3/iyK5S9kJRaTe
pLiaWN0bfVKfjllDiIGknibVb63dDcY3fe0Dkhvld1927jyNxF1WW6LZZm6zNTfl
MrY=
-----END CERTIFICATE-----)PEM"; // PEM da CA raiz usada no prototipo
const int TRIG[] = {18, 25}, ECHO[] = {19, 26};
const int GREEN = 21, RED = 22;
const int EXPECTED_FIRST_SENSOR = 0; // 0 = A (sentido esperado A -> B); 1 = B (sentido esperado B -> A)
const uint32_t PASS_MS = 2500, BLOCK_MS = 5000, CLEAR_MS = 400;
struct Snapshot { int a, b, wrong, block; uint32_t wrongTotal, blockTotal; };
QueueHandle_t mailbox;
bool occupied[2]{};
int pending = -1;
uint32_t firstAt, bothAt, clearAt, wrongTotal, blockTotal;
bool wrong, block, bothTiming, clearTiming, armed;

int readCm(int i) {
  digitalWrite(TRIG[i], LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG[i], LOW);
  unsigned long us = pulseIn(ECHO[i], HIGH, 26000);
  int cm = (us + 29) / 58;
  return us && cm >= 2 && cm <= 400 ? cm : -1;
}

void publish(void*) {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin("Wokwi-GUEST", "", 6);
  configTime(0, 0, "pool.ntp.org", "time.google.com");
  uint32_t last = millis() - 60000U;
  uint32_t sentWrongTotal = 0, sentBlockTotal = 0;
  for (;;) {
    Snapshot s;
    if (WiFi.status() == WL_CONNECTED && time(nullptr) > 1700000000L && millis() - last >= 60000U &&
        xQueuePeek(mailbox, &s, 0) == pdTRUE) {
      last = millis();
      WiFiClientSecure tls;
      tls.setCACert(ROOT_CA);
      HTTPClient http;
      if (http.begin(tls, "https://api.thingspeak.com/update")) {
        http.setConnectTimeout(5000);
        http.setTimeout(5000);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String body = String("api_key=") + WRITE_KEY;
        body += "&field1=" + String(s.a);
        body += "&field2=" + String(s.b);
        bool wrongEvent = s.wrong || s.wrongTotal > sentWrongTotal;
        bool blockEvent = s.block || s.blockTotal > sentBlockTotal;
        body += "&field3=" + String(wrongEvent ? 1 : 0);
        body += "&field4=" + String(blockEvent ? 1 : 0);
        body += "&field5=" + String(s.wrongTotal);
        body += "&field6=" + String(s.blockTotal);
        int code = http.POST(body);
        long id = code == 200 ? http.getString().toInt() : 0;
        if (id > 0) {
          sentWrongTotal = s.wrongTotal;
          sentBlockTotal = s.blockTotal;
          Serial.printf("ThingSpeak: entrada %ld aceita | A=%d B=%d eventos=%d/%d totais=%lu/%lu\n", id, s.a, s.b, wrongEvent, blockEvent, (unsigned long)s.wrongTotal, (unsigned long)s.blockTotal);
        }
        else Serial.printf("ThingSpeak: escrita nao confirmada (HTTP %d)\n", code);
        http.end();
      }
    }
    delay(250);
  }
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 2; i++) {
    pinMode(TRIG[i], OUTPUT);
    pinMode(ECHO[i], INPUT);
  }
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  if (*WRITE_KEY && *ROOT_CA) {
    mailbox = xQueueCreate(1, sizeof(Snapshot));
    if (!mailbox || xTaskCreate(publish, "telemetry", 8192, nullptr, 1, nullptr) != pdPASS)
      Serial.println("Telemetria indisponivel; deteccao local ativa.");
  } else Serial.println("Modo local: configure chave e CA para publicar.");
}

void loop() {
  int a = readCm(0);
  delay(65);
  int b = readCm(1);
  uint32_t now = millis();
  bool valid = a >= 0 && b >= 0;
  if (valid) {
    bool prevA = occupied[0], prevB = occupied[1];
    occupied[0] = a <= (prevA ? 50 : 40);
    occupied[1] = b <= (prevB ? 50 : 40);
    bool riseA = occupied[0] && !prevA, riseB = occupied[1] && !prevB;
    bool clear = !occupied[0] && !occupied[1];
    if (clear) {
      if (!clearTiming) { clearAt = now; clearTiming = true; }
      if (now - clearAt >= CLEAR_MS) {
        wrong = block = false;
        pending = -1;
        armed = true;
      }
    } else clearTiming = false;

    if (pending >= 0 && now - firstAt > PASS_MS) pending = -1;
    if (riseA || riseB) {
      if (armed) {
        armed = false;
        if (riseA != riseB) { pending = riseA ? 0 : 1; firstAt = now; }
      } else if ((pending == 0 && riseB) || (pending == 1 && riseA)) {
        if (pending != EXPECTED_FIRST_SENSOR && !wrong) {
          wrong = true;
          ++wrongTotal;
          Serial.printf("CANDIDATO SIMULADO: CONTRAMAO (%c -> %c)\n", pending == 0 ? 'A' : 'B', pending == 0 ? 'B' : 'A');
        }
        pending = -1;
      }
    }

    if (occupied[0] && occupied[1]) {
      if (!bothTiming) { bothAt = now; bothTiming = true; }
      if (!block && now - bothAt >= BLOCK_MS) {
        block = true;
        ++blockTotal;
        Serial.println("CANDIDATO SIMULADO: BLOQUEIO");
      }
    } else bothTiming = false;
  } else {
    pending = -1;
    armed = clearTiming = bothTiming = false;
  }
  digitalWrite(RED, wrong || block || !valid);
  digitalWrite(GREEN, valid && !wrong && !block);
  Snapshot s{a, b, wrong, block, wrongTotal, blockTotal};
  if (mailbox) xQueueOverwrite(mailbox, &s);
  static uint32_t lastLog;
  if (now - lastLog >= 1000U) {
    lastLog = now;
    Serial.printf("A=%d B=%d cm | contramao=%d bloqueio=%d | totais=%lu/%lu\n",
                  a, b, wrong, block, (unsigned long)wrongTotal, (unsigned long)blockTotal);
  }
  delay(65);
}
