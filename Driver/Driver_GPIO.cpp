#include "Driver_GPIO.h"

namespace Driver
{
	
	void GPIO::GPIO_bus_enable(Structures::e_gpio_port_t e_iop_enr, bool enable)
			{
				if (enable == true)
				{
					RCC->APB2ENR |= Registers::RCC_APB2ENR[e_iop_enr];
				}
				else
				{
					RCC->APB2ENR &= ~(Registers::RCC_APB2ENR[e_iop_enr]);
				}
			}
			
			void GPIO::GPIO_set_direction(Structures::e_gpio_port_t e_iop_enr, 
															std::uint8_t pin, 
															Structures::e_gpio_direction_t direction)
			{
				if(pin < 8)
				{
					if (direction == Structures::INPUT)
					{
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::MODE_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::MODE_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::CNF_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL |= (Variables::CNF_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->ODR |= (Variables::PULL_UP << pin);
					}
					else if (direction == Structures::OUTPUT)
					{
						Registers::GPIO_x[e_iop_enr]->CRL |= (Variables::MODE_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::MODE_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::CNF_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::CNF_1 << (pin*4));
					}
					else if (direction == Structures::ANALOG)
					{
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::MODE_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::MODE_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::CNF_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRL &= ~(Variables::CNF_1 << (pin*4));
					}
					else if (direction == Structures::ALTERNATE)
					{
						
					}
					else
					{
						//Does nothing
					}
				}
				else if (pin >= 8)
				{
					if (direction == Structures::INPUT)
					{
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::MODE_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::MODE_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::CNF_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH |= (Variables::CNF_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->ODR |= ~(Variables::PULL_UP << pin);
					}
					else if (direction == Structures::OUTPUT)
					{
						Registers::GPIO_x[e_iop_enr]->CRH |= (Variables::MODE_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::MODE_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::CNF_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::CNF_1 << (pin*4));
					}
					else if (direction == Structures::ANALOG)
					{
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::MODE_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::MODE_1 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::CNF_0 << (pin*4));
						Registers::GPIO_x[e_iop_enr]->CRH &= ~(Variables::CNF_1 << (pin*4));
					}
					else if (direction == Structures::ALTERNATE)
					{

					}
					else
					{
						//Does nothing
					}
				}
				else
				{
					//Does Nothing
				}
			}
}

