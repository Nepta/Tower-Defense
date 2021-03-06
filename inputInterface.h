#ifndef __inputInterface_H__
#define __inputInterface_H__

#include "interfaces.h"

/**
 * get mouse position and give it to an interface
 * \param interfaces container that contain all the interface
 */
int pollMouseClick(Interface *interfaces);

#endif /* __inputInterface_H__ */

