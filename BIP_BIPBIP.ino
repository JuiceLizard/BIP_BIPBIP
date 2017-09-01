/*"Bip Bipbip"
 * 
 * A Pong demake by Juice Lizard
 * coded on Friday, September 01, 2017
 * that allows two players to compete
 * in a real one dimensional video game!
 * 
 * Le seul et unique jeu 1D !!!
 * 
 * Left button is for the left player.
 * B button is for the right player.
 * 
 * You lose when you reach the middle of the screen
 * or when the ball touches you when you don't press your button.
 * 
 * The winner has the white on his side.
 * He starts a new game when pressing his button.
 * 
 * Buy my paintings
 * and sell it one year later
 * a hundred times its price!
 * www.juicelizard.canalblog.com
 * juice.lizard@hotmail.fr
 */

#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

#define START 0
#define PLAY 1
#define SCORE 2
#define WINNER_LEFT 1
#define WINNER_RIGHT 2

byte gameState = START;
byte winner = 0;
byte xLeftPlayer;
byte leftSize;
byte xRightPlayer;
byte rightSize;
byte xBall;
bool ballGoesRight = true;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.audio.on();
}

void loop() {
  if (!(arduboy.nextFrame()))
  return;

  switch(gameState){
    case START:
      xLeftPlayer = 2;
      leftSize = 2;
      xRightPlayer = 126;
      rightSize = 2;
      xBall = 63;
      gameState = PLAY;
     break;
    
    case PLAY:
      arduboy.pollButtons();
      arduboy.clear();
  
      if (xBall > xRightPlayer) {
        sound.tone(1200, 100);
        ballGoesRight = false;
      }
      if (xBall < xLeftPlayer) {
        sound.tone(1200, 100);
        ballGoesRight = true;
      }

      if (ballGoesRight) {
        xBall = xBall + 1;
      }
      if (!ballGoesRight) {
        xBall = xBall - 1;
      }

      if (arduboy.pressed(LEFT_BUTTON) && !ballGoesRight) {
        leftSize = leftSize + 1;
        xLeftPlayer = xLeftPlayer + 1;
      }
      if (arduboy.pressed(B_BUTTON) && ballGoesRight) {
        rightSize = rightSize + 1;
        xRightPlayer = xRightPlayer - 1;
      }

      if (((xBall == (xLeftPlayer - 1)) && !(arduboy.pressed(LEFT_BUTTON))) || (xLeftPlayer > 62)) {
        winner = WINNER_RIGHT;
        gameState = SCORE;
      }
      if ((xBall == (xRightPlayer + 1)) && !(arduboy.pressed(B_BUTTON)) || (xRightPlayer < 65)) {
        winner = WINNER_LEFT;
        gameState = SCORE;
      }

      arduboy.fillRect(0, 0, xLeftPlayer, 64, WHITE);
      arduboy.fillRect(xBall, 0, 2, 64, WHITE);
      arduboy.fillRect(xRightPlayer, 0, rightSize, 64, WHITE);
      arduboy.display();
      break;

    case SCORE:
      arduboy.clear();
      if (winner == WINNER_LEFT) {
        arduboy.clear();
        arduboy.fillRect(0, 0, 64, 64, WHITE);
        arduboy.display();
        delay(1500);
          while(!arduboy.justReleased(LEFT_BUTTON)) {
          delay(5);
          arduboy.pollButtons();
        }
        ballGoesRight = false;
        gameState = START;
      }
      
      if (winner == WINNER_RIGHT) {
        arduboy.clear();
        arduboy.fillRect(64, 0, 64, 64, WHITE);
        arduboy.display();
        delay(1500);
        while(!arduboy.justReleased(B_BUTTON)) {
          delay(5);
          arduboy.pollButtons();
        }
        ballGoesRight = true;
        gameState = START;
      }
      break;
  }
}
