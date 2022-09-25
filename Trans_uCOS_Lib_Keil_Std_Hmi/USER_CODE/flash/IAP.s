;/***********************************************************************/
;/*  This file is part of the ARM Toolchain package                     */
;/*  Copyright KEIL ELEKTRONIK GmbH 2003 - 2008                         */
;/***********************************************************************/
;/*                                                                     */
;/*  IAP.S:  IAP Execution Function                                     */
;/*                                                                     */
;/***********************************************************************/

				PRESERVE8
                AREA    IAPEXE, CODE, READONLY


;void IAP_Execute (struct sIAP *pIAP);
                EXPORT  IAP_Execute		 

IAP_Execute     ;STMFD   SP, {R3, SP, LR}^      ; 保存用户状态的R3,SP,LR,注意不能回写
				                               ; 如果回写的是用户的SP，所以后面要调整SP	
			    STMFD   SP!,{LR}               ; Save Return Address
                ADD     R1,R0,#0x14            ; R0 = &IAP.cmd, R1 = &IAP.stat
                ADR     LR,IAP_Exit            ; Return Address
                LDR     R2,=0x7FFFFFF1         ; IAP Entry (Thumb Mode)
                BX      R2                     ; Execute IAP Command

IAP_Exit        ;LDMFD   SP, {R3, SP, LR}^      ; 恢复用户状态的R3,SP,LR,注意不能回写
                                               ; 如果回写的是用户的SP，所以后面要调整SP
                LDMFD   SP!,{LR}               ; Restore Return Address
               ; MOV     PC,LR                  ; Return
				BX 		LR

                END
