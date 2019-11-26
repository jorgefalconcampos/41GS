
 ;Programa que hace TRES interrupciones, dos de baja prioridad y una de alta prioridad
 ;El programa principal decodifica en un display 7SEG la palabra "hola".
 
 ;En la interrupción de alta prioridad muestra una carita feliz
 
     
    LIST P=18F4550
    #INCLUDE<P18F4550.INC> 
    
    
    
    		;CONFIG1L dir 300000h 	20
		;CONFIG	PLLDIV=1	 ; 
		;CONFIG	CPUDIV=OSC1_PLL2 ;CUANDO SE USA XTAL	
		;CONFIG	USBDIV=2

		;CONFIG1H dir 300001h	08
		CONFIG	FOSC=INTOSCIO_EC ;OSCILADOR INTERNO, RA6 COMO PIN, USB USA OSC EC
		CONFIG	FCMEN=OFF        ;DESHABILITDO EL MONITOREO DEL RELOJ
		CONFIG	IESO=OFF

		;CONFIG2L DIR 300002H	38
		CONFIG	PWRT=ON          ;PWRT HABILITADO
		CONFIG  BOR=OFF		 ;BROWN OUT RESET DESHABILITADO
		CONFIG BORV=3		 ;RESET AL MINIMO VOLTAJE NO UTILZADO EN ESTE CASO
		CONFIG	VREGEN=ON	 ;REULADOR DE USB ENCENDIDO

		;CONFIG2H DIR 300003H	1E
		CONFIG	WDT=OFF          ;WACH DOG DESHABILITADO
		CONFIG WDTPS=32768      ;TIMER DEL WATCHDOG 
		
		;CONFIG3H DIR 300005H	81
		CONFIG	CCP2MX=ON	 ;CCP2 MULTIPLEXADAS CON RC1	
		CONFIG	PBADEN=OFF       ;PUERTO B PINES DEL 0 AL 4 ENTRADAS DIGITALES
		CONFIG  LPT1OSC=OFF	 ;TIMER1 CONFIURADO PARA OPERAR EN BAJA POTENCIA
		CONFIG	MCLRE=ON         ;MASTER CLEAR HABILITADO
		
		;CONFIG4L DIR 300006H	81
		CONFIG	STVREN=ON	 ;SI EL STACK SE LLENA CAUSE RESET		
		CONFIG	LVP=OFF		 ;PROGRAMACIÒN EN BAJO VOLTAJE APAGADO
		CONFIG	ICPRT=OFF	 ;REGISTRO ICPORT DESHABILITADO
		CONFIG	XINST=OFF	 ;SET DE EXTENCION DE INSTRUCCIONES Y DIRECCIONAMIENTO INDEXADO DESHABILITADO

		;CONFIG5L DIR 300008H	0F
		CONFIG	CP0=OFF		 ;LOS BLOQUES DEL CÒDIGO DE PROGRAMA
		CONFIG	CP1=OFF          ;NO ESTAN PROTEGIDOS
		CONFIG	CP2=OFF		 
		CONFIG	CP3=OFF
		
		;CONFIG5H DR 300009H	C0
		CONFIG	CPB=OFF		 ;SECTOR BOOT NO ESTA PROTEGIDO
		CONFIG	CPD=OFF		 ;EEPROM N PROTEGIDA

		;CONFIG6L DIR 30000AH	0F
		CONFIG	 WRT0=OFF	 ;BLOQUES NO PROTEGIDOS CONTRA ESCRITURA
		CONFIG	 WRT1=OFF
		CONFIG	 WRT2=OFF
		CONFIG	 WRT3=OFF

		;CONFIG6H DIR 30000BH	E0
		CONFIG	 WRTC=OFF	 ;CONFIGURACION DE REGISTROS NO PROTEGIDO
		CONFIG	 WRTB=OFF	 ;BLOQUE BOOTEBLE NO PROTEGIDO
		CONFIG	 WRTD=OFF	 ;EEPROMDE DATOS NO PROTGIDA

		;CONFIG7L DIR 30000CH	0F
		CONFIG	 EBTR0=OFF	 ;TABLAS DE LETURA NO PROTEGIDAS
		CONFIG	 EBTR1=OFF
		CONFIG	 EBTR2=OFF
		CONFIG	 EBTR3=OFF

		;CONFIG7H DIR 30000DH	40
		CONFIG	 EBTRB=OFF	 ;TABLAS NO PROTEGIDAS	
    
    
    
    CBLOCK H'00' ; SE HACE ESTA 'COPIA' XQ DEBEMOS REGRESAR AL ESTADO QUE ESTABA DESPUÉS DE HACER LA INTERRUPCIÓN
	
	;Copias de baja prioridad
	WREGC_BAJA ;Copia de WREG
	STATUSC_BAJA ;Copia de STATUS
	BSRC_BAJA ;Copia del BSR
	TMR0LC_BAJA ;Copia del TIMER0-LOW
	
	;Copias de alta prioridad
	WREGC_ALTA ;Copia del registro W
	STATUSC_ALTA ;Copia de STATUS
	BSRC_ALTA ;Copia del BSR
	TMR0LC_ALTA ;Copia del TIMER0-LOW
	
	;Copias de... 
	WREGC ;Copia de WREG
	STATUSC ;Copia de STATUS
	BSRC ;Copia del BSR
	TMR0LC ;Copia del TIMER0-LOW

    ENDC
    
    #DEFINE LED PORTC,0,0 ;Alta prioridad
    #DEFINE LED2 PORTC,1,0 ;Baja prioridad (1)
    #DEFINE LED3 PORTC, 2,0 ;Baja prioridad (2)
    
    
    
    
    
    
    
    
    
    
    ORG .0
    GOTO INICIO
    
    ORG .8
    GOTO BACKUP_ALTA
    
    ORG .18
    GOTO BACKUP_BAJA1
    
  
