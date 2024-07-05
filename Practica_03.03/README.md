# Para pensar luego de resolver el ejercicio:

* ¿Es suficientemente clara la consigna 2 o da lugar a implementaciones con distinto comportamiento?
**Parece clara la consigna.**

* ¿Se puede cambiar el tiempo de encendido del led fácilmente en un solo lugar del código o éste está hardcodeado? ¿Hay números “mágicos” en el código?

**El tiempo de encendido se puede cambiar en un único punto de código y es en la línea 74 del archivo main.c.**

* ¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código compile? Si las funcionalidades de una API propia crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usen en la implementación, ¿Cuál sería el mejor lugar?.

**Las bibliotecas estandar que se debieron agregar a API_delay.h son: stdbool.h, stdint.h y stm32f4xx_hal.h**

* ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos esperados?

**Se valida que el puntero a la estructura delay sea distinto de NULL y que duration sea menor o igual a MAXdELAY.**
