#include <Arduino.h>

#define LED_ESP 4

#define ESP_RX 18
#define ESP_TX 17

HardwareSerial ArduinoSerial(1);

void setup() {
    pinMode(LED_ESP, OUTPUT);
    digitalWrite(LED_ESP, LOW);

    // Serial Monitor trên máy tính
    Serial.begin(115200);

    // UART giao tiếp với Arduino
    ArduinoSerial.begin(
        9600,
        SERIAL_8N1,
        ESP_RX,
        ESP_TX
    );

    Serial.println("ESP32-S3 READY");
    Serial.println("Nhap:");
    Serial.println("1 = bat LED ben Arduino");
    Serial.println("0 = tat LED ben Arduino");
}

void loop() {

    // =================================
    // PC -> ESP32 -> Arduino
    // =================================
    if (Serial.available()) {
        char cmd = Serial.read();

        if (cmd == '1' || cmd == '0') {

            ArduinoSerial.write(cmd);

            Serial.print("ESP32 gui Arduino: ");
            Serial.println(cmd);
        }
    }

    // =================================
    // Arduino -> ESP32
    // =================================
    if (ArduinoSerial.available()) {

        char cmd = ArduinoSerial.read();

        if (cmd == '1') {

            digitalWrite(LED_ESP, HIGH);

            Serial.println("Arduino yeu cau:");
            Serial.println("LED ESP32 ON");
        }

        else if (cmd == '0') {

            digitalWrite(LED_ESP, LOW);

            Serial.println("Arduino yeu cau:");
            Serial.println("LED ESP32 OFF");
        }
    }
}