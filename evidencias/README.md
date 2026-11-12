# Evidências da entrega

## Verificação da integração — 12/11/2026

A simulação Wokwi conectou-se à rede `Wokwi-GUEST`. O Monitor Serial confirmou os envios e o feed público do ThingSpeak confirmou as entradas 99–105. A última entrada verificada foi a 105: campos 1–6 = `152, 152, 0, 0, 0, 0`, com os dois sensores em repouso e sem alerta ativo.

O teste de curta distância permanece nas entradas 93 e 94: ambos os sensores a 20 cm, com bloqueio simulado ativo (campos 1–6 = `20, 20, 0, 1, 0, 1`). A entrada 95 registra o retorno ao repouso. Os resultados estão no [arquivo JSON de validação](validacao-thingspeak-12-11-2026.json) e no [feed público ao vivo](https://api.thingspeak.com/channels/3574113/feeds.json?results=9).

## Projeto e gráficos públicos

- [Simulação Wokwi](https://wokwi.com/projects/480355518486978561)
- [Painel ThingSpeak público](https://thingspeak.mathworks.com/channels/3574113)
- [Campo 1 — Distância A](https://thingspeak.mathworks.com/channels/3574113/charts/1?dynamic=true&results=30)
- [Campo 2 — Distância B](https://thingspeak.mathworks.com/channels/3574113/charts/2?dynamic=true&results=30)
- [Campo 3 — Contramão](https://thingspeak.mathworks.com/channels/3574113/charts/3?dynamic=true&results=30)
- [Campo 4 — Bloqueio](https://thingspeak.mathworks.com/channels/3574113/charts/4?dynamic=true&results=30)
- [Campo 5 — Total de contramãos](https://thingspeak.mathworks.com/channels/3574113/charts/5?dynamic=true&results=30)
- [Campo 6 — Total de bloqueios](https://thingspeak.mathworks.com/channels/3574113/charts/6?dynamic=true&results=30)

## Captura atual da simulação Wokwi

A captura mostra a montagem, as leituras seriais em 152 cm e uma publicação aceita pelo ThingSpeak.

![Simulação Wokwi em execução](https://github.com/user-attachments/assets/af1fa78d-1396-46a9-adce-f69dd2bfe521)

## Capturas atuais do painel ThingSpeak

As imagens seguintes mostram os gráficos públicos do canal. A imagem local `thingspeak-painel.png` permanece como registro histórico anterior; o painel público continua sendo a fonte atual dos gráficos.

### Distâncias e alertas

<img width="1265" height="712" alt="clipboard" src="https://github.com/user-attachments/assets/e49ae7ca-8524-4a0f-a7ff-07250d6795ed" />


<img width="1265" height="712" alt="clipboard" src="https://github.com/user-attachments/assets/c522e963-3c0c-4d83-94ac-8d424b5a44a2" />


### Contadores

<img width="1265" height="712" alt="clipboard" src="https://github.com/user-attachments/assets/3fcbf28d-56f3-48f4-bd26-96456c5ed2d0" />


As medições são simuladas. Os alertas são candidatos demonstrativos e não comprovam infrações.
