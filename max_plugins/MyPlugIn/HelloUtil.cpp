#include "HelloUtil.h"

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
    ip->PushPrompt(_M("Hello World"));
    //DebugPrint(_M("The LibClassDesc() was called with the input %x"), i);
    GetCOREInterface14()->ForceCompleteRedraw();
}

void HelloUtil::EndEditParams(Interface *ip, IUtil *iu)
{
    this->iu = NULL;
    ip->PopPrompt();
}