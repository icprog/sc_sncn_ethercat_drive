/**
 * @file cia402_wrapper.xc
 * @brief Control Protocol Handler
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <refclk.h>
#include <cia402_wrapper.h>

void print_object_dictionary(client interface i_co_communication i_co)
{
	int sdo_value;
	int index;
	int error;
	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 3);
    {sdo_value, void, void} = i_co.od_get_object_value(index); // Number of pole pairs
    printstr("Number of pole pairs: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 1);
    {sdo_value, void, void} = i_co.od_get_object_value(index); // Nominal Current
    printstr("Nominal Current: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 6);
	{sdo_value, void, void} = i_co.od_get_object_value(index);  //motor torque constant
	printstr("motor torque constant: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(COMMUTATION_OFFSET_CLKWISE, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index); //Commutation offset CLKWISE
    printstr("Commutation offset CLKWISE: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(COMMUTATION_OFFSET_CCLKWISE, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index); //Commutation offset CCLKWISE
    printstr("Commutation offset CCLKWISE: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(MOTOR_WINDING_TYPE, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index); //Motor Winding type STAR = 1, DELTA = 2
    printstr("Motor Winding type: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 4);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Max Speed
    printstr("Max Speed: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_SENSOR_SELECTION_CODE, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Position Sensor Types HALL = 1, QEI_{index, error} =2, QEI_NO_{index, error} =3
    printstr("Position Sensor Types: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_GEAR_RATIO, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Gear ratio
    printstr("Gear ratio: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_POSITION_ENC_RESOLUTION, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//QEI resolution
    printstr("QEI resolution: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(SNCN_SENSOR_POLARITY, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//QEI_POLARITY_NORMAL = 0, QEI_POLARITY_INVERTED = 1
    printstr("QEI POLARITY: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_MAX_TORQUE, 0);
	{sdo_value, void, void} = i_co.od_get_object_value(index);//MAX_TORQUE
	printstr("MAX TORQUE: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_SOFTWARE_POSITION_LIMIT, 1);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//negative positioning limit
    printstr("negative positioning limit: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_SOFTWARE_POSITION_LIMIT, 2);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//positive positioning limit
    printstr("positive positioning limit: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_POLARITY, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//motor driving polarity
    printstr("motor driving polarity: ");printintln(sdo_value);  // -1 in 2'complement 255
	{index, error} =i_co.od_find_index(CIA402_MAX_PROFILE_VELOCITY, 0);
	{sdo_value, void, void} = i_co.od_get_object_value(index);//MAX PROFILE VELOCITY
	printstr("MAX PROFILE VELOCITY: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_PROFILE_VELOCITY, 0);
	{sdo_value, void, void} = i_co.od_get_object_value(index);//PROFILE VELOCITY
	printstr("PROFILE VELOCITY: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_MAX_ACCELERATION, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//MAX ACCELERATION
    printstr("MAX ACCELERATION: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_PROFILE_ACCELERATION, 0);
	{sdo_value, void, void} = i_co.od_get_object_value(index);//PROFILE ACCELERATION
	printstr("PROFILE ACCELERATION: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_PROFILE_DECELERATION, 0);
	{sdo_value, void, void} = i_co.od_get_object_value(index);//PROFILE DECELERATION
	printstr("PROFILE DECELERATION: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_QUICK_STOP_DECELERATION, 0);
	{sdo_value, void, void} = i_co.od_get_object_value(index);//QUICK STOP DECELERATION
	printstr("QUICK STOP DECELERATION: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_TORQUE_SLOPE, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//TORQUE SLOPE
    printstr("TORQUE SLOPE: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_POSITION_GAIN, 1);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Position P-Gain
    printstr("Position P-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_POSITION_GAIN, 2);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Position I-Gain
    printstr("Position I-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_POSITION_GAIN, 3);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Position D-Gain
    printstr("Position D-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_VELOCITY_GAIN, 1);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Velocity P-Gain
    printstr("Velocity P-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_VELOCITY_GAIN, 2);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Velocity I-Gain
    printstr("Velocity I-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_VELOCITY_GAIN, 3);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Velocity D-Gain
    printstr("Velocity D-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_CURRENT_GAIN, 1);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Current P-Gain
    printstr("Current P-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_CURRENT_GAIN, 2);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Current I-Gain
    printstr("Current I-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_CURRENT_GAIN, 3);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//Current D-Gain
    printstr("Current D-Gain: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(LIMIT_SWITCH_TYPE, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//LIMIT SWITCH TYPE: ACTIVE_HIGH = 1, ACTIVE_LOW = 2
    printstr("LIMIT SWITCH TYPE: ");printintln(sdo_value);
	{index, error} =i_co.od_find_index(CIA402_HOMING_METHOD, 0);
    {sdo_value, void, void} = i_co.od_get_object_value(index);//HOMING METHOD: HOMING_NEGATIVE_SWITCH = 1, HOMING_POSITIVE_SWITCH = 2
    printstr("HOMING METHOD: ");printintln(sdo_value);
}

{int, int} homing_sdo_update(client interface i_co_communication i_co)
{
	int homing_method;
	int limit_switch_type;
	int index;
	int error;

	{index, error} =i_co.od_find_index(LIMIT_SWITCH_TYPE, 0);
	{limit_switch_type, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_HOMING_METHOD, 0);
	{homing_method, void, void} = i_co.od_get_object_value(index);

	return {homing_method, limit_switch_type};
}


{int, int, int, int, int} pv_sdo_update(client interface i_co_communication i_co)
{
	int max_profile_velocity;
	int profile_acceleration;
	int profile_deceleration;
	int quick_stop_deceleration;
	int polarity;
	int index;
	int error;

	{index, error} = i_co.od_find_index(CIA402_MAX_PROFILE_VELOCITY, 0);
	{max_profile_velocity, void, void} = i_co.od_get_object_value(index);
	{index, error} = i_co.od_find_index(CIA402_PROFILE_ACCELERATION, 0);
	{profile_acceleration, void, void} = i_co.od_get_object_value(index);
	{index, error} = i_co.od_find_index(CIA402_PROFILE_DECELERATION, 0);
	{profile_deceleration, void, void} = i_co.od_get_object_value(index);
	{index, error} = i_co.od_find_index(CIA402_QUICK_STOP_DECELERATION, 0);
	{quick_stop_deceleration, void, void} = i_co.od_get_object_value(index);
	{index, error} = i_co.od_find_index(CIA402_POLARITY, 0);
	{polarity, void, void} = i_co.od_get_object_value(index);
	return {max_profile_velocity, profile_acceleration, profile_deceleration, quick_stop_deceleration, polarity};
}


{int, int} pt_sdo_update(client interface i_co_communication i_co)
{
	int torque_slope;
	int polarity;
	int index;
	int error;

	{index, error} = i_co.od_find_index(CIA402_TORQUE_SLOPE, 0);
	{torque_slope, void, void} = i_co.od_get_object_value(index);
	{index, error} = i_co.od_find_index(CIA402_POLARITY, 0);
	{polarity, void, void} = i_co.od_get_object_value(index);
	return {torque_slope, polarity};
}


{int, int, int} cst_sdo_update(client interface i_co_communication i_co)
{
	int max_motor_speed;
	int polarity;
	int max_torque;
	int index;
	int error;

	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 4);
	{max_motor_speed, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_POLARITY, 0);
	{polarity, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_MAX_TORQUE, 0);
	{max_torque, void, void} = i_co.od_get_object_value(index);

	return {max_motor_speed, polarity, max_torque};
}

{int, int, int} csv_sdo_update(client interface i_co_communication i_co)
{
	int max_motor_speed;
	int polarity;
	int max_acceleration;
	int index;
	int error;

	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 4);
	{max_motor_speed, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_POLARITY, 0);
	{polarity, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_MAX_ACCELERATION, 0);
	{max_acceleration, void, void} = i_co.od_get_object_value(index);

	return {max_motor_speed, polarity, max_acceleration};
}


{int, int, int, int, int} csp_sdo_update(client interface i_co_communication i_co)
{
	int max_motor_speed;
	int polarity;
	int min;
	int max;
	int max_acc;
	int index;
	int error;

	{index, error} =i_co.od_find_index(CIA402_MOTOR_SPECIFIC, 4);
	{max_motor_speed, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_POLARITY, 0);
	{polarity, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_SOFTWARE_POSITION_LIMIT, 1);
	{min, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_SOFTWARE_POSITION_LIMIT, 2);
	{max, void, void} = i_co.od_get_object_value(index);
	{index, error} =i_co.od_find_index(CIA402_MAX_ACCELERATION, 0);
	{max_acc, void, void} = i_co.od_get_object_value(index);

	return {max_motor_speed, polarity, min, max, max_acc};
}


void update_cst_param_ecat(ProfilerConfig &cst_params, client interface i_co_communication i_co)
{
    {cst_params.max_velocity, cst_params.polarity, cst_params.max_current} = cst_sdo_update(i_co);

    if (cst_params.polarity >= 0) {
        cst_params.polarity = 1;
    } else if (cst_params.polarity < 0) {
        cst_params.polarity = -1;
    }
}

void update_csv_param_ecat(ProfilerConfig &csv_params, client interface i_co_communication i_co)
{
    {csv_params.max_velocity,
        csv_params.polarity,
        csv_params.max_acceleration} = csv_sdo_update(i_co);

    if (csv_params.polarity >= 0) {
        csv_params.polarity = 1;
    } else if (csv_params.polarity < 0) {
        csv_params.polarity = -1;
    }
}

void update_csp_param_ecat(ProfilerConfig &csp_params, client interface i_co_communication i_co)
{
    {csp_params.max_velocity, csp_params.polarity, csp_params.min_position, csp_params.max_position,
            csp_params.max_acceleration} = csp_sdo_update(i_co);
    if (csp_params.polarity >= 0) {
        csp_params.polarity = 1;
    } else if (csp_params.polarity < 0) {
        csp_params.polarity = -1;
    }
}

void update_pt_param_ecat(ProfilerConfig &pt_params, client interface i_co_communication i_co)
{
    {pt_params.current_slope, pt_params.polarity} = pt_sdo_update(i_co);
    if (pt_params.polarity >= 0) {
        pt_params.polarity = 1;
    } else if (pt_params.polarity < 0) {
        pt_params.polarity = -1;
    }
}

void update_pv_param_ecat(ProfilerConfig &pv_params, client interface i_co_communication i_co)
{
    {pv_params.max_velocity, pv_params.acceleration,
            pv_params.deceleration,
            pv_params.max_deceleration,
            pv_params.polarity} = pv_sdo_update(i_co);
}