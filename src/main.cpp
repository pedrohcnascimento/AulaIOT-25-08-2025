/*
Autor: Pedro (PHCN)
Turma: DEV-T1
Aula: 05
Data: 25/08/2025
Projeto: DualCore código base
Versão: 1.0
Comentários: Estrutura base para ativar o segundo núcleo (Núcleo 0 do ESP32)
*/
//______________________________________________________________________________________________________________________________________________________________________________________________________

// Incluir Bibliotecas
#include <Arduino.h> //inclui bibliotecas de compatibilidade de funções do Arduino
#include <esp_task_wdt.h>//Biblioteca que permite manipular o watchdog no segundo núcleo
TaskHandle_t Task1; //Declara tarefa que será executa nosegundo núcleo (dual core)
//______________________________________________________________________________________________________________________________________________________________________________________________________
// Define pinos do Hardware

// Saídas digitais (LEDs)
#define LED_1 19
#define LED_2 18
#define LED_3 5
#define LED_4 4
#define LED_5 2

// Entradas digitais (Botões)
#define BT_1 35
#define BT_2 32
#define BT_3 27
#define BT_4 25
#define BT_5 26

// Entradas analógicas (Sensores)
#define POT 33
#define LDR 34

// Outras definições de hardware

//______________________________________________________________________________________________________________________________________________________________________________________________________
// Declara variáveis e constantes globais

//______________________________________________________________________________________________________________________________________________________________________________________________________
// Inicializa Objetos

//______________________________________________________________________________________________________________________________________________________________________________________________________
// Declara funções
void Task1code(void *pvParameters);
//______________________________________________________________________________________________________________________________________________________________________________________________________
// Configuração do sistema

void setup()
{
  // Configura LEDs como saidas (OUTPUT)
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);

  // Configura BOTÕES como entradas (INPUT)
  pinMode(BT_1, INPUT);
  pinMode(BT_2, INPUT);
  pinMode(BT_3, INPUT);
  pinMode(BT_4, INPUT);
  pinMode(BT_5, INPUT);

  // Configurando o segundo núcleo
  xTaskCreatePinnedToCore(
    Task1code,  //1. A função que contém o código da tarefa
    "Task1",    //2. Um nome descritivo para a tarefa
    1000,       //3. O tamanho da memória "stack" para a tarefa
    NULL,       //4. Parâmetros a serem passados para a tarefa (nenhum neste caso)
    0,          //5. A prioridade da tarefa
    &Task1,     //6. Um "handle" para controlar a terfa depois
    0           //7. O núcleo (core) da CPU onde a tarefa deve rodar
  );
}
//______________________________________________________________________________________________________________________________________________________________________________________________________
// Laço principal
void loop()
{
  digitalWrite(LED_1, LOW);
  delay(1000);
  digitalWrite(LED_1, HIGH);
  delay(1000);
}
//______________________________________________________________________________________________________________________________________________________________________________________________________
// Laço secundário
void loop_2()
{
  //Roda no núcleo 0 do ESP32
  digitalWrite(LED_3, LOW);
  delay(500);
  digitalWrite(LED_3, HIGH);
  delay(500);
}
//______________________________________________________________________________________________________________________________________________________________________________________________________
//Funções

void Task1code(void *pvParameters){
  esp_task_wdt_init(3000, false);
  while(1)
  {
    loop_2();
  }
}