;----- BAJA PRIORIDAD -----    
    
;BAJA(1)    
BACKUP_BAJA1 ;Hacemos la copia para cuando se interrumpe en baja prioridad
    MOVFF WREG, WREGC_BAJA
    MOVFF STATUS, STATUSC_BAJA
    MOVFF BSR, BSRC_BAJA
    MOVFF TMR0L, TMR0LC_BAJA  
    
ASKB ;Interrupción de baja prioridad
    BTFSS INTCON3, INT1IF
    GOTO ASK1A  ;Interr. de baja prioridad
    BCF INTCON3, INT1IF
LED_INTERMITENTE ;Prendemos el LED intermitente que anuncia una interrupción baja (1), esperamos... y lo apagamos para indicar una interrupción
    BSF LED2
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BCF LED2
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BSF LED2
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BCF LED2
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BSF LED2
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BCF LED2  
SALIR_BAJA1
    MOVFF WREGC_BAJA, WREG
    MOVFF STATUSC_BAJA, STATUS
    MOVFF BSRC_BAJA,BSR
    MOVFF TMR0LC_BAJA, TMR0L
    RETFIE
    
    
   
;BAJA(2)  
BACKUP_BAJA2 ;Hacemos la copia para cuando se interrumpe
    MOVFF WREG, WREGC
    MOVFF STATUS, STATUSC
    MOVFF BSR, BSRC
    MOVFF TMR0L, TMR0LC
    
ASK2
    BTFSS INTCON3, INT2IF
    BRA ASK1A
    BCF INTCON3, INT2IF
    
  LED_ON_OFF_INT_BAJA ;Prendemos el LED que anuncia una interrupción baja(2), esperamos... y lo apagamos para indicar que terminó la interrupción
    BSF LED3
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BCF LED3
    
SALIR_BAJA2
    MOVFF WREGC, WREG
    MOVFF STATUSC, STATUS
    MOVFF BSRC,BSR
    MOVFF TMR0LC, TMR0L
    RETFIE
    
    
   

;----- ALTA PRIORIDAD -----   
    
BACKUP_ALTA ;Hacemos la copia para cuando se interrumpe en alta prioridad
    MOVFF WREG, WREGC_ALTA
    MOVFF STATUS, STATUSC_ALTA
    MOVFF BSR, BSRC_ALTA
    MOVFF TMR0L, TMR0LC_ALTA
    
ASK1A
    BTFSS INTCON, INT0IF
    BRA ASK2 ;ESTA ES DE ALTA PRIORIDAD
    BCF INTCON, INT0IF
    
   
    BSF LED    
    MOVLW B'0101001' ;Carita feliz
    MOVWF PORTD,0
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY 
    CALL DELAY
    CALL DELAY
    CALL DELAY
    CALL DELAY
    BCF LED
    
 

SALIR_ALTA
    MOVFF WREGC_ALTA, WREG
    MOVFF STATUSC_ALTA, STATUS
    MOVFF BSRC_ALTA, BSR
    MOVFF TMR0LC_ALTA, TMR0L
    RETFIE

    

	
INICIO
    CLRF PORTB,0 ;Limpiamos PORTB, esto serán los botones de la interrupción
    CLRF PORTD,0 ;Limpiamos PORTD, esto será el display 7SEG
    CLRF PORTC,0 ;Limpiamos PORTC, esto será el LED de la interrupción baja
    
    SETF TRISB,0 ;Establecemos (hacemos 1) al PORTB, esto hace 1's los bits de PORTB, o sea una entrada
    CLRF TRISD,0 ;DISPLAY.... Limpiamos PORTD con TRISD, esto hace 0's los bits de PORTD, o sea una salida
    BCF TRISC,0,0 ;Limpiamos el bit 0 del PORTC con TRISC, esto hace 0 a ese bit de PORTC, o sea una salida
    BCF TRISC,1,0 ;Limpiamos el bit 1 del PORTC con TRISC, esto hace 0 a ese bit de PORTC, o sea una salida
    BCF TRISC,2,0 ;Limpiamos el bit 2 del PORTC con TRISC, esto hace 0 a ese bit de PORTC, o sea una salida
    
    BSF RCON, IPEN
    
    MOVLW .15
    MOVWF ADCON1,0
    
    MOVLW B'11010111'
    MOVWF T0CON, 0
    
    MOVLW B'11010000'
    MOVWF INTCON,0
    
    MOVLW B'11110101'
    MOVWF INTCON2,0
    
    MOVLW B'00011000'
    MOVWF INTCON3,0
    
    MOVLW B'00000000'
    MOVWF PORTB
    
HOLA 
    MOVLW B'01101110' ;Decodificación de la H en display de 7 seg
    MOVWF PORTD,0
    CALL DELAY 
     MOVLW B'00111111' ;Decodificación de la O en display de 7 seg 
    MOVWF PORTD,0
    CALL DELAY 
    MOVLW B'00100101' ;Decodificación de la L en display de 7 seg
    MOVWF PORTD,0
    CALL DELAY 
    MOVLW B'01111110' ;Decodificación de la A en display de 7 seg
    MOVWF PORTD,0
    CALL DELAY
    GOTO HOLA
   
DELAY
    CLRF TMR0L, 0
    MOVLW .60 ;255 . . . . ;ADDED:
    MOVWF TMR0L
    CLRF WREG
    
ASK 
    CPFSEQ TMR0L,0
    GOTO ASK
    RETURN 
    END
   