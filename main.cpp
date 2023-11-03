#include "stm32f10x.h"
#include <type_traits>
#include <cstdint>
#include <array>

namespace Driver
{
	namespace Variables
	{
		static constexpr std::uint32_t MODE_0 = UINT32_C(0b0001);
		static constexpr std::uint32_t MODE_1 = UINT32_C(0b0010);
		static constexpr std::uint32_t CNF_0 = UINT32_C(0b0100);
		static constexpr std::uint32_t CNF_1 = UINT32_C(0b1000);
		static constexpr std::uint32_t PULL_UP = UINT32_C(0b0001);
	}
	
	namespace Structures
	{		
		typedef enum
		{
			IOP_A,
			IOP_B,
			IOP_C,
			IOP_D,
			IOP_E,
			IOP_MAX,
		}e_gpio_port_t;
				
		typedef enum
		{
			INPUT,
			OUTPUT,
			ANALOG,
			ALTERNATE
		}e_gpio_direction_t;

		typedef enum
		{
			PIN_0,
			PIN_1,
			PIN_2,
			PIN_3,
			PIN_4,
			PIN_5,
			PIN_6,
			PIN_7,
			PIN_8,
			PIN_9,
			PIN_10,
			PIN_11,
			PIN_12,
			PIN_13,
			PIN_14,
			PIN_15,
			PIN_MAX,
		}e_gpio_pin_t;
		
		typedef struct
		{
			bool is_pin_active;
		}s_gpio_data_t;

		
	}
	namespace Registers
	{
		static constexpr std::array<std::uint32_t, Structures::IOP_MAX> RCC_APB2ENR = 
		{
			RCC_APB2ENR_IOPAEN,
			RCC_APB2ENR_IOPBEN,
			RCC_APB2ENR_IOPCEN,
			RCC_APB2ENR_IOPDEN,
			RCC_APB2ENR_IOPEEN			
		};
		
		static std::array<GPIO_TypeDef*, Structures::IOP_MAX> GPIO_x =
		{
			GPIOA,
			GPIOB,
			GPIOC,
			GPIOD,
			GPIOE,
		};
				
	}
	
	class GPIO
	{		
		private:
			Structures::s_gpio_data_t gpio_data;
		
		public:
			void GPIO_bus_enable(Structures::e_gpio_port_t e_iop_enr, bool enable)
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
			
			void GPIO_set_direction(Structures::e_gpio_port_t e_iop_enr, 
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
				
	};
}

 
int main()
{
	
	Driver::GPIO Led1;
	Led1.GPIO_bus_enable(Driver::Structures::IOP_A, true);
	Led1.GPIO_set_direction(Driver::Structures::IOP_A, 0, Driver::Structures::OUTPUT);
	Led1.GPIO_set_direction(Driver::Structures::IOP_A, 0, Driver::Structures::INPUT);
	Led1.GPIO_set_direction(Driver::Structures::IOP_A, 0, Driver::Structures::ANALOG);
	Led1.GPIO_set_direction(Driver::Structures::IOP_A, 1, Driver::Structures::OUTPUT);
	for(;;) 
	{
		
	}
}
