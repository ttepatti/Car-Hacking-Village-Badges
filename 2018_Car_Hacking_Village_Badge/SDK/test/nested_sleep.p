/******************************************************************************
 * Copyright 2017 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * Nested sleep testing - sleeping multiple times in main and
 * idle functions should function correctly.
 *
 * Note that because PAWN is stack based, and is a 
 * cooperative multi-tasking system, events may not fire 
 * at expected times.  For example, if timer 1 fires, then immediately
 * afterwards timer 2 fires, the timer 2 handler will run to completetion 
 * before coming back to the timer 1 handler.  Therefore, the sleep duration
 * for timer 1 will be closer to 90 milliseconds instead of 50.  This can be seen
 * by running this test.
 *
 * Also note that it is very easy to blow the stack for the internal task running
 * the PAWN interpreter.  At each sleep, a new frame will be pushed onto the 
 * task stack.  For very short delays (or "stacking" up multiple events with sleep)
 * a reset can be encountered.
 *
 *****************************************************************************/
new start_time

get_current_time()
{
	return qcm_get_system_time() - start_time
}
@timer0()
{
	printf("\tT0: %d\n", get_current_time())
	
	sleep 75
	
	printf("\tT0S: %d\n", get_current_time())
}

@timer1()
{
	printf("\t\t\tT1: %d\n", get_current_time())
	
	sleep 50
	
	printf("\t\t\tT1S: %d\n", get_current_time())
}

@timer2()
{
	printf("\t\t\t\tT2: %d\n", get_current_time())
	
	sleep 90
	
	printf("\t\t\t\tT2S: %d\n", get_current_time())
}

main()
{
	sleep 2000
	
	printf("\nTest Start\n\n")
	
	start_time = qcm_get_system_time()
	
	qcm_timer_start(TIMER_0, 200, true)
	qcm_timer_start(TIMER_1, 300, true)
	qcm_timer_start(TIMER_2, 400, true)
	
	sleep 301
	printf("M1: %d\n", get_current_time())
	sleep 301
	printf("M2: %d\n", get_current_time())
	sleep 301
	printf("M3: %d\n", get_current_time())
	sleep 301
	printf("M4: %d\n", get_current_time())
	sleep 301
	printf("M5: %d\n", get_current_time())
	
	while (get_current_time() < 6000)
	{
		sleep 1000
	}
	
	qcm_timer_stop(TIMER_0)
	qcm_timer_stop(TIMER_1)
	qcm_timer_stop(TIMER_2)
	
	printf("Test complete\n")
}
