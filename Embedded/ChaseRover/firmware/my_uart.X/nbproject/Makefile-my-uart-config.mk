#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-my-uart-config.mk)" "nbproject/Makefile-local-my-uart-config.mk"
include nbproject/Makefile-local-my-uart-config.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=my-uart-config
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/my-uart-config/framework/driver/adc/src/drv_adc_static.c ../src/system_config/my-uart-config/framework/driver/oc/src/drv_oc_static.c ../src/system_config/my-uart-config/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/my-uart-config/framework/driver/usart/drv_usart_static.c ../src/system_config/my-uart-config/framework/system/clk/src/sys_clk_static.c ../src/system_config/my-uart-config/framework/system/ports/src/sys_ports_static.c ../src/system_config/my-uart-config/system_init.c ../src/system_config/my-uart-config/system_interrupt.c ../src/system_config/my-uart-config/system_exceptions.c ../src/system_config/my-uart-config/system_tasks.c ../src/system_config/my-uart-config/system_interrupt_a.S ../src/system_config/my-uart-config/rtos_hooks.c ../src/main.c ../src/debug.c ../src/coordinator.c ../src/coordinator_public.c ../src/coordinator_timer1.c ../src/monitor.c ../src/motor.c ../src/sensor.c ../src/sensor_public.c ../src/motor_public.c ../src/monitor_public.c ../src/message.c ../src/message_public.c ../src/sensor_timer1.c ../src/motor_timer.c ../../../../framework/osal/src/osal_freertos.c ../../../../framework/system/devcon/src/sys_devcon.c ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c ../../../../framework/system/int/src/sys_int_pic32.c ../../../../framework/system/ports/src/sys_ports.c ../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../third_party/rtos/FreeRTOS/Source/croutine.c ../../../../third_party/rtos/FreeRTOS/Source/list.c ../../../../third_party/rtos/FreeRTOS/Source/queue.c ../../../../third_party/rtos/FreeRTOS/Source/tasks.c ../../../../third_party/rtos/FreeRTOS/Source/timers.c ../../../../third_party/rtos/FreeRTOS/Source/event_groups.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1444944969/drv_adc_static.o ${OBJECTDIR}/_ext/479494361/drv_oc_static.o ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o ${OBJECTDIR}/_ext/840685753/drv_usart_static.o ${OBJECTDIR}/_ext/556318272/sys_clk_static.o ${OBJECTDIR}/_ext/553332464/sys_ports_static.o ${OBJECTDIR}/_ext/513330327/system_init.o ${OBJECTDIR}/_ext/513330327/system_interrupt.o ${OBJECTDIR}/_ext/513330327/system_exceptions.o ${OBJECTDIR}/_ext/513330327/system_tasks.o ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o ${OBJECTDIR}/_ext/513330327/rtos_hooks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/coordinator.o ${OBJECTDIR}/_ext/1360937237/coordinator_public.o ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o ${OBJECTDIR}/_ext/1360937237/monitor.o ${OBJECTDIR}/_ext/1360937237/motor.o ${OBJECTDIR}/_ext/1360937237/sensor.o ${OBJECTDIR}/_ext/1360937237/sensor_public.o ${OBJECTDIR}/_ext/1360937237/motor_public.o ${OBJECTDIR}/_ext/1360937237/monitor_public.o ${OBJECTDIR}/_ext/1360937237/message.o ${OBJECTDIR}/_ext/1360937237/message_public.o ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o ${OBJECTDIR}/_ext/1360937237/motor_timer.o ${OBJECTDIR}/_ext/24337685/osal_freertos.o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ${OBJECTDIR}/_ext/77319752/sys_ports.o ${OBJECTDIR}/_ext/1856876499/heap_1.o ${OBJECTDIR}/_ext/12131622/port.o ${OBJECTDIR}/_ext/12131622/port_asm.o ${OBJECTDIR}/_ext/1128951024/croutine.o ${OBJECTDIR}/_ext/1128951024/list.o ${OBJECTDIR}/_ext/1128951024/queue.o ${OBJECTDIR}/_ext/1128951024/tasks.o ${OBJECTDIR}/_ext/1128951024/timers.o ${OBJECTDIR}/_ext/1128951024/event_groups.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d ${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d ${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d ${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d ${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d ${OBJECTDIR}/_ext/513330327/system_init.o.d ${OBJECTDIR}/_ext/513330327/system_interrupt.o.d ${OBJECTDIR}/_ext/513330327/system_exceptions.o.d ${OBJECTDIR}/_ext/513330327/system_tasks.o.d ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d ${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/debug.o.d ${OBJECTDIR}/_ext/1360937237/coordinator.o.d ${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d ${OBJECTDIR}/_ext/1360937237/monitor.o.d ${OBJECTDIR}/_ext/1360937237/motor.o.d ${OBJECTDIR}/_ext/1360937237/sensor.o.d ${OBJECTDIR}/_ext/1360937237/sensor_public.o.d ${OBJECTDIR}/_ext/1360937237/motor_public.o.d ${OBJECTDIR}/_ext/1360937237/monitor_public.o.d ${OBJECTDIR}/_ext/1360937237/message.o.d ${OBJECTDIR}/_ext/1360937237/message_public.o.d ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d ${OBJECTDIR}/_ext/1360937237/motor_timer.o.d ${OBJECTDIR}/_ext/24337685/osal_freertos.o.d ${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d ${OBJECTDIR}/_ext/77319752/sys_ports.o.d ${OBJECTDIR}/_ext/1856876499/heap_1.o.d ${OBJECTDIR}/_ext/12131622/port.o.d ${OBJECTDIR}/_ext/12131622/port_asm.o.d ${OBJECTDIR}/_ext/1128951024/croutine.o.d ${OBJECTDIR}/_ext/1128951024/list.o.d ${OBJECTDIR}/_ext/1128951024/queue.o.d ${OBJECTDIR}/_ext/1128951024/tasks.o.d ${OBJECTDIR}/_ext/1128951024/timers.o.d ${OBJECTDIR}/_ext/1128951024/event_groups.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1444944969/drv_adc_static.o ${OBJECTDIR}/_ext/479494361/drv_oc_static.o ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o ${OBJECTDIR}/_ext/840685753/drv_usart_static.o ${OBJECTDIR}/_ext/556318272/sys_clk_static.o ${OBJECTDIR}/_ext/553332464/sys_ports_static.o ${OBJECTDIR}/_ext/513330327/system_init.o ${OBJECTDIR}/_ext/513330327/system_interrupt.o ${OBJECTDIR}/_ext/513330327/system_exceptions.o ${OBJECTDIR}/_ext/513330327/system_tasks.o ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o ${OBJECTDIR}/_ext/513330327/rtos_hooks.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/debug.o ${OBJECTDIR}/_ext/1360937237/coordinator.o ${OBJECTDIR}/_ext/1360937237/coordinator_public.o ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o ${OBJECTDIR}/_ext/1360937237/monitor.o ${OBJECTDIR}/_ext/1360937237/motor.o ${OBJECTDIR}/_ext/1360937237/sensor.o ${OBJECTDIR}/_ext/1360937237/sensor_public.o ${OBJECTDIR}/_ext/1360937237/motor_public.o ${OBJECTDIR}/_ext/1360937237/monitor_public.o ${OBJECTDIR}/_ext/1360937237/message.o ${OBJECTDIR}/_ext/1360937237/message_public.o ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o ${OBJECTDIR}/_ext/1360937237/motor_timer.o ${OBJECTDIR}/_ext/24337685/osal_freertos.o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ${OBJECTDIR}/_ext/77319752/sys_ports.o ${OBJECTDIR}/_ext/1856876499/heap_1.o ${OBJECTDIR}/_ext/12131622/port.o ${OBJECTDIR}/_ext/12131622/port_asm.o ${OBJECTDIR}/_ext/1128951024/croutine.o ${OBJECTDIR}/_ext/1128951024/list.o ${OBJECTDIR}/_ext/1128951024/queue.o ${OBJECTDIR}/_ext/1128951024/tasks.o ${OBJECTDIR}/_ext/1128951024/timers.o ${OBJECTDIR}/_ext/1128951024/event_groups.o

# Source Files
SOURCEFILES=../src/system_config/my-uart-config/framework/driver/adc/src/drv_adc_static.c ../src/system_config/my-uart-config/framework/driver/oc/src/drv_oc_static.c ../src/system_config/my-uart-config/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/my-uart-config/framework/driver/usart/drv_usart_static.c ../src/system_config/my-uart-config/framework/system/clk/src/sys_clk_static.c ../src/system_config/my-uart-config/framework/system/ports/src/sys_ports_static.c ../src/system_config/my-uart-config/system_init.c ../src/system_config/my-uart-config/system_interrupt.c ../src/system_config/my-uart-config/system_exceptions.c ../src/system_config/my-uart-config/system_tasks.c ../src/system_config/my-uart-config/system_interrupt_a.S ../src/system_config/my-uart-config/rtos_hooks.c ../src/main.c ../src/debug.c ../src/coordinator.c ../src/coordinator_public.c ../src/coordinator_timer1.c ../src/monitor.c ../src/motor.c ../src/sensor.c ../src/sensor_public.c ../src/motor_public.c ../src/monitor_public.c ../src/message.c ../src/message_public.c ../src/sensor_timer1.c ../src/motor_timer.c ../../../../framework/osal/src/osal_freertos.c ../../../../framework/system/devcon/src/sys_devcon.c ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c ../../../../framework/system/int/src/sys_int_pic32.c ../../../../framework/system/ports/src/sys_ports.c ../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S ../../../../third_party/rtos/FreeRTOS/Source/croutine.c ../../../../third_party/rtos/FreeRTOS/Source/list.c ../../../../third_party/rtos/FreeRTOS/Source/queue.c ../../../../third_party/rtos/FreeRTOS/Source/tasks.c ../../../../third_party/rtos/FreeRTOS/Source/timers.c ../../../../third_party/rtos/FreeRTOS/Source/event_groups.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-my-uart-config.mk dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/513330327/system_interrupt_a.o: ../src/system_config/my-uart-config/system_interrupt_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.ok ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d" "${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -I"../src/system_config/my-uart-config" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d"  -o ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o ../src/system_config/my-uart-config/system_interrupt_a.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
${OBJECTDIR}/_ext/12131622/port_asm.o: ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/12131622" 
	@${RM} ${OBJECTDIR}/_ext/12131622/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/12131622/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/12131622/port_asm.o.ok ${OBJECTDIR}/_ext/12131622/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/12131622/port_asm.o.d" "${OBJECTDIR}/_ext/12131622/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -I"../src/system_config/my-uart-config" -MMD -MF "${OBJECTDIR}/_ext/12131622/port_asm.o.d"  -o ${OBJECTDIR}/_ext/12131622/port_asm.o ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/12131622/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/_ext/513330327/system_interrupt_a.o: ../src/system_config/my-uart-config/system_interrupt_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.ok ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d" "${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -I"../src/system_config/my-uart-config" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.d"  -o ${OBJECTDIR}/_ext/513330327/system_interrupt_a.o ../src/system_config/my-uart-config/system_interrupt_a.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/513330327/system_interrupt_a.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/12131622/port_asm.o: ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/12131622" 
	@${RM} ${OBJECTDIR}/_ext/12131622/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/12131622/port_asm.o 
	@${RM} ${OBJECTDIR}/_ext/12131622/port_asm.o.ok ${OBJECTDIR}/_ext/12131622/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/12131622/port_asm.o.d" "${OBJECTDIR}/_ext/12131622/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -I"../src/system_config/my-uart-config" -MMD -MF "${OBJECTDIR}/_ext/12131622/port_asm.o.d"  -o ${OBJECTDIR}/_ext/12131622/port_asm.o ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/12131622/port_asm.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1444944969/drv_adc_static.o: ../src/system_config/my-uart-config/framework/driver/adc/src/drv_adc_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1444944969" 
	@${RM} ${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1444944969/drv_adc_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d" -o ${OBJECTDIR}/_ext/1444944969/drv_adc_static.o ../src/system_config/my-uart-config/framework/driver/adc/src/drv_adc_static.c     
	
${OBJECTDIR}/_ext/479494361/drv_oc_static.o: ../src/system_config/my-uart-config/framework/driver/oc/src/drv_oc_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/479494361" 
	@${RM} ${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/479494361/drv_oc_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d" -o ${OBJECTDIR}/_ext/479494361/drv_oc_static.o ../src/system_config/my-uart-config/framework/driver/oc/src/drv_oc_static.c     
	
${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o: ../src/system_config/my-uart-config/framework/driver/tmr/src/drv_tmr_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1490729040" 
	@${RM} ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o ../src/system_config/my-uart-config/framework/driver/tmr/src/drv_tmr_static.c     
	
${OBJECTDIR}/_ext/840685753/drv_usart_static.o: ../src/system_config/my-uart-config/framework/driver/usart/drv_usart_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/840685753" 
	@${RM} ${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/840685753/drv_usart_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/840685753/drv_usart_static.o ../src/system_config/my-uart-config/framework/driver/usart/drv_usart_static.c     
	
${OBJECTDIR}/_ext/556318272/sys_clk_static.o: ../src/system_config/my-uart-config/framework/system/clk/src/sys_clk_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/556318272" 
	@${RM} ${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/556318272/sys_clk_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d" -o ${OBJECTDIR}/_ext/556318272/sys_clk_static.o ../src/system_config/my-uart-config/framework/system/clk/src/sys_clk_static.c     
	
${OBJECTDIR}/_ext/553332464/sys_ports_static.o: ../src/system_config/my-uart-config/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/553332464" 
	@${RM} ${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/553332464/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/553332464/sys_ports_static.o ../src/system_config/my-uart-config/framework/system/ports/src/sys_ports_static.c     
	
${OBJECTDIR}/_ext/513330327/system_init.o: ../src/system_config/my-uart-config/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_init.o.d" -o ${OBJECTDIR}/_ext/513330327/system_init.o ../src/system_config/my-uart-config/system_init.c     
	
${OBJECTDIR}/_ext/513330327/system_interrupt.o: ../src/system_config/my-uart-config/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/513330327/system_interrupt.o ../src/system_config/my-uart-config/system_interrupt.c     
	
${OBJECTDIR}/_ext/513330327/system_exceptions.o: ../src/system_config/my-uart-config/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/513330327/system_exceptions.o ../src/system_config/my-uart-config/system_exceptions.c     
	
${OBJECTDIR}/_ext/513330327/system_tasks.o: ../src/system_config/my-uart-config/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_tasks.o.d" -o ${OBJECTDIR}/_ext/513330327/system_tasks.o ../src/system_config/my-uart-config/system_tasks.c     
	
${OBJECTDIR}/_ext/513330327/rtos_hooks.o: ../src/system_config/my-uart-config/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/513330327/rtos_hooks.o ../src/system_config/my-uart-config/rtos_hooks.c     
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c     
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c     
	
${OBJECTDIR}/_ext/1360937237/coordinator.o: ../src/coordinator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/coordinator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/coordinator.o.d" -o ${OBJECTDIR}/_ext/1360937237/coordinator.o ../src/coordinator.c     
	
${OBJECTDIR}/_ext/1360937237/coordinator_public.o: ../src/coordinator_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/coordinator_public.o ../src/coordinator_public.c     
	
${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o: ../src/coordinator_timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d" -o ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o ../src/coordinator_timer1.c     
	
${OBJECTDIR}/_ext/1360937237/monitor.o: ../src/monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/monitor.o.d" -o ${OBJECTDIR}/_ext/1360937237/monitor.o ../src/monitor.c     
	
${OBJECTDIR}/_ext/1360937237/motor.o: ../src/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/motor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/motor.o.d" -o ${OBJECTDIR}/_ext/1360937237/motor.o ../src/motor.c     
	
${OBJECTDIR}/_ext/1360937237/sensor.o: ../src/sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sensor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor.o ../src/sensor.c     
	
${OBJECTDIR}/_ext/1360937237/sensor_public.o: ../src/sensor_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sensor_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor_public.o ../src/sensor_public.c     
	
${OBJECTDIR}/_ext/1360937237/motor_public.o: ../src/motor_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/motor_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/motor_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/motor_public.o ../src/motor_public.c     
	
${OBJECTDIR}/_ext/1360937237/monitor_public.o: ../src/monitor_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/monitor_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/monitor_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/monitor_public.o ../src/monitor_public.c     
	
${OBJECTDIR}/_ext/1360937237/message.o: ../src/message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/message.o.d" -o ${OBJECTDIR}/_ext/1360937237/message.o ../src/message.c     
	
${OBJECTDIR}/_ext/1360937237/message_public.o: ../src/message_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/message_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/message_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/message_public.o ../src/message_public.c     
	
${OBJECTDIR}/_ext/1360937237/sensor_timer1.o: ../src/sensor_timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o ../src/sensor_timer1.c     
	
${OBJECTDIR}/_ext/1360937237/motor_timer.o: ../src/motor_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/motor_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/motor_timer.o.d" -o ${OBJECTDIR}/_ext/1360937237/motor_timer.o ../src/motor_timer.c     
	
${OBJECTDIR}/_ext/24337685/osal_freertos.o: ../../../../framework/osal/src/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/24337685" 
	@${RM} ${OBJECTDIR}/_ext/24337685/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/24337685/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/24337685/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/24337685/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/24337685/osal_freertos.o ../../../../framework/osal/src/osal_freertos.c     
	
${OBJECTDIR}/_ext/1271179505/sys_devcon.o: ../../../../framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ../../../../framework/system/devcon/src/sys_devcon.c     
	
${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o: ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c     
	
${OBJECTDIR}/_ext/122796885/sys_int_pic32.o: ../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/122796885" 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ../../../../framework/system/int/src/sys_int_pic32.c     
	
${OBJECTDIR}/_ext/77319752/sys_ports.o: ../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/77319752" 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" -o ${OBJECTDIR}/_ext/77319752/sys_ports.o ../../../../framework/system/ports/src/sys_ports.c     
	
${OBJECTDIR}/_ext/1856876499/heap_1.o: ../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1856876499" 
	@${RM} ${OBJECTDIR}/_ext/1856876499/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1856876499/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1856876499/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1856876499/heap_1.o.d" -o ${OBJECTDIR}/_ext/1856876499/heap_1.o ../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c     
	
${OBJECTDIR}/_ext/12131622/port.o: ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/12131622" 
	@${RM} ${OBJECTDIR}/_ext/12131622/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/12131622/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/12131622/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/12131622/port.o.d" -o ${OBJECTDIR}/_ext/12131622/port.o ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c     
	
${OBJECTDIR}/_ext/1128951024/croutine.o: ../../../../third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/croutine.o.d" -o ${OBJECTDIR}/_ext/1128951024/croutine.o ../../../../third_party/rtos/FreeRTOS/Source/croutine.c     
	
${OBJECTDIR}/_ext/1128951024/list.o: ../../../../third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/list.o.d" -o ${OBJECTDIR}/_ext/1128951024/list.o ../../../../third_party/rtos/FreeRTOS/Source/list.c     
	
${OBJECTDIR}/_ext/1128951024/queue.o: ../../../../third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/queue.o.d" -o ${OBJECTDIR}/_ext/1128951024/queue.o ../../../../third_party/rtos/FreeRTOS/Source/queue.c     
	
${OBJECTDIR}/_ext/1128951024/tasks.o: ../../../../third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/tasks.o.d" -o ${OBJECTDIR}/_ext/1128951024/tasks.o ../../../../third_party/rtos/FreeRTOS/Source/tasks.c     
	
${OBJECTDIR}/_ext/1128951024/timers.o: ../../../../third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/timers.o.d" -o ${OBJECTDIR}/_ext/1128951024/timers.o ../../../../third_party/rtos/FreeRTOS/Source/timers.c     
	
${OBJECTDIR}/_ext/1128951024/event_groups.o: ../../../../third_party/rtos/FreeRTOS/Source/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/event_groups.o.d" -o ${OBJECTDIR}/_ext/1128951024/event_groups.o ../../../../third_party/rtos/FreeRTOS/Source/event_groups.c     
	
else
${OBJECTDIR}/_ext/1444944969/drv_adc_static.o: ../src/system_config/my-uart-config/framework/driver/adc/src/drv_adc_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1444944969" 
	@${RM} ${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1444944969/drv_adc_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1444944969/drv_adc_static.o.d" -o ${OBJECTDIR}/_ext/1444944969/drv_adc_static.o ../src/system_config/my-uart-config/framework/driver/adc/src/drv_adc_static.c     
	
${OBJECTDIR}/_ext/479494361/drv_oc_static.o: ../src/system_config/my-uart-config/framework/driver/oc/src/drv_oc_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/479494361" 
	@${RM} ${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/479494361/drv_oc_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/479494361/drv_oc_static.o.d" -o ${OBJECTDIR}/_ext/479494361/drv_oc_static.o ../src/system_config/my-uart-config/framework/driver/oc/src/drv_oc_static.c     
	
${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o: ../src/system_config/my-uart-config/framework/driver/tmr/src/drv_tmr_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1490729040" 
	@${RM} ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1490729040/drv_tmr_static.o ../src/system_config/my-uart-config/framework/driver/tmr/src/drv_tmr_static.c     
	
${OBJECTDIR}/_ext/840685753/drv_usart_static.o: ../src/system_config/my-uart-config/framework/driver/usart/drv_usart_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/840685753" 
	@${RM} ${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/840685753/drv_usart_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/840685753/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/840685753/drv_usart_static.o ../src/system_config/my-uart-config/framework/driver/usart/drv_usart_static.c     
	
${OBJECTDIR}/_ext/556318272/sys_clk_static.o: ../src/system_config/my-uart-config/framework/system/clk/src/sys_clk_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/556318272" 
	@${RM} ${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/556318272/sys_clk_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/556318272/sys_clk_static.o.d" -o ${OBJECTDIR}/_ext/556318272/sys_clk_static.o ../src/system_config/my-uart-config/framework/system/clk/src/sys_clk_static.c     
	
${OBJECTDIR}/_ext/553332464/sys_ports_static.o: ../src/system_config/my-uart-config/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/553332464" 
	@${RM} ${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/553332464/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/553332464/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/553332464/sys_ports_static.o ../src/system_config/my-uart-config/framework/system/ports/src/sys_ports_static.c     
	
${OBJECTDIR}/_ext/513330327/system_init.o: ../src/system_config/my-uart-config/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_init.o.d" -o ${OBJECTDIR}/_ext/513330327/system_init.o ../src/system_config/my-uart-config/system_init.c     
	
${OBJECTDIR}/_ext/513330327/system_interrupt.o: ../src/system_config/my-uart-config/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/513330327/system_interrupt.o ../src/system_config/my-uart-config/system_interrupt.c     
	
${OBJECTDIR}/_ext/513330327/system_exceptions.o: ../src/system_config/my-uart-config/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/513330327/system_exceptions.o ../src/system_config/my-uart-config/system_exceptions.c     
	
${OBJECTDIR}/_ext/513330327/system_tasks.o: ../src/system_config/my-uart-config/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/system_tasks.o.d" -o ${OBJECTDIR}/_ext/513330327/system_tasks.o ../src/system_config/my-uart-config/system_tasks.c     
	
${OBJECTDIR}/_ext/513330327/rtos_hooks.o: ../src/system_config/my-uart-config/rtos_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513330327" 
	@${RM} ${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/513330327/rtos_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/513330327/rtos_hooks.o.d" -o ${OBJECTDIR}/_ext/513330327/rtos_hooks.o ../src/system_config/my-uart-config/rtos_hooks.c     
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c     
	
${OBJECTDIR}/_ext/1360937237/debug.o: ../src/debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/debug.o.d" -o ${OBJECTDIR}/_ext/1360937237/debug.o ../src/debug.c     
	
${OBJECTDIR}/_ext/1360937237/coordinator.o: ../src/coordinator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/coordinator.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/coordinator.o.d" -o ${OBJECTDIR}/_ext/1360937237/coordinator.o ../src/coordinator.c     
	
${OBJECTDIR}/_ext/1360937237/coordinator_public.o: ../src/coordinator_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/coordinator_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/coordinator_public.o ../src/coordinator_public.c     
	
${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o: ../src/coordinator_timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o.d" -o ${OBJECTDIR}/_ext/1360937237/coordinator_timer1.o ../src/coordinator_timer1.c     
	
${OBJECTDIR}/_ext/1360937237/monitor.o: ../src/monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/monitor.o.d" -o ${OBJECTDIR}/_ext/1360937237/monitor.o ../src/monitor.c     
	
${OBJECTDIR}/_ext/1360937237/motor.o: ../src/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/motor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/motor.o.d" -o ${OBJECTDIR}/_ext/1360937237/motor.o ../src/motor.c     
	
${OBJECTDIR}/_ext/1360937237/sensor.o: ../src/sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sensor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor.o ../src/sensor.c     
	
${OBJECTDIR}/_ext/1360937237/sensor_public.o: ../src/sensor_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sensor_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor_public.o ../src/sensor_public.c     
	
${OBJECTDIR}/_ext/1360937237/motor_public.o: ../src/motor_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/motor_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/motor_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/motor_public.o ../src/motor_public.c     
	
${OBJECTDIR}/_ext/1360937237/monitor_public.o: ../src/monitor_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/monitor_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/monitor_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/monitor_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/monitor_public.o ../src/monitor_public.c     
	
${OBJECTDIR}/_ext/1360937237/message.o: ../src/message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/message.o.d" -o ${OBJECTDIR}/_ext/1360937237/message.o ../src/message.c     
	
${OBJECTDIR}/_ext/1360937237/message_public.o: ../src/message_public.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_public.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/message_public.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/message_public.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/message_public.o.d" -o ${OBJECTDIR}/_ext/1360937237/message_public.o ../src/message_public.c     
	
${OBJECTDIR}/_ext/1360937237/sensor_timer1.o: ../src/sensor_timer1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/sensor_timer1.o.d" -o ${OBJECTDIR}/_ext/1360937237/sensor_timer1.o ../src/sensor_timer1.c     
	
${OBJECTDIR}/_ext/1360937237/motor_timer.o: ../src/motor_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/motor_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/motor_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/motor_timer.o.d" -o ${OBJECTDIR}/_ext/1360937237/motor_timer.o ../src/motor_timer.c     
	
${OBJECTDIR}/_ext/24337685/osal_freertos.o: ../../../../framework/osal/src/osal_freertos.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/24337685" 
	@${RM} ${OBJECTDIR}/_ext/24337685/osal_freertos.o.d 
	@${RM} ${OBJECTDIR}/_ext/24337685/osal_freertos.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/24337685/osal_freertos.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/24337685/osal_freertos.o.d" -o ${OBJECTDIR}/_ext/24337685/osal_freertos.o ../../../../framework/osal/src/osal_freertos.c     
	
${OBJECTDIR}/_ext/1271179505/sys_devcon.o: ../../../../framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon.o ../../../../framework/system/devcon/src/sys_devcon.c     
	
${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o: ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1271179505" 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1271179505/sys_devcon_pic32mx.o ../../../../framework/system/devcon/src/sys_devcon_pic32mx.c     
	
${OBJECTDIR}/_ext/122796885/sys_int_pic32.o: ../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/122796885" 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/122796885/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/122796885/sys_int_pic32.o ../../../../framework/system/int/src/sys_int_pic32.c     
	
${OBJECTDIR}/_ext/77319752/sys_ports.o: ../../../../framework/system/ports/src/sys_ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/77319752" 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/77319752/sys_ports.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/77319752/sys_ports.o.d" -o ${OBJECTDIR}/_ext/77319752/sys_ports.o ../../../../framework/system/ports/src/sys_ports.c     
	
${OBJECTDIR}/_ext/1856876499/heap_1.o: ../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1856876499" 
	@${RM} ${OBJECTDIR}/_ext/1856876499/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1856876499/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1856876499/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1856876499/heap_1.o.d" -o ${OBJECTDIR}/_ext/1856876499/heap_1.o ../../../../third_party/rtos/FreeRTOS/Source/portable/MemMang/heap_1.c     
	
${OBJECTDIR}/_ext/12131622/port.o: ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/12131622" 
	@${RM} ${OBJECTDIR}/_ext/12131622/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/12131622/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/12131622/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/12131622/port.o.d" -o ${OBJECTDIR}/_ext/12131622/port.o ../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c     
	
${OBJECTDIR}/_ext/1128951024/croutine.o: ../../../../third_party/rtos/FreeRTOS/Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/croutine.o.d" -o ${OBJECTDIR}/_ext/1128951024/croutine.o ../../../../third_party/rtos/FreeRTOS/Source/croutine.c     
	
${OBJECTDIR}/_ext/1128951024/list.o: ../../../../third_party/rtos/FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/list.o.d" -o ${OBJECTDIR}/_ext/1128951024/list.o ../../../../third_party/rtos/FreeRTOS/Source/list.c     
	
${OBJECTDIR}/_ext/1128951024/queue.o: ../../../../third_party/rtos/FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/queue.o.d" -o ${OBJECTDIR}/_ext/1128951024/queue.o ../../../../third_party/rtos/FreeRTOS/Source/queue.c     
	
${OBJECTDIR}/_ext/1128951024/tasks.o: ../../../../third_party/rtos/FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/tasks.o.d" -o ${OBJECTDIR}/_ext/1128951024/tasks.o ../../../../third_party/rtos/FreeRTOS/Source/tasks.c     
	
${OBJECTDIR}/_ext/1128951024/timers.o: ../../../../third_party/rtos/FreeRTOS/Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/timers.o.d" -o ${OBJECTDIR}/_ext/1128951024/timers.o ../../../../third_party/rtos/FreeRTOS/Source/timers.c     
	
${OBJECTDIR}/_ext/1128951024/event_groups.o: ../../../../third_party/rtos/FreeRTOS/Source/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1128951024" 
	@${RM} ${OBJECTDIR}/_ext/1128951024/event_groups.o.d 
	@${RM} ${OBJECTDIR}/_ext/1128951024/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1128951024/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -D__XC -I"../src" -I"../../../../framework" -I"../src/system_config/my-uart-config/framework" -I"../src/my-uart-config" -I"../src/system_config/my-uart-config" -I"../../../../third_party/rtos/FreeRTOS/Source/portable/MPLAB/PIC32MX" -I"../../../../third_party/rtos/FreeRTOS/Source/include" -MMD -MF "${OBJECTDIR}/_ext/1128951024/event_groups.o.d" -o ${OBJECTDIR}/_ext/1128951024/event_groups.o ../../../../third_party/rtos/FreeRTOS/Source/event_groups.c     
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a          -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a        -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/my_uart.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/my-uart-config
	${RM} -r dist/my-uart-config

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
