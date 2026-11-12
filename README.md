# CitizenTech IoT — Sentinela 360 Rio

Protótipo da atividade CitizenTech IoT: Monitoramento Inteligente com ESP32 e ThingSpeak, da disciplina Edge Computing & Computer Systems — FIAP Global Solution 2026.2.

## Acesso e arquivos

- [Simulação Wokwi](https://wokwi.com/projects/480355518486978561)
- [ThingSpeak — canal público e gráficos](https://thingspeak.mathworks.com/channels/3574113)
- [Relatório técnico](TRABALHO.md)
- [Firmware ESP32 sem a chave de escrita](wokwi/sketch.ino)
- [Diagrama do circuito](wokwi/diagram.json)

## Problema, objetivo e beneficiários

O protótipo observa dois pontos de uma travessia e sinaliza padrões simulados de passagem em sentido inesperado ou ocupação simultânea prolongada. Pode apoiar discussões sobre segurança de pedestres, ciclistas e usuários de transporte público. Relaciona-se aos ODS 11 (Cidades e Comunidades Sustentáveis) e 3 (Saúde e Bem-Estar). A equipe ainda deve registrar o cruzamento/bairro e uma observação própria; não inventamos um endereço ou ocorrência local.

## Como funciona

Dois HC-SR04 medem as distâncias A/B. O ESP32 processa transições localmente, acende LED verde em leitura válida sem alerta e vermelho diante de alerta ou leitura inválida. A ordem esperada é A→B; a sequência inversa gera candidato a contramão. Ocupação simultânea por mais de 5 s gera candidato a bloqueio. A cada 20 s são enviados snapshots ao ThingSpeak. Para observar valores, mantenha a distância de teste até a próxima publicação.

| Campo | Conteúdo |
|---|---|
| 1 e 2 | Distâncias A/B (cm) |
| 3 e 4 | Estado candidato a contramão/bloqueio (0/1) |
| 5 e 6 | Contadores cumulativos desses eventos |

## Componentes e pinagem

ESP32 DevKit V1, dois HC-SR04, LEDs verde/vermelho e resistores de 220 Ω. TRIG/ECHO A: GPIO 18/19; B: 25/26; LEDs: GPIO 21/22. Em montagem física, adapte o ECHO de 5 V ao GPIO de 3,3 V do ESP32.

## Equipe e pendências

Guilherme Correia e João Vitor Barros — confirmar nomes completos oficiais. Falta registrar o bairro/cruzamento e uma observação da equipe. O cenário de bloqueio já foi testado: ambos os sensores em 20 cm geraram alerta no serial e total 1 no campo 6 do ThingSpeak; ao voltar a 150 cm, o alerta apagou e o total foi mantido. Ainda falta testar a sequência inversa e salvar capturas reais dos cenários.

## Limitações

Sensores e tráfego são simulados. Dois sensores não identificam pessoas/veículos nem comprovam infração; os sinais são candidatos para avaliação humana. Contadores em RAM zeram ao reiniciar. A chave de escrita não está no código público e deve ser configurada apenas numa cópia privada.
