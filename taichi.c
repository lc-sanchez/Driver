/*
 * taichi.c - Tp driver OC II 
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>    //Para el put_user y get_user 
#include <linux/string.h>     //Para el memset 

//ATRIBUTOS
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Apruebeme, por favah");
MODULE_AUTHOR("Camila Sanchez");

#define DEVICE_NAME "taichi"  

//DECLARACION DE METODOS
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);


//VARIABLES GLOBALES   
static int Major = 60;          //Major number arbitrario
static char msj[150]={0};    
static short Pos=0;		

//ESTRUCTURA QUE DECLARA LAS FUNCIONES DE ACCESO
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

//LLAMADA CUANDO EL MODULO ESTA CARGADO
int init_module(void)
{
	int ret = register_chrdev(Major, DEVICE_NAME, &fops);
	if (Major < 0) {
		printk(KERN_INFO "Registro fallido.\n");
		
	}
	else{
		printk(KERN_INFO "El Major Number asignado al driver es %d\n", Major);
	}
	return ret;
}

//LLAMADA CUANDO EL MODULO ES DESCARGADO

void cleanup_module(void)
{
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_INFO "Quitando modulo.\n");
	
}

//LLAMADA CUANDO SE INTENTA ABRIR
static int device_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	return 0;
}


//LLAMADA CUANDO SE INTENTA LEER EN EL DEVICE
static ssize_t device_read(struct file *file, char *buffer, size_t len, loff_t *offset){
	
	short contador = 0;
	while (len && msj[Pos] != 0){
		/* Aca usamos put_user, el cual copia data del data segment del 
		 * kernel al data segment del usuario 
		 */
		put_user(msj[Pos], buffer++);
		contador++;
		len--;
		Pos++;
	}
	/* Los metodos de lectura se supone que deben devolver el numero de bytes
	 * que fueron agregados de verdad al buffer 
	 */
	printk(KERN_INFO "Se leyeron %d bytes",contador);
	return contador;
}

//LLAMADA CUANDO SE INTENTA ESCRIBIR EN EL DEVICE FILE
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off){
	
	short indice = 0;
	short contador = 0;
	memset(msj,0,150);
	Pos=0;
	while (len > 0){
		msj[contador++]=buff[indice++];
		len--;
	}
	printk(KERN_INFO "Se escribieron %d bytes",contador);
	return contador;
}

//LLAMADO CUANDO SE CIERRA EL DEVICE FILE
static int device_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;
}





















