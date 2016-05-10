#include <PololuLedStrip.h>

#define LED_COUNT 60

PololuLedStrip<12> ledStrip;
rgb_color colors[LED_COUNT];
String temp;
int temps[12];
int count = 0;

//sets up the initial arduino
void setup() {
    //open serial
    Serial.begin(115200);
    //initializes the temps array
    for (int i = 0; i < 12; i++) {
        temps[i] = 0;
    }
    while (!Serial);
}

void setTemps() {
    //all temperatures already received
    if (count >= 12)
        return;
    //wait for serial
    while (!Serial.available()) {}
    while (Serial.available()) {
        char c = Serial.read();
        //spaces separate out the temperatures
        if (c == ' ') {
            if (temp.length() != 0) {
                //converts serial reads to ints
                double t = (double)temp.toInt();
                //scales and stores temperatures
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
    //fill in the temps array
    setTemps();
    //convert from temperatures to colors for the LEDs
    for (int i = 0; i < 12; i++) {
        colors[5*i+0] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+1] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+2] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+3] = (rgb_color){255, 255-temps[i], 0};
        colors[5*i+4] = (rgb_color){255, 255, 255};
    }
    //write out colors to the LEDs
    ledStrip.write(colors, LED_COUNT);
    //debugging purposes
    /*Serial.print("Showing color: ");
    Serial.print(colors[0].red);
    Serial.print(",");
    Serial.print(colors[0].green);
    Serial.print(",");
    Serial.println(colors[0].blue);*/
}
