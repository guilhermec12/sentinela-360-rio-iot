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

Os seis gráficos incorporados ao painel foram ajustados para 30 resultados, títulos e eixos claros, cores distintas e escalas adequadas; a alteração persistiu após recarregar o canal. A janela de opções do painel não oferece o campo “Update Interval” e usa seu padrão. Os atalhos individuais abaixo especificam atualização visual de 60 s e 30 resultados.

- [Distância A (cm)](https://thingspeak.mathworks.com/channels/3574113/charts/1?bgcolor=%23ffffff&color=%230070c0&dynamic=true&results=30&type=line&update=60&title=Dist%C3%A2ncia%20A&xaxis=Tempo&yaxis=Dist%C3%A2ncia%20%28cm%29&yaxismin=0&yaxismax=400)
- [Distância B (cm)](https://thingspeak.mathworks.com/channels/3574113/charts/2?bgcolor=%23ffffff&color=%23e67e22&dynamic=true&results=30&type=line&update=60&title=Dist%C3%A2ncia%20B&xaxis=Tempo&yaxis=Dist%C3%A2ncia%20%28cm%29&yaxismin=0&yaxismax=400)
- [Evento de contramão (0/1)](https://thingspeak.mathworks.com/channels/3574113/charts/3?bgcolor=%23ffffff&color=%23d62728&dynamic=true&results=30&type=line&update=60&title=Contram%C3%A3o&xaxis=Tempo&yaxis=Evento%20%280%2F1%29&yaxismin=0&yaxismax=1)
- [Evento de bloqueio (0/1)](https://thingspeak.mathworks.com/channels/3574113/charts/4?bgcolor=%23ffffff&color=%239467bd&dynamic=true&results=30&type=line&update=60&title=Bloqueio&xaxis=Tempo&yaxis=Evento%20%280%2F1%29&yaxismin=0&yaxismax=1)
- [Total de contramão](https://thingspeak.mathworks.com/channels/3574113/charts/5?bgcolor=%23ffffff&color=%232ca02c&dynamic=true&results=30&type=line&update=60&title=Total%20de%20contram%C3%A3o&xaxis=Tempo&yaxis=Ocorr%C3%AAncias)
- [Total de bloqueios](https://thingspeak.mathworks.com/channels/3574113/charts/6?bgcolor=%23ffffff&color=%23ff7f0e&dynamic=true&results=30&type=line&update=60&title=Total%20de%20bloqueios&xaxis=Tempo&yaxis=Ocorr%C3%AAncias)

## Componentes e pinagem

ESP32 DevKit V1; dois HC-SR04; LEDs verde e vermelho com resistores de 220 Ω. Sensor A: TRIG/ECHO GPIO 18/19; sensor B: GPIO 25/26; LEDs: GPIO 21/22. O canal ThingSpeak 3574113 está público para avaliação. A chave de escrita não está no repositório GitHub, mas está visível no código do Wokwi compartilhado. A cópia não listada do Wokwi requer um plano pago; a chave exposta deve ser revogada e substituída em uma configuração privada antes da entrega.

## Verificação e limitações

Em 12/11/2026, o Wokwi iniciou, conectou ao Wi-Fi e publicou dados aceitos no ThingSpeak. O repouso A=153 cm/B=257 cm coincidiu com os campos 1/2 da entrada 65. Com ambos os sensores a 30 cm por mais de cinco segundos, o alerta de bloqueio foi acionado e a entrada 67 registrou os campos como 30, 30, 0, 1, 0, 1. Na sequência inversa B → A, o alerta de contramão foi acionado; a entrada 69 registrou 152, 253, 1, 1, 1, 2. Em um teste posterior, uma tentativa de A → B não foi válida: os sensores permaneceram ocupados por mais de cinco segundos, gerando o bloqueio na entrada 81 (30, 30, 0, 1, 1, 3). Depois de afastar os objetos, o estado de bloqueio voltou a 0; o sentido A → B ainda precisa de um teste controlado. As entradas 84–86 depois confirmaram estados ativos em 0/0 e totais 1/3, com sensores em cerca de 152 cm. A compilação automatizada do sketch local passou no GitHub Actions.

O painel agora mantém os seis gráficos com 30 resultados, nomes, cores e escalas legíveis. O intervalo de atualização do painel continua no padrão porque não aparece na janela de opções; os atalhos individuais usam 60 s. Ainda faltam testar A → B sem alerta, anexar capturas reais, confirmar os nomes oficiais da equipe, registrar uma observação territorial própria e substituir a chave exposta do Wokwi por uma configuração privada.

Sensores e tráfego são simulados: o sistema não identifica veículos nem comprova infrações.


**Checagem final (12/11/2026):** o canal ainda mostrava a entrada 88, de 05:52:52 UTC. Uma nova tentativa no Wokwi falhou ao conectar ao gateway IoT (`wss://netwi.wokwi.com/`) e não gerou novo dado após mais de 60 s. Assim, as publicações anteriores estão comprovadas, mas a atualização em tempo real não foi confirmada nesta última checagem. A captura dos gráficos comprova suas configurações, não o envio atual.
