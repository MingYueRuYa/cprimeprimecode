/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef xibao_cloneable_h
#define xibao_cloneable_h

namespace XIBAO
{

template <typename T>
class ICloneable {
public:
	virtual T clone() = 0;
};

} // XIBAO

#endif // cloneable_h