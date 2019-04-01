#include <stdafx.h>
#include <tinyxml.h>
#include "params.h"

bool ReadParams(const char* filename, Params& params)
{
    TiXmlDocument doc(filename);
    if (!doc.LoadFile())
    {
        fprintf(stderr, "Couldn't read params from %s", filename);
        return false;
    }

    TiXmlHandle hDoc(&doc);

    TiXmlElement* pElem;
    pElem = hDoc.FirstChildElement().Element();
    if (!pElem)
    {
        fprintf(stderr, "Invalid format for %s", filename);
        return false;
    }

    TiXmlHandle hRoot(pElem);
    TiXmlHandle hParams = hRoot.FirstChildElement("params");

	TiXmlElement* paramElem = hParams.FirstChildElement("max_velocity").Element();
    if (paramElem)
        paramElem->Attribute("value", &params.max_velocity);

    paramElem = hParams.FirstChildElement("max_acceleration").Element();
    if (paramElem)
        paramElem->Attribute("value", &params.max_deceleration);
	paramElem = hParams.FirstChildElement("max_acceleration").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_deceleration);

    paramElem = hParams.FirstChildElement("dest_radius").Element();
    if (paramElem)
        paramElem->Attribute("value", &params.dest_radius);

	paramElem = hParams.FirstChildElement("arrive_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.arrive_radius);

    paramElem = hParams.FirstChildElement("target_position").Element();
    if (paramElem)
    {
        paramElem->Attribute("x", &params.target_position.mX);
        paramElem->Attribute("y", &params.target_position.mY);
    }

	paramElem = hParams.FirstChildElement("max_angular_velocity").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_angular_velocity);

	paramElem = hParams.FirstChildElement("max_angular_acceleration").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.max_angular_acceleration);

	paramElem = hParams.FirstChildElement("dest_angle").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.dest_angle);
	paramElem = hParams.FirstChildElement("target_rotation").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.target_rotation);
	paramElem = hParams.FirstChildElement("look_ahead").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.look_ahead);
	paramElem = hParams.FirstChildElement("look_ahead_avoid").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.look_ahead_avoid);
	paramElem = hParams.FirstChildElement("char_radius").Element();
	if (paramElem)
		paramElem->Attribute("value", &params.char_radius);
	
    return true; 
}