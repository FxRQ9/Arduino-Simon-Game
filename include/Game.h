#pragma once
#include "Arduino.h"
#include <stdint.h>
#include <vector>

namespace pins {
static constexpr uint8_t LED[3] = {11,12,13};
static constexpr uint8_t BUTTONS[3] = {2,3,4};
static constexpr uint8_t BUZZER = 8;
} // namespace pins


class controlSystem;

class dataReciever {
private:
  int buttons[3] = {HIGH,HIGH,HIGH};

public:
  void setter(unsigned int number, int state);
  int getter(unsigned int number) const;
  void changeReciever(unsigned int Button, int current , controlSystem& controller);
};

class controlSystem {
  private:
  dataReciever data;
  uint16_t score;
  unsigned long lastDebounce[3]={}; //time for debounce
  int flickerableState[3] = {HIGH,HIGH,HIGH}; 
  const unsigned int debounceDelay = 50; //50ms
  std::vector<uint8_t> sequence;
  std::vector<uint8_t> playedSequence;
  const long PLAY_INTERVAL = 1000;
  unsigned long previousMillis = 0;
  int tones[3]= {523,659,784};
  uint8_t level= 1;
  uint8_t playStep=0;
  
  // bool waitingForPlayer = true;

  public:
  void setup();
  dataReciever getData();
  void debounceButtons();
  void createSequence();
  void startGame();
  void playedStep(uint8_t button);
  bool stepChecker(uint8_t playStep);
  void startLevel();
  void restart();
  void plusPlayStep();
  void nextLevel();
  void printScore();  
};
