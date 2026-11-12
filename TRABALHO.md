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

O ESP32 publica snapshots a cada 60 segundos, com a primeira publicação após Wi-Fi e sincronização do horário. Os seis gráficos devem atualizar a cada 60 s e mostrar os últimos 30 resultados, mantendo um gráfico por campo.

| Campo | Conteúdo |
|---|---|
| 1 e 2 | Distâncias A/B em centímetros |
| 3 | Evento de contramão desde o último envio aceito ou alerta ainda ativo, 0/1 |
| 4 | Evento de bloqueio desde o último envio aceito ou alerta ainda ativo, 0/1 |
| 5 e 6 | Contadores cumulativos de contramão e bloqueio |

O firmware usa HTTPS com validação TLS. A chave de escrita foi omitida do código público e deve ficar somente na cópia privada do Wokwi. O canal 3574113 está público para avaliação.

## Verificação observada e estado da atualização

No teste anterior, ambos os sensores em 20 cm geraram candidato a bloqueio após cinco segundos; uma escrita foi aceita e o campo 6 mostrou total 1. Ao voltar a 150 cm, o alerta apagou e o total permaneceu. Esse teste usava intervalo de 20 s. O firmware agora foi ajustado para 60 s e para manter eventos curtos até o próximo envio aceito; essa revisão ainda precisa ser verificada ao vivo no Wokwi.

## Beneficiários, ODS e limitações

O tema se relaciona ao ODS 11 (Cidades e Comunidades Sustentáveis) e ao ODS 3 (Saúde e Bem-Estar). Sensores, distâncias e passagens são simulados. Dois pontos ultrassônicos não identificam pessoas ou veículos nem provam direção real. Os contadores ficam em memória e zeram ao reiniciar o ESP32; o protótipo não substitui engenharia de tráfego nem fiscalização.

## Pendências da equipe

- Confirmar os nomes completos oficiais.
- Registrar o bairro/cruzamento e uma observação local própria.
- Demonstrar a sequência inversa para contramão após sincronizar o novo firmware.
- Salvar capturas reais do Wokwi e dos gráficos na pasta de evidências.
- Conferir os links sem sessão autenticada.

**Referência:** FIAP, Desafio FIAP: CitizenTech, Global Solution 2026.2, Edge Computing & Computer Systems, pp. 36–39.
