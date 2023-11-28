#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#include <IRremote.h>

#define SENSOR_TMP A0
#define LED_VERDE 13
#define LED_ROJO 12
#define SERVO 3
#define BOTON_0 0xF30CBF00
#define BOTON_1 0xEF10BF00
#define BOTON_2 0xEE11BF00
#define BOTON_3 0xED12BF00
#define FUNC_STOP 0xFD02BF00
#define DATOS_INFRARROJO 11

LiquidCrystal_I2C lcd(34, 16, 2); 
Servo mi_servo;

int info_sensor_tmp;
int temperatura;
String estacion = "Spring";
String mensaje_temperatura = "Temp: ";
bool sistema_incendio_encendido = true;
int limite_temperatura = 44;
int resultado;
bool incendio_en_curso = false;

void setup()
{
  lcd.init(); 
  lcd.backlight();
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  mi_servo.attach(SERVO,400,2600);
  mi_servo.write(0);
  IrReceiver.begin(DATOS_INFRARROJO, DISABLE_LED_FEEDBACK);
  Serial.begin(9600);
}

void loop()
{   
  detectar_botones();  
  temperatura = sensor_temperatura();
  detectar_incendio(temperatura,limite_temperatura);
  escribir_display();   
  delay(500);       
}

void detectar_botones()
{
  if (IrReceiver.decode()) 
  {          
   // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  
    switch (IrReceiver.decodedIRData.decodedRawData)
  	{
      case BOTON_0:
        estacion = "Spring";
   		limite_temperatura = 44;
        break;

      case BOTON_1:
         estacion = "Summer";
    	 limite_temperatura = 50;
        break;

      case BOTON_2:
        estacion = "Autumn";
        limite_temperatura = 40;
        break;

      case BOTON_3:
        estacion = "Winter";
        limite_temperatura = 36;
        break;
      
      case FUNC_STOP:
        sistema_incendio_encendido = !sistema_incendio_encendido;
        break;      
     }
    IrReceiver.resume();
  }   
}

int sensor_temperatura()
{
  info_sensor_tmp = analogRead(SENSOR_TMP);
  resultado = map(info_sensor_tmp, 20, 358, -40, 125); 
  return resultado;
}

void escribir_display()
{
  if(incendio_en_curso)
  {
    lcd.setCursor(0,0);
    lcd.print("Se detecto un"); 
    lcd.setCursor(0,1);
    lcd.print("incendio!       "); 
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print(mensaje_temperatura);
    lcd.print(temperatura);
    lcd.print("C     ");  
    lcd.setCursor(0,1); 
    lcd.print(estacion);  
    lcd.setCursor(6,1); 
    lcd.print("  Sist.");  
    if(sistema_incendio_encendido)
    {
      lcd.setCursor(13,1);
      lcd.print("On ");  
    }
    else
    {
      lcd.print("Off");
    }  
  }  
}

void detectar_incendio(int temperatura,int limite_temperatura)
{
  if(sistema_incendio_encendido && temperatura > limite_temperatura)
  {       
    sistema_contra_incendios();
    encender_leds(0,1);
    incendio_en_curso = true;    
  }  
  else
  {
    mi_servo.write(0); 
    encender_leds(1,0);
    incendio_en_curso = false;
  }
}

void sistema_contra_incendios()
{
  Serial.println("Sistema contra incendios activado") ;
  mi_servo.write(90);
}

void encender_leds(int led_verde,int led_rojo)
{
  digitalWrite(LED_VERDE, led_verde);
  digitalWrite(LED_ROJO, led_rojo);
}
