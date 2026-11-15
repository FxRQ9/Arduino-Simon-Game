#include <Game.h>

// put function declarations here:
controlSystem c;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
c.setup();
c.startGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  c.debounceButtons();
  

}

// put function definitions here: