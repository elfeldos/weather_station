#include <Arduino.h>
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
// set up dht instance by defining pin and type
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup( )
{
  Serial.begin( 9600);
  // // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // // Print a message to the LCD.
  // lcd.print("Moin Franco!");
}

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 300000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}

/*
 * Main program loop.
 */
void loop( )
{
  float temperature;
  float humidity;
  // lcd.setCursor(0, 0);
  // lcd.print(temperature);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print(millis() / 1000);

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");

    lcd.setCursor(6, 0);
    lcd.print(temperature, 1);

    lcd.setCursor(11, 0);
    lcd.print("*C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");

    lcd.setCursor(6, 1);
    lcd.print(humidity, 1);

    lcd.setCursor(11, 1);
    lcd.print("%");

    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  }
}



