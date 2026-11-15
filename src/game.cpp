#include "Game.h"
#include "Arduino.h"
#include <cstdint>
#include <cstdlib>

void controlSystem::setup() {
  pinMode(pins::LED[0], OUTPUT);
  pinMode(pins::LED[1], OUTPUT);
  pinMode(pins::LED[2], OUTPUT);
  pinMode(pins::BUTTONS[0], INPUT_PULLUP);
  pinMode(pins::BUTTONS[1], INPUT_PULLUP);
  pinMode(pins::BUTTONS[2], INPUT_PULLUP);
  pinMode(pins::BUZZER, OUTPUT);
}
void dataReciever::setter(unsigned int number, int state) {
  if (number >= 1 && number <= 3) {
    buttons[number - 1] = state;
  }
}

// int dataReciever::getter(unsigned int number) const {
//   if (number == 1) {
//     return buttons[0];
//   } else if (number == 2) {
//     return buttons[1];
//   } else if (number == 3) {
//     return buttons[2];
//   }
//   return NULL;
// }

// void dataReciever::changeReciever(unsigned int Button,
//                                   controlSystem &controller) {
//   // detecting HIGH to LOW = Button is pressed
//   switch (Button) {
//   case 0:
//     if (digitalRead(pins::BUTTONS[0]) == LOW && buttons[0] == HIGH) {
//       dataReciever::setter(1);
//       controller.playedStep(1);
//     } else {
    
//       dataReciever::setter(1);
//     }
//     break;
//   case 1:
//     if (digitalRead(pins::BUTTONS[1]) == LOW && buttons[1] == HIGH) {
//       dataReciever::setter(2);
//       controller.playedStep(2);
//     } else {
//       dataReciever::setter(2);
    
//     }
//     break;
//   case 2:
//     if (digitalRead(pins::BUTTONS[2]) == LOW && buttons[2] == HIGH) {
//       dataReciever::setter(3);
//       controller.playedStep(3);
//     } else {
//       dataReciever::setter(3);
    
//     }
//     break;
//   }
// }
void dataReciever::changeReciever(
    unsigned int Button,
    int current,
    controlSystem& controller) {

  if (Button >= 3) {
    return;
  }

  bool pressed = (current == LOW && buttons[Button] == HIGH);

  setter(Button + 1, current);

  if (pressed) {
    controller.playedStep(Button + 1);
  }
}
// void controlSystem::debounceButtons() {
//   for (int i = 0; i < 3; i++) {
//     if (digitalRead(pins::BUTTONS[i]) != flickerableState[i]) {
//       lastDebounce[i] = millis(); // reset timer
//       flickerableState[i] =
//           digitalRead(pins::BUTTONS[i]); // save debounce state
//     }
//     if ((millis() - lastDebounce[i]) > debounceDelay) {
//       data.changeReciever(i, *this);
//     }
//   }
// }
void controlSystem::debounceButtons() {
  for (int i = 0; i < 3; i++) {
    int current = digitalRead(pins::BUTTONS[i]);
    unsigned long now = millis();

    if (current != flickerableState[i]) {
      flickerableState[i] = current;
      lastDebounce[i] = now;
    }

    if (now - lastDebounce[i] >= debounceDelay) {
      data.changeReciever(i, current, *this);
    }
  }
}
void controlSystem::createSequence() {
  uint8_t randomNumber = random(0, 3);
  sequence.push_back(randomNumber);
}

void controlSystem::startGame() {
  if (level == 1) {
    createSequence();
    digitalWrite(pins::LED[sequence[0]], HIGH);
    tone(pins::BUZZER, tones[sequence[0]], 1000);
    delay(1000);
    digitalWrite(pins::LED[sequence[0]], LOW); 
  }
}

void controlSystem::nextLevel(){
  level++;
  createSequence();
  delay(500);
  for (size_t i = 0; i < sequence.size(); ++i) {
  uint8_t index = sequence[i];

  digitalWrite(pins::LED[index], HIGH);
  tone(pins::BUZZER, tones[index], 1000);
  delay(1000);

  noTone(pins::BUZZER);
  digitalWrite(pins::LED[index], LOW);
  delay(300);
}

}
// void controlSystem::startLevel() {
//   if (level == 1) {
//     createSequence();
//     digitalWrite(pins::LED[sequence[0]], HIGH);
//     tone(pins::BUZZER, sequence[0], 1500);
//     delay(2000);
//     digitalWrite(pins::LED[sequence[0]], LOW); 
//   } else if(level > 1){
    
//   }
// }

void controlSystem::playedStep(uint8_t button) {
  plusPlayStep();
  switch (button) {
  case 1:
    playedSequence.push_back(0);

    digitalWrite(pins::LED[0], HIGH);
    tone(pins::BUZZER, tones[0], 1000);
    delay(1000);
    digitalWrite(pins::LED[0], LOW);
    if (stepChecker(playStep) == false) {
      controlSystem::restart();
    } else {
      score += 10;
      if (level == playStep) {
        playStep=0;
        playedSequence.clear();
        printScore();
        nextLevel();
      }
    }
    break;
    case 2:
    playedSequence.push_back(1);
    digitalWrite(pins::LED[1], HIGH);
    tone(pins::BUZZER, tones[1], 1000);
    delay(1000);
    digitalWrite(pins::LED[1], LOW);
    if (stepChecker(playStep) == false) {
      controlSystem::restart();
    } else {
      score += 10;
      if (level == playStep) {
        playStep=0;
        playedSequence.clear();
        printScore();
        nextLevel();
      }
      
    }
    break;
    case 3:
    playedSequence.push_back(2);
    digitalWrite(pins::LED[2], HIGH);
    tone(pins::BUZZER, tones[2], 1000);
    delay(1000);
    digitalWrite(pins::LED[2], LOW);
    if (stepChecker(playStep) == false) {
      controlSystem::restart();
    } else {
      score += 10;
      if (level == playStep) {
        playStep=0;
        playedSequence.clear();
        printScore();
        nextLevel();
      }
    }
    break;
  }
}

// bool controlSystem::stepChecker(uint8_t playStep) {
//   if (sequence.at(playStep - 1) == playedSequence.at(playStep - 1)) {
//     return true;
//   } else {
//     return false;
//   }
// }
bool controlSystem::stepChecker(uint8_t stepCount) {
  if (stepCount == 0) {
    return false;
  }

  size_t index = stepCount - 1;

  if (index >= sequence.size() ||
      index >= playedSequence.size()) {
    return false;
  }

  return sequence.at(index) == playedSequence.at(index);
}

void controlSystem::restart() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pins::LED[i], HIGH);
  }

  tone(pins::BUZZER, 330, 200); // E4
  delay(200);
  noTone(pins::BUZZER);
  for (int i = 0; i < 3; i++) {
    digitalWrite(pins::LED[i], LOW);
  }
  score = 0;
  sequence.clear();
  playedSequence.clear();
  level = 1;
  playStep = 0;
  delay(400);
  startGame();
}

void controlSystem::plusPlayStep() {
  playStep++;
}
 void controlSystem::printScore(){
  Serial.println(score);
 }
dataReciever controlSystem::getData() { return data; }