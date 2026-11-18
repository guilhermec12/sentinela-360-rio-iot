# CitizenTech IoT — Sentinela 360 Rio

Disciplina: Edge Computing & Computer Systems · FIAP Global Solution 2026.2 · Engenharia de Software, 1º ano, RJ

## Equipe

- Guilherme de Paula Correia
- João Vitor Barbosa Silva

## Problema e público beneficiado

Veículos que bloqueiam cruzamentos ou trafegam no sentido contrário podem elevar riscos para pedestres, ciclistas e passageiros do transporte público. O Relatório de Segurança Viária 2023 da Prefeitura do Rio informa que atropelamentos de pedestres e ciclistas representaram 46,9% dos sinistros fatais e aponta concentração de atropelamentos no Centro, incluindo o entorno da Avenida Presidente Vargas. O relatório fundamenta o recorte; a equipe não realizou observação de campo. Os locais e as imagens do protótipo são fictícios e não representam registros reais do Rio. Fonte: https://saude.prefeitura.rio/wp-content/uploads/sites/47/2025/01/Livro_RelatorioDeSegurancaViaria2023_Miolo_20240529-BaixaResolucao.pdf

## Solução

O ESP32 lê dois sensores ultrassônicos HC-SR04, processa os sinais localmente e acende LEDs para indicar candidatos simulados a contramão ou bloqueio. A ordem esperada é A → B; B → A gera candidato a contramão. A ocupação simultânea por mais de cinco segundos gera candidato a bloqueio. São alertas para análise, não infrações comprovadas.

Componentes: ESP32 DevKit V1, 2 HC-SR04, LED verde e LED vermelho com resistores de 220 Ω. Pinos: A TRIG/ECHO 18/19; B TRIG/ECHO 25/26; LEDs verde/vermelho 21/22. Em montagem física, o ECHO de 5 V deve ser reduzido para proteger GPIOs de 3,3 V.

## Links e arquivos

- Simulação Wokwi: https://wokwi.com/projects/480355518486978561
- Canal público ThingSpeak: https://thingspeak.mathworks.com/channels/3574113
- Firmware e circuito: pasta wokwi
- Evidências do ThingSpeak: pasta evidencias
- Repositório: https://github.com/guilhermec12/sentinela-360-rio-iot

A chave foi removida do sketch público. O Wokwi atual inicia em modo local e não envia novas leituras ao ThingSpeak. Uma chave nova só deve ser configurada numa cópia privada. A chave antiga continua válida até ser revogada na conta MathWorks.

## Validação e evidências

Em 18/11/2026, antes da limpeza da chave, o Wokwi conectou ao Wi-Fi virtual, reconheceu um candidato a bloqueio com os dois sensores a 20 cm e o ThingSpeak confirmou a entrada 111 com evento e total de bloqueios iguais a 1. Depois da limpeza, o sketch compilou e iniciou em modo local, lendo A=152 cm e B=152 cm. O histórico de 12/11 registra o cenário B → A. As leituras são simuladas; os contadores reiniciam com o ESP32 e não há câmera, IA treinada, identificação de veículos ou aplicação de multas.

- Detalhes do teste: evidencias/VALIDACAO-18-11-2026.md
- Dados do teste: evidencias/validacao-thingspeak-18-11-2026.json
- Gráficos históricos: evidencias/thingspeak-painel.png

## ODS relacionados

- ODS 11 — Cidades e Comunidades Sustentáveis.
- ODS 3 — Saúde e Bem-Estar.
