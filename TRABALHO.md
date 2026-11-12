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

O README contém seis atalhos individuais com janela de 30 resultados, atualização visual de 60 s, unidades, cores e escalas. Esses atalhos abrem visualizações personalizadas; não alteram as configurações padrão dos gráficos incorporados ao painel do canal. O firmware usa HTTPS com validação TLS. A chave de escrita foi omitida do código público e deve ficar somente na cópia privada do Wokwi. O canal 3574113 está público para avaliação.

## Verificação observada e estado da atualização

No teste anterior, ambos os sensores em 20 cm geraram candidato a bloqueio após cinco segundos; uma escrita foi aceita e o campo 6 mostrou total 1. Ao voltar a 150 cm, o alerta apagou e o total permaneceu. Esse teste usava intervalo de 20 s. O firmware revisado para intervalo de 60 s e retenção de eventos foi salvo no Wokwi e publicado em wokwi/sketch.ino no GitHub. Ainda é necessário executar a versão revisada para confirmar a telemetria de ponta a ponta e demonstrar a sequência inversa de contramão. Capturas atuais do teste também precisam ser registradas.

## Pendências da equipe

- Confirmar nomes completos oficiais.
- Registrar o bairro/cruzamento e observação local própria.
- Executar e registrar os cenários A → B, B → A e bloqueio após atualizar.
- Conferir cada gráfico do canal ThingSpeak em uso.

## Limitações

Sensores e tráfego são simulados. Dois pontos ultrassônicos não identificam pessoas ou veículos nem comprovam infrações. Os contadores ficam em memória e zeram quando o ESP32 reinicia. Uma instalação real exigiria validação em campo, adequação elétrica e avaliação humana.
