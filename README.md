# STTP
Simple Text Transfer Protocol.

En este repositorio se pueden encontrar las especificaciones del Prototocolo de Transferencia de Texto Simple (**STTP**, por sus siglas en inglés) más una implementación de este escrita en C.

#### Aviso de licencencia(s):

Las especificaciones y la documentación STTP de [Álvaro Torralba](https://github.com/Alvarito050506/) están licenciados bajo la [Creative Commons Attribution-ShareAlike International License 4.0](http://creativecommons.org/licenses/by-sa/4.0/).

La implementación de STTP es software libre; puedes redistribuirlo y/o modificarlo bajo los términos de la GNU [General Public License](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html) publicada por la [Free Software Foundation](https://www.fsf.org), versión 2.

## Obtener las fuentes
Para obtener el código fuente de la implementación de STTP incluida aquí existen dos opciones:
- Clonar el repositorio: Para clonar el repositorio, ingrese en su terminal el siguiente comando:
```sh
git clone https://github.com/Alvarito050506/Yed.git
```
- Descargar los archivos: para descargar los archivos, ingrese al URL https://github.com/Alvarito050506/STTP y haga click en el botón “_download_”, o, simplemente haga click en el siguiente enlace: [:package:](https://github.com/Alvarito050506/STTP/archive/master.zip)


## Compilar
Para compilar la implementación **STTP** incluida en este repositorio primero [obtenga las fuentes](https://github.com/Alvarito050506/STTP/blob/master/README.md#obtener-las-fuentes) y luego ingrese los siguientes comandos:
```sh
unzip ./STTP-master
cd ./STTP-master
make
```

## Errores conocidos o posibles
Advertencia: STTP/1.0 **NO BRINDA ABSOLUTAMENTE NINGUNA GARANTÍA DE CALIDAD, SEGURIDAD O PROTECCIÓN DE DATOS.**

Se ha encontrado un posible error en la implementación escrita en C adjunta en este repositorio: Si usted acaba de terminar de ejecutar un servidor, para volver a ejecutarlo tendrá que esperar apróximadamente 30 segundos porque, al parecer, el servidor tarda la cantidad de tiempo ya mencionada para cerrar el puerto 3890 de la computadora y devolverá el error 202 si este no está disponible.
