#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define delay_time 5000 //tempo de espera em ms para a mudança de 90 graus
#define delay_step 10   //tempo de espera em ms para a mudança do passo

const uint16_t PWM_SERVO_PIN = 22;
const uint16_t PWM_LED_PIN = 12;
const uint16_t WRAP_PERIOD = 24999; //valor máximo do contador - WRAP
const float PWM_DIVISER = 100.0; //divisor do clock para o PWM
const uint16_t PWM_STEP = 6; //passo de incremento/decremento para o duty cycle do LED
uint16_t PWM_LEVEL1 = 3000; //duty cycle 12%    (180 graus)
uint16_t PWM_LEVEL2 = 1837; //duty cycle 7,35%  (90 graus)
uint16_t PWM_LEVEL3 = 625; //duty cycle 2,5% (0 grau)
uint16_t PWM_DEG = 0; //duty cycle para variar o angulo.
bool flag = false;

//fpwm = 125E+6/((100+0/16)*(24999+1)) = 50Hz
//dc1 = 12% => PWM_LEVEL = 3000 
//dc2 = 7,35% => PWM_LEVEL = 1875
//dc3 = 2,5% => PWM_LEVEL = 625
//step = (WRAP_PERIOD * 5E-06)/20E-03

//função para configurar o módulo PWM
void pwm_setup(const uint16_t PWM_PIN)
{
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice1 = pwm_gpio_to_slice_num(PWM_PIN); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice1, PWM_DIVISER); //define o divisor de clock do PWM

    pwm_set_wrap(slice1, WRAP_PERIOD); //definir o valor de wrap

    pwm_set_enabled(slice1, true); //habilita o pwm no slice correspondente
}


void pwm_control()
{
        printf("Topo do contador: %d (180º)\n", PWM_LEVEL1);
        pwm_set_gpio_level(PWM_SERVO_PIN, PWM_LEVEL1); // Aplica PWM_LEVEL1
        pwm_set_gpio_level(PWM_LED_PIN, PWM_LEVEL1); // Aplica PWM_LEVEL1
        sleep_ms(delay_time);
    
        printf("Topo do contador: %d (90º)\n", PWM_LEVEL2);
        pwm_set_gpio_level(PWM_SERVO_PIN, PWM_LEVEL2); // Aplica PWM_LEVEL2
        pwm_set_gpio_level(PWM_LED_PIN, PWM_LEVEL2); // Aplica PWM_LEVEL1
        sleep_ms(delay_time);
    
        printf("Topo do contador: %d (0º)\n", PWM_LEVEL3);
        pwm_set_gpio_level(PWM_SERVO_PIN, PWM_LEVEL3); // Aplica PWM_LEVEL3
        pwm_set_gpio_level(PWM_LED_PIN, PWM_LEVEL3); // Aplica PWM_LEVEL1
        sleep_ms(delay_time);
}

//função principal
int main()
{
    stdio_init_all(); //inicializa o sistema padrão de I/O
    
    pwm_setup(PWM_SERVO_PIN); //configura o PWM
    pwm_setup(PWM_LED_PIN); //configura o PWM

    pwm_control();

    PWM_DEG = PWM_LEVEL3;

    //loop principal
    while (true) {
        
        if(!flag)
        {
            PWM_DEG += PWM_STEP;
            pwm_set_gpio_level(PWM_SERVO_PIN, PWM_DEG); // Aplica PWM_LEVEL3
            pwm_set_gpio_level(PWM_LED_PIN, PWM_DEG); // Aplica PWM_LEVEL3
            printf("\nTopo do contador incrementado: %d \n", PWM_DEG);
            
            if(PWM_DEG >= PWM_LEVEL1) flag = true;
            

        }else
        {
            PWM_DEG -= PWM_STEP;
            pwm_set_gpio_level(PWM_SERVO_PIN, PWM_DEG); // Aplica PWM_LEVEL3
            pwm_set_gpio_level(PWM_LED_PIN, PWM_DEG); // Aplica PWM_LEVEL3
            printf("\nTopo do contador decrementado: %d \n", PWM_DEG);

            if(PWM_DEG <= PWM_LEVEL3) flag = false;
        }

        sleep_ms(delay_step);
    }
} 


