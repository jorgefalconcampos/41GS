;FALCÓN CAMPOS JORGE ANTONIO, 2019. IPN.

;Programa que enciende un LED en RD5 si el SWITCH conectado en RA5 está cerrado (cerrando circuito), en caso contrario el LED se apaga.
 
    LIST P=18F4550
    #INCLUDE<P18F4550.INC>
        
    #DEFINE LED PORTD,5,0  ;Definimos como "LED" al bit 5 del registro PORTD del puerto D
    #DEFINE SWITCH PORTA, RA5,0 ;Definimos como "SWITCH" al bit 5 del registro PORTA del puerto A
       
    ORG H'000' ;Origen en 0
    
    INICIO ;Comienzo de la subrutina principal
	CLRF PORTA,0 ;Limpiamos el puerto A
	CLRF PORTD,0 ;Limpiamos el puerto D
	MOVLW H'20'  ;Movemos el núm. 32 a W ...  B-10 = 100000 
	MOVWF TRISA,0 ;Movemos el núm. 32 de W a TRISA del puerto A. Esto hace una entrada al bit 5 del puerto A
		      ;Linea anterior equivale a: BSF TRISA,5,0 
	MOVLW H'0F' ;Movemos el núm. 15 a W
	MOVWF ADCON1,0 ;Pasamos el 15 de W a ADCON1, esto hace digital la entrada del bit 5 de A 
	MOVLW H'07' ;Movemos el núm. 7 a W
	MOVWF CMCON,0 ;Pasamos el núm. 7 de W a CMCON para apagar el comparador de voltajes
	BCF TRISD,RD5,0  ;Limpiamos el LED, el bit 5 del registro TRISD del puerto D 
	
    MAIN ;Comienzo de la subrutina principal
	BTFSS SWITCH ;Testea si el bit 5 del registro PORTA del puerto A tiene "algo" (si está encendido el SWITCH)
		     ;Linea anterior equivale a: BTFSS PORTA,RA5,0  
	GOTO NO ;Si no tiene "algo", está apagado, entonces salta a la subrutina NO       
	GOTO SI ;Si SWITCH tiene "algo", está encendido, entonces va a la subrutina SI
     SI
	BSF LED ;Pone en 1 al LED, o sea el bit 5 del registro PORTD del puerto D 
		;Linea anterior equivale a: BSF PORTD,RD5,0	
	GOTO MAIN ;Regresa a la subrutina principal 
     NO
	BCF LED ;Limpia el bit 5 del registro PORTD del puerto D
	GOTO MAIN ;Regresa a la subrutina principal
	  
   GOTO MAIN
   
   END