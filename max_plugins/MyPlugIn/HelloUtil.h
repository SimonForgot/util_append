#include <max.h>
#include "Max.h"
#include "notify.h"
#include "utilapi.h"
#include "istdplug.h"

class HelloUtil : public UtilityObj
{
public:
	IUtil		*iu;
	Interface	*ip;
	HWND		hPanel;
    
	HelloUtil();
	~HelloUtil();

	void	BeginEditParams(Interface *ip,IUtil *iu);
	void	EndEditParams(Interface *ip,IUtil *iu);
	void	DeleteThis() {}

};