/*
 * drive_function.c
 *
 *  Created on: Jul 26, 2013
 *      Author: pkanajar
 */
#include "drive_function.h"
#include <stdio.h>
#include <math.h>

int check_ready(int status_word) {
	return (status_word & READY_TO_SWITCH_ON_STATE);
}

int check_switch_enable(int status_word) {
	return (~((status_word & SWITCH_ON_DISABLED_STATE) >> 6) & 0x1);
}

int check_switch_on(int status_word) {
	return (status_word & SWITCHED_ON_STATE) >> 1;
}

int check_op_enable(int status_word) {
	return (status_word & OPERATION_ENABLED_STATE) >> 2;
}

int check_quick_stop_active(int status_word){
	return (status_word & QUICK_STOP_STATE)>>5;
}

int check_target_reached(int status_word)
{
	return (status_word & TARGET_REACHED)>>10;
}

int check_quick_stop_inactive(int status_word)
{
	return (status_word & QUICK_STOP_STATE)>>5;
}

int check_shutdown_active(int status_word)
{
	return (status_word & VOLTAGE_ENABLED_STATE)>>4;
}

void set_velocity(int target_velocity, int slave_number, ctrlproto_slv_handle *slv_handles)
{
	slv_handles[slave_number].speed_setpoint = target_velocity;
}

int get_velocity_actual(int slave_number, ctrlproto_slv_handle *slv_handles)
{
	return slv_handles[slave_number].speed_in;
}

float get_position_actual_deg(int slave_number, ctrlproto_slv_handle *slv_handles)
{
	return ((float)slv_handles[slave_number].position_in )/10000.0f;
}

void set_position_deg(int target_position, int slave_number, ctrlproto_slv_handle *slv_handles)
{
	slv_handles[slave_number].position_setpoint = target_position;
}

void set_profile_position_deg(float target_position, int slave_number, ctrlproto_slv_handle *slv_handles)
{
	//int ack = 1;
	slv_handles[slave_number].position_setpoint = (int) round( (target_position*10000.0f) );
}

int position_set_flag(int slave_number, ctrlproto_slv_handle *slv_handles)
{
	int flag = check_target_reached(read_statusword(slave_number, slv_handles));
	if(flag == 0)
		return 1;
	else
		return 0;
}

int velocity_set_flag(int slave_number, ctrlproto_slv_handle *slv_handles)
{
	int flag = check_target_reached(read_statusword(slave_number, slv_handles));
	if(flag == 0)
		return 1;
	else
		return 0;
}

void set_controlword(int controlword, int slave_number, ctrlproto_slv_handle *slv_handles)
{
	slv_handles[slave_number].motorctrl_out = controlword;
}

int read_statusword(int slave_number, ctrlproto_slv_handle *slv_handles)
{
	return slv_handles[slave_number].motorctrl_status_in;
}

int init_position_profile_params(float target_position, float actual_position, int velocity, int acceleration, int deceleration)
{
	int target = (int) (target_position * 10000.0f);
	int actual = (int) (actual_position * 10000.0f);
	init_position_profile(target, actual,	velocity, acceleration, deceleration);
}

