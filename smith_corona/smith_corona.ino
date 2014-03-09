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

void setup() {
  for (uint8_t i=0; i < NUM_ROWS; ++i) {
    pinMode(rows[i], INPUT);
  }
  for (uint8_t i=0; i < NUM_COLS; ++i) {
    digitalWrite(cols[i],HIGH);
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i],HIGH);
  }
  Serial.begin(9600);
}

void loop() {

  uint16_t i,j,b=1,val=0;
  for (i=0; i < NUM_ROWS; ++i) {
    if (digitalRead(rows[i]) == LOW) {
      val |= b;
    }
    b <<= 1;
  }
  if (val & 1) {
    digitalWrite(cols[2],LOW);
  } else {
    digitalWrite(cols[2],HIGH);
  }
}

