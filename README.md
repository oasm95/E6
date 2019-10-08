# E6

Clase1:

    se creó un modulo sensillo que demuestra lógica combinacional y secuencial, 
    se lee el valor de los switches de la zybo, dependiendo el valor de los 
    switches, cambiará valor que despliegan los led(2-0) y varia la velocidad 
    de un blinking led {led(3)}.

    Se creó un testbench que estimula los valores de entrada del modulo anterior
    desplegando el resultado, para ser utilizado en una simulación y comprobar el
    correcto funcionamiento.
  
 Clase2:

    Se utiliza el código del modulo de la clase1 y se utiliza para crear un 
    IP Core con interfaz AXI-Lite

 Clase 3:
 
    Se creó un IPCore el cual funciona como un simple GPIO de entrada capaz 
    de generar y controlar una interrupcion generada por flanco de subida.
