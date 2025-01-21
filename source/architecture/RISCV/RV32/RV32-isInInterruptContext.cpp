/**
 * \file
 * \brief isInInterruptContext() implementation for RV32
 *
 * \author Copyright (C) 2016-2024 Kamil Szczygiel https://distortec.com https://freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "distortos/architecture/isInInterruptContext.hpp"

namespace distortos
{

namespace architecture
{

extern bool isInThread;
/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

bool isInInterruptContext()
{
	return isInThread == false;
}

}	// namespace architecture

}	// namespace distortos
