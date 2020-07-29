/******************************************************************************
 * Copyright 2014-2017 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * FLoating point tests
 *
 *****************************************************************************/
new Float:test

    
main()
{
    sleep 2000
    
    printf "Starting Float_1 Tests\n"

    test = 2.0123456789

    printf("%f\n", test)

    test = test / 2.1

    printf("%f\n", test)

}


