# Para pensar luego de resolver el ejercicio:

* ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?
**En esta biblioteca de debounce el usuario no hace ingreso de datos**
* ¿Se nota una mejora en la detección de las pulsaciones respecto a la práctica 0?¿Se pierden pulsaciones? ¿Hay falsos positivos?
**No pareceria que se pierdan pulsaciones o que hubieran falsos positivos**
* ¿Es adecuada la temporización con la que se llama a debounceFSM_update()? ¿Y a readKey()? ¿Qué pasaría si se llamara con un tiempo mucho más grande? ¿Y mucho más corto?
**El criterio con que se eligio el refresco de la FSM es que dado se estan buscando señales con frecuencias de 1/40ms, de acuerdo con Nyquist la frecuencia de sampleo debe ser mayor o igual al doble de la frecuencia. Por lo que se eligio una frecuencia que tenga un periodo de 10ms**