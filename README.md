Simulador de Memória Cache para IOAC
============

OBJETIVO

Simulador de Memória Cache para a disciplina IOAC

COMPILAR

Estando na pasta raiz do projeto, basta executar o comando make e aguardar a compilação do projeto, bem como a criação da documentação pelo Doxygen

CONFIGURAÇÕES

Na pasta "data" deve existir um arquivo de configurações com as opções de configuração da memória conforme descrita no documento disponibilizado pelo professor.
O arquivo deve ser nomeado como "config.dat"

EXECUTAR

Ainda na pasta raiz do projeto, se em ambiente linux, digite "./bin/cache" para executar o programa sem argumentos. Após a leitura do arquivo de configurações, o sistema apresentará um relatório sobre a configuração lida.

OPÇÕES EXTRA

Para executar o programa e carregar um script de comandos (.smc - simulador de memória cache) automaticamente, basta executá-lo passando como primeiro argumento, o caminho/nome do script.
Por exemplo: "./bin/cache ./data/script1.smc"
Durante a  execução, será apresentado uma animação com o carregamento de cada comando de leitura (READ). Ao término, um relatório sobre quantos HITS, MISS e a taxa de percentual de HITS.

MENU PRINCIPAL
Acesse a opção "Ler" para fazer a leitura de uma palavra. Caso ela não esteja na cache, ele retornará a informação de MISS e a linha em que foi alocada a palavra.
A opção "Exibir" listará todos as informações na cache e na memória principal.
"Exibir configurações" emite o mesmo relatório que foi gerado durante o carregamento da aplicação sobre as configurações da memória.
"Exibir histórico" mostrará todas as operações de acesso feitas na memória e a situação em que estava em cada uma delas. Esta opção solicitará quantas dos últimos eventos deseja rever. Digitando "0", o sistema exibirá todas as alterações.
Para executar um script de comandos, acesse a opção "Executar script". O sistema solicitará um caminho/nome do arquivo.
Por fim, a opção "Sair" encerra a aplicação.

ARQUIVO DE SCRIPT (.smc)
O script de simulador de memória cache pode conter três tipos de linhas:
    Iniciadas com "#" - indicam linhas de comentários
    Iniciadas com "READ;" - comando de leitura (deve ser seguido pela palavra desejada. P.E.: READ;15)
    Iniciadas com "SHOW;" - comando de exibição da memória