/*
 * LED Lines with Independent Delays
 * Leonardo Merza
 * https://lmerza.com
 * 
 * This sketch creates multiple independent LED lines with individual
 * delay timings for varied animation effects.
 */

#include <FastLED.h>

/*
 * LED Configuration
 */
#define NUM_LEDS 90              // total number of LEDs in the strip
#define DATA_PIN 5               // data pin to LED strip
#define LINELENGTH 5             // length of each LED line
#define EIGHTBIT 255             // maximum value for 8-bit color
#define HUESPEED 2               // how fast the hue increments for each LED movement
#define STRIPNUMB 7              // number of independent LED lines

// Initial hue values for each LED line (evenly distributed across color spectrum)
unsigned int hues[STRIPNUMB] = {0,36,72,108,144,180,216};
// Delay values for each LED line (controls animation speed)
unsigned int delays[STRIPNUMB];
// Counters to track delay timing for each line
unsigned int delayCounters[STRIPNUMB];
// Starting positions for each LED line
unsigned int positions[STRIPNUMB] = {0,13,26,39,52,65,78};
// Active state for each line (1 = active, 0 = inactive)
unsigned int actives[STRIPNUMB] = {1,1,1,1,1,1,1};
// Brightness values for each LED line
unsigned int values[STRIPNUMB] = {100,255,100,255,100,255,100};
// Count of currently active lines
unsigned int numbOfActives = 0;

boolean ledChange = false;       // flag to track if any LED color has changed

CRGB leds[NUM_LEDS];             // FastLED color array for the LED strip
/*
 * Setup function - initializes LED strip and delay counters
 */
void setup () { 
	// Initialize FastLED library with NeoPixel strip
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	
	// Initialize serial communication for debugging
	Serial.begin(9600);
	
	// Initialize delay counters and values for each LED line
	for ( int i = 0; i < STRIPNUMB; i++ ) {
		delayCounters[i] = 0;
		delays[i] = 50;
	}
}


/*
 * Main loop - updates LED animations with independent delays
 */
void loop () {
	/*
	 * Process each LED line independently
	 * Each line has its own delay counter and timing
	 */
    for ( unsigned int k = 0; k < STRIPNUMB; k++ ) {

		// Only process active LED lines
		if ( actives[k] == 1) {
	        // Check if delay counter has exceeded the line's delay threshold
	        if ( delayCounters[k] > delays[k] ) {
	        	ledChange = true;
	        	
	        	// Set color for each LED in the current line
	        	for( int i = 0; i < LINELENGTH; i++ ){
	        		if ( positions[k] + i <  NUM_LEDS) {
	        			// Set LED color using HSV (Hue, Saturation, Value/Brightness)
	        			leds[positions[k] + i] = CHSV(hues[k], 255, values[k]);
	        		}
	        	}

	        	// Turn off trailing LED, advance position, reset delay counter
	        	leds[positions[k]] = CRGB::Black;
	        	positions[k]++;
	        	delayCounters[k] = 0;

	        	// Update hue for color cycling effect
	        	hues[k] += HUESPEED;
	        	if( hues[k] > EIGHTBIT ){
	        		hues[k] = 0;
	        	}

	        	// Check if line has reached the end of strip
	        	if ( positions[k] > NUM_LEDS + LINELENGTH-1) {
	        		// Reset position when line reaches end
	        		positions[k] = 0;
	        		// Optionally deactivate line (currently commented out)
	        		//actives[k] = 0;
	        		
	        		// Decrement active counter (if applicable)
	        		if ( numbOfActives > 0 ) {
	        			numbOfActives--;
	        		}
	        	}

	        	// Update LED strip only if colors have changed (optimization)
	        	if ( ledChange ){
	        		FastLED.show();
	        		ledChange = false;
	        	}
	        }

	        // Increment delay counter each loop iteration
	        delayCounters[k]++;
	    } 
	}

	// Small delay for timing control
	delay(1);
}