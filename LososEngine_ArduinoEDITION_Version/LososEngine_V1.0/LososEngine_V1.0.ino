/*      LososEngine - Простой игровой движок позволяющий создавать
     игры ходилки-бродилки

     Version: V1.0
     
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


String Sprite[7] = {" ", "#", "-", "|", "O", "@", "Z"}; // " Textures "
// Разрешение поля для вывода в консоль
// А также редактор уровня 
byte Level[20][20] = {
  {1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,6,6,6,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,6,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1}
};
// Конец реадактора уровня


//  position player |x|y|
byte player_Pos[2] = {8, 8};
bool Draw_On = true;


void setup() {
  Serial.begin(230400);
  pinMode(4,OUTPUT);
  delay(2000);
  // put your setup code here, to run once:

}

void drawLevel() {
  Level[player_Pos[0]][player_Pos[1]] = 5;
  //========================== Level draw, PON?
  byte pos_X = 0;
  byte pos_Y = 0;
  while (pos_X < 20) {
    while (pos_Y < 20) {
      Serial.print(Level[pos_X][pos_Y]);
      pos_Y = pos_Y + 1;
    }
    pos_Y = 0;
    Serial.print("      ");
    while (pos_Y < 20) {
      byte Remb_Level_State = Level[pos_X][pos_Y];
      Serial.print(Sprite[Remb_Level_State]);
      pos_Y = pos_Y + 1;
    }

    Serial.println("");
    pos_X = pos_X + 1;
    pos_Y = 0;
  }
  Serial.println("Use Numb_Bord on your KeyBoard. And sell after...");
  Serial.println("");
}


//  position player     player_Pos[x][y]
void loop() {
  if (Serial.available() > 0) {
    char Move = Serial.read();
    if (Move == '8') {
      bool Move_Player = false;
      if (Level[player_Pos[0] - 1] [player_Pos[1]] != 0) {
        Move_Player = false;
        tone(4,125);
        delay(100);
        noTone(4);
      } else {
        Move_Player = true;
        Draw_On = true;
        tone(4,255);
        delay(25);
        noTone(4);
      }

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[0] = player_Pos[0] - 1;
      }

    } else if (Move == '6') {
      bool Move_Player = false;
      if (Level[player_Pos[0]] [player_Pos[1] + 1] != 0) {
        Move_Player = false;
        tone(4,125);
        delay(100);
        noTone(4);
      } else {
        Move_Player = true;
        Draw_On = true;
        tone(4,255);
        delay(25);
        noTone(4);
      }

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[1] = player_Pos[1] + 1;
      }

    } else if (Move == '4') {
      bool Move_Player = false;
      if (Level[player_Pos[0]] [player_Pos[1] - 1] != 0) {
        Move_Player = false;
        tone(4,125);
        delay(100);
        noTone(4);
      } else {
        Move_Player = true;
        Draw_On = true;
        tone(4,255);
        delay(25);
        noTone(4);
      }

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[1] = player_Pos[1] - 1;
      }

    } else if (Move == '2') {
      bool Move_Player = false;
      if (Level[player_Pos[0] + 1] [player_Pos[1]] != 0) {
        Move_Player = false;
        tone(4,125);
        delay(100);
        noTone(4);
      } else {
        Move_Player = true;
        Draw_On = true;
        tone(4,255);
        delay(25);
        noTone(4);
      }

      if (Move_Player == true) {
        Level[player_Pos[0]] [player_Pos[1]] = 0;
        player_Pos[0] = player_Pos[0] + 1;
      }

    }
  } else {
    if (Draw_On == true) {
      drawLevel();
    }
    Draw_On = false;
  }


}
