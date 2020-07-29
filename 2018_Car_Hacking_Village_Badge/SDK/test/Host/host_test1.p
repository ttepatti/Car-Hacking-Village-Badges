/******************************************************************************
 * Copyright 2015-2017 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * QCM Hosts test 1
 *
 *****************************************************************************/
new host_count = 0

@host_rx(data[], data_size)
{
    new i
    printf("Data Size: %d\r\nData:\r\n", data_size)
    
    for (i = 0; i < data_size; i++)
    {
        printf("%x ", data[i])
    }
    
    printf("\r\n")

    host_count += data_size

}

main()
{
    printf "Starting Host 1 Tests\n"

    while(host_count < 20)
    {
        sleep 100

    }

    printf ("Host test 1 complete\n")

}