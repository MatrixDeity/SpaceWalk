#include "GameMath.h"

//====================================================================================================

const float GameMath::TO_RAD = acos(-1.0F) / 180.0F;
const float GameMath::TO_DIG = 180.0F / acos(-1.0F);
std::mt19937 GameMath::mGenerator = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());