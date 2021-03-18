#include <LiquidCrystal.h>   
#include <Keypad.h>
int a=0, b=0, c=0, d=0;//Inteiros que vão armazenar a password
int var=0; //Variavel auxialiar para o switch
int C1=1,C2=2,C3=3,C4=4;//Definição da password
char f='*';  //Caracter para esconder o carcater original
int vezes=0,incorrecto=0; //Segurança de apenas 3 tentativas.
int aviso=3; //Aviso para saber em quantas tentativas vai
const byte filas = 4; //numero de filas.
const byte columnas = 4; //numero de colunas.
char tecla[filas][columnas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinFilas[filas] = {7, 6, 5, 4}; //declaração dos pinos ligados as filas
byte pinColumnas[columnas] = {3, 2, 1, 0}; //declaração dos pinos ligados as colunas

Keypad keypad = Keypad( makeKeymap(tecla), pinFilas, pinColumnas, filas, columnas );
LiquidCrystal lcd(8,9,10,11,12,13); //D7,D6,D4,E,RS
void setup(){
  lcd.begin(16,2); //LCD (16 COLUNAS e 2 FILAS)
  pinMode(A0,OUTPUT); //LED Verde - Pass correta
  pinMode(A1,OUTPUT); //LED Vermelho - Pass incorreta
}
  
void loop(){
  char key = keypad.getKey();
  if (key){
   lcd.setCursor(6+var,1);
   lcd.print(key),lcd.setCursor(6+var,1),lcd.print(f);//imprimir o caracter * no lcd
   key=key-48; //converção de char em inteiros
   var++; //incremento da auxiliar para armazenar todos os casos no switch
   switch(var){
    case 1:
    a=key; //armazenar o primeiro digito para a contrasenha 
    break;
    case 2:
    b=key; //armazenar o segundo digito para a contrasenha 
    break;
    case 3:
    c=key; //armazenar o terceiro digito para a contrasenha 
    break;
    case 4:
    d=key; //armazenar o quarto digito para a contrasenha 
   delay(100);
  if(a==C1 && b==C2 && c==C3 && d==C4){//se a,b,c,d forem iguais ao declarado em cima na pass entao
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Password");
    lcd.setCursor(5,1);
    lcd.print("Valida");
    digitalWrite(A0,HIGH);//LED Verde acende
    delay(1000); //fica ligado durante 1segundo
    lcd.clear();
    digitalWrite(A0,LOW);//LED Verde desliga
    }
  else{
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Password");
    lcd.setCursor(4,1);
    lcd.print("Invalida");
    digitalWrite(A1,HIGH); //LED Vermelho acende
    delay(1000); //fica ligado durante 1segundo
    lcd.clear();
    digitalWrite(A1,LOW); //Led vermelho desliga
    }
//------Segurança das tres falhas-------------------//

  if(a==C1 && b==C2 && c==C3 && d==C4){
      vezes=0;//Se for correto, a variavel vezes não altera
      aviso=3;//E a variavel aviso manten-se no 3
    }
  else{
      vezes ++; //acrescenta-se 1 valor a variavel vezes
      aviso --; //decrementa-se 1 valor a variavel aviso. até atingir o 0
      lcd.setCursor(2,0);
      lcd.print("RESTA-LHE: "); 
      lcd.setCursor(13,0);
      lcd.print(aviso); //imprime o numero de oportunidades restantes
      lcd.setCursor(2,1);
      lcd.print("OPORTUNIDADE");
      delay(1000);
       if(aviso==0){
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("ALARME");
          lcd.setCursor(4,1);
          lcd.print("ATIVADO");
        }
      delay(300);lcd.clear();
      }

  while(vezes>=3){ //quando atingir as 3 vezes erradas, vai aparecer a piscar a mensagem
      lcd.setCursor(1,0),lcd.print("Alerta Policia");
      lcd.setCursor(4,1),lcd.print("Intrusos");
      digitalWrite(A1,HIGH); //acende o led vermelho
      delay(500);
      lcd.clear();
      digitalWrite(A1,LOW);
      delay(500);
  }

   var=0;
   lcd.clear();

  break;//termina
  }

 }
 if(!key){lcd.setCursor(0,0),lcd.print("Insira Password");}//mensagem de inicio

  delay(2);
}
