
#include "stdafx.h"

#include <thread>
#include <iostream>
#include "Fila.h"
#include <vector>
#include <chrono>
#include <mutex>

mutex mu;

std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration> tempoInicial;
int cntr;

long getClock(){
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - tempoInicial).count();
}

void atende(int i, Fila *f, Fila *fo){
	Carro* c = NULL;
	std::cout << "inicializando bomba de combustivel " << i << "." << std::endl;

	while (getClock() < 15){   //atende enquanto Clock < 15 segundos
       
		if (f->isEmpty() == false){		//se fila nao vazia atende...			
			mu.lock();
			  c= f->getFirst();			//pega primeiro da fila
			mu.unlock();
			if (c != NULL){				//se conseguiu pegar alguem da fila
				std::cout << " bomba " << i << " atendendo " << c->getPlaca() << " em " << getClock() << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));  //aqui, por exemplo, o valor 2 poderia ser substituido por normal(5,2) =>EXEMPLO!
				std::cout << " bomba " << i << " liberando " << c->getPlaca() << " em " << getClock() << std::endl;

				//sorteia se carro vai para troca de oleo ou nao
				//chance de ir para troca de oleo é de 30% neste exemplo...
				//se nao for para troca de oleo carro é destruido...
				//Obs.: substituir uso do rand() pelo random LCG thread safe 
				if ((rand()%100) < 30) fo->insert(c);
				else delete c;
				c = NULL;
			}
		}         
		
	}
	std::cout << "encerrando processo bomba... " << i << std::endl;
}
void trocaOleo(Fila *fo){
	Carro* c = NULL;
	std::cout << "inicializando troca de oleo." << std::endl;

	while (getClock() < 25){   //atende enquanto Clock < 25 segundos

		if (fo->isEmpty() == false){		//se fila da troca de oleo nao vazia atende...			
			mu.lock();
			c = fo->getFirst();				//pega primeiro da fila
			mu.unlock();
			if (c != NULL){					//se conseguiu pegar alguem da fila
				std::cout << " trocando oleo de " << c->getPlaca() << " em " << getClock() << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(5));  //aqui, por exemplo, o valor 5 poderia ser substituido por normal(7,1) =>EXEMPLO!
				std::cout << " terminou troca de " << c->getPlaca() << " em " << getClock() << std::endl;
				delete c;
				c = NULL;
			}
		}

	}
	std::cout << "encerrando processo troca de oleo... " << std::endl;
}
void gerador(int i, int tempo,  Fila *f){

	int placa;

	std::cout << "disparando gerador " << i << std::endl;
	std::cout << "thread id:" << std::this_thread::get_id() << std::endl;

	for (int x = 0; x < 6; x++){     //neste exemplo os geradores criam so 6 carros cada (fixo); alterar isto no modelo do prototipo...
		std::this_thread::sleep_for(std::chrono::seconds(tempo));  //aqui o tempo pode ser substituido por exponencial(tempo)

	    mu.lock();
	     cntr++;
		 placa = cntr;  // o valor da placa é obtido a partir da variavel global cntr; como cntr esta sendo compartilhada entre as threads
	    mu.unlock();	// o acesso a ela deve ser protegido.

		std::cout << "gerador " << i << " criou carro " << placa << " em " << getClock() << std::endl;
		f->insert(new Carro(placa));
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//captura o tempo inicial da simulação
	tempoInicial = std::chrono::system_clock::now();

	//cria e inicializa contador que sera usado para identificar as placas dos carros
	cntr = 0;

	//cria filas de carros
	Fila f;			//fila de carros a espera de atendimento nas bombas
	Fila fOleo;		//fila de carros na troca de oleo
	
	//cria 3 geradores (de carros)
	std::thread t1(gerador, 1, 2, &f);  //gerador 1, cria carros de 2 em 2 segundos
	std::thread t2(gerador, 2, 5, &f);	//gerador 2, cria carros de 5 em 5 segundos
	std::thread t3(gerador, 3, 7, &f);	//gerador 3, cria carros de 7 em 7 segundos

	//cria 2 bombas para atendimento
	//neste exemplo, as duas bombas "consomem" carros a partir da mesma fila
	//elas tem todas o mesmo tempo de atendimento; isto pode ser alterado no prototipo...
	//as bombas recebem referencias para as duas filas (a de atendimento e a fila oleo)
	//porque elas removem da fila de atendimento e inserem (possivelmente) na fila oleo...
	std::thread t4(atende, 1, &f, &fOleo);	//bomba 1
	std::thread t5(atende, 2, &f, &fOleo);  //bomba 2

	//cria estação de troca de oleo
	//30% dos carros que saem do atendimento vao para troca de oleo
	//os demais sao destruidos logo apos o atendimento
	std::thread t6(trocaOleo, &fOleo);  //troca de oleo

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	std::cout << "encerrando... " << getClock() << std::endl;

	cin.get();

	return 0;
}



