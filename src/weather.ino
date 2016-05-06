#include <PololuLedStrip.h>

#define LED_COUNT 60

PololuLedStrip<12> ledStrip;
rgb_color colors[LED_COUNT];
String temp;
int temps[12];
int count = 0;
int set = 0;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 12; i++) {
        temps[i] = 0;
    }
    while (!Serial);
}

void setTemps() {
    if (count >= 12)
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
    for (int i = 0; i < 12; i++) {
        colors[5*i+0] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+1] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+2] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+3] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+4] = (rgb_color){255, 255, 255};
    }
    ledStrip.write(colors, LED_COUNT);
    set = 1;
    delay(20);
}
