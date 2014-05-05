// testeThreadSDL2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SDL.h"
#include "SDL_thread.h"
#include <iostream>
#include <string>
#include <cstdlib>

#include "Carro.h"

SDL_mutex* mu;
SDL_sem* semAtende;

int sharedBuffer[10];
unsigned long clockInicio;

using namespace std;


// atendimento ---------------------------------------------------
int atende(void *data){

	Carro *c = (Carro *)data;
	int duracao = 8;
	//sscanf_s((char *) data,"%d",&duracao);

	unsigned long t;

	int valSem = SDL_SemValue(semAtende);
	if (valSem<1) cout << "Fila: [" << c->getId() << "]" << endl;
	cout << "S:" << valSem << endl;
	SDL_SemWait(semAtende); //decrementa semaforo e suspende se semAtende ==0

	t = SDL_GetTicks();
	cout << "atende [" << c->getId() << "]" << endl;

	//espera final do atendimento...  
	while (SDL_GetTicks() < (t + duracao * 1000)) {}

	cout << "fim atende" << endl;

	delete c;

	SDL_SemPost(semAtende); //incrementa semaforo

	return 0;
}

// geradores -----------------------------------------------------
int gerador1(void *data){

	SDL_Thread *tAtende[10];
	char *nome = (char *)data;
	Carro *car;
	unsigned long t;
	int i;

	SDL_mutexP(mu);
	for (i = 0; i<10; i++) sharedBuffer[i] = 1;
	SDL_mutexV(mu);

	i = 0;
	while (i<10){
		t = SDL_GetTicks();
		cout << "gerador1 comecou." << endl;

		car = new Carro(i);

		while (SDL_GetTicks() < (t + 1000)) {} //espera 2 segundos
		tAtende[i] = SDL_CreateThread(atende, NULL, (void *)car);

		cout << "gerador1 terminou." << endl;

		i++;
	}

	for (int j = 0; j<10; j++) SDL_WaitThread(tAtende[j], NULL);  //so encerra gerador1 apos todos atendimentos encerrarem

	cout << "saindo do gerador 1..." << endl;
	return 0;
}

int gerador2(void *data){

	char *nome = (char *)data;
	unsigned long t = SDL_GetTicks();
	int i;

	SDL_mutexP(mu);
	for (i = 0; i<10; i++) sharedBuffer[i] = 2;
	SDL_mutexV(mu);

	for (int i = 0; i < 3; i++){
	    cout << "gerador2 comecando..." << endl;
		//while (SDL_GetTicks() < (t + 10000)) {} 
		SDL_Delay(10000);	//espera 10 segundos
	}
    cout << "gerador2 terminou." << endl;
	return 0;
}



int _tmain(int argc, _TCHAR* argv[])
{
	SDL_Thread *t1, *t2;

	//SDL_Init(SDL_INIT_EVERYTHING);

	mu = SDL_CreateMutex(); 

	semAtende = SDL_CreateSemaphore(3);

	char *nomes[2] = { "uma", "dois" };

	clockInicio = SDL_GetTicks();

	t1 = SDL_CreateThread(gerador1, NULL, nomes[0]); //NULL ou "gerador1"
	t2 = SDL_CreateThread(gerador2, NULL, nomes[1]);

	SDL_WaitThread(t1, NULL);
	SDL_WaitThread(t2, NULL);

	SDL_DestroyMutex(mu);

	cout << "Fim simulacao com duracao de " << (SDL_GetTicks() - clockInicio) / 1000 << " segundos..." << endl;

	system("pause");
	return 0;
}

