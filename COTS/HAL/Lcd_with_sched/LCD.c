 
 #include "../../LIB/BIT_MATH.h"
 #include "../../LIB/STD_TYPES.h"
 #include "../../MCAL/DIO/DIO.h"
 #include "LCD.h"
 #include "LCD_Cfg.h"


 typedef struct {
	 const u8 * string;
	 u8 str_len;
	 u8 xpos;
	 u8 ypos;
	 u8 request_type;
	 
 }LCD_requestHandler;
 
 typedef enum {
	 LCD_NoTask,
	 LCD_WriteStringRequest,
	 LCD_ClearScreenRequest,
 }LCD_requestsTypes;
 
 typedef enum {
	 LCD_FunctionSet_Stage=0,
	 LCD_DisplayControl_Stage,
	 LCD_DisplayClearCommand_Stage,
	 LCD_EntryMode_Stage,
	 LCD_Finished_Stage,
 }LCD_initSequence;

 typedef enum {
	 setposition_stage=0,
	 writeCharacter_stage,
	 finishied_stage,
 }writeString_sequence;

 static u8 LCD_enuSendData    (u8 Copy_u8Data);
 static u8 LCD_enuSendCommand (u8 Copy_u8Command);
 static u8 LCD_enuGotoXY_seq(void);
 static u8 set_enablePin(void);
 static u8 LCD_intiallized_flag=0;
 static u8 LCD_state_flag=LCD_Ideal;
 static LCD_requestHandler request;
 
  static u8 LCD_enuSendCommand  (u8 Copy_u8Data){
	  static u8 stage =0;
	  u8 finished_flag=0;
	  switch(stage){
		  case 0:
		  DIO_enuSetValue(RS_PIN, DIO_enuLOW);
		  DIO_enuSetValue(RW_PIN, DIO_enuLOW);
		  DIO_enuSetValue(E_PIN, DIO_enuHIGH);
		  DIO_enuSetPortValue(DATA_PORT,Copy_u8Data);
		  stage ++;
		  break;
		  case 1:
		  DIO_enuSetValue(E_PIN, DIO_enuLOW);
		  stage++;
		  break;
		  case 2:
		  stage=0;
		  finished_flag=1;
		  break;
	  }
	  return finished_flag;
  }


  static u8 LCD_enuSendData    (u8 Copy_u8Data){
	  static u8 stage =0;
	  u8 finished_flag=0;
	  switch(stage){
		  case 0:
		  DIO_enuSetValue(RS_PIN, DIO_enuHIGH);
		  DIO_enuSetValue(RW_PIN, DIO_enuLOW);
		  DIO_enuSetValue(E_PIN, DIO_enuHIGH);
		  DIO_enuSetPortValue(DATA_PORT,Copy_u8Data);
		  stage ++;
		  break;
		  case 1:
		  DIO_enuSetValue(E_PIN, DIO_enuLOW);
		  stage++;
		  break;
		  case 2:
		  stage=0;
		  finished_flag=1;
		  break;
		  
	  }
	  return finished_flag;
  }

 void  LCD_vidInit  (){
	 static u8 stage = LCD_FunctionSet_Stage,count=0;
	 u8 flag=0;
	 switch(stage){
		 case LCD_FunctionSet_Stage:
		 count ++;
		 if (count>=30){
		 flag = LCD_enuSendCommand(LCD_FunctionSet);
		 if (flag==1)
		 stage++;
		 }
		 break;
		 case LCD_DisplayControl_Stage:
		 flag = LCD_enuSendCommand(LCD_DisplayControl);
		 if (flag==1)
		 stage++;
		 break;
		 case LCD_DisplayClearCommand_Stage:
		 flag= LCD_enuSendCommand(LCD_DisplayClearCommand);
		 if (flag==1)
		 stage++;
		 break;
		 case LCD_EntryMode_Stage:
		 flag = LCD_enuSendCommand(LCD_EntryMode);
		 if (flag==1)
		 stage++;
		 break;
		 case LCD_Finished_Stage:
		 LCD_intiallized_flag=1;
		 stage=0;
		 break;
		 
	 }
	 
 }
 
 u8 LCD_enuWriteString (char* Add_pchString,u8 cpy_len, u8 xpos ,u8 ypos){
	 u8 loc_state=LCD_Busy;
	 if (LCD_state_flag == LCD_Ideal){
		 loc_state = LCD_Ideal;
		 LCD_state_flag = LCD_Busy;
		 request.request_type= LCD_WriteStringRequest;
		 request.string= Add_pchString;
		 request.str_len =cpy_len;
		 request.xpos = xpos;
		 request.ypos= ypos;
	 }
	 return loc_state;
 }
 
  u8 LCD_enuClearScreen(void){
	  u8 loc_state=LCD_Busy;
	  if (LCD_state_flag == LCD_Ideal){
		  loc_state = LCD_Ideal;
		  LCD_state_flag = LCD_Busy;
		  request.request_type= LCD_ClearScreenRequest;
	  }
	  return loc_state;
  }

 static u8 LCD_enuWriteString_seq (void){
	 
	 static u8 stage = setposition_stage ;
	 static u8 current_char=0;
	 u8 flag,finished_flag=0;
	 switch(stage){
		 case setposition_stage:
		 flag = LCD_enuGotoXY_seq();
		 if (flag==1){
			 stage ++;
		 }
		 break;
		 case writeCharacter_stage:
		 flag = LCD_enuSendData (request.string[current_char]);
		 if (flag==1)
		 {
			 current_char ++;
		 }
		 if (current_char == request.str_len&& flag==1)
		 {
			 current_char =0;
			 finished_flag =1;
			 stage = setposition_stage;
		 }
		 break;
		 case finishied_stage:
		 
		 break;
	 }
	 
	 return finished_flag;
 }



 
 static u8 LCD_enuClearScreen_seq(void){
	 u8 finished_flag=0;
	 finished_flag = LCD_enuSendCommand(LCD_DisplayClearCommand);
	 return finished_flag;
 }


 static u8 LCD_enuGotoXY_seq(void){
	 u8 finished_flag=0;
	 u8 Loc_u8Command = (request.xpos * (0x40) + request.ypos )+128;
	 finished_flag = LCD_enuSendCommand(Loc_u8Command );
	 return finished_flag;
 }



 /* performed each 2 msec */
 void LCD_Task(void){
	 if (LCD_intiallized_flag == 0)
	 {
		 LCD_vidInit  ();
	 }
	 else {
		 
		 if (LCD_state_flag==LCD_Busy){
			 u8 finishedFlag=0;
			 if (request.request_type== LCD_WriteStringRequest)
			 {
				 finishedFlag =LCD_enuWriteString_seq();
			 }
			 else if (request.request_type== LCD_ClearScreenRequest){
				 finishedFlag =LCD_enuClearScreen_seq();
				 
			 }
			 if (finishedFlag==1)
			 {
				 LCD_state_flag=LCD_Ideal;
				 
			 }
		 }
	 }
	 
 }