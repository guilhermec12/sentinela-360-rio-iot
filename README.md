# CitizenTech IoT — Sentinela 360 Rio

Protótipo da atividade de Edge Computing & Computer Systems da FIAP Global Solution 2026.2: ESP32 no Wokwi, dois sensores HC-SR04, sinalização local e telemetria no ThingSpeak.

## Links

- [Simulação Wokwi](https://wokwi.com/projects/480355518486978561)
- [ThingSpeak — canal público e gráficos](https://thingspeak.mathworks.com/channels/3574113)

## Problema, objetivo e beneficiários

O projeto demonstra como observar dois pontos de uma travessia e sinalizar padrões simulados de passagem em sentido inesperado ou ocupação simultânea prolongada. Busca apoiar a discussão sobre segurança de pedestres, ciclistas e usuários do transporte público (ODS 11 e ODS 3). O protótipo não identifica veículos nem comprova infrações. A equipe deve incluir a observação real do cruzamento/bairro escolhido antes da entrega; esse dado não foi inventado.

## Como funciona

O ESP32 lê as distâncias A/B, processa localmente as transições, acende LED verde para condição normal e vermelho para alerta/medição inválida, e envia snapshots ao canal a cada 20 s. O sentido padrão é A→B; a sequência contrária e a ocupação dos dois pontos por mais de 5 s geram candidatos a alerta.

| Campo | Dado |
|---|---|
| 1–2 | Distâncias A/B (cm) |
| 3–4 | Candidato a contramão/bloqueio (0/1) |
| 5–6 | Totais de candidatos a contramão/bloqueio |

Para notar uma mudança de distância, mantenha o valor de teste até a publicação seguinte. Os contadores preservam ocorrências entre snapshots.

## Componentes e pinagem

ESP32 DevKit V1, dois HC-SR04, LEDs verde/vermelho e resistores de 220 Ω. TRIG/ECHO A: GPIO 18/19; B: 25/26; LEDs: 21/22.

## Equipe e pendências

- Guilherme Correia — inserir nome completo oficial.
- João Vitor Barros — inserir nome completo oficial.

O briefing pede nomes completos e uma necessidade local documentada. Completar esses dados e adicionar capturas reais de circuito, monitor serial e gráficos antes da entrega. O relatório e os arquivos-fonte completos estão no pacote local disponibilizado nesta conversa.

## Limitações

Simulação didática: sensores, tráfego e distâncias são virtuais; alertas exigem avaliação humana. Os contadores ficam na RAM e zeram ao reiniciar. Em montagem física, o ECHO de 5 V requer adequação ao GPIO de 3,3 V do ESP32. A Write API Key não deve ser armazenada neste repositório público.
