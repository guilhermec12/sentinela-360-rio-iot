# Relatório técnico — Sentinela 360 Rio

**Atividade:** CitizenTech IoT: Monitoramento Inteligente com ESP32 e ThingSpeak  
**Disciplina:** Edge Computing & Computer Systems — FIAP Global Solution 2026.2  
**Equipe:** Guilherme de Paula Correia e João Vitor Barbosa Silva

## Links

- [Projeto no Wokwi](https://wokwi.com/projects/480355518486978561)
- [Canal público ThingSpeak](https://thingspeak.mathworks.com/channels/3574113)
- [Repositório desta entrega](https://github.com/guilhermec12/sentinela-360-rio-iot)

## Problema e beneficiários

O protótipo demonstra dois pontos de uma travessia e sinaliza padrões simulados de ocupação prolongada e de circulação em sentido inverso ao esperado. O público considerado são pedestres, ciclistas e usuários do transporte público. O tema relaciona-se aos ODS 11 e 3.

## Objetivo e arquitetura

Demonstrar uma cadeia IoT didática: dois sensores ultrassônicos HC-SR04 medem distâncias; o ESP32 processa as leituras localmente, controla LEDs e transmite snapshots via Wi-Fi ao ThingSpeak. O sentido esperado é A → B. Uma sequência B → A gera alerta simulado de contramão. A ocupação simultânea por mais de cinco segundos gera alerta simulado de bloqueio.

As leituras válidas vão de 2 a 400 cm. Um ponto ocupa a 40 cm ou menos e libera acima de 50 cm. A sequência entre sensores precisa ocorrer em até 2,5 s; 400 ms com ambos livres rearma a detecção. A telemetria é publicada a cada 60 segundos após a conexão e a sincronização do horário.

## Componentes e conexões

| Componente | Conexão |
|---|---|
| ESP32 DevKit V1 | Controlador central |
| HC-SR04 A | TRIG GPIO 18, ECHO GPIO 19 |
| HC-SR04 B | TRIG GPIO 25, ECHO GPIO 26 |
| LED verde | GPIO 21, resistor de 220 Ω |
| LED vermelho | GPIO 22, resistor de 220 Ω |

O circuito e firmware sanitizado estão em wokwi/diagram.json e wokwi/sketch.ino. A chave de escrita não foi incluída no repositório.

## Dados no ThingSpeak

| Campo | Conteúdo |
|---|---|
| 1 e 2 | Distâncias dos sensores A e B, em cm |
| 3 | Evento/alerta simulado de contramão, 0/1 |
| 4 | Evento/alerta simulado de bloqueio, 0/1 |
| 5 e 6 | Contadores cumulativos de contramão e bloqueio |

## Validação de integração — 12/11/2026

A simulação conectou ao Wi-Fi e os envios foram aceitos pelo ThingSpeak. Com os dois sensores ajustados a 20 cm por mais de cinco segundos, o Monitor Serial confirmou A=20 cm/B=20 cm e o alerta de bloqueio. As entradas 93 e 94 registraram os campos 1–6 como **20, 20, 0, 1, 0, 1**. Isso confirma a transmissão das distâncias baixas e do estado de bloqueio.

Após restaurar os sensores para o repouso nominal de 150 cm, a entrada 95 registrou **152, 152, 0, 0, 0, 1**. O estado do alerta foi limpo e o contador de bloqueio permaneceu em 1. Os registros JSON e a captura do painel estão em evidencias/.

## Limitações

Todo o tráfego e todas as leituras são simulados. Dois sensores ultrassônicos não identificam veículos ou pessoas nem comprovam infrações. O protótipo é acadêmico, não é um sistema certificado para controlar tráfego real e exige avaliação humana. Os contadores ficam em memória e zeram quando o ESP32 reinicia.
