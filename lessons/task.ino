TaskHandle_t tTask1;
TaskHandle_t tTask2;

SemaphoreHandle_t mutex;

int count = 0;

void minhaTask1(void *pvParameters)
{
  Serial.print("Minha task1 está no core ");
  Serial.println(xPortGetCoreID());
  while (true)
  {
    xSemaphoreTake(mutex, portMAX_DELAY);
    count = count - 2;
    xSemaphoreGive(mutex);
    delay(15000);
  }
}

void minhaTask2(void *pvParameters)
{
  Serial.print("Minha task2 está no core ");
  Serial.println(xPortGetCoreID());
  while (true)
  {
    xSemaphoreTake(mutex, portMAX_DELAY);
    count = count - 3;
    xSemaphoreGive(mutex);
    delay(30000);
  }
}

void setup()
{
  Serial.begin(115200);

  mutex = xSemaphoreCreateMutex();
  if (mutex == NULL)
  {
    Serial.println("Ops, nao criei essa parada ai");
  }

  xTaskCreatePinnedToCore(
      minhaTask1,   // task function
      "MinhaTask1", // task name
      10000,        // Task stack size
      NULL,         // task parameters
      1,            // task priority
      &tTask1,      // task handle
      0);           // task core (core 1=loop)

  xTaskCreatePinnedToCore(
      minhaTask2,   // task function
      "MinhaTask2", // task name
      10000,        // Task stack size
      NULL,         // task parameters
      1,            // task priority (1=highest, 4=lowest)
      &tTask2,      // task handle
      1);           // task core (core 1=loop)
}

// o loop roda core 1
void loop()
{
  xSemaphoreTake(mutex, portMAX_DELAY);
  count = count + 1;
  xSemaphoreGive(mutex);
  Serial.println(count);
  delay(5000);
}