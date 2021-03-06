/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "logMsg/logMsg.h"
#include "logMsg/traceLevels.h"

#include "ngsi/ParseData.h"
#include "ngsi9/RegisterContextResponse.h"
#include "rest/ConnectionInfo.h"
#include "serviceRoutines/postRegisterContext.h"
#include "serviceRoutines/postContextEntityTypes.h"



/* ****************************************************************************
*
* postContextEntityTypes -
*
* POST /v1/registry/contextEntityTypes/{entityType}
* POST /v1/registry/contextEntityTypes/{entityType}/attributes
* POST /ngsi9/contextEntityTypes/{entityType}
* POST /ngsi9/contextEntityTypes/{entityType}/attributes
*
* Payload In:  RegisterProviderRequest
* Payload Out: RegisterContextResponse
*
* 1. Transform RegisterProviderRequest+entityType into a RegisterContextRequest
* 2. Call the Standard operation for RegisterContextRequest
*/
std::string postContextEntityTypes
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  // Other similar functions use a condition based on compV.size(), but in this
  // case is ambiguous so we use compV[0]
  std::string  entityType    = (compV[0] == "v1")? compV[3] : compV[2];
  std::string  answer;

  parseDataP->rcr.res.fill(parseDataP->rpr.res, "", entityType, "");
  answer = postRegisterContext(ciP, components, compV, parseDataP);

  parseDataP->rpr.res.release();
  parseDataP->rcr.res.release();

  return answer;
}
