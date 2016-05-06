#include <PololuLedStrip.h>

#define LED_COUNT 60

PololuLedStrip<20> ledStrip;
rgb_color colors[LED_COUNT];
String temp;
int temps[20];
int count = 0;

void setup() {
    Serial.begin(9600);
    for (int j = 0; j < 20; j++) {
        temps[j] = 0;
    }
    while (!Serial);
}

void setTemps() {
    if (count >= 20)
        return;
    while (!Serial.available());
    while (Serial.available()) {
        if (Serial.available() > 0) {
            char c = Serial.read();;
        }
    }
    double t = (double)temp.toInt();
    t = t / 120.0 * 255.0;
    temps[count] = (int)t;
    #if (temp.length() > 0) {
    #    Serial.print("Arduino received ");
    #    Serial.println(temp);
    #}
    #delay(500);
    #char ard_sends = '1';
    #Serial.print("Adruino sends: ");
    #Serial.println(ard_sends);
    #Serial.print("\n");
    #Serial.flush();
}

void loop() {
    setTemps();
    for (int i = 0; i < 20; i++) {
        colors[3*i+0] = (rgb_color){255, 255-temps[i], 0};
        colors[3*i+1] = (rgb_color){255, 255-temps[i], 0};
        colors[3*i+2] = (rgb_color){255, 255-temps[i], 0};
    }
    ledStrip.write(colors, LED_COUNT)
    delay(20);
}
