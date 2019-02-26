#include "Track.h"


Load::Load()
{
	
}

Load::Load(int _type, float _bound_max, float _bound_min, float _before, float _back)
{
	this->type = _type;
	this->bound_max = _bound_max;
	this->bound_min = _bound_min;
	this->before = _before;
	this->back = _back;
}

Track::Track()
{
	loads.push_back(Load(1, 477, 473, 475, 471));

	loads.push_back(Load(1, 477, 473, 475, 471));
	loads.push_back(Load(1, 477, 473, 551, 475));
	loads.push_back(Load(13, 555, 473, 477, 551));
	loads.push_back(Load(3, 555, 551, 549, 477));
	loads.push_back(Load(32, 553, 555, 551, 549));
	loads.push_back(Load(2, 553, 549, 539, 551));
	loads.push_back(Load(24, 535, 553, 549, 539));
	loads.push_back(Load(4, 539, 535, 485, 549));
	loads.push_back(Load(42, 481, 539, 535, 485));
	loads.push_back(Load(2, 485, 481, 523, 535));
	loads.push_back(Load(23, 519, 481, 485, 523));
	loads.push_back(Load(3, 523, 519, 549, 485));
	loads.push_back(Load(32, 553, 523, 519, 549));
	loads.push_back(Load(2, 553, 549, 507, 519));
	loads.push_back(Load(24, 503, 553, 549, 507));
	loads.push_back(Load(4, 507, 503, 485, 549));
	loads.push_back(Load(42, 481, 507, 503, 485));
	loads.push_back(Load(2, 485, 481, 491, 503));
	loads.push_back(Load(23, 487, 481, 485, 491));
	loads.push_back(Load(3, 491, 487, 553, 485));
	loads.push_back(Load(3, 491, 487, 557, 553));

}

Track::~Track()
{

}
