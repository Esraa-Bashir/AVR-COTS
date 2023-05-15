
#include "../../MCAL/DIO/DIO.h"
#include "LED_Cfg.h"
#include "LED.h"

const LED_strCfg_t LED_strCfg [LED_enuNoOfLeds]
 = {
	/*LED_NUMBER*/ /*PIN NUMBER*/ /*LED FORWARD OR REVERSE*/
	/*LED0*/{DIO_enuPin0,LED_enuActiveHigh	},
	/*LED1*/{DIO_enuPin1,LED_enuActiveHigh	},
	/*LED2*/{DIO_enuPin2,LED_enuActiveHigh	},
	/*LED3*/{DIO_enuPin3,LED_enuActiveHigh	},
	/*LED4*/{DIO_enuPin4,LED_enuActiveHigh	},
	///*LED5*/{DIO_enuPin5,LED_enuForward	},
	///*LED6*/{DIO_enuPin6,LED_enuForward	},
	///*LED7*/{DIO_enuPin7,LED_enuForward	},
	
};

	