/* YourDuino.com Example Software Sketch
   Small Stepper Motor and Driver V1.4 11/30/2013
   http://arduino-direct.com/sunshop/index.php?l=product_detail&p=126
   Steps one revolution of output shaft, then back
   terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  
 

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

/*-----( Declare Variables )-----*/
int  Steps2Take;
// 可變電阻接在 Analog pin 0 
int potpin = 0;
// 儲存旋轉角度的變數
int val;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
// Nothing  (Stepper Library sets pins as outputs)
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  val = analogRead(potpin);            // 讀取可變電阻(數值介於 0 到 1023)
  val = map(val, 0, 1023, 0, 179);     // 把 0 - 1023 的數值按比例縮放為 0 - 180 的數值
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
  small_stepper.setSpeed(val*3);   
  small_stepper.step(val);
  delay(15);                           // 等待 Servo 旋轉指定的位置
}/* --(end main loop )-- */

/* ( THE END ) */