int target_position_reached(int slave_number, float target_position, float tolerance, ctrlproto_slv_handle *slv_handles)
{
	float actual_position =  get_position_actual_deg(slave_number, slv_handles);
//	printf("\n act pos %f", actual_position);
	if(actual_position > target_position-tolerance/2.0f && actual_position < target_position + tolerance/2.0f)
	{	if(check_target_reached(read_statusword(slave_number, slv_handles)))
		{
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int target_velocity_reached(int slave_number, int target_velocity, int tolerance, ctrlproto_slv_handle *slv_handles)
{
	int actual_velocity =  get_velocity_actual(slave_number, slv_handles);
//	printf("\n act vel %d min %d max %d \n", actual_velocity , target_velocity-tolerance/2,  target_velocity + tolerance/2);
	if(actual_velocity > target_velocity-tolerance/2 && actual_velocity < target_velocity + tolerance/2)
	{	if(check_target_reached(read_statusword(slave_number, slv_handles)))
		{
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

int set_operation_mode(int operation_mode, int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	int ready = 0;
	int switch_enable = 0;
	int status_word = 0;
	int switch_on_state = 0;
	int op_enable_state = 0;


	set_controlword(0, slave_number, slv_handles);
	printf("updating motor parameters\n");
	fflush(stdout);
	/***** Set up Parameters *****/
	while(1)
	{
		if(slv_handles[slave_number].motor_config_param.update_flag == 1)
		{
			slv_handles[slave_number].motor_config_param.update_flag = 0;	// reset to update next set of paramaters
			break;
		}

		else
		{
			sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, MOTOR_PARAM_UPDATE, slave_number);
			printf (".");
			fflush(stdout);

		}
	}
	printf ("\n");
	fflush(stdout);
	set_controlword(SHUTDOWN, slave_number, slv_handles);//*/

	/**********************check ready***********************/
	while(!ready)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			//check ready
			status_word = read_statusword(slave_number, slv_handles);
			ready = check_ready(status_word);
		}
		else
			continue;
	}

	#ifndef print_slave
	printf("ready\n");
	fflush(stdout);
	#endif

	/**********************check switch_enable***********************/
	while(!switch_enable)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			//check switch
			status_word = read_statusword(slave_number, slv_handles);
			switch_enable = check_switch_enable(status_word);
		}
		else
			continue;
	}

	#ifndef print_slave
	printf("switch_enable\n");
	fflush(stdout);
	#endif


	/************************output switch on**************************/
	while(!switch_on_state)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			set_controlword(SWITCH_ON_CONTROL, slave_number, slv_handles);
			/*************check switch_on_state***************/
			status_word = read_statusword(slave_number, slv_handles);
			switch_on_state = check_switch_on(status_word);
		}
		else
			continue;
	}

	#ifndef print_slave
	printf("switch_on_state\n");
	fflush(stdout);
	#endif


	printf("updating control parameters\n");
	fflush(stdout);
	/***** Set up Parameters *****/
/*	while(1)
	{
		if(slv_handles[slave_number].motor_config_param.update_flag == 1)
		{
			slv_handles[slave_number].motor_config_param.update_flag = 0;	// reset to update next set of paramaters
			break;
		}

		else
		{
			sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, MOTOR_PARAM_UPDATE, slave_number);
			printf (".");
			fflush(stdout);

		}
	}*/

	if (operation_mode == CSV)
	{
		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				slv_handles[slave_number].motor_config_param.update_flag = 0; // reset to update next set of paramaters
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, VELOCITY_CTRL_UPDATE, slave_number);  //mode specific updates
				printf (".");
				fflush(stdout);
			}
		}

		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				//slv_handles[slave_number].motor_config_param.update_flag = 0;
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, CSV_MOTOR_UPDATE, slave_number);		//mode specific updates
				printf (".");
				fflush(stdout);
			}
		}
	}
	else if (operation_mode == CSP)
	{
		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				slv_handles[slave_number].motor_config_param.update_flag = 0;
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, POSITION_CTRL_UPDATE, slave_number);		//mode specific updates
				printf (".");
				fflush(stdout);
			}
		}

		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				//slv_handles[slave_number].motor_config_param.update_flag = 0;
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, CSV_MOTOR_UPDATE, slave_number);		//mode specific updates
				printf (".");
				fflush(stdout);
			}
		}

	}

	else if (operation_mode == PV)
	{
		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				slv_handles[slave_number].motor_config_param.update_flag = 0; // reset to update next set of paramaters
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, VELOCITY_CTRL_UPDATE, slave_number);  //mode specific updates
				printf (".");
				fflush(stdout);
			}
		}
		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				//slv_handles[slave_number].motor_config_param.update_flag = 0;
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, PV_MOTOR_UPDATE, slave_number);  //mode specific updates
				printf (".");
				fflush(stdout);
			}
		}
	}

	else if (operation_mode == PP)
	{
		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				slv_handles[slave_number].motor_config_param.update_flag = 0;
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, POSITION_CTRL_UPDATE, slave_number);		//mode specific updates
				printf (".");
				fflush(stdout);
			}
		}

		while(1)
		{
			if(slv_handles[slave_number].motor_config_param.update_flag == 1)
			{
				//slv_handles[slave_number].motor_config_param.update_flag = 0;
				break;
			}
			else
			{
				sdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves, PP_MOTOR_UPDATE, slave_number);  //mode specific updates
				printf (".");
				fflush(stdout);
			}
		}
	}
	printf ("\n");
	fflush(stdout);

