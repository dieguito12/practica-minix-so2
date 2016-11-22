#include <lib.h>
#include <unistd.h>
#include <stdio.h>

int sem_create(int sem_id)
{
	message m;
	m.m1_i1 = sem_id;
	m.m1_i2 = getpid();
	
	if (sem_id > 30 || sem_id < 0) {
		printf("El ID del semaforo debe ser un numero entre 0 y 30\n");
		return -1;
	}	
	int aux = (_syscall(PM_PROC_NR, PM_SEM_CREATE, &m));

	if(aux==-1)
	{
		printf("Error al crear el Semaforo \n ");		
	}
	else
	{
		printf("El Semaforo fue creado con Exito \n");	
	}
	return aux;
}

int sem_terminate(int sem_id)
{
	message m;
	m.m1_i1 = sem_id;
	if (sem_id > 30 || sem_id < 0) {
		printf("El ID del semaforo debe ser un numero entre 0 y 30\n");
		return -1;
	}
	m.m1_i2 = getpid();
	int aux = (_syscall(PM_PROC_NR, PM_SEM_TERMINATE, &m));
	
	if(aux==-1)
	{
		printf("Error al destruir el semaforo\n");
	}
	else
	{
		printf("Semaforo destruido correctamente\n");
	}
	return aux;
}

int sem_down(int sem_id)
{
	message m;
	m.m1_i1 = sem_id;
	if (sem_id > 30 || sem_id < 0) {
		printf("El ID del semaforo debe ser un numero entre 0 y 30\n");
		return -1;
	}
	m.m1_i2 = getpid();
	int aux = (_syscall(PM_PROC_NR, PM_SEM_DOWN, &m));

	if(aux==-1)
	{
		printf("Error al inhabilitar semaforo.\n");
	}
	if(aux==-2)
	{
		printf("Sleep please\n");
		int aux1 = -2;
		while(aux1 != -2){
			aux1 = (_syscall(PM_PROC_NR, PM_SEM_DOWN, &m));
		}
		if(aux1 == 0) {
			printf("Semaforo abajo\n");
			return 0;
		}
	}
	if(aux==0)
	{
		printf("Semaforo abajo!\n");
	}
	return aux;
}

int sem_up(int sem_id)
{
	message m;
	m.m1_i1 = sem_id;
	if (sem_id > 30 || sem_id < 0) {
		printf("El ID del semaforo debe ser un numero entre 0 y 30\n");
		return -1;
	}
	m.m1_i2 = getpid();
	int aux = (_syscall(PM_PROC_NR, PM_SEM_UP, &m));

	if(aux==-1)
	{
		printf("Error al habilitar el semaforo\n");
	}
	else if(aux == -2)
	{
		printf("Sleep please\n");
	}
	else
	{
		printf("Semaforo arriba\n");
	}
	return aux;
}
