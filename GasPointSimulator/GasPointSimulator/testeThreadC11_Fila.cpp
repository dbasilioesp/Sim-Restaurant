#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>

#include "Fila.h"

using namespace std;
using namespace chrono;

int cntr;
mutex mu;

time_point<system_clock, system_clock::duration> tempoInicial;


long getClock(){
	return duration_cast<seconds>(system_clock::now() - tempoInicial).count();
}

void atende(int i, Fila *queueCar, Fila *queueOleo){

	Carro* c = NULL;
	
	cout << "inicializando bomba de combustivel " << i << "." << endl;

	// atende enquanto Clock < 15 segundos
	while (getClock() < 15){   
        
		// se fila nao vazia atende...
		if (queueCar->isEmpty() == false){
			
			mu.lock();
			  c= queueCar->getFirst();
			mu.unlock();

			// se conseguiu pegar alguem da fila
			if (c != NULL){				
				
				cout << " bomba " << i << " atendendo " << c->getPlaca() << " em " << getClock() << endl;
				
				// TODO: substituir por normal(5,2) =>EXEMPLO!
				this_thread::sleep_for(seconds(2));  
				cout << " bomba " << i << " liberando " << c->getPlaca() << " em " << getClock() << endl;

				/*	sorteia se carro vai para troca de oleo ou nao
					chance de ir para troca de oleo é de 30% neste exemplo...
					se nao for para troca de oleo carro é destruido...
					Obs.: substituir uso do rand() pelo random LCG thread safe 
				*/
				if ((rand()%100) < 30) 
					queueOleo->insert(c);
				else 
					delete c;

				c = NULL;
			}
		}         
		
	}

	cout << "encerrando processo bomba... " << i << endl;
}


void trocaOleo(Fila *queueOleo){
	
	Carro* c = NULL;
	
	cout << "inicializando troca de oleo." << endl;

	while (getClock() < 25){

		if (queueOleo->isEmpty() == false){
			
			mu.lock();
				c = queueOleo->getFirst();
			mu.unlock();

			if (c != NULL){
				cout << " trocando oleo de " << c->getPlaca() << " em " << getClock() << endl;
				
				// TODO: substituido por normal(7,1) =>EXEMPLO!
				this_thread::sleep_for(seconds(5));  
				
				cout << " terminou troca de " << c->getPlaca() << " em " << getClock() << endl;
				
				delete c;
				c = NULL;
			}
		}

	}
	
	cout << "encerrando processo troca de oleo... " << endl;
}


void gerador(int i, int tempo,  Fila *queueCar){

	int placa;

	cout << "disparando gerador " << i << endl;
	cout << "thread id:" << this_thread::get_id() << endl;

	// TODO: neste exemplo os geradores criam so 6 carros cada (fixo); alterar isto no modelo do prototipo...
	for (int x = 0; x < 6; x++){

		// TODO: aqui o tempo pode ser substituido por exponencial(tempo)
		this_thread::sleep_for(seconds(tempo));

	    mu.lock();
	     cntr++;
		 // O valor da placa é obtido a partir da variavel global cntr; 
		 // como cntr esta sendo compartilhada entre as threads 
		 placa = cntr;
	    mu.unlock();

		cout << "gerador " << i << " criou carro " << placa << " em " << getClock() << endl;
		queueCar->insert(new Carro(placa));
	}
}

int main(int argc)
{
	cntr = 0;
	tempoInicial = system_clock::now();

	Fila queueCar;
	Fila queueOleo;
	
	// cria 3 geradores (de carros)
	thread t1(gerador, 1, 2, &queueCar);    //gerador 1, cria carros de 2 em 2 segundos
	thread t2(gerador, 2, 5, &queueCar);	//gerador 2, cria carros de 5 em 5 segundos
	thread t3(gerador, 3, 7, &queueCar);	//gerador 3, cria carros de 7 em 7 segundos

	//cria 2 bombas para atendimento
	//neste exemplo, as duas bombas "consomem" carros a partir da mesma fila
	//elas tem todas o mesmo tempo de atendimento; isto pode ser alterado no prototipo...
	//as bombas recebem referencias para as duas filas (a de atendimento e a fila oleo)
	//porque elas removem da fila de atendimento e inserem (possivelmente) na fila oleo...
	thread t4(atende, 1, &queueCar, &queueOleo);	//bomba 1
	thread t5(atende, 2, &queueCar, &queueOleo);    //bomba 2

	//cria estação de troca de oleo
	//30% dos carros que saem do atendimento vao para troca de oleo
	//os demais sao destruidos logo apos o atendimento
	thread t6(trocaOleo, &queueOleo);  //troca de oleo

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	cout << "encerrando... " << getClock() << endl;

	cin.get();

	return 0;
}



