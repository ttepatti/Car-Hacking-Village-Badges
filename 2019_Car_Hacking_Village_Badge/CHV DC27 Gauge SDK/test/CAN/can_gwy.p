/******************************************************************************
 * Copyright 2014-2018 Specialized Solutions LLC
 *
 * Title to the Materials (contents of this file) remain with Specialized
 * Solutions LLC.  The Materials are copyrighted and are protected by United
 * States copyright laws.  Copyright notices cannot be removed from the
 * Materials.
 *
 * See the file titled "Specialized Solutions LLC License Agreement.txt"
 * that has been distributed with this file for further licensing details.
 *
 * QCM GWY CAN test #1 - test HSCAN1 gateways to HSCAN2 and vice-versa
 * requires a jumper and termination resistor between CAN channels.
 *
 *****************************************************************************/


new tx_msg[QCM_CAN_MSG]

@can0_rx_all(rx_msg[QCM_CAN_MSG])
{
	printf("CAN0 Received ID %x\n", rx_msg.id);
	rx_msg.id++
	qcm_can_tx(CAN0, rx_msg)
}


@can1_rx_all(rx_msg[QCM_CAN_MSG])
{
	printf("CAN1 Received ID %x\n", rx_msg.id);
	rx_msg.id++
	qcm_can_tx(CAN1, rx_msg)
}

main()
{
	
	sleep 1000
	
	printf "\nStarting CAN GWY Test 1\n"
    printf("Initialized\n")
    
	qcm_can_init(CAN0, 500000)
    qcm_can_init(CAN1, 500000)
	
	tx_msg.id = 0x222
	tx_msg.is_extended = false
	tx_msg.dlc = 8
	
	qcm_can_tx(CAN0, tx_msg)
}

