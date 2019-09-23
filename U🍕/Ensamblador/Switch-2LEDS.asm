;FALCÓN CAMPOS JORGE ANTONIO, 2019. IPN.

    ;Programa que enciende un LED en RD5 si el SWITCH conectado en RA5 está cerrado, en caso contrario el LED se apaga.
    ;Agregar un Switch conectado en RA4 para controlar el encendido de un LED en RD4
    ;(2 SWITCHES, 2 LEDS, CADA LED TIENE SU PROPIO SWITCH)
    
    LIST P=18F4550
    #INCLUDE<P18F4550.INC>
    
    #DEFINE LED PORTD,5,0
    #DEFINE SWITCH PORTA, RA5,0
   
    
    ORG H'000'
    
    INICIO
	CLRF PORTA,0 ;Limpiamos el puerto A
	CLRF PORTD,0 ;Limpiamos el puerto D
	MOVLW H'30' ;Movemos el núm. 48 a W ...  B-10 = 110000 
	MOVWF TRISA,0 ;Movemos el núm. 32 de W a TRISA del puerto A. Esto hace una entrada al bit 4 y 5 del puerto A
	MOVLW H'0F' ;Movemos el núm. 15 a W
	MOVWF ADCON1,0 ;Pasamos el 15 de W a ADCON1, esto hace digital la entrada del bit 4 y 5 de A 
	MOVLW H'07' ;Movemos el núm. 7 a W
	MOVWF CMCON,0 ;Pasamos el núm. 7 de W a CMCON para apagar el comparador de voltajes
	BCF TRISD,RD5,0  ;Limpiamos el LED, el bit 5 del registro TRISD del puerto D 
	BCF TRISD,RD4,0  ;Limpiamos el LED, el bit 5 del registro TRISD del puerto D 
	
	

    MAIN
	BTFSS SWITCH ;Testea si el bit 5 del registro PORTA del puerto A tiene "algo" (si está encendido el SWITCH)
	GOTO NO ;Si no tiene "algo", está apagado, entonces salta a la subrutina NO 
	GOTO SI ;Si SWITCH tiene "algo", se está encendiendo, entonces va a la subrutina SI
	
	
	
     SI
	BSF LED ;Pone en 1 al LED, o sea el bit 5 del registro PORTD del puerto D
     GOTO S2 
     
     
     NO
	BCF LED ;Limpia el bit 5 del registro PORTD del puerto D
     GOTO S2
  
    
     S2 
	BTFSS PORTA,RA4,0 ;Testea si el bit 4 del registro PORTA del puerto A tiene "algo" (si está encendido el SWITCH)
     GOTO OFF ;Si no tiene "algo", está apagado, entonces salta a la subrutina OFF
     GOTO ON ;Si tiene "algo", se está encendiendo, entonces va a la subrutina ON
	
	
     ON 
	BSF PORTD,4,0 ;Pone en 1 al LED, o sea el bit 4 del registro PORTD del puerto D
     GOTO MAIN
   
	
     OFF 
	BCF PORTD,4,0 ;Limpia el bit 4 del registro PORTD del puerto D
     GOTO MAIN	
   
    
   
   END
	

	
	
	






