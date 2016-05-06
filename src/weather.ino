#include <PololuLedStrip.h>

#define LED_COUNT 60

PololuLedStrip<20> ledStrip;
rgb_color colors[LED_COUNT];
String temp;
int temps[20];
int count = 0;
int set = 0;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 20; i++) {
        temps[i] = 0;
    }
    while (!Serial);
}

void setTemps() {
    if (count >= 20)
        return;
    while (!Serial.available());
    while (Serial.available() > 0) {
        char c = Serial.read();
        if (c == ' ') {
            if (temp.length() != 0) {
                Serial.print(temp);
                double t = (double)temp.toInt();
                t = t / 120.0 * 255.0;
                if (t > 255.0)
                    t = 255.0;
                temps[count] = (int)t;
                count++;
            }
            temp = "";
            continue;
        }
        temp += c;
    }
}

void loop() {
    if (set == 1)
        return;
    setTemps();
    for (int i = 0; i < 20; i++) {
        colors[3*i+0] = (rgb_color){255, 255-temps[i], 0};
        colors[3*i+1] = (rgb_color){255, 255-temps[i], 0};
        colors[3*i+2] = (rgb_color){255, 255-temps[i], 0};
    }
    ledStrip.write(colors, LED_COUNT);
    set = 1;
    delay(20);
}
