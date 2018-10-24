//#include "CSeekArrive.h"

/*void CSeekArrive::setArrivalVelocity(Character* character, Params params) {
	float distanceToTarget = (character->GetLoc() - params.targetPosition).Length();

	if (distanceToTarget <= params.dest_radius) {
		USVec2D desiredSpeed = character->GetLinearVelocity();
		desiredSpeed.Lerp(params.targetPosition, distanceToTarget / params.dest_radius);
		character->SetLinearVelocity(desiredSpeed.mX, desiredSpeed.mY);
	}
}*/