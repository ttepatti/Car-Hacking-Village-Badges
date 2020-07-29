/******************************************************************************
 * Copyright 2014-2016 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * QCM Timer tests
 *
 *****************************************************************************/
new counter = 0
new counter2 = 0

timer_notice(timer)
{
    printf("T%d expired at %d\n", timer, qcm_get_system_time())
}


@timer0()
{
    timer_notice(0);
}

@timer1()
{
    timer_notice(1);
}

@timer2()
{
    timer_notice(2);
}

@timer3()
{
    timer_notice(3);
}

@timer4()
{
    timer_notice(4);
}

@timer5()
{
    timer_notice(5);
}

@timer6()
{
    timer_notice(6);
}

@timer7()
{
    timer_notice(7);
	counter2++

	if (counter2 < 3)
	{
    	qcm_timer_start(8, 500, true)
	}
	else
	{
		printf("All done.\n")
	}


}

@timer8()
{
    timer_notice(8);

	counter++;

	if (counter > 10)
	{
		qcm_timer_stop(8);
		qcm_timer_start(7,2250,false)
	}

}

main()
{
    sleep 1000
	
	printf "Starting Timer Tests\n"

    qcm_timer_start(0,250,false)
    qcm_timer_start(1,500,false)
    qcm_timer_start(2,750,false)
    qcm_timer_start(3,1000,false)
    qcm_timer_start(4,1250,false)
    qcm_timer_start(5,1500,false)
    qcm_timer_start(6,2000,false)
    qcm_timer_start(7,2250,false)

    /* Timer 8 is started by the expiration of timer 7 */

    qcm_timer_start(9,2500,false)

	while (false == qcm_timer_expired(9))
	{
		sleep
	}

	timer_notice(9)

}


