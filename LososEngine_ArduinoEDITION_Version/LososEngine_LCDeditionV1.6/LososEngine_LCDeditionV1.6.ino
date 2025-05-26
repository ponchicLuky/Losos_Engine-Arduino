/*      LososEngine - Простой игровой движок позволяющий создавать
     игры ходилки-бродилки

     Version: V1.5

     ПРИМЕЧАНИЕ: В случае если вы не обладаете платами перейдите по ссылке:
                 https://wokwi.com/projects/new/arduino-uno
                 Она позволет запустить эмуляцию платы


     // ====================================
     управление: 8 - Вверх
                 2 - Вниз

                 6 - Вправо
                 4 - Влево

     // ====================================
     объекты редактора:
              0 - пробел   |  6 - Z
              1 - #        |
              2 - -        |  элементы дальше отсутствуют,
              3 - |        |  если вам нужны дополнительные тестуры
              4 - O        |  то добавьте их по адресу: " Textures "
              5 - @        |

*/
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

//Кол-во Текстур:
//            V
String Sprite[7] = {" ", "#", "-", "|", "O", "@", "Z"}; // " Textures "

#define Lenth_X 20
#define Lenth_Y 4
// Разрешение поля для вывода в консоль
// А также редактор уровня
byte Level[Lenth_Y+1][Lenth_X+1] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
// Конец реадактора уровня


//  position player |x|y|
int player_Pos[2] = {0, 0};
bool Move_Player = false; // Движение Игрока
bool Draw_On = true;      // Отрисовка кадра после действия

byte Rad_Back = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Losos.inc present...");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Losos_ENGINE V1.6");
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(9, OUTPUT);
  delay(2000);
  lcd.clear();

}

void drawLevel() {
  //Serial.println("drawLevel() - Work");
  lcd.clear();
  Level[player_Pos[0]][player_Pos[1]] = 5;
  //========================== Level draw, PON?
  byte pos_X = 0;
  byte pos_Y = 0;
  while (pos_X < Lenth_Y) { 
    while (pos_Y < Lenth_X) {
      byte Remb_Level_State = Level[pos_X][pos_Y];
      lcd.setCursor(pos_Y,pos_X);
      lcd.print(Sprite[Remb_Level_State]);
      pos_Y = pos_Y + 1;
    }
    pos_X = pos_X + 1;
    pos_Y = 0;
  }
}
void Move_Sensor() {
  //Serial.println("Move_Sensor() - Work");
  int command_X = 0;
  int command_Y = 0;
  if (Rad_Back == 8) {command_X = -1;command_Y = 0;}
  if (Rad_Back == 6) {command_X = 0;command_Y = 1;}
  if (Rad_Back == 4) {command_X = 0;command_Y = -1;}
  if (Rad_Back == 2) {command_X = 1;command_Y = 0;}

  
    switch (Level[player_Pos[0] + command_X][player_Pos[1] + command_Y]) {
      case 0:
        Move_Player = true;
        Draw_On = true;
        break;
      case 1:
        Move_Player = false;
        Draw_On = false;
        break;
      case 2:
        Move_Player = false;
        Draw_On = false;
        break;
      case 3:
        Move_Player = false;
        Draw_On = false;
        break;
      case 4:
        Move_Player = false;
        Draw_On = false;
        break;
      case 5:
        Move_Player = false;
        Draw_On = false;
        break;
      case 6:
        Move_Player = false;
        Draw_On = false;
        break;
    }

  if (player_Pos[0] < 0 or player_Pos[1] < 0) {
    Move_Player = false;
    Draw_On = false;
  }

  if (Move_Player == true) {
    tone(4, 125);
    delay(70);
    noTone(4);
  } else if (Move_Player == false) {
    tone(4, 255);
    delay(20);
    noTone(4);
  }
}


void loop() {
  base_Mode();
  /*
  if(Serial.available()>0){
    int posX = Serial.parseInt();
    int posY = Serial.parseInt();
    int Sprite = Serial.parseInt();
    Serial.println(String(posX)+String(posY)+String(Sprite));
    Level[posY][posX] = Sprite;
    drawLevel();
  }
  */
}


void base_Mode() {
  //Serial.println("base_Mode() - Work");
  bool btn_UP = digitalRead(4);
  bool btn_DOWN = digitalRead(2);
  bool btn_LEFT = digitalRead(3);
  bool btn_RIGHT = digitalRead(5);
  
    if(btn_UP == HIGH){
      Rad_Back = 8;
      Move_Sensor();

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[0] = player_Pos[0] - 1;

      }
    } else if (btn_RIGHT == HIGH) {
      Rad_Back = 6;
      Move_Sensor();

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[1] = player_Pos[1] + 1;

      }
    
    } else if (btn_LEFT == HIGH) {
      Rad_Back = 4;
      Move_Sensor();

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[1] = player_Pos[1] - 1;

      }
    } else if (btn_DOWN == HIGH) {
      Rad_Back = 2;
      Move_Sensor();

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[0] = player_Pos[0] + 1;

      }
    }
    if(Draw_On == true) {
      drawLevel();
      Move_Player = false;
      Draw_On = false;
    }
    
  }
