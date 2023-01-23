//#include <Keyboard.h>
#define columncount 4
#define rowcount 6

// In het geval van mijn mooie printje zijn hier
// de rows en columns wel omgedraaid.

int columns[] = {7, 6, 5, 4};
int rows[] = {A3, A2, A1, A0, 15, 14};

int pressed [rowcount][columncount] = {HIGH};
/*
  N / * -
  7 8 9 +
  4 5 6
  1 2 3
  0   . enter
*/

int keycodes [rowcount][columncount] = {
  {801, 905, 904, 910},
  {219, 220, 221, 222},
  {231, 232, 233, 223},
  {228, 229, 230, 0},
  {225, 226, 227, 224},
  {0,   234, 235, 0}
};

long millisOld[columncount * rowcount];

/*
  219 Numlock
  220 '\334' Keypad /
  221 '\335' Keypad *
  222 '\336' Keypad -
  223 '\337' Keypad +
  224 '\340' Keypad ENTER
  225 '\341' Keypad 1 and End
  226 '\342' Keypad 2 and Down Arrow
  227 '\343' Keypad 3 and PageDn
  228 '\344' Keypad 4 and Left Arrow
  229 '\345' Keypad 5
  230 '\346' Keypad 6 and Right Arrow
  231 '\347' Keypad 7 and Home
  232 '\350' Keypad 8 and Up Arrow
  233 '\351' Keypad 9 and PageUp
  234 '\352' Keypad 0 and Insert
  235 '\353' Keypad . and Delete
*/

void setup() {

  //  pinMode(13, OUTPUT);
  //  digitalWrite(13, LOW);

  //Serial.begin(9600);
  //Serial.println("Hi!");

  for (int i = 0; i < columncount; i++)
  {
    pinMode(columns[i], INPUT_PULLUP);
  }

  for (int i = 0; i < rowcount; i++)
  {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }

  Keyboard.begin();

}

void loop() {
  dokey();
}

void dokey()
{
  for (int r = 0; r < rowcount; r++)
  {
    digitalWrite(rows[r], LOW);
    for (int c = 0; c < columncount; c++)
    {
      int val = digitalRead(columns[c]);

      if (pressed[r][c] != val) //Delta
      {
        long currentTime = millis();
        if (currentTime - millisOld[c * r] > 3)
        {
          millisOld[c * r] = currentTime;
          /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
          if (val == LOW)
          {
            int keycode = keycodes[r][c];
            //Serial.print(keycode);
            //Serial.println();
            
            if (keycode < 256)
            {
              Keyboard.press(keycode);

            }
            else {
              switch (keycode) {
                case 800:
                  modifierKeyPress('a', true, false, false, false);
                  break;
                case 801:
                  Remote.playPause();
                  break;
                case 900:
                  Remote.play();
                  Remote.clear();
                  break;
                case 901:
                  Remote.pause();
                  Remote.clear();
                  break;
                case 902:
                  Remote.playPause();
                  Remote.clear();
                  break;
                case 903:
                  Remote.stop();
                  Remote.clear();
                  break;
                case 904:
                  Remote.next();
                  Remote.clear();
                  break;
                case 905:
                  Remote.previous();
                  Remote.clear();
                  break;
                case 906:
                  Remote.forward();
                  Remote.clear();
                  break;
                case 907:
                  Remote.rewind();
                  Remote.clear();
                  break;
                case 908:
                  Remote.increase();
                  Remote.clear();
                  break;
                case 909:
                  Remote.decrease();
                  Remote.clear();
                  break;
                case 910:
                  Remote.mute();
                  Remote.clear();
                  break;
              }
            }
          }
          else
          {
            if (keycodes[r][c] < 256)
            {
              Keyboard.release(keycodes[r][c]);
            }
          }
          pressed[r][c] = val;
        }
      }
    }
    digitalWrite(rows[r], HIGH);
  }
}

void modifierKeyPress(byte keyCode, bool Ctrl, bool Shift, bool Alt, bool Win)
{
  if (Ctrl)
    Keyboard.press(KEY_LEFT_CTRL);
  if (Shift)
    Keyboard.press(KEY_LEFT_SHIFT);
  if (Alt)
    Keyboard.press(KEY_LEFT_ALT);
  if (Win)
    Keyboard.press(KEY_LEFT_GUI);

  Keyboard.press(keyCode);
  delay(50);
  Keyboard.release(keyCode);

  if (Ctrl)
    Keyboard.release(KEY_LEFT_CTRL);
  if (Shift)
    Keyboard.release(KEY_LEFT_SHIFT);
  if (Alt)
    Keyboard.release(KEY_LEFT_ALT);
  if (Win)
    Keyboard.release(KEY_LEFT_GUI);
}

