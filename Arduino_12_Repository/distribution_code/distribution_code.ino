#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>
#include <stdlib.h>

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;
const int WHITE_PIN_NUMBER = 11;
const int YEL_PIN_NUMBER = 12;
const int BLUE_PIN_NUMBER = 13;

// global constant for the number of Invaders in the game
const int NUM_ENEMIES = 16;

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

//a global variable that represents losing a level
bool gameLose = false;
bool gameWin = false;

// the following functions are for printing messages
void print_game_name();
void print_level(int level);
void print_lives(int lives);
void game_over();

class Color {
  public:
    int red;
    int green;
    int blue;
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    uint16_t to_333() const {
      return matrix.Color333(red, green, blue);
    }
};

const Color BLACK(0, 0, 0);
const Color RED(7, 0, 0);
const Color ORANGE(7, 2, 0);
const Color YELLOW(7, 7, 0);
const Color GREEN(0, 7, 0);
const Color BLUE(0, 0, 7);
const Color PURPLE(7, 0, 7);
const Color WHITE(7, 7, 7);
const Color LIME(4, 7, 0);
const Color AQUA(0, 7, 7);


class Background {
  public:
  void background() {
      print_background();
  }
  private:
  void print_background() {
      //red button outer square
        matrix.drawPixel(2, 10, RED.to_333());
        matrix.drawPixel(3, 10, RED.to_333());
        matrix.drawPixel(4, 10, RED.to_333());
        matrix.drawPixel(5, 10, RED.to_333());
        matrix.drawPixel(6, 10, RED.to_333());
        matrix.drawPixel(2, 11, RED.to_333());
        matrix.drawPixel(2, 12, RED.to_333());
        matrix.drawPixel(2, 13, RED.to_333());
        matrix.drawPixel(2, 14, RED.to_333());
        matrix.drawPixel(6, 11, RED.to_333());
        matrix.drawPixel(6, 12, RED.to_333());
        matrix.drawPixel(6, 13, RED.to_333());
        matrix.drawPixel(6, 14, RED.to_333());
        matrix.drawPixel(3, 14, RED.to_333());
        matrix.drawPixel(4, 14, RED.to_333());
        matrix.drawPixel(5, 14, RED.to_333());
  
      //white button outer square
        matrix.drawPixel(10, 10, WHITE.to_333());
        matrix.drawPixel(11, 10, WHITE.to_333());
        matrix.drawPixel(12, 10, WHITE.to_333());
        matrix.drawPixel(13, 10, WHITE.to_333());
        matrix.drawPixel(14, 10, WHITE.to_333());
        matrix.drawPixel(10, 11, WHITE.to_333());
        matrix.drawPixel(10, 12, WHITE.to_333());
        matrix.drawPixel(10, 13, WHITE.to_333());
        matrix.drawPixel(10, 14, WHITE.to_333());
        matrix.drawPixel(14, 11, WHITE.to_333());
        matrix.drawPixel(14, 12, WHITE.to_333());
        matrix.drawPixel(14, 13, WHITE.to_333());
        matrix.drawPixel(14, 14, WHITE.to_333());
        matrix.drawPixel(11, 14, WHITE.to_333());
        matrix.drawPixel(12, 14, WHITE.to_333());
        matrix.drawPixel(13, 14, WHITE.to_333());
  
     //yellow button outer square
        matrix.drawPixel(17, 10, YELLOW.to_333());
        matrix.drawPixel(18, 10, YELLOW.to_333());
        matrix.drawPixel(19, 10, YELLOW.to_333());
        matrix.drawPixel(20, 10, YELLOW.to_333());
        matrix.drawPixel(21, 10, YELLOW.to_333());
        matrix.drawPixel(17, 11, YELLOW.to_333());
        matrix.drawPixel(17, 12, YELLOW.to_333());
        matrix.drawPixel(17, 13, YELLOW.to_333());
        matrix.drawPixel(17, 14, YELLOW.to_333());
        matrix.drawPixel(21, 11, YELLOW.to_333());
        matrix.drawPixel(21, 12, YELLOW.to_333());
        matrix.drawPixel(21, 13, YELLOW.to_333());
        matrix.drawPixel(21, 14, YELLOW.to_333());
        matrix.drawPixel(18, 14, YELLOW.to_333());
        matrix.drawPixel(19, 14, YELLOW.to_333());
        matrix.drawPixel(20, 14, YELLOW.to_333());
  
      //blue button outer square
        matrix.drawPixel(25, 10, BLUE.to_333());
        matrix.drawPixel(26, 10, BLUE.to_333());
        matrix.drawPixel(27, 10, BLUE.to_333());
        matrix.drawPixel(28, 10, BLUE.to_333());
        matrix.drawPixel(29, 10, BLUE.to_333());
        matrix.drawPixel(25, 11, BLUE.to_333());
        matrix.drawPixel(25, 12, BLUE.to_333());
        matrix.drawPixel(25, 13, BLUE.to_333());
        matrix.drawPixel(25, 14, BLUE.to_333());
        matrix.drawPixel(29, 11, BLUE.to_333());
        matrix.drawPixel(29, 12, BLUE.to_333());
        matrix.drawPixel(29, 13, BLUE.to_333());
        matrix.drawPixel(29, 14, BLUE.to_333());
        matrix.drawPixel(26, 14, BLUE.to_333());
        matrix.drawPixel(27, 14, BLUE.to_333());
        matrix.drawPixel(28, 14, BLUE.to_333());
  }
};
 
