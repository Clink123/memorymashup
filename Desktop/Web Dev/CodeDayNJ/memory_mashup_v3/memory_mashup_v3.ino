int redLed = 10; //this sets the red led pin
int blueLed = 11; //this sets the blue led pin
int yellowLed = 12;//this sets the yellow led pin
int greenLed = 13; //this sets the green led pin

#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 2, A2, A3, A4, 1);

void setup() {
  pinMode(A0, INPUT);//player 1 red
  pinMode(A1, INPUT);//player 1 blue
  pinMode(3, INPUT);//player 1 yellow
  pinMode(4, INPUT);//player 1 green

  pinMode(6, INPUT);//player 2 red
  pinMode(7, INPUT);//player 2 blue
  pinMode(8, INPUT);//player 2 yellow
  pinMode(9, INPUT);//player 2 green

  pinMode(10, OUTPUT);//red
  pinMode(11, OUTPUT);//blue
  pinMode(12, OUTPUT);//yellow
  pinMode(13, OUTPUT);//green

  randomSeed(analogRead(5));
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Memory Mashup");
  lcd.setCursor(0, 1);
  lcd.print("By James & Shawn");
  delay(5000);
  lcd.clear();
}

void loop() {
  int counter = 0;
  int rounds = 5;
  lcd.print("Set # of rounds.");
  while (digitalRead(A1) == LOW) {
    if (digitalRead(A0) == HIGH) {
      lcd.clear();
      lcd.print("How many rounds?");
      rounds--;
      lcd.setCursor(0, 1);
      lcd.print(rounds);
      delay(300);
    }
    else if (digitalRead(3) == HIGH) {
      lcd.clear();
      lcd.print("How many rounds?");
      rounds++;
      lcd.setCursor(0, 1);
      lcd.print(rounds);
      delay(300);
    }
    if (rounds > 10) {
      lcd.clear();
      lcd.print("Value must be");
      lcd.setCursor(0, 1);
      lcd.print("below 10,go down");
      delay(300);
    }
    else if (rounds <= 0) {
      lcd.clear();
      lcd.print("Value must be");
      lcd.setCursor(0, 1);
      lcd.print("above 0,go up");
      delay(300);
    }
  }
  lcd.clear();
  lcd.print(counter);
  lcd.print(" rounds");
  lcd.setCursor(0, 1);
  lcd.print("Get Ready!");
 
  while (counter <= rounds) {
    int array[counter];
    for (int i = 0; i < counter; i++) {
      int rand = random(4);
      array[i] = rand;
      switch (rand) {
        case 0: //if ledcolor equals 0 then the led will turn red
          delay(100);
          digitalWrite(redLed, HIGH);
          delay(400);
          digitalWrite(redLed, LOW);
          break;
        case 1: //if ledcolor equals 1 then the led will turn green
          delay(100);
          digitalWrite(blueLed, HIGH);
          delay(400);
          digitalWrite(blueLed, LOW);
          break;
        case 2: //if ledcolor equals 2 then the led will turn blue
          delay(100);
          digitalWrite(yellowLed, HIGH);
          delay(400);
          digitalWrite(yellowLed, LOW);
          break;
        case 3:
          delay(100);
          digitalWrite(greenLed, HIGH);
          delay(400);
          digitalWrite(greenLed, LOW);
          break;
      }
      delay(100);
    }

    play(counter, array);

    counter++;
    delay(1000);
  }
  delay(5000);
  lcd.clear();
  lcd.print("Game Over");
  delay(10000);
  lcd.clear();
}


void play (int counter, int array[]) {
  Serial.println("Play initiated.");
  int p1Inputs[counter];
  int p2Inputs[counter];
  int inputs1 = 0;
  int inputs2 = 0;
  int static p1Score = -1;
  int static p2Score = -1;
  String original = "";
  String p1 = "";
  String p2 = "";

  while (inputs1 < counter) {
    if (digitalRead(A0) == HIGH) {
      p1Inputs[inputs1] = 0;
      inputs1++;
      Serial.println("Player 1 pressed red.");
      delay(300);
    }
    else if (digitalRead(A1) == HIGH) {
      p1Inputs[inputs1] = 1;
      inputs1++;
      Serial.println("Player 1 pressed blue.");
      delay(300);
    }
    else if (digitalRead(3) == HIGH) {
      p1Inputs[inputs1] = 2;
      inputs1++;
      Serial.println("Player 1 pressed yellow.");
      delay(300);
    }
    else if (digitalRead(4) == HIGH) {
      p1Inputs[inputs1] = 3;
      inputs1++;
      Serial.println("Player 1 pressed green.");
      delay(300);
    }
  }

  while (inputs2 < counter) {
    if (digitalRead(6) == HIGH) {
      p2Inputs[inputs2] = 0;
      inputs2++;
      Serial.println("Player 2 pressed red.");
      delay(300);
    }
    else if (digitalRead(7) == HIGH) {
      p2Inputs[inputs2] = 1;
      inputs2++;
      Serial.println("Player 2 pressed blue.");
      delay(300);
    }
    else if (digitalRead(8) == HIGH) {
      p2Inputs[inputs2] = 2;
      inputs2++;
      Serial.println("Player 2 pressed yellow.");
      delay(300);
    }
    else if (digitalRead(9) == HIGH) {
      p2Inputs[inputs2] = 3;
      inputs2++;
      Serial.println("Player 2 pressed green.");
      delay(300);
    }
  }

  for (int i = 0; i < counter; i++) {
    original += (String) array[i];
  }

  for (int i = 0; i < counter; i++) {
    p1 += (String) p1Inputs[i];
  }
  if (p1.equals(original)) {
    p1Score++;
  }

  for (int i = 0; i < counter; i++) {
    p2 += (String) p2Inputs[i];
  }
  if (p2.equals(original)) {
    p2Score++;
  }

  lcd.clear();

  Serial.println(p1Score);
  lcd.print("Player 1: ");
  lcd.print(p1Score);

  lcd.setCursor(0, 1);

  Serial.println(p2Score);
  lcd.print("Player 2: ");
  lcd.print(p2Score);
}
