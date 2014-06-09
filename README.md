Sim Restaurant
==============

This is a project to simulate a restaurant using threads and random variates.

Professor: Ernesto Lindstaedt  
Deadline: 21/05/2014

### Description

Description of the problem (in portuguese):
 
* A cada exponencial (3) minutos chega um grupo de clientes; este grupo pode ser de 1 a 4 
pessoas (sorteio randomico); 
* O grupo escolhe uma das filas (a menor) e faz o pedido e 
pagamento (isto consome normal (8,2) min).

* São duas caixas, cada uma com uma fila. Depois de pedir e pagar, o grupo:
    * se for de 1 cliente, vai para o Balcão; se não houver banco disponível, aguarda na FilaBalc;
    * se for de 2 a 4 clientes, vai para as mesas; caso não hajam mesas disponíveis, o grupo aguarda em FilaMesas;  
* O tempo de preparo das refeições é de normal (14,5)min. 
* Até 3 refeições podem ser prepadas simultaneamente pela cozinha. Se um pedido chega na cozinha e caso já hajam 3 pedidos sendo atedidos, o novo pedido aguarda na Fila Ped.
* O tempo de refeição é de normal (20,8)min. Após o término da refeição o grupo se retira do 
restaurante liberando então sua mesa ou banco.

Um problema a ser resolvido neste sistema é como tratar o caso da refeição ficar pronta para 
um grupo que ainda aguarda numa Fila (na FilaBalc ou FilaMesas). Alguma solução deve ser 
adotada para tratar esta situação.


### Contributors

- David Basilio
- Joarez Santini