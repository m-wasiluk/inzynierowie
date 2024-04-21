#include "motor_driver.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CENG_init(){
  //ustawienie stanu wyjść
  pinMode (AIN1_PIN, OUTPUT);
  pinMode (BIN1_PIN, OUTPUT);
  pinMode (AIN2_PIN, OUTPUT);
  pinMode (BIN2_PIN, OUTPUT);
  pinMode (PWMA_PIN, OUTPUT);
  pinMode (PWMB_PIN, OUTPUT);
  pinMode (STBY_PIN, OUTPUT);

  //wyłączenie powerSaveMode
  digitalWrite(STBY_PIN, HIGH);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void CENG_setEngines( float vA, bool gA, float vB, bool gB ){
  if( vA > 100 )  vA = 100;
  if( vB > 100 )  vB = 100;
  if( vA < 0 )    vA = 0;
  if( vB < 0 )    vB = 0;
  

  vA = vA * 2.55;
  digitalWrite( AIN1_PIN, gA );
  digitalWrite( AIN2_PIN, !gA );
  analogWrite( PWMA_PIN, vA );

  vB = vB * 2.55;
  digitalWrite( BIN1_PIN, gB );
  digitalWrite( BIN2_PIN, !gB );
  analogWrite( PWMB_PIN, vB );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void CENG_tip( int angle, bool side ){
  int stopTime   = 1500 / 90 * angle;
  int turnSpeed  = 55;
  
  if( side ){
    CENG_setEngines( 0, 0, turnSpeed, 0 );
  }else{
    CENG_setEngines( turnSpeed, 0, 0, 0 );
  }

  delay( stopTime );
  CENG_straight( 45, FORWARDS );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void CENG_straight( int Speed, bool Gear ){
  CENG_setEngines( 80, Gear, 80, Gear );
  delay( 100 );
  CENG_setEngines( Speed*1.1, Gear, Speed, Gear );
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void CENG_rip(){
  CENG_setEngines( 0, 0, 0, 0 );

}
