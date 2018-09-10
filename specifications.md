### Simple Text Transfer Protocol (STTP/1.0)

#### Aviso de licencencia(s):
Las especificaciones y la documentación STTP de [Álvaro Torralba](https://github.com/Alvarito050506/) están licenciados bajo la [Creative Commons Attribution-ShareAlike International License 4.0](http://creativecommons.org/licenses/by-sa/4.0/).

#### Abstracto
Este documento describe STTP, un protocolo "de juguete" para enviar mensajes en formato de texto plano entre computadoras.

#### 1. Introducción
##### 1.1. Propósito
El Protocolo de Transferencia de Texto Simple (STTP) es un protocolo de nivel de aplicación "de juguete" diseñado para enviar mensajes en formato de texto plano (text/plain) entre computadoras. Actualmente sólo está implementado para sistemas Unix.
##### 1.2. Requisitos
Una implementación no es compatible si no cumple con uno o más de los requisitos de nivel OBLIGATORIO para los protocolos que implementa. Se dice que una implementación que satisfaga todos los niveles OBLIGATORIOS es compatible.

#### 2. Protocolo STTP
##### 2.1. Operación general
En el protocolo STTP el servidor se mantiene a la escucha de que algún cliente que se conecte a él y envíe un mensaje codificado en UTF-8. Cuando el servidor recibe el mensaje envía al cliente una confirmación de esto, muestra el mensaje recibido y sale. Si el proceso falla en algún momento, el servidor enviará el código del error ocurrido más un mensaje que lo describa al cliente.

La comunicación STTP se lleva a cabo a través de conexiones TCP/IP. El puerto predeterminado para el protocolo es 3890, lo que no impide que se implemente en cualquier otro puerto.


