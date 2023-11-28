# Modelo de Sistema de incendios

![Imagen Sistema de incendios](Sistema%20de%20incendios.png)

## Descripción
Simulación de un sistema de incendios configurable con control remoto para determinar funciones como prender/apagar el sistema de detección de incendios e indicar que estación del año transcurre, esto delimitará las temperaturas máximas aceptables para un ambiente seguro. En estado normal, el led verde estará encendido y la temperatura, estación y estado del sistema de detección de incendios se mostrará por un display LCD constantemente, en caso de ocurrir un incendio se indicará por el LCD, el servo motor activará el sistema contra incendios y el led rojo será encendido.

## Función principal
Los estados del sensor de temperatura y señales del control remoto son constantemente observados y el programa actua en consecuencia tomando las acciones pertinentes.

~~~c++
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
~~~

## Link al proyecto
[Sistema de incendios](https://www.tinkercad.com/things/lGLQsdvbMFu?sharecode=bm5o3k-DSUPGoevGUhO3CT9j1sGEWcCdbMCvZCUUL2s)

### Fuentes
- [Tinkercad](https://www.tinkercad.com/)
- [Arduino](https://www.arduino.cc/)
