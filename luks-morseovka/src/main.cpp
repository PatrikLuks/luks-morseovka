#include <Arduino.h>

#define LED_PIN 12
#define KRATCE '.'
#define DLOUZE '-'

#define TRV_KRATCE 200 // Delší trvání pro lepší viditelnost
#define TRV_DLOUZE 600
#define PAUZA 200 // Pauza mezi symboly v jednom písmenu
#define PAUZA_DELSI 600 // Pauza mezi písmeny
#define PAUZA_SLOVO 1000 // Pauza mezi slovy

const char *morseovka[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."};

bool text_vypsan = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void led_blikni(int pin, int trvani)
{
  digitalWrite(pin, HIGH);
  delay(trvani);
  digitalWrite(pin, LOW);
}

void morseovka_blikni(const char *vstupni_text)
{
  while (*vstupni_text)
  {
    if (*vstupni_text == KRATCE)
    {
      led_blikni(LED_PIN, TRV_KRATCE);
    }
    else if (*vstupni_text == DLOUZE)
    {
      led_blikni(LED_PIN, TRV_DLOUZE);
    }
    vstupni_text++;
    delay(PAUZA);
  }
}

void loop()
{
  if (!text_vypsan)
  {
    Serial.print("Zadejte text (a-z): ");
    text_vypsan = true;
  }

  if (Serial.available())
  {
    String vstupni_text = Serial.readString();
    
    for (int i = 0; i < (int)vstupni_text.length(); i++)
    {
      char znak = toupper(vstupni_text[i]);

      if (znak >= 'A' && znak <= 'Z')
      {
        int index = znak - 'A';
        morseovka_blikni(morseovka[index]);
        delay(PAUZA_DELSI);
      }
      else if (znak == ' ') // Detekce mezery pro slovo
      {
        delay(PAUZA_SLOVO);
      }
    }
    
    text_vypsan = false;
    Serial.println();
  }
}
