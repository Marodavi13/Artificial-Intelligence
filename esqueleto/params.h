#ifndef __PARAMS_H__
#define __PARAMS_H__

struct Params
{
    USVec2D target_position;
    float max_velocity;
    float max_acceleration;
	float max_deceleration;
    float dest_radius;
	float arrive_radius;
	float max_angular_velocity;
	float max_angular_acceleration;
	float dest_angle;
	float target_rotation;
	float look_ahead;
	float look_ahead_avoid;
	float char_radius;
};

bool ReadParams(const char* filename, Params& params);

#endif