class Notes {
  public:
      Notes() {
          int x = 0;
          int y = -10;      //If we change the move function to try and hide bugs,
      }                      //also change the y being set here?
 
      void initialize(int x_arg, int y_arg) {
          x = x_arg;
          y = y_arg;
      }
      
      int get_x() {
          return x;
      }
      
      int get_y() {
          return y;
      }
      
      void set_x(int x_arg) {
          x = x_arg;
      }
      
      void set_y(int y_arg) {
          y = y_arg;
      }
 
      void draw() {
        if (x == 3) {
            draw_with_rgb(RED);
        }
        else if (x == 11) {
            draw_with_rgb(WHITE);
        }
        else if (x == 18) {
            draw_with_rgb(YELLOW);
        }
        else if (x == 26) {
            draw_with_rgb(BLUE);
        }
      }
 
      void erase() {
          draw_with_rgb(BLACK);
      }
      
      void move() {
          if (y >= -10 && y <= 15) {  //Possibly change the starting and ending y values to deal
              y += 1;                 // with syncing the music and bugs
          }
          else {
            erase();   //Possibly call clear_note() here instead? I think it'll
          }             // help with the glitches if we change the y of moving cuz
      }                 // then they'll be thrown offscreen, and perhaps we can sync the 
                        // music better too
      void clear_note() {
          erase();
          y = 16;
      }
      
      
  private:
      int x;
      int y;
      
      //draws 3x3 square music "notes"
      void draw_with_rgb(Color color) {
          if ((x >= 0) && (x <= 31)) {
              matrix.drawPixel(x, y, color.to_333());
              matrix.drawPixel(x, y + 1, color.to_333());
              matrix.drawPixel(x, y + 2, color.to_333());
              matrix.drawPixel(x + 1, y, color.to_333());
              matrix.drawPixel(x + 1, y + 1, color.to_333());
              matrix.drawPixel(x + 1, y + 2, color.to_333());
              matrix.drawPixel(x + 2, y, color.to_333());
              matrix.drawPixel(x + 2, y + 1, color.to_333());
              matrix.drawPixel(x + 2, y + 2, color.to_333());
    }
  }
};

const int NUM_NOTES = 48;
class GameMusic {
  public:
    void redNoteClicked(bool button_pressed, int index) {
      int y0 = notes[index].get_y();
        if ((y0 == 11) && (button_pressed)) {
           notes[index].erase();
           notes[index].clear_note();
           numNotesHit++;
        }
     }

    void whiteNoteClicked(bool white_button_pressed, int index) {
      int y1 = notes[index].get_y();
        if ((y1 == 11) && (white_button_pressed)) {
          notes[index].erase();
          notes[index].clear_note();
          numNotesHit++;
        }
    }

