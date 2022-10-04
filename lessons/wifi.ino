#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"

char *ssid = "Mi 9 SE";
char *pwd = "150118vini";

char *ntpServer = "pool.ntp.org";
long gmtOffset_sec = 0;
int daylightOffset_sec = 0;

time_t now;
struct tm timeinfo;

String serverName = "http://postman-echo.com/";

void connectWifi()
{
  Serial.println("Conectando...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" ");
  Serial.print("Conectado ao WiFi com o IP: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, pwd);
  connectWifi();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Acesso ao ntp falhou");
  }
}

float t = 12.0;
float u = 27.0;

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!getLocalTime(&timeinfo))
    {
      Serial.println("Acesso ao ntp falhou");
    }
    HTTPClient http_get;
    String tmp = serverName + "get?unx=" + time(&now) + "&temp=" + t + "&umi=" + u;
    http_get.begin(tmp.c_str());
    int httpCode = http_get.GET();

    if (httpCode > 0)
    {
      Serial.println(tmp);
      Serial.println(httpCode);
      String payload = http_get.getString();
      Serial.print("Resposta do server: ");
      Serial.println(payload);
    }
    else
    {
      Serial.println("Http error");
    }

    ////HTTP POST
    WiFiClient client;
    HTTPClient http_post;
    //"//http://postman-echo.com/post"
    String url = serverName + "post";
    http_post.begin(client, url);
    Serial.println("\nPOST");
    http_post.addHeader("Content-Type", "application/json");
    http_post.addHeader("x-api-key", "qwertyuiopasdfghjklzxcvbnm");
    String data = "{\"nome\":38972142176126, \"temp\":24.5, \"umi\":80}";
    httpCode = http_post.POST(data);
    if (httpCode > 0)
    {
      Serial.println(httpCode);
      String payload = http_post.getString();
      Serial.print("Resposta do server: ");
      Serial.println(payload);
    }
    else
    {
      Serial.println("Http error");
    }
  }
  else
  {
    Serial.println("Na FATEC nunca tem internet");
    connectWifi();
  }
  t = t + 0.25;
  u = u + 0.11;
  delay(30000);
}
1