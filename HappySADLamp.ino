#include <Adafruit_NeoPixel.h>

float lightLevel = 0;
float colorTemperature = 0;

int pinAddressable = 3;
int numberStrips = 16;
Adafruit_NeoPixel pixels(numberStrips, pinAddressable, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(115200);
	Serial.println("Start HappySADLamp");
	pixels.begin();
}

void checkLightLevelPot() {
	int potLightLevel = analogRead(A1);
	// Scale inverted pot 0-3.7V (0-780)
	potLightLevel = map(potLightLevel, 660, 0, 0, 255);
	// Avoid negative nambers due to voltage differences when scaling
	potLightLevel = max(potLightLevel, 0);
	lightLevel = potLightLevel/255.0f;

	int potTemperature = analogRead(A2);
	// Scale inverted pot 0-3.7V (0-780)
	potTemperature = map(potTemperature, 660, 0, 0, 255);
	// Avoid negative nambers due to voltage differences when scaling
	potTemperature = max(potTemperature, 0);
	colorTemperature = potTemperature/255.0f;
}

void tick() {
	int stripLevelCool = 255 * lightLevel * (1-colorTemperature);
	int stripLevelWarm = 255 * lightLevel * colorTemperature;
	for(int i=0; i<numberStrips; i++) {
		//int b = 255 * lightLevel;
		//b = 80;
		if (i % 2 == 0) {
			pixels.setPixelColor(i, pixels.Color(stripLevelWarm, stripLevelWarm, stripLevelWarm));
		} else {
			pixels.setPixelColor(i, pixels.Color(stripLevelCool, stripLevelCool, stripLevelCool));
		}
	}
    pixels.show();
}

void loop() {
	checkLightLevelPot();
	tick();
	delay(2);
	Serial.print("Level: ");
	Serial.print(lightLevel);
	Serial.print(" Temperature: ");
	Serial.println(colorTemperature);
}