//*/


	/**********************output Mode of Operation******************/
	while(1)
	{
			pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
			if(master_setup->op_flag)
			{
				slv_handles[slave_number].operation_mode = operation_mode;
				/*************check operation_mode display**************/
				if (slv_handles[slave_number].operation_mode_disp == operation_mode)
					break;
			}
			else
				continue;
	}
	#ifndef print_slave
	printf("operation_mode enabled\n");
	fflush(stdout);
	#endif

	return 1;
}


int enable_operation(int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	int op_enable_state = 0;
	int status_word = 0;

	while(!op_enable_state && master_setup->op_flag)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			set_controlword(SWITCH_ON, slave_number, slv_handles);
			/*************check op_enable_state**************/
			status_word = read_statusword(slave_number, slv_handles);
			op_enable_state = check_op_enable(status_word);
		}
		else
			continue;
	}

	#ifndef print_slave
	printf("operation enabled\n");
	fflush(stdout);
	#endif

	return 1;
}

int quick_stop_position(int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	int quick_stop_active = 0, quick_stop_inactive = 1;
	int status_word;
	while(!quick_stop_active && master_setup->op_flag)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			set_controlword(ENABLE_OPERATION_CONTROL|(~QUICK_STOP_CONTROL & 0x000F)|ENABLE_VOLTAGE_CONTROL|SWITCH_ON_CONTROL, slave_number, slv_handles);
			/*************check quick_stop_state**************/
			status_word = read_statusword(slave_number, slv_handles);
			quick_stop_active = check_quick_stop_active(status_word);
		}
		else
			continue;
		//printf("\n stats %x", status_word);
	}
#ifndef print_slave
	printf("quick_stop_active\n");
	fflush(stdout);
#endif



	while(quick_stop_inactive)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			/*************check quick_stop_state**************/
			status_word = read_statusword(slave_number, slv_handles);
			quick_stop_inactive = check_quick_stop_active(status_word);
			//printf("%d\n",quick_stop_active);
			//printf("\n stats %x", status_word);
		}
		else
			continue;
	}
	set_position_deg(get_position_actual_deg(slave_number, slv_handles)*10000, slave_number, slv_handles);
	#ifndef print_slave
	printf("ack stop received \n");
	fflush(stdout);
	#endif
}

int renable_ctrl_quick_stop(int operation_mode, int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	/**********************output Mode of Operation******************/
	while(1)
	{
			pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
			if(master_setup->op_flag)
			{
				slv_handles[slave_number].operation_mode = 100;
				/*************check operation_mode display**************/
				set_controlword(QUICK_STOP_CONTROL, slave_number, slv_handles);
				//status_word = read_statusword();
				//op_enable_state = check_op_enable(status_word);
				if (slv_handles[slave_number].operation_mode_disp == 100)
					break;
				//printf("operation_m %d\n",slv_handles[slave_number].operation_mode_disp);
			}
			else
				continue;
	}
	#ifndef print_slave
	printf("operation_mode reset enabled\n");
	fflush(stdout);
	#endif

	/**********************output Mode of Operation******************/
//	while(1)
//	{
//			pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
//			if(master_setup->op_flag)
//			{
//				slv_handles[slave_number].operation_mode = operation_mode;
//				/*************check operation_mode display**************/
//				if (slv_handles[slave_number].operation_mode_disp == operation_mode)
//					break;
//			}
//			else
//				continue;
//	}
//	#ifndef print_slave
//	printf("operation_mode enabled\n");
//	fflush(stdout);
	//#endif
}

int shutdown_operation(int operation_mode, int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	int ack_stop = 1, status_word;
	while(ack_stop)
	{
			pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
			if(master_setup->op_flag)
			{
				//if(operation_mode == CSV)
				slv_handles[slave_number].operation_mode = 100;
				/*************check operation_mode display**************/
				set_controlword(SHUTDOWN, slave_number, slv_handles);
				status_word = read_statusword(slave_number, slv_handles);
				ack_stop = check_shutdown_active(status_word);
				//printf("status %x\n",status_word);
				//op_enable_state = check_op_enable(status_word);
			}
			else
				continue;
	}
	#ifndef print_slave
	printf("shutdown  \n");
	fflush(stdout);
	#endif
}

