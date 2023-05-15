#include "DIO_Cfg.h"
#include "DIO.h"
const DIO_strPinCfg_t DIO_strPinCfg [32] = {
	/*PORTA*/ /*PIN Direction*/ /*Pull UP Pull Down*/
	/*pin0*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin1*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin2*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin3*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin4*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin5*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin6*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	/*pin7*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN	},
	
	/*PORTB*/ /*PIN Direction*/ /*Pull UP Pull Down*/
	/*pin8*/{DIO_enuINPUT,DIO_INPUT_PULL_UP  },
	/*pin9*/{DIO_enuINPUT,DIO_INPUT_PULL_UP  },
	/*pin10*/{DIO_enuINPUT,DIO_INPUT_PULL_UP },
	/*pin11*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin12*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin13*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin14*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin15*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	
	/*PORTC*/ /*PIN Direction*/ /*Pull UP Pull Down*/
	/*pin16*/{DIO_enuINPUT,DIO_INPUT_PULL_UP },
	/*pin17*/{DIO_enuINPUT,DIO_INPUT_PULL_UP },
	/*pin18*/{DIO_enuINPUT,DIO_INPUT_PULL_UP },
	/*pin19*/{DIO_enuINPUT,DIO_INPUT_PULL_UP },
	/*pin20*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin21*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin22*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin23*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	
	/*PORTD*/ /*PIN Direction*/ /*Pull UP Pull Down*/
	/*pin24*/{DIO_enuINPUT,DIO_INPUT_PULL_DOWN },
	/*pin25*/{DIO_enuINPUT,DIO_INPUT_PULL_DOWN },
	/*pin26*/{DIO_enuINPUT,DIO_INPUT_PULL_UP },
	/*pin27*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin28*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin29*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin30*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN },
	/*pin31*/{DIO_enuOUTPUT,DIO_INPUT_PULL_DOWN }
	
};