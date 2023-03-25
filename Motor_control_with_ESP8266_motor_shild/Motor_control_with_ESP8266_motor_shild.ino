// Двигатель A
#define in1 5  
#define in2 0  
// Двигатель B
#define in3 4  
#define in4 2  

void setup() 
   {
    pinMode(in1, OUTPUT);       // Устанавливаем in1 как выход
    pinMode(in2, OUTPUT);       // Устанавливаем in2 как выход
    pinMode(in3, OUTPUT);       // Устанавливаем in3 как выход
    pinMode(in4, OUTPUT);       // Устанавливаем in4 как выход
   }

void loop()
{
  digitalWrite(in1, HIGH);   // Включаем двигатель A
  digitalWrite(in2, LOW);    // Вращение двигателем А по часовой стрелке 
  delay(10000);               // Пауза 
  digitalWrite(in2, HIGH);   // Вращение двигателем А против часовой стрелке
  delay(10000);               // Пауза
  digitalWrite(in1, LOW);    // Выключаем двигатель А
  delay(10000);
  }
  
