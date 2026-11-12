# Evidências da entrega

## Verificação mais recente — 12/11/2026

O projeto Wokwi foi iniciado, conectou-se ao Wi-Fi `Wokwi-GUEST` e publicou no ThingSpeak. O Monitor Serial confirmou os envios e o feed público confirmou as entradas 99, 100 e 101: campos 1–6 = `152, 152, 0, 0, 0, 0`. Os dois sensores estavam em repouso e sem alertas ativos.

O teste de distância curta permanece registrado nas entradas 93 e 94: ambos os sensores a 20 cm, com bloqueio simulado ativo (campos 1–6 = `20, 20, 0, 1, 0, 1`). A entrada 95 registra o retorno ao repouso. Confira os registros no [arquivo JSON de validação](validacao-thingspeak-12-11-2026.json) e no [feed público ao vivo](https://api.thingspeak.com/channels/3574113/feeds.json?results=9).

## Projeto e gráficos ao vivo

- [Abrir a simulação no Wokwi](https://wokwi.com/projects/480355518486978561)
- [Abrir o canal público ThingSpeak](https://thingspeak.mathworks.com/channels/3574113)

As imagens consultam os últimos 30 resultados do canal público:

![Distância A (cm)](https://api.thingspeak.com/channels/3574113/charts/1?results=30&dynamic=true&height=240&width=600)

![Distância B (cm)](https://api.thingspeak.com/channels/3574113/charts/2?results=30&dynamic=true&height=240&width=600)

![Contramão ativa](https://api.thingspeak.com/channels/3574113/charts/3?results=30&dynamic=true&height=240&width=600)

![Bloqueio ativo](https://api.thingspeak.com/channels/3574113/charts/4?results=30&dynamic=true&height=240&width=600)

![Total de contramãos](https://api.thingspeak.com/channels/3574113/charts/5?results=30&dynamic=true&height=240&width=600)

![Total de bloqueios](https://api.thingspeak.com/channels/3574113/charts/6?results=30&dynamic=true&height=240&width=600)

A captura local `thingspeak-painel.png` é histórica e mostra até a entrada 88; os gráficos acima consultam os dados atuais. As medições e alertas são simulados e não comprovam infrações.