int quick_stop_velocity(int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	int quick_stop_active = 0, status_word, ack_stop;
	while(!quick_stop_active && master_setup->op_flag)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			set_controlword(ENABLE_OPERATION_CONTROL|(~QUICK_STOP_CONTROL & 0x000F)|ENABLE_VOLTAGE_CONTROL|SWITCH_ON_CONTROL, slave_number, slv_handles);
			/*************check quick_stop_state**************/
			status_word = read_statusword(slave_number, slv_handles);
			quick_stop_active = check_quick_stop_active(status_word);
		}
		else
			continue;
		//printf("\n stats %x", status_word);
	}

	#ifndef print_slave
	printf("quick_stop_active\n");
	fflush(stdout);
	#endif

	ack_stop = 1;
	while(ack_stop)
	{
		pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
		if(master_setup->op_flag)
		{
			/*************check quick_stop_state**************/
			status_word = read_statusword(slave_number, slv_handles);
			ack_stop = check_quick_stop_inactive(status_word);;
			//printf("%d\n",quick_stop_active);
			//printf("\n stats %x", status_word);
		}
		else
			continue;
	}

	#ifndef print_slave
	printf("quick stop executed \n");
	fflush(stdout);
	#endif
}

int renable_velocity_ctrl(int slave_number, master_setup_variables_t *master_setup, ctrlproto_slv_handle *slv_handles, int total_no_of_slaves)
{
	/**********************output Mode of Operation******************/
	while(1)
	{
			pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
			if(master_setup->op_flag)
			{
				slv_handles[slave_number].operation_mode = 100;
				/*************check operation_mode display**************/
				set_controlword(QUICK_STOP_CONTROL, slave_number, slv_handles);
				//status_word = read_statusword();
				//op_enable_state = check_op_enable(status_word);
				if (slv_handles[slave_number].operation_mode_disp == 100)
					break;
			}
			else
				continue;
	}
	#ifndef print_slave
	printf("operation_mode reset enabled\n");
	fflush(stdout);
	#endif

	while(1)
	{
			pdo_handle_ecat(master_setup, slv_handles, total_no_of_slaves);
			if(master_setup->op_flag)
			{
				slv_handles[slave_number].operation_mode = CSV;
				/*************check operation_mode display**************/
				//status_word = read_statusword();
				//op_enable_state = check_op_enable(status_word);
				if (slv_handles[slave_number].operation_mode_disp == CSV)
					break;
			}
			else
				continue;
	}
	#ifndef print_slave
	printf("operation_mode CSV enabled\n");
	fflush(stdout);
	#endif
}
void run_drive()
{
/*	int ready = 0;
	int switch_enable = 0;
	int status_word = 0;
	int switch_on_state = 0;
	int op_enable_state = 0;
	int control_word;

	while(!ready)
	{
		//check ready
		status_word = get_statusword(info);
		ready = check_ready(status_word);
	}
#ifndef print_slave
	printstrln("ready");
#endif

	while(!switch_enable)
	{
		//check switch
		status_word = get_statusword(info);
		switch_enable = check_switch_enable(status_word);
	}
#ifndef print_slave
	printstrln("switch_enable");
#endif

	//out CW for S ON
	control_word = SWITCH_ON_CONTROL;
	set_controlword(control_word, info);


	while(!switch_on_state)
	{
		set_controlword(control_word, info);
		printintln(control_word);
		//check switch_on_state
		status_word = get_statusword(info);
		switch_on_state = check_switch_on(status_word);
	}

#ifndef print_slave
	printstrln("switch_on_state");
#endif
	//out CW for En OP
	control_word = ENABLE_OPERATION_CONTROL;
	set_controlword(control_word, info);

	while(!op_enable_state)
	{
		//check op_enable_state
		status_word = get_statusword(info);
		op_enable_state = check_op_enable(status_word);
	}

#ifndef print_slave
	printstrln("op_enable_state");
#endif
*/



}
