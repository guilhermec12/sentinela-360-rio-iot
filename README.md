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

## Problema, objetivo e público

O protótipo representa dois pontos de uma travessia e sinaliza padrões simulados de circulação em sentido inesperado ou ocupação simultânea prolongada. A solução didática usa dois sensores HC-SR04, processa as distâncias localmente no ESP32, aciona LEDs e envia os dados ao ThingSpeak. O público considerado são pedestres, ciclistas e usuários do transporte público. O tema se relaciona aos ODS 11 e 3.

A equipe ainda precisa registrar o bairro/cruzamento e uma observação local própria; não inventamos endereço ou ocorrência real. Integrantes informados: Guilherme Correia e João Vitor Barros; confirmar os nomes completos oficiais para a entrega.

## Como funciona

O sentido padrão esperado é A → B. Uma sequência B → A gera um candidato simulado a contramão. A ocupação simultânea dos dois pontos por mais de cinco segundos gera um candidato a bloqueio. O firmware lê os sensores continuamente e publica snapshots a cada 60 segundos; a primeira publicação ocorre assim que o Wi-Fi e o horário estiverem prontos.

Os campos 3 e 4 sinalizam evento ocorrido desde o último envio aceito ou alerta ainda ativo. Assim, um evento curto continua visível no próximo ponto do gráfico. Os campos 5 e 6 mantêm os contadores cumulativos até reiniciar o ESP32.

| Campo | Conteúdo | Visualização |
|---|---|---|
| 1 | Distância A, cm | Linha, centímetros |
| 2 | Distância B, cm | Linha, centímetros |
| 3 | Evento de contramão, 0/1 | Degrau binário |
| 4 | Evento de bloqueio, 0/1 | Degrau binário |
| 5 | Total de eventos de contramão | Contagem cumulativa |
| 6 | Total de eventos de bloqueio | Contagem cumulativa |

Para facilitar a leitura, os seis gráficos devem atualizar a cada 60 s e mostrar os últimos 30 resultados. Mantenha um gráfico por campo para não misturar distâncias em cm com estados binários e contadores.

## Componentes e pinagem

ESP32 DevKit V1, dois sensores ultrassônicos HC-SR04, LEDs verde e vermelho com resistores de 220 Ω. Sensor A: TRIG/ECHO GPIO 18/19; sensor B: GPIO 25/26; LEDs: GPIO 21/22. O canal ThingSpeak 3574113 está público para avaliação. A chave de escrita não está no firmware do GitHub e deve permanecer apenas na cópia privada do Wokwi.

## Verificação e limitações

O cenário de bloqueio foi observado anteriormente: ambos os sensores em 20 cm geraram alerta no serial e total 1 no campo 6; ao retornar a 150 cm, o alerta apagou e o total permaneceu. Essa verificação usava o intervalo anterior de 20 s. O novo intervalo de 60 s e a retenção de eventos nos campos 3/4 precisam ser confirmados em execução após a atualização do projeto Wokwi.

Sensores, distâncias e passagens são simulados. Dois pontos ultrassônicos não identificam pessoas ou veículos, nem comprovam infrações. Os alertas exigem avaliação humana. Os contadores ficam em memória e zeram no reinício. Ainda faltam testar contramão, registrar o território observado e salvar capturas reais para a entrega.

## Referência

FIAP Global Solution 2026.2, Desafio FIAP: CitizenTech, Edge Computing & Computer Systems, páginas 36–39.
