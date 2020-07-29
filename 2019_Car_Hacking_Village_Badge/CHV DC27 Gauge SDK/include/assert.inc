/******************************************************************************
 * Copyright 2014 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * @brief Test Harness Functions
 *
 *****************************************************************************/
#pragma library Assert

/*****************************************************************************
 * Data structure definitions 
 ****************************************************************************/

/*****************************************************************************
 * Tags (types) for use in calling the handlers 
 *****************************************************************************/

/********************************************************************************
 * Native handlers 
 *******************************************************************************/

/******************************************************************************
 * Forward declarations for event handlers 
 *****************************************************************************/

/********************************************************************************
 * Pawn Routines 
 *******************************************************************************/

stock test_assert(value1, value2, msg[], line = __line)
{
    if (value1 != value2)
    {
        printf("FAIL %d: %s - %d not equal to %d\n", line, msg, value1, value2)
        
        qcm_console_disable()
		
		exit
    }
}


