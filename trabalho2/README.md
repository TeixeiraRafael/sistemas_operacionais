### Individual ou em duplas

Ao permitir que processos/threads colaborem através de memória compartilhada, surgem problemas de concorrência que devem ser tratados pelo programador. Estes problemas são chamados de condições de disputa. Entre as alternativas disponíveis estão semáforos e mutexes.

O objetivo desta tarefa é a paralelização de tarefas de um processo através do uso de threads e o uso de semáforos e mutexes tanto para exclusão mútua como para sincronização.

### Tarefa: 
Você foi contratado pelo C3 (Clube do Capitalismo Compulsivo) para desenvolver um sistema de gerenciamento de um banco. Sua principal tarefa é desenvolver um sistema que evite que múltiplas operações sejam realizadas em uma mesma conta bancária de forma simultânea. Assuma que, para cada conta corrente, você possui tanto o seu identificador como o saldo disponível. 

Crie diversas threads para simular sequências de operações em paralelo e, aleatoriamente, defina qual conta receberá a operação, o tipo de operação (crédito ou débito), e o valor da operação. Realize simulações com diferentes números de threads. Após, assuma que existe uma nova operação que realiza a consulta do saldo. A principal diferença para esta operação é que múltiplas threads podem consultar o saldo de uma conta simultaneamente, desde que nenhuma outra thread esteja realizando uma operação de crédito ou débito. Operações de débito e crédito continuam precisando de acesso exclusivo aos registros da conta para executarem adequadamente. 

O que entregar? Códigos do exercício. O códigos deve ser nomeado seguindo o padrão NUM_MATRICULA1_NUMMATRICULA2.formato (e.g., 39133_39199.py).

Critérios de avaliação: o código atende a especificação? os resultados produzidos estão corretos? o código está documentado e de fácil entendimento?