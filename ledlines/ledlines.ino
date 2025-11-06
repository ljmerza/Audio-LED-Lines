/*
 * Audio-Reactive LED Lines
 * Leonardo Merza
 * https://lmerza.com
 * 
 * This sketch creates animated LED lines that react to audio input
 * using the MSGEQ7 audio spectrum analyzer chip.
 */

#include <FastLED.h>


/*
 * LED Configuration
 */
#define NUM_LEDS 90              // total number of LEDs in the strip
#define DATA_PIN 5               // data pin to LED strip
#define LINELENGTH 4             // length of each LED line
#define NUMBEROFLINES 14         // number of LED lines on strip at one time
#define EIGHTBIT 255             // maximum value for 8-bit color
#define HUESPEED 5               // how fast the hue increments for each LED movement
#define LEDSPEED 0               // how fast the LED lines move in ms - affects MSGEQ7 reads

// Initial hue values for each LED line (evenly distributed across color spectrum)
int hues[NUMBEROFLINES] = {0,18,36,54,72,91,109,127,145,163,182,200,218,236};
// Starting positions for each LED line
int positions[NUMBEROFLINES] = {0,7,14,21,28,35,42,49,56,63,70,77,84,90};
// Brightness values for each LED line (populated from audio input)
int values[NUMBEROFLINES];

/*
 * MSGEQ7 Audio Analyzer Configuration
 */
int analogPin = 0;               // pin for MSGEQ7 analog output
int strobePin = 13;              // MSGEQ7 strobe pin for cycling through channels
int resetPin = 3;                // reset pin of the MSGEQ7
int spectrumValue[7];            // array to store the 7 values of the 7 frequency channels
int resetDelay_USec = 100;       // delay of resetting MSGEQ7 in microseconds
int strobeDelay_USec = 40;       // delay to settle input recording in microseconds
int numberOfChannels = 7;        // number of frequency channels in MSGEQ7

CRGB leds[NUM_LEDS];             // FastLED color array for the LED strip


/*
 * Setup function - initializes LED strip and configures MSGEQ7 pins
 */
void setup () { 
	// Initialize FastLED library with NeoPixel strip
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

	// Configure MSGEQ7 pins
	pinMode(analogPin, INPUT);
	pinMode(strobePin, OUTPUT);
	pinMode(resetPin, OUTPUT);

	// Initialize MSGEQ7 to ensure clean startup
	digitalWrite(resetPin, LOW);
	digitalWrite(strobePin, HIGH);
}


/*
 * Main loop - reads audio spectrum and updates LED animations
 */
void loop () {
	/*
	 * Read audio spectrum from MSGEQ7
	 * Each iteration reads all 7 frequency channels
	 */
	for(int i=0; i<numberOfChannels; i++){

		// Pulse reset pin to restart channel reading
		digitalWrite(resetPin, HIGH);
		delayMicroseconds(resetDelay_USec);
		digitalWrite(resetPin, LOW);

		// Toggle strobe to select current channel
		digitalWrite(strobePin, LOW);
		delayMicroseconds(strobeDelay_USec); // Allow input to settle

		// Read current channel and map to LED brightness (0-255)
		spectrumValue[i] = analogRead(analogPin);
		values[i] = map(spectrumValue[i], 0, 1024, 0, EIGHTBIT);
		values[i+numberOfChannels] = map(spectrumValue[i], 0, 1024, 0, EIGHTBIT);

		// Complete strobe cycle to move to next channel
		digitalWrite(strobePin, HIGH);
	}


	/*
	 * Update LED animations
	 * Each LED line moves forward with its own color and brightness
	 */
    for ( unsigned int k = 0; k < NUMBEROFLINES; k++ ) {

	    // Set color for each LED in the current line
	    for( int i = 0; i < LINELENGTH; i++ ){
	        if ( positions[k] + i <  NUM_LEDS) {
	        	// Set LED color using HSV (Hue, Saturation, Value/Brightness)
	        	leds[positions[k] + i] = CHSV(hues[k], 255, values[k]);
	        }
	    }

	    // Update LED strip to show changes
	    FastLED.show();

	    // Turn off trailing LED and advance position
	    leds[positions[k]] = CRGB::Black;
	    positions[k]++;

	    // Update hue for color cycling effect
	    hues[k] += HUESPEED;
	    if ( hues[k] > EIGHTBIT ) {
	    	hues[k] = 0;
	    }

	    // Reset position when line reaches the end of strip
	    if ( positions[k] > NUM_LEDS + LINELENGTH - 2 ) {
	        positions[k] = 0;
	    }
	}

	// Control animation speed
	delay(LEDSPEED);
}
