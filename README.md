# CitizenTech IoT: Sentinela 360 Rio

**Disciplina:** Edge Computing & Computer Systems · FIAP Global Solution 2026.2 · Engenharia de Software, 1º ano, RJ

> Protótipo de IoT com ESP32 no Wokwi, processamento local e telemetria no ThingSpeak.

## Acesso e arquivos

- Wokwi: https://wokwi.com/projects/480355518486978561
- ThingSpeak público: https://thingspeak.mathworks.com/channels/3574113
- Firmware: wokwi/sketch.ino
- Diagrama: wokwi/diagram.json
- Relatório: TRABALHO.md
- Guia ThingSpeak: thingspeak/CONFIGURACAO.md
- Roteiro: wokwi/ROTEIRO-DEMO-BASE.md
- Checklist: CHECKLIST-ENTREGA.md

## Problema e funcionamento

O protótipo representa dois pontos de uma travessia e sinaliza padrões simulados de circulação em sentido inesperado ou ocupação simultânea prolongada. Usa dois sensores HC-SR04, processamento local no ESP32, LEDs e telemetria ThingSpeak. O público considerado são pedestres, ciclistas e usuários do transporte público; o tema se relaciona aos ODS 11 e 3.

O sentido esperado padrão é A → B. Uma sequência B → A gera candidato simulado a contramão; os dois pontos ocupados por mais de cinco segundos geram candidato a bloqueio. O firmware lê sensores continuamente e publica snapshots a cada 60 segundos, começando assim que Wi-Fi e horário estão prontos.

Os campos 3 e 4 sinalizam evento ocorrido desde o último envio aceito ou alerta ainda ativo. Assim, um evento breve continua visível no próximo envio. Os campos 5 e 6 mantêm contadores cumulativos até reiniciar o ESP32.

| Campo | Conteúdo | Visualização |
|---|---|---|
| 1 | Distância A, cm | Linha |
| 2 | Distância B, cm | Linha |
| 3 | Evento de contramão, 0/1 | Degrau binário |
| 4 | Evento de bloqueio, 0/1 | Degrau binário |
| 5 | Total de eventos de contramão | Contagem cumulativa |
| 6 | Total de eventos de bloqueio | Contagem cumulativa |

## Gráficos legíveis

Os atalhos individuais abaixo usam janela de 30 resultados, atualização visual de 60 s, nomes, unidades e escalas adequadas. Eles abrem visualizações personalizadas e **não alteram** as configurações dos gráficos incorporados ao painel do canal.

- [Distância A (cm)](https://thingspeak.mathworks.com/channels/3574113/charts/1?bgcolor=%23ffffff&color=%230070c0&dynamic=true&results=30&type=line&update=60&title=Dist%C3%A2ncia%20A&xaxis=Tempo&yaxis=Dist%C3%A2ncia%20%28cm%29&yaxismin=0&yaxismax=400)
- [Distância B (cm)](https://thingspeak.mathworks.com/channels/3574113/charts/2?bgcolor=%23ffffff&color=%23e67e22&dynamic=true&results=30&type=line&update=60&title=Dist%C3%A2ncia%20B&xaxis=Tempo&yaxis=Dist%C3%A2ncia%20%28cm%29&yaxismin=0&yaxismax=400)
- [Evento de contramão (0/1)](https://thingspeak.mathworks.com/channels/3574113/charts/3?bgcolor=%23ffffff&color=%23d62728&dynamic=true&results=30&type=line&update=60&title=Contram%C3%A3o&xaxis=Tempo&yaxis=Evento%20%280%2F1%29&yaxismin=0&yaxismax=1)
- [Evento de bloqueio (0/1)](https://thingspeak.mathworks.com/channels/3574113/charts/4?bgcolor=%23ffffff&color=%239467bd&dynamic=true&results=30&type=line&update=60&title=Bloqueio&xaxis=Tempo&yaxis=Evento%20%280%2F1%29&yaxismin=0&yaxismax=1)
- [Total de contramão](https://thingspeak.mathworks.com/channels/3574113/charts/5?bgcolor=%23ffffff&color=%232ca02c&dynamic=true&results=30&type=line&update=60&title=Total%20de%20contram%C3%A3o&xaxis=Tempo&yaxis=Ocorr%C3%AAncias)
- [Total de bloqueios](https://thingspeak.mathworks.com/channels/3574113/charts/6?bgcolor=%23ffffff&color=%23555555&dynamic=true&results=30&type=line&update=60&title=Total%20de%20bloqueios&xaxis=Tempo&yaxis=Ocorr%C3%AAncias)

## Componentes e pinagem

ESP32 DevKit V1; dois HC-SR04; LEDs verde e vermelho com resistores de 220 Ω. Sensor A: TRIG/ECHO GPIO 18/19; sensor B: GPIO 25/26; LEDs: GPIO 21/22. O canal ThingSpeak 3574113 está público para avaliação. A chave de escrita foi omitida do firmware do GitHub e deve permanecer apenas na cópia privada do Wokwi.

## Verificação e limitações

Em um teste anterior, ambos os sensores em 20 cm geraram candidato a bloqueio após cinco segundos; o campo 6 chegou a 1. Ao voltar a 150 cm, o alerta apagou e o contador permaneceu. Esse ensaio usava o intervalo anterior de 20 s. O firmware foi atualizado para 60 s e para reter eventos até um envio aceito; a versão atualizada ainda precisa de execução acompanhada para confirmar telemetria de ponta a ponta. Os sensores e o tráfego são simulados: o sistema não identifica veículos nem comprova infrações.

A equipe precisa confirmar nomes completos oficiais e registrar o cruzamento/bairro e uma observação local própria. Não se inventou local ou ocorrência real.
