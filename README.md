# Embarcatech_PWM

Repositório criado para a tarefa relacionada ao uso do PWM.

O programa implementa uma rotina que varia o ciclo de trabalho de um servomotor e de um LED azul.
Inicialmente, esse ciclo é alterado três vezes de maneira instantânea, com intervalos de 5 segundos entre cada alteração. O ciclo é ajustado para 12%, 7,35% e 2,5%, respectivamente. Isso gera uma variação no ângulo da hélice do servomotor, que se inicia em 180º, depois é reduzida para 90º e, por fim, para 0º. Essa mudança também é percebida na intensidade luminosa do LED azul.

Após isso, o programa entra em um loop que gradualmente incrementa e decrementa o ciclo de trabalho do PWM em aproximadamente 0,024% a cada 10 milissegundos.
O incremento ocorre enquanto o ciclo de trabalho for menor que 12%, e o decremento ocorre enquanto for maior que 2,5%. Esse controle é realizado com o auxílio de uma flag, que indica se a rotina deve incrementar ou decrementar o ciclo.


# Instruções de compilação

Para compilar o código, são necessárias as seguintes extensões:

*Wokwi Simulator*
*Raspberry Pi Pico*
*CMake*

Após instalá-las, basta compilar o projeto pelo CMake. Em seguida, abra o arquivo diagram.json e clique no botão verde para iniciar a simulação.

# Vídeo demonstrativo

https://youtube.com/shorts/bDYek8KA6ws?feature=share
