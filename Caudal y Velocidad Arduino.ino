/*
UNIVERSIDAD DE GUANAJUATO 
DESARROLLO DE SOFTWARE PARA LOCALIZAR FUGAS EN TIEMPO REAL EN LINEAS DE CONDUCCION DE AGUA POTABLE 
Veranos de la Ciencia UG 2022

Universidad de Guanajuato, CIS-DICIVA-DIA; eherrera@ugto.mx 
Universidad de Guanajuato, CG-DCEA; g.leonlanderos@ugto.mx 
Servicio Nacional De Aprendizaje Sena, Colombia; cikapudi@gmail.com 
Universidad de San Carlos de Guatemala, Guatemala; 201908045@ingenieria.usac.edu.gt 
Instituto Tecnológico Superior de la Región Sierra, Tabasco Méx.; pablo.halo.0426@hotmail.com 
*/

//Conteo de pulsos, número correspondiente al pin de ensamblaje 
volatile unsigned int count2; 
volatile unsigned int count3; 
volatile unsigned int count18;
volatile unsigned int count19; 

//Variables donde se almacena la frecuencia (Hz)
float frec_2; 
float frec_3; 
float frec_18; 
float frec_19; 

//Funcionones Count_ISR para incrementar de 1 en 1 el conteo de pulsos  
void count2_ISR(){
  count2++; 
} 
void count3_ISR(){ 
  count3++; 
} 
void count18_ISR(){ 
  count18++; 
} 
void count19_ISR() { 
  count19++; 
} 

void setup(){ 
  Serial.begin(9600); 
  //envio de  señal de prueba a los pines de interrupción 
  attachInterrupt(0, count2_ISR, RISING);  
  attachInterrupt(1, count3_ISR, RISING);  
  attachInterrupt(5, count18_ISR, RISING); 
  attachInterrupt(4, count19_ISR, RISING); 
} 

void loop(){ 
  static unsigned long lastSecond; 
  if (micros() - lastSecond >= 1000000L){
    lastSecond += 1000000; 

    getCount(); 
    float caudal_1 = obtener_caudal(frec_2); //Obtiene el caudal 1 
    Serial.print(caudal_1); //imprime caudal de caudalimetro 1 
    Serial.print(",");   
    float velocidad_1 = obtener_velocidad(caudal_1); //obtiene velocidad de caudal 1 
    Serial.print(velocidad_1); //imprime la velocidad de caudalimetro 1 
    Serial.print(","); 

    float caudal_2 = obtener_caudal(frec_3); 
    Serial.print(caudal_2); 
    Serial.print(","); 
    float velocidad_2 = obtener_velocidad(caudal_2); 
    Serial.print(velocidad_2); 

    float caudal_3 = obtener_caudal(frec_18); 
    Serial.print(caudal_3); 
    Serial.print(","); 
    float velocidad_3 = obtener_velocidad(caudal_3); 
    Serial.print(velocidad_3); 
    Serial.print(","); 

    float caudal_4 = obtener_caudal(frec_19); 
    Serial.print(caudal_4); 
    Serial.print(","); 
    float velocidad_4 = obtener_velocidad(caudal_4); 
    Serial.print(velocidad_4); 
    Serial.print(","); 
  } 
}

//funcion Contador de pulsacion de frecuencia 
unsigned int getCount(){ 
  noInterrupts(); 
  frec_2 = count2; 
  count_2 = 0; 
  frec_3 = count3; 
  count_3 = 0; 
  frec_18 = count18; 
  count_18 = 0; 
  frec_19 = count19; 
  count_19 = 0; 
  interrupts(); 
} 

float obtener_caudal(float frec){ 
  float caudal = frec/7.5;   //Caudal en L/min  
  return caudal;   
  } 

float obtener_Velocidad(float caudal){ 
  float velocidad = caudal/(0.000126676*60000);  //Velocidad en m/s 
  return velocidad;
} 