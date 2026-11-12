# Relatório técnico — CitizenTech IoT

**Projeto:** Sentinela 360 Rio  
**Atividade:** CitizenTech IoT: Monitoramento Inteligente com ESP32 e ThingSpeak  
**Disciplina:** Edge Computing & Computer Systems — FIAP Global Solution 2026.2  
**Equipe informada:** Guilherme Correia e João Vitor Barros; confirmar nomes completos oficiais.

## Problema e beneficiários

O protótipo demonstra a leitura de dois pontos de uma travessia e sinaliza padrões simulados de ocupação prolongada e circulação em sequência inversa ao sentido esperado. O público considerado são pedestres, ciclistas e usuários do transporte público. A equipe ainda deve registrar o bairro/cruzamento observado e uma nota ou foto própria; endereço e ocorrência real não foram inventados.

## Objetivo e arquitetura

Demonstrar uma cadeia IoT didática com dois HC-SR04, processamento local no ESP32, LEDs e monitor serial para indicar estados, Wi-Fi para enviar dados ao ThingSpeak e gráficos para consultar o histórico. O sentido esperado é A → B. A sequência B → A gera candidato simulado a contramão. A ocupação simultânea por mais de cinco segundos gera candidato a bloqueio. Esses sinais exigem avaliação humana e não comprovam infração.

## Componentes e conexões

| Componente | Conexão no ESP32 |
|---|---|
| HC-SR04 A TRIG/ECHO | GPIO 18/19 |
| HC-SR04 B TRIG/ECHO | GPIO 25/26 |
| LED verde/vermelho | GPIO 21/22, resistores de 220 Ω |
| VCC/GND dos sensores | VIN/GND |

Em montagem física, adapte o ECHO de 5 V ao limite de 3,3 V do ESP32. O diagrama está em wokwi/diagram.json; o firmware está em wokwi/sketch.ino.

## Processamento e telemetria

Leituras válidas: 2–400 cm. Cada ponto ocupa a 40 cm ou menos e libera acima de 50 cm (histerese). A ordem de passagem é avaliada em 2,5 s; 400 ms com os dois pontos livres rearma a detecção. O bloqueio é contado após cinco segundos com ambos ocupados.

O ESP32 publica snapshots a cada 60 segundos, com a primeira publicação após Wi-Fi e sincronização do horário. Os campos 3/4 sinalizam evento ocorrido desde o último envio aceito ou alerta ainda ativo; os campos 5/6 guardam os totais cumulativos até reiniciar o ESP32.

| Campo | Conteúdo |
|---|---|
| 1 e 2 | Distâncias A/B em centímetros |
| 3 | Evento de contramão, 0/1 |
| 4 | Evento de bloqueio, 0/1 |
| 5 e 6 | Contadores cumulativos de contramão e bloqueio |

O README contém seis atalhos individuais com janela de 30 resultados, atualização visual de 60 s, unidades, cores e escalas. Esses atalhos abrem visualizações personalizadas; não alteram as configurações padrão dos gráficos incorporados ao painel do canal. O canal 3574113 está público para avaliação. Não inclua chaves de API em relatórios, capturas ou no repositório.

## Testes de integração observados em 12/11/2026

O Wokwi iniciou, conectou ao Wi-Fi e confirmou gravações no ThingSpeak. No repouso, as leituras A=153 cm e B=257 cm coincidiram com os campos 1/2 da entrada 65. Com os dois sensores a 30 cm por mais de cinco segundos, o serial indicou bloqueio; a entrada 67 registrou 30, 30, 0, 1, 0, 1. Na sequência inversa B → A, o serial indicou contramão; a entrada 69 registrou 152, 253, 1, 1, 1, 2. O bloqueio também foi contado nessa última entrada porque ambos ficaram ocupados tempo suficiente. Ao afastar os objetos, os alertas voltaram a 0 e os totais cumulativos foram preservados. A compilação automatizada do sketch local passou no GitHub Actions.

Os atalhos individuais do README usam 30 resultados e atualização visual de 60 s. Os gráficos incorporados ao painel ainda exibem 60 resultados; os campos 5/6 atualizam visualmente em 15 s. Falta salvar os parâmetros desejados nos seis gráficos do painel.

## Pendências da equipe

- Testar e registrar a sequência esperada A → B sem acionar contramão.
- Salvar capturas reais do Wokwi e ThingSpeak em evidencias/.
- Ajustar os seis gráficos incorporados ao painel para 30 resultados e 60 s.
- Confirmar nomes completos oficiais e registrar uma observação territorial própria.

## Limitações

Sensores e tráfego são simulados. Dois pontos ultrassônicos não identificam pessoas ou veículos nem comprovam infrações. Os contadores ficam em memória e zeram quando o ESP32 reinicia. Uma instalação real exigiria validação em campo, adequação elétrica e avaliação humana.
