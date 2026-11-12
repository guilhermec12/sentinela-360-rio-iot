# Sentinela 360 Rio — CitizenTech IoT

Protótipo acadêmico da FIAP Global Solution 2026.2 para **Edge Computing & Computer Systems**. O circuito simula dois pontos de uma travessia: o ESP32 lê as distâncias, sinaliza condições localmente e publica telemetria no ThingSpeak.

## Equipe

- Guilherme de Paula Correia
- João Vitor Barbosa Silva

## Links da entrega

- [Projeto executável no Wokwi](https://wokwi.com/projects/480355518486978561)
- [Canal público ThingSpeak](https://thingspeak.mathworks.com/channels/3574113)
- [Relatório técnico](TRABALHO.md)
- [Evidências e registros de validação](evidencias/README.md)

## Problema, objetivo e beneficiários

A proposta demonstra como sensores conectados podem ajudar a observar padrões de circulação em travessias. Considera pedestres, ciclistas e usuários do transporte público. Relaciona-se aos ODS 11 (Cidades e Comunidades Sustentáveis) e 3 (Saúde e Bem-Estar).

É uma demonstração didática com sensores simulados: não identifica veículos ou pessoas, não detecta infrações reais e não substitui avaliação humana.

## Como funciona

Dois sensores ultrassônicos HC-SR04 representam os pontos A e B. O ESP32 processa as leituras e controla os LEDs verde e vermelho. A sequência esperada é A → B; a sequência B → A gera um alerta simulado de contramão. A ocupação simultânea dos dois pontos por mais de cinco segundos gera um alerta simulado de bloqueio.

Cada ponto considera ocupado a 40 cm ou menos e livre acima de 50 cm (histerese). A ordem de passagem é avaliada em até 2,5 s. Após 400 ms com os pontos livres, a detecção é rearmada. Leituras fora de 2–400 cm são inválidas.

O firmware publica snapshots no ThingSpeak a cada 60 segundos, após conexão Wi-Fi e sincronização do horário. A simulação precisa estar rodando no Wokwi para produzir novos dados.

## Componentes e conexões

| Componente | Pinos |
|---|---|
| ESP32 DevKit V1 | Microcontrolador |
| HC-SR04 A | TRIG 18, ECHO 19 |
| HC-SR04 B | TRIG 25, ECHO 26 |
| LED verde | GPIO 21, resistor de 220 Ω |
| LED vermelho | GPIO 22, resistor de 220 Ω |

O diagrama está em wokwi/diagram.json e o sketch sanitizado em wokwi/sketch.ino. A chave de escrita não está no repositório.

## Campos do ThingSpeak

| Campo | Conteúdo |
|---|---|
| 1 | Distância A, em cm |
| 2 | Distância B, em cm |
| 3 | Evento/alerta de contramão, 0 ou 1 |
| 4 | Evento/alerta de bloqueio, 0 ou 1 |
| 5 | Total acumulado de eventos de contramão |
| 6 | Total acumulado de eventos de bloqueio |

Os campos de evento ficam ativos enquanto o alerta estiver presente ou até o evento ser confirmado em um envio. Os totais são cumulativos durante a execução e reiniciam quando o ESP32 reinicia.

## Teste de integração

Em 12/11/2026, ajustei os dois sensores para 20 cm no Wokwi. O serial confirmou A=20 cm e B=20 cm; após cinco segundos, o ESP32 indicou bloqueio. O ThingSpeak aceitou as entradas 93 e 94 com os campos 1–6: **20, 20, 0, 1, 0, 1**.

Depois de restaurar os sensores ao repouso, a entrada 95 registrou **152, 152, 0, 0, 0, 1**. Os 152 cm são a leitura observada no simulador com o ajuste nominal de 150 cm. Os registros e a captura dos gráficos estão na pasta evidencias/.

## Estrutura

- wokwi/sketch.ino: código do ESP32 sem a chave de escrita.
- wokwi/diagram.json: componentes e conexões.
- TRABALHO.md: descrição técnica.
- evidencias/: captura dos gráficos e registros da validação.

## Execução

Abra o projeto Wokwi, inicie a simulação e altere a distância de cada HC-SR04 pelo controle do componente. Acompanhe leituras e alertas no Monitor Serial e os envios no canal ThingSpeak. O projeto Wokwi compartilhado está configurado para a demonstração.
