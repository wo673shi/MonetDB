/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2019 MonetDB B.V.
 */

#ifndef _MAL_EMBEDDED_H
#define _MAL_EMBEDDED_H

#include "monetdb_config.h"
#include "mal_type.h"
#include "mal_client.h"
#include "mal_namespace.h"
#include "mal_exception.h"
#include "mal_linker.h"
#include "mal_import.h"
#include "mal_builder.h"
#include "mal_private.h"

/* #define MAL_EMBEDDED_DEBUG  */

mal_export str malEmbeddedBoot(Client c);
mal_export str malEmbeddedStop(Client c);
mal_export str malEmbeddedRestart(Client c);

#endif /*  _MAL_EMBEDDED_H*/
