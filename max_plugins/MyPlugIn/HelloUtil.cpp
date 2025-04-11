#include "HelloUtil.h"
#include "Geom/matrix3.h"

HelloUtil::HelloUtil()
{
    iu = NULL;
    ip = NULL;	
}

HelloUtil::~HelloUtil()
{
}

void HelloUtil::BeginEditParams(Interface *ip, IUtil *iu)
{
    this->iu = iu;
    this->ip = ip;
    ip->PushPrompt(_M("Hello World!"));
    //DebugPrint(_M("The LibClassDesc() was called with the input %x"), i);
    Object* pObj = (Object*)GetCOREInterface14()->CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(0, 32670));
    INode* pNode = GetCOREInterface14()->CreateObjectNode(pObj, _M("Hello"));
    pNode->SetNodeTM(0, Matrix3());
    GetCOREInterface14()->ForceCompleteRedraw();
}

void HelloUtil::EndEditParams(Interface *ip, IUtil *iu)
{
    this->iu = NULL;
    ip->PopPrompt();
}