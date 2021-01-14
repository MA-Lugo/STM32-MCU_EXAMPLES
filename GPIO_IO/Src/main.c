/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mario A. Lugo
 * @brief          : GPIO, input & output configuration and implementation
 * 					 from scratch on STM32F103C8T6 "Bluepill"
 ******************************************************************************
 */

#define RCC_BASE_ADDR			0X40021000UL

#define APB2_ENR_OFFSET			0X18U
#define APB2_ENR				(RCC_BASE_ADDR + APB2_ENR_OFFSET)


#define PORTB_BASE_ADDR			0X40010C00UL
#define PORTC_BASE_ADDR			0X40011000UL

#define GPIOx_CRH_OFFSET		0X04U
#define GPIOx_IDR_OFFSET		0X08U
#define GPIOx_ODR_OFFSET		0X0CU

#define GPIOB_CRL				PORTB_BASE_ADDR
#define GPIOB_CRH				(PORTB_BASE_ADDR + GPIOx_CRH_OFFSET)
#define GPIOB_ODR				(PORTB_BASE_ADDR + GPIOx_ODR_OFFSET)
#define GPIOB_IDR				(PORTB_BASE_ADDR + GPIOx_IDR_OFFSET)

#define GPIOC_CRL				PORTC_BASE_ADDR
#define GPIOC_CRH				(PORTC_BASE_ADDR + GPIOx_CRH_OFFSET)
#define GPIOC_ODR				(PORTC_BASE_ADDR + GPIOx_ODR_OFFSET)


#include <stdint.h>

int main(void)
{

//Enable Peripherarl clock for GPIOA and GPIOC
	uint32_t *pAPB2_ENR		= (uint32_t*) APB2_ENR;
	*pAPB2_ENR		|= ( 1 << 3 );		//Enable GPIOB clock
	*pAPB2_ENR		|= ( 1 << 4 );		//Enable GPIOC clock


//Configure pins
	uint32_t *pGPIOB_CRL	= (uint32_t*) GPIOB_CRL;
	uint32_t *pGPIOC_CRH	= (uint32_t*) GPIOC_CRH;

//***SET PB4
	//Set as input							MODE
	*pGPIOB_CRL		&= ~( 0x3 << 21 );
	// Set input with pull-up/pull-down 	CNF
	*pGPIOB_CRL		|= ( 1 << 23);
	*pGPIOB_CRL		&= ~( 1 << 22);
	//set pull-up resistor	(1:pull-up, 0:pull-down)
	uint32_t *pPORTB_WPU  = (uint32_t*)	GPIOB_ODR;
	*pPORTB_WPU		|= ( 1 << 5);


  //***SET PC13
	//Set as output max 10MHZ				MODE
	*pGPIOC_CRH		&= ~( 1 << 21);
	*pGPIOC_CRH		|= ( 1 << 20);
	// Set Push-pull output					CNF
	*pGPIOC_CRH		&= ~( 0x3 << 23);



//Clear PORTC
	uint32_t *pPORTC_OUT	= (uint32_t*) GPIOC_ODR;
	*pPORTC_OUT = 0X0000;

//Define PORTB input data reg
	uint32_t *pPORTB_IDR	= (uint32_t*) GPIOB_IDR;

	while(1){
		if (*pPORTB_IDR & ( 1 << 5)){
			*pPORTC_OUT |= ( 1 << 13);
		}
		else{
			*pPORTC_OUT &= ~( 1 << 13);
		}

	}
}