    void yelNoteClicked(bool yel_button_pressed, int index) {
      int y2 = notes[index].get_y();
        if ((y2 == 11) && (yel_button_pressed)) {
          notes[index].erase();
          notes[index].clear_note();
          numNotesHit++;
        }
    }

    void blueNoteClicked(bool blue_button_pressed, int index) {
      int y3 = notes[index].get_y();
        if ((y3 == 11) && (blue_button_pressed)) {
          notes[index].erase();
          notes[index].clear_note();
          numNotesHit++;
      }
    }

    void NoteMove(int frequency, int index) {
      if (notes[index].get_y() < 16) {         //Also change this 16 here to sync music
        time = millis();
        if ((time - lastMillisRed) > frequency) {
          notes[index].erase();
          notes[index].move();        
          notes[index].draw();
          lastMillisRed = time;
        } 
      }
      else {
        return;
      }  
    }

    int scoreCalc(int NotesHit) {
       if (songNum == 1) {
         numNotesInSong = 36;
       }
       else if (songNum == 2) {
         numNotesInSong = 36;
       }
       else if (songNum == 3) {
         numNotesInSong = 40;
       }
       else if (songNum == 4) {
         numNotesInSong = 48;
       }
       else if (songNum == 5) {
         numNotesInSong = 40;
       }
       
       else if (songNum == 6) {
         numNotesInSong = 34;
       }
       else if (songNum == 7) {
         numNotesInSong = 32;
       }
       else if (songNum == 8) {
         numNotesInSong = 34;
       }
       else if (songNum == 9) {
         numNotesInSong = 32;
       }
       else if (songNum == 10) {
         numNotesInSong = 35;
       }
       else if (songNum == 11) {
         numNotesInSong = 48;
       }
       score = (NotesHit * 1.0 / numNotesInSong) * 100;
       return score;
    }

    void print_score() {
      matrix.setTextColor(AQUA.to_333());
      matrix.setTextSize(1);
      matrix.setCursor(0,0);
      matrix.print('S');
      matrix.print('C');
      matrix.print('O');
      matrix.print('R');
      matrix.print('E');
      
      matrix.setTextColor(AQUA.to_333());
      matrix.setTextSize(1);
      matrix.setCursor(6,8);
      matrix.print(score);
      matrix.print('%');
    }

    void reset_level() {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      songNum++;
      print_level(songNum);
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      numNotesHit = 0;
      score = 0;

      for (int i = 0; i < NUM_NOTES; i++) {
        if ((i >= 0) && (i <= 11)) {
          notes[i].initialize(3, -10);  //If we change the move function to try and hide bugs, also change the y being set here
        }
        else if ((i >= 12) && (i <= 23)) {
          notes[i].initialize(11, -10);
        }
        else if ((i >= 24) && (i <= 35)) {
          notes[i].initialize(18, -10);
        }
        else if ((i >= 36) && (i <= 47)) {
          notes[i].initialize(26, -10);
         }
        notes[i].draw();
      }
    }

