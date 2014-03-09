String keys[] = {
  "Tab S","1","2","3","4","5","6",
  "7","8","9","0","-","=","\b",
  "Tab","q","w","e","r","t","y",
  "u","i","o","p","½","\n","j",
  "ShiftLock","a","s","d","f","g","h",
  "k","l",";","'","m",",",".",
  "LShift","z","x","c","v","b","n",
  "RShift","/","Code","Margin"," ","Word Erase","Correct"
};
String codeKeys[] = {
  "Tab S","1","2","3","4","5","6",
  "7","8","9","0","-","=","\b",
  "Tab C","^","ç","é","`","¿","~",
  "[","]","D.Tab","p","§","Reloc","j",
  "ShiftLock","a","s","d","f","g","h",
  "k","l",";","¶","m",",",".",
  "LShift","Demo","x","c","v","Bold","n",
  "RShift","/","Code","Margin R","Half Space","Word Erase","Correct"
};
String shiftKeys[] = {
  "Tab S","!","@","#","$","%","^",
  "&","*","(",")","_","+","\b",
  "Tab","Q","W","E","R","T","Y",
  "U","I","O","P","¼","\n","J",
  "ShiftLock","A","S","D","F","G","H",
  "K","L",";","'","M",",",".",
  "LShift","Z","X","C","V","B","N",
  "RShift","?","Code","Margin L"," ","®","Correct"
};

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

uint8_t rows[] = {
  A2,A3,A1,A4,A0,A5,3,12
};

// pullups are on the columns
uint8_t cols[] = {
  6,7,8,9,10,11,13
};

#define NUM_ROWS (sizeof(rows))
#define NUM_COLS (sizeof(cols))

uint8_t state = 0;

void setup() 
{
  for (uint8_t i=0; i < NUM_ROWS; ++i) {
    pinMode(rows[i], OUTPUT);
  }
  for (uint8_t i=0; i < NUM_COLS; ++i) {
    pinMode(cols[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() 
{
    if (Serial.available()) {
        byte b = Serial.read();
        String key(b);
        pressKey(key);
    }
}

void findKey(String &key, int16_t &row, int16_t &column, uint8_t &meta)
{
    meta = 0;
    row = -1;
    column = -1;
    uint8_t index = 0xff;
    for (index = 0; index < SIZE(keys); ++index) {
        if (keys[index] == key) {
            break;
        }
    }
    if (index < SIZE(keys)) {
        row = index / NUM_ROWS;
        column = index % NUM_ROWS;
        return;
    }
    for (index = 0; index < SIZE(shiftKeys); ++index) {
        if (keys[index] == key) {
            break;
        }
    }
    if (index < SIZE(shiftKeys)) {
        row = index / NUM_ROWS;
        column = index % NUM_ROWS;
        meta = 1;
    }
    return;
}

static String shiftLock = "ShiftLock";

void pressKey(String& key)
{
  int16_t row, column;
  uint8_t meta;
  findKey(key, row, column,meta);
  if (row != -1) {
    if (meta) {
      pressKey(shiftLock);
    }
    digitalWrite(rows[row], HIGH);
    digitalWrite(cols[column], HIGH);
    delay(50);
    digitalWrite(rows[row], LOW);
    digitalWrite(cols[column], LOW);
    if (meta) {
      pressKey(shiftLock);
    }
  }
}
