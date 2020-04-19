Trabajo Practico Driver

Usando el código provisto y los comandos de carga y descarga de drivers, se cargó el modulo "miModulo.c". En primer lugar se instalaron module-init-tools
y linux-headers con los siguientes comandos:

>>sudo apt-get update
>>sudo apt-get install module-init-tools

>>sudo apt-get update
>>sudo apt install linux-headers-$(uname -r)

Luego, despues de transcribir el código del makefile, se ejecutó el comando make clean & make.
Luego, se ejecutó el comando insmod el cual carga el modulo.  

>>sudo insmod ./miModulo.ko

Para verificar la carga, introducimos el comando lsmod el cual lista los modulos, luego el comando "rmmod", que descarga el modulo. Para ver dichos cambios
ejecutamos el comando dmesg, con el cual vemos el log del kernel.

>>sudo lsmod (imagen: miModulo.c registrado.png)
>>sudo rmmod ./miModulo.ko
>>sudo dmesg (imagen: Dmesg del driver miModulo.c.png)

Respecto al modulo Char Device

Se creo el archivo.c llamado "taichi.c" y el archivo makefile. 
Nuevamente se ejecutó make clean & make.
Luego, una vez creamos los archivos temporales, se ejecutó el comando "insmod" para la carga del modulo, "dmesg" para ver el log del kernel y "lsmod"
para verificar la lista de modulos. 

Comandos:  (imagen: Carga del modulo taichi.png)
>>cd Escritorio
>>make clean
>>make
>>sudo insmod ./taichi.ko
>>sudo dmesg
>>sudo lsmod 

Para verificar la ejecución del modulo em lectura y escritura, se realizo una prueba con los siguientes comandos:
(imagen: Ejecucion Lectura y Escritura modulo taichi.png)

>>cd Escritorio
>>sudo mknod /dev/taichi c 60 0   (creamos la carpeta para nuestro driver, c: char device, 60: major number, 0: minor number)
>>sudo chmod 777 /dev/taichi    (Habilitamos permisos)
>>echo "Probamos escritura" >> /dev/taichi 
>>cat /dev/taichi
>>"Probamos escritura"

Observamos que devuelve lo ultimo que fue escrito.

Por ultimo, realizamos los comandos de descarga del modulo utilizando las siguientes instrucciones:
(Imagen: Descarga modulo taichi.png)

>>sudo rmmod ./taichi.ko  (Descargamos modulo)
>>sudo rm /dev/taichi     (Eliminamos la carpeta donde se guardaba el driver)
>>sudo dmesg      (Verificamos)
>>sudo lsmod
