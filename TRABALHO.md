# Relatório técnico — CitizenTech IoT

**Projeto:** Sentinela 360 Rio  
**Atividade:** CitizenTech IoT: Monitoramento Inteligente com ESP32 e ThingSpeak  
**Disciplina:** Edge Computing & Computer Systems — FIAP Global Solution 2026.2  
**Equipe cadastrada até agora:** Guilherme Correia e João Vitor Barros. Confirmar a forma completa dos nomes para a entrega.

## Problema e beneficiários

O protótipo demonstra observação de dois pontos de uma travessia e sinaliza sequências simuladas em sentido diferente do esperado e ocupação simultânea prolongada. O público considerado são pedestres, ciclistas e usuários do transporte público. A equipe ainda deve registrar o cruzamento/bairro observado e uma nota/foto própria; o endereço e a observação local não foram inventados.

## Objetivo e arquitetura

Demonstrar uma cadeia IoT didática: dois HC-SR04 medem distâncias; o ESP32 processa transições localmente; LEDs e monitor serial mostram os estados; Wi-Fi envia seis valores a cada 20 segundos ao ThingSpeak; os gráficos apresentam as séries. O sentido esperado configurado é A→B. A sequência B→A gera candidato a contramão. Ambos os pontos ocupados por mais de cinco segundos geram candidato a bloqueio. São sinais para demonstração e avaliação humana, não identificação nem prova de infração.

## Componentes e conexões

| Componente | Conexão no ESP32 |
|---|---|
| HC-SR04 A TRIG/ECHO | GPIO 18/19 |
| HC-SR04 B TRIG/ECHO | GPIO 25/26 |
| LED verde/vermelho | GPIO 21/22, cada um com resistor de 220 Ω |
| VCC/GND dos sensores | VIN/GND |

Veja o circuito em [wokwi/diagram.json](wokwi/diagram.json) e o firmware em [wokwi/sketch.ino](wokwi/sketch.ino). Para montagem real, adapte o ECHO de 5 V ao limite de 3,3 V do ESP32.

## Processamento e transmissão

Leituras válidas: 2–400 cm. O ponto é considerado ocupado a 40 cm ou menos e liberado acima de 50 cm (histerese). A ordem de passagem é avaliada em janela de 2,5 s. Quatrocentos milissegundos com os dois pontos livres rearma a detecção; cinco segundos simultaneamente ocupados contam bloqueio.

| Campo ThingSpeak | Conteúdo |
|---|---|
| 1 e 2 | Distâncias A/B em cm |
| 3 e 4 | Candidatos a contramão/bloqueio (0/1) |
| 5 e 6 | Contadores cumulativos desses candidatos |

O firmware usa HTTPS e valida TLS. A chave de escrita foi omitida do código público; deve ser configurada somente numa cópia privada do sketch. O estado dos campos 3/4 é um snapshot periódico e pode não coincidir com um evento breve; os contadores 5/6 conservam a ocorrência até reiniciar o ESP32.

## Verificação observada

A simulação conectou ao Wi-Fi Wokwi e o monitor serial confirmou as entradas ThingSpeak. Com os dois sensores em 20 cm, o serial indicou candidato a bloqueio após cinco segundos e contador 1; o canal recebeu a mudança de distância e o total no campo 6. Ao restaurar 150 cm, o alerta foi limpo e o total permaneceu 1. Ainda falta demonstrar a sequência inversa para testar contramão e salvar capturas reais dos cenários.

## Beneficiários e ODS

O projeto promove debate sobre segurança de pedestres, ciclistas e usuários de transporte público e se relaciona aos ODS 11 (Cidades e Comunidades Sustentáveis) e 3 (Saúde e Bem-Estar). Não substitui engenharia de tráfego nem fiscalização.

## Limitações e pendências da equipe

Sensores, tráfego e distâncias são simulados. Dois pontos ultrassônicos não identificam objetos nem provam direção real. Os contadores ficam na RAM e zeram no reinício. Antes da entrega, completar os nomes oficiais da equipe, registrar o território e a observação real, e anexar evidências de cada cenário. O canal ThingSpeak 3574113 está público.

**Referência:** FIAP, *Desafio FIAP: CitizenTech*, Global Solution 2026.2, Edge Computing & Computer Systems, pp. 36–39.
