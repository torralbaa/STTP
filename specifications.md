## Simple Text Transfer Protocol (STTP/1.0)

### Aviso de licencencia(s):
Las especificaciones y la documentación STTP de [Álvaro Torralba](https://github.com/Alvarito050506/) están licenciados bajo la [Creative Commons Attribution-ShareAlike International License 4.0](http://creativecommons.org/licenses/by-sa/4.0/).

### Abstracto
Este documento describe STTP, un protocolo "de juguete" para enviar mensajes en formato de texto plano entre computadoras.

### 1. Introducción
#### 1.1. Propósito
El Protocolo de Transferencia de Texto Simple (STTP, por sus siglas en inglés) es un protocolo de nivel de aplicación "de juguete" diseñado para enviar mensajes en formato de texto plano (text/plain) entre computadoras. Actualmente sólo está implementado para sistemas Unix.
#### 1.2. Requisitos
Una implementación no es compatible si no cumple con uno o más de los requisitos de nivel OBLIGATORIO para los protocolos que implementa. Se dice que una implementación que satisfaga todos los niveles OBLIGATORIOS es compatible.

### 2. Protocolo STTP
#### 2.1. Operación general
En el protocolo STTP el servidor se mantiene a la escucha de que algún cliente que se conecte a él y envíe un mensaje codificado en UTF-8. Cuando el servidor recibe el mensaje envía al cliente una confirmación de esto, muestra el mensaje recibido repite el proceso. Si este falla en algún momento, el servidor enviará el código del error ocurrido más un mensaje que lo describa al cliente.

La comunicación STTP se lleva a cabo a través de conexiones TCP/IP. El puerto predeterminado para el protocolo es 3890, lo que no impide que se implemente en cualquier otro puerto.

Las comunicaciones STTP son iniciadas por un usuario que envía un mensaje al servidor. Estas deben llevarse a cabo a través de una única conexión (C) entre el cliente (U) y el servidor (S).
```
mensaje -----> U --- C --- S <----- confirmación
```

### 3. Convenciones de notación y gramática genérica
#### 3.1. Construcciones genéricas RFC 822
Todos los mecanismos especificados en este documento se describen tanto en prosa como en construcciones genéricas definidas en el [RFC 822](https://tools.ietf.org/html/rfc822).
#### 3.2. Reglas básicas
Las siguientes reglas son las que se usarán a lo largo de esta especificación.
```
CHAR      = <cualquier carácter UTF-8>
DIGIT     = <cualquier díguito UTF-8>
UPLETTER  = <cualquier letra mayúscula UTF-8 "A"..."Z">
LOWLETTER = <cualquier letra minúscula UTF-8 "a"..."z">
LETTER    = UPLETTER / LOWLETTER
```
### 4. Parámetros del protocolo
#### 4.1. Versiones STTP
STTP, al igual que otros protocolos utiliza el sistema de numeración de versiones "\<major>.\<minor>".

El número \<minor> se incrementa cuando los cambios realizados en el protocolo agregan características que no crean incompatibilidad con versiones anteriores. El número \<major> se incrementa cuando se realizan cambios que generan incompatibilidades con versiones aneriores.

La versión de un mensaje STTP se indica en el mensaje de que confirma la conexión entre el servidor y el cliente.
```
STTP-Version = "STTP" "/" 1*DIGIT "." 1*DIGIT
```
La versión STTP de una aplicación es la versión STTP más alta para la cual la aplicación cumpla los requisitos.
#### 4.2. URIs STTP
En realidad, los URIs STTP no existen, ya que el único dato que le tiene que proporcionar el usuario al cliente es el DNS si el servidor está fuera de la red local o el nombre de la máquina si el servidor está dentro de la red local. Aún así, si se desea indicar que el una URL apunta a un servidor STTP, se puede implementar el siguiente esquema:
```
STTP-URL = "sttp:" "//" host [":" puerto]
```
#### 4.3. Codificación de los datos
Todos los datos que se transmiten mediante STTP lo hacen bajo el MIME type text/plain usando el charset **UTF-8**.

### 5. Mensajes STTP
#### 5.1. Tipos de mensajes
Los tipos de mensajes que existen son: estados de servidor a cliente y texto del cliente al servidor.
```
STTP-Message = Estados / Texto
```
Los mensajes de estado le informan al cliente y, a veces, al mismo servidor el estado del proceso y la conexión. Los mensajes de texto le envían al servidor el texto que ingresó el usuario en el cliente.
#### 5.2. Mensajes de estado
Los mensajes de estado envían un código de estado de tres dígitos junto con una breve descripción del mismo.

El primer dígito del código de estado define de que tipo es. Los dos últimos dígitos no tienen ningún valor de categorización. Hay tres valores para el primer dígito:

- 1xx: Éxito - La acción fue aceptada y completada con éxito.
- 2xx: Error del servidor - La acción requerida no se puede efectuar a causa de un error en el servidor.
- 3xx: Error del cliente - La acción requerida no se puede efectuar a causa de un error en el cliente.

Los mensajes de estado usan los siguientes esquemas:
```
STTP-Status_code = (100 / 101 / 200 / 201 / 202 / 300 / 301)
STTP-Status_text = ("Mensaje recibido." / "Conectado." / "No se pudo escribir o leer el socket." / "No se pudo crear el socket." / "El puerto necesario no está disponible." / "No se especificó un host." / "El host especificado no es válido.")
STTP-Status = STTP-Status_code "-" STTP-Status_text
```
#### 5.3. Mensajes de texto
Los mensajes de texto del cliente al servidor, como ya se mencionó, envían al servidor el texto que ingresó el usuario, pero también envían una pequeña indicación que dice que el ya mencionado es el mensaje que se obtuvo del cliente. Utilizan el siguiente esquema:
```
STTP-Text = indication [":"] user_text
```

### 6. Definiciones de códigos de estado
#### 6.1. 1xx - Éxito
Esta clase de código de estado indica que el mensaje del cliente fue recibido, entendido y aceptado satisfactoriamente.
#### 6.1.1. 100 - Mensaje recibido
Indica que todo el proceso fue llevado a cabo con éxito y que se recibió el mensaje de texto del cliente.
#### 6.1.2. 101 - Conectado
Indica que se estableció correctamente una conexión entre el cliente y el servidor y la versión del protocolo. El servidor también recibe la dirección IP del cliente junto con este mensaje.
#### 6.2. 2xx - Error del servidor
Esta clase de código de estado indica casos en los que el servidor no puede realizar una acción a causa de algún impedimento.
#### 6.2.1. 200 - No se pudo escribir o leer el socket
Indica que ocurrió un error al leer o escribir el socket del cliente.
#### 6.2.2. 201 - No se pudo crear el socket
Indica que ocurrió un error al crear el socket en el cliente.
#### 6.2.3. 202 - El puerto necesario no está disponible
Indica que el puerto necesario para crear la conexión (3890) no está disponible en el servidor.
#### 6.3. 3xx - Error del cliente
Esta clase de código de estado indica casos en los que el cliente parece haber cometido algún error.
#### 6.3.1. 300 - No se especificó un host
Indica que el usuario no le especificó un host al que conectarse al cliente.
#### 6.3.2. 301 - El host especificado no es válido
Indica que el host que el se especificó al cliente no es válido o está desconectado.

### 7. Consideraciones de seguridad
Advertencia: STTP/1.0 **NO BRINDA ABSOLUTAMENTE NINGUNA GARANTÍA DE CALIDAD, SEGURIDAD O PROTECCIÓN DE DATOS.**

Esta sección está destinada a informar a todos aquellos que desarrollen, provean y/o usen servicios o aplicaciones STTP/1.0 sobre las limitaciones de seguridad en este.
#### 7.1. Información personal e información sensible
Son una realidad la fuga de datos, el robo de identidad y muchos otros inconvenientes causados por la falta de control sobre la información por parte los usuarios de Internet. Por ese mismo motivo no se recomienda enviar o recibir datos personales a través del protocolo STTP por la obvia razón de que este no utiliza ningún algoritmo de cifrado o codificado durante la transmisión de datos, aunque estos se podrían implementar.
#### 7.2. Abuso de la información por parte del servidor
El servidor al cual un cliente se conecta está en posición de guardar toda la información que se le brinde, incluidas IP, ubicación, idioma y (NO RECOMENDADO) datos personales. Toda esta información, como era de suponer, es de carácter confidencial por naturaleza y quienes la distribuyan deberán garantizar que dicho material no se distribuya sin el permiso de cualquier persona que sea identificable por los resultados publicados. Actualmente hay países en los que el uso de esta información está restringido o controlado por las leyes, tratados o directivas.
#### 7.3. Transferencia de datos ilegales
Como cualquier otro protocolo de tranferencia de datos, STTP no puede controlar la información que se transmite mediante el mismo, lo cual sería ilegal en muchos países. Por este motivo ni los proveedores de servicios ni los desarrolladores se harán cargo de cualquier inconveniente causado por tráfico de información ilegal, secreta o restringida.

Hata este momento no se han encontrado vulnerabilidades técnicas que afecten a la seguridad en el protocolo, pero existen.

### 8. Agradecimientos
En esta especificación se ha hecho uso de las construcciones genéricas definidas por David H. Crocker para el [RFC 822](https://tools.ietf.org/html/rfc822) y su estructura está basada en la del [RFC 2616](https://tools.ietf.org/html/rfc2616).

Agradezco también a todos aquellos que trabajan para que Internet sea lo que es hoy y más.

### 9. Datos del autor
Álvaro Torralba \<donfrutosgomez@gmail.com> (http://alvarito050506.tk/)

### Anexo A. Errores conocidos o posibles
Nota: Este anexo solamente debe tomarse en cuenta si se está leyendo esta especificación desde el repositorio git oficial del protocolo, donde hay implementaciones del mismo.
