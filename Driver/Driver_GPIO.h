#pragma once

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
		
		typedef enum
		{
			RISING_EDGE,
			FALLING_EDGE,
			BOTH_EDGES,
		}e_gpio_edge_detection_t;
		
		typedef struct
		{
			bool read_input;
			bool read_output;
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
			void GPIO_bus_enable(Structures::e_gpio_port_t e_iop_enr, bool enable);
			void GPIO_set_direction(Structures::e_gpio_port_t e_iop_enr, 
															std::uint8_t pin, 
															Structures::e_gpio_direction_t direction);
			void GPIO_set_edge_detection(Structures::e_gpio_edge_detection_t edge_detection);
			void GPIO_set_output(bool status);
			bool GPIO_get_input_state(void);
			bool GPIO_get_output_state(void);	
	};
}