  void song1(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Can't Stop the Feeling
    
    NoteMove(30, 0);
    NoteMove(30, 17);
    NoteMove(30, 42);
    NoteMove(30, 26);
    NoteMove(30, 14);
    NoteMove(30, 2);
    NoteMove(30, 6);
    NoteMove(30, 23);
    NoteMove(30, 33);
    NoteMove(30, 43);
    NoteMove(30, 31);
    NoteMove(30, 3);
    NoteMove(30, 12);
    
    NoteMove(30, 37);
    NoteMove(30, 25);
    NoteMove(30, 19);
    NoteMove(30, 47);
    NoteMove(30, 5);
    NoteMove(30, 21); 
    NoteMove(30, 29);
    NoteMove(30, 40);
    NoteMove(30, 9);
    NoteMove(30, 35);
    NoteMove(30, 15);
    NoteMove(30, 24);
    NoteMove(30, 11);

    
    NoteMove(30, 45);
    NoteMove(30, 27);
    NoteMove(30, 1); 
    NoteMove(30, 38);
    NoteMove(30, 20);
    NoteMove(30, 28);
    NoteMove(30, 8);
    NoteMove(30, 46);
    NoteMove(30, 41);
    NoteMove(30, 32);

    if ((notes[32].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[32].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }

   void song2(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Viva La Vida
    
    NoteMove(30, 6);
    NoteMove(30, 21);
    NoteMove(30, 29);
    NoteMove(30, 4);
    NoteMove(30, 43);
    NoteMove(30, 13);
    NoteMove(30, 26);
    NoteMove(30, 39);
    NoteMove(30, 3);
    NoteMove(30, 24);
    NoteMove(30, 19);
    NoteMove(30, 41);
    NoteMove(30, 9);
    
    NoteMove(30, 8);
    NoteMove(30, 17);
    NoteMove(30, 28);
    NoteMove(30, 12);
    NoteMove(30, 38);
    NoteMove(30, 40); 
    NoteMove(30, 16);
    NoteMove(30, 2);
    NoteMove(30, 32);
    NoteMove(30, 20);
    NoteMove(30, 42);
    NoteMove(30, 18);
    NoteMove(30, 30);

    
    NoteMove(30, 5);
    NoteMove(30, 14);
    NoteMove(30, 37); 
    NoteMove(30, 25);
    NoteMove(30, 36);
    NoteMove(30, 1);
    NoteMove(30, 0);
    NoteMove(30, 31);
    NoteMove(30, 15);
    NoteMove(30, 7);
    
    if ((notes[7].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[7].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }

  void song3(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Someone Like You
    
    NoteMove(30, 40);
    NoteMove(30, 33);
    NoteMove(30, 36);
    NoteMove(30, 12);
    NoteMove(30, 1);
    NoteMove(30, 2);
    NoteMove(30, 14);
    NoteMove(30, 22);
    NoteMove(30, 29);
    NoteMove(30, 41);
    
    NoteMove(30, 7);
    NoteMove(30, 3);
    NoteMove(30, 13);
    NoteMove(30, 35);
    NoteMove(30, 44); 
    NoteMove(30, 37);
    NoteMove(30, 15);
    NoteMove(30, 27);
    NoteMove(30, 6);
    NoteMove(30, 9);
   
    NoteMove(30, 25);
    NoteMove(30, 5);
    NoteMove(30, 24);
    NoteMove(30, 34); 
    NoteMove(30, 45);    
    NoteMove(30, 46);
    NoteMove(30, 0);
    NoteMove(30, 23);
    NoteMove(30, 10);
    NoteMove(30, 20);
   
    NoteMove(30, 11);
    NoteMove(30, 38);
    NoteMove(30, 43);
    NoteMove(30, 8);
    NoteMove(30, 21);
    NoteMove(30, 26);
    NoteMove(30, 39);
    NoteMove(30, 31);
    NoteMove(30, 17);
    NoteMove(30, 30);
    
    if ((notes[30].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[30].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }

  void song4(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Cheap Thrills
    
    NoteMove(30, 23);
    NoteMove(30, 34);
    NoteMove(30, 0);
    NoteMove(30, 1);
    NoteMove(30, 46);
    NoteMove(30, 27);
    NoteMove(30, 11);
    NoteMove(30, 13);
    NoteMove(30, 3);
    NoteMove(30, 45);
    
    NoteMove(30, 37);
    NoteMove(30, 25);
    NoteMove(30, 14);
    NoteMove(30, 4);
    NoteMove(30, 22); 
    NoteMove(30, 41);
    NoteMove(30, 38);
    NoteMove(30, 47);
    NoteMove(30, 18);
    NoteMove(30, 24);
    
    NoteMove(30, 8);
    NoteMove(30, 39);
    NoteMove(30, 28);
    NoteMove(30, 17); 
    NoteMove(30, 6);    
    NoteMove(30, 15);
    NoteMove(30, 44);
    NoteMove(30, 33);
    NoteMove(30, 43);
    NoteMove(30, 16);
   
    NoteMove(30, 26);
    NoteMove(30, 5);
    NoteMove(30, 42);
    NoteMove(30, 36);
    NoteMove(30, 12);
    NoteMove(30, 10);
    NoteMove(30, 9);
    NoteMove(30, 32);
    NoteMove(30, 40);
    NoteMove(30, 21);

    NoteMove(30, 31);
    NoteMove(30, 2);
    NoteMove(30, 30);
    NoteMove(30, 7);
    NoteMove(30, 35);
    NoteMove(30, 20);
    NoteMove(30, 19);
    NoteMove(30, 29);
   
    if ((notes[29].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[29].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }

  void song5(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Counting Stars
    
    NoteMove(30, 2);
    NoteMove(30, 32);
    NoteMove(30, 25);
    NoteMove(30, 33);
    NoteMove(30, 39);
    NoteMove(30, 3);
    NoteMove(30, 29);
    NoteMove(30, 4);
    NoteMove(30, 36);
    NoteMove(30, 6);
    
    NoteMove(30, 38);
    NoteMove(30, 17);
    NoteMove(30, 28);
    NoteMove(30, 9);
    NoteMove(30, 10); 
    NoteMove(30, 41);
    NoteMove(30, 13);
    NoteMove(30, 15);
    NoteMove(30, 1);
    NoteMove(30, 37);
    
    NoteMove(30, 18);
    NoteMove(30, 42);
    NoteMove(30, 5);
    NoteMove(30, 19); 
    NoteMove(30, 20);    
    NoteMove(30, 21);
    NoteMove(30, 22);
    NoteMove(30, 35);
    NoteMove(30, 43);
    NoteMove(30, 7);
    
    NoteMove(30, 16);
    NoteMove(30, 44);
    NoteMove(30, 26);
    NoteMove(30, 30);
    NoteMove(30, 14);
    NoteMove(30, 31);
    NoteMove(30, 8);
    NoteMove(30, 34);
    NoteMove(30, 40);
    NoteMove(30, 27);
    
    if ((notes[27].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[27].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }
   
  void song6(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
  //What Makes You Beautiful
    
    NoteMove(30, 25);
    NoteMove(30, 5);
    NoteMove(30, 36);
    NoteMove(30, 12);
    NoteMove(30, 13);
    NoteMove(30, 26);
    NoteMove(30, 41);
    NoteMove(30, 42);
    NoteMove(30, 14);
    NoteMove(30, 1);
    
    NoteMove(30, 38);
    NoteMove(30, 2);
    NoteMove(30, 6);
    NoteMove(30, 18);
    NoteMove(30, 15); 
    NoteMove(30, 44);
    NoteMove(30, 17);
    NoteMove(30, 3);
    NoteMove(30, 19);
    NoteMove(30, 37);
    
    NoteMove(30, 39);
    NoteMove(30, 16);
    NoteMove(30, 8);
    NoteMove(30, 7); 
    NoteMove(30, 20);    
    NoteMove(30, 0);
    NoteMove(30, 47);
    NoteMove(30, 9);
    NoteMove(30, 32);
    NoteMove(30, 23);
    
    NoteMove(30, 10);
    NoteMove(30, 40);
    NoteMove(30, 27);
    NoteMove(30, 46);
    
    if ((notes[46].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[46].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }  
  }
  
  void song7(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Sorry
    
    NoteMove(20, 37);
    NoteMove(20, 28);
    NoteMove(20, 21);
    NoteMove(20, 13);
    NoteMove(20, 14);
    NoteMove(20, 3);
    NoteMove(20, 40);
    NoteMove(20, 41);
    NoteMove(20, 5);
    NoteMove(20, 29);
    
    NoteMove(20, 15);
    NoteMove(20, 22);
    NoteMove(20, 6);
    NoteMove(20, 42);
    NoteMove(20, 33); 
    NoteMove(20, 46);
    NoteMove(20, 0);
    NoteMove(20, 1);
    NoteMove(20, 10);
    NoteMove(20, 24);
    
    NoteMove(20, 36);
    NoteMove(20, 7);
    NoteMove(20, 47);
    NoteMove(20, 26); 
    NoteMove(20, 19);    
    NoteMove(20, 11);
    NoteMove(20, 44);
    NoteMove(20, 45);
    NoteMove(20, 32);
    NoteMove(20, 27);
    
    NoteMove(20, 8);
    NoteMove(20, 16);
    
    if ((notes[16].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[16].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }
  
  void song8(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Firework
    
    NoteMove(20, 26);
    NoteMove(20, 47);
    NoteMove(20, 36);
    NoteMove(20, 24);
    NoteMove(20, 25);
    NoteMove(20, 14);
    NoteMove(20, 0);
    NoteMove(20, 11);
    NoteMove(20, 6);
    NoteMove(20, 23);
    
    NoteMove(20, 22);
    NoteMove(20, 33);
    NoteMove(20, 35);
    NoteMove(20, 27);
    NoteMove(20, 5); 
    NoteMove(20, 17);
    NoteMove(20, 45);
    NoteMove(20, 21);
    NoteMove(20, 12);
    NoteMove(20, 2);
   
    NoteMove(20, 28);
    NoteMove(20, 38);
    NoteMove(20, 46);
    NoteMove(20, 40); 
    NoteMove(20, 20);    
    NoteMove(20, 31);
    NoteMove(20, 42);
    NoteMove(20, 3);
    NoteMove(20, 4);
    NoteMove(20, 15);
    
    NoteMove(20, 44);
    NoteMove(20, 8);
    NoteMove(20, 37);
    NoteMove(20, 7);
    
    if ((notes[7].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[7].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }    
  }
  
  void song9(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Wake Me Up
    
    NoteMove(20, 9);
    NoteMove(20, 33);
    NoteMove(20, 24);
    NoteMove(20, 25);
    NoteMove(20, 1);
    NoteMove(20, 44);
    NoteMove(20, 2);
    NoteMove(20, 47);
    NoteMove(20, 46);
    NoteMove(20, 29);
    
    NoteMove(20, 3);
    NoteMove(20, 34);
    NoteMove(20, 36);
    NoteMove(20, 15);
    NoteMove(20, 11); 
    NoteMove(20, 6);
    NoteMove(20, 45);
    NoteMove(20, 31);
    NoteMove(20, 32);
    NoteMove(20, 28);
    
    NoteMove(20, 12);
    NoteMove(20, 10);
    NoteMove(20, 8);
    NoteMove(20, 43); 
    NoteMove(20, 35);    
    NoteMove(20, 17);
    NoteMove(20, 13);
    NoteMove(20, 27);
    NoteMove(20, 40);
    NoteMove(20, 30);
   
    NoteMove(20, 20);
    NoteMove(20, 21);

    if ((notes[21].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[21].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }
  
  void song10(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Honey I'm Good
   
    NoteMove(20, 18);
    NoteMove(20, 8);
    NoteMove(20, 38);
    NoteMove(20, 28);
    NoteMove(20, 37);
    NoteMove(20, 2);
    NoteMove(20, 3);
    NoteMove(20, 44);
    NoteMove(20, 47);
    NoteMove(20, 32);
   
    NoteMove(20, 27);
    NoteMove(20, 15);
    NoteMove(20, 11);
    NoteMove(20, 5);
    NoteMove(20, 0); 
    NoteMove(20, 34);
    NoteMove(20, 21);
    NoteMove(20, 25);
    NoteMove(20, 46);
    NoteMove(20, 14);
   
    NoteMove(20, 6);
    NoteMove(20, 7);
    NoteMove(20, 36);
    NoteMove(20, 24); 
    NoteMove(20, 16);    
    NoteMove(20, 45);
    NoteMove(20, 12);
    NoteMove(20, 33);
    NoteMove(20, 1);
    NoteMove(20, 23);
    
    NoteMove(20, 40);
    NoteMove(20, 10);
    NoteMove(20, 42);
    NoteMove(20, 30);
    NoteMove(20, 31);
    
    if ((notes[31].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      reset_level();
    }
    else if ((notes[31].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }

  void song11(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //Staying Alive
   
    NoteMove(10, 36);
    NoteMove(10, 13);
    NoteMove(10, 3);
    NoteMove(10, 26);
    NoteMove(10, 0);
    NoteMove(10, 40);
    NoteMove(10, 31);
    NoteMove(10, 28);
    NoteMove(10, 9);
    NoteMove(10, 16);
    
    NoteMove(10, 33);
    NoteMove(10, 5);
    NoteMove(10, 37);
    NoteMove(10, 44);
    NoteMove(10, 18); 
    NoteMove(10, 6);
    NoteMove(10, 24);
    NoteMove(10, 21);
    NoteMove(10, 10);
    NoteMove(10, 7);
 
    NoteMove(10, 25);
    NoteMove(10, 12);
    NoteMove(10, 41);
    NoteMove(10, 20); 
    NoteMove(10, 8);    
    NoteMove(10, 30);
    NoteMove(10, 42);
    NoteMove(10, 14);
    NoteMove(10, 38);
    NoteMove(10, 27);
    
    NoteMove(10, 32);
    NoteMove(10, 17);
    NoteMove(10, 39);
    NoteMove(10, 46); 
    NoteMove(10, 19);    
    NoteMove(10, 1);
    NoteMove(10, 2);
    NoteMove(10, 15);
    NoteMove(10, 23);
    NoteMove(10, 43);
   
    NoteMove(10, 4);
    NoteMove(10, 22);
    NoteMove(10, 11);
    NoteMove(10, 29);
    NoteMove(10, 34);
    NoteMove(10, 47);
    NoteMove(10, 35);
    NoteMove(10, 45);
    
    if ((notes[45].get_y() >= 12) && (scoreCalc(numNotesHit) >= 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameWin = true;
    }
    else if ((notes[45].get_y() >= 12) && (scoreCalc(numNotesHit) < 60)) {
      matrix.fillScreen(BLACK.to_333());
      print_score();
      delay(2000);
      matrix.fillScreen(BLACK.to_333());
      gameLose = true;
    }
  }  
  
  // sets up a new game
  // Modifies: global variable matrix
  // see http://arduino.cc/en/Reference/Setup
  void setup() {
    score = 0;
    songNum = 1;
    print_level(songNum);
    delay(2000);
    matrix.fillScreen(BLACK.to_333());

    for (int i = 0; i < NUM_NOTES; i++) {
      if ((i >= 0) && (i <= 11)) {
        notes[i].initialize(3, -10);  //If we change the move function to try and hide bugs, also change the y being set here
      }
      else if ((i >= 12) && (i <= 23)) {
        notes[i].initialize(11, -10);
      }
      else if ((i >= 24) && (i <= 35)) {
        notes[i].initialize(18, -10);
      }
      else if ((i >= 36) && (i <= 47)) {
        notes[i].initialize(26, -10);
      }
      notes[i].draw();
    }
  }
  
  // displays and runs Game
  // see spec for details of game
  // Modifies: global variable matrix
  void loop(bool button_pressed, bool white_button_pressed, bool yel_button_pressed, bool blue_button_pressed) {
    //REACH LOOP
    Background bg1;
    bg1.background();

    if (songNum == 1) {
       Serial.println("1");
       song1(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 2) {
       Serial.println("2");
       song2(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 3) {
       Serial.println("3");
       song3(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 4) {
       Serial.println("4");
       song4(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 5) {
       Serial.println("5");
       song5(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 6) {
       Serial.println("6");
       song6(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 7) {
       Serial.println("7");
       song7(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 8) {
       Serial.println("8");
       song8(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 9) {
       Serial.println("9");
       song9(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 10) {
       Serial.println("10");
       song10(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    if (songNum == 11) {
       Serial.println("-");
       song11(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
    }
    
    for (int i = 0; i < NUM_NOTES; i++) {
       if ((i >= 0) && (i <= 11)) {
         redNoteClicked(button_pressed, i);
       }
       else if ((i >= 12) && (i <= 23)) {
         whiteNoteClicked(white_button_pressed, i);
       }
       else if ((i >= 24) && (i <= 35)) {
         yelNoteClicked(yel_button_pressed, i);
       }
       else if ((i >= 36) && (i <= 47)) {
         blueNoteClicked(blue_button_pressed, i);
       }
    }
    
  }
  private:
  int level;
  unsigned long time;
  long lastMillisRed = 0;
  long lastMillisWhite = 0;
  long lastMillisYellow = 0;
  long lastMillisBlue = 0;
  long lastMillisDouble = 0;
  int songNum;
  int numNotesHit = 0;
  int numNotesInSong = 0;
  int score = 0;
  Notes notes[NUM_NOTES];
 
};


// a global variable that represents the game
GameMusic music;

// see http://arduino.cc/en/Reference/Setup
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  pinMode(WHITE_PIN_NUMBER, INPUT);
  pinMode(YEL_PIN_NUMBER, INPUT);
  pinMode(BLUE_PIN_NUMBER, INPUT);
  pinMode(POTENTIOMETER_PIN_NUMBER, INPUT);
  
  matrix.begin();

  print_game_name();
  delay(2500);
  matrix.fillScreen(BLACK.to_333());
  
  music.setup();
}

// see http://arduino.cc/en/Reference/Loop
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  bool white_button_pressed = (digitalRead(WHITE_PIN_NUMBER) == HIGH);
  bool yel_button_pressed = (digitalRead(YEL_PIN_NUMBER) == HIGH);
  bool blue_button_pressed = (digitalRead(BLUE_PIN_NUMBER) == HIGH);

  if ((gameLose == false) && (gameWin == false)) {
    music.loop(button_pressed, white_button_pressed, yel_button_pressed, blue_button_pressed);
  }
  else if (gameWin == true) {
    matrix.fillScreen(BLACK.to_333());
    game_win();
    delay(2000);
    matrix.fillScreen(BLACK.to_333());
    return;  
  }
  else {
    matrix.fillScreen(BLACK.to_333());
    game_over();
    delay(2000);
    matrix.fillScreen(BLACK.to_333());
    return;
  }

}

// displays Level
void print_level(int level) {
  matrix.setTextColor(ORANGE.to_333());
  matrix.setTextSize(1);
  matrix.setCursor(0,0);
  matrix.print('L');
  matrix.print('E');
  matrix.print('V');
  matrix.print('E');
  matrix.print('L');
  
  //":"
  matrix.drawPixel(30, 2, ORANGE.to_333());
  matrix.drawPixel(30, 4, ORANGE.to_333());
  
  if ((level >= 1) && (level <= 10)) {
    matrix.setTextColor(ORANGE.to_333());
    matrix.setTextSize(1);
    matrix.setCursor(15,9);
    matrix.print(level);
  }
  if (level == 11) {
    matrix.setTextColor(RED.to_333());
    matrix.setTextSize(1);
    matrix.setCursor(4,9);
    matrix.print('B');
    matrix.print('O');
    matrix.print('S');
    matrix.print('S');
  }

}

//displays game name
void print_game_name() {
  matrix.setTextColor(BLUE.to_333());
  matrix.setTextSize(1);
  matrix.setCursor(1, 0);
  matrix.print('M');
  matrix.print('U');
  matrix.print('S');
  matrix.print('I');
  matrix.print('C');
  matrix.setCursor(5, 9);
  matrix.setTextColor(PURPLE.to_333());
  matrix.print('H');
  matrix.print('E');
  matrix.print('R');
  matrix.print('O');
}

// displays "game over"
void game_over() {
  matrix.setTextColor(RED.to_333());
  matrix.setTextSize(1);
  matrix.setCursor(4,0);
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E');
  matrix.setCursor(4, 9);
  matrix.print('O');
  matrix.print('V');
  matrix.print('E');
  matrix.print('R'); 
}

// displays "WIN GAME"
void game_win() {
  matrix.setTextColor(GREEN.to_333());
  matrix.setTextSize(1);
  matrix.setCursor(8,0);
  matrix.print('W');
  matrix.print('I');
  matrix.print('N');
  matrix.setCursor(4, 9);
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E'); 
}

