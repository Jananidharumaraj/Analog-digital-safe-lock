#include <Keypad.h>
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// 4x4 Matrix keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to Arduino pins.
byte rowPins[ROWS] = {5, 4, 3, 2};

// Connect keypad COL0, COL1, COL2 and COL3 to Arduino pins.
byte colPins[COLS] = {6, 7, 8, 9};

// Create the Keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Predefined password
String password = "1234"; // Change this to your desired password
String inputPassword;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Enter Password:");
}

void loop() {
  char key = kpd.getKey();

  // Check for a valid key
  if (key) {
    // If the key is '#', check the password
    if (key == '#') {
      lcd.clear();
      lcd.print("Checking...");
      delay(1000); // Delay to show the message

      // Check if the entered password matches the predefined password
      if (inputPassword == password) {
        lcd.clear();
        lcd.print("Access Granted!");
        // You can add code to unlock the safe here
      } else {
        lcd.clear();
        lcd.print("Access Denied!");
      }
      delay(2000); // Show the message for a while
      lcd.clear();
      lcd.print("Enter Password:");
      inputPassword = ""; // Reset input password
    } 
    // If the key is '*', clear the input
    else if (key == '*') {
      inputPassword = ""; // Clear the input
      lcd.clear();
      lcd.print("Enter Password:");
    } 
    // Otherwise, add the key to the input password
    else {
      inputPassword += key; // Append the key to the input password
      lcd.setCursor(0, 1);
      lcd.print("Input: " + inputPassword); // Display input
    }
  }